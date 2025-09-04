#include<lpc214x.h>

void delay(void);

int main(){
	PINSEL0 = 0x00000000;
	PINSEL1 = 0x00000000;
	
	IODIR0	= 0xFFFFFFFF;
	
	while(1){
		IOSET0 = 0x000000FF;
		delay();
		IOCLR0 = 0x000000FF;
		delay();
		
		IOSET0 = 0x0000FF00;
		delay();
		IOCLR0 = 0x0000FF00;
		delay();
		
		IOSET0 = 0x00FF0000;
		delay();
		IOCLR0 = 0x00FF0000;
		delay();
		
		IOSET0 = 0xFF000000;
		delay();
		IOCLR0 = 0xFF000000;
		delay();
	}
}

void delay(void){
	int i,j;
	for(i=0; i<255; i++)
	for(j=0; j<255; j++);
}
