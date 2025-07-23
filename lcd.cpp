#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define LCD_DDR DDRC
#define LCD_PORT PORTC
#define LCD_RS PC0
#define LCD_RW PC1
#define LCD_EN PC2
#define LCD_D4 PC4
#define LCD_D5 PC5
#define LCD_D6 PC6
#define LCD_D7 PC7

void send_nibble(uint8_t nibble){
	LCD_PORT = (LCD_PORT & 0x0F) | (nibble << 4);
	LCD_PORT |= (1<<LCD_EN); //Set EN HIGH to latch data...tells LCD "get ready, I'm about to send some data"
	_delay_us(1); //delay for the LCD to detect the EN going HIGH
	LCD_PORT &= ~(1<<LCD_EN); //Set EN LOW to complete the pulse
	_delay_us(100); //Delay for LCD to process the nibble...actually now tells the LCD to latch the nibble just sent
}

void lcd_command(uint8_t cmd){
	LCD_PORT &= ~(1<<LCD_RS); //RS = 0 (command mode)
	LCD_PORT &= ~(1<<LCD_RW); //RW = 0 (write mode)...configure the LCD for a write to the instruction register
	send_nibble(cmd >> 4); //send high nibble
	send_nibble(cmd & 0x0F); //send low nibble
	_delay_ms(5);
}

void lcd_data(uint8_t data){
	LCD_PORT |= (1<<LCD_RS); //data register(mode)
	LCD_PORT &= ~(1<<LCD_RW); //write mode....a write to the data register
	send_nibble(data >> 4);
	send_nibble(data & 0x0F);
	_delay_ms(5);
}

void lcd_init(){
	//Set LCD control and data pins as outputs
	LCD_DDR |= (1<<LCD_RS) | (1<<LCD_RW) | (1<<LCD_EN) | (1<<LCD_D4) | (1<<LCD_D5) | (1<<LCD_D6) | (1<<LCD_D7);
	_delay_ms(20); //LCD takes time to power up, so we wait
	lcd_command(0x02); //return home
	lcd_command(0x28); //4-bit mode, 2 lines, 5*8 font
	lcd_command(0x0C); //display ON, cursor OFF
	lcd_command(0x06); //increment cursor after each character
	lcd_command(0x01); //clear display
	_delay_ms(2); //clear screen takes longer, so we wait
}

void lcd_send_string(const char *str){
	while(*str){
		lcd_data(*str++);
	}
}