package lm.jna;

import com.sun.jna.*;

/**
 * JNA Wrapper for library <b>lm</b><br>
 * This file was autogenerated by <a href="http://jnaerator.googlecode.com/">JNAerator</a>,<br>
 * a tool written by <a href="http://ochafik.com/">Olivier Chafik</a> that <a href="http://code.google.com/p/jnaerator/wiki/CreditsAndLicense">uses a few opensource projects.</a>.<br>
 * For help, please visit <a href="http://nativelibs4java.googlecode.com/">NativeLibs4Java</a> , <a href="http://rococoa.dev.java.net/">Rococoa</a>, or <a href="http://jna.dev.java.net/">JNA</a>.
 */
public interface LmLibrary extends Library {
    public static final String JNA_LIBRARY_NAME = "lm";
    public static final NativeLibrary JNA_NATIVE_LIB = NativeLibrary.getInstance(LmLibrary.JNA_LIBRARY_NAME);
    public static final LmLibrary INSTANCE = (LmLibrary) Native
            .loadLibrary(LmLibrary.JNA_LIBRARY_NAME, LmLibrary.class);
    public static final int DEFAULT_BASE_TIME_NANOS = (int) 200;

    /**
     * Original signature : <code>lmFontLibrary* lm_fonts_init()</code><br>
     * <i>native declaration : line 17</i>
     */
    LmLibrary.lmFontLibrary lm_fonts_init();

    /**
     * Original signature : <code>void lm_fonts_free(lmFontLibrary*)</code><br>
     * <i>native declaration : line 19</i>
     */
    void lm_fonts_free(LmLibrary.lmFontLibrary lmFontLibraryPtr1);

    /**
     * Original signature : <code>lmFont* lm_fonts_font_new(lmFontLibrary*, const char*, font_size_t)</code><br>
     * <i>native declaration : line 21</i>
     */
    LmLibrary.lmFont lm_fonts_font_new(LmLibrary.lmFontLibrary library, String font, int size);

    /**
     * Original signature : <code>void lm_fonts_font_free(lmFontLibrary*, lmFont*)</code><br>
     * <i>native declaration : line 23</i>
     */
    void lm_fonts_font_free(LmLibrary.lmFontLibrary library, LmLibrary.lmFont font);

    /**
     * Original signature : <code>lmString* lm_fonts_string_new()</code><br>
     * <i>native declaration : line 26</i>
     */
    LmLibrary.lmString lm_fonts_string_new();

    /**
     * Original signature : <code>int lm_fonts_string_width(lmString*)</code><br>
     * <i>native declaration : line 28</i>
     */
    int lm_fonts_string_width(LmLibrary.lmString string);

    /**
     * Original signature : <code>int lm_fonts_string_height(lmString*)</code><br>
     * <i>native declaration : line 30</i>
     */
    int lm_fonts_string_height(LmLibrary.lmString string);

    /**
     * Original signature : <code>void lm_fonts_string_apply_transformation(lmString*, lmMatrix)</code><br>
     * <i>native declaration : line 32</i>
     */
    void lm_fonts_string_apply_transformation(LmLibrary.lmString string, Matrix.ByValue matrix);

    /**
     * Original signature : <code>void lm_fonts_string_free(lmString*)</code><br>
     * <i>native declaration : line 34</i>
     */
    void lm_fonts_string_free(LmLibrary.lmString string);

    /**
     * Original signature : <code>void lm_fonts_populate_string(lmFontLibrary*, lmString*, const char*, lmFont*)</code><br>
     * <i>native declaration : line 36</i>
     */
    void lm_fonts_populate_string(LmLibrary.lmFontLibrary library, LmLibrary.lmString string, String text, LmLibrary.lmFont font);
    /**
     * Original signature : <code>void lm_fonts_populate_wstring(lmFontLibrary*, lmString*, const wchar_t*, lmFont*)</code><br>
     * <i>native declaration : line 38</i>
     */
    void lm_fonts_populate_wstring(LmLibrary.lmFontLibrary library, LmLibrary.lmString string, WString text, LmLibrary.lmFont font);

    /**
     * Original signature : <code>void lm_fonts_render_string(lmLedMatrix*, lmString*, uint16_t, uint16_t, rgb*)</code><br>
     * <i>native declaration : line 40</i>
     */
    void lm_fonts_render_string(LmLibrary.lmLedMatrix matrix, LmLibrary.lmString string, short x, short y, RGB rgb);

