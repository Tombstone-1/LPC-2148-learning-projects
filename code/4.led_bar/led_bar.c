#include<lpc214x.h>

void delay(void);

int main(){
	//IODIR0 = 1 << 0;		// bitwise shifting 1 value in 0th position.
	//IODIR0 = led;
	//IODIR0 = led1;
	
	IODIR0	= 0x0000003FF;		// 33 << 9 , 10 bit position
	
	while(1){
		IOSET0 = 0x0000003FF;
		delay();
		IOCLR0 = 0x0000003FF;
		delay();
	}
}

void delay(void){
	int i,j;
	for(i=0; i<255; i++)
	for(j=0; j<255; j++);
}
