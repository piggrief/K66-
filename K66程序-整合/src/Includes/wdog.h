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

#ifndef __WDOG_H__
#define __WDOG_H__

//-------------------------------------------------------------------------*
//������: wdog_disable                                                     *
//��  ��: �رտ��Ź�ģ��                                                   * 
//��  ��: ��							       *	
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
void wdog_disable(void);

//-------------------------------------------------------------------------*
//������: wdog_unlock                                                      *
//��  ��: ���Ź�����                                                       * 
//��  ��: ��					             	       *	
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
void wdog_unlock(void);
void wdog_enable(void);
void wdog_feed(void);
void wdog_init_ms(uint32 ms);
#endif 
