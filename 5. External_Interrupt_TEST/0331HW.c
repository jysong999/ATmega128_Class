// ���ڰ��к� 201918147 ���翵
// ö���ڽ� ���






#include <mega128.h>
#include <delay.h>


typedef  unsigned char  BYTE;
typedef  unsigned int   WORD;


BYTE COUNT = 0;
BYTE Left_Shift = 0;


interrupt [EXT_INT0] void ext_int0_isr (void)
{
   Left_Shift++;
    }    
   
   
    
    
void main(void)
{
    
    DDRE = 0xff;  //PORTE�� ������ ������� ��.
    PORTE = 0xff; //PORTE �ʱ� ������ '1' ���·� ����.   
    
    EIMSK = 0x01;     //external inturrupt int0 enable ���·�
    EICRA = 0x02;    // falling edge
    
    SREG = 0x80;  //Global Interrupt Enable
             
    
    
while (1) 
    {
        if(Left_Shift < 3)
        {
             COUNT++;       //LED Count ����
             PORTE = ~(1<<(COUNT+3));
             delay_ms(500);
             if (COUNT>=4) COUNT = 0;
        }            
            
            
        else if(Left_Shift == 3)
        {
            COUNT++;
            PORTE = ~(1<<(8-COUNT));
            delay_ms(500); 
            if (COUNT>=4) COUNT = 0;
        }     
                
                
        else if(Left_Shift > 3)
        {
            Left_Shift=0;
        }   
    }
}