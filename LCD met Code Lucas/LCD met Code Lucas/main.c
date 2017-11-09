#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define dataport PORTD
#define commport PORTB

#define rs  PORTB4
#define wr  PORTB5
#define en  PORTB3

int LCD_Init(void);
int LCD_SendData(const char *);
int wrcomm(void);
int wrdata(void);

static volatile int pulse = 0;					//used to store counter value for calculating distance
static volatile int i = 0;						//used for starting and stopping counter at pinstate change

int main(void)
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
		
		itoa(distance, sendToLCD, 10);			//Converting int distance to char sendToLCD in decimals
		
		
		dataport = 0x80;
		wrcomm();
		
		LCD_SendData("ONS PROJECT");
		
		dataport = (0xC0);
		wrcomm();
		
		LCD_SendData("AFSTAND = ");
		LCD_SendData(sendToLCD);
		LCD_SendData("cm");
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

int LCD_Init(void)
{

	//Function set
	dataport = 0x38;    //0b00111000, DL = "Low", 8-bit mode; N = "high", 2-line display; F=0, 5x8 display
	wrcomm();
	_delay_us(50);

	//clear LCD screen
	dataport = 0x01;    //clear screen
	wrcomm();
	_delay_ms(2);

	//display on/off control
	dataport = 0x0e;    //0b00001110, D=1, display is turned on; C=1, cursor is turned on; B=0, blink is off
	wrcomm();

	//cursor at line 1
	dataport = 0x80;
	wrcomm();
	_delay_us(50);

	//entry mode set
	dataport = 0x06;
	_delay_us(50);

	//cursor or display shift
	dataport = 0x1C;    //0b00011100, S/C=1, R/L=1, shift all the display to the right, cursor moves according to the display
	wrcomm();
	_delay_us(50);

	return 1;

}

int LCD_SendData(const char *s)
{
	const char *j = s;
	int i;
	for (i = 0; i < strlen(j); i++)
	{
		dataport = j[i];
		wrdata();
	}
	return 1;
}
int wrcomm(void)
{
	commport &= ~(1 << rs);     //selecting command register
	commport &= ~(1 << wr);     //selecting write mode
	_delay_us(200);
	commport |= 1 << en;        //EN = 1
	_delay_ms(1);
	commport &= ~(1 << en);     //EN = 0
	_delay_ms(1);
	return 1;
}
int wrdata(void)
{
	commport |= 1 << rs;        //selecting data register
	commport &= ~(1 << wr);     //selecting write mode
	_delay_us(200);
	commport |= 1 << en;        //EN = 1
	_delay_ms(1);
	commport &= ~(1 << en);     //EN = 0
	_delay_ms(1);
	return 1;
}
