#pragma once

#include <pthread.h>
#include "stdint.h"
#include "io_bits.h"
#include <wchar.h>

typedef struct lmLedMatrix_ lmLedMatrix;

struct rgb_ {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

typedef struct rgb_ rgb;

lmLedMatrix *lm_matrix_new(uint16_t columns, uint16_t rows, uint8_t pwm_bits);

void lm_matrix_free(lmLedMatrix *matrix);

uint16_t lm_matrix_columns(lmLedMatrix *matrix);

uint16_t lm_matrix_rows(lmLedMatrix *matrix);

uint16_t lm_matrix_pwm_bits(lmLedMatrix *matrix);

void lm_matrix_lock(lmLedMatrix *matrix);

void lm_matrix_unlock(lmLedMatrix *matrix);

inline uint8_t lm_matrix_double_rows(lmLedMatrix *matrix);

io_bits *lm_matrix_bit_plane(lmLedMatrix *matrix);

void lm_matrix_fill(lmLedMatrix *matrix,
        rgb rgb);

void lm_matrix_set_pixel(lmLedMatrix *matrix,
        uint16_t x, uint16_t y,
        rgb rgb);

void lm_matrix_clear(lmLedMatrix *matrix);

void lm_matrix_swap_buffers(lmLedMatrix *matrix);
