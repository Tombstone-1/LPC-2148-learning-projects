#include<lpc214x.h>

void delay(){
	int i,j;
	for(i=0; i<255; i++)
	for(j=0; j<255; j++);
}

int main(){
	IO0DIR = 0x000000FF;
	
	while(1){
		IO0SET = 0x3F;
		delay();
		IO0CLR = 0x3F;
		delay();
		
		IO0SET = 0x06;
		delay();
		IO0CLR = 0x06;
		delay();
		
		IO0SET = 0x58;
		delay();
		IO0CLR = 0x58;
		delay();
		
		IO0SET = 0x4F;
		delay();
		IO0CLR = 0x4F;
		delay();
		
		IO0SET = 0x66;
		delay();
		IO0CLR = 0x66;
		delay();
		
		IO0SET = 0x6D;
		delay();
		IO0CLR = 0x6D;
		delay();
		
		IO0SET = 0x7D;
		delay();
		IO0CLR = 0x7D;
		delay();
		
		IO0SET = 0x07;
		delay();
		IO0CLR = 0x7F;
		delay();
		
		IO0SET = 0x6F;
		delay();
		IO0CLR = 0x6F;
		delay();
	}
}
