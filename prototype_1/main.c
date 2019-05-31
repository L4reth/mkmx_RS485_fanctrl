//#define F_CPU 16000000UL //kwarc zewnętrzny //definiowane w makefile

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "comm_functions.h"

//Measuring and Calculating RPM
volatile uint16_t u16CounterDiff = 1;
volatile uint16_t u16TmpDiff = 0;
volatile uint16_t u16Period = 0;
//Detecting fan stop
volatile uint8_t u8stopFlag = 0;
volatile uint16_t u16ICPCounter = 0;
//Returning RPM value
volatile uint16_t u16LastRPM = 0;
volatile uint16_t u16SetRPM = 0;
//Device adress in net
volatile uint8_t u8DeviceAdres = 0;

volatile uint8_t szybkosc = 0;

ISR(TIMER2_CAPT_vect)
{
	u16CounterDiff = (TCNT2 - u16TmpDiff);
	u16TmpDiff = TCNT2;
	
	TCCR2B ^= (1<<ICES2);
	
	if(u16CounterDiff > 700)
	{
		u16Period = u16CounterDiff;
	}
	
	u16ICPCounter++;	
}

ISR(TIMER1_OVF_vect)
{
	if(u16ICPCounter == 0)
	{
		u8stopFlag = 1;
	}
	else
		u8stopFlag = 0;
	u16ICPCounter = 0;	
}




int main(void)
{	
	///////// PWM ///////
	       //76543210
 	DDRA = 0b01110000;
 	DDRB = 0b00000000;
	//PORTA = 0b01000000;
	TOCPMSA1 = 0x00; //wybór pinu  =0;
	TOCPMSA0 = 0x00;
		       //76543210	
	TCCR0A =   0b10000011;
	TCCR0B =   0b00000010;
	TOCPMCOE |= (1<<TOCC5OE);  
	OCR0A = 0; //Default speed 680 RPM
	  
	///////// ICP ///////
			 //76543210
	TCCR2A = 0b00000000;
	//TCCR2B = 0b10000010; //prescaler = 8	
	//TCCR2B = 0b10000011; //prescaler = 64
	TCCR2B = 0b11000100; //prescaler = 256
	TIMSK2 |= (1<<ICIE2);
	
	//////// wykrycie zatrzymania
	TCCR1A = 0b00000000;
	TCCR1B = 0b00000100;
	TIMSK1 |= (1<<TOIE1); 	
	
	//////// ADRES ////
	_delay_ms(50);
	//u8DeviceAdres = ReadArdress();
	u8DeviceAdres = 10;
	DDRA |= (1<<DDRA3);
	/////// UART ////////
	Protocolinit();
	//PORTA |= (1<<PORTA4); //wysylanie
	
	sei();
	
	//uart_puts("PwmFan");
	_delay_ms(30);
	PORTA ^= (1<<PORTA3);
	_delay_ms(200);
	PORTA ^= (1<<PORTA3);
	//PORTA &=~ (1<<PORTA4); //odbieranie
	
	//PORTA |= (1<<PORTA4); //wysylanie
	while(1)
	{
// 		if(TXC0 == 1)			
// 			PORTA &=~ (1<<PORTA4); //odbieranie
			
		u16LastRPM = SpeedRetrun(u16Period, u8stopFlag);
		//PID(u16SetRPM, u16LastRPM);		
		ParseData();
		OCR0A = szybkosc;
		
// 		if(TXC0 == 1)			
// 			PORTA &=~ (1<<PORTA4); //odbieranie
// 		PORTA &=~ (1<<PORTA4); //odbieranie
// 		uint16_t u16ster = uart_getc();
//		OCR0A = (u16ster);
// 		if((u16ster & 0xFF00) == 0)
// 		{
// 			OCR0A = u16ster;		
// 		}
				
// 		if((u16ster & 0xFF00) == 0)
// 		{
			//PORTA |= (1<<PORTA4); //wysylanie
// 			u16LastRPM = SpeedRetrun(u16Period, u8stopFlag);
// 			
// 			uart_puts("\ncount_");
// 			sendNumber(u8DeviceAdres);
// 			
// 			uart_puts("\nRPM_");
// 			sendNumber(u16LastRPM);
// 			uart_puts("\n");
// 			_delay_ms(1000);
			//PORTA &=~ (1<<PORTA4); //odbieranie
			//u16ster = 0x00;
		//}		
	};
	
}
