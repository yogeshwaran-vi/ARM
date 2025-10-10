#include <lpc21xx.h>
#include "lcd_header.h"

int main()
{
	lcd_init();
	lcd_cmd(0x80);
	lcd_string("YOGESH MARI");

}
