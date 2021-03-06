
//File includie common functions 
#ifndef comm_functions_h
#define comm_functions_h

#define UART_BAUD_RATE 4800  
#define PL_LENGHT 16
#define ADRR 10

#define PING			0x01 //send back to master information abut module
#define SET_SPEED		0x02 //set Fan speed 
#define RETURN_SPEED	0x03 //send to master information abut current fan speed
#define RETURN_OCR		0x04 //send OCR0A register value	

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <util/crc16.h>
#include "uart.h"

extern volatile uint16_t u16SetRPM;
extern volatile uint16_t u16LastRPM;
extern volatile uint8_t szybkosc; 

//Protocol comunictation functions
void SendData(uint8_t u8Addr, uint8_t u8Cmd, uint8_t *pu8Payload, uint16_t u8PayloadLen);
void SendText(uint8_t u8Addr, char *pcStr);
uint8_t CalcCRC(uint8_t *pu8Data,uint16_t u16Len);
uint8_t ReadArdress(void);
void ParseData(void);
void Protocolinit(void);
void ParseFrame(void);

//Serial port debugging functions
void send16bit(uint16_t value);
void sendNumber(uint32_t _nb);
//Debugging diode function
void blink(void); 

//Fan control functions
void SpeedUp(uint8_t value);
void SpeedDown(uint8_t value);
void PID(uint16_t u16ExpRPM, uint16_t u16RPM); 
uint16_t SpeedRetrun(uint16_t u16RecivedPeriod, uint8_t u8CheckStop);			//Return speed in RPM
//uint8_t DectectStop(void);

#endif