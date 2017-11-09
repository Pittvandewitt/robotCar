/*
 * commandLCD.h
 *
 * Created: 8-11-2017 13:39:11
 *  Author: jelle
 */ 

#ifndef COMMANDLCD_H_
#define COMMANDLCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
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

#endif /* COMMANDLCD_H_ */