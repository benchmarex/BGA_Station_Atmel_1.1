/*
 * adc.c
 *
 *  Created on: 24-11-2014
 *      Author: Marek
 */
#include <avr/io.h>
#include "adc.h"

	    //   float _vkeyboard; //napiecie klawiatury
	       float _vcurrent1; //napiecie sensora pr¹du1
	       float _vcurrent2; //napiecie sensora pr¹du2
	       float _v_msr_vin; //napiecie zasilania

void init_adc(void)
{


	ADCSRA |= (1<<ADEN ) | (1<<ADPS1) |(1<<ADPS0)|(1<<ADPS2);
//	ADCSRA &=~_BV(ADFR);



/*
	//ustawienie wejœc
	DDRF |=(1<<ADC_KEYB);
	DDRF |=(1<<ADC_MSR_VIN);
	DDRF |= (1<<ADC_CURR2);
	DDRF |= (1<<ADC_CURR1);

*/
}

void read_adc(void)

{



	ADMUX = (0b11000010);

		ADCSRA |= (1<<ADSC);//Bit 6 – ADSC: ADC Start Conversion (uruchomienie pojedynczej konwersji
		while(ADCSRA & (1<<ADSC));//czeka na zakoñczenie konwersji

	_v_msr_vin=ADC;

	_v_msr_vin=(_v_msr_vin)/1024*VREF*_div;



//pomiar napiêcia _vcurrent1  1 pomiar na pusto dopiero po nim dzia³a

/*
ADMUX = (0b11000000);     //Ustawienie Wejœcia ADC

	ADCSRA |= (1<<ADSC);//Bit 6 – ADSC: ADC Start Conversion (uruchomienie pojedynczej konwersji
	while(ADCSRA & (1<<ADSC));//czeka na zakoñczenie konwersji

_vcurrent1=ADCW;
_vcurrent1=_vcurrent1/1024*VREF;
*/

ADMUX = (0b11000000);     //Ustawienie Wejœcia ADC

	ADCSRA |= (1<<ADSC);//Bit 6 – ADSC: ADC Start Conversion (uruchomienie pojedynczej konwersji
	while(ADCSRA & (1<<ADSC));//czeka na zakoñczenie konwersji

_vcurrent1=ADC;
_vcurrent1=_vcurrent1/1024*VREF;



_vcurrent2=_vcurrent1;

////////////
/*
ADMUX = (0b11000001);


	          //Ustawienie Wejœcia ADC


	ADCSRA |= (1<<ADSC);//Bit 6 – ADSC: ADC Start Conversion (uruchomienie pojedynczej konwersji
	while(ADCSRA & (1<<ADSC));//czeka na zakoñczenie konwersji

_vcurrent2=ADCW;
_vcurrent2=(_vcurrent2)/1024*VREF;
*/



}
