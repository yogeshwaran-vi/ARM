#include <lpc21xx.h>


void pwm_init(void)
{
	PINSEL0 |=0X00000008;
	
	PWMTCR = (1<<1);
	PWMPR  = 15-1;
	PWMMR0 = 20000;
	PWMMR3 = 1000;
	PWMMCR = (1<<1);	       
    PWMLER = (1<<0)|(1<<3);     
    PWMPCR = 0X800;// Latch MR0 & MR3
    PWMTCR = (1<<0)|(1<<3);	//ENABLE PWM
}
void servo_write(int angle)
{
	int val = 1000+(angle*1000)/180;
	PWMMR3  = val;
	PWMLER  = 1<<3; 
}
void delay_ms(unsigned int ms)
{
	T0PR  = 15000-1;
	T0TCR = 0X01;
	while(T0TC<ms);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
int main()
{
    //IO0DIR &= ~((1<<14) | (1<<15));
	pwm_init();
	servo_write(0);
	delay_ms(500);
	while(1)
	{
		if((IOPIN0 & 1<<14)==0)
		{
			//servo_write(0);
			//delay_ms(500);
			//servo_write(90);
			//delay_ms(500);
			servo_write(180);
			delay_ms(500);
		}
		else if((IOPIN0 & 1<<15)==0)
		{
			servo_write(0);
			delay_ms(500);
		}
	}
}
