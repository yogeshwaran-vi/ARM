#include<lpc21xx.h>

#define LED1 1<<17
#define LED2 1<<18
#define SW   14

int flag=0;	   						//INTERRUPT LED BLINKING PURPOSE
void TIMER0_ISR(void) __irq;

int main()
{
	IODIR0 = LED1|LED2;					//P0.17 AS A OUTPUT PIN
	//IODIR1 = LED2;	    			//P0.18 AS A OUTPUT PIN
	T0MCR  = 0x03; 
	T0MR0  = 7500000-1;
	VICIntSelect = 0;     			//ALL ARE IRO MODE
	VICVectCntl0 = (0x20)|4;
	VICVectAddr0 = (int)TIMER0_ISR;
	VICIntEnable = 1<<4;
	T0TCR = 0x01; 					//ENBLE
	   			//TIMER INT NUMBER 4

//*********MAIN LINE CODE************//
	while(1)
	{
		if(((IOPIN0 >> SW)&1)==0)
			IOCLR0 = LED1;
		else
			IOSET0 = LED1;
	}

}
void TIMER0_ISR(void) __irq
{
	T0IR = 0X01; 						//TO CLEAR A MR0 FLAG
	if(flag==0)
	{
		IOCLR0 = LED2;
		flag=1; 
	}
	else
	{
		IOSET0 = LED2;
		flag=0;
	}
	VICVectAddr = 0;	
}
