#ifndef SSD1306_HAL_H
#define SSD1306_HAL_H

#include <stdint.h>

void ssd1306_hal_i2c_write(uint8_t addr,
                           uint8_t reg,
                           uint8_t* data,
                           uint32_t len);

#endif