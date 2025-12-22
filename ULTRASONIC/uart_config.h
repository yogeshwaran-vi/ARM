#include <lpc21xx.h>

void UART0_CONFIG(void)
{
	PINSEL0|= 0X05;
	U0LCR	= 0X83;
	U0DLL	= 97;
	U0DLM	= 0;
	U0LCR	= 0X03;	
}
unsigned char UART0_RX(void)
{
	while((U0LSR&0x1)==0);
	return U0RBR;
}
void UART0_TX(unsigned char data)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=data;
}
void UART0_str(unsigned char *s)
{
	while(*s)
		UART0_TX(*s++);
}

