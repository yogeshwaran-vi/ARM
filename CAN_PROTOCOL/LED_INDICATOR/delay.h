void delay_sec(unsigned int ms)
{
	T0PR = 60000000-1;
	T0TCR = 0X01;
	while(T0TC<ms);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
void delay_ms(unsigned int ms)
{
	T0PR = 60000-1;
	T0TCR = 0X01;
	while(T0TC<ms);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
void delay_mic(unsigned int ms)
{
	T0PR = 60-1;
	T0TCR = 0X01;
	while(T0TC<ms);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
