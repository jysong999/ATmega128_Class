
//Futher Example 2-1    : 플라스틱박스 장비 사용

//key를 누르면 연결된 LED를 제외한 나머지 LED가 켜지도록 한다. 
//Key를 누르지 않은 조건에서는 전부 꺼진 상태를 유지

#include<mega128.h>

typedef unsigned char BYTE;
typedef unsigned int WORD;

BYTE S_PORTD, S_PORTE;

void main(void)
{
    //PORT초기화
    DDRD = 0x00;            //Key : PORTD : 입력 = 0
    PORTD = 0xf0;           //상위 4비트만 사용
    DDRE = 0xff;            //LED : PORTE : 출력 = 1
    PORTE = 0x00;           //KEY를 누르지 않았을 때 모두 꺼진 상태
    
    while(1){
    
        S_PORTD = (PIND&0xf0);   // 임시 버퍼 생성, 상위 4비트를 읽어서 저장
        S_PORTE = (PORTE&0xf0);  // 임시 버퍼 생성, 동작에 상관 없는 하위 4비트는 MASK처리 
        
        if(S_PORTD != S_PORTE){
            
            if(S_PORTD == 0x10) PORTE = 0xE0;   //K : 0001 0000  L : 1110 0000 
            if(S_PORTD == 0x20) PORTE = 0xD0;   //K : 0010 0000  L : 1101 0000
            if(S_PORTD == 0x40) PORTE = 0xB0;   //K : 0100 0000  L : 1011 0000
            if(S_PORTD == 0x80) PORTE = 0x70;   //K : 1000 0000  L : 0111 0000
            
            }
                                 
    }
    
}
