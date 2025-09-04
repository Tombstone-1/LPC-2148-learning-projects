#include<lpc214x.h>

#define led1 1<<17
#define led2 1<<18
#define led3 1<<19

void init_PLL(void);
void delay_ms(unsigned int ms);

int main(){
	// 1. Config Port for led 
	PINSEL1 = 0x00000000;
	IO0DIR |= led1 | led2 | led3;	
	
	// call pll
	init_PLL();
	
	while(1){
		IO0SET = led1;
		delay_ms(200);
		IO0SET = led2;
		delay_ms(200);
		IO0SET = led3;
		delay_ms(200);
		
		IO0CLR = led1 | led2 | led3;
		delay_ms(50);
		IO0SET = led1 | led2 | led3;
		delay_ms(50);
		IO0CLR = led1 | led2 | led3;
		delay_ms(50);
		IO0SET = led1 | led2 | led3;
		delay_ms(50);
		
		IO0CLR = led1 | led2 | led3;
		delay_ms(200);
	}
}

void init_PLL(void){
	// to generate 60 mhz from 12 mhz crystal input.
	PLL0CFG = 0x24;		// set PSEL = 2 and MSEL = 5
	PLL0CON = 0x01;		// enable PLL
	PLL0FEED = 0xAA; 	// FEED SEQUENCE 
	PLL0FEED = 0x55;	// FEED SEQUENCE this two should always reamin same
	
	while((PLL0STAT & 0x400) == 0); //  wait for feed to inserted it will go 1.
	PLL0CON = 0x03;		// PLL HAS BEEN ACTIVE AND BEING CONNECTED
	VPBDIV = 0x01;		// DIVIDE PHERIPHERAL TO HIGH performance 1/1 factor = 60 mhz
	PLL0FEED = 0xAA; 	// FEED SEQUENCE 
	PLL0FEED = 0x55;
	
}

void delay_ms(unsigned int ms){
	// 1.load timer count control register and prescaler register value. 
	T1CTCR = 0x00;		// timer mode
	T1PR = 60000-1;		// load maximum value for pulse count. 60kHz/60=1Khz for every 1ms timer counter reset.
	
	// 2. ocnfig timer control register and timer counter to reached desired value.
	T1TCR = 0x01;		// timer enable
	while(T1TC < ms);		// wait till desired delay reached
	T1TC = 0;			// reset timer counter
	T1TCR = 0x00;		// timer disable
}
