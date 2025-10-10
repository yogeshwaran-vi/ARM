#include <LPC21XX.h>
#include "lcd_header.h"

#define interrupt pin 16

unsigned int i,j,count=0;
unsigned char a=0xC3,b=0x86,c=0xCA,d=0x8D,x=0x80,y=0,obj;

void cgram_car(void);
void cgram_obj(void);
void game_over(void);
void ext_int0_isr(void) __irq;

unsigned char cgram_car_sym[]={0x00,0X0E,0X1F,0X1F,0X1F,0X0A,0X0A,0X00};
unsigned char cgram_obj_sym[]={0x00,0x00,0x04,0x08,0x1F,0x08,0x04,0x00};

int main()
{
	lcd_init();
	PINSEL1 = 0x01;
	lcd_cmd(0x84);						//p0.16 interrupr pin
	lcd_string("PLAY  NOW");
	delay_ms(500);

	lcd_cmd(0xC8);
	lcd_string("03");
	delay_ms(500);

	lcd_cmd(0xC8);
	lcd_string("02");
	delay_ms(500);

	lcd_cmd(0xC8);
	lcd_string("01");
	delay_ms(500);

	lcd_cmd(0xC8);
	lcd_string("GO");
	delay_ms(500);

	cgram_car();
	lcd_cmd(0xC0); 						//STARTING ADDRESS OF LCD
	cgram_obj();
	cgram_obj();
	cgram_obj();
	cgram_obj();
   
	VICIntSelect = 0;  					//ALL IRQ SELCET-0
	
	VICVectCntl0 = (0x20)|14; 			//EXTINT NUMBER 14
	VICVectAddr0 = (unsigned long)ext_int0_isr;

	EXTMODE = 0x01;   					//EDGE SENSITIVE
	EXTPOLAR = 0x00;  					//FALLING EDGE-SENSITIVITY

	VICIntEnable = 1<<14|1<<15;   		//START WHATCHING THE INT SIGNAL

//**********main line code************//
	while(1)
	{
		lcd_cmd(0x01);
		
		if((y%2)==0)
		{
			obj=0x80;
			lcd_cmd(0x80);
		}
		else
		{
			obj=0xC0;
			lcd_cmd(0xc0);
		}

		lcd_data(0);
			
		lcd_cmd(a--);
		lcd_data(1);
		if(a==0xBF)
		{
			count++;
			a=0xCF;
		}	
		
		lcd_cmd(b--);
		lcd_data(1);
		if(b==0x7F)
		{
			count++;
			b=0x8F;
		}

		lcd_cmd(c--);
		lcd_data(1);
		if(c==0xBF)
		{
			count++;
			c=0xCF;
		}

		lcd_cmd(d--);
		lcd_data(1);
		if(d==0x7f)
		{
			count++;
			d=0x8F;
		}
		  delay_ms(500);

		if(obj==a)
		  	game_over();
		else if(obj==b)
		  	game_over();
		else if(obj==c)
		  	game_over();
		else if(obj==d)
		  	game_over();		
	}
}

//******CAR_SYMBOL_LUT********//
void cgram_car(void)
{
	char i=0;
	lcd_cmd(0x40);						//DATA 0 STARTING ADDRESS OF CGRAM
	for(i=0;i<8;i++)
	{
		lcd_data(cgram_car_sym[i]);
	}
}

//******obj_SYMBOL_LUT********//
void cgram_obj(void)
{
	char i=0;
	lcd_cmd(0x48);						//NEXT DATA 1 ADDRESS OF CGRAM
	for(i=0;i<8;i++)
	{
		lcd_data(cgram_obj_sym[i]);
	}
}

//***********GAME OVER**********//
void game_over(void)
{
	lcd_cmd(0x01);
	while(1)
	{
		lcd_cmd(0x84);
		lcd_string("GAME OVER");
		lcd_cmd(0xc7);
		lcd_integer(count);
	}
}

//***********EXINT0-ISR**********//
void ext_int0_isr(void) __irq
{
	EXTINT = 0x01;  					//reset flag 
	    y++;
	VICVectAddr=0; 
}
//*********END OF ISR********//
//****************************************THE END************************************************//
