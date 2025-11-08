#include <lpc21xx.h>
#include "spi_driver.h"
#include "LCD_HEADER_NEW.h"

int main()
{
	float f;

	SPI_INIT();
	LCD_INIT();
	LCD_STRING("MCP3204:");

	IOPIN0 |= 1<<7;

	while(1)
	{
		f=READ_MCP3204(0);
		LCD_CMD(0xC0);
		LCD_FLOAT(f);
	}
}
