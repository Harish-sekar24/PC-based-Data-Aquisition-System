int i2c_rtc_read(char slaveaddr,char wordaddr);
void i2c_rtc_write(char slaveaddr,char wordaddr,char d);
void i2c_start(void);
void i2c_write(char d);
void i2c_restart(void);
int i2c_nack(void);
void i2c_stop(void);
void i2c_init(void)
{
  PINSEL0|=0x50;
  I2SCLL=75;
  I2SCLH=75;
  I2CONSET=1<<6;
}

int i2c_rtc_read(char slaveaddr,char wordaddr)
{
  int d;
  i2c_start();
  i2c_write(slaveaddr<<1);
  i2c_write(wordaddr);
  i2c_restart();
  i2c_write(slaveaddr<<1|1);
  d=i2c_nack();
  i2c_stop();
  return d;
}
void i2c_rtc_write(char slaveaddr,char wordaddr,char d)
{
  i2c_start();
  i2c_write(slaveaddr<<1);
  i2c_write(wordaddr);
  i2c_write(d);
  i2c_stop();
  delay_millisecond(10);
}
void i2c_start(void)
{
  I2CONSET=1<<5;
  while(((I2CONSET>>3)&1)==0);
  I2CONCLR=1<<5;
}
void i2c_write(char d)
{
  I2DAT=d;
  I2CONCLR=1<<3;
  while(((I2CONSET>>3)&1)==0);
}
void i2c_restart(void)
{
  I2CONSET=1<<5;
  I2CONCLR=1<<3;
  while(((I2CONSET>>3)&1)==0);
  I2CONCLR=1<<5;
}
int i2c_nack(void)
{
  I2CONSET=0x00;
  I2CONCLR=1<<3;
  while(((I2CONSET>>3)&1)==0);
  return I2DAT;
}
void i2c_stop(void)
{
  I2CONSET=1<<4;
  I2CONCLR=1<<3;
}
