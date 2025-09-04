#include<lpc214x.h>

#define led 1 << 0
#define led1 1 << 1

void delay(void);

int main(){
	//IODIR0 = 1 << 0;		// bitwise shifting 1 value in 0th position.
	//IODIR0 = led;
	//IODIR0 = led1;
	
	IODIR0	= led | led1;		// this way of writing consider both to run as OR condition is there.
	
	while(1){
		IOSET0 = led | led1;
		delay();
		IOCLR0 = led | led1;
		delay();
	}
}

void delay(void){
	int i,j;
	for(i=0; i<255; i++)
	for(j=0; j<255; j++);
}
