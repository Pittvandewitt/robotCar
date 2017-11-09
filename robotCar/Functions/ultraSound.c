/*
* ultraSound.c
*
* Created: 9-11-2017 15:15:53
*  Author: Thomas
*/

#include <ultraSound.h>
#include <commandLCD.c>

int ultraSound(void)
{
	DDRD	|=	0b11111111;						//PORTD as OUTPUT
	DDRB	|=	0b00011001;						//PORTB except PB1 as OUTPUT, PB1 as PCINT1 interrupt INPUT
	_delay_ms(50);								//Delay?? Unnecessary??
	PCICR	|= (1<<PCIE0);						//Enabled Pin Change Interrupt 0:7
	PCMSK0	|= (1<<PCINT1);						//Pin Change Interrupt on PB1 enabled
	int16_t distance = 0;						//declared 16 bit integer COUNTA = 0
	char sendToLCD [16];						//declared
	send_a_command(0b00000001);					//Clearing screen
	_delay_ms(50);
	send_a_command(0b00111100);					//Specifying 8bit data and 2 line display, 	5x11 dot font size
	_delay_ms(50);
	send_a_command(0b00001100);					//LCD on
	_delay_ms(50);
	sei();										//interrupts enabled

	while(1)
	{
		PORTB	&=	~(1<<PINB0);				//OUTPUT LOW for clear HIGH
		_delay_us(5);
		PORTB	|=	(1<<PINB0);					//OUTPUT trigger HIGH
		_delay_us(15);							//trigger signal must be at least 10uS, 15uS for safety
		PORTB	&=	~(1<<PINB0);				//OUTPUT trigger LOW
		_delay_ms(1000);						//Delay for clear signal
		distance = pulse/58;					//Duration of pulse/58 is distance in CM
		send_a_string ("DIRK SCHURINK");		//First line on LCD
		send_a_command(0x80 + 0x40 + 0);		//Set cursor to start of second line
		send_a_string ("DISTANCE = ");			//Second line on LCD
		itoa(distance, sendToLCD, 10);			//Converting int COUNTA to char SHOWA in decimals
		send_a_string(sendToLCD);				//Sending distance SHOWA to LCD
		send_a_string ("cm    ");				//Adding cm to second line
		send_a_command(0x80 + 0);				//Set cursor to start of first line
	}
}


ISR(PCINT1_vect)								//If pinstate in PB1 changes start interrupt
{
	if (i==0)									//First enable counter (i starts at 0 so this executes first)
	{
		TCCR1B	|=	(1<<CS10);					//Start counter
		i=1;									//Set i to 1 so other if-statement executes next time pinstate changes
	}

	if (i==1)									//Pinstate changes again so this if statement is now executed as i = 1
	{
		TCCR1B	=	0;							//Stop counter
		pulse	=	TCNT1;						//pulse is counter value
		TCNT1	=	0;							//reset counter value
		i = 0;									//reset i to 0 so counter starts on next pinstate change, count is needed to calculate distance
	}
}
