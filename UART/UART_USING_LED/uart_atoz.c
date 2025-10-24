#include <lpc21xx.h>
#include "lcd_header.h"
#define LED0 1<<19
void string(unsigned char *);
void UART0_CONFIG(void)
{
	PINSEL0|=0X5;
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}
char UART0_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}
void UART0_TX(unsigned char data)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=data;
}

int main()
{
	int rxbyte;
	lcd_init();
	IODIR0=LED0;
	IOSET0=LED0;
	UART0_CONFIG();
	string("TURNED ON '1' AND OFF '0': ");
	while(1)
	{
		rxbyte=UART0_RX();
		UART0_TX(rxbyte);

		if(rxbyte=='0')
		{
			string("TURNED OFF");
			lcd_string("TURNED OFF");
			IOSET0=LED0;
		}
		else if(rxbyte=='1')
		{
			string("TURNED ON");
			lcd_string("TURNED ON");
			IOCLR0=LED0;
		}
	}
}
void string(unsigned char *s)
{
	while(*s)
	{
		UART0_TX(*s++);
	}
}

