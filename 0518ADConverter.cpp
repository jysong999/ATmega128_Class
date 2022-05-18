/*****************************************************
Chip type           : ATmega128
Program type        : Application
Clock frequency     : 16.000000 MHz
Memory model        : Small
External SRAM size  : 65536
Ext. SRAM wait state: 0
Data Stack size     : 1024
*****************************************************/

#include <mega128.h> 
#include <lcd.h>
#include <delay.h> 
#include <stdio.h>

typedef unsigned char BYTE;
typedef unsigned int  WORD;

#asm
   .equ __lcd_port=0x18 ;PORTB
#endasm


BYTE LCD_BUFFER[20];
BYTE MAIN_COUNT;


//사용자 폰트 정의

BYTE flash FONT1[8]={
0b00011111,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011011,
0b00011111}; 


#define ADC0_DATA   *(unsigned int *)(0x1100)
#define ADC1_DATA   *(unsigned int *)(0x2000)
#define ADC2_DATA   *(unsigned int *)(0x3000)          
#define ADC3_DATA   *(unsigned int *)(0x4000)


#define ADC_VREF_TYPE 0x00      //ADC 전압 REFERENCE 

BYTE ADC_CHANNEL_COUNT;         //ADC 채널을 변경하기 위한 COUNT


/***********************************************
      폰트 생성 함수                                 
************************************************/
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







/***********************************************
 ADC 변환 함수 
***********************************************/
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
delay_us(10);                   // Delay needed for the stabilization of the ADC input voltage
ADCSRA|=0x40;                   // Start the AD conversion
while ((ADCSRA & 0x10)==0);     // Wait for the AD conversion to complete
return ADCW;                    //10-bit ADC Data register
} 
/***********************************************
Timer0 Overflow Interrupt (10ms)
***********************************************/
interrupt [TIM0_OVF] void timer0_overflow(void) {
// 10msec 마다 Interrupt 발생 
    TCNT0 = 99; //10msec 인터럽트 시간 조절 coun
     
    switch (ADC_CHANNEL_COUNT){
        case 0 :    ADC0_DATA = read_adc(ADC_CHANNEL_COUNT); 
                    break;
        case 1 :    ADC1_DATA = read_adc(ADC_CHANNEL_COUNT); 
                    break;
        case 2 :    ADC2_DATA = read_adc(ADC_CHANNEL_COUNT); 
                    break;
        case 3 :    ADC3_DATA = read_adc(ADC_CHANNEL_COUNT); 
                    break;
        default:    break;
    
    }

    ADC_CHANNEL_COUNT++;
    if (ADC_CHANNEL_COUNT>=4) ADC_CHANNEL_COUNT = 0;

}

// Declare your global variables here







void main(void)
{
// External SRAM page configuration: 
//              -              / 0000h - FFFFh
// Lower page wait state(s): None
// Upper page wait state(s): None
MCUCR=0x80;
XMCRA=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 1000.000 kHz
// ADC Voltage Reference: AREF pin
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x84;

//Timer0 setting
TCCR0 = 0x07; //Clock Division /1025
TCNT0 = 99; //10msec 인터럽트 시간 조절 count
TIMSK = 0x01; //Timer0_overflow Interrupt Enable

// LCD module initialization 
lcd_init(16);

SREG = 0x80;
while (1)
      { 
      
      
      // Place your code here
        lcd_gotoxy(0,0);
        sprintf(LCD_BUFFER,"ADC0,1=%4d,%4d",ADC0_DATA,ADC1_DATA);
        lcd_puts(LCD_BUFFER);
        
        
        
        lcd_gotoxy(0,1);    
        sprintf(LCD_BUFFER,"ADC2,3=%4d,%4d",ADC2_DATA,ADC3_DATA);
        lcd_puts(LCD_BUFFER);     
                        
       switch ()
             {
             case //MAX :   
     
                    lcd_gotoxy(0,0); 
                    lcd_putchar(1);    
                    lcd_gotoxy(0,1);  
                    lcd_putchar(1);    

                    make_custom_font(1, FONT1);
             break;

             case //Middle :   

                    lcd_gotoxy(0,0); 
                	lcd_putchar(1);    

 
                    

                 break;
             
             case // 1/4 :
             
             		lcd_gotoxy(0,0);
             		lcd_putchar(1);    
             		
             		
             	break;
             	
            case // min :
            
            break;

             }
          
         
      };          
        
      
            
         
      
}
