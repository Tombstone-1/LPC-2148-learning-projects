#include<lpc214x.h>

#define rs 1<<8
#define en 1<<9

void delay(int);
void lcd_init(void);;
void lcd_cmd(char);
void lcd_print(char);
char keypad(void);

int main(){
	char key_dat;
	// PINSEL CONFIGURE PIN FUNCTIONALITY (0 = DEFAULT)
	PINSEL0=PINSEL2=0;		
	
	// config direction for lcd 10 bit port selection.
	IO0DIR = 0x000003FF;
	
	// config keypad p16 -18 input, p19 -22 output.
	IO1DIR = 0x0780000;
	
	lcd_init();
	while(1){
		key_dat = keypad();
		lcd_print(key_dat);
		delay(100);
	}
}

void delay(int x){
	int i,j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}

void lcd_init(void){
	lcd_cmd(0x0E);
	lcd_cmd(0x01);
	lcd_cmd(0x38);
	lcd_cmd(0x06);
	lcd_cmd(0x80);
}

void lcd_cmd(char cmd){
	IO0PIN = cmd;
	IO0CLR = rs;
	IO0SET = en;
	delay(100);
	IO0CLR = en;
}

void lcd_print(char data){
	IO0PIN = data;
	IO0SET = rs;
	IO0SET = en;
	delay(100);
	IO0CLR = en;
}

char keypad(void){
	while(1){
		// FOR ROW 1 SCAN
		IO1CLR = (1<<19);
		IO1SET = (1<<20) | (1<<21) | (1<<22);
		if(!(IO1PIN & (1<<16))){ while(!(IO1PIN & (1<<16))); return '1';}
		if(!(IO1PIN & (1<<17))){ while(!(IO1PIN & (1<<17))); return '2';}
		if(!(IO1PIN & (1<<18))){ while(!(IO1PIN & (1<<18))); return '3';}

		
		// FOR ROW 2 SCAN
		IO1CLR = (1<<20);
		IO1SET = (1<<19) | (1<<21) | (1<<22);
		if(!(IO1PIN & (1<<16))){ while(!(IO1PIN & (1<<16))); return '4';}
		if(!(IO1PIN & (1<<17))){ while(!(IO1PIN & (1<<17))); return '5';}
		if(!(IO1PIN & (1<<18))){ while(!(IO1PIN & (1<<18))); return '6';}
		
		
		// FOR ROW 3 SCAN
		IO1CLR = (1<<21);
		IO1SET = (1<<19) | (1<<20) | (1<<22);
		if(!(IO1PIN & (1<<16))){ while(!(IO1PIN & (1<<16))); return '7';}
		if(!(IO1PIN & (1<<17))){ while(!(IO1PIN & (1<<17))); return '8';}
		if(!(IO1PIN & (1<<18))){ while(!(IO1PIN & (1<<18))); return '9';}
		
		
		// FOR ROW 4 SCAN
		IO1CLR = (1<<22);
		IO1SET = (1<<19) | (1<<20) | (1<<21);
		if(!(IO1PIN & (1<<16))){ while(!(IO1PIN & (1<<16))); return '*';}
		if(!(IO1PIN & (1<<17))){ while(!(IO1PIN & (1<<17))); return '0';}
		if(!(IO1PIN & (1<<18))){ while(!(IO1PIN & (1<<18))); return '#';}
	}
}

