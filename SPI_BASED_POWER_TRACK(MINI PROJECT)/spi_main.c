//SPI BASED POWER TRACK - SMART ENERGY MONITORING & GSM ALERT SYSTEM USING ARM7

#include <lpc21xx.h>
#include "spi_driver.h"
#include "LCD_HEADER_NEW.h"
#include "uart_driver.h"
unsigned char j[4]={0x86,0xC6,0x9A,0xDA};  //using lcd address
int flag=0;
int main()
{
	float f[4];unsigned int i;
	IODIR0|=1<<17;	  //LED  p0.17
	IOSET0=1<<17;
	SPI_INIT();
	UART0_CONFIG();
	LCD_INIT();
	LCD_STRING("V0-->");
	delay_ms(2);
	LCD_CMD(0XC0);
	LCD_STRING("V1-->");
	delay_ms(2);
	LCD_CMD(0X94);
	LCD_STRING("V2-->");
	delay_ms(2);
	LCD_CMD(0XD4);
	LCD_STRING("V3-->");
	delay_ms(2);

	IOPIN0 |= 1<<7;

	while(1)
	{
		for(i=0;i<4;i++)
		{
			f[i]=READ_MCP3204(i);
			LCD_CMD(j[i]);
			LCD_FLOAT(f[i]);
			LCD_DATA('V');
		}
		if((f[0]<=2.5)&&(flag!=1))
		{
		  GSM_SMS("V0-->LOW VOLTAGE...ALART..!");
		  flag=1;
		}  
		else if((f[1]<=2.5)&&(flag!=2))
		{
			GSM_SMS("V1-->LOW VOLTAGE...ALART..!");
			flag=2;
		}
		else if(f[2]>=2.0)
		{
			IOCLR0=1<<17;         //using This LED LDR sensor purpose
			delay_ms(1000);
			IOSET0=1<<17;
			delay_ms(1000);
		}
		else if((f[3]<=2.0)&&(flag!=3))
		{
			GSM_SMS("V3-->LOW VOLTAGE...ALART..!");
			flag=3;
		}	 
	}
}
