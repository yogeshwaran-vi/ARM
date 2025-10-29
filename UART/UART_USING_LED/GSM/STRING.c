#include <lpc21xx.h>
#include "4-BIT_LCD_INTERFACE.h"


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
void gsm_sms(unsigned char*msg)
{
    UART0_str("AT");
	delay_ms(500);
	UART0_str("AT+CMGF=1\r\n");
	delay_ms(500);
    UART0_str("AT+CMGS=\"+917708779222\"\r\n");
    //UART0_str(phone_number);
    delay_ms(1000);
    UART0_str(msg);
	delay_ms(1000);
	UART0_str("\r\n");
    UART0_TX(0x1A);   // Ctrl+Z
    delay_ms(2000);
}
int main()
{
	unsigned char rxbyte[20];
	unsigned char i=0;
	UART0_CONFIG();
	LCD_INIT();
	LCD_CMD(0X01);
	LCD_CMD(0X80);
	LCD_DATA('A');
	LCD_STR("hiii...");

	UART0_str("AT\r\n");
	delay_ms(1000);
	//while(1)
	//{
	while(1)
	{
		rxbyte[i++]=UART0_RX();
		if(rxbyte[i-1]=='\r')
		break;
	}					  
	  rxbyte[i-1]='\0';

		
		i=0;
		UART0_str((unsigned char*)rxbyte);
		LCD_STR("hiii...");
		gsm_sms((unsigned char*)rxbyte);
	//}

}
