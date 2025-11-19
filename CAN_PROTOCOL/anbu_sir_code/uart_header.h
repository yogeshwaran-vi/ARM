//uart0 serial communication header file
#include<stdio.h>
//uart0 pin selection
#define TXD0 0x00000001
#define RXD0 0x00000004

//uart0 baudrate calculation.....
//U0DLL and U0DLM registers are used to set the baudrate

#define cry_osc 12000000
#define cpu_clk cry_osc*5
#define per_clk cpu_clk
#define baudrate 115200
#define reg_val (per_clk/(16*baudrate))

//uart0 initialisation........

void uart0_init(void)
{
	PINSEL0 |= TXD0|RXD0;
	U0LCR = 0x83;
	U0DLL = 34;
//	U0DLM = reg_val>>8;
	U0LCR = 0x03;
}

void uart0_tx(uc data)
{
	while((U0LSR&(1<<6))==0);
	U0THR = data;
}

void uart0_string_tx(char *d)
{
	while(*d)
	{
		uart0_tx(*d++);
	}
}
void uart0_integer(si n)
{
	uc arr[10];
	int i=0;
	if(n==0)
	{
		uart0_tx('0');
	}
	else if(n<0)
	{
		uart0_tx('-');
		n=-n;
	}
	while(n!=0)
	{
		arr[i++] = n%10;
		n=n/10;
	}
	for(--i;i>=0;i--)
	{
		uart0_tx(arr[i]+48);
	}
}
//LCD float display.....
void uart0_float(f val)
{
		int t = val;
	  uart0_integer(t);
		uart0_tx('.');
		if(val>0)
			t = (val-t)*100;
		else
			t = -(val-t)*100;
		
		uart0_integer(t);
}
void uart0_hexa(si hv)
{
	char a[10];
	sprintf(a,"%x",hv);
	uart0_string_tx(a);
}
