#include "font.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedImportStatement"

#include <ft2build.h>

#pragma clang diagnostic pop

#include <freetype.h>
#include <ftglyph.h>

#include <ftcache.h>

FT_Library library;
FTC_Manager manager;
FTC_ImageCache image_cache;

typedef struct CacheFace_ {
    const char *file_path;
    int face_index;

} CacheFace, *PCacheFace;

struct lmFont_ {
    FTC_ScalerRec scaler;
};

struct lmString_ {
    signed int height, width;
    FT_Glyph *glyphs;
    int num_glyphs;

    int use_matrix;

    lmMatrix matrix;
};

static FT_Error face_requester(FTC_FaceID face_id,
        FT_Library library,
        FT_Pointer req_data,
        FT_Face *aface) {
    PCacheFace face = (PCacheFace) face_id;

    FT_Error error = FT_New_Face(library, face->file_path, face->face_index, aface);
    return error;
}

int lm_fonts_init() {
    if (FT_Init_FreeType(&library)) {
        return -1;
    }

    if (FTC_Manager_New(library, 0, 0, 0, face_requester, NULL, &manager)) {
        return -2;
    }

    if (FTC_ImageCache_New(manager, &image_cache)) {
        return -2;
    }

    return 0;
}

lmFont *lm_fonts_font_new(char *font_file, font_size_t size) {
    lmFont *font = malloc(sizeof(lmFont));

    CacheFace *cache_face = malloc(sizeof(CacheFace)); // How to fuck do I clear this?
    cache_face->face_index = 0;
    cache_face->file_path = font_file;

    FTC_ScalerRec scaler;

    scaler.face_id = cache_face;
    scaler.width = size;
    scaler.height = size;
    scaler.pixel = 1;

    font->scaler = scaler;

    return font;
}

FT_Face get_font_face(FTC_ScalerRec scaler) {
    FT_Size size;
    FTC_Manager_LookupSize(manager, &scaler, &size);
    return size->face;
}

static void render_bitmap(lmLedMatrix *matrix, lmString *string, FT_Bitmap bitmap,
        FT_Int x, FT_Int y,
        rgb rgb) {

    FT_Int i, j;

    for (j = 0; j < bitmap.rows; j++) {
        for (i = 0; i < bitmap.width; i++) {
            if (i < 0 || j < 0 || i >= 32 || j >= 32)
                continue;

            // For non-monochrome: unsigned char value = bitmap.buffer[bitmap.width * y + x ];

            unsigned char *row = &bitmap.buffer[bitmap.pitch * j];
            char value = row[(i >> 3)];

            char exists = (value & (128 >> (i & 7))) == 0;

            if (exists) {
                continue;
            }

            uint16_t x_pixel = (uint16_t) (i + x);
            uint16_t y_pixel = (uint16_t) (j + y);

            lm_matrix_set_pixel(matrix, x_pixel, y_pixel, rgb);
        }
    }
}

static void compute_string_bbox(int num_glyphs, FT_Glyph *glyphs, FT_BBox *abbox) {
    int n;
    FT_BBox bbox;
    FT_BBox glyph_bbox;


    /* initialize string bbox to "empty" values */
    bbox.xMin = bbox.yMin = 32000;
    bbox.xMax = bbox.yMax = -32000;

    /* for each glyph image, compute its bounding box, */
    /* translate it, and grow the string bbox          */
    for (n = 0; n < num_glyphs; n++) {
        FT_Glyph_Get_CBox(glyphs[n], ft_glyph_bbox_pixels,
                &glyph_bbox);

        if (glyph_bbox.xMin < bbox.xMin)
            bbox.xMin = glyph_bbox.xMin;

        if (glyph_bbox.yMin < bbox.yMin)
            bbox.yMin = glyph_bbox.yMin;

        if (glyph_bbox.xMax > bbox.xMax)
            bbox.xMax = glyph_bbox.xMax;

        if (glyph_bbox.yMax > bbox.yMax)
            bbox.yMax = glyph_bbox.yMax;
    }

    /* check that we really grew the string bbox */
    if (bbox.xMin > bbox.xMax) {
        bbox.xMin = 0;
        bbox.yMin = 0;
        bbox.xMax = 0;
        bbox.yMax = 0;
    }

    /* return string bbox */
    *abbox = bbox;
}

static inline void create_string(lmString *string, FT_ULong *text, int length, lmFont *font) {
    // Get font face
    FT_Error error;
    FT_Face face = get_font_face(font->scaler);

    // Load glyphs

    FT_GlyphSlot slot = face->glyph;   // a small shortcut
    FT_UInt glyph_index;
    FT_Long use_kerning;
    FT_UInt previous;
    int pen_x, pen_y, n;
    FT_Glyph *glyphs = malloc(sizeof(FT_Glyph) * length);  // glyphs table
    FT_UInt num_glyphs;

    // start at (0,0)
    pen_x = 0;
    pen_y = 0;

    num_glyphs = 0;
    use_kerning = FT_HAS_KERNING(face);
    previous = 0;

    for (n = 0; n < length; n++) {
        FT_Vector pos;

        glyph_index = FT_Get_Char_Index(face, text[n]);

        /* retrieve kerning distance and move pen position */
        if (use_kerning && previous && glyph_index) {
            FT_Vector delta;


            FT_Get_Kerning(face, previous, glyph_index,
                    FT_KERNING_DEFAULT, &delta);

            pen_x += delta.x >> 6;
        }

        /* store current pen position */
        pos.x = pen_x;
        pos.y = pen_y;

        FTC_Node node;
        FT_Glyph cachedGlyph;

        error = FTC_ImageCache_LookupScaler(image_cache, &font->scaler, FT_LOAD_DEFAULT, glyph_index, &cachedGlyph, &node);

        if (error) {
            continue;  /* ignore errors, jump to next glyph */
        }

        error = FT_Glyph_Copy(cachedGlyph, &glyphs[n]);
        FTC_Node_Unref(node, manager);

        if (error) {
            continue;  /* ignore errors, jump to next glyph */
        }

        FT_Glyph_Transform(glyphs[n], 0, &pos);

        /* increment pen position */
        pen_x += slot->advance.x >> 6;

        /* record current glyph index */
        previous = glyph_index;

        /* increment number of glyphs */
        num_glyphs++;
    }

    // Compute box

    FT_BBox string_bbox;
    compute_string_bbox(num_glyphs, glyphs, &string_bbox);

    string->height = (int) (string_bbox.xMax - string_bbox.xMin);
    string->width = (int) (string_bbox.yMax - string_bbox.yMin);
    string->glyphs = glyphs;
    string->num_glyphs = num_glyphs;
}

