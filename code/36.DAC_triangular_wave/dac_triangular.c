#include<lpc214x.h>

void delay(unsigned int);

int main(){
	int i;
	PINSEL1 = 0x00080000;
	IO0DIR = 0x02000000;
	
	delay(100);
	
	while(1){
		for(i=0x000; i<=0x3FF; i++){
			DACR = (i << 6);
		}
		for(i=0x3FF; i>=0x000; i--){
			DACR = (i << 6);
		}
	}
}

void delay(unsigned int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}
