#include <lpc21xx.h>


/**I2C_PIN_FUNCTION**/
#define SCL  		0x00000010 //p0.2 as a output pin for scl
#define SDA  		0x00000040 //p0.3 as a output pin for scl

/**I2C_BIT REGISTERS**/
#define AA_BIT   	2
#define SI_BIT   	3
#define STO_BIT  	4
#define STA_BIT  	5
#define I2EN_BIT 	6

/**SPEED CONFIGURATION**/
#define CCLK 		60000000 
#define PCLK 		CCLK/4
#define I2C_SPEED	100000
#define LOADVAL		((PCLK/I2C_SPEED)/2)

/**I2C_INITAIALIZE FUNCTION**/
void I2C_INIT(void)
{
	PINSEL0 = SCL|SDA;
	I2SCLL	= LOADVAL;
	I2SCLH	= LOADVAL;
	I2CONSET= 1<<I2EN_BIT;
}

/**START CONDITION **/
void I2C_START(void)
{
	I2CONSET = 1<<STA_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0); //WAIT FOR SI FLAG TO SET
	I2CONCLR = 1<<STA_BIT;
}

/**RE-START FUNCTION**/
void I2C_RESTART(void)
{
	I2CONSET = 1<<STA_BIT;
	I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	I2CONCLR = 1<<STA_BIT;
}

/**WRITE FUNCTION**/
void I2C_WRITE(unsigned char DATA)
{
	I2DAT=DATA;
	I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
}

/**NO_ACKNOWLEDGE**/
char I2C_NACK(void)
{
	//I2CONSET = 0X00;
	I2CONCLR = 1<<SI_BIT;
	while(((I2CONSET>>SI_BIT)&1)==0);
	return I2DAT;
}
/**STOP CONDITION **/
void I2C_STOP(void)
{
	I2CONSET = 1<<STO_BIT;
	I2CONCLR = 1<<SI_BIT;
}

/**DELAY FUNCTION**/
void delay_ms(unsigned ms)
{
	T0PR  = 15000-1;
	T0TCR = 0X01;
	while(T0TC<ms);
	T0TCR = 0X03;
	T0TCR = 0X00; 
}
