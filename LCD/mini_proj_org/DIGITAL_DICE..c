#include <lpc21xx.h>
#include "LCD_HEADER.H"

#define sw 16
#define EINT0_FN (1<<0)

unsigned int count=0;
void ext_int0_isr(void) __irq;
void lcd_string(unsigned char *);

int main()
{
	unsigned char s[15] = "DIGITAL DICE";
	PINSEL1 |= 0x01;	//pin p0.16 pin select in EXINT0 functinality 2 so 0x01
	
  
	lcd_init();
	lcd_cmd(0x80);
	lcd_string(s);
	
	VICIntSelect = 0;
	VICVectCntl0 = (0x20)|14;
	VICVectAddr0 = (unsigned long)ext_int0_isr;

	EXTMODE  = 0x01;
	EXTPOLAR = 0x00;

	VICIntEnable = (1<<14);

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
	unsigned int a;
	EXTINT=0X01;	//CLEAR FLAG
	lcd_cmd(0xc0);
		if(T0PC==0)
				a=6;
		else
				a=T0PC;
	lcd_integer(a);
	count++;
	lcd_cmd(0xCD);
	lcd_integer(count);
			delay_ms(150);
	lcd_cmd(0x80);
	VICVectAddr=0;
}
