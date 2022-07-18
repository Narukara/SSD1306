#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>

// commonly used offset
#define Line1 (0)
#define Line2 (256)
#define Line3 (512)
#define Line4 (768)

void ssd1306_init();
void ssd1306_set_display(uint8_t state);
void ssd1306_commit_buffer();
void ssd1306_clear_buffer();
void ssd1306_draw_pixel(uint8_t x, uint8_t y);
void ssd1306_draw_char(uint8_t row,
                       uint8_t col,
                       const uint8_t* font,
                       uint16_t offset);
void ssd1306_print(char* str, uint16_t offset);

#endif
