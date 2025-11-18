#include <lpc21xx.h>
typedef struct can
{
	unsigned int id;
	unsigned int rtr;
	unsigned int dlc;
	unsigned int byteA;
	unsigned int byteB;
}CAN2_MSG;

#include "can_driver.h"
#include "uart_driver.h"
int main()
{
	CAN2_MSG m1;
	//IODIR0 |=1<<19;
	can2_init();
	uart1_init();
    
	while(1)
	{
		can2_rx(&m1);
		
		if(m1.rtr==0)
		{
			uart1_hex(m1.id);
			uart1_tx(' ');
			uart1_hex(m1.dlc);
			uart1_tx(' ');
			uart1_hex(m1.byteA);
			uart1_tx(' ');
			uart1_hex(m1.byteB);
			uart1_tx(' ');
			uart1_string("\r\n");		
		}
		else
		{
			uart1_hex(m1.id);
			uart1_tx(' ');
			uart1_hex(m1.dlc);
			uart1_tx(' ');
			uart1_string("\r\n");
		}	
	}
		
}
