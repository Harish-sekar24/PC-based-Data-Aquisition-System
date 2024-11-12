int s;
float read_ADC(int);
char SPI0(char);
void SPI_INIT()
{
 	PINSEL0|=0x00001500;
	S0SPCCR=150;
	S0SPCR=(1<<5)|(0x18);
	IODIR0|=1<<7;
}
float read_ADC(int channelno)
{
 	int hbyte,lbyte;
	int adcval=0;

	IOCLR0|=1<<7;

	SPI0(0x06);
	hbyte=SPI0(channelno<<6);
	lbyte=SPI0(0x00);

	IOSET0|=1<<7;

	adcval=((hbyte&0x0f)<<8)|lbyte;
	return ((adcval*3.3)/4096);
}
char SPI0(char data)
{
	 
	  s=S0SPSR;
	  S0SPDR=data;
	  while(((S0SPSR>>7)&1)==0);
	  return S0SPDR;
}
