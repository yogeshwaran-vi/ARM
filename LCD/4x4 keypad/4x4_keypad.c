 #include <lpc21xx.h>
 #include "lcd_header.h"
 #include "lcd_integer.h"
   //*********TO DECLARE COLUMN**********//
 #define c0 (IOPIN0&(1<<16))
 #define c1 (IOPIN0&(1<<17))
 #define c2 (IOPIN0&(1<<18))
 #define c3 (IOPIN0&(1<<19))
   //*********TO DECLAR ROW**********//
 #define ro 1<<20;
 #define r1 1<<21;
 #define r2 1<<22;
 #define r3 1<<23;
 
 unsigned int num_lut[4][4]={{1,2,3,+},{4,5,6,-},{7,8,9,/},{*,0,#,%}};
 unsigned int key_scan(void)
 {
 	unsigned int row_val,col_val;
 	PINSEL1=0x00000000;
	IODIR0=r0|r1|r2|r3;
	
	while(1)
	{
	IOCLR0=r0|r1|r2|r3;		 //initial row also 0
	IOSET0=c0|c1|c2|c3;		 //initial col also 1

	while((c0&c1&c2&c3)==0);  //wating for key press
	
	IOCLR0=r0;
	IOSET0=r1|r2|r3;
	if((c0&c1&c2&c3)==0)
	{
		row_val=0;
		break;
	}
	IOCLR0=r1;
	IOSET0=r0|r2|r3;
	if((c0&c1&c2&c3)==0)
	{
		row_val=1;
		break;
	}
	IOCLR0=r2;
	IOSET0=r1|r0|r3;
	if((c0&c1&c2&c3)==0)
	{
		row_val=2;
		break;
	}
	IOCLR0=r3;
	IOSET0=r1|r2|r0;
	if(C)
	{
		row_val=3;
		break;
	}
	}
	
	if(c0==0)
	{
		col_val=0;
	}
	if(c1==0)
	{
		col_val=1;
	}
	if(c2==0)
	{
		col_val=2;
	}
	if(c3==0)
	{
		col_val=3;
	}
	delay_ms(500);

	while((c0&c1&c2&c3)==0);   //wating for key release
	return num_lut[row_val][col_val];
 } 
 int main()
 {
 	unsigned int res;
	lcd_init();
 	lcd_string("4x4 keypad");
	while(1)
	{
		lcd_cmd(0xc0);
		res=key_scan();
		lcd_integer(res);
		delay_ms(500);
		lcd_cmd(0x01);
	}	
 }