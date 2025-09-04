#include<lpc214x.h>

void delay(unsigned int);

int main(){
	int i;		// use int as using char will give warning( comparison will always true.
	PINSEL1 = 0x00080000;
	IO0DIR = 0x02000000;
	
	delay(100);
	
	while(1){
		for(i=0x000; i<=0x3FF; i++){
			DACR = (i << 6);
		}
		DACR = 0x000;
	}
}

void delay(unsigned int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}
