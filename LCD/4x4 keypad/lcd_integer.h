void lcd_integer(unsigned int res)
{
	char arr[20];
	int i=0;
	if(res==0)
	{
		lcd_data('0');
	}
	else 
	{
		while(res<0)
		{
			lcd_data('-');
			res=-res;
		}
		if(0<res)
		{
			 arr[i++]=res%10;
			 res=res/10;
		}
		for(i=i-1;i>=0;i--)
		{
			lcd_data(arr[i]-48);
		}
	}
}
