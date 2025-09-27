void delay_ms(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0x01;     //ENABLE
	while(T0TC<ms);
	T0TCR=0X03;		//RESET	
	T0TCR=0X00;		//DISABLE
}	
