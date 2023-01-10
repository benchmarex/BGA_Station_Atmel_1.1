/*
 * _keyboard.c
 *
 *  Created on: 25-11-2014
 *      Author: Marek
 */
#include <avr/io.h>
#include "_keyboard.h"
#include "adc.h"

uint8_t _keyboard (void) //funkcja zwraca nr klawisza od 1 do 4
{

	//pomiar napiecia klawiatury wczesniej musi byæ init_adc wywo³any ale to raz w programie
		ADMUX = (0B11000011);

		ADCSRA |= (1<<ADSC);//Bit 6 – ADSC: ADC Start Conversion (uruchomienie pojedynczej konwersji
		while(ADCSRA & (1<<ADSC));//czeka na zakoñczenie konwersji


	uint16_t _vkey;
	uint8_t _key_nr=0;
//	static uint8_t latch_key,_key_nr1;


			_vkey=ADC;
			//_vkeyboard=(_vkeyboard)/1024*VREF; //przeliczenie na napiecie

//sprawdzenie który klawisz zosta³ naciniety, sprawdzane s¹ wartoci binarne ¿eby procedura dzia³a jak najszybcie nie przelicza³a na wolty


///////////////////////////////////////////////

			if (_vkey>759 &&_vkey<779)  //769
			{
			_key_nr=1;
			
			return _key_nr;
			}

///////////////////////////////////////////////

			if (_vkey>505 &&_vkey<525)   //515
			{
			_key_nr=2;
			return _key_nr;
			}


///////////////////////////////////////////////

			if (_vkey>251 &&_vkey<271)   //261
			{
			_key_nr=3;
		     return _key_nr;
			}

/////////////////////////////////////////////

			if (_vkey==0 &&_vkey<20) //0
			{
			_key_nr=4;
		    return _key_nr;
			}

///////////////////////////////////////////////

			if (_vkey>673 &&_vkey<693)   //683
			{
			_key_nr=5; //klawisze 1 i 2 trzymane razem
			return _key_nr;
			}

///////////////////////////////////////////////

			if (_vkey>335 &&_vkey<355)   //345
			{
			_key_nr=6; //klawisze 2 i 3 trzymane razem
			return _key_nr;
			}

////////////////////////////////////////////////

			_key_nr=0;
			//nie wciniety zaden klawisz
 
		//	if (_vkey>1000)  // 1023 ¿aden nie wciniety
		//	{
		//	_key_nr=0;
		//	}  //nie wciniety zaden klawisz
			return 			_key_nr;
		
/*

if (_key_nr>0) {    //naciœniêcie przycisku
if (_key_nr1==_key_nr) {return _key_nr1;}  //CZY KLAWISZ JEST CIAGLE WCISNIETY to zwraca wartosc
else{_key_nr1=_key_nr;} // jesli nie jest to ma natychmiast zaktualizowaæ na now¹ wartoœæ
return _key_nr1;



if  (latch_key>=5) //jesli nie jest wcisniety ten sam klawisz to sprawdza czy wskaznik latch key jest >5 
	 {	latch_key=0;_key_nr1=_key_nr;}  //jesli jest to zeruje go i zmienia wartosc na now¹ 
	 latch_key++;
	  return _key_nr1; //jesli nie to zwieksza latch key i zwraca star¹ wartoœæ bez aktualizacji
	 }
	*/
//}
	
// jesli nie nacisniety zaden klawisz to zwraca 0 i nie robi nic w tej funkcji 


	

	

 



}









