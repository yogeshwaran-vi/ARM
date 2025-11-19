
typedef struct can2
{
	int id;
	int rtr;
	int dlc;
	int byte_A;
	int byte_B;
}CAN2_MSG;

#define RM 0     //C2MOD---->CAN mode register

void can2_init(void)
{
	PINSEL1|= 0X00014000;
	VPBDIV  = 1;
	C2MOD   = 0X01;
	AFMR    = 0X02;
	C2BTR   = 0X001C001D;
	C2MOD   = 0X00;
}

void can2_tx(CAN2_MSG m1)
{
	C2TID1 = m1.id;
	C2TFI1 = m1.dlc<<16;

	if(m1.rtr==0)
	{
		C2TFI1 &=~(1<<30);
		C2TDA1  = m1.byte_A;
		C2TDB1  = m1.byte_B;
	}
	else
	{
		C2TFI1 |=(1<<30);
	}
	C2CMR |=(1<<0)|(1<<5);
	while((C2GSR&(1<<3))==0);
}
void can2_rx(CAN2_MSG *m1)
{
	while((C2GSR&(0x1))==0);
	m1->id  = C2RID;
	m1->dlc = (C2RFS>>16)&0xf;
	m1->rtr = (C2RFS>>30)&0x1;

	if(m1->rtr==0)
	{
		m1->byte_A = C2RDA;
		m1->byte_B = C2RDB;
	}
	C2CMR = (1<<2);
}
