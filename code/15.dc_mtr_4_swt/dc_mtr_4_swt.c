#include<lpc214x.h>

#define in1 1<<0
#define in2 1<<1
#define en1 1<<2
#define en2 1<<3
#define in3 1<<4
#define in4 1<<5

#define sw1 1<<6
#define sw2 1<<7
#define sw3 1<<8
#define sw4 1<<9

int main(){
	// config direction (direction for switch is directly mentions as 0<<6 or 0<<9)
	IO0DIR = in1 | in2 | en1 | en2 | in3 | in4 | 0<<6 | 0<<7 | 0<<8 | 0<<9;
	
	while(1){
		if((IO0PIN & sw1) == 0){	// all clockwise
			IO0SET = en1 | en2 | in1 | in3;
			//IO0SET = in1 | in3;
			IO0CLR = in2 | in4;
		}
		else if((IO0PIN & sw2) == 0){	// all anti clockwise
			IO0SET = en1 | en2 | in2 | in4;
			IO0CLR = in1 | in3;
			//IO0SET = in2 | in4;
		}
		else if((IO0PIN & sw3) == 0){	// upper 2 clockwise
			IO0SET = en1 | in1;
			IO0CLR = en2 | in2;
		}
		else if((IO0PIN & sw4) == 0){	// lower 2 anti clockwise
			IO0SET = en2 | in4;
			IO0CLR = en1 | in3;
		}
		else{
			// always clear
			IO0CLR = en1 | en2;
		}
	}
}

	