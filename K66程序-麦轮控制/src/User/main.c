/****************************************************************************************************
��ƽ    ̨�������������ܿƼ�MK66FX1M0VLQ18���İ�
����    д��CHIUSIR
��E-mail  ��chiusir@aliyun.com
������汾��V1.0
�������¡�2016��08��24��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.3
��Target  ��K66FX1M0VLQ18
��Crystal �� 50.000Mhz
��busclock�� 40.000MHz
��pllclock��200.000MHz
=============================================================
LPTMR��ʱ������ʾ��1S�Ӱ���LED(PTE26)��˸
=============================================================
�޸���ʷ��
******************************************************************************************************/



#include "include.h" 
extern uint32 SpeedCount[4];

//������
int count_1ms = 0;
void main(void) 
{   
   DisableInterrupts;           //�ر��ж�
   PLL_Init(PLL200);            //��ʼ��PLLΪ200M,����Ϊ40M  
   PIT_Init(PIT0, 5);
   /*******************GPIO***************************/
   //LED_Init();                  //LED��ʼ��    
   LCD_Init();
   TFT_init(SPI_1, SPIn_PCS0);
   //MT9V032_Init();

   EncoderMeasure_Init();

   FTM_PWM_Init(FTM0, FTM_CH0, 65535, 0);
   FTM_PWM_Init(FTM0, FTM_CH1, 65535, 0);
   FTM_PWM_Init(FTM0, FTM_CH2, 65535, 0);
   FTM_PWM_Init(FTM0, FTM_CH3, 65535, 0);
   FTM_PWM_Init(FTM0, FTM_CH4, 65535, 0);
   FTM_PWM_Init(FTM0, FTM_CH5, 65535, 0);
   FTM_PWM_Init(FTM0, FTM_CH6, 65535, 0);
   FTM_PWM_Init(FTM0, FTM_CH7, 65535, 0);
   
   EnableInterrupts;
   //dsp_single_colour(RED);
   //UART_Put_Str(UART_3, "33333333\n");
   UART_Init(UART_3, 115200);
   //LPTMR_delay_ms(5000);

   //FTM_PWM_Duty(FTM0, FTM_CH0, 58000);
   //FTM_PWM_Duty(FTM0, FTM_CH1, 0);//58000
   //FTM_PWM_Duty(FTM0, FTM_CH2, 58000);
   //FTM_PWM_Duty(FTM0, FTM_CH3, 0);
   //FTM_PWM_Duty(FTM0, FTM_CH4, 0);
   //FTM_PWM_Duty(FTM0, FTM_CH5, 58000);//58000
   //FTM_PWM_Duty(FTM0, FTM_CH6, 0);
   //FTM_PWM_Duty(FTM0, FTM_CH7, 58000);

   //LPTMR_delay_ms(2000);

   while(1)
   {
       LCD_PrintInt5(0, 0, SpeedCount[0]);
       //LCD_PrintInt4(0, 1, -321);
       //LCD_PrintFloat_31(0, 2, 231.23);
	   FTM_PWM_Duty(FTM0, FTM_CH0, 0);
	   FTM_PWM_Duty(FTM0, FTM_CH1, 0);
	   FTM_PWM_Duty(FTM0, FTM_CH2, 0);
	   FTM_PWM_Duty(FTM0, FTM_CH3, 0);
	   FTM_PWM_Duty(FTM0, FTM_CH4, 0);
	   FTM_PWM_Duty(FTM0, FTM_CH5, 0);
	   FTM_PWM_Duty(FTM0, FTM_CH6, 0);
	   FTM_PWM_Duty(FTM0, FTM_CH7, 0);
	  //dsp_single_colour(RED);
       //UART_Put_Buff(UART_3, "Hello!", 6);
       //LPTMR_delay_ms(500);
      //LED_Ctrl(LED3, RVS);      //LEDָʾ��������״̬  
   }
}

void PIT0_Interrupt()
{
    int i = 0;
	//count_1ms++;
	//if (count_1ms >= 500)
	//{
	//	count_1ms = 0;
	//	Count++;
	//	TFT_showint16(0, 0, Count, BLACK, WHITE);
	//	TFT_showstr(0, 20, "S", BLACK, WHITE);
	//}
    for (i = 1; i < 5; i++)
    {
        GetSpeed(i);
    }

  PIT_Flag_Clear(PIT0);       //���жϱ�־λ


}

void PIT1_Interrupt()
{
  PIT_Flag_Clear(PIT1);       //���жϱ�־λ
 /*�û�����������*/
}

void PIT2_Interrupt()
{
  PIT_Flag_Clear(PIT2);       //���жϱ�־λ
  /*�û�����������*/
}

void PIT3_Interrupt()
{
  PIT_Flag_Clear(PIT3);       //���жϱ�־λ
  /*�û�����������*/
}