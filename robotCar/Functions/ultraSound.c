/*
* ultraSound.c
*
* Created: 9-11-2017 15:15:53
*  Author: Jelle
*/

#include <ultraSound.h>
#include <commandLCD.h>

int ultraSound(void)
{
	DDRB = 0b11111111;
	DDRD = 0b11111111;    //set portD 4,5,6 as output pins
	DDRC = 0b00000000;
	_delay_ms(500);
	
	PCICR	|= (1<<PCIE1);						//Enabled Pin Change Interrupt 0:7
	PCMSK1	|= (1<<PCINT13);					//Pin Change Interrupt on PB1 enabled
	
	int16_t distance = 0;						//declared 16 bit integer COUNTA = 0
	char sendToLCD [16];						//declared string to send to LCD
	LCD_Init();
	sei();
	
	while (1)
	{
		PORTB	&=	~(1<<PINB0);				//OUTPUT LOW for clear HIGH
		_delay_us(5);
		PORTB	|=	(1<<PINB0);					//OUTPUT trigger HIGH
		_delay_us(15);							//trigger signal must be at least 10uS, 15uS for safety
		PORTB	&=	~(1<<PINB0);				//OUTPUT trigger LOW
		_delay_ms(50);							//Delay for clear signal
		distance = pulse/58/16;					//Duration of pulse/58/16 (16Mhz means 16 pulses per us) is distance in CM
		
		if(distance>15)
		{
			itoa(distance, sendToLCD, 10);			//Converting int distance to char sendToLCD in decimals
			dataport = 0x80;
			wrcomm();
			LCD_SendData("ONS PROJECT      ");
			dataport = (0xC0);
			wrcomm();
			LCD_SendData("AFSTAND = ");
			LCD_SendData(sendToLCD);
			LCD_SendData("cm");
		}
		
		else if(distance < 15 && distance > 0)
		{
			dataport = 0x80;
			wrcomm();
			LCD_SendData("     PAS OP     ");
			dataport = (0xC0);
			wrcomm();
			LCD_SendData("  BOTSGEVAAR!  ");
		}
		
		else
		{
			dataport = 0x80;
			wrcomm();
			LCD_SendData("      ERROR!     ");
			dataport = (0xC0);
			wrcomm();
			LCD_SendData("   GEEN ECHO   ");
		}
	}
	//while(1);
	return 1;
}

ISR(PCINT1_vect)								//If PORTC interrupts (on PCINT13 pin state change) fire ISR
{
	if (i==1)									//this has to be executed second, because this stops the timer
	//i starts at 0 that is why this if-statement has i == 1.
	{
		TCCR1B	=	0;							//Stop timer
		pulse	=	TCNT1;						//store counter in pulse, for calculating distance
		TCNT1	=	0;							//reset counter
		i = 0;									//reset i to 0 so timer starts in next if statement
	}
	
	if (i==0)									//First enable timer (i starts at 0 so this executes first)
	{
		TCCR1B	|=	(1<<CS10);					//Start timer
		i = 1;									//Set i to 1 so timer is stopped and counter is used to calculate distance next interrupt
	}
}
