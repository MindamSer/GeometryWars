#include "Utils.h"

uint32_t c_rgb_to_32bit(uint8_t r, uint8_t g, uint8_t b)
{
    return RED / 255 * r + GREEN / 255 * g + BLUE / 255 * b;
}

std::tuple<uint8_t, uint8_t, uint8_t> c_32bit_to_rgb(uint32_t color)
{
    uint8_t r = (color % 0x01000000) / 0x00010000;
    uint8_t g = (color % 0x00010000) / 0x00000100;
    uint8_t b = (color % 0x00000100);
    return {r, g, b};
}

void draw_pixel(int x, int y, uint32_t color, float intens)
{
    if ((x >= SCREEN_WIDTH) + (x < 0) + (y >= SCREEN_HEIGHT) + (y < 0))
    {
        return;
    }

    uint32_t old_color = buffer[SCREEN_HEIGHT - 1 - y][x];

    auto [old_r, old_g, old_b] = c_32bit_to_rgb(old_color);
    auto [r, g, b] = c_32bit_to_rgb(color);

    r = std::min(int(intens * r) + old_r, 255);
    g = std::min(int(intens * g) + old_g, 255);
    b = std::min(int(intens * b) + old_b, 255);

    buffer[SCREEN_HEIGHT - 1 - y][x] = c_rgb_to_32bit(r, g, b);
}

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

void draw_line(Vector2d p1, Vector2d p2, uint32_t color, float intens)
{
    int x1 = round(p1.getX());
    int y1 = round(p1.getY());
    int x2 = round(p2.getX());
    int y2 = round(p2.getY());

    if (x1 == x2)
    {
        if (y2 < y1)
        {
            swap(y1,y2);
        }
        for (int i = 0; i <= y2 - y1; i++)
        {
            draw_pixel(x1, y1 + i, color, intens);
        }
        return;
    }

    if (y1 == y2)
    {
        if (x2 < x1)
        {
            swap(x1,x2);
        }
        for (int i = 0; i <= x2 - x1; i++)
        {
            draw_pixel(x1 + i, y1, color, intens);
        }
        return;
    }

    draw_pixel(x1, y1, color, intens);
    draw_pixel(x2, y2, color, intens);

    float k = abs((y1 - y2) / (x1 - x2));

    if (k > 1.)
    {
        swap(x1, y1);
        swap(x2, y2);
    }

    if (x2 < x1)
    {
        swap(x1,x2);
        swap(y1,y2);
    }

    float grad = 1. * (y2 - y1) / (x2 - x1);

    float y = y1 + grad;
    for (int x = x1 + 1; x < x2; x++)
    {
        if (k > 1.)
        {
            draw_pixel(int(y), x, color, (1 - (y - int(y))) * intens);
            draw_pixel(int(y+1), x, color, (y - int(y)) * intens);
        }
        else
        {
            draw_pixel(x, int(y), color, (1 - (y - int(y))) * intens);
            draw_pixel(x, int(y+1), color, (y - int(y)) * intens);
        }
        y = y + grad;
    }
}

void draw_poly(Polygon poly, float intens)
{
    for (int i_1 = 0; i_1 < poly.getN(); i_1++)
    {
        int i_2 = (i_1 + 1) % poly.getN();
        draw_line(poly[i_1], poly[i_2], poly.getColor(), intens);
    }
}

void draw_poly(Polygon poly)
{
    draw_poly(poly, 1.);
}

const char* char_to_bitmap(char c)
{
    if (c == ' ')
    {
        return bitmap_space;
    }
    const char* chars = "0123456789score:";
    int i = 0;
    for (int i = 0; i < CHAR_AMOUNT; i++)
    {
        if(chars[i] == c)
        {
            return bitmaps[i];
        }
    }
    return bitmap_wrong;
}

void draw_block(int x, int y, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            draw_pixel(x + j, y - i, WHITE, 1);
        }
    }
}

void draw_char(int x, int y, char c, int font)
{
    const char* bitmap = char_to_bitmap(c);
    for (int i = 0; i < BITMAP_HEIGHT; i++)
    {
        for (int j = 0; j < BITMAP_WIDTH; j++)
        {
            if (bitmap[BITMAP_WIDTH*i+j]=='1')
            {
                draw_block(x + font * j, y - font * i, font);
            }
        }
    }
}

void draw_text(int x, int y, const char* string, int font)
{
    int i = 0;
    int cur_x = x;
    for (int i = 0; string[i] != '\0'; i++)
    {
        draw_char(cur_x, y, string[i], font);
        cur_x += (BITMAP_WIDTH+2) * font;
    }
}

void load_bitmaps(const char* filename)
{
    FILE* p = fopen(filename, "r");
    if (p == NULL)
    {
        printf("Error loading bitmaps!\n%s\nNo file!\n", filename);
        exit(1);
    }
    for (int i = 0; i < CHAR_AMOUNT; i++)
    {
        if (fgets(bitmaps[i], 48, p) == NULL)
        {
            printf("Error loading bitmaps!\n%s\nWrong file!\n", filename);
            exit(2);
        }
    }
}

Polygon load_poly(const char* filename)
{
    FILE* p = fopen(filename, "r");
    if (p == NULL)
    {
        printf("Error loading asset!\n%s\nNo file!\n", filename);
        exit(1);
    }
    char line[48];
    fgets(line, sizeof(line), p);
    int n, rd, k, r, g, b, x, y;
    if (sscanf(line, "%d %d %d %d %d %d", &n, &rd, &k, &r, &g, &b) != 6)
    {
        printf("Error loading asset!\n%s\nWrong first line!\n", filename);
        exit(3);
    }
    Vector2d* arr = new Vector2d[n];
    for (int i = 0; i < n; i++)
    {
        fgets(line, sizeof(line), p);
        if (sscanf(line, "%d %d", &x, &y) != 2)
        {
            printf("Error loading asset!\n%s\nWrong coord lines!\n", filename);
            exit(4);
        }
        arr[i] = Vector2d(x, y);
    }
    return k * Polygon(n, arr, c_rgb_to_32bit(r, g, b), rd);
}

Vector2d get_control()
{
    return
    Vector2d(1, 0) * is_key_pressed(VK_RIGHT) +
    Vector2d(-1, 0) * is_key_pressed(VK_LEFT) +
    Vector2d(0, 1) * is_key_pressed(VK_UP) +
    Vector2d(0, -1) * is_key_pressed(VK_DOWN);
}
