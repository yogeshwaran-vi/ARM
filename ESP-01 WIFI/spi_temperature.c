#include<lpc21xx.h>
#include<stdio.h>
#include"spi_header.h"
#include"uart_header.h"
#include"lcd_header.h"
int main()
{
	float Temperature;
	char buf[100];
	IODIR1|=lcd_pin|RS|E;
	spi_init();
	lcd_init();
	uart_init();
	esp_init();

	IOPIN0 |=1<<7;

	while(1)
	{
		
		Temperature = read_mcp3204(1);
		lcd_cmd(0x80);
		lcd_float(Temperature);
		sprintf(buf,"%.2f",Temperature);
		esp_send((unsigned char*)buf);
		delay_ms(15000);
	}
}
