#include<lpc214x.h>

#define in1 1<<0
#define in2 1<<1
#define en1 1<<2

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}

int main(){
	// config directins
	IO0DIR = en1 | in1 | in2;
	IO0SET = en1;
	
	while(1){
		IO0SET = in1;
		IO0CLR = in2;
		delay(500);
	}
}
