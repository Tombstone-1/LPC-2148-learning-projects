// PORT 0.21 buzzer
#include<LPC214x.H>
#define buzzer 1<<21

void delay(int);

int main(){
	// 1. config port
	IODIR0 |= buzzer;
	
	// 2. conditions
	while(1){
		IOSET0 = buzzer;
		delay(100);
		IOCLR0 = buzzer;
		delay(300);
		IOSET0 = buzzer;
		delay(100);
		IOCLR0 = buzzer;
		delay(300);
		IOSET0 = buzzer;
		delay(500);
		IOCLR0 = buzzer;
		delay(300);	
	}
}

void delay(int x){
	int i,j;
	for(i=0; i<x; i++)
	for(j=0; j<i; j++);
}

