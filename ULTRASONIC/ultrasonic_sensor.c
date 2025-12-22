#include <lpc21xx.h>
#include <stdio.h>
#include "uart_config.h"
#include "4-BIT_LCD_INTERFACE.h"

#define TRIG 1<<5
#define ECHO 1<<6
unsigned int get_distance(void);
void delay_us(unsigned int us)
{
    T0PR  = 15;
    T0TCR = 1;
    T0TC  = 0;
    while(T0TC < us);
    T0TCR = 0;
}
unsigned int distance;
int main()
{
	char buffer[50];
	IODIR0 = TRIG|ECHO;
	UART0_CONFIG();
	LCD_INIT();
	LCD_CMD(0X01);
	LCD_CMD(0X80);
	delay_ms(1000);
	while(1)
	{
		distance = get_distance();

        sprintf(buffer, "Distance: %d cm\r\n", distance);
        UART0_str((unsigned char*)buffer);

        if(distance < 30)
            UART0_str("Obstacle Detected!\r\n");
        else
            UART0_str("No Obstacle\r\n");

        delay_us(50000);
	}					  
}
unsigned int get_distance(void)
{
    unsigned int time;

    IOSET0 = TRIG;
    delay_us(10);
    IOCLR0 = TRIG;

    while(!(IOPIN0 & ECHO));
    T0TC = 0;
    T0TCR = 1;

    while(IOPIN0 & ECHO);
    T0TCR = 0;

    time = T0TC;
    return time / 58;
}
