#include <lpc21xx.h>

unsigned char spi_data(unsigned char data);
void spi_init(void)
{
	PINSEL0|=0x1500;
	
	S0SPCCR = 150;
	S0SPCR	= ((1<<5)|(0X18));

	IODIR0  |= 1<<7;
}
float READ_MCP3204(unsigned char ch_no)
{
	float vout=0;
	unsigned char adcval;
	unsigned char hbyte,lbyte;

	IOCLR0=1<<7;

	spi_data(0x06);
	hbyte=spi_data(ch_no<<6);
	lbyte=spi_data(0x00);

	IOSET0=1<<7;

	adcval=((hbyte&(0x0f))<<8)|lbyte;
	vout=((adcval*3.3)/4096.0)*100;
	return vout;
}
unsigned char spi_data(unsigned char data)
{
	S0SPDR = data;
	while(((S0SPSR>>7)&1)==0);
	return S0SPDR;
}
