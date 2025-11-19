// header file for CAN TX and RX

#include<lpc21xx.h>

//pin selection for CAN2

#define RD2 0x00004000   //p0.23 --> RD2
#define TD2 0x00010000		// P0.24 --> TD2


//frame formet of CAN .........
struct CAN2
{
	int id;
	int rtr;
	int dlc;
	int A_bytes;
	int B_bytes;
};
typedef struct CAN2 CAN2_msg;

//CAN register bit details.............
//=========================================================
//C2MOD ---> CAN mode register.....
#define RM 0

//C2BTR  ---> CAN Bus timer register
#define speed 0x0001C001D		//125 Kbps
//#define speed 0x0001C0011		//100 kbps

//AFMR ---> Acceptance filetr mode register
#define AccBp 1		//accept all msg

//CANCMR ---> CAN command register
#define TR 0		//Transmit request
#define RRB 2		//Release receiver Buffer
#define STB1 5	// select Buffer 1 register

//C2GSR ---> CAN2 Global status register
#define TCS 3

//===========================================================
void CAN2_init(void)
{
	PINSEL1 = TD2|RD2;
	VPBDIV = 1;
	C2MOD = 0X01;	//reset mode
//	C2MOD |= (1<<RM) ;	//reset mode
	AFMR = 0X02;	//AccBp = 1 ->>> it means accept all messages
//	AFMR |= 1<<AccBp;	//AccBp = 1 ->>> it means accept all messages
	C2BTR = 0X001C001D; // 125kbps @ PCLK = 6000000
//	C2BTR = speed;
	C2MOD = 0X00;	//normal mode
//	C2MOD &= ~(1<<RM) ;	
}

void CAN2_msg_tx(CAN2_msg M1)
{
	
	C2TID1 = M1.id;
	C2TFI1 = M1.dlc<<16;
	
	if(M1.rtr == 0)
	{
		C2TFI1 &= ~(1<<30);
		C2TDA1 = M1.A_bytes;
		C2TDB1 = M1.B_bytes;
	}
	else
	{
		C2TFI1 |= (1<<30);
	}
//	C2CMR = (1<<TR)|(1<<STB1);
	C2CMR |= (1<<0)|(1<<5);
//	while((C2GSR&(1<<TCS))==0);
		while((C2GSR&(1<<3))==0);
}

void CAN2_msg_rx(CAN2_msg *M1)
{
	while((C2GSR&(0x1))==0);
	M1->id = C2RID;
	M1->dlc = (C2RFS>>16)&0xF;//current rxd msg,storing data 0 t0 3dlc
	M1->rtr = (C2RFS>>30)&0x1;//checking rtr bit 0 0r 1
	
	if(M1->rtr == 0)
	{
		M1->A_bytes = C2RDA;//upper bytes collected
		M1->B_bytes = C2RDB;//lower bytes collected
	}
	C2CMR = (1<<RRB);//release receive buffer
}
