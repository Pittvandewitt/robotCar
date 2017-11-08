/*
 * turnSignal.h
 *
 * Created: 8-11-2017 12:42:00
 * Author : Pittvandewitt
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<DDB1) | (1<<DDB2);
	
    while (1) 
    {
	PORTC |= (1<<PINC5);
	PORTC |= (1<<PINC4);
	
		while (LEFT_TURN)
		{
			_delay_ms(250);
			PINB |= (1<<PINB1);
		}
	
		while (RIGHT_TURN)
		{
			_delay_ms(250);
			PINB |= (1<<PINB2);
		}
	PINB |= (0<<PINB1) | (0<<PINB2);				//End state is always off
	}
}