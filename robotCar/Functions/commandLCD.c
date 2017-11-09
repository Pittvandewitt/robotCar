/*
 * audioLCD.c
 *
 * Created: 9-11-2017 13:16:49
 *  Author: Thomas
 */ 

#include <commandLCD.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
/*
void send_a_command(unsigned char command)		//command prototype
{
	PORTD	=	command;						//PORTD is an 8bit word that is sent to the LCD
	PORTB	&=	~(1<<REGISTER);					//registerselection == 0 means the LCD can receive instructions
	PORTB	|=	(1<<ENABLE);					//enable == 1 means start reading
	_delay_ms(10);								//processing time
	PORTB	&=	~(1<<ENABLE);					//enable == 0 means stop reading
	PORTD	|=	0;								//clear the 8 bit word from PORTD
}

void send_a_character(unsigned char character)	//character prototype
{
	PORTD	=	character;						//PORTD stores a character
	PORTB	|=	(1<<REGISTER);
	PORTB	|=	(1<<ENABLE);
	_delay_ms(10);
	PORTB	&=	~(1<<ENABLE);
	PORTD	=	0;
}

void send_a_string(char *string_of_characters)		//string sending prototype
{
	while(*string_of_characters > 0)				//checking to see if PORTD still stores a character
	{
		send_a_character(*string_of_characters++);	//sending characters 1 by 1 till 0 is returned
	}
}
*/