#include<lpc214x.h>

#define rs 1<<8
#define en 1<<9

void delay_ms(unsigned int);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_print(unsigned char);
void lcd_string(char*str);

int main(){
	char lcd_dat[4];
	unsigned int adc_val;
	int i;
	
	// PORT0 config for lcd
	PINSEL0 = 0x00000000;		// PORT0 0-15 set as default 
	PINSEL1 = 0x01000000;		// PORT0 16-31 set as PORT 0.28 AD 0.1 channel active.
	IO0DIR = 0x000003FF;	// output 10 pins for lcd and rest input.
	
	// Port 1 config
	//PINSEL2 = 0x00000000;
	//IODIR1 = 0xFFFF0000;
	
	lcd_init();
	lcd_string("ADC_0.1 = ");
	delay_ms(400);
	
	while(1){
		lcd_cmd(0xC0);
		
		AD0CR = 0x09200302;	// falling edge, conversion now, operational mode, 11 clock, x=3 clkdiv, AD0 channel 1.
		
		// 1<<31 can be use but giving warning as integer conversion.(signed change)
		while(!(AD0GDR & 0x80000000));		// ADC conversion in program and checking the Done bit by 1<<31.
		
		// storing adc val and getting least significant 10 bit.
		adc_val = AD0GDR;
		adc_val = (adc_val >> 6);		// shifing and masking.
		adc_val = (adc_val & 0x3FF);
		
		for(i=0; i<4; i++){
			int temp = adc_val % 10;
			lcd_dat[i] = temp + '0';
			adc_val = adc_val / 10;
		}
		for(i=3; i>=0; i++){
			lcd_print(lcd_dat[i]);
		}
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
	lcd_cmd(0x06);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
}

void lcd_cmd(unsigned char cmd){
	IO0PIN = cmd;
	IO0CLR = rs;
	IO0SET = en;
	delay_ms(200);
	IO0CLR = en;
}

void lcd_print(unsigned char data){
	IO0PIN = data;
	IO0SET = rs;
	IO0SET = en;
	delay_ms(200);	// enable pin creating issue as with higher frequency delay is less.
	IO0CLR = en;
}

void lcd_string(char*str){
	while(*str != '\0'){
		lcd_print(*str);
		str++;
	}
}

