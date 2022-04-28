
//Futher Example 2-2    : 철제 박스 장비 사용

//Key를 누르면 연결된 LED가 아래 표에 약속된 방법으로 2개씩 켜진다
//Key 4    LED 5,6 
//Key 5    LED 6,7 
//Key 6    LED 7,4 
//Key 7    LED 4,5


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
    PORTE = 0xf0;           //KEY를 누르지 않았을 때 모두 꺼진 상태
    
    while(1){
    
        S_PORTD = (PIND&0xf0);   // 임시 버퍼 생성, 상위 4비트를 읽어서 저장
        S_PORTE = (PORTE&0xf0);  // 임시 버퍼 생성, 동작에 상관 없는 하위 4비트는 MASK처리 
        
        if(S_PORTD != S_PORTE){
            //철제 박스 : 키가 눌렸을 때 0, LED 0일 때 점등
            if(S_PORTD == ~0x10) PORTE = ~0x60;   //K : (0001 0000)'  L : (0110 0000)' 
            if(S_PORTD == ~0x20) PORTE = ~0xC0;   //K : (0010 0000)'  L : (1100 0000)'
            if(S_PORTD == ~0x40) PORTE = ~0x90;   //K : (0100 0000)'  L : (1001 0000)'
            if(S_PORTD == ~0x80) PORTE = ~0x30;   //K : (1000 0000)'  L : (0011 0000)'
            
            }
                                 
    }
    
}
