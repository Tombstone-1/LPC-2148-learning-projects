#include<LPC214X.H>

#define led  1<<18

int main(){
	unsigned char Rx_char;
	IO0DIR = led;
	
	// 1. config PORT pin selections.	P0.0 Tx, P0.1 Rx
	PINSEL0 = 0x00000005;
	
	// 2. config UART register and select Baud rate value.
	U0LCR = 0x83; 	//DLAB enable, stop bit 0, word 8 bit.
	
	// 3. load DLL and DLM value. (PLCK = 15mhz.)
	//U0DLL = 0x61;		// value 97.65 = 97 = 61 hex
	U0DLL = 0xC3;		// internal pll
	U0DLM = 0x00;
	
	// 4. Disable and Lock DLAB for baud rate.
	U0LCR = 0x03;
	
	// 5. Rx or Tx value.
	while(1){
		while(!(U0LSR & 0x01));			//RBR IN DEFAULT STAY ZERO. EMPTY, wait till filled.
		Rx_char = U0RBR;
		
		switch(Rx_char){
			case '1': IO0SET = led;
			break;
			
			case '0': IO0CLR = led;
			break;
			
		}
	}
}




