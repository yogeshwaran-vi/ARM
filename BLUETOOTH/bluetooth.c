#include <lpc21xx.h>
#include "uart_header.h"
#include "4bit_lcd.h"
#define led 1<<14
int flag=1;
int main()
{
	unsigned char receive;
	IODIR0|=led;
	IOSET0 = led;
   	uart1_init();
   	lcd_init();
	uart_str("WELCOME\r\n");

   while(1)
   {
   		lcd_cmd(0x01);
		lcd_cmd(0x80);
   	    receive=uart1_rx();
		if(receive == '\r' || receive == '\n' || receive == 0)
		{
    		continue;
		}
		if(receive == '1')
		{
			 IOCLR0 = led;
			 uart_str("LED ON\r\n");
			 lcd_str("LED ON");
			 flag=0;
		} 
		else if(receive == '0')
		{
			 IOSET0 = led;
			 uart_str("LED OFF\r\n");
			 lcd_str("LED OFF");
			 flag=0;
		} 	
		else
		{
			uart_str("select the correct option\r\n");
			lcd_str("select the correct option");
		}
   }
}
