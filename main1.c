#include<reg51.h>
#include "ports.h"
#include "lcd.h"
#include "rtc.h"

bit flag=0,aflag=0,aon=0,aoff=0, alarm_off = 0;

void main()
{
	unsigned char i=0;
	alarmset_port = 0;	  /*make the alarm port pin low*/
	LCD_INI();
	build_ram();
	//rtc_check();	
	disp_intro();
			
	ENABLE_INT;
	wrt_cmd(0x1);	 /*clear screen*/
	start_rtc();	  
	send_adr(0xd0);	  /*send the device address*/
	send_adr(0x00);	   /*send the secs register address*/
	start_rtc();		/*repeated start*/
	send_adr(0xd1);		 /*read the data from the device*/
	recv_data();		  /*receive the data from slave*/
	while(1)
	{

		start_rtc();
		send_adr(0xd0);	   /*send the device address*/
		send_adr(0x00);		/*send the secs register address*/
		start_rtc();		 /*repeated start*/
		send_adr(0xd1);		  /*read the data from the device*/
		recv_data();		   /*receive the data from slave*/
		disp_rtc();			   /*display data on LCD*/
		if(_testbit_(flag))		   /* rtc set flag*/
		{
			DISABLE_INT
			rtc_set();
			ENABLE_INT
			flag=0;
		}
		check_alarm();

	}
}

void set_flag() interrupt 0			   /*set tne RTC*/
{
	flag=1;
}

void set_aflag() interrupt 1			/*set the alarm*/
{
	aflag=1;
	if(aoff)
	{
		aoff=1;
		aflag=0;
		aon=0;
	}
}