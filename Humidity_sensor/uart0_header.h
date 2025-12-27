void uart0_init(void)
{
	PINSEL0 |=0x00000005;
	U0LCR = 0X83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0X03;
}
unsigned char uart0_rx(void)
{
	while((U0LSR & 0x1)==0);
	return U0RBR;
}
void uart0_tx(unsigned char data)
{
	while((U0LSR & (1<<5))==0);
	U0THR = data;
}
void uart_str(unsigned char *s)
{
	while(*s)
	{
		uart0_tx(*s++);
	}
}
