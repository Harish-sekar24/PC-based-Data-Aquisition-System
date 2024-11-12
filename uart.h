#include<lpc21xx.h>
void UART0_CONFIG(void);
void UART0_TX(unsigned char );
unsigned char UART0_RX(void);
void UART0_STR(unsigned char *);
void UART0_TXRX(char *);
void UART0_FLOAT(float );
void UART0_INTEGER(int );
 void UART0_TXRX(char *rx)
 {
    int i=0;
	char rx_byte;
		 while(1)
  {
   rx_byte=UART0_RX();
   if(rx_byte==13)
   break;
   else
   rx[i++]=rx_byte;
  }
  rx[i]='\0';
 }
 void UART0_CONFIG(void)
 {
    PINSEL0|=0X00000005;
	U0LCR=0x83;
	U0DLL=32;
	U0LCR=0x03;
 }
 void UART0_TX(unsigned char c)
 {
     U0THR=c;
	 while(((U0LSR>>5)&1)==0);
 }
  unsigned char UART0_RX(void)
  {
  while((U0LSR&1)==0);
  return U0RBR;
  }
   void UART0_STR(unsigned char *s)
   {
   while(*s)
   UART0_TX(*s++);
   }
  void UART0_INTEGER(int n)
{
int arr[5],i=0;

if(n==0)
UART0_TX('0');
else
{
if(n<0)
{
UART0_TX('-');
n=-n;
}
while(n>0)
{
arr[i++]=n%10;
n=n/10;
}
for(--i;i>=0;i--)
UART0_TX(arr[i]+48);
}
}
void UART0_FLOAT(float f)
{
  int temp;
  temp=f;
  UART0_INTEGER(temp);
  UART0_TX('.');
  temp=(f-temp)*100;
  UART0_INTEGER(temp);
}
