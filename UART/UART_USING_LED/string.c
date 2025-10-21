#include<lpc21xx.h>
void UART0_str(unsigned char *);
void UART0_CONFIG(void)
{
	PINSEL0=0x05;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}
/*char UART0_RX(void)
{
	while((U0LSR & 1)==0);
	return U0RBR;
}*/
void UART0_TX(char RXbyte)
{
	while(((U0LSR>>5)&1)==0);
	
	if('A'<=RXbyte & 'Z'>=RXbyte)
	U0THR=RXbyte+32;
	else if('a'<=RXbyte & 'z'>=RXbyte)
	U0THR=RXbyte-32;
}
void UART0_str(unsigned char *s)
{
	while(*s)
	{
		UART0_TX(*s++);
	}
}
int main()
{
	UART0_CONFIG();
	UART0_str("yogesh");
}