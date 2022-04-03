
//���ڰ��к� 201918147 ���翵

//Futher Example 2-1    : ö�� �ڽ� ��� ���

//key�� ������ ����� LED�� ������ ������ LED�� �������� �Ѵ�. 
//Key�� ������ ���� ���ǿ����� ���� ���� ���¸� ����

#include<mega128.h>

typedef unsigned char BYTE;
typedef unsigned int WORD;

BYTE S_PORTD, S_PORTE;

void main(void)
{
    //PORT�ʱ�ȭ
    DDRD = 0x00;            //Key : PORTD : �Է� = 0
    PORTD = 0xf0;           //���� 4��Ʈ�� ���
    DDRE = 0xff;            //LED : PORTE : ��� = 1
    PORTE = 0xf0;           //KEY�� ������ �ʾ��� �� LED ��� ���� ����, LED�� 0�� �� ����
    
    while(1){
    
        S_PORTD = (PIND&0xf0);   // �ӽ� ���� ����, ���� 4��Ʈ�� �о ����
        S_PORTE = (PORTE&0xf0);  // �ӽ� ���� ����, ���ۿ� ��� ���� ���� 4��Ʈ�� MASKó�� 
        
        if(S_PORTD != S_PORTE){
            //ö�� �ڽ� : Ű�� ������ �� 0, LED 0�� �� ����
            if(S_PORTD == ~0x10) PORTE = ~0xE0;   //K : (0001 0000)'  L : (1110 0000)' 
            if(S_PORTD == ~0x20) PORTE = ~0xD0;   //K : (0010 0000)'  L : (1101 0000)'
            if(S_PORTD == ~0x40) PORTE = ~0xB0;   //K : (0100 0000)'  L : (1011 0000)'
            if(S_PORTD == ~0x80) PORTE = ~0x70;   //K : (1000 0000)'  L : (0111 0000)'
            
            }
                                 
    }
    
}