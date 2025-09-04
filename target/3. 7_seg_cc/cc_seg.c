#include<LPC214x.h>

void delay(int);

int main(){
	int i;
	unsigned char cc_hex[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	
	// 1. config port
	PINSEL0 = 0x00000000;
	IODIR0 |= 0xFF;
	
	// 2. conditions
	while(1){
		for(i=0; cc_hex[i]!= '\0'; i++){
			IOSET0 = cc_hex[i];
			delay(100);
			IOCLR0 = cc_hex[i];
			delay(100);
		}
	}
}

void delay(int x){
	int i,j;
	for(i=0; i<x; i++)
	for(j=0; j<i; j++);
}
