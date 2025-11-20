#include <lpc21xx.h>
#include "spi_driver.h"
#include "LCD_HEADER.h"
int main()
{
	float temp;
	spi_init();
	LCD_INIT();

	IOPIN0 |=1<<7;
	
	while(1)
	{
		temp=READ_MCP3204(0);
		LCD_CMD(0xc0);
		LCD_FLOAT(temp);
		delay_ms(250);
	} 
}
