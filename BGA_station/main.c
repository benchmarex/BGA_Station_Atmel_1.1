#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>

//#include  <math.h>
//#include <avr/signal.h>
#include <avr/interrupt.h>

#include "i2c_twi.h"
#include "pcd8544.h"
#include "adc.h"
#include "main.h"
#include "TWI_TC74_read.h"
#include "_keyboard.h"
#include  "pid.h"
#include  "R_temp31855.h"

 float _vcur_zero1, _vcur_zero2; ; //napiecie przy 0 przePlywie pr¹du sensora pr¹du1,2
float pb_factor_;
int16_t  T1, T2, w1;
uint16_t Tz1, Tz2;




uint8_t  T3,w2,pb_sw;
volatile uint8_t pwm1,xa;

char _string[13];

volatile uint8_t pw1,pw2;



int main()
{
	LcdInit();  //uwaga w tej funkcji sa jescze ustawiane linie spi innych urzadzen
		//display image
		    LcdContrast(0x7F);
		    LcdClear();
		    LcdImage(waitImage);
		    LcdUpdate();

		 //  _delay_ms(500);

 Init();
_calibrate();
//buzzer(10);
/*
    T1=R_temp31855(PB4);
	T2=R_temp31855(PB5);
	T3=TWI_TC74_read();
*/
//_delay_ms(1000);


////////////////////////////////////////////


//	rdy_relay(1);   //za³¹czenie przekaznikow relay oraz ready

//	_delay_ms(200);
//	rdy_relay(0);
//	_delay_ms(200);

/*
	heater_relay(1); //za³¹czenie przekaznika heater
	_delay_ms(500);
	heater_relay(0);
*/
/////////////////////////////////////////
	////////////////////////////////////



//rdy_relay(1);
//	_pwm(2); // za³¹czenie halogenu z moc¹ podan¹ w procentach
   // _pwm1(0); //moc w procentach
//	_delay_ms(500);


	LcdInit();


while (1)
{


//	read_adc();

	//pr¹d mo¿na przetworzyc na moc w W p=u*i
	//_vcurrent1=_v_msr_vin*_current1();

//	_vcurrent1=_current1();



//memset(_string,0,sizeof(_string[20])*12); // Clear all to 0 so string properly represented



// LcdClear();
//	LcdInit();
T2=R_temp31855(PB5);
T1=R_temp31855(PB4);


	sprintf(_string,"1.LUTOWANIE Pb");pisz_lcd(1);
	sprintf(_string,"2.LUTOWAN. Pbf");pisz_lcd(2);
	sprintf(_string,"3. NIC        ");pisz_lcd(3);
	sprintf(_string,"4. NIC        ");pisz_lcd(4);
	sprintf(_string,"--------------");pisz_lcd(5);
	sprintf(_string,"T1=%d  T2=%d       ",T1,T2);pisz_lcd(6);



/*
	sprintf(_string," MENU WIERSZ5 ");pisz_lcd(5);
	sprintf(_string," MENU WIERSZ6 ");pisz_lcd(6);
*/


	//uint8_t z=0;
//    uint8_t key;

//	key=_keyboard();
	switch(xa)

	{
	case 1:
		pb_sw=0; //0 dla lutu o³owiowego 
		pre_lutuj();
		lutuj();
		LcdClear();
		
		break;


	case 2:
	pb_sw=1; //1 dla lutu bezo³wiowego 
	pre_lutuj();
	lutuj();
	LcdClear();
	//	sprintf(_string,">>PRZYCISK 2<<");pisz_lcd(2);
	// _delay_ms(MENUTIME);
	//	profil_test();
				break;


	case 3:


		sprintf(_string,">>PRZYCISK 3<<");pisz_lcd(3);
		_delay_ms(MENUTIME);
										break;

	case 4:
		sprintf(_string,">>PRZYCISK 4<<");pisz_lcd(4);
		_delay_ms(MENUTIME);
						break;
/*
	case 5:
				sprintf(_string,">>PRZYCISK 5<<");pisz_lcd(5);
	_delay_ms(MENUTIME);
							break;


	case 6:
		sprintf(_string,">>PRZYCISK 6<<");pisz_lcd(6);
	_delay_ms(MENUTIME);
							break;
*/

default:

	_delay_ms(1);

}
	_delay_ms(100);


	/*


sprintf(_string,"TEMP1: %d  ",T1);
sprintf(_string,"TEMP2: %d    ",T2);
sprintf(_string,"TEMP3: %i    ",T3);
uint8_t xx;
xx=_keyboard();
sprintf(_string,"VKEYB: %i      ",xx);
sprintf(_string,"VCUR1: %f      ",_vcurrent1);
sprintf(_string,"VZAS: %f      ",_v_msr_vin);
sprintf(_string,"VCUR2: %f      ",_vcurrent2);
sprintf(_string,"VCRz1: %f      ",_vcur_zero1);
printf(_string,"VCRz2: %f      ",_vcur_zero2);


*/
}
  return 0;
}

