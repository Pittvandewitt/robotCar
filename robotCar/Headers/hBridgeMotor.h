/*
 * hBridgeMotor.h
 *
 * Created: 9-11-2017 15:19:03
 *  Author: Thomas
 */ 


#ifndef HBRIDGEMOTOR_H_
#define HBRIDGEMOTOR_H_

#include <avr/io.h>
#include <stdlib.h>

#define SWITCH_PRESSED !(PINC & (1<<PINC5))
#define SWITCH_PRESSED2 !(PINC & (1<<PINC4))

#endif /* HBRIDGEMOTOR_H_ */