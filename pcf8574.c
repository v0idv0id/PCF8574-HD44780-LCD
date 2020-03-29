#include "pcf8574.h"

void pcf8574_send_cmd(uint8_t cmd)
{
    // EXAMPLE
    // cmd = 1101 1010 = 0xDA
    // du  = 1101 0000 = 0xD0
    // dl  = 1010 0000 = 0xA0
    // d[0]= 1101 1100 = 0xDC
    // d[1]= 1101 1000 = 0xD8
    // d[2]= 1010 1100 = 0xAC
    // d[3]= 1010 1000 = 0xA8

    uint8_t du, dl;
    uint8_t data[4];
    du = cmd & 0xf0; // & 0b1111 0000
    dl = (cmd << 4) & 0xf0;
    data[0] = du | 0x0C; // | 0b0000 1100
    data[1] = du | 0x08; // | 0b0000 1000
    data[2] = dl | 0x0C; // | 0b0000 1100
    data[3] = dl | 0x08; // | 0b0000 1000
    HAL_I2C_Master_Transmit(&PCF8574_I2C_HANDLER, PCF8574_I2C_ADDRESS, data, sizeof(data), 0xf);
}

void pcf8574_send_data(uint8_t cmd)
{
    uint8_t du, dl;
    uint8_t data[4];
    du = cmd & 0xf0;
    dl = (cmd << 4) & 0xf0;
    data[0] = du | 0x0D; // | 0b0000 1101
    data[1] = du | 0x09; // | 0b0000 1001
    data[2] = dl | 0x0D; // | 0b0000 1101
    data[3] = dl | 0x09; // | 0b0000 1001
    HAL_I2C_Master_Transmit(&PCF8574_I2C_HANDLER, PCF8574_I2C_ADDRESS, data, sizeof(data), 0xf);
}

void pcf8574_clr()
{
    pcf8574_send_cmd(0x80);
    for (int i = 0; i < 70; i++)
    {
        pcf8574_send_data(0x20);
    }
}

void pcf8574_cursor(uint8_t row, uint8_t col)
{
    switch (row)
    {
    case 0:
        col |= 0x80;
        break;
    case 1:
        col |= 0xC0;
        break;
    }
    pcf8574_send_cmd(col);
}

void pcf8574_send_string(char *str)
{
    while (*str)
        pcf8574_send_data(*str++);
}

void pcf8574_send_float(double f)
{
    char str[20];
    sprintf(str, "%f", f);
    pcf8574_send_string(str);
}

void pcf8574_send_integer(int32_t i)
{
    char str[20];
    sprintf(str, "%li", i);
    pcf8574_send_string(str);
}

void pcf8574_test()
{
    int col=0, row=0;
    for (int i = 0; i < 255; i++)
    {
        pcf8574_cursor(row, col);
        pcf8574_send_data(i + 48);
        col++;
        if (col > 15)
        {
            row++;
            col = 0;
        }
        if (row > 1)
            row = 0;
        HAL_Delay(50);
    }
}

void pcf8574_init()
{
    for (uint8_t i = 0; i < 3; i++)
    {
        pcf8574_send_cmd(0x03); // init sequence
        HAL_Delay(5);
    }
    pcf8574_send_cmd(0x02); // 4-bit mode
    HAL_Delay(100);
    pcf8574_send_cmd(0x28); // 2 rows, 5x7 points
    HAL_Delay(1);
    pcf8574_send_cmd(0x01); // clear
    HAL_Delay(2);
    pcf8574_send_cmd(0x06); // entry mode
    HAL_Delay(1);
    pcf8574_send_cmd(0x08); // disp=off , cur=off, blink=off
    pcf8574_send_cmd(0x0C); // disp=on , cur=off, blink=off
    pcf8574_send_cmd(0x0E); // disp=on , cur=on, blink=off
    pcf8574_send_cmd(0x0F); // disp=on , cur=on, blink=on
}
