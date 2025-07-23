#ifndef LCD_H
#define LCD_H

void lcd_init();
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_send_string(const char* str);

#endif