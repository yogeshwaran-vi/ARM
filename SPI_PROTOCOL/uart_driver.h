#include <lpc21xx.h>

UART0_CONFIG(void)
{
	PINSEL0 |= 0x05;
	U0LCR	 = 0X83;
	U0DLL	 = 97;
	U0DLM	 = 0;
	U0LCR	 = 0X03;
}
UART0_TX(unsigned char data)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=data;
}
UART0_STR(unsigned char *S)
{
	while(*S)
		UART0_TX(*S++);
}
GSM_SMS(unsigned char *msg)
{
	UART0_STR("AT\r\n");
	delay_ms(500);
	UART0_STR("AT+CMGF=1\r\n");
	delay_ms(500);
	UART0_STR("AT+CMGS=\"+916380405110\"\r\n");
	delay_ms(1000);
	UART0_STR(msg);
	delay_ms(1000);
	UART0_STR("\r\n");
	delay_ms(1000);
	UART0_TX(0X1A);
	delay_ms(5000);
}
