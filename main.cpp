#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"

#define THERMOMETER_CHANNEL 0

//ADC global variables
uint16_t adc_results[16];
uint8_t channel = 0;

ISR(ADC_vect){
	adc_results[channel] = ADCL | (ADCH<<8);
	channel++;
	if(channel>15) channel = 0;
	ADMUX = (1<<REFS0) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC);
}

int main(void)
{
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1);
	
    sei();
	
	ADCSRA |= (1<<ADSC);
	
	lcd_init();
	
    while (1) 
    {
		float voltage = adc_results[THERMOMETER_CHANNEL] * 5.0 / 1024.0;
		float temperature = voltage * 100.0;
		
		char tempStr[8];
		dtostrf(temperature, 4, 1, tempStr);
		
		char buffer[16];
		sprintf(buffer, "Temp: %s C", tempStr);
		
		lcd_command(0x80); //Move to beginning of first line
		lcd_send_string(buffer);
		
		_delay_ms(1000);
    }
}

