#include <string.h>

#include "ssd1306_font.h"
#include "ssd1306_hal.h"

#define SSD1306 (0x78)
// write 0x78
// read  0x79
#define COMD (0x80)
#define DATA (0x40)

/**
 *      buffer(index) <-> display
 * |   0|   1|   2|........| 126| 127|
 * | 128|....                   | 255|
 * | 256|....                   |    |
 * | 384|....                   |    |
 * | 512|....                   |    |
 * | 640|....                   |    |
 * | 768|....                   |    |
 * | 896| 897| 898|........     |1023|
 *
 * every || stands for one byte
 *
 *         |0|
 *         |1|
 *         |2|
 *  || --> |3|
 *         |4|
 *         |5|
 *         |6|
 *         |7|
 *
 * Therefore, there are 8 row, 128 col in totol
 *
 * -----------------------------------------------
 *
 *                                  <-8 bits->
 * a 16x8 character -->    /\    | | | | | | | | |
 *                       16 bits | | | | | | | | |
 *                         \/
 * it has 2 row and 8 col
 *
 *                                              <-col->
 * a (8*row) x col character -->    /\    | | | | | | | | | |
 *                                (8*row) | | | | | | | | | |
 *                                  \/    | | | | | | | | | |
 *                                        | | | | | | | | | |
 */
static uint8_t buffer[1024];

/**
 * @brief initialize ssd1306
 */
void ssd1306_init() {
    uint8_t init[] = {
        0x8D,        // Charge Pump Setting
        COMD, 0x14,  // Enable Charge Pump
        COMD, 0xAF,  // Display ON
        COMD, 0x20,  // Set Memory Addressing Mode
        COMD, 0x00,  // Horizontal Addressing Mode
        COMD, 0x21,  // Set Column Address
        COMD, 0x00,  // Column start address = 0
        COMD, 0x7F,  // Column end address = 127
        COMD, 0x22,  // Set Page Address
        COMD, 0x00,  // Page start Address = 0
        COMD, 0x07   // Page end Address = 7
    };
    ssd1306_hal_i2c_write(SSD1306, COMD, init, 21);
}

/**
 * @brief turn on/off display
 * @param state
 * | 1 = display on
 * | 0 = display off
 */
void ssd1306_set_display(uint8_t state) {
    if (state) {
        ssd1306_hal_i2c_write(SSD1306, COMD, (uint8_t[]){0xAF}, 1);
    } else {
        ssd1306_hal_i2c_write(SSD1306, COMD, (uint8_t[]){0xAE}, 1);
    }
}

/**
 * @brief push buffer to GDDRAM to display it
 */
void ssd1306_commit_buffer() {
    ssd1306_hal_i2c_write(SSD1306, DATA, buffer, 1024);
}

/**
 * @brief clear buffer
 */
void ssd1306_clear_buffer() {
    memset(buffer, 0, sizeof(uint8_t) * 1024);
}

/**
 * @brief draw a pixel in buffer
 * @param x 0 <= x <= 127
 * @param y 0 <= y <= 63
 * @note
 *  0------------------127>  X axis
 *  |
 *  |
 *  |
 *  |
 *  63
 *  \/  Y axis
 */
void ssd1306_draw_pixel(uint8_t x, uint8_t y) {
    buffer[((y & 0xf8) << 4) + x] |= 1 << (y & 7);
}

/**
 * @brief draw a character (or image) in buffer
 * @param row number of rows occupied by character, 1 row == 8 bits == 1
 * byte, 1 <= row <= 8
 * @param col Number of columns occupied by character, 1 col == 1 bit, 1 <=
 * col <= 128
 * @param font font of character
 * @param offset begin position (index of buffer), 0 <= offset <= 1023
 */
void ssd1306_draw_char(uint8_t row,
                       uint8_t col,
                       const uint8_t* font,
                       uint16_t offset) {
    uint16_t index = 0;
    for (uint16_t c = 0; c < col; c++) {
        for (uint16_t r = 0; r < row; r++) {
            buffer[offset + (r << 7) + c] = font[index++];
        }
    }
}

/**
 * @brief print a string
 * @param str length <= 16, end with \0
 * @param offset begin position (index of buffer), 0 <= offset <= 1023
 */
void ssd1306_print(char* str, uint16_t offset) {
    for (char* p = str; *p != 0; p++) {
        ssd1306_draw_char(2, 8, ascii_font_2x8[(*p) - 32], offset);
        offset += 8;
    }
}