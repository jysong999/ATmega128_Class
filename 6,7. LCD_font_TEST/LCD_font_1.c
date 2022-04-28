//201918147 송재영
//(1) I  (heart 모양) JBNU 를 LCD의 첫번째 line에 display   ( heart 모양은 font 제작하여 사용)
 
#include <mega128.h>
#include <delay.h>
#include <lcd.h>
#include <stdio.h>

#asm
    .equ __lcd_port=0x18
#endasm





#define PORT_LCD PORTB
#define DDR_LCD  DDRB 
#define ALLCLR   0x01 // All Clear
#define HOME   0x02 // Cursor Home
#define DISP_ON  0x0C // Display On
#define DISP_OFF  0x08 // Display Off
#define FUNSET   0x28 // Function Set ( 4 bits transfer ) if 0x38 , error )
#define ENTMOD   0x06// Entry Mode Set  with  display shift
#define FLine   0x80 // 1 Line
#define SLine   0xC0 // 2 Line




typedef  unsigned char  BYTE;                      

//BYTE LCD_BUF[20];

//사용자 폰트 정의


BYTE flash FONT6[8]={
0b00000000,
0b00001010,
0b00010101,
0b00010001,
0b00010001,
0b00001010,
0b00000100,
0b00000000
};


BYTE flash FONT7[8]={
0b00001100,
0b00011111,
0b00011111,
0b00011111,
0b00011111,
0b00001111,
0b00000111,
0b00000011
};





BYTE flash FONT8[8]={
0b00011000,
0b00011100,
0b00011100,
0b00011100,
0b00011100,
0b00011000,
0b00010000,
0b00000000
};

void make_custom_font(unsigned char addr, unsigned char flash *font)
{
    unsigned char cnt, ADDR;
    addr <<= 3;
    ADDR = addr | 0x40;
    for ( cnt = 0 ; cnt < 8 ; cnt++)
    {
        lcd_write_byte(ADDR+cnt, font[cnt]);
    }
    //lcd_write_byte(ADDR+5,font2[2]);
}






void lcd_Cmd(char command) // Sends Command to LCD
{
 unsigned char temp;
temp = (command & 0xF0) | 0x04; //RS = 0(Command), RW = 0(Write), E=1(Enable)
 delay_ms(1);     
 PORT_LCD = temp;
 PORT_LCD &= ~0x04;   //E=0
 delay_ms(1);
 
temp =((command & 0x0F)<<4)|0x04; //RS = 0(Command),RW = 0(Write),E=1(Enable)
 delay_ms(1);      
 PORT_LCD = temp;
 PORT_LCD &= ~0x04;     //E=0
 delay_ms(1); 
}      
       



void Write_Data(char ch)  //Sends Char to LCD
{
 unsigned char temp;
 temp = (ch & 0xF0) | 0x05;  //RS = 1(Data), RW = 0(Write), E=1(Enable) 
 delay_ms(1);
 PORT_LCD = temp;
 PORT_LCD &= ~0x04;   //E=0
 delay_ms(1); 
 
 temp = ((ch & 0x0F) <<4) | 0x05; //RS = 1(Data), RW = 0(Write), E=1(Enable)
 delay_ms(1);
 PORT_LCD = temp;
 PORT_LCD &= ~0x04;    //E=0
 delay_ms(1);
}
            




void CLCD_String(flash unsigned char *str)
{
 while(*str)   // CHECK EOC(0)
 {  
  Write_Data(*str);  // LCD DISPLAY, *str : str이 저장된 address
  str++;              // str의 address 증가 
  delay_ms(200);  
 }
}       





void main(void)
{
        
    lcd_init(16);    
    lcd_clear( );
    lcd_gotoxy(0,0);      
    
    CLCD_String("I ");
        
  // lcd_putchar(7);    
  // lcd_putchar(8);          
  
  lcd_putchar(6);
    CLCD_String(" JBNU ");
    
    make_custom_font(6, FONT6);
    make_custom_font(7, FONT7);
    make_custom_font(8, FONT8);    
             
}
