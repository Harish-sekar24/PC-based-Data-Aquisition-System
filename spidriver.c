#include <LPC21XX.H>
#include"spi.h"
#include"4bitheader.h"
#include "rtc.h"
#include"uart.h"
 int bcd(int );
int main()
{
    char d,m,s;
	float f;
	
	SPI_INIT();
	i2c_init();

	LCD_INIT();
	LCD_STR("TEMP:");
	IOPIN0|=1<<7;
    
	LCD_COMMAND(0xC0);
	LCD_STR("TIME:");
	UART0_CONFIG();	
	
	  
	 
      i2c_rtc_write(0x68,0x02,0x23);
	  i2c_rtc_write(0x68,0x01,0x59);
	  i2c_rtc_write(0x68,0x00,0x00);

	while(1)
	{

	
		UART0_STR("TEMP:");
	f=read_ADC(0);
	LCD_COMMAND(0x85);
	f=f*100;
	LCD_FLOAT(f);
    
      UART0_FLOAT(f);
	  UART0_TX('\r');
	  UART0_TX('\n');

      d=bcd(i2c_rtc_read(0x68,0x02));
	  LCD_COMMAND(0xC5);
	  LCD_DATA((d/10)+48);
	  LCD_DATA((d%10)+48);
	  LCD_DATA(':');
	   UART0_TX((d/10)+48);
	   UART0_TX((d%10)+48);
	  UART0_TX(':');
	  m=bcd(i2c_rtc_read(0x68,0x01));	  
	  LCD_DATA((m/10)+48);	 
	  LCD_DATA((m%10)+48);	  
	  LCD_DATA(':');
	 UART0_TX((m/10)+48);
	   UART0_TX((m%10)+48);
	  UART0_TX(':');	  

	  s=bcd(i2c_rtc_read(0x68,0x00));

	  LCD_DATA((s/10)+48);
	  
	  LCD_DATA((s%10)+48);
	  UART0_TX((s/10)+48);
	   UART0_TX((s%10)+48);
	   UART0_TX('\r');
	  UART0_TX('\n');
	}
}
 int bcd(int d)
 {
  	return ((d>>4)*10)+(d&0x0f);
 }
