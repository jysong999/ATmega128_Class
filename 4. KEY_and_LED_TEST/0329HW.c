// ���ڰ��к� 201918147 ���翵
// ö���ڽ� ���




#include <mega128.h>
#include <delay.h>

typedef  unsigned char  BYTE;
typedef  unsigned int   WORD;  

#define SW4    0xE0 //LED DIRECTION = LEFT
#define SW5    0xD0 //LED DIRECTION = RIGHT
#define SW6    0xB0 //LED TOGGLE TIME = INCREASE
#define SW7    0x70 //LED TOGGLE TIME = DECREASE

BYTE KEY_CURRENT, KEY_OLD;              //SAVE key_buffer
BYTE MAIN_COUNT = 0,COUNT = 0;          //main counter, LED Shift Counter
BYTE INT_FLAG = 0;                      //Timer0 0verflow Interrupt set flag
WORD TIMER_COUNT = 0, LED_SET_TIME=1;   //Timer0 10msec Timer Counter, LED Toggle Timer 
BYTE LED_DIR = 0;                       //LED Parameter Variable


interrupt [TIM0_OVF] void timer0_overflow(void) {
// 10msec ���� Interrupt �߻� 
TCNT0 = 99;     //10msec ���ͷ�Ʈ �ð� ���� count
TIMER_COUNT++;  //Interrupt �߻� Count 

    if (LED_SET_TIME == 0 ) LED_SET_TIME = 1; // LED TIMER�� 1���� ������ 0xff�̴� 
    
    if (LED_SET_TIME == TIMER_COUNT){        //LED_SET_TIME ���� ũ�� 
        TIMER_COUNT = 0;                     //Interruput Count �ʱ�ȭ
        INT_FLAG = 1;                        //LED ON ���ͷ�Ʈ �߻� �÷�ũ 
    }
} 
/****************************************
 KEY CHECK FUCTION
Returns : 0 - Non key_press
          1 - key_press
*****************************************/
BYTE key_check(){
 
char key_flag = 0;

    KEY_CURRENT = (PIND&0xf0);                  //PIND�� ���� 4bit ������� �ʱ� ���� mask 
    
    if (KEY_CURRENT != 0xf0) key_flag = 1;      //���� Key�� ������ 
    
    if ((key_flag)&&(KEY_CURRENT != KEY_OLD)){  //���� Ű�� ������, Ű ���� �ٲ����� 
        KEY_OLD = KEY_CURRENT;                  //���� Ű ���� ���� Ű�� ���� 
         return (1);                            // Ű ���� ���� �Ǿ��� 
    }
    else if (!key_flag){                        //Ű�� ������ �ʾ�����, 
         KEY_OLD = 0;                           // Ű ���� ������� �ʾ���. 
         return (0);
    }    
    else return (0);                            //Ű�� ������ �ʾ���. 

} 
/****************************************
 LED TOGGLE ON Direction
Parameters : 0 - SHIFT RIGHT
             1 - SHIFT LEFT
*****************************************/
void led_shift(char dir){
//4��° ��Ʈ���� 7��° ��Ʈ���� ���� ���Ѿ� �ϹǷ� MAIN_COUNT�� +3�� ���� ��Ų ��  ���������� 1�� shift
    if (!dir){
          //PORTE = ~(1<<(COUNT+3));
                      switch (COUNT){            //COUNT ���� ���� LED ������ �޶���
                case 0 : PORTE = 0x30;     
                            break;
                case 1 : PORTE = 0x60;
                            break;
                case 2 : PORTE = 0xc0;
                            break;
                case 3 : PORTE = 0x90;
                            break;
                case 4 : PORTE = 0x30;     
                            break; 
                            
                default : break;            

            }  
           
    }
    else {                   
            switch (COUNT){                      //COUNT ���� ���� LED ������ �޶���
                case 0 : PORTE = 0x30;     
                            break;
                case 1 : PORTE = 0x90;
                            break;
                case 2 : PORTE = 0xc0;
                            break;
                case 3 : PORTE = 0x60;
                            break;
                case 4 : PORTE = 0x30;     
                            break; 
                            
                default : break;            

            }
    }
}

void main(void)
{
    TCCR0 = 0x07;   //Clock Division /1024
    TCNT0 = 99;     //10msec ���ͷ�Ʈ �ð� ���� count
    TIMSK = 0x01;   //Timer0_overflow Interrupt Enable
    
    DDRE = 0xff;    //PORTE�� ������ ������� ��.
    PORTE = 0xff;   //PORTE �ʱ� ������ '1' ���·� ����. 
    
    DDRD = 0x00;    //PORTD�� ������ �Է����� ��.
    PORTD = 0xff;   //PORTD�� �ʱ� ������ '1' ���·� ����. 

    SREG = 0x80;    //Global Interrupt Enable

while (1)
      {
        MAIN_COUNT++;     //COUNT 1�� ���� 
        if(INT_FLAG){  //���� �ð� ���� 
            INT_FLAG = 0;  //Interrupt Flag�� Clear
            COUNT++;       //LED Count ���� 
            led_shift(LED_DIR);
            //shift �� ���� 7�� �ʰ� ���� ���ƾ� �ϹǷ� '0'���� �ʱ�ȭ �Ѵ�.
            if (COUNT>=4) COUNT = 0;
        } 
        if (key_check()){                   // Ű��  ���ȴٸ�, 
            switch (PIND&0xf0){             // Ű�� � ���� ���ȴ°�? 
                case SW4 : LED_DIR = 1;     
                            break;
                case SW5 : LED_DIR = 0;
                            break;
                case SW6 : LED_SET_TIME--,TIMER_COUNT=0;
                            break;
                case SW7 : LED_SET_TIME++,TIMER_COUNT=0;
                            break;
                default : break;            

            }
        }
      };
}
