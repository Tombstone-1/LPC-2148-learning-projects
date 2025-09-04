#include<lpc214x.h>

void delay(){
	int i,j;
	for(i=0; i<255; i++)
	for(j=0; j<255; j++);
}

int main(){
	int i,temp;
	char cc_hex[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	IO0DIR = 0x000000FF;
	IO1DIR = 0x00030000;
	
	while(1){
		for(i=0; i<100; i++){
			
			temp = i/10;
			IO0CLR = 0xFF;
			
			IO1CLR = 0x30000;
			IO1SET = 0x20000;
			
			IO0SET = cc_hex[temp];
			delay();
			
			temp = i%10;
			IO0CLR = 0xFF;
			
			IO1CLR = 0x30000;
			IO1SET = 0X10000;
			IO0SET = cc_hex[temp];
			delay();
		}
	}
}
