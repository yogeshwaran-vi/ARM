#include<lpc21xx.h>
#include "LCD_HEADER.H"

#define sw 14
#define EINT0_FN (1<<0)

unsigned  int count=0,v,a;

void ext_int0_isr(void) __irq;
void lcd_string(unsigned char *);

int main()
{
	//unsigned int count=0;
	PINSEL1 |= 0x01;	//pin p0.16 pin select in EXINT0 functinality 2 so 0x01
	
    lcd_init();
//	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_string("DIGITAL DICE");
	VICIntSelect=0;
	VICVectCntl0=(0x20)|14;
	VICVectAddr0=(unsigned long)ext_int0_isr;

	EXTMODE=0x01;
	EXTPOLAR=0x00;

	VICIntEnable = 1<<14;

	while(1)
	{
		T0PR=6-1;
		T0TCR=0X01;
	}	
}

void lcd_string(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
	}
}
        //*************EXTINT0 FUNCTION **************//
void ext_int0_isr(void) __irq
{
	EXTINT=0X01;		//CLEAR FLAG
	lcd_cmd(0xC0);
	a=T0PC;
		if(a==0)
			v=6;
		else
		 	v=a;

	lcd_integer(v);
	count++;
	lcd_cmd(0xD1);
	lcd_integer(count);
		delay_ms(250);
	lcd_cmd(0x80);
	VICVectAddr=0;
}
