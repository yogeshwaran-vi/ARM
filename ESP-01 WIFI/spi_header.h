
#define mode_3   0x18  //like 3 bit CPOL 1 and 4 bit CPHA 1
#define cs       7
#define mstr_bit 5
#define spif_bit 7
#define spi_pclk 15000000
#define spi_rate 100000
unsigned char spi_data(unsigned char);
void spi_init(void)
{
	PINSEL0 |= 0X1500;
	S0SPCCR  = 150;
	S0SPCR   = (1<<mstr_bit|mode_3);
	IODIR0  |= 1<<7;
}
float read_mcp3204(unsigned char channel_no)
{
	unsigned char hbyte,lbyte;
	unsigned int adc_val=0;

	IOCLR0 = 1<<cs;

	spi_data(0x06);
	hbyte=spi_data(channel_no<<6);
	lbyte=spi_data(0x00);

	IOSET0 = 1<<cs;

	adc_val=((hbyte&0x0f)<<8)|lbyte;
	return ((adc_val*3.3)/4095)*100;  //vref 3.3 and 12 bit of 2 power 12 is 4096
}
unsigned char spi_data(unsigned char data)
{
	S0SPDR = data;
	while(((S0SPSR>>spif_bit)&1)==0);
	return S0SPDR;	
}




