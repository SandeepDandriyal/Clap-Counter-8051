// Program to count the number of clap
#include<reg51.h>
#define port P1
#define dataport P2  //Data Port for LCD
#define sec 1000
sbit rs = port^0;
sbit rw = port^1;
sbit e = port^2;
sbit sensor_input=P0^0;
unsigned char str3[10]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};


void delay(unsigned int msec) // Time delay function
{
int i,j ;
for(i=0;i<msec;i++)
  for(j=0;j<1275;j++);
}

void lcd_cmd(unsigned char item) // Function to send command
{
dataport = item;
rs= 0;
rw=0;
e=1;
delay(1);
e=0;
return;
}

void lcd_data(unsigned char item) // Function to send data
{
dataport = item;
rs= 1;
rw=0;
e=1;
delay(1);
e=0;
return;
}

void lcd_data_string(unsigned char *str) // Function to send string
{
int i=0;
while(str[i]!='\0')
{
  i++;
}
while(i>=0)
{
  lcd_data(str[i]);
  i--;
  delay(10);
}
return;
}

void convert(int num)  // Function to extract digits and send to LCD
{
int i=0;
while(num>0)
{
  str3[i]=(num%10)+48;
  num=num/10;
  i++;
}
str3[i]='\0';
}
  
void main()
{
int count=0;
sensor_input=1;
sensor_input=0;
lcd_cmd(0x38);
lcd_cmd(0x0e);
lcd_cmd(0x01);
while(1)
{
  sensor_input=0;
  while(sensor_input==0);
  if(sensor_input==1)
  {
   lcd_cmd(0x01);
   count++;
   convert(count);
   lcd_cmd(0x82);
   lcd_data_string(str3);
  }
}
}
