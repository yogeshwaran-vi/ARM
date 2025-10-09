#include<lpc21xx.h>
void fiq_extint0(void) __irq
{
	EXTINT = 0X01;

	IOSET0 = 0X01;
	IOCLR0 = 0X01; 	
}
int main()
{
	unsigned int count=0;
	PINSEL1 = 0x01;	//po.16
	IODIR0  = 0X01;
	
	VICIntSelect = 1<<14;
	
	EXTMODE  = 0X01;
	EXTPOLAR = 0X00;

	VICIntEnable = 1<<14;

	while(1)
	{
		count++;
	}
}

