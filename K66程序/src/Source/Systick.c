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

void SysTick_delay(u32 tm)
{
   SysTick->LOAD |=tm;
   SysTick->VAL  |=0;
   SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk
                   |SysTick_CTRL_CLKSOURCE_Msk;
   while( !(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk) );
}
void SysTick_delay_ms(uint32 ms)
{
    while(ms--)
    {
        SysTick_delay(core_clk_M*1000);
    }
}
void SysTick_delay_us(u32 tm)//��׼��ʱ1us
{
  tm=(u32)(tm*core_clk_M);
  SysTick_delay(tm);
}
