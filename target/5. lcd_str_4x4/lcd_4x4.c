/* PORT pins for lcd are in port 1
*	rs = 17
* rw = 18
* en = 19
* D4-D7 = 20-23
*/

#include<LPC214x.H>

#define rs 1<<17
#define rw 1<<18
#define en 1<<19

void delay(int);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_print(unsigned char);
void lcd_string(unsigned char*);

int main(){
	int i;
	//1. config port 1 
	PINSEL1 = 0x00000000;
	IODIR1 = 0xFFFFFFFF;
	
	// 2.initialize lcd function on 4 bit.
	lcd_init();
	lcd_string("LPC 2148");
	lcd_cmd(0xC0);
	lcd_string("4 BIT MODE");
	
	// 3. conditions
	while(1){
		/* scroll left */
		for(i=0; i<5; i++){ lcd_cmd(0x1C);}
		
		/* scroll right */
		for(i=0; i<5; i++){ lcd_cmd(0x18);}
	}
}

void delay(int x){
	int i, j;
	for(i=0; i<x; i++){
		for(j=0; j<i; j++);
	}
}

void lcd_init(void){
	lcd_cmd(0x02);	// 4 bit mode
	lcd_cmd(0x0E);	// display on cursor steady
	lcd_cmd(0x01);	// clear display
	lcd_cmd(0x06);	//	increment cursor
	lcd_cmd(0x28);	// use 5x7 matrix font , 4 bit mode
	lcd_cmd(0x80); 	// force begin 1.1
}

void lcd_cmd(unsigned char cmd){
	unsigned char temp;
	// 1. mask and send higher nibble
	temp = cmd << 16;			// 16-23 is 8 bit, and 0x80 as 0-3 has 0 and 4-7 has 8 and we need higher nibble.
	temp = (cmd & 0xF0);
	IOPIN1 = temp;
	IOCLR1 = rs;
	IOCLR1 = rw;
	IOSET1 = en;
	delay(100);
	IOCLR1 = en;
	
	// 2. mask and send lower nibble
	temp = cmd << 20;		// coz we only need lower bit so first position lower bit in place of higher 4 bit. that is 4-7 i.e 20
	temp = (cmd & 0x0F);
	IOPIN1 = temp;
	IOCLR1 = rs;
	IOCLR1 = rw;
	IOSET1 = en;
	delay(100);
	IOCLR1 = en;
}
	
void lcd_print(unsigned char data){
	unsigned char temp;
	// 1. mask and send higher nibble
	temp = data << 16;			// 16-23 is 8 bit, and 0x80 as 0-3 has 0 and 4-7 has 8 and we need higher nibble.
	temp = (data & 0xF0);
	IOPIN1 = temp;
	IOSET1 = rs;
	IOCLR1 = rw;
	IOSET1 = en;
	delay(100);
	IOCLR1 = en;
	
	// 2. mask and send lower nibble
	temp = data << 20;		// coz we only need lower bit so first position lower bit in place of higher 4 bit. that is 4-7 i.e 20
	temp = (data & 0x0F);
	IOPIN1 = temp;
	IOSET1 = rs;
	IOCLR1 = rw;
	IOSET1 = en;
	delay(100);
	IOCLR1 = en;
}

void lcd_string(unsigned char *msg){
	while(*msg != '\0'){
		lcd_print(*msg);
		msg++;
	}
}
