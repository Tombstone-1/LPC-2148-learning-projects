// switch at p0.14, 15, 16

#include<LPC214x.h>

#define led1 1<<17
#define led2 1<<18
#define led3 1<<19

#define swt1 1<<14
#define swt2 1<<15
#define swt3 1<<16

void delay(int);

int main(){
	// 1. config ports
	PINSEL0 = 0x00000000;
	PINSEL1 = 0x00000000;
	IODIR0 |= led1 | led2 | led3 | 0<<14 | 0<<15 | 0<<16;
	
	// 2. conditions
	while(1){
		if((IOPIN0 & swt1) == 0){
			IOSET0 = led1;
		}
		else{
			IOCLR0 = led1;
		}
		if((IOPIN0 & swt2) == 0){
			IOSET0 = led2;
		}
		else{
			IOCLR0 = led2;
		}
		if((IOPIN0 & swt3) == 0){
			IOSET0 = led3;
		}
		else{
			IOCLR0 = led3;
		}
	}
}

	