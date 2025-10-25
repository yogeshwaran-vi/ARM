#include <lpc21xx.h>

#define SCL  		0x00000010 //p0.2 as a output pin for scl
#define SDA  		0x00000040 //p0.3 as a output pin for scl
#define AA_BIT   	2
#define SI_BIT   	3
#define STO_BIT  	4
#define STA_BIT  	5
#define I2EN_BIT 	6

/**SPEED CONFIGURATION**/
#define CCLK 		6000000 
#define PCLK 		CCLK/4
#define I2C_SPEED	100000
#define LOADVAL		((PCLK/I2C_SPEED)/2)

void I2C_INIT(void)
{
	PINSEL0 = SCL|SDA;
	I2SCLL	= LOADVAL;
	I2SCLH	= LOADVAL;
	I2CONSET= 1<<I2EN_BIT;
}
int main()
{
	I2C_CONFIG();

}