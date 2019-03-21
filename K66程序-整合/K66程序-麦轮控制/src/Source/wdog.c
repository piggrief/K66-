/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�MK66FX1M0VLQ18���İ�
����    д��CHIUSIR
����    ע��
������汾��V1.0
�������¡�2016��08��20��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
���������䡿chiusir@163.com
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
#include "wdog.h"	//����wdog.hͷ�ļ�
       
//-------------------------------------------------------------------------*
//������: wdog_enable                                                      *
//��  ��: ���Ź�ʹ��                                                       * 
//��  ��: ��							           *	
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
void wdog_enable(void)
{
    wdog_unlock();                                  //�������Ź��������������ÿ��Ź�

    WDOG_STCTRLH |= WDOG_STCTRLH_WDOGEN_MASK;       //WDOGEN��λ��ʹ�� ���Ź�
}
//-------------------------------------------------------------------------*
//������: wdog_disable                                                     *
//��  ��: ���Ź��ر�                                                       * 
//��  ��: ��			  					   *	
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
void wdog_disable(void)
{
    //�����Ź�ģ��������Ա�д�Ĵ���
    wdog_unlock();
    //�رտ��Ź�
    WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;
}
//-------------------------------------------------------------------------*
//������: wdog_unlock                                                      *
//��  ��: ���Ź�ι��                                                       * 
//��  ��: ��							           *	
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
void wdog_feed(void)
{
    //�˺������ܵ���ִ��
    DisableInterrupts;

    //���Ź�ˢ�¼Ĵ���
    WDOG_REFRESH = 0xA602;
    WDOG_REFRESH = 0xB480;
    
    EnableInterrupts;
    
}
//-------------------------------------------------------------------------*
//������: wdog_unlock                                                      *
//��  ��: ���Ź�����                                                       * 
//��  ��: ��							           *	
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
void wdog_unlock(void)
{    
    //�����ж�
    DisableInterrupts;		
    //д�����Ĵ���
    WDOG_UNLOCK = 0xC520;//�˺������ܵ���ִ��
    //��ɽ���
    WDOG_UNLOCK = 0xD928;	
    //�����ж�
    EnableInterrupts;		
}

//-------------------------------------------------------------------------*
//������: wdog_unlock                                                      *
//��  ��: ���Ź�����                                                       * 
//��  ��: ��							           *	
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
void wdog_init_ms(uint32 ms)
{  

    wdog_unlock();                                  //�������Ź��������������ÿ��Ź�

    WDOG_PRESC = WDOG_PRESC_PRESCVAL(0);            //���÷�Ƶϵ�� = PRESCVAL +1(PRESCVALȡֵ��ΧΪ0~7)

    WDOG_TOVALH = ms >> 16;                         //����ι��ʱ��
    WDOG_TOVALL = (uint16)ms;

    WDOG_STCTRLH = ( 0
                    | WDOG_STCTRLH_WDOGEN_MASK     //WDOGEN��λ��ʹ�� ���Ź�
                    //| WDOG_STCTRLH_CLKSRC_MASK   //���Ź�ʱ��ѡ��0Ϊ LDO ��1Ϊbus ʱ�ӣ�
                    | WDOG_STCTRLH_ALLOWUPDATE_MASK
                    | WDOG_STCTRLH_STOPEN_MASK
                    | WDOG_STCTRLH_WAITEN_MASK
                    | WDOG_STCTRLH_STNDBYEN_MASK                    
                    );
}