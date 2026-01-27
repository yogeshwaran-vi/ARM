void uart1_init(void)
{
	PINSEL0|= 0x00050000;
	U1LCR   = 0x83;
	U1DLL	= 97;
	U1DLM   = 0;
	U1LCR	= 0X03;
}

void uart1_tx(unsigned char data)
{
	while(((U1LSR>>5)&1)==0);
	U1THR   = data;

}
unsigned char uart1_rx(void)
{
	while((U1LSR&1)==0);
	return U1RBR;
}
void uart_str(unsigned char *s)
{
	while(*s)
		uart1_tx(*s++);
}
