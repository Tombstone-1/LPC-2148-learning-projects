#include<lpc214x.h>

void delay(){
	int i,j;
	for(i=0; i<255; i++)
	for(j=0; j<255; j++);
}

int main(){
	int i,j;
	int cc_hex[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	IO0DIR = 0x0000FFFF;
	
	while(1){
		for(i=0; i<10; i++){
			IO0SET = cc_hex[i];
			delay();
				
			for(j=0; j<10; j++){
				// shifting for pin 8 to 15
				
				IO0SET = cc_hex[j] << 7;
				delay();
				IO0CLR = cc_hex[j] << 7;
				delay();
			}
			IO0CLR = cc_hex[i];
			delay();
		}
	}
}
