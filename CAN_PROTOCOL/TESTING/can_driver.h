#include <lpc21xx.h>

void can2_init(void)
{
	PINSEL1|=0X00014000;
	VPBDIV  = 1;

	C2MOD   = 0X1;
	AFMR    = 0X2;
	C2BTR	= 0X001C001D;
	C2MOD   = 0X0;
}
void can2_tx(CAN2_MSG m1)
{
	C2TID1= m1.id;
	C2TFI1=(m1.dlc<<16);
	if(m1.rtr==0)
	{
		C2TFI1&=~(1<<30);
		C2TDA1=m1.byteA;
		C2TDB1=m1.byteB;
	}
	else
		C2TFI1|=(1<<30);

	C2CMR = ((1<<0) | (1<<5));
	while((C2GSR&(1<<3))==0);
}
void can2_rx(CAN2_MSG *m1)
{
	while((C2GSR&0x1)==0);
	m1->id=C2RID;
	m1->dlc=(C2RFS>>16)&0XF;
	m1->rtr=(C2RFS>>30)&0X1;
	if(m1->rtr==0)
	{
		m1->byteA=C2RDA;
		m1->byteB=C2RDB;
	}	
	C2CMR = (1<<2);
}
void delay_ms(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<ms);
	T0TCR=0X03;
	T0TCR=0X00;
}