    /**
     * Original signature : <code>void lm_fonts_print_string(lmFontLibrary*, lmLedMatrix*, const char*, lmFont*, uint16_t, uint16_t, rgb*)</code><br>
     * <i>native declaration : line 44</i>
     */
    void lm_fonts_print_string(LmLibrary.lmFontLibrary library, LmLibrary.lmLedMatrix matrix, String text, LmLibrary.lmFont font, short x, short y, RGB rgb);

    /**
     * Original signature : <code>void lm_fonts_print_wstring(lmFontLibrary*, lmLedMatrix*, const wchar_t*, lmFont*, uint16_t, uint16_t, rgb*)</code><br>
     * <i>native declaration : line 48</i>
     */
    void lm_fonts_print_wstring(LmLibrary.lmFontLibrary library, LmLibrary.lmLedMatrix matrix, WString text, LmLibrary.lmFont font, short x, short y, RGB rgb);

    /**
     * Original signature : <code>int lm_gpio_init()</code><br>
     * <i>native declaration : line 57</i>
     */
    int lm_gpio_init();

    /**
     * Original signature : <code>uint32_t lm_gpio_init_output(uint32_t)</code><br>
     * <i>native declaration : line 59</i>
     */
    int lm_gpio_init_output(int outputs);

    /**
     * Original signature : <code>void lm_gpio_set_bits(uint32_t)</code><br>
     * <i>native declaration : line 61</i>
     */
    void lm_gpio_set_bits(int value);

    /**
     * Clear the bits that are '1' in the output. Leave the rest untouched.<br>
     * Original signature : <code>void lm_gpio_clear_bits(uint32_t)</code><br>
     * <i>native declaration : line 64</i>
     */
    void lm_gpio_clear_bits(int value);

    /**
     * Write all the bits of "value" mentioned in "mask". Leave the rest untouched.<br>
     * Original signature : <code>void lm_gpio_set_masked_bits(uint32_t, uint32_t)</code><br>
     * <i>native declaration : line 67</i>
     */
    void lm_gpio_set_masked_bits(int value, int mask);

    /**
     * Original signature : <code>uint32_t lm_io_bits_new()</code><br>
     * <i>native declaration : line 74</i>
     */
    int lm_io_bits_new();

    /**
     * Original signature : <code>io_bits* lm_io_bits_value_at(io_bits*, int, int, int, int)</code><br>
     * <i>native declaration : line 76</i>
     */
    LmLibrary.io_bits lm_io_bits_value_at(LmLibrary.io_bits bitplane, int columns, int double_row, int column, int bit);

    /**
     * Original signature : <code>lmLedMatrix* lm_matrix_new(uint16_t, uint16_t, uint8_t)</code><br>
     * <i>native declaration : line 90</i>
     */
    LmLibrary.lmLedMatrix lm_matrix_new(short columns, short rows, byte pwm_bits);

    /**
     * Original signature : <code>void lm_matrix_free(lmLedMatrix*)</code><br>
     * <i>native declaration : line 92</i>
     */
    void lm_matrix_free(LmLibrary.lmLedMatrix matrix);

    /**
     * Original signature : <code>uint16_t lm_matrix_columns(lmLedMatrix*)</code><br>
     * <i>native declaration : line 94</i>
     */
    short lm_matrix_columns(LmLibrary.lmLedMatrix matrix);

    /**
     * Original signature : <code>uint16_t lm_matrix_rows(lmLedMatrix*)</code><br>
     * <i>native declaration : line 96</i>
     */
    short lm_matrix_rows(LmLibrary.lmLedMatrix matrix);

    /**
     * Original signature : <code>uint16_t lm_matrix_pwm_bits(lmLedMatrix*)</code><br>
     * <i>native declaration : line 98</i>
     */
    short lm_matrix_pwm_bits(LmLibrary.lmLedMatrix matrix);

    /**
     * Original signature : <code>void lm_matrix_lock(lmLedMatrix*)</code><br>
     * <i>native declaration : line 100</i>
     */
    void lm_matrix_lock(LmLibrary.lmLedMatrix matrix);

    /**
     * Original signature : <code>void lm_matrix_unlock(lmLedMatrix*)</code><br>
     * <i>native declaration : line 102</i>
     */
    void lm_matrix_unlock(LmLibrary.lmLedMatrix matrix);

