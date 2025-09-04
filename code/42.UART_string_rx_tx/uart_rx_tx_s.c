#include<lpc214x.h>

void uart_init(void);
void send_msg(unsigned char *);

int main(){
	
	unsigned char Rx_char;
	
	// PORT pin selections for tx and rx;
	PINSEL0 = 0x0000005;
	
	uart_init();
	
	// send on uart 
	send_msg("press any key........\n");
	send_msg("A) Hello World \n");
	send_msg("B) LPC2148 ARM core \n");
	
	while(1){
		
		// Reciever register config.
		while(!(U0LSR & 0x01));			// wait until buffer register is full.
		Rx_char = U0RBR;				// rx buffer register.
		
		switch(Rx_char){
			case 'A': send_msg("\nHello World");
			break;
			
			case 'B': send_msg("\nLPC2148 ARM core");
			break;
			
			default : send_msg("\nInvalid selection");
			break;
		}
	}
}

void uart_init(void){
	// make sure main has PORT pin selection appropriately.
	U0LCR = 0x83;		// DLAB en, continuous, no parity, 8 bit word
	U0DLL = 0x61;		// LSB
	U0DLM = 0x00; 	// MSB
	U0LCR = 0x03;		// disable DLAB (lock baud rate value)
}

/* --- string Transmit Function --- */

void send_msg(unsigned char *str){
	
	while(*str != '\0'){
		while(!(U0LSR & 0x60));		// checking both bit 6 (TEMT) and bit 5 (THRE)
		
		if(*str == '\n'){
			U0THR = '\r';			// for newline in terminal.
		}
		
		U0THR = *str;
		str++;
	}
}
