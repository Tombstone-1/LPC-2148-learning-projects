#include<lpc214x.h>

#define led1 1<<0
#define sw1	1<<2

#define led2 1<<1
#define sw2 1<<3

int main(){
	
	IO0DIR = 0x00000003;		//port0.0, 0.1 output, 0.2, 0.3 input.
	
	//IODIR0 = led1;
	//IODIR0 = led2;
	
	while(1){
	
		if((IOPIN0 & sw1)==0){	// masking sw value
			IOSET0 = led1;
		}
		else{
			IOCLR0 = led1;
		}
		
		if((IOPIN0 & sw2)==0){	// masking sw value
			IOSET0 = led2;
		}
		else{
			IOCLR0 = led2;
		}
	}
}
