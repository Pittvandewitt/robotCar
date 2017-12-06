/*
* hBridgeMotor.c
*
* Created: 9-11-2017 15:17:59
*  Author: dirks
*/

#include <hBridgeMotor.h>

int hBridgeMotor(void)
{
	DDRD |= (1<<DDD0) | (1<<DDD1)| (1<<DDD2)| (1<<DDD5);
	DDRB |= (1<<DDB5);
	DDRB &= ~(1<<DDB7);
	DDRC &= ~(1<<DDC4) | ~(1<<DDC5);

	while (1)
	{
		PORTC |= (1<<PINC4);
		PORTC |= (1<<PINC5);

		if(SWITCH_PRESSED)
		{
			PORTD|= (1<<PIND5);
			PIND |= (1<<PIND1);
		}

		if(SWITCH_PRESSED2)
		{
			PORTD|= (1<<PIND5);
			PIND |= (1<<PIND0);
		}
	}
}