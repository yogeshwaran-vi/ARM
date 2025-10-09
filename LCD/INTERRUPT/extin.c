#include<lpc21xx.h>
void ext_int0_isr(void) __irq
{
	EXTINT=0x01;

	IOCLR0=1<<18;  
	IOSET0=1<<18;

	VICVectAddr=0;
}
int main()
{
	unsigned int count=0;
	PINSEL1= 0x01;// pin connect as p0.16 pin
	IODIR0=1<<18;
	
	VICIntSelect=1;
	VICVectCntl0=0x20|14;
	VICVectAddr0=(unsigned long)ext_int0_isr;

	EXTMODE=0x00;
	EXTPOLAR=0x00;

	VICIntEnable=1<<14;
/**********main line***************/
	while(1)
	{
		count++;
	}
}

