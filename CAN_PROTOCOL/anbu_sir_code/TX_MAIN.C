// node_ A _transmit msg to node_B

#include<lpc21xx.h>
#include"common_define.h"
#include"CAN_delay.h"
#include"CAN_header.h"
#include"uart_header.h"

//LED define..........
#define sw1 1<<15
#define sw2 1<<16

int main(void)
{
	CAN2_msg m1,m2;
	uart0_init();
	CAN2_init();
	m1.id = 0x1AF;
	m1.dlc = 4;
	m1.rtr = 0;	//
	m1.A_bytes = 0xAABBCCDD;
	m1.B_bytes = 0x00;
	m2.id = 0x03F;
	m2.dlc = 4;
	m2.rtr = 0;
	m2.A_bytes = 0x11223344;
	m2.B_bytes = 0x00;

	uart0_string_tx("Node A is ready...");
	uart0_string_tx("\r\n");
	
	while(1)
	{
		if((IOPIN0 & sw1)==0)
		{
				delay_ms(250);
				uart0_string_tx("Node_A transmit the message to Node_B");
				uart0_string_tx("\r\n");
				uart0_string_tx("Msg id : ");
				uart0_hexa(m1.id);
				uart0_string_tx("\r\n");
				uart0_string_tx("Switch 1 is pressed ===> Turn ON LED_1");
				uart0_string_tx("\r\n");
				CAN2_msg_tx(m1);
				while((IOPIN0 & sw1)==0);
		}
		else if((IOPIN0 & sw2)==0)
		{
				delay_ms(250);			
				uart0_string_tx("Node_A transmit the message to Node_B");
				uart0_string_tx("\r\n");
				uart0_string_tx("Msg id : ");
				uart0_hexa(m2.id);
				uart0_string_tx("\r\n");
				uart0_string_tx("Switch 2 is pressed ===> Turn ON LED_2");
				uart0_string_tx("\r\n");
				CAN2_msg_tx(m2);
				while((IOPIN0 & sw2)==0);
		}
	}
}
