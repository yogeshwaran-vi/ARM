#define VREF  			3.3
#define BIT_RESOLUTION 4096


#define CS			7
#define SPIF_BIT	7
#define PCLK 		15000000
#define SPI_RATE	100000

#define SET(num,pos)	(num|=1<<pos)
#define CLR(num,pos)	(num&=1<<pos)
#define READ_BIT		(((num>>pos)&1)==0)

unsigned char SPI_DATA(unsigned char data);
void SPI_INIT(void)
{
	PINSEL0 |= 0x1500;
	
	S0SPCCR  = 150;
	S0SPCR   = (1<<5|0X18);

	IODIR0  = 1<<7;
}
float READ_MCP3204(int channelno)
{
	 unsigned char hbyte,lbyte;
	 int adc_val=0;

	 CLR(IOPIN0,CS);//ACTIVATED CHIP
	 
	 SPI_DATA(0x06);
	 hbyte = SPI_DATA(channelno<<6);
	 lbyte = SPI_DATA(0x00);
	 
	 SET(IOSET0,CS); //DE-ACTIVATED CHIP

	 adc_val=(((hbyte&0x0f)<<8)|lbyte);
	 return (adc_val*VREF)/BIT_RESOLUTION;

}
unsigned char SPI_DATA(unsigned char data)
{
	//unsigned char status;
	//status = S0SPSR;
	S0SPDR = data;
	while(((S0SPSR>>SPIF_BIT)&1)==0);
	return S0SPDR;
}

