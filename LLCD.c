#include "ports.h"
#include "lcd.h"
#include<reg51.h>

code bit_8 code *intro[]={" Digi clock by:"," NCET "};
code bit_8 code cgram[]={0x4,0xe,0xe,0xe,0x1f,0x0,0x4,0x0,
						0x1,0x3,0xf,0xf,0xf,0x3,0x1,0x0,
						0x8,0x10,0x0,0x18,0x0,0x10,0x8,0x0,
						0x0,0xe,0x15,0x17,0x11,0xe,0x0,0x0,
						0x0,0x1,0x3,0x16,0x1c,0x8,0x0,0x0,
						0xa,0x1f,0x1f,0x1f,0xe,0x4,0x0,0x0,
						0x2,0x3,0x2,0x0e,0x1e,0x0c,0x0,0x0};
					



void MS_Delay(unsigned int itime)
{
	unsigned char j;
	for(;itime != 0;itime--)
		for(j = 0;j<100;j++) ;
		
}


void busy()
{
	
	D7=1;  /* making D7 as input port pin		  */
	rs=0;  /*command */
	rw=1;  /*read*/	
		while(D7!=0)
	{
  		en=0;
   		en=1;
    }
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**** Writing command to LCD ****
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void wrt_cmd(bit_8 val_lcd)
{

	MS_Delay(10);
	busy();
	lcd_port=val_lcd;
	rs=0;
	rw=0;
	en=1;
	en=0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~
**** Writing data on LCD ****
~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void wrt_data(bit_8 *string)
{
	bit_8 i;
	for(i=0;string[i]!='\0';i++)
		wrt_byte(string[i]);
}

void wrt_byte(bit_8 value)
{
	
	MS_Delay(10);
	busy();
	lcd_port=value;	  /*put the value on LCD*/
	rs=1;
	rw=0;
	en=1;
	en=0;
}

void LCD_INI(void)
{
	wrt_cmd(0X38);	 /*5*7 Matrix LCD inialization*/
	wrt_cmd(0X0C);	 /*	display on cursor off*/
	wrt_cmd(0X01);	/*clear display screen*/
	wrt_cmd(0X06);	 /*increment cursor,shift cursor to right*/
}

void build_ram()		  /*this is for displaying symbols on LCD*/
{						 
	bit_8 i;
	wrt_cmd(0x40);
	for(i=0;i<56;i++)
		wrt_byte(cgram[i]);
}

void disp_intro()
{
	bit_8 i;
	bit_16 j;
	wrt_cmd(0x80);		/*Force cursor to beginning of 1st line*/
	wrt_byte(CLOCK);	/*displaying clock symbol on LCD*/
	wrt_data(intro[0]);
	wrt_cmd(0xc0);		 /*force cursor to beginning of 2nd line*/
	wrt_byte(HEART);
	wrt_data(intro[1]);	  /*displaying speaker symbol on LCD*/
	wrt_byte(HEART);
	for(i=0x5;i>0;i--)
		for(j=0xffff;j>0;j--);
}  
