#include<lpc214x.h>

void init_PLL(void);
void delay_ms(unsigned int ms);

int main(){
	// config led port p0.0
	IO0DIR = 1<<0;	
	
	// call pll, no while needed.
	init_PLL();
	
	while(1){
		IO0SET = 1 << 0;
		delay_ms(2);
		IO0CLR = 1 << 0;
		delay_ms(2);
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
	T0CTCR = 0x00;		// CONFIGURE T0 as timer
	T0PR = 60000-1;		// load maximum value for pulse count.
	
	T0TCR = 0x01;		// ENABLE	timer
	while(T0TC < ms);		// wait till given ms value is reach by timer count.
	T0TC = 0;
	T0TCR = 0x00;		// disable timer
}