////////////////////////////////////////
////////////////////////////////////////

void Init (void)
{
//inicjalizacja  ca³ego urz¹dznia

DDRD=(0B11111111); //USTAWIENIE KIERUNKU
DDRB=(0B11110111);
DDRE=(0B00001000);
DDRF=(0b00000000);


//PORTF=(0b00000000);
PORTD=(0B00001111); //wartoœci pocz¹tkowe
PORTB=(0B01111111);


PORTE=(0B00000000);

////////////
//ustawienia timerów
//
// do pwm sprzetowego góry do funkcji _pwm();

DDRE = 0b00011000;						//Set Pins 3 and 4 to output
		/* 
		 TCCR3A |= (1 << WGM31)|(1<<WGM00); // FAST PWM
		 TCCR3A |= (1 << COM3A1) | (1 << COM3A0);
		  TCCR3A |= (1 << CS31);
		OCR3A = 10000;
		*/
		
	TCCR3B |= (1 << WGM33) | (1 << WGM32);	// Enable Fast PWM mode with ICR3 as top

	  TCCR3B |= (1 << CS31);					// Set prescaler on clock 3 to CPU_Freq/8
	  TCCR3A |= (1 << COM3A1);// | (1 << COM3B1);	// Enable toggling of OCR3A/B in Fast PWM
	  TCCR3A |= (1 << WGM31);					// Enable Fast PWM mode with ICR3 as top
	  TCCR3B |= (1 << WGM33) | (1 << WGM32);	// Enable Fast PWM mode with ICR3 as top
	  ICR3 = CYKL_U;								// 5000us.  200HZ.  Set Top of PWM function at 31500, equivalent to 31.5 ms
	  // Range for CCW is 18025 (Off/Lowest Speed) to 17600 (Max Speed)
	  // Range for CW is 14050 (Off/Lowest Speed) to 14475 (Max Speed)
		

// ////////////////////////////////
	  //ustawienia do softwareowgo _pwm1()

	    TCCR2 |= (1<<WGM21); //TRYB CTC
	  	TCCR2 |= (1<<CS20 |1<<CS22); //prescaler ustwiæ na 1024  jest na 1
	  	TCCR2 &= ~(1<<CS21);

	  	OCR2= 255; //DZIELNIK CZESTOTLIWOSCI DODATKOWY
	  	TIMSK |=(1<<OCIE2); //ZEZWOLENIE NA PRZERW. COMPARE MATCH
	    sei();

}
//========================================================
//PWM
void _pwm (uint16_t wypeln) //W PROCENTACH

{
//ustawienia timerow w funkcji init()

//uint8_t xxx=wypeln*_pwmperiod/255;	//
OCR3A =wypeln;
	  //OCR3B = 250;   //drugie wyjscie ale taka sama czestotliwosc jak wyjscia 3A
}



//pwm programowy do podgrzewacza do³u


