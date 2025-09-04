#include<lpc214x.h>

int main(){
	// CONFIG port pins for pwm.
	PINSEL0 = 0x00008002;		// port0.0 pwm 1 , p0.7 pwm 2
	
	// control register pwm set pwm1 and pwm 2 as set.
	PWMPCR = 0x00000600;
	
	// store total time in MR0 
	PWMMR0 = 0x000249FE;		// 150000
	
	// time control register
	PWMTCR = 0x00000009;
	
	// match control register.
	PWMMCR = 0x00000002;
	
	while(1){
		// store on time for pwm1 in mr1 and pwm2 in mr2
		PWMMR1 = 0x000124F8;		// 75000		50% 
		PWMMR2 = 0x00015F90;		// 90000		60% of 150000
		
		// PWM LATCH ENABLE REGISTER.
		PWMLER = 0x00000006;
	}
}
