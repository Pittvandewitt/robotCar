/*
* turnSignal.c
*
* Created: 9-11-2017 15:06:54
*  Author: Thomas
*/

#include <turnSignal.h>

int turnSignal(void)
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