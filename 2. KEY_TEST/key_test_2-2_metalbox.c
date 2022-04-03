
//���ڰ��к� 201918147 ���翵

//Futher Example 2-2    : ö�� �ڽ� ��� ���

//Key�� ������ ����� LED�� �Ʒ� ǥ�� ��ӵ� ������� 2���� ������
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
    //PORT�ʱ�ȭ
    DDRD = 0x00;            //Key : PORTD : �Է� = 0
    PORTD = 0xf0;           //���� 4��Ʈ�� ���
    DDRE = 0xff;            //LED : PORTE : ��� = 1
    PORTE = 0xf0;           //KEY�� ������ �ʾ��� �� ��� ���� ����
    
    while(1){
    
        S_PORTD = (PIND&0xf0);   // �ӽ� ���� ����, ���� 4��Ʈ�� �о ����
        S_PORTE = (PORTE&0xf0);  // �ӽ� ���� ����, ���ۿ� ��� ���� ���� 4��Ʈ�� MASKó�� 
        
        if(S_PORTD != S_PORTE){
            //ö�� �ڽ� : Ű�� ������ �� 0, LED 0�� �� ����
            if(S_PORTD == ~0x10) PORTE = ~0x60;   //K : (0001 0000)'  L : (0110 0000)' 
            if(S_PORTD == ~0x20) PORTE = ~0xC0;   //K : (0010 0000)'  L : (1100 0000)'
            if(S_PORTD == ~0x40) PORTE = ~0x90;   //K : (0100 0000)'  L : (1001 0000)'
            if(S_PORTD == ~0x80) PORTE = ~0x30;   //K : (1000 0000)'  L : (0011 0000)'
            
            }
                                 
    }
    
}