    /**
     * Original signature : <code>io_bits* lm_matrix_bit_plane(lmLedMatrix*)</code><br>
     * <i>native declaration : line 106</i>
     */
    LmLibrary.io_bits lm_matrix_bit_plane(LmLibrary.lmLedMatrix matrix);

    /**
     * Original signature : <code>void lm_matrix_fill(lmLedMatrix*, rgb*)</code><br>
     * <i>native declaration : line 108</i>
     */
    void lm_matrix_fill(LmLibrary.lmLedMatrix matrix, RGB rgb);

    /**
     * Original signature : <code>void lm_matrix_set_pixel(lmLedMatrix*, uint16_t, uint16_t, rgb*)</code><br>
     * <i>native declaration : line 111</i>
     */
    void lm_matrix_set_pixel(LmLibrary.lmLedMatrix matrix, short x, short y, RGB rgb);

    /**
     * Original signature : <code>void lm_matrix_clear(lmLedMatrix*)</code><br>
     * <i>native declaration : line 115</i>
     */
    void lm_matrix_clear(LmLibrary.lmLedMatrix matrix);

    /**
     * Original signature : <code>void lm_matrix_swap_buffers(lmLedMatrix*)</code><br>
     * <i>native declaration : line 117</i>
     */
    void lm_matrix_swap_buffers(LmLibrary.lmLedMatrix matrix);

    /**
     * Original signature : <code>lmThread* lm_thread_new(lmLedMatrix*, long)</code><br>
     * <i>native declaration : line 125</i>
     */
    LmLibrary.lmThread lm_thread_new(LmLibrary.lmLedMatrix matrix, NativeLong base_time_nanos);

    /**
     * Original signature : <code>void lm_thread_free(lmThread*)</code><br>
     * <i>native declaration : line 127</i>
     */
    void lm_thread_free(LmLibrary.lmThread thread);

    /**
     * Original signature : <code>void lm_thread_start(lmThread*)</code><br>
     * <i>native declaration : line 129</i>
     */
    void lm_thread_start(LmLibrary.lmThread thread);

    /**
     * Original signature : <code>void lm_thread_wait(lmThread*)</code><br>
     * <i>native declaration : line 131</i>
     */
    void lm_thread_wait(LmLibrary.lmThread thread);

    /**
     * Original signature : <code>int lm_thread_is_paused(lmThread*)</code><br>
     * <i>native declaration : line 2</i>
     */
    int lm_thread_is_paused(LmLibrary.lmThread thread);

    /**
     * Original signature : <code>void lm_thread_pause(lmThread*)</code><br>
     * <i>native declaration : line 4</i>
     */
    void lm_thread_pause(LmLibrary.lmThread thread);

    /**
     * Original signature : <code>void lm_thread_unpause(lmThread*)</code><br>
     * <i>native declaration : line 6</i>
     */
    void lm_thread_unpause(LmLibrary.lmThread thread);

    /**
     * Original signature : <code>void lm_thread_stop(lmThread*)</code><br>
     * <i>native declaration : line 8</i>
     */
    void lm_thread_stop(LmLibrary.lmThread thread);

    /**
     * Original signature : <code>int lm_thread_is_stopped(lmThread*)</code><br>
     * <i>native declaration : line 10</i>
     */
    int lm_thread_is_stopped(LmLibrary.lmThread thread);

    public static class lmFontLibrary extends PointerType {
        public lmFontLibrary(Pointer address) {
            super(address);
        }

        public lmFontLibrary() {
            super();
        }
    }

    public static class lmString extends PointerType {
        public lmString(Pointer address) {
            super(address);
        }

        public lmString() {
            super();
        }
    }

    public static class lmLedMatrix extends PointerType {
        public lmLedMatrix(Pointer address) {
            super(address);
        }

        public lmLedMatrix() {
            super();
        }
    }

    public static class lmThread extends PointerType {
        public lmThread(Pointer address) {
            super(address);
        }

        public lmThread() {
            super();
        }
    }

    public static class lmFont extends PointerType {
        public lmFont(Pointer address) {
            super(address);
        }

        public lmFont() {
            super();
        }
    }

    public static class io_bits extends PointerType {
        public io_bits(Pointer address) {
            super(address);
        }

        public io_bits() {
            super();
        }
    }
}