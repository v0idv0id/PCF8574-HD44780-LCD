# PCF8574 16x2 LCD  for STM32CubeMX projects

This is a very simple way to use the PCF8574(A) port expander with the common LCD HD44780. The "library" was tested with a STM32F407 (STM32F4-Discovery) but should work flawless with any all i2c STM32 systems. The code is very simple and was not intended to be elegant or to cover all features. 

This code can be intergrated into STM32CubeMX projects without any problems or breaking the baim framework. Follow the instructions below to integrate it.

## STM32CubeMX configuration requirements 

This code was tested with STM32CubeMX version 5.6.0 and STM32F4 MCU Package 1.25.0 on a STM32F4-Discovery, STM32F427-Discovery and STM32F1


* Configure an I2Cx connectivity with the parameters:
  * I2C Speed Mode: Standard
  * I2C Clock Speed (Hz): 100000
  * Clock No Strech Mode: Disabled
  * Primary Address Length selection: 7-bit
  * Dual Address Ack: Disabled
  * Primary slave address: 0
  * General Call address detection: Disabled

## Project code preperation 

* Generate the code from CubeMX. Open the main.c and add at the top:
  * ```
    ...
    /* USER CODE BEGIN Includes */
    #include "pcf8574.h"
    /* USER CODE END Includes */
    ...
    ```

* Before the main while add: 
  * ```
    ...
    /* USER CODE BEGIN WHILE */
    pcf8574_init();
    pcf8574_send_string("HELLO WORLD");
    HAL_Delay(1000);
    while (1)
    ...
    ```

* Make a new directory called ```Libs/PCF8574/``` in the base workfolder of the project. Copy the files ```pcf8574.c  pcf8574.h``` to this directory. Then open the ```Makefile``` and add:
  * In the includes section:
    * ```
      # C includes
      C_INCLUDES =  \
      Libs/PCF8574/ \
      ...
      ```
  * In the source section:
    * ```
      # C sources
      C_SOURCES =  \
      Libs/PCF8574/pcf8574.c \
      ...
      ```
* Open up the ```Libs/PCF8574/pcf8574.h``` and modify the address and i2c handler so it fits your settings. In the case below I2C3 was used and A0,A1 and A2 are OPEN on the breakout board:
    * ```
      #define PCF8574_I2C_ADDRESS (0x3F << 1) 
      #define PCF8574_I2C_HANDLER hi2c3
      ```
* Now you can compile the whole project. It should compile without any errors.
  
## Usage in the code

* To run a simple test add the function ``` pcf8574_test()``` in your main loop or right below the ```pcf8574_init()```.
* There common functions are:
  * void pcf8574_clr();
  * void pcf8574_cursor(uint8_t row, uint8_t col);
  * void pcf8574_send_string(char *str);
  * void pcf8574_send_integer(int32_t i);
  * void pcf8574_send_float(double f);

## References

* https://www.mouser.at/datasheet/2/302/PCF8574_PCF8574A-1127673.pdf
* http://site.gravitech.us/MicroResearch/Others/LCD-20x4B/HD44780.pdf
* https://controllerstech.com/interface-lcd-16x2-with-stm32-without-i2c/
* https://hmario.home.xs4all.nl/arduino/LiquidCrystal_I2C/
* https://mikrocontroller.bplaced.net/wordpress/?page_id=2110
  
## License and Author

MIT License - Copyright (c) 2020 v0idv0id - Martin Willner - lvslinux@gmail.com