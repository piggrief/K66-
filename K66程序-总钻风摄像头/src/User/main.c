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

//������
int count_1ms = 0;
extern int16 GET_CFG[9 - 1][2];
extern uint8 image[120][188];

void main(void) 
{   
    int i = 0, j = 0;
   DisableInterrupts;           //�ر��ж�
   PLL_Init(PLL200);            //��ʼ��PLLΪ200M,����Ϊ40M  
//     GPIO_Init(PTC,8,GPI,1);
//     GPIO_Init(PTC,9,GPI,1);
//     GPIO_Init(PTC,10,GPI,1);
//     GPIO_Init(PTC,11,GPI,1);
//     GPIO_Init(PTC,12,GPI,1);
//     GPIO_Init(PTC,13,GPI,1);
//     GPIO_Init(PTC,14,GPI,1);
//     GPIO_Init(PTC,15,GPI,1);
//     
   //PIT_Init(PIT0, 1);
   /*******************GPIO***************************/
   LED_Init();                  //LED��ʼ��    
   TFT_init(SPI_1, SPIn_PCS0);
   //MT9V032_Init();

   //FTM_PWM_Init(FTM0, FTM_CH0, 65535, 0);
   //FTM_PWM_Init(FTM0, FTM_CH1, 65535, 0);
   //FTM_PWM_Init(FTM0, FTM_CH2, 65535, 0);
   //FTM_PWM_Init(FTM0, FTM_CH3, 65535, 0);

   //EnableInterrupts;
   //dsp_single_colour(RED);
   ////UART_Put_Str(UART_3, "33333333\n");

   //LPTMR_delay_ms(5000);


   //FTM_PWM_Duty(FTM0, FTM_CH0, 0);
   //FTM_PWM_Duty(FTM0, FTM_CH1, 58000);//58000
   //FTM_PWM_Duty(FTM0, FTM_CH2, 0);
   //FTM_PWM_Duty(FTM0, FTM_CH3, 58000);

   //LPTMR_delay_ms(2000);
   EnableInterrupts;
   TFT_showstr(0, 0, "Test!", BLACK, WHITE);
   camera_init();

   TFT_showstr(1, 0, "Success!", BLACK, WHITE);

   for (i = 0; i < 120; i++)
   {
       for (j = 0; j < 188; j++)
       {
           image[i][j] = 0xff;
       }
   }
   while (1)
   {
       if (ImageDealState_Now == Image_CollectFinish)
       {
           ImageDealState_Now = Image_Dealing;
           LED_Ctrl(LED3, ON);      //LEDָʾ��������״̬  

           displayimage032(image[0]);

           ImageDealState_Now = Image_DealingFinsh;
       }
       else
           LED_Ctrl(LED3, OFF);      //LEDָʾ��������״̬  

	   //FTM_PWM_Duty(FTM0, FTM_CH0, 0);
	   //FTM_PWM_Duty(FTM0, FTM_CH1, 0);
	   //FTM_PWM_Duty(FTM0, FTM_CH2, 0);
	   //FTM_PWM_Duty(FTM0, FTM_CH3, 0);

	  //dsp_single_colour(RED);

   }
}
int Count = 0;
void PIT0_Interrupt()
{
	count_1ms++;
	if (count_1ms >= 500)
	{
		count_1ms = 0;
		Count++;
		TFT_showint16(0, 0, Count, BLACK, WHITE);
		TFT_showstr(0, 20, "S", BLACK, WHITE);
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