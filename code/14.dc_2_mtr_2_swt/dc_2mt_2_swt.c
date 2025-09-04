#include<lpc214x.h>

#define in1 1<<0
#define in2 1<<1
#define en1 1<<2
#define en2 1<<3
#define in3 1<<4
#define in4 1<<5

#define sw1 1<<6
#define sw2 1<<7

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}

int main(){
	// config directins
	IO0DIR = en1 | in1 | in2 | en2 | in3 | in4 | 0<<6 | 0<<7;
	
	while(1){
		if((IO0PIN & sw1) == 0){
			IO0SET = en1;
			IO0SET = in1;
			IO0CLR = in2;
		}
		else{
			IO0CLR = en1;
			IO0CLR = in1;
			IO0CLR = in2;
		}
		//delay(500);
		if((IO0PIN & sw2) == 0){
			IO0SET = en2;
			IO0CLR = in3;
			IO0SET = in4;
		}
		else{
			IO0CLR = en2;
			IO0CLR = in3;
			IO0CLR = in4;
		}
		//delay(500);
	}
}
