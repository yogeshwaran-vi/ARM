#include <lpc21xx.h>
#include <stdio.h>
#include "uart0_header.h"

#define DHT (1<<15)
void delay_ms(unsigned int ms)
{
	T0PR  = 60000-1;
	T0TCR = 0x01;
	while(T0TC<ms);
	T0TCR =	0x03;
	T0TCR = 0x00;
}
void delay_us(unsigned int us)
{
	T0PR  = 60-1;
	T0TCR = 0x01;
	while(T0TC<us);
	T0TCR =	0x03;
	T0TCR = 0x00;
}
void DHT_START(void)
{
	IODIR0 |= DHT;

	IOCLR0 = DHT;
	delay_ms(18);
	
	IOSET0 = DHT;
	delay_us(30);
	
	IODIR0 &= ~DHT; 
}
unsigned char DHT_ReadByte(void)
{
	int i,data = 0;

    for(i=0;i<8;i++)
    {
        while(!(IOPIN0 & DHT));   // Wait for HIGH
        delay_us(30);

        if(IOPIN0 & DHT)
            data = (data<<1) | 1;
        else
            data = (data<<1);

        while(IOPIN0 & DHT);      // Wait for LOW
    }
    return data;
}
int main()
{
	unsigned char RH_int,RH_dec,T_int,T_dec,SUM;
	char buffer[40];

	uart0_init();
	uart_str("DHT11 ready");
	uart_str("\r\n");
	while(1)
	{
		DHT_START();

		while(IOPIN0 & DHT);
        while(!(IOPIN0 & DHT));
        while(IOPIN0 & DHT);

        RH_int   = DHT_ReadByte();
        RH_dec   = DHT_ReadByte();
        T_int    = DHT_ReadByte();
        T_dec    = DHT_ReadByte();
        SUM      = DHT_ReadByte();

		//if(SUM==(RH_int + RH_dec + T_int + T_dec))
        //{
            sprintf(buffer,"Humidity: %d Temp: %d  \r\n",RH_int,T_int);
            uart_str((unsigned char*)buffer);
        //}
        //else
        //{
           uart_str("sum Error");
        //}
		delay_ms(2000);
	} 
}

