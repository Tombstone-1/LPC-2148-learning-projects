#include<lpc214x.h>

void delay(unsigned int);

int main(){
	PINSEL1 = 0x00080000;
	IO0DIR = 0x02000000;
	
	delay(100);
	
	while(1){
		DACR = (0x3FF << 6);
		delay(200);
		DACR = (0x000 << 6);
		delay(200);
	}
}

void delay(unsigned int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}
