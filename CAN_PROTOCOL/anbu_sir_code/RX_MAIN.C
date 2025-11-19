// Node_ B _receiver program

#include<lpc21xx.h>
#include"common_define.h"
#include"CAN_delay.h"
#include"CAN_header.h"
#include"uart_header.h"

//LED define.........
#define LED1 1<<17
#define LED2 1<<18


int main(void)
{
	CAN2_msg k1;
	uart0_init();
	CAN2_init();
	IODIR0 = LED1|LED2;
	IOSET0 = LED1|LED2;
	
	uart0_string_tx("Node_B is ready.....");
	uart0_string_tx("\r\n");
//	uart0_string_tx("\r\n");
	while(1)
	{
		CAN2_msg_rx(&k1);
		
			if(k1.id ==(int)0x1AF)
			{
				uart0_string_tx("Node_B get the Message from Node_A");
				uart0_string_tx("\r\n");
				uart0_string_tx("Msg Id : 0x");
				uart0_hexa(k1.id);
				uart0_string_tx("\r\n");
				uart0_string_tx("LED 1 ON condition");
				uart0_string_tx("\r\n");
				IOSET0 = LED2;
				IOCLR0 = LED1;
				delay_ms(5000);
			}
			else if(k1.id == (int)0x03F)
			{
				uart0_string_tx("Node_B get the Message from Node_A");
				uart0_string_tx("\r\n");
				uart0_string_tx("Msg Id : 0x");
				uart0_hexa(k1.id);
				uart0_string_tx("\r\n");
				uart0_string_tx("LED 2 ON condition");
				uart0_string_tx("\r\n");
				IOSET0 = LED1;
				IOCLR0 = LED2;
				delay_ms(5000);				
			}
			else
			{
				uart0_string_tx("Node_B didn't get any Messages from Node_A");
				uart0_string_tx("\r\n");
				IOSET0 = LED1|LED2;
			}				
	}
}
