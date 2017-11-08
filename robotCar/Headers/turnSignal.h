/*
 * IncFile.h
 *
 * Created: 8-11-2017 13:27:37
 *  Author: Thomas
 */ 


#ifndef INCFILE_H_
/*
 * turnSignal.h
 *
 * Created: 8-11-2017 13:40:58
 *  Author: Pittvandewitt
 */

#ifndef TURNSIGNAL_H_
#define TURNSIGNAL_H_

#define F_CPU 16000000
#define LEFT_TURN !(PINC & (1<<PINC5))
#define RIGHT_TURN !(PINC & (1<<PINC4))

#endif /* TURNSIGNAL_ */