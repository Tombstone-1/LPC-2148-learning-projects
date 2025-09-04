#include<lpc214x.h>
#define rs 0
#define en 1
void lcd_cmd(char);
void lcd_dat(unsigned char);
void delay(int);
void display();

int main()
{    
    unsigned char i;
    char cmd[8]={0x38,0x0e,0x01,0x06,0X80};
    char name1[12]="ADC Values";
    char name2[12]="ADC Values";

    PINSEL0=0x00000000;
    PINSEL1=0x11000000;
    IODIR0=0x000FFFF;
    PINSEL2=0;
    IODIR1=0XFFFF0000;
    for(i=0;i<6;i++)
     {
         lcd_cmd(cmd[i]);
        delay(5);
              
     }
     for(i=0;i<12;i++)
    {
         lcd_dat(name1[i]);
        delay(100);
        
    }
    
    lcd_cmd(0Xc0);
    for(i=0;i<12;i++)
    {
         lcd_dat(name2[i]);
        delay(100);
        
    }
while(1)
{
    AD0CR=0X01200302;       //AD0.1 //0000 0010
    while(!(AD0GDR & 1<<31));       //waiting A/D conversion
    lcd_cmd(0X80);
    display();
    delay(1000);
    lcd_cmd(0x01);
    
    
    
    AD0CR=0X01200308;       //AD0.3 refer calculation in book////0000 1000
    while(!(AD0GDR & 1<<31));       //waiting A/D conversion
    lcd_cmd(0xC0);
    display();
    delay(1000);
    

}

}

void lcd_cmd(char cmd)
{
    IOPIN0=cmd<<8;
    IOCLR0=(1<<rs);
    IOSET0=(1<<en);
    delay(10);
    IOCLR0=(1<<en);
}

void lcd_dat(unsigned char dat)
{
    IOPIN0=dat<<8;
    IOSET0=(1<<rs);
    IOSET0=(1<<en);
    delay(10);
    IOCLR0=(1<<en);
}

void delay(int x)
{
    int i,j;
    for(i=0;i<100;i++)
    for(j=0;j<x;j++);
}

void display()
{
    
  unsigned char a,b,c,d;
   unsigned int val;
       val=AD0GDR;
    val=(val>>6)&0x3FF;
    IOPIN1=val<<16;
   a=val%10;
   val=val/10;
   b=val%10;
   val=val/10;
   c=val%10;
   val=val/10;
   d=val;
   lcd_dat(d+48);
   lcd_dat(c+48);
   lcd_dat(b+48);
   lcd_dat(a+48);
    
}