void _pwm1 (uint8_t wypeln) //W PROCENTACH)
{
	//ustawienia timerow w funkcji init
	pwm1 = wypeln;//0..255

}

//przerwanie softowego pwm1

ISR( TIMER2_COMP_vect )  //wywo³uje siê co 8E6/1024/256=30Hz (33ms)
{

xa=_keyboard();	
	
static uint8_t cnt;
if (cnt>=pwm1)	PORTD &= ~(1<< PD7 );
else PORTD |= (1<< PD7 );	
if (pwm1==255)
cnt=255;
cnt++;
if (cnt==0)
pw1=1; //flaga do wykrycia przerwania w programie
pw2=1;
}



//======================================================



void buzzer (uint8_t _xi)   // ilosc pikniêc buzzera

{

while (_xi>0)

{			PORTD |= _BV ( PD5 );
			_delay_ms(40);
			PORTD &= ~_BV ( PD5 );
			_delay_ms(40);
			_xi--;
}

}

//=========================================================================


void rdy_relay (uint8_t x)   //1 w³¹cza przekaŸnik ready relay zabezpieczaj¹cy. dodatkow steruje przekaznikiem od halogenu sygnal relay ka¿da inna wartosc wy³acza
{
if (x==1)
	{PORTD |= _BV ( PD4 );}
else{PORTD &= ~_BV ( PD4 );}
}


void heater_relay (uint8_t x)   //1 w³¹cza przekaŸnik heater relay zabezpieczaj¹cy. ka¿da inna wartosc wy³acza
{
if (x==1)
	{PORTD |= _BV ( PD7 );}
else{PORTD &= ~_BV ( PD7 );}
}


//kalibracja sensorów pr¹du punkt zero po odlaczeniu przekaznika

void _calibrate (void)
{
//zapamiêtaj stan bitu rdy

uint8_t i;
i=PORTD;


PORTD &= ~_BV ( PD4); //wy³aczenie obci¹¿enie na czas kalibracji
_delay_ms(500);  //czas na uspokojenie sie uk³adu
init_adc();
read_adc();


_vcur_zero1=_vcurrent1*_acs712div;
_vcur_zero2=_vcurrent2*_acs712div;

PORTD=i;
}


///////////////////////////////////////

float _current1 (void)  //zwraca pr¹d w amperach
{
	float curmsr1;
	curmsr1=(_vcur_zero1-(_vcurrent1*_acs712div))*10;
if (curmsr1<0) {curmsr1=0;}

	return curmsr1;
}


void pisz_lcd(uint8_t wiersz) //funkcja pisze na wyswietlacz jako arg nr wiersza
{
uint8_t i;
			for (i = 1; i <= 14; i++ )
			{
     		LcdGotoXYFont(i,wiersz);
			LcdChr(FONT_1X,_string[i-1]);
			LcdUpdate();
			}

}
///////////////////////////////////////

void pre_lutuj (void)  
{
xa=0;	
LcdClear();	
rdy_relay(1);

//wstepne nagrzanie dolnego podgrzewacza zanim sterowanie zostanie przekazane do profilu do temperatury prelutuj
while (!(xa<5 && xa>3)) //ponizsza procedura trwa do momentu wcisniecia przycisku 4
{
T2=R_temp31855(PB5); //odczyt temperatury z podgrzewacza
//xa=_keyboard();

if (T2<pre_lutuj_temp)
{_pwm1(255); // za³¹czenie paneli  z moc¹ podan¹ w przedziale 0-100
sprintf(_string,"  PODGRZEWANIE");pisz_lcd(1);
_delay_ms(MENUTIME2);
sprintf(_string,"> PODGRZEWANIE");pisz_lcd(1);
_delay_ms(MENUTIME2);
sprintf(_string,">>PODGRZEWANIE");pisz_lcd(1);
_delay_ms(MENUTIME2);
sprintf(_string," >PODGRZEWANIE");pisz_lcd(1);
_delay_ms(MENUTIME2);
sprintf(_string,"T2              ");pisz_lcd(3);
sprintf(_string,"%d              ",T2);pisz_lcd(4);}
else {return;}
}

while (xa==4) //ponizsza procedura trwa do momentu zwolnienia przycisku 4
{//xa=_keyboard();
	sprintf(_string,">>POMINIETO<<");pisz_lcd(5);
	_delay_ms(MENUTIME2);
buzzer(1);	
}

_delay_ms(MENUTIME2);
}

