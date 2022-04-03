//���ڰ��к� 201918147 ���翵

// ���� interrupt�� �ܺ� interrupt�� �̿��� LED ����

//�ö�ƽ �ڽ� ��� ���





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
// 10msec ���� Interrupt �߻� 
TCNT0 = -156; //10msec ���ͷ�Ʈ �ð� ���� count
TIMER_COUNT++; //Interrupt �߻� Count 

    if (TIMER_COUNT>=50){  //500msec ���� ũ�� 
        TIMER_COUNT = 0;   //Interruput Count �ʱ�ȭ
        INT_FLAG = 1;      //500msec ���ͷ�Ʈ �߻� �÷�ũ 
    }

}






void main(void){



    
    TCCR0 = 0x07; //Clock Division /1025
    TCNT0 = 99; //10msec ���ͷ�Ʈ �ð� ���� count
    TIMSK = 0x01; //Timer0_overflow Interrupt Enable



    DDRD = 0x00; //PORTD(KEY)�� �Է����� ����
    sw = (PIND&0b00000001);

    DDRE = 0xff; //PORTE(LED)�� ������� ���� 
    PORTE = 0xff; //PORTE �ʱ� ������ 1��    
    
    
    EIMSK = 0b0000001;  //int0�� ���ͷ�Ʈ�� ���
    
    EICRA = 0b00000010;    //INT0�� �ϰ��𼭸����� ���ͷ�Ʈ ��û
    
    SREG = 0b10000000; //global ���ͷ�Ʈ enable bit 

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
                  
            
                      MAIN_COUNT++;     //COUNT 1�� ���� 
                //4��° ��Ʈ���� 7��° ��Ʈ���� ���� ���Ѿ� �ϹǷ� MAIN_COUNT�� +3�� ���� ��Ų ��  ���������� 1�� shift
                 if(INT_FLAG){  //10msec ���ͷ�Ʈ�� 50�� �ɸ���, (�� 500msec���� INT_FLAG�� �߻�)
                                 INT_FLAG = 0;  //Interrupt Flag�� Clear
                                 COUNT++;       //LED Count ���� 
                                 PORTE = 1<<(COUNT+3); 
                //shift �� ���� 7�� �ʰ� ���� ���ƾ� �ϹǷ� '0'���� �ʱ�ȭ �Ѵ�.
                                if (COUNT>=4) COUNT = 0;
                                }
            
            
            
            
            
            
            
            
            }
    
    
    
    
    
    
    }
    

}