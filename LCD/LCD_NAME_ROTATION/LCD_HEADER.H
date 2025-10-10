#define lcd_pin 0xFF
#define RS      1<<8
#define E		1<<9

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *);
void delay_ms(unsigned int ms)
{
	T0PR  = 15000000-1;
	T0TCR =	0x01;
	while(T0TC<ms);
	T0TCR = 0x03;
	T0TCR = 0x00;
}
void lcd_init(void)
{
	IODIR0=lcd_pin|RS|E;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0C);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}
void lcd_cmd(unsigned char CMD)
{
	IOCLR0 = lcd_pin;
	IOSET0 = CMD;
	IOCLR0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E; 
}
void lcd_data(unsigned char D)
{
	IOCLR0 = lcd_pin;
	IOSET0 = D;
	IOSET0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E; 
}
void lcd_string(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
	}
}
