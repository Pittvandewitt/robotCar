/*
 * commandLCD.h
 *
 * Created: 8-11-2017 13:39:11
 *  Author: jelle
 */ 

#ifndef COMMANDLCD_H_
#define COMMANDLCD_H_

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define ENABLE              PINB3
#define REGISTER            PINB4                   
#define INTERRUPTPIN        PINB1
#define PCINTERUPT          PCINT1
/*
void send_a_command(unsigned char command);     //function to send commands corresponding with datasheet entries to LCD
void send_a_character(unsigned char character); //function to display characters on the LCD
void send_a_string(char *string_of_characters); //function to allow for multiple characters to be sent at once
 */
static volatile int pulse = 0;                  //used to store counter value for calculating distance
static volatile int i = 0;                      //used for starting and stopping counter at pinstate change

#endif /* COMMANDLCD_H_ */