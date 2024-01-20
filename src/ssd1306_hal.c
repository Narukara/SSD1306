#include "ssd1306_hal.h"

void ssd1306_hal_i2c_write(uint8_t addr,
                           uint8_t reg,
                           uint8_t* data,
                           uint32_t len) {
/**
 * Implement this function!
 *
 * addr - address of slave
 * reg & data - data to write
 * len - length of data
 *
 * I2C sequence:
 * | addr | reg | data[0] | data[1] | ... | data[len-1] |
 */
#error function ssd1306_hal_i2c_write is not implemented!
}
