/*
 * TWI_TC74_read.c
 *
 *  Created on: 25-11-2014
 *      Author: Marek
 */
#include <avr/io.h>

#include "i2c_twi.h"

#include "TWI_TC74_read.h"

uint8_t TWI_TC74_read() //zwracana jest w odpowiedzi temp 8bitowa bez znaku chc¹c mierzyc ujemne trzeba zminiæ typ na int
{
	uint8_t data=0;
	i2cSetBitrate(100);


   TWI_start(); //wytworzenie warunku startu i2c

        TWI_write(0b10010001); //adres7bitow +rw bit ma byc na 1
        data= TWI_read(0); //odebrane dane
        TWI_stop(); //zatrzymanie interfejsu
        return data;
}
