/*write an ecp for transmit 'A' using UART0*/
#include <lpc21xx.h>
void UART0_config(void);
void UART0_TX(unsigned char);
int main()
{
	int i=0;
	char ch='a';
	UART0_config();
	while(i<26)
	{
	UART0_TX(ch++);
		i++;
	}
	
}
void UART0_config(void)
{
	PINSEL0=0X05;
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}
void UART0_TX(unsigned char RXbyte)
{
	while(((U0LSR>>5)&1)==0);
	if('A'<=RXbyte & 'Z'>=RXbyte)
	U0THR=RXbyte+32;
	else if('a'<=RXbyte & 'z'>=RXbyte)
	U0THR=RXbyte-32;
		//U0THR=TXbyte;	
}
