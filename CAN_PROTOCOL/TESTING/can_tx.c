#include <lpc21xx.h>
typedef struct can2
{
	unsigned int id;
	unsigned int rtr;
	unsigned int dlc;
	unsigned int byteA;
	unsigned int byteB;
}CAN2_MSG;

#include "can_driver.h"

int main()
{
	CAN2_MSG m1;
	can2_init();
	m1.id  = 0x1CD;
	m1.rtr = 0;
	m1.dlc = 4;
	m1.byteA = 0xAABBCCDD;
	m1.byteB = 0x00;

	while(1)
	{
		can2_tx(m1);
	}
}

