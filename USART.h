#ifndef UART_H_
#define UART_H_

#include "main.h"

void USART_ini(unsigned int speed);
void USART_Advanced_ini(unsigned int speed,unsigned char data_bit_s,unsigned char parity,unsigned char stop_bit_s );
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_Str(char  *string);
void USART_float(float f);
void USART_int(int _int);
void USART_Flush( void );
void USART_endl(void);

#endif /* UART_H_ */