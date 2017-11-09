/*
 * hBrugMotor.h
 *
 * Created: 8-11-2017 13:42:23
 *  Author: dirks
 */ 

#ifndef HBRUGMOTOR_H_
#define HBRUGMOTOR_H_

#define LED5_ON PORTB |= (1<<PORTB5)
#define SWITCH_PRESSED !(PINC & (1<<PINC5))
#define SWITCH_PRESSED2 !(PINC & (1<<PINC4))

#endif /* HBRUGMOTOR_H_ */