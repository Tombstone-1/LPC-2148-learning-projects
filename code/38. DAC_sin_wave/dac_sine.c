#include<lpc214x.h>

void delay(unsigned int);

int main(){
	int sin_wave[42] = { 512,591,665,742,808,873,926,968,998,1017,1023,1017,998,968,926,873,808,742,665,591,512,436,359,282,216,211,151,97,55,25,6,0,6,25,55,97,151,211,216,282,359,436 };
	int i;
		
	PINSEL1 = 0x00080000;
	IO0DIR = 0x02000000;
	
	while(1){
		for(i=0; i<42; i++){
			DACR = sin_wave[i] << 6;
			delay(100);
		}
	}
}

void delay(unsigned int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}
