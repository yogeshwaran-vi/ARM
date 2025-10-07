void delay_ms(unsigned int S)
{
	T1PR=15000-1;
	T1TCR=0x01;		//ENABLE
	while(T1TC<S);
	T1TCR=0x03;		//RESET
	T1TCR=0x00;	    //DISABLE
}
