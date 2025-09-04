// port 1 occupied by lcd
// port 0 to keypad.

#include<LPC214x.H>

/* keypad */
#define r1 1<<0
#define r2 1<<1
#define r3 1<<2
#define r4 1<<3
#define c1 1<<4
#define c2 1<<5
#define c3 1<<6
#define c4 1<<7

/* lcd */

#define rs 1<<17
#define rw 1<<18
#define en 1<<19

void delay(int);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_print(unsigned char);
void lcd_string(unsigned char*);
char getkey(void);

int main(){
	char key;
	// 1. config ports
	PINSEL0 = 0x00000000;
	PINSEL1 = 0x00000000;
	PINSEL2 = 0x00000000;
	
	IODIR0 |= 0x0F;		// rows = output, columns = input.
	IODIR1 |= 0xFFFF0000;
	
	// 2. init lcd
	lcd_init();
	lcd_string("   Keypad   ");
	delay(800);
	lcd_cmd(0x01);
	
	// 3. setup keypad getkey
	while(1){
		key = getkey();
		if(key == 'C'){
			lcd_cmd(0x01);
		}
		lcd_print(key);
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

char getkey(void){
	
	while(1){
        
        // scan row 1
		IOCLR0 = r1;
		IOSET0 = r2 | r3 | r4;
		if(!(IO0PIN & c1)){ while(!(IO0PIN & c1)); return '7';}
		if(!(IO0PIN & c2)){ while(!(IO0PIN & c2)); return '8';}
		if(!(IO0PIN & c3)){ while(!(IO0PIN & c3)); return '9';}
		if(!(IO0PIN & c4)){ while(!(IO0PIN & c4)); return '/';}
		
		// scan row 2
		IOCLR0 = r2;
		IOSET0 = r1 | r3 | r4;
		if(!(IO0PIN & c1)){ while(!(IO0PIN & c1)); return '4';}
		if(!(IO0PIN & c2)){ while(!(IO0PIN & c2)); return '5';}
		if(!(IO0PIN & c3)){ while(!(IO0PIN & c3)); return '6';}
		if(!(IO0PIN & c4)){ while(!(IO0PIN & c4)); return 'x';}
			
		// scan row 3
		IOCLR0 = r3;
		IOSET0 = r1 | r2 | r4;
		if(!(IO0PIN & c1)){ while(!(IO0PIN & c1)); return '1';}
		if(!(IO0PIN & c2)){ while(!(IO0PIN & c2)); return '2';}
		if(!(IO0PIN & c3)){ while(!(IO0PIN & c3)); return '3';}
		if(!(IO0PIN & c4)){ while(!(IO0PIN & c4)); return '-';}
			
		// scan row 4
		IOCLR0 = r4;
		IOSET0 = r1 | r2 | r3;
		if(!(IO0PIN & c1)){ while(!(IO0PIN & c1)); return 'C';}
		if(!(IO0PIN & c2)){ while(!(IO0PIN & c2)); return '0';}
		if(!(IO0PIN & c3)){ while(!(IO0PIN & c3)); return '=';}
		if(!(IO0PIN & c4)){ while(!(IO0PIN & c4)); return '+';}
    }
}
