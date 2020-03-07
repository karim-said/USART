
#include "main.h"
 
ISR(USART_RXC_vect)
{      char r;
	   USART_Str("Hoo i'm INERUP and i Recive data -> ");			 
	   r= USART_Receive();
	   USART_Transmit(r);
	   USART_endl();
	   USART_Flush();
	   //_delay_ms(1000);                         //Recive
}
ISR(USART_TXC_vect)
{  
	USART_Str("Hoo i'm transmit data");			//Transmit
	USART_endl();
	USART_endl();
	_delay_ms(100);
}
ISR(USART_UDRE_vect)
{
		USART_Str("UDR Empty");		//UDR empty
		USART_endl();
		_delay_ms(500);
} 
//unsigned char msg1[] = "S.T.A.R.";


int main(void)
{
	
	 float Float=3.14345667676;
	 int Int=32234;
	 
	 
     USART_ini(8);//115200
	  sei();
	   
	USART_Transmit('K');
	USART_endl();
	USART_endl();

	USART_Str("S.T.A.R.");
	USART_endl();
	USART_endl();
	
	USART_float(Float);
    USART_endl();
	USART_endl();
	
	USART_int(Int);
	USART_endl();
	USART_endl();
	  
	
	
    while (1) 
    {
		// another code
		
	}
}

