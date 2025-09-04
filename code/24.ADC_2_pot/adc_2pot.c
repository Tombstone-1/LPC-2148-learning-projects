#include<lpc214x.h>
#define rs 1<<8
#define en 1<<9

void delay(unsigned int);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_print(unsigned char);
void lcd_string(char* str);
void display(void);

int main(){
	
	// 1. Config Pin Port for ADC 0.1 and AD0.2
	PINSEL0 = 0x00000000;
	PINSEL1 = 0x05000000;		// PORT 0 pin 28 and 29 AD0.1 AD0.2
	
	// 2. setup lcd PORT pins and initialize.
	IODIR0 = 0x0000FFFF;		// lcd_output 10 bit.
	lcd_init();
	lcd_string("AD0.1= ");
	lcd_cmd(0xC0);
	lcd_string("AD0.2= ");
	
	// 3. Config AD0CR value w/o starting it. (central value is not working. keep them seperate)
	AD0CR = 0x08200306;		// falling edge, operation mode, no start, 11 clk, 3 clkdiv, AD0.1, AD0.2
	
	while(1){
		/* falling edge, operation mode, start, 11 clk, 3 clkdiv, AD0.1, AD0.2  */
		
		// 4. load AD0.1 and setup print on lcd.
		//AD0CR = 0X09200302;
		while(!(AD0GDR & 0x80000000));	// wait for data conversion complete at ad0.1 channel
		lcd_cmd(0x87);
		display();
		delay(1000);
		
		// 5. load AD0.2 and setup print on lcd
		//AD0CR = 0X09200304;
		while(!(AD0GDR & 0x80000000));	// WAIT for conversion complete at ad0.2 channel
		lcd_cmd(0xC7);
		display();
		delay(1000);
		
	}
}

void display(void){
	int i;
	unsigned int adc_val;
	unsigned char temp;
	unsigned char adc_arr[4];
	
	adc_val = AD0GDR;
	adc_val = (adc_val >> 6) & 0x000003FF;
	
	for(i=0; i<4; i++){
		temp = adc_val % 10;
		adc_arr[i] = temp + '0';
		adc_val = adc_val / 10;
	}
	for(i=3; i>=0; i--){
		lcd_print(adc_arr[i]);
	}
}
	
void delay(unsigned int x){
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

void lcd_cmd(unsigned char cmd){
	IO0PIN = cmd;
	IO0CLR = rs;
	IO0SET = en;
	delay(200);
	IO0CLR = en;
}

void lcd_print(unsigned char dat){
	IO0PIN = dat;
	IO0SET = rs;
	IO0SET = en;
	delay(200);
	IO0CLR = en;
}

void lcd_string(char* str){
	while(*str != '\0'){
		lcd_print(*str);
		str++;
	}
}

