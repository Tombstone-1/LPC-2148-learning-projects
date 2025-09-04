#include <lpc214x.h>

int main(){
	// 1. config port of External Interrupt.
	PINSEL0 = 0x000000C0;		// EINT 1	, p0.3
	IO0DIR = 0x000000008;		// output
}