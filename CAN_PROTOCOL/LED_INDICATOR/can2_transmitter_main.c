#include <lpc21xx.h>
#include "can2_driver.h"
#include "uart_new.h"
#include "delay.h"
#define sw1 1<<14
#define sw2 1<<15
int main()
{
	CAN2_MSG m1,m2;

	uart0_init(115200);
	can2_init();
	m1.id     = 0x1BF;
	m1.dlc    = 4;
	m1.rtr    = 0;
	m1.byte_A = 0xDDCCBBAA;
	m1.byte_B = 0x00;

	m2.id	  = 0x2AB;
	m2.dlc    = 4;
	m2.rtr    = 0;
	m2.byte_A = 0xAABBCCDD;
	m2.byte_B = 0x00;

	while(1)
	{
		if((IOPIN0 & sw1)==0)
		{
			delay_ms(250);
			uart0_string("Node_A transmit the message to Node_B");
			uart0_string("\r\n");
			uart0_string("Switch 1 is pressed--->TURNED ON LED_1\r\n");
			can2_tx(m1);
			while((IOPIN0 & sw1)==0);
		}
		else if((IOPIN0 & sw2)==0)
		{
			delay_ms(250);
			uart0_string("Node_A transmit the message to Node_B");
			uart0_string("\r\n");
			uart0_string("Switch 2 is pressed--->TURNED ON LED_2\r\n");
			can2_tx(m2);
			while((IOPIN0 & sw2)==0);	
		}
	}
}
