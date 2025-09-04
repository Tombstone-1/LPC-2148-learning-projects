#include<lpc214x.h>

#define led 1<<0
#define sw	1<<1

int main(){
	
	IODIR0 = led | 0<<1;		// toggle its state.
	
	while(1){
	
		if((IOPIN0 & sw)==0){	// masking sw value
			IOSET0 = led;
		}
		else{
			IOCLR0 = led;
		}
	}
}
