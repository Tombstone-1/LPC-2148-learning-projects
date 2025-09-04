#include<lpc214x.h>

#define rs 1<<0
#define en 1<<1

void delay_ms(unsigned int);
void lcd_init(void);
void lcd_cmd(char);
void lcd_print(char);

int main(){
	IO0DIR = 0x000003FF;	//10 pin as output
	
	lcd_init();
	
	while(1){
		lcd_print('H');
		lcd_print('E');
		lcd_print('L');
		lcd_print('L');
		lcd_print('O');
		lcd_print('!');
		delay_ms(100);
	}
}

void delay_ms(unsigned int x){
	int i,j;
	for(i=0;i<x;i++)
	{
    for(j=0; j<i; j++); 
	}
}

void lcd_init(void){
	lcd_cmd(0x0E);
	lcd_cmd(0x01);
	//lcd_cmd(0x06);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}

void lcd_cmd(char cmd){
	IO0PIN = cmd << 2;
	IO0CLR = rs;
	IO0SET = en;
	delay_ms(100);
	IO0CLR = en;
}

void lcd_print(char data){
	IO0PIN = data << 2;
	IO0SET = rs;
	IO0SET = en;
	delay_ms(100);
	IO0CLR = en;
}

