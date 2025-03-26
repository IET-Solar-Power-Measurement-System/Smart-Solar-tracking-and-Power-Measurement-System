#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "stm32f4xx_hal.h"

// Define the LCD I2C Address (Usually 0x27 or 0x3F)
#define LCD_I2C_ADDR 0x4E

// LCD Commands
#define LCD_CMD_CLEAR_DISPLAY 0x01
#define LCD_CMD_RETURN_HOME 0x02
#define LCD_CMD_ENTRY_MODE 0x04
#define LCD_CMD_DISPLAY_ON 0x0C
#define LCD_CMD_DISPLAY_OFF 0x08
#define LCD_CMD_CURSOR_SHIFT 0x10
#define LCD_CMD_FUNCTION_SET 0x28
#define LCD_CMD_SET_DDRAM_ADDR 0x80

// Function Prototypes
void LCD_Init(I2C_HandleTypeDef *hi2c);
void LCD_SendCommand(uint8_t cmd);
void LCD_SendChar(char data);
void LCD_SendString(char *str);
void LCD_Clear();
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif
