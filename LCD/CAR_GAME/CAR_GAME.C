#include <LPC21XX.h>
#include "lcd_header.h"

void cgram_car(void);
unsigned char cgram_car_sym[]={0x1C,0x14,0x14,0x1F,0x1F,0x15,0x15,0x0A};

int main()
{
	lcd_init();
	cgram_car();
	lcd_cmd(0x80);
	lcd_data(0);
}
void cgram_car(void)
{
	char i=0;
	lcd_cmd(0x40);
	for(i=0;i<8;i++)
	{
		lcd_data(cgram_car_sym[i]);
	}
}



