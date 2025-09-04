/* working with UART 1 */

#include <lpc214x.h>
#define sw1 1<<14
#define sw2 1<<15

void delay(int);
void send_msg(char *);

int main(){
	
	// 1. config port pins for UART1 and Switch
	PINSEL0 = 0x00050000;		// port0.8 tx , port 0.9 rx UART 1
	IO0DIR |= (5<<16) | (0<<14) | (0<<15);
	
	// 2. load UART control register
	U1LCR = 0x83;	// DLAB enable, word length 8 bit
	
	// 3. load baud rate calculation and disable DLAB
	U1DLM = 0x00;
	U1DLL = 0x61;	// if pclk = 15mhz
	//U1DLL = 0x4E;	// if pclk = 12mhz
	U1LCR = 0x03;	// DLAB disabled and locked baud rate value.
	
	// 4. call transmit function.
	while(1){
		if(!(IO0PIN & sw1)){
			send_msg(" sw1 pressed ");
		}
		else if(!(IO0PIN & sw2)){
			send_msg(" sw2 pressed ");
		}
		else{
			// do not send anything.
		}
		delay(200);
	}
}

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}

void send_msg(char *str){
	while(*str != '\0'){
		// 5. check line status register for THR Buffer.
		while(!(U1LSR & 0x60));		// wait for THRE and TEMT to get cleared or empty
		U1THR = *str;
		str++;
	}
}

