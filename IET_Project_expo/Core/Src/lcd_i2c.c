#include "lcd_i2c.h"
#include "stm32f4xx_hal.h"
#include <string.h>

// Store the I2C handle
static I2C_HandleTypeDef *lcd_i2c;

// Send data to LCD (Command or Data)
void LCD_Send(uint8_t data, uint8_t mode) {
    uint8_t high_nibble = (data & 0xF0) | mode | 0x08;  // Backlight ON
    uint8_t low_nibble = ((data << 4) & 0xF0) | mode | 0x08;
    
    uint8_t data_buffer[4] = { high_nibble | 0x04, high_nibble, low_nibble | 0x04, low_nibble };
    HAL_I2C_Master_Transmit(lcd_i2c, LCD_I2C_ADDR, data_buffer, 4, HAL_MAX_DELAY);
    HAL_Delay(1);
}

// Send a command to LCD
void LCD_SendCommand(uint8_t cmd) {
    LCD_Send(cmd, 0x00);
}

// Send a character to LCD
void LCD_SendChar(char data) {
    LCD_Send(data, 0x01);
}

// Send a string to LCD
void LCD_SendString(char *str) {
    while (*str) {
        LCD_SendChar(*str++);
    }
}

// Clear LCD
void LCD_Clear() {
    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
    HAL_Delay(2);
}

// Set cursor position
void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    LCD_SendCommand(addr);
}

// Initialize LCD
void LCD_Init(I2C_HandleTypeDef *hi2c) {
    lcd_i2c = hi2c;
    
    HAL_Delay(50);
    LCD_SendCommand(0x03);
    HAL_Delay(5);
    LCD_SendCommand(0x03);
    HAL_Delay(1);
    LCD_SendCommand(0x03);
    LCD_SendCommand(0x02);
    
    LCD_SendCommand(LCD_CMD_FUNCTION_SET);
    LCD_SendCommand(LCD_CMD_DISPLAY_ON);
    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
    HAL_Delay(2);
    LCD_SendCommand(LCD_CMD_ENTRY_MODE | 0x02);
}
