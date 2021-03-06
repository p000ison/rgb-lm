#pragma once

#include <lm/lm.h>
#include "lm.pb-c.h"


int init_controller();


lmFontLibrary *get_font_library();

lmFont *get_default_font();

lmFont *get_small_font();

lmLedMatrix *get_matrix();

lmThread *get_thread();

void free_controller();

void process_buffer(uint8_t *buffer, size_t size);
