#include<lpc214x.h>

unsigned char Rx_msg(void);
void Tx_msg(unsigned char);

int main(){
	unsigned char Rx_char;
	
	// 1. config PORT pin selections.	P0.0 Tx, P0.1 Rx
	PINSEL0 = 0x00000005;
	
	// 2. config UART register and select Baud rate value.
	U0LCR = 0x83; 	//DLAB enable, stop bit 0, word 8 bit.
	
	// 3. load DLL and DLM value. (PLCK = 15mhz.)
	U0DLL = 0x61;		// value 97.65 = 97 = 61 hex
	U0DLM = 0x00;
	
	// 4. Disable and Lock DLAB for baud rate.
	U0LCR = 0x03;
	
	// 5. Rx or Tx value.
	while(1){
		Rx_char = Rx_msg();
		Tx_msg(Rx_char);
		
	}
}

unsigned char Rx_msg(void){
	while(!(U0LSR & 0x01));			//RBR IN DEFAULT STAY ZERO. EMPTY, wait till filled.
	return (U0RBR);
}

void Tx_msg(unsigned char msg){
	while(!(U0LSR & 0x60));			// check bit 5, 6 for THRE, TEMT
	U0THR = msg;
}