void lutuj(void)

{
	const uint8_t profil_gora[] PROGMEM ={				//profil lutowniczy 
		
		//góra nie za³¹cza sie

		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		40,40,40,40,40,  40,40,40,40,40,
		50,60,70,80,90,      100,100,100,100,100,
		110,110,110,110,110, 120,120,120,125,125,



		130,131,131,132,132, 133,133,134,134,135,
		135,136,136,137,137, 138,138,139,139,140,
		140,141,141,142,142, 143,143,144,144,145,
		145,146,146,147,147, 148,148,149,149,150,
		150,151,151,152,152, 153,153,154,154,155,
		155,156,156,157,157, 158,158,159,159,159,
		//góra wspomaga dolny grzejnik
		
		//w³asciwy profil lutowniczy dla góry, dó³ w tym czasie nie powinien przeszkadzac dla do³u w tym przedziale
		//wstawi³em ten sam profil co dla góry jednak to góra ma byæ wiod¹ca mozliwe ¿e dó³ bedzie trzeba os³abiæ w tym miejscu
		
		160,160,160,161,161, 161,161,162,162,162,
		163,163,163,164,164, 164,164,165,165,165,
		166,166,166,167,167, 167,167,168,168,168,
		169,169,169,170,170, 170,170,171,171,171,


		172,172,172,173,173, 173,173,174,174,174,
		175,175,175,176,176, 176,176,177,177,177,
		178,178,178,179,179, 179,179,180,180,180,
		181,181,181,182,182, 182,182,183,183,183,
		184,184,184,185,185, 185,186,186,186,187,
		187,188,188,188,189, 189,189,190,190,190,
		
		
		191,191,191,192,192, 192,193,193,193,194,
		194,195,195,195,196, 196,196,197,197,197,
		198,198,198,199,199, 199,200,200,200,201,
		201,202,202,202,203, 203,203,204,204,204,
		205,205,205,206,206, 206,207,207,207,208,
		208,209,209,209,210, 210,210,211,211,211,
		212,212,212,213,213, 213,214,214,214,215,
		215,216,216,216,217, 217,217,218,218,218,
		219,219,219,220,220, 220,221,221,221,222,
		222,222,223,223,223, 223,224,224,224,225,
		225,225,225,225,225, 225,225,225,225,225,
		225,225,225,225,225, 225,225,225,225,225,
		225,225,225,225,225, 225,225,225,225,225,
		40,40,40,40,40,      40,40,40,40,40,
		40,40,40,40,40,      40,40,40,40,40,
		40,40,40,40,40,      40,40,40,40,40,
		
	0}; // na koñcu profilu musi byc wstawione 0
	const uint8_t profil_dol[] PROGMEM ={				//profil lutowniczy dolnej grza³ki 
		
		// dolna grza³ka wiodaca
		
		40,41,41,42,42, 43,43,44,44,45,
		45,46,46,47,47, 48,48,49,49,50,
		50,51,51,52,52, 53,53,54,54,55,
		55,56,56,57,57, 58,58,59,59,60,
		60,61,61,62,62, 63,63,64,64,65,
		65,66,66,67,67, 68,68,69,69,70,
		70,71,71,72,72, 73,73,74,74,75,
		75,76,76,77,77, 78,78,79,79,80,
		80,81,81,82,82, 83,83,84,84,85,
		85,86,86,87,87, 88,88,89,89,90,
		90,91,91,92,92, 93,93,94,94,95,
		95,96,96,97,97, 98,98,99,99,100,
		100,101,101,102,102, 103,103,104,104,105,
		105,106,106,107,107, 108,108,109,109,110,
		110,111,111,112,112, 113,113,114,114,115,
		115,116,116,117,117, 118,118,119,119,120,
		120,121,121,122,122, 123,123,124,124,125,
		125,126,126,127,127, 128,128,129,129,130,
		
		//od tego momentu pomaga góra, jednak to dó³ jest ca³y czas wiod¹cy
		
		130,131,131,132,132, 133,133,134,134,135,
		135,136,136,137,137, 138,138,139,139,140,
		140,141,141,142,142, 143,143,144,144,145,
		145,146,146,147,147, 148,148,149,149,150,
		150,151,151,152,152, 153,153,154,154,155,
		155,156,156,157,157, 158,158,159,159,159,
		//280s
		
		//w tym przedziale dó³ nie mo¿e byæ wiod¹cy tylko ma byc pomocniczy. Temperature  profiluje górna grza³ka.
		//mo¿liwe ¿e trzeba bêdzie przesun¹æ profil dolnej grza³ki tak by nie przeszkadza³ górze trzeba to sprawdziæ
		
		160,160,160,160,160, 160,160,160,160,160,
		160,160,160,160,160, 160,160,160,160,160,
		160,160,160,160,160, 160,160,160,160,160,
		160,160,160,160,160, 160,160,160,160,160,


		160,160,160,160,160, 165,165,165,165,165,
		165,165,165,165,165, 165,165,165,165,165,
		170,170,170,170,170, 175,175,175,175,175,
		180,180,180,180,180, 180,180,180,180,180,
		180,180,180,180,180, 185,185,185,185,185,
		185,185,185,185,185, 190,190,190,190,190,
		
		
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		190,190,190,190,190, 190,190,190,190,190,
		40,40,40,40,40,      40,40,40,40,40,
		40,40,40,40,40,      40,40,40,40,40,
		40,40,40,40,40,      40,40,40,40,40,
			
	0}; //na koñcu profilu musi byc wstawione 0
	
	
	buzzer(1);
	// animacja

		//	for ( z=0;z<=1; z++)
		//	{
			sprintf(_string,"   LUTOWANIE  ");pisz_lcd(1);
			_delay_ms(MENUTIME2);
			sprintf(_string,">  LUTOWANIE <");pisz_lcd(1);
	 	    _delay_ms(MENUTIME2);
			sprintf(_string,">> LUTOWANIE<<");pisz_lcd(1);
			_delay_ms(MENUTIME2);
			sprintf(_string,">>>LUTOWANIE<<");pisz_lcd(1);
			_delay_ms(MENUTIME2);
		    LcdClear();

	//animacja
	/*}

			//obrazek do procesu lutowania na razie jest pls wait


					 	 	 	 //LcdContrast(0x7F);
							    LcdClear();
							    LcdImage(waitImage);
							    LcdUpdate();
							    _delay_ms(MENUTIME);
							    LcdClear();

			 //obrazek
	*/





uint16_t i;
uint8_t it1;
int it;
//static uint8_t ;

i=0;it1=9;////time out na (9-1)x8,36s;


if (pb_sw==1) pb_factor_=pb_factor;   //jesli factor =1 to jest bezo³ow, jesli nie to o³ow
else{pb_factor_=1;}

init_PID();
init_PID_1();


T2=R_temp31855(PB5); //odczyt temperatury z podgrzewacza
T1=R_temp31855(PB4);

//ekran lutowania i w³asciwa procedura

while (!(xa<5 && xa>3)) //ponizsza procedura trwa do momentu wcisniecia przycisku 4


{
	Tz1=(profil_gora[i]*pb_factor_); //ten sam profil dla bezolowiu i olowiu mnozenie o wspolczynnik dla bezolowiu 
	Tz2=(profil_dol [i]*pb_factor_); 
	
		if (Tz1==0 || Tz2==0) break; //przerywa kiedy koniec któregoœ profilu 
		
		
	
			sprintf(_string,"CZAS = %d           ",i);pisz_lcd(2);
		
		    //xa=_keyboard();
			if (pb_sw==1)
			    {sprintf(_string,"T_MAX_245_nPb ");pisz_lcd(1);}
			else{sprintf(_string,"T_MAX_225_Pb  ");pisz_lcd(1);} //napis zale¿ny od wyboru technologii
				 sprintf(_string,"T1 Tz___T2 Tz ");pisz_lcd(3);
			     sprintf(_string,"%d %d           ",T1,Tz1);pisz_lcd(4);
			     sprintf(_string,"%d    %d %d     ",xa,T2,Tz2);pisz_lcd(5);
			     sprintf(_string,"w1=%d  w2=%d    ",w1,w2);pisz_lcd(6);
		
			  			
						 
	
	
			
	//zabezpieczenie przed nieprawid³owym przyrostem temp
		it=Tz1-40*pb_factor_;
	if (T2<(it))  //róznica 40 st C *wsp dla pfree miedzy odczytana doln¹ a zadan¹ górn¹ ¿eby nie eksplodowa³ chip  mo¿e potem  domkn¹æ na ni¿sz¹ wartoœc 
	{
			
		//time out korzysta z 8 sekundowego przerwania 
		if (pw2==1)   ////flaga wykrycia przerwania w programie
		
		{
		buzzer(3);
		sprintf(_string,"KONIEC ZA = %d  ",it1);pisz_lcd(2);
		sprintf(_string,"PROBLEM !!!     ");pisz_lcd(3);
		
		
		it1--;
		if (it1==0)break;	//time out na (9-1)x8,36s
		pw2=0;
		_delay_ms(MENUTIME);
		}
		
		
		
		
		} //zatrzymuje up³yw czasu i wlacza buzer , daæ tutaj time out bo zatrzymuje sie porfil
		else
		 {i++;  //up³yw czasu i wykonanie górnego profilu
			
			//    xa=_keyboard(); xa zaczytywane w przerwaniu 
				if (xa==2 && i>10) {i=i-10;}  //cofniecie profilu o 10 s jezeli nie jest mniej niz 10 sek
				if (xa==3)		   {i=i+10;} //przyspieszenie profilu o 10 sek
				if (xa==1 && i>1)  {i--;}    //póki wciœniety przycisk 1 to wstrzymany up³yw czasu 
		 
				
			
		
	   		T1=R_temp31855(PB4);
			w1=PID(Tz1,T1); //temperatura zadana i odczytana z funkcji pid zwracane jest bie¿¹ce wysterowanie halegonu
			_delay_ms(CYKL_U); // w argumencie przekazany czas ca³kowania w ms
			_pwm(w1); // za³¹czenie halogenu z moc¹ podan¹ w przedziale 0-255
			
					
					 	
			T2=R_temp31855(PB5); //odczyt temperatury z podgrzewacza
			if (pw1==1)   ////flaga wykrycia przerwania w programie
			{
			// T2=R_temp31855(PB5); //odczyt temperatury z podgrzewacza
	       	w2=PID_1(Tz2,T2); //temperatura zadana i odczytana z funkcji pid zwraca wysterowanie halogenu//	_delay_ms(CYKL_D); // w argumencie przekazany czas ca³kowania w ms
			_pwm1(w2); // za³¹czenie paneli  z moc¹ podan¹ w przedziale 0-255
			pw1=0;
			}}}
			
			
	//T3=TWI_TC74_read();

_pwm(0);
_pwm1(0);
rdy_relay(0); //wy³¹czenie gotowosci
buzzer(2);
}

void profil_test (void)
{
	return;
}


//wywietliæ temp. zadan¹ i bierz¹c¹, nazwê procesu oraz czas który up³yn¹³,
//mo¿liwosci przerwania, wstrzymania, rozpoczêcia od nowa i przyspieszenia

