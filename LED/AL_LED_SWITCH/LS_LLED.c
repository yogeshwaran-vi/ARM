#include<lpc21xx.h>
#define	AL_LED 1<<17
#define AL_SW 1<<14
int main()
{
	 IODIR0=AL_LED;
	 while(1)
	 {
			if((IOPIN0&AL_SW)==0)
				IOCLR0=AL_LED;
			else
				IOSET0=AL_LED;
	 }

}
