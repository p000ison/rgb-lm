#pragma once

#include "stdint.h"
#include "limits.h"

#define MAX_BITPLANES 11
#define COLOR_SHIFT MAX_BITPLANES - CHAR_BIT

typedef unsigned int bits_t;

union io_bits_ {
    struct {
        bits_t unused : 4;              // 0-3
        bits_t strobe : 1;              // 4
        bits_t unused2 : 2;             // 5..6
        bits_t row : 4;                 // 7..10
        bits_t clock_rev2  : 1;         // 11
        bits_t unused3 : 5;             // 12..16
        bits_t r1 : 1;                  // 17
        bits_t g1 : 1;                  // 18
        bits_t unused4 : 3;
        bits_t b1 : 1;                  // 22
        bits_t r2 : 1;                  // 23
        bits_t g2 : 1;                  // 24
        bits_t b2 : 1;                  // 25
        bits_t unused6 : 1;
        bits_t output_enable_rev2 : 1;  // 27
    } bits;

    uint32_t raw;
};

typedef union io_bits_ io_bits;

uint32_t lm_io_bits_new();

io_bits *lm_io_bits_value_at(io_bits *bitplane, int columns, int double_row, int column, int io_bits);
