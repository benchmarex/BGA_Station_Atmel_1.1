/*
 * pid.c
 *
 *  Created on: 04-12-2014
 *      Author: Marek
 */

#include <avr/io.h>
#include  "pid.h"



//-----------------------
float   a0_1, a1_1, a2_1, b0_1, b1_1, b2_1, ku1_1, ku2_1, ke0_1, ke1_1, ke2_1, Ts_1;
int16_t  u_1, Kp_1, Ki_1, Kd_1, e2_1, e1_1, e0_1, u0_1, u2_1, u1_1;
uint8_t  N_1;

//--------------------
float   a0,a1,a2,b0,b1,b2,ku1,ku2,ke0,ke1,ke2, Ts;
int16_t  u,Kp, Ki,Kd, e2, e1, e0,u0,u2, u1;
uint8_t  N;

void init_PID(void)
{

//Ts=CYKL_U;
//Ts=Ts/1000;    //wartosc w ms 
//Ts = 0.01;   // This must match actual sampling time PID

Ts=CYKL_U/1000;  //wartosc w ms dziele przez 1000 ms bo i cykl tyle wynosi 

N = 10;   	   // filter coefficients
Kp =10;   // proportional gain
Ki =5; 	// integral gain
Kd =100;  	// derivative gain

a0 = (1+N*Ts);
a1 = -(2 + N*Ts);
a2 = 1;
b0 = Kp*(1+N*Ts) + Ki*Ts*(1+N*Ts) + N;
b1 = -(Kp*(2+N*Ts) + Ki*Ts + 2*N);
b2 = Kp + N;

ku1 = a1/a0; 
ku2 = a2/a0;
ke0 = b0/a0;
ke1 = b1/a0;
ke2 = b2/a0;
}

uint16_t  PID(int16_t w_zadana, int16_t w_zmierzona)
{
		e2=e1; e1=e0; u2=u1; u1=u0; // update variables
		
		e0 =w_zadana-w_zmierzona;
		u0 = -ku1*u1 - ku2*u2+ ke0*e0 + ke1*e1 + ke2*e2; // eq (12)
		
		if (u0 > CYKL_U) u0 = CYKL_U; // if (u0 > I_max) u0 = I_max; maksymalna wartoœc regulatora  odpowaiada CYKL_U wiec nie ma co przepisywac po innych zmiennych 
		if (u0 < I_min) u0 = I_min;
		
		a2_1 = 1;
		
				return u0;
}
	
////
//do pid1 dó³




void init_PID_1(void)
{
	Ts_1=CYKL_D;		// This must match actual sampling time PID
	Ts_1=Ts_1/1000;    //wartosc w ms
	N_1 = 10;   	   // filter coefficients

	Kp_1 =55;//22;   // proportional gain
	Ki_1 =1; 	//0.1 integral gain
	Kd_1 =1;  	// derivative gain

	a0_1 = (1+N_1*Ts_1);
	a1_1 = -(2 + N_1*Ts_1);
	a2_1 = 1;
	b0_1 = Kp_1*(1+N_1*Ts_1) + Ki_1*Ts_1*(1+N_1*Ts_1) + N_1;
	b1_1 = -(Kp_1*(2+N_1*Ts_1) + Ki_1*Ts_1 + 2*N_1);
	b2_1 = Kp_1 + N_1;

	ku1_1 = a1_1/a0_1;
	ku2_1 = a2_1/a0_1;
	ke0_1 = b0_1/a0_1;
	ke1_1 = b1_1/a0_1;
	ke2_1 = b2_1/a0_1;
	
	e2_1=0; e1_1=0; u2_1=0; u1_1=0; u0_1=0;
}

uint8_t  PID_1(int16_t w_zadana, int16_t w_zmierzona)
{
	uint8_t u0_11;
	
	e2_1=e1_1; e1_1=e0_1; u2_1=u1_1; u1_1=u0_1; // update variables
	
	e0_1 =w_zadana-w_zmierzona;
	u0_1 =-ku1_1*u1_1 - ku2_1*u2_1+ ke0_1*e0_1 + ke1_1*e1_1 + ke2_1*e2_1; // eq (12)
	//u0_1 =- ku2_1*u2_1+ ke0_1*e0_1 + ke1_1*e1_1 + ke2_1*e2_1;
	if (u0_1 > I_max_1) u0_1 = I_max_1; // maksymalna wartoœc regulatora  odpowaiada tutaj 255
	if (u0_1 < I_min) u0_1 = I_min;
	
	u0_11=u0_1;// rzutowanie na uint8
	//	a2_1 = 1;
	
		
	return u0_11;
	
}