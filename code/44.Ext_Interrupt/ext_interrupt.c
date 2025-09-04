#include <lpc214x.H>  

void delay(int count);
void init_ext_interrupt(void);
__irq void Ext_ISR(void);					// note double underscore here (__) or else it will not work.

void delay(int x){
  int i=0, j=0;
  for(i=0; i<x; i++){
    for(j=0; j<i; j++);
  }
}

int main (void) {
    init_ext_interrupt();   // initialize the external interrupt function
    
		while (1){
			 // do nothing   
		}
}

 void init_ext_interrupt(void){  // Initialize Interrupt
	 
  EXTMODE = 0x4;         //Edge sensitive mode on EINT2
  EXTPOLAR =0x00;     //falling Edge Sensitive

  PINSEL0 = 0x80000000; //Select Pin function P0.15 as EINT2
  PINSEL2 = 0X00000000;
  
  /* initialize the interrupt vector */
  VICIntSelect &= ~ (1<<16);            // EINT1 selected as IRQ 16	, clearing select bit as it is complimented.
  VICVectAddr5 = (unsigned int)Ext_ISR; // return address of ISR function when done.
  VICVectCntl5 = (1<<5) | 16;            // IRQ slot enabled, and 16 is EINT2 register bit.
  VICIntEnable = (1<<16);               // EINT2 interrupt enabled

  EXTINT &= ~(0x4);    // clearing the bit.
}

__irq void Ext_ISR(void) // Interrupt Service Routine-ISR 
{
    IO0DIR = (1<<0) | 1<<15;
    IO0SET = (1<<0);      // Turn ON LED
    delay(100000);
    IO0CLR = (1<<0);      // Turn OFF LED
    delay(100000);
    EXTINT = 0x4;          //clear interrupt
    VICVectAddr = 0;      // End of interrupt execution
}
