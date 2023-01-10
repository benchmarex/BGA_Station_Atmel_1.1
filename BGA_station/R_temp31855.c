/*
 * R_temp31855.c
 *
 * Created: 2015-01-21 20:23:59
 *  Author: Marek
 */ 

#include <avr/io.h>
#include "R_temp31855.h"

int16_t  R_temp31855 ( uint8_t x )
{
	uint8_t _spcr; //tymczasowa wartosæ rejestru spcr

	//PORTB |= _BV ( PB0 ); //SS NA HIGH
	// PORTB |=LCD_CE_PIN; //zablokowanie wyswietlacza

	_spcr=SPCR; //(tymczasowe zapamietanie stanu rejestru spi by³y problemy z innymi urzadzeniami wyswietlaczem)

	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0) | (1<<SPR1) | (1<<CPHA);

	int32_t                      d;
	unsigned char                n;

	PORTB &=~(1<<x);  //cs na low
	d = 0;                                // start with nothing
	for (n=3; n!=0xff; n--)
	{
		SPDR = 0;                         // send a null byte
		while ((SPSR & (1<<SPIF)) == 0)  ;    // wait until transfer ends
		d = (d<<8) + SPDR;                // add next byte, starting with MSB
	}

	PORTB |= (1<<x);  //cs na HIGH

	char                        neg;
	neg = FALSE;                // assume a positive raw value
	d = ((d >> 18) & 0x3fff);   // leave only thermocouple value in d
	if (d & 0x2000)             // if thermocouple reading is negative...
	{
		d = -d & 0x3fff;        // always work with positive values
		neg = TRUE;             // but note original value was negative
	}
	d = d + 2;                  // round up by 0.5 degC (2 LSBs)
	d = d >> 2;                 // now convert from 0.25 degC units to degC
	if (neg)  d = -d;           // convert to negative if needed
	SPCR=_spcr;					//przywrócenie stanu rejestru spi
	return  d;                  // return as integer
}

//================================================================================
