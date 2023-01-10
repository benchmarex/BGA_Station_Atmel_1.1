/*
 * pid.h
 *
 *  Created on: 04-12-2014
 *      Author: Marek
 */

#ifndef PID_H_
#define PID_H_

#define CYKL_U 1000 //z czas cyklu wl/wyl górnego podgrzewacza w msek czas ca³kowania przekazany przez f init_pid ORAZ okres pwm co czyli 
#define CYKL_D 8356 //dolny podgrzewacz /w sekundach 8E6/1024/256/255  f procesora/dzielnik timera /dodatkowy dzielnik timera/i softw dzilenik w przerwaniu


#define I_min 0 //minimum dla kontorlera pid
#define I_max_1 255 //max dla kontorlera pid_1 dó³


void init_PID(void);
void init_PID_1(void);

uint16_t PID(int16_t, int16_t);
uint8_t PID_1(int16_t, int16_t);

#endif /* PID_H_ */
