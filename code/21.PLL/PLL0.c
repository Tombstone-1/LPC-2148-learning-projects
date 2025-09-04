#include<lpc214x.h>

void init_PLL(void);

int main(){
	// call pll, no while needed.
	init_PLL();
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

