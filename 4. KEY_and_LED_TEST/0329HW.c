// 철제박스 장비




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
// 10msec 마다 Interrupt 발생 
TCNT0 = 99;     //10msec 인터럽트 시간 조절 count
TIMER_COUNT++;  //Interrupt 발생 Count 

    if (LED_SET_TIME == 0 ) LED_SET_TIME = 1; // LED TIMER가 1보다 작을면 0xff이다 
    
    if (LED_SET_TIME == TIMER_COUNT){        //LED_SET_TIME 보다 크면 
        TIMER_COUNT = 0;                     //Interruput Count 초기화
        INT_FLAG = 1;                        //LED ON 인터럽트 발생 플래크 
    }
} 
/****************************************
 KEY CHECK FUCTION
Returns : 0 - Non key_press
          1 - key_press
*****************************************/
BYTE key_check(){
 
char key_flag = 0;

    KEY_CURRENT = (PIND&0xf0);                  //PIND의 하위 4bit 사용하지 않기 위한 mask 
    
    if (KEY_CURRENT != 0xf0) key_flag = 1;      //만약 Key가 눌리면 
    
    if ((key_flag)&&(KEY_CURRENT != KEY_OLD)){  //만약 키가 눌리고, 키 값이 바꿨으면 
        KEY_OLD = KEY_CURRENT;                  //이전 키 값에 현재 키값 저장 
         return (1);                            // 키 값이 변경 되었음 
    }
    else if (!key_flag){                        //키가 눌리지 않았으면, 
         KEY_OLD = 0;                           // 키 값이 변경되지 않았음. 
         return (0);
    }    
    else return (0);                            //키가 눌리지 않았음. 

} 
/****************************************
 LED TOGGLE ON Direction
Parameters : 0 - SHIFT RIGHT
             1 - SHIFT LEFT
*****************************************/
void led_shift(char dir){
//4번째 비트부터 7번째 비트까지 증가 시켜야 하므로 MAIN_COUNT에 +3을 증가 시킨 후  오른쪽으로 1씩 shift
    if (!dir){
          //PORTE = ~(1<<(COUNT+3));
                      switch (COUNT){            //COUNT 값에 따라서 LED 점등이 달라짐
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
            switch (COUNT){                      //COUNT 값에 따라서 LED 점등이 달라짐
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
    TCNT0 = 99;     //10msec 인터럽트 시간 조절 count
    TIMSK = 0x01;   //Timer0_overflow Interrupt Enable
    
    DDRE = 0xff;    //PORTE의 방향을 출력으로 함.
    PORTE = 0xff;   //PORTE 초기 레벨을 '1' 상태로 만듬. 
    
    DDRD = 0x00;    //PORTD의 방향을 입력으로 함.
    PORTD = 0xff;   //PORTD의 초기 레벨을 '1' 상태로 만듬. 

    SREG = 0x80;    //Global Interrupt Enable

while (1)
      {
        MAIN_COUNT++;     //COUNT 1씩 증가 
        if(INT_FLAG){  //설정 시간 보다 
            INT_FLAG = 0;  //Interrupt Flag를 Clear
            COUNT++;       //LED Count 증가 
            led_shift(LED_DIR);
            //shift 된 값이 7을 초과 하지 말아야 하므로 '0'으로 초기화 한다.
            if (COUNT>=4) COUNT = 0;
        } 
        if (key_check()){                   // 키가  눌렸다면, 
            switch (PIND&0xf0){             // 키가 어떻 값이 누렸는가? 
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
