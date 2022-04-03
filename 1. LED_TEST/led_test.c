
//전자공학부 201918147 송재영
//LED 0000 0011 1100 1111 반복 점멸 코드
//플라스틱 박스 장비 ATmega128 사용  

#include <mega128.h>
#include <delay.h>


//예제 코드 변형 
//typedef  unsigned char  BYTE;
//typedef  unsigned int   WORD;
//BYTE MAIN_COUNT = 0; 

void main(void)
{

    DDRE = 0xff; //PORTE의 방향을 출력으로 함.    
        
    while(1)
    {
    PORTE = 0x00;      //0000 0000
    delay_ms(500); 
    PORTE = 0x30;      //0011 0000
    delay_ms(500);
    PORTE = 0xC0;      //1100 0000
    delay_ms(500);
    PORTE = 0xF0;      //1111 0000 
    delay_ms(500);
    }
}
