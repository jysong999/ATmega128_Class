/*
2) big number font 를 사용하여 LCD 첫번째 line과 두번째 line에 
   1초 단위로  0, ~ ,9 까지 바꿔가면서 반복하여 display        */     
         
         
         
#include <mega128.h>
#include <delay.h>
#include <lcd.h>
#include <stdio.h>

#asm
    .equ __lcd_port=0x18
#endasm


typedef  unsigned char  BYTE;                      

//BYTE LCD_BUF[20];

//사용자 폰트 정의

BYTE flash FONT1[8]={
0b00000011,
0b00000011,
0b00000011,
0b00000011,
0b00000011,
0b00000011,
0b00000011,
0b00000011}; 

BYTE flash FONT2[8]={
0b00011111,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011011};

BYTE flash FONT3[8]={
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011111};

BYTE flash FONT4[8]={
0b00011111,
0b00000011,
0b00000011,
0b00000011,
0b00000011,
0b00000011,
0b00000011,
0b00000011};

BYTE flash FONT5[8]={
0b00011111,
0b00011000,
0b00011000,
0b00011000,
0b00011000,
0b00011000,
0b00011000,
0b00011111};

BYTE flash FONT6[8]={
0b00011111,
0b00000011,
0b00000011,
0b00000011,
0b00000011,
0b00000011,
0b00000011,
0b00011111};

BYTE flash FONT7[8]={
0b00011111,
0b00011000,
0b00011000,
0b00011000,
0b00011000,
0b00011000,
0b00011000,
0b00011000};

BYTE flash FONT8[8]={
0b00011111,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011111}; 



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

void main(void)
{
        
    lcd_init(16);    
    lcd_clear( );
 
    
  while(1){
  
    //0
    lcd_gotoxy(0,0);
    lcd_putchar(2);   
    lcd_gotoxy(0,1);
    lcd_putchar(3);    
    delay_ms(1000);                 
    
    //1
    lcd_gotoxy(0,0);
    lcd_putchar(1);   
    lcd_gotoxy(0,1);
    lcd_putchar(1);   
    delay_ms(1000);

    //2
    lcd_gotoxy(0,0);
    lcd_putchar(4);   
    lcd_gotoxy(0,1);
    lcd_putchar(5);   
    delay_ms(1000);
    
    //3
    lcd_gotoxy(0,0);
    lcd_putchar(6);   
    lcd_gotoxy(0,1);
    lcd_putchar(6);  
    delay_ms(1000);
    
    //4
    lcd_gotoxy(0,0);
    lcd_putchar(3);   
    lcd_gotoxy(0,1);
    lcd_putchar(1);   
    delay_ms(1000);
    
    //5               
    lcd_gotoxy(0,0);
    lcd_putchar(5);   
    lcd_gotoxy(0,1);
    lcd_putchar(6);   
    delay_ms(1000);
    
    //6              
    lcd_gotoxy(0,0);
    lcd_putchar(7);   
    lcd_gotoxy(0,1);
    lcd_putchar(8);                   
    delay_ms(1000);
    
    //7                               
    lcd_gotoxy(0,0);
    lcd_putchar(4);   
    lcd_gotoxy(0,1);
    lcd_putchar(1);    
    delay_ms(1000);
    
    //8           
    lcd_gotoxy(0,0);
    lcd_putchar(8);   
    lcd_gotoxy(0,1);
    lcd_putchar(8);     
    delay_ms(1000);
    
    //9
    lcd_gotoxy(0,0);
    lcd_putchar(8);   
    lcd_gotoxy(0,1);
    lcd_putchar(1);      
    delay_ms(1000);         
    
   
   
    
    make_custom_font(1, FONT1);  
    make_custom_font(2, FONT2);
    make_custom_font(3, FONT3);
    make_custom_font(4, FONT4);
    make_custom_font(5, FONT5);
    make_custom_font(6, FONT6);
    make_custom_font(7, FONT7);
    make_custom_font(8, FONT8);     
       
    }
             
}
