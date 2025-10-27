#include <LPC21XX.H>
#include "I2C_DRIVER.h"

#define GLED 1<<16
#define RLED 1<<17

void EEPROM_WRITE(unsigned char SLAVE_ADDR,unsigned char WBUFF_ADDR,unsigned char dat)
{
	I2C_START();
	I2C_WRITE(SLAVE_ADDR<<1);
	I2C_WRITE(WBUFF_ADDR);
	I2C_WRITE(dat);
	I2C_STOP();
	delay_ms(10);
}
char EEPROM_READ(unsigned char SLAVE_ADDR,unsigned char RBUFF_ADDR)
{
	unsigned char dat;
	I2C_START();
	I2C_WRITE(SLAVE_ADDR<<1);
	I2C_WRITE(RBUFF_ADDR);
	I2C_RESTART();
	I2C_WRITE(SLAVE_ADDR<<1|1);
	dat=I2C_NACK();
	I2C_STOP();
	return dat;
}
int main()
{
	unsigned char ch;
	I2C_INIT();
	IODIR1|=GLED|RLED;
		EEPROM_WRITE(0X50,0X00,'A');
		ch=EEPROM_READ(0X50,0X00);
	
	delay_ms(100);
	
	if(ch=='A')
	{
		IOCLR1 = GLED;
	}
	else
	{
		IOCLR1 = RLED;
	}
	
	while(1);
}
