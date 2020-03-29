#ifndef __PCF8574_H_
#define __PCF8574_H_
#include "main.h"
#include "i2c.h"

#include <stdio.h>

// PCF8574A
// 3F is the address if A0, A1, A2 are OPEN ( all are high => 1 1 1 ) on the PCF8574A breakout board for the LCD display.
// The SHIFT the the left is needed because the R/W byte on the 8-Bit bus is bit[0]; so the 7-bit address must be shifted to the left.
// The STM32-HAL does not do the shift internally so you have to make it. 
#define PCF8574_I2C_ADDRESS (0x3F << 1) 
#define PCF8574_I2C_HANDLER hi2c3

void pcf8574_send_cmd(uint8_t cmd);
void pcf8574_send_data(uint8_t cmd);
void pcf8574_clr();
void pcf8574_cursor(uint8_t row, uint8_t col);
void pcf8574_send_string(char *str);
void pcf8574_send_integer(int32_t i);
void pcf8574_send_float(double f);
void pcf8574_test();

void pcf8574_init();
#endif