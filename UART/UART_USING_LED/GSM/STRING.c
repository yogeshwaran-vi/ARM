#include <lpc21xx.h>

void delay_ms(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<1);
	T0TCR=0X03;
	T0TCR=0X00;
}
void UART0_CONFIG(void)
{
	PINSEL0 = 0X05;
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
void gsm_sms(unsigned char* phone_number,unsigned char*msg)
{
	UART0_str("AT+CMGF=1\r");
	delay_ms(500);
    UART0_str("AT+CMGS=\"");
    UART0_str(phone_number);
    UART0_str("\"\r");
    delay_ms(500);
    UART0_str(msg);
    UART0_TX(0x1A);   // Ctrl+Z
    delay_ms(5000);
}
int main()
{
	unsigned char rxbyte[20];
	unsigned char i=0;
	UART0_CONFIG();
	UART0_str("AT\r\n");
	delay_ms(100);
	while(1)
	{
		rxbyte[i++]=UART0_RX();
		if(rxbyte[i-1]=='\r')
		break;
	}
		rxbyte[i-1]='\0';
		UART0_str((unsigned char*)rxbyte);
		gsm_sms("+919092070939",(unsigned char*)rxbyte);
	
}
