#include <mega128.h>
#include <delay.h>


typedef  unsigned char  BYTE;
typedef  unsigned int   WORD;

BYTE MAIN_COUNT = 0; 

void main(void)
{

    DDRE = 0xff; //PORTE의 방향을 출력으로 함.    
        
    while(1)
    {
    PORTE = 0x00;      //0000 0000
    delay_ms(500); 
    PORTE = 0x0C;       //0000 1100
    delay_ms(500);
    PORTE = 0x03;      //0000 0011
    delay_ms(500);
    PORTE = 0x0F;      //0000 1111 
    delay_ms(500);
    }
}
