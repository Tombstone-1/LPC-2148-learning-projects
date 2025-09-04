// p0.17,18,19
#include<LPC214x.H>

#define led 1<<17

void delay(int);

int main(){
	// 1. config port direction.
	PINSEL0 = 0x00000000;
	IODIR0 |= led;
	
	// 2. conditions.
	while(1){
		IOSET0 = led;
		delay(200);
		IOCLR0 = led;
		delay(200);
	}
}

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}
