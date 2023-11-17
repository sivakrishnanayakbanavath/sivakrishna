#include "alarm.h"
#include "ports.h"
#include "lcd.h"
#include "rtc.h"
#include<reg51.h>
#define I2C_Base 0x10


unsigned char Keypress_Info = 0;
unsigned char Count =1;
unsigned char Alaram_Table_Dispaly[2][2];
unsigned char temp[4];
/*
void RTC_Write_Alarms()
{
			
 */

void Keypad_Polling()
{
	while(1)
	{
		if (increment == 0)
		{
			while(increment == 0);
			Keypress_Info = 1;
			break;	
		}
		if (decrement == 0)
		{
			while(decrement == 0);
			Keypress_Info = 2;
			break;	
		}
	}
}

void Alarm_Display()
{
	wrt_cmd(0x01);
	wrt_cmd(0x80);
	wrt_data("1.Start:");
	wrt_cmd(0xc0);
	wrt_data("  End:");
	wrt_cmd(0x80);
	wrt_cmd(0x0e);
	Alarm_Display_1();
}

void Alarm_Display_1()
{
	while(1)
	{
		Keypad_Polling();
		switch(Keypress_Info)
		{
			case 1:
					if (Count == 7)
						Count =0;
					wrt_cmd(0x80);
					wrt_byte(++Count + '0');	  
					wrt_cmd(0x80);
					wrt_cmd(0x0e);
					wrt_cmd(0x89);
					RTC_Read(0x13,1,temp);
					Keypress_Info = 0;
					break;


			case 2:
					if (Count == 1)
						Count =8;
					wrt_cmd(0x80);
					wrt_byte(--Count + '0');
					wrt_cmd(0x80);
					wrt_cmd(0x0e);
					Keypress_Info = 0;
					break;


			case 3:	break;

		 }
	}
	wrt_cmd(0x01);
}

	

		
