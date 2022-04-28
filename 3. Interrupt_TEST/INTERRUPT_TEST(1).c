
// 내부 interrupt와 외부 interrupt를 이용한 LED 제어

//플라스틱 박스 장비 사용





#include <mega128.h>
#include <delay.h>
#include <interrupt.h>

typedef unsigned char BYTE;
typedef unsigned int WORD;

BYTE sw = 0;

BYTE MAIN_COUNT = 0, COUNT = 0;
BYTE INT_FLAG = 0;
WORD TIMER_COUNT = 0;



 
interrupt [EXT_INT0] void ext_int0_isr(void)
// int0 
{
        
       sw = !sw;
}  





interrupt [TIM0_OVF] void timer0_overflow(void) {
// 10msec 마다 Interrupt 발생 
TCNT0 = -156; //10msec 인터럽트 시간 조절 count
TIMER_COUNT++; //Interrupt 발생 Count 

    if (TIMER_COUNT>=50){  //500msec 보다 크면 
        TIMER_COUNT = 0;   //Interruput Count 초기화
        INT_FLAG = 1;      //500msec 인터럽트 발생 플래크 
    }

}






void main(void){



    
    TCCR0 = 0x07; //Clock Division /1025
    TCNT0 = 99; //10msec 인터럽트 시간 조절 count
    TIMSK = 0x01; //Timer0_overflow Interrupt Enable



    DDRD = 0x00; //PORTD(KEY)를 입력으로 설정
    sw = (PIND&0b00000001);

    DDRE = 0xff; //PORTE(LED)를 출력으로 설정 
    PORTE = 0xff; //PORTE 초기 레벨을 1로    
    
    
    EIMSK = 0b0000001;  //int0만 인터럽트를 허용
    
    EICRA = 0b00000010;    //INT0를 하강모서리에서 인터럽트 요청
    
    SREG = 0b10000000; //global 인터럽트 enable bit 

    while(1){
    
            if(sw){ 
            
                PORTE = 0b10000000; 
                delay_ms(500);
                
                PORTE = 0b11000000;   
                delay_ms(500);
                
                PORTE = 0b11100000;    
                delay_ms(500);
                
                PORTE = 0b11110000;   
                delay_ms(500);
            
            }
            else{
                  
            
                      MAIN_COUNT++;     //COUNT 1씩 증가 
                //4번째 비트부터 7번째 비트까지 증가 시켜야 하므로 MAIN_COUNT에 +3을 증가 시킨 후  오른쪽으로 1씩 shift
                 if(INT_FLAG){  //10msec 인터럽트가 50번 걸리면, (즉 500msec마다 INT_FLAG가 발생)
                                 INT_FLAG = 0;  //Interrupt Flag를 Clear
                                 COUNT++;       //LED Count 증가 
                                 PORTE = 1<<(COUNT+3); 
                //shift 된 값이 7을 초과 하지 말아야 하므로 '0'으로 초기화 한다.
                                if (COUNT>=4) COUNT = 0;
                                }
            
            
            
            
            
            
            
            
            }
    
    
    
    
    
    
    }
    

}
