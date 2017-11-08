/*
 * lineTracker.h
 *
 * Created: 8-11-2017 13:40:58
 *  Author: dirks
 */ 

#ifndef LINETRACKER_H_
#define LINETRACKER_H_

#define LED5_ON PORTB |= (1<<PORTB5)
#define LED5_OFF PORTB &= ~(1<<PORTB5)
#define LED4_ON PORTB |= (1<<PORTB4)
#define LED4_OFF PORTB &= ~(1<<PORTB4)
#define LED3_ON PORTB |= (1<<PORTB3)
#define LED3_OFF PORTB &= ~(1<<PORTB3)
#define LED2_ON PORTB |= (1<<PORTB2)
#define LED2_OFF PORTB &= ~(1<<PORTB2)

#endif /* LINETRACKER_H_ */