#include<lpc214x.h>

// (P0-P1)
#define RS 1<<0
#define EN 1<<1

void delay(unsigned int);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_print(unsigned char);
void lcd_string(char *str);

int main(){
		IO0DIR = 0x0000003F;
		
		lcd_init();
		lcd_string("  Hello World!  ");
		
		while(1){
			lcd_cmd(0xC0);
			lcd_string("** 4 bit mode **");
			delay(800);
		}
}

void delay(unsigned int x){
		int i, j;
		for(i=0; i<x; i++){
			for(j=0; j<i; j++);
		}
}

void lcd_string(char *str){
	while(*str != '\0'){
		lcd_print(*str);
		str++;
	}
}

void lcd_init(void){
		lcd_cmd(0x02);		// 4 bit mode
		lcd_cmd(0x0E);		// display on cursor steady
		lcd_cmd(0x01);		// clear screen
		lcd_cmd(0x28);		// 5x7 font in 4 bit mode
		lcd_cmd(0x80);		// force line 1 begin
}

void lcd_cmd(unsigned char cmd){
		char cmd_4bit;
	
	// for higher nibble ( D4-D7, P2-P5)
		cmd_4bit	= (cmd & 0xF0);
		IO0PIN = cmd_4bit >> 2;
	
		IO0CLR = RS;
		IO0SET = EN;
		delay(100);
		IO0CLR = EN;

	// for lower nibble ( D4-D7, P2-P5)
		cmd_4bit	= (cmd & 0x0F);
		IO0PIN = cmd_4bit << 2;
	
		IO0CLR = RS;
		IO0SET = EN;
		delay(100);
		IO0CLR = EN;
}

void lcd_print(unsigned char data){
		char data_4bit;
	
	// for higher nibble (D4-D7, P2-P5)
		data_4bit = (data & 0xF0);
		IO0PIN = data_4bit >> 2;
	
		IO0SET = RS;
		IO0SET = EN;
		delay(100);
		IO0CLR = EN;

	// for lower nibble (D4-D7, P2-P5)
		data_4bit = (data & 0x0F);
		IO0PIN  = data_4bit << 2;
		
		IO0SET = RS;
		IO0SET = EN;
		delay(100);
		IO0CLR = EN;
}
