#include<lpc214x.h>
#include<math.h>

void delay(unsigned int);

int main(){
	float sin_val;
	int i;
	
	// config pins and port
	PINSEL1 = 0x0008000;
	IO0DIR = 0x02000000;
	
	while(1){
		for(i=0; i<1023; i++){
			sin_val = sin((2* 3.14 * i)/ 1023);		// formula : sin(2 * pi * number / size) where size is your bits. like 256 1023.
			sin_val = ((sin_val * 512) + 512);		// formula : (sin_val * amplitude) + offset, amplitude is your middle value and offset is to keep the wave or center it, within positive range.
			
			DACR = (int)sin_val << 6;
			delay(100);
		}
	}
}

void delay(unsigned int x){
	int i,j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}
