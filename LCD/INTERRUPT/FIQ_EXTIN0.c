#include <lpc21xx.h>

void EXTINT_ISR(void) __irq
{
	EXTINT=0x01;

	IOSET0=0XFF;
	IOCLR0=0XFF;

	VICVectAddr=0;
}
int main()
{
	PINSEL1=0X01;
	IODIR0=0XFF;

	VICIntSelect=1<<14;
	VICIntEnable=1<<14;

	while(1)
	{
		int count=0;
		count++;
	}
}
