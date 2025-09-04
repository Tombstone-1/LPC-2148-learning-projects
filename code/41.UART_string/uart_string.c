#include<lpc214x.h>

int main(){
	
	unsigned char str[] = "Hello World";
	int i;

	PINSEL0 = 0x00000005;
	U0LCR = 0x83;
	U0DLL = 0x61;
	U0DLM = 0x00;
	U0LCR = 0x03;
	
	while(1){
		i=0;
		
		while(str[i] != '\0'){
			while(!(U0LSR & 0x60));
			U0THR = str[i];
			i++;
		}
	}
}
