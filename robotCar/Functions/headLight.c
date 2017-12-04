/*
 * headLight.c
 *
 * Created: 4-12-2017 12:17:23
 *  Author: Thomas
 */ 
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

		if		(val > 75)	{ PORTB=0b00100000; }	// Output pin
		else 				{ PORTB=0b00000000; }
}

void ADC_init(void)
{
	ADMUX |= (1<<REFS0) | (1<<MUX0);
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1);
	sei();
}

int headLight(void)
{
	DDRB |= (1<<DDB5);			// Output pin
	
	ADC_init();
	
	while (1)
	{
		
	}
}
