#include <lpc21xx.h>

void uart1_init(void)
{
	PINSEL0|=0X050000;
	U1LCR=0X83;
	U1DLL=32;
	U1DLM=0;
	U1LCR=0X03;
}

void uart1_tx(unsigned char data)
{
	while((U1LSR&(1<<5))==0);
	U1THR=data;
}
unsigned char uart1_rx(void)
{
	while((U1LSR&(0x1))==0);
	return U1RBR;
}
void uart1_string(unsigned char *s)
{
	while(*s)
		uart1_tx(*s++);
}
void uart1_hex(unsigned int num)
{
	char buf[10];
	sprintf(buf,"%x",num);
	uart1_string((unsigned char*)buf);
}
void uart1_int(unsigned int num)
{
	char buf[10];
	sprintf(buf,"%d",num);
	uart1_string((unsigned char*)buf);
}
