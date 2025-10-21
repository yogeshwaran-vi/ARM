#include <lpc21xx.h>

void delay_ms(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<ms);
	T0TCR=0X03;
	T0TCR=0X00;
}
void UART0_STR(unsigned char *);
void UART0_CONFIG(void)
{
	PINSEL0=0X05;
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}
char UART0_RX(void)
{
	while((U0LSR & 0x1)==0);
	return U0RBR;
}
void UART0_TX(char TXbyte)
{
	while(((U0LSR>>5)&1)==0);
	if(TXbyte=='1')
	{
		U0THR=TXbyte;
		IOSET0=1<<17;
		delay_ms(500);
		IOCLR0=1<<17;
		delay_ms(500);
	}
	else if(TXbyte=='2')
	{
		U0THR=TXbyte;
		IOSET0=1<<18;
		delay_ms(500);
		IOCLR0=1<<18;
		delay_ms(500);
	}
	else
	{
		UART0_STR("ENTER THE VALID INPUT EITHER 1 OR 5");
	}
}
void UART0_STR(unsigned char *s)
{
	while(*s)
	{
		while(((U0LSR>>5)&1)==0);
		U0THR=(*s++);
	}
}

int main()
{
	char RXbyte;
	IODIR0=1<<17|1<<18;
	UART0_CONFIG();
	while(1)
	{
		RXbyte=UART0_RX();
		UART0_TX(RXbyte);
	}
}
