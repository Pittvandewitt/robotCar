/*
 * turnSignal.h
 *
 * Created: 9-11-2017 15:08:21
 *  Author: Thomas
 */ 

#ifndef TURNSIGNAL_H_
#define TURNSIGNAL_H_

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#define LEFT_TURN !(PINC & (1<<PINC5))
#define RIGHT_TURN !(PINC & (1<<PINC4))

#endif /* TURNSIGNAL_H_ */