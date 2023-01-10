/*
 * adc.h
 *
 *  Created on: 24-11-2014
 *      Author: Marek
 */

#ifndef ADC_H_
#define ADC_H_

#define ADC_CURR1   PF0  //acs_current1
#define ADC_CURR2   PF1  //acs_current2
#define ADC_MSR_VIN PF2  //msr_vin
#define ADC_KEYB    PF3  //klawiatura

#define VREF 2.56 //napiêcie odniesienia
#define _div 6.6 //dzielnik do pomiaru nap. zasilania



 extern  float _vcurrent1; //napiecie sensora pr¹du1
 extern  float _vcurrent2; //napiecie sensora pr¹du2
 extern  float _v_msr_vin; //napiecie zasilania


void init_adc(void);
void read_adc(void);





#endif /* ADC_H_ */
