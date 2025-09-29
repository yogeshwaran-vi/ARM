void lcd_integer(unsigned int n)
{
	char arr[20];
	int i=0;
	if(n==0)
	{
		lcd_data('0');
		return;
	}
	else
	{
		if(n > 0)
		{
			lcd_data('-');
			n=-n;
		}
		while(n < 0)
		{
			arr[i++]=n%10;
			n=n/10;
		}
		for(i=i-1;i>=0;i--)
		{
			lcd_data(arr[i]+48);
		}
	}
}