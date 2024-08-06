#pragma once

#include "Geometry.h"

extern char bitmaps[CHAR_AMOUNT][BITMAP_HEIGHT * BITMAP_WIDTH];

uint32_t c_rgb_to_32bit(uint8_t r, uint8_t g, uint8_t b);

std::tuple<uint8_t, uint8_t, uint8_t> c_32bit_to_rgb(uint32_t color);

void draw_pixel(int x, int y, uint32_t color, float intens);

void draw_poly(Polygon poly, float intens);

void draw_poly(Polygon poly);

void draw_text(int x, int y, const char* string, int font);

void load_bitmaps(const char* filename);

Polygon load_poly(const char* filename);

Vector2d get_control();
