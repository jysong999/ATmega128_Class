
//���ڰ��к� 201918147 ���翵
//LED 0000 0011 1100 1111 �ݺ� ���� �ڵ�
//�ö�ƽ �ڽ� ��� ATmega128 ���  

#include <mega128.h>
#include <delay.h>


//���� �ڵ� ���� 
//typedef  unsigned char  BYTE;
//typedef  unsigned int   WORD;
//BYTE MAIN_COUNT = 0; 

void main(void)
{

    DDRE = 0xff; //PORTE�� ������ ������� ��.    
        
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
