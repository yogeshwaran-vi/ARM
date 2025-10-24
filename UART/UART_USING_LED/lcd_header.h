#define LCD 0x3ff00

void lcd_cmd(unsigned char );
void lcd_data(unsigned char );
void lcd_string(unsigned char *);
void delay(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<ms);
	T0TCR=0X03;
	T0TCR=0X00;
}
void lcd_init(void)
{
	IODIR0|= LCD;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0xc0);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}
void lcd_cmd(unsigned char CMD)
{
	IOCLR0=0X3FC00;
	IOSET0=CMD;
	IOCLR0=0X100;
	IOSET0=0X200;
	delay(2);
	IOCLR0=0X200;
}
void lcd_data(unsigned char D)
{
	IOCLR0=0X3FC00;
	IOSET0=D;
	IOSET0=0X100;
	IOSET0=0X200;
	delay(2);
	IOCLR0=0X200;
}
void lcd_string(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
	}
}
