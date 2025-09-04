#include<lpc214x.h>

int main(){
	// CONFIG port pins for pwm.
	PINSEL0 = 0x00020008;		// port0.1 pwm 3 , p0.8 pwm 4
	
	// control register pwm set pwm3 and pwm 4 as set.
	PWMPCR = 0x00001800;
	
	// store total time in MR0 
	PWMMR0 = 0x000249FE;		// 150000
	
	// time control register
	PWMTCR = 0x00000009;		// counter enable, pwm enable
	
	// match control register.
	PWMMCR = 0x00000002;			// reset PWM time counter on MR0
	
	while(1){
		// store on time for pwm1 in mr1 and pwm2 in mr2
		PWMMR3 = 45000;		// 45000		30% 
		PWMMR4 = 105000;		// 105000		70% of 150000
		
		// PWM LATCH ENABLE REGISTER.
		PWMLER = 0x00000018;
	}
}
