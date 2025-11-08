

#define LCD_PIN 0x0f<<20
#define RS		1<<8
#define E		1<<9

void LCD_CMD(unsigned char ); 
void LCD_DATA(unsigned char );
void LCD_INTEGER(unsigned int);
void LCD_FLOAT(float );

void delay_ms(unsigned int ms)
{
	T1PR  = 15000-1;
	T1TCR = 0X01;
	while(T1TC<ms);
	T1TCR = 0X03;
	T1TCR = 0X00;
}
void LCD_INIT(void)
{
	IODIR0 |= LCD_PIN|RS|E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0c);
	LCD_CMD(0x28);
	LCD_CMD(0x80);
} 
void LCD_CMD(unsigned char cmd)
{
	IOCLR0 = (cmd&0XF0)<<20;
	IOSET0 = cmd;
	IOCLR0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;

	IOCLR0 = (cmd&0X0F)<<24;
	IOSET0 = cmd;
	IOCLR0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;
}
void LCD_DATA(unsigned char d)
{
	IOCLR0 = LCD_PIN;
	IOSET0 = (d&0XF0)<<20;
	IOSET0 = RS;
	IOSET0 = E;
	delay_ms(2);
	IOCLR0 = E;

	IOCLR0 = LCD_PIN;
	IOSET0 = (d&0X0F)<<24;
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
void LCD_INTEGER(unsigned int num)
{
	char arr[10];
	unsigned int i;
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
		for(i=i-1;i>=0;i--)
		{
			LCD_DATA(arr[i]-48);
		}
	}
}
