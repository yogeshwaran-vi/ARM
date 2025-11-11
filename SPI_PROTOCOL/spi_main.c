#include <lpc21xx.h>
#include "spi_driver.h"
#include "LCD_HEADER_NEW.h"
#include "uart_driver.h"
unsigned char j[4]={0x86,0xC6,0x9A,0xDA};
int main()
{
	float f[4];unsigned int i;
	IODIR0|=1<<17;
	//IOSET0=1<<17;
	SPI_INIT();
	UART0_CONFIG();
	LCD_INIT();
	LCD_STRING("CH0-->");
	delay_ms(2);
	LCD_CMD(0XC0);
	LCD_STRING("CH1-->");
	delay_ms(2);
	LCD_CMD(0X94);
	LCD_STRING("CH2-->");
	delay_ms(2);
	LCD_CMD(0XD4);
	LCD_STRING("CH3-->");
	delay_ms(2);

	IOPIN0 |= 1<<7;

	while(1)
	{
		for(i=0;i<4;i++)
		{
			f[i]=READ_MCP3204(i);
			LCD_CMD(j[i]);
			LCD_FLOAT(f[i]);
		}
		if(f[0]<=2.5)
		{
		  GSM_SMS("CH0-->LOW VOLT...ALART..!");
		}  
		else if(f[1]<=2.5)
		{
			GSM_SMS("CH1-->LOW VOLT...ALART..!");
		}
		else if(f[2]>=2.0)
		{
			IOCLR0=1<<17;
			delay_ms(1000);
			IOSET0=1<<17;
			delay_ms(1000);
		}
		else if(f[3]<=2.5)
		{
			GSM_SMS("CH3-->LOW VOLT...ALART..!");
		}	 
	}
}
