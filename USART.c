#include "USART.h"

void USART_ini(unsigned int speed)
{   
	
	//=======================================================================
	/*
	      UBRRL and UBRRH – USART Baud Rate Registers			____________________________________________
	 	 	|URSEL|  -  |  -  |  -  |     UBRR[11:8]    | UBRRH
	 	 	---------------------------------------------  
			|                 UBRR[7:0]                 | UBRRL
			---------------------------------------------  
	*/
	UBRRH = (unsigned char)(speed>>8);
	UBRRL = (unsigned char)speed; //speed
	//=======================================================================
	/*
		     UCSRA – USART Control and Status Register A
	 		 ____________________________________________
	 		| RXC | TXC |UDRE | FE |DOR | PE | U2X |MPCM|
     		 --------------------------------------------
    */
	//UCSRA -> (RXC);   //USART Receive Complete
	//UCSRA -> (TXC);   //USART Transmit Complete
	//UCSRA -> (UDRE);  //USART Data Register(UDR) Empty
	//UCSRA -> (FE);    //Frame Error
	//UCSRA -> (DOR);   //Transmitter Enable
	//UCSRA -> (PE);    //Parity Error
	UCSRA |=(1<<U2X);   //Double the USART transmission speed
	//UCSRA |=(0<<MPCM);  //Multi-processor Communication Mode
    
	//=======================================================================
	  /*
		     UCSRB – USART Control and Status Register B
	 		 ____________________________________________
	 		|RXCIE|TXCIE|UDRIE|RXEN|TXEN|UCSZ2|RXB8|TXB8|
     		 -------------------------------------------- 
      */
	
	UCSRB |=(1<<RXCIE); //RX Complete Interrupt Enable
	UCSRB |=(0<<TXCIE); //TX Complete Interrupt Enable
	UCSRB |=(1<<UDRIE); //USART Data Register(UDR) Empty Interrupt Enable
	UCSRB |=(1<<RXEN);  //Receiver enable
	UCSRB |=(1<<TXEN);  //Transmitter Enable
	UCSRB |=(0<<UCSZ2); //Character Size(frame size) (UCSRB->UCSZ1[2],UCSZ0[1])
	//UCSRB -> RXB8     //Receive Data bit 8
	//UCSRB -> TXB8     //Transmit Data bit 8
	//=======================================================================
	  /*
		       UCSRC – USART Control and Status Register C
	 		 _______________________________________________
	 		|URSEL|UMSEL|UPM1 |UPM0 |USBS |UCSZ1|UCSZ0|UCPOL|
     		 ------------------------------------------------
      */
	
	UCSRC |=(1<<URSEL); //Register Select(S)
	UCSRC |=(0<<UMSEL); //USART Mode Select
	UCSRC |=(0<<UPM1);  //Parity Mode
	UCSRC |=(0<<UPM0);  //Parity Mode
	UCSRC |=(1<<USBS);  //Stop Bit Select
	UCSRC |=(1<<UCSZ1); //Character Size(frame size)
	UCSRC |=(1<<UCSZ0); //Character Size(frame size)
	UCSRC |=(0<<UCPOL); //Clock Polarity(S)
	  
	/*//=======================================================================
			                        UMSEL Bit Settings
			_____________________________________
			| UMSEL |  Mode                     |  
			-------------------------------------
			|   0   |  Asynchronous Operation   |  
			-------------------------------------
			|   1   |  Synchronous Operation    |
			-------------------------------------   
	 
											 UPM Bits Settings
			____________________________________
			| UPM1 | UPM0 | Parity Mode         |
			-------------------------------------
			|  0   |   0  | Disabled            |
			-------------------------------------
			|  0   |   1  | Reserved            |
			-------------------------------------
			|  1   |   0  | Enable, Even Parity |
			-------------------------------------
			|  1   |   1  | Enable, Odd Parity  |
			-------------------------------------
			
			
			   USBS Bit Settings
			________________________
			| USBS  |  Stop Bit(s) |
			------------------------
			|   0   |     1-bit    |
			------------------------
			|   1   |     2-bit    |
			------------------------
	
			
			UPM Bits Settings
			_____________________________________
			| UPM2 | UPM1 | UPM0 | Charcter Size |
			--------------------------------------
			|  0   |   0  |  0   |     5-bit     |
			--------------------------------------
			|  0   |   0  |  1   |     6-bit     |
			--------------------------------------
			|  0   |   1  |  0   |     7-bit     |
			--------------------------------------
			|  0   |   1  |  1   |     8-bit     |
			--------------------------------------
			|  1   |   0  |  0   |    Reserved   |
			--------------------------------------
			|  1   |   0  |  1   |    Reserved   |
			--------------------------------------
			|  1   |   1  |  0   |    Reserved   |
			--------------------------------------
			|  1   |   1  |  1   |      9-bit    |
			--------------------------------------
			
			
			         UCPOL Bit Settings
			______________________________________________________________
			| UCPOL |  Transmitted Data Changed  | Received Data Sampled |
			|       |      (Output of TxD Pin)   | (Input on RxD Pin)    |
			--------------------------------------------------------------
			|  0    |  Rising XCK Edge           | Falling XCK Edg       |
			--------------------------------------------------------------
			|  0    |  Falling XCK Edge          | Rising XCK Edge       |
			--------------------------------------------------------------
				
	//=======================================================================*/
}
//=======================================================================*/
void USART_Advanced_ini(unsigned int speed,unsigned char data_bit_s,unsigned char parity,unsigned char stop_bit_s )
{
	switch(data_bit_s)
	{
		case 5:
		{
			UCSRB |=(0<<UCSZ2);
			UCSRC |=(0<<UCSZ1); 
			UCSRC |=(0<<UCSZ0);
		}break;
		case 6:
		{
			UCSRB |=(0<<UCSZ2);
			UCSRC |=(0<<UCSZ1);
			UCSRC |=(1<<UCSZ0);
		}break;
		case 7:
		{
			UCSRB |=(0<<UCSZ2);
			UCSRC |=(1<<UCSZ1);
			UCSRC |=(0<<UCSZ0);
		}break;
		case 8:
		{
			UCSRB |=(0<<UCSZ2);
			UCSRC |=(1<<UCSZ1);
			UCSRC |=(1<<UCSZ0);
		}break;
		case 9:
		{
			UCSRB |=(1<<UCSZ2);
			UCSRC |=(1<<UCSZ1);
			UCSRC |=(1<<UCSZ0);
		}break;
	}
	
	switch(parity)
	{
		case 0:
			UCSRC |=(1<<UPM1); 
			UCSRC |=(0<<UPM0);
		break;
		case 1:
			UCSRC |=(1<<UPM1);
			UCSRC |=(1<<UPM0);
		break;
	}
	switch(stop_bit_s)
	{
		case 1:
			UCSRC |=(0<<USBS);
		break;
		case 2:
			UCSRC |=(1<<USBS);
		break;
	}
}
//=======================================================================*/
void USART_Transmit(unsigned char data)
{
	while(! (UCSRA & (1<<UDRE)) );
	
	UDR=data;
}
//=======================================================================*/
unsigned char USART_Receive(void)
{
	 while ( !(UCSRA & (1<<RXC)) ); 
	 
	 return UDR; 
}
//=======================================================================*/
void USART_Str (char *string)
{    
	while(*string != '\0')
	{
		USART_Transmit(*string);
		string++;
	}

}
//=======================================================================*/
void USART_float(float f)
{
	 char out_str[30] = {0};
	 
	 dtostrf(f, 4, 6, out_str);
      
	 USART_Str(out_str);
	 
}
//=======================================================================*/
void USART_int(int i)
{
	char out_str[30] = {0};
	
	dtostrf(i, 4, 0, out_str);
	
	USART_Str(out_str);
	
}
//=======================================================================*/
void USART_endl(void)
{
	USART_Str("\r\n");
}
//=======================================================================*/
	void USART_Flush( void )
	{
		unsigned char dummy;
		while ( UCSRA & (1<<RXC) ) dummy = UDR;
	}
//=======================================================================*/