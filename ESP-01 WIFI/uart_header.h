void delay_ms(unsigned int ms)
{
	T0PR  = 15000-1;
	T0TCR = 0X01;
	while(T0TC<ms);
	T0TCR = 0X03;
	T0TCR = 0X00;
}
void uart_init()
{
	PINSEL0|= 0x00000005;
	U0LCR   = 0X83;
	U0DLL   = 97;
	U0DLM	= 0;
	U0LCR   = 0X03;
}
unsigned char uart_rx(void)
{
	while((U0LSR&0x01)==0);
	return U0RBR;
}
void uart_tx(unsigned char data)
{
	while(((U0LSR>>5)&1)==0);
	U0THR = data;
}
void uart_str(unsigned char *s)
{
	while(*s)
		uart_tx(*s++);
}
void esp_init()
{
	uart_str("AT\r\n");
	delay_ms(5000);
	uart_str("ATE0\r\n");
	delay_ms(5000);
	uart_str("AT+CWQAP\r\n");
	delay_ms(5000);
	uart_str("AT+CWJAP=\"yogesh\",\"12345678\"\r\n");
	delay_ms(5000);
}
void esp_send(unsigned char *val)
{
	uart_str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
	delay_ms(5000);
	uart_str("AT+CIPSEND=90\r\n");
	delay_ms(5000);
	uart_str("GET /update?api_key=VHUZBR7KFRYEI6FN&field1=");
	uart_str(val);
	uart_str("HTTP/1.1\r\n");
	uart_str("Host: api.thingspeak.com\r\n");
	uart_str("\r\n");
	delay_ms(5000);
	uart_str("AT+CIPCLOSE\r\n");
}
