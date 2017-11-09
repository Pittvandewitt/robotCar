/*
* lineTracker.c
*
* Created: 9-11-2017 15:03:10
*  Author: Thomas
*/

#include <lineTracker.h>

int lineTracker(void)
{
	DDRB |= (1<<DDB5);
	DDRB |= (1<<DDB4);
	DDRB |= (1<<DDB3);
	DDRB |= (1<<DDB2);
	DDRC &= ~(1<<DDC0);
	
	while (1)
	{
		if((PINC & 0b00000001) == 0)	//PINC.0
		{
			LED5_ON;					// Detected
		}
		else {
			LED5_OFF;					//B5 off
		}
		
		if((PINC & 0b00000010) == 0)	//PINC.1
		{
			LED4_ON;					// Detected
		}
		else {
			LED4_OFF;					//B4 off
		}
		
		if((PINC & 0b00000100) == 0)	//PINC.2
		{
			LED3_ON;					// Detected
		}
		else {
			LED3_OFF;					//B3 off
		}
		
		if((PINC & 0b00001000) == 0)	//PINC.3
		{
			LED2_ON;					// Detected
		}
		else {
			LED2_OFF;					//B2 off
		}
	}
}