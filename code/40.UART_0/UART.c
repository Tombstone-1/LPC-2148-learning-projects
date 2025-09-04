#include<lpc214x.h>

int main(){
	// config port pin as RX and Tx for UART
	PINSEL0 = 0x00000005;
	
	// config UART
	U0LCR = 0x83;	// DLAB enable, stop 1 bit, parity 0, break disable, word length 8 bit.
	U0DLL = 0x61;
	U0DLM = 0x00;		// DLM AND DLL VALUE OF BAUD RATE CALCULATION.
	
	U0LCR = 0x03;		// disable DLAB.
	
	while(1){
		while(!(U0LSR & 0x60));	// wait for empty // check THR and TEMT register.
		U0THR = 'A';
	}
}
