/*
 * headLight.c
 *
 * Created: 4-12-2017 12:13:23
 *  Author: Pittvandewitt
 */

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(ADC_vect)
{
		uint16_t val = ADC;

		if (val < 200)
		{
			PORTB=0b00000000;
		}
		else
		{
			PORTB=0b00000001;
		}
}

void ADC_init(void)
{
	ADMUX |= (1<<REFS0) | (1<<MUX0);
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1);
	sei();
}

int headLight(void)
{
	DDRB |= (1<<DDB5) | (1<<DDB4) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
	DDRB &= ~(1<<DDB7);
	
	ADC_init();
	
	while (1)
	{
	}
}
