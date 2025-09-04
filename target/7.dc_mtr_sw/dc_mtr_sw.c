#include <lpc214x.h>

/*  inbuilt switch on p0.14, p0.15 */
#define sw1 1<<14
#define sw2 1<<15
#define in1 1<<0
#define in2 1<<1

void delay(int);

int main(){
	// 1.config ports
	PINSEL0 = 0x00000000;
	IO0DIR |= in1 | in2 | (0<<14) | (0<<15);
	
	// 2. conditions
	while(1){
		if((IO0PIN & sw1) == 0){
			IO0SET = in1;
			IO0CLR = in2;
		}
		else if((IO0PIN & sw2) == 0){
			IO0CLR = in1;
			IO0SET = in2;
		}
		else{
			IO0CLR = in1;
			IO0CLR = in2;
		}
		delay(200);
	}

}

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}

	