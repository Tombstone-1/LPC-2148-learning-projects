#include<lpc214x.h>

void delay(int);

int main(){
	// config GPIO, and PORT 0 pin 0 as output
	IODIR0 = 0x00000001;		// 1 = output
	
	while(1){
		IOSET0 = 0x00000001;		// 1 FOR HIGH
		delay(255);
		IOCLR0 = 0x00000001;		// 1 for clear set
		delay(255);
	}
}

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<x; j++);
	}
}

