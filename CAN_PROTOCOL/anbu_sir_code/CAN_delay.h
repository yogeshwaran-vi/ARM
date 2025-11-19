//delay function for seconds
void delay_sec(uc sec)
{
	T0PR = 60000000-1;
	T0TCR = 0X01;
	while(T0TC < sec);
	T0TCR = 0X03;
	T0TCR = 0X00;	
}

//delay function for milli seconds
void delay_ms(ui ms)
{
	T0PR = 60000-1;
	T0TCR = 0X01;
	while(T0TC < ms);
	T0TCR = 0X03;
	T0TCR = 0X00;	
}

//delay function for microseconds
void delay_micsec(ui micsec)
{
	T0PR = 60-1;
	T0TCR = 0X01;
	while(T0TC < micsec);
	T0TCR = 0X03;
	T0TCR = 0X00;	
}
