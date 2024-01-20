## Simple SSD1306 driver

Supported Features:

- I2C interface
- draw patterns
- print characters
- turn on and off the screen

### Example

```c
#include <ssd1306.h>

ssd1306_init();
ssd1306_print("0123456789 !@#$^", Line1);
for (uint16_t x = 0; x < 128; x++) {
    ssd1306_draw_pixel(x, 24);
}
ssd1306_print("ABCDEFGHIJKLMNOP", Line3);
ssd1306_print("QRSTUVWXYZ", Line4);
ssd1306_show();
```

<img src=".assets/image-20220719023923524.png" alt="image-20220719023923524" style="zoom:50%;" />

### How to use

1. Import all source code into your project
2. Implement the function `ssd1306_hal_i2c_write` in `ssd1306_hal.c`
3. Import the header file `ssd1306.h` then use the functions provided there