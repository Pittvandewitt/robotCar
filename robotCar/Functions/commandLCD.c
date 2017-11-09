/*
 * audioLCD.c
 *
 * Created: 9-11-2017 13:16:49
 *  Author: Thomas
 */ 

#include <commandLCD.h>

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
