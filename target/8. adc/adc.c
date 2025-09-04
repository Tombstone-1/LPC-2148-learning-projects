#include<lpc214x.h>

#define rs 1<<17
#define rw 1<<18
#define en 1<<19

void delay(int);
void display(void);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_print(unsigned char);
void lcd_string(unsigned char*);

int main(){
	
	// 1. config port pins
	PINSEL0 = 0x00000000;
	PINSEL1 = 0x01000000;		// PORT0.28 adc 0.1
	PINSEL2 = 0x00000000;
	IO0DIR |= 0 << 28;
	IO1DIR |= 0xFFFF0000;
	
	// 2. config lcd 
	lcd_init();
	lcd_string("Checking ADC... ");
	
	// 3. setup ADC
	AD0CR = 0x00200302;	// rising edge, operational, 11 clks, clkdiv 3, ad0.1
	
	while(1){
		AD0CR |= (1 << 24);		// start conversion.
		while(!(AD0GDR & 0x80000000));	// wait for conversion.
		
		// 4. parse adc_val
		lcd_cmd(0xC0);
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
	adc_val = (adc_val >> 6) & 0x000003FF;		// 6 shift cause of 0-5 bit reserved and we have to find 10 bit value of adc.
	
	for(i=0; i<4; i++){
		temp = adc_val % 10;
		adc_arr[i] = temp + '0';
		adc_val = adc_val / 10;
	}
	for(i=3; i>=0; i--){
		lcd_print(adc_arr[i]);
	}
}


void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}

void lcd_init(void){
	lcd_cmd(0x02);	// 4 bit mode
	lcd_cmd(0x0E);	// display on cursor steady
	lcd_cmd(0x01);	// clear display
	lcd_cmd(0x06);	//	increment cursor
	lcd_cmd(0x28);	// use 5x7 matrix font , 4 bit mode
	lcd_cmd(0x80); 	// force begin 1.1
}

void lcd_cmd(unsigned char cmd){
	unsigned char temp;
	// 1. mask and send higher nibble
	temp = cmd << 16;			// 16-23 is 8 bit, and 0x80 as 0-3 has 0 and 4-7 has 8 and we need higher nibble.
	temp = (cmd & 0xF0);
	IOPIN1 = temp;
	IOCLR1 = rs;
	IOCLR1 = rw;
	IOSET1 = en;
	delay(100);
	IOCLR1 = en;
	
	// 2. mask and send lower nibble
	temp = cmd << 20;		// coz we only need lower bit so first position lower bit in place of higher 4 bit. that is 4-7 i.e 20
	temp = (cmd & 0x0F);
	IOPIN1 = temp;
	IOCLR1 = rs;
	IOCLR1 = rw;
	IOSET1 = en;
	delay(100);
	IOCLR1 = en;
}
	
void lcd_print(unsigned char data){
	unsigned char temp;
	// 1. mask and send higher nibble
	temp = data << 16;			// 16-23 is 8 bit, and 0x80 as 0-3 has 0 and 4-7 has 8 and we need higher nibble.
	temp = (data & 0xF0);
	IOPIN1 = temp;
	IOSET1 = rs;
	IOCLR1 = rw;
	IOSET1 = en;
	delay(100);
	IOCLR1 = en;
	
	// 2. mask and send lower nibble
	temp = data << 20;		// coz we only need lower bit so first position lower bit in place of higher 4 bit. that is 4-7 i.e 20
	temp = (data & 0x0F);
	IOPIN1 = temp;
	IOSET1 = rs;
	IOCLR1 = rw;
	IOSET1 = en;
	delay(100);
	IOCLR1 = en;
}

void lcd_string(unsigned char *msg){
	while(*msg != '\0'){
		lcd_print(*msg);
		msg++;
	}
}
