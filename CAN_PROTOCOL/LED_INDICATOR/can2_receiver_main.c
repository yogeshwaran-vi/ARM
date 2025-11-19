#include<lpc21xx.h>
#include "can2_driver.h"
#include "uart0_driver.h"
#include "delay.h"

#define LED1 1<<16
#define LED2 1<<17

int main()
{
	CAN2_MSG k1,k2;
	int i=0,j=0;
	uart0_init(115200);
	can2_init();
	IODIR0 |= LED1|LED2;
	IOSET0 = LED1|LED2;

	uart0_string("Node_B is ready.....\r\n");

	while(1)
	{
		can2_rx(&k1);
		can2_rx(&k2);

		if(k1.id==0x1BF)
		{	
			uart0_string("Node_B get the message from Node_A..");
			uart0_string("\r\n");
			uart0_string("MSG Id1 : 0x");
			uart0_hex(k1.id);
			uart0_string("\r\n");
			uart0_string("LED_1 TURNED ON");
			uart0_string("\r\n");
			if(i<10)
			{
				IOCLR0 = LED1;
				delay_ms(500);
				IOSET0 = LED1;
				delay_ms(500);
				i++;
			}
			else
				IOSET0 = LED1;
		}
		else if(k2.id==0x2AB)
		{
			uart0_string("Node_B get the message from Node_A..");
			uart0_string("\r\n");
			uart0_string("MSG Id2 : 0x");
			uart0_hex(k2.id);
			uart0_string("\r\n");
			uart0_string("LED_2 TURNED ON");
			uart0_string("\r\n");
			if(j<10)
			{
				IOCLR0 = LED2;
				delay_ms(500);
				IOSET0 = LED2;
				delay_ms(500);
				j++;
			}
			else
				IOSET0 = LED2;	
		}
		else
		{
			uart0_string("Node_B didn't get any messages from Node_A..");
			uart0_string("\r\n");
			IOSET0 = LED1;
		}
	}
}
