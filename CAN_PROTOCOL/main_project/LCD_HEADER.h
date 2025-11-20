#define LCD_PIN 0xff<<8
#define RS		1<<16
#define E		1<<18

void LCD_CMD(unsigned char ); 
void LCD_DATA(unsigned char );
void LCD_INTEGER(int);
void LCD_FLOAT(float );

void delay_ms(unsigned int ms)
{
	T0PR  = 15000-1;
	T0TCR = 0X01;
	while(T0TC<ms);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
void LCD_INIT(void)
{
	IODIR0 |= LCD_PIN|RS|E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0c);
	LCD_CMD(0x38);
	LCD_CMD(0x80);
} 
void LCD_CMD(unsigned char cmd)
{
	IOPIN0 = cmd<<8;
	IOCLR0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;
}
void LCD_DATA(unsigned char d)
{
	IOPIN0 = d<<8;
	IOSET0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;
}
void LCD_STRING(unsigned char *s)
{
	while(*s)
		LCD_DATA(*s++);
}
void LCD_FLOAT(float value)
{

  unsigned int number;
  number = value;
  LCD_INTEGER(number);
  LCD_DATA('.');
  number=(value-number)*100;
  LCD_INTEGER(number);
}
void LCD_INTEGER(int num)
{
	signed char arr[5],i=0;
	if(num==0)
		LCD_DATA('0');
	else
	{
		if(num<0)
		{
			LCD_DATA('-');
			num=-num;
		} 
		while(num>0)
		{
			arr[i++]=num%10;
			num=num/10;
		}
		for(--i;i>=0;i--)
		{
			LCD_DATA(arr[i]+48);
		}
	}
}