void render_string(lmLedMatrix *matrix, lmString *string,
        uint16_t x, uint16_t y,
        rgb rgb) {
    int n;
    FT_Error error;
    // Render font and apply transformations
    FT_Glyph image;
    FT_Vector pen;
    pen.x = 0;
    pen.y = 0;

    for (n = 0; n < string->num_glyphs; n++) {
        image = string->glyphs[n];

        FT_Vector delta;
        delta.x = x * 64;
        delta.y = -y * 64;


        FT_Matrix *ft_matrix = 0;

        if (string->use_matrix > 0) {
            FT_Matrix m;

            m.xx = string->matrix.xx * 0x10000L;
            m.xy = string->matrix.xy * 0x10000L;
            m.yx = string->matrix.yx * 0x10000L;
            m.yy = string->matrix.yy * 0x10000L;

            ft_matrix = &m;
        }

        FT_Glyph_Transform(image, ft_matrix, &delta);

        error = FT_Glyph_To_Bitmap(
                &image,
                FT_RENDER_MODE_MONO,
                &pen,     // Apply pen
                0);       // Do not destroy!

        if (!error) {
            FT_BitmapGlyph bit = (FT_BitmapGlyph) image;

            render_bitmap(matrix, string, bit->bitmap,
                    bit->left,
                    string->height - bit->top,
                    rgb);

            /* increment pen position --                       */
            /* we don't have access to a slot structure,       */
            /* so we have to use advances from glyph structure */
            /* (which are in 16.16 fixed float format)         */
            pen.x += image->advance.x >> 10;
            pen.y += image->advance.y >> 10;
        }
    }
}

static inline void init_string(lmString *string) {
    string->use_matrix = 0;
    string->glyphs = 0;
}

lmString *lm_fonts_string_new() {
    lmString *string = malloc(sizeof(lmString));
    init_string(string);
    return string;
}

static inline void free_glyphs(lmString *string) {
    int n;
    for (n = 0; n < string->num_glyphs; ++n) {
        FT_Glyph glyph = string->glyphs[n];
        FT_Done_Glyph(glyph);
    }
    free(string->glyphs);
}

void lm_fonts_string_free(lmString *string) {
    free_glyphs(string);
    free(string);
}

void lm_fonts_print_string(lmLedMatrix *matrix, const char *text, lmFont *font,
        uint16_t x, uint16_t y,
        rgb rgb) {
    lmString string;
    init_string(&string);
    lm_fonts_populate_string(&string, text, font);
    lm_fonts_render_string(matrix, &string, x, y, rgb);
    free_glyphs(&string);
}

void lm_fonts_print_wstring(lmLedMatrix *matrix, const wchar_t *text, lmFont *font,
        uint16_t x, uint16_t y,
        rgb rgb) {
    lmString string;
    init_string(&string);
    lm_fonts_populate_wstring(&string, text, font);
    lm_fonts_render_string(matrix, &string, x, y, rgb);
    free_glyphs(&string);
}

void lm_fonts_font_free(lmFont *font) {
    FTC_FaceID faceID = font->scaler.face_id;
    FTC_Manager_RemoveFaceID(manager, faceID);
    free(faceID);
    free(font);
}

void lm_fonts_free() {
    FTC_Manager_Reset(manager);
    FTC_Manager_Done(manager);
    FT_Done_FreeType(library);
}

#define TO_FT_STRING(text, len, out) int i; FT_ULong out[length]; for (i = 0; i < len; i++) {out[i] = (FT_ULong) text[i];}

void lm_fonts_populate_string(lmString *string, const char *text, lmFont *font) {
    int length = (int) strlen(text);
    TO_FT_STRING(text, length, ft_text);
    create_string(string, ft_text, length, font);
}

void lm_fonts_populate_wstring(lmString *string, const wchar_t *text, lmFont *font) {
    int length = (int) wcslen(text);
    TO_FT_STRING(text, length, ft_text);
    create_string(string, ft_text, length, font);
}

void lm_fonts_render_string(lmLedMatrix *matrix, lmString *string,
        uint16_t x, uint16_t y,
        rgb rgb) {
    render_string(matrix, string, x, y, rgb);
}

int lm_fonts_string_width(lmString *string) {
    return string->width;
}

int lm_fonts_string_height(lmString *string) {
    return string->height;
}

void lm_fonts_string_apply_transformation(lmString *string,
        lmMatrix matrix) {
    string->use_matrix = 1;
    string->matrix = matrix;
}
