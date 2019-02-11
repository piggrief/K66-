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

uint8   uart_receive_flag = 1;
uint8   receive[3];
uint8   receive_num = 0;
#define MT9V032_COF_UART    UART_3  //��������ͷ��ʹ�õ��Ĵ���     

void MT9V032_Config_interrupt()
{
	receive[receive_num] = UART_Get_Char(MT9V032_COF_UART);;
	receive_num++;

	if (1 == receive_num && 0XA5 != receive[0])  receive_num = 0;
	if (3 == receive_num)
	{
		receive_num = 0;
		uart_receive_flag = 1;
	}

}
#define COL     188//ͼ����   ��Χ1-752     K60�ɼ���������188
#define ROW     120//ͼ��߶�	��Χ1-480

//����ͷ����ö��
typedef enum
{
	INIT = 0,               //����ͷ��ʼ������
	AUTO_EXP,               //�Զ��ع�����
	EXP_TIME,               //�ع�ʱ������
	FPS,                    //����ͷ֡������
	SET_COL,                //ͼ��������
	SET_ROW,                //ͼ��������
	LR_OFFSET,              //ͼ������ƫ������
	UD_OFFSET,              //ͼ������ƫ������
	GAIN,                   //ͼ��ƫ������
	CONFIG_FINISH,          //������λ����Ҫ����ռλ����

	SET_EXP_TIME = 0XF0,    //���������ع�ʱ������
	GET_STATUS,             //��ȡ����ͷ��������
	GET_VERSION,            //�̼��汾������

	SET_ADDR = 0XFE,        //�Ĵ�����ַ����
	SET_DATA                //�Ĵ�����������
}CMD;

//��Ҫ���õ�����ͷ������
int16 MT9V032_CFG[CONFIG_FINISH][2] =
{
	{ AUTO_EXP, 0 },   //�Զ��ع�����      ��Χ1-63 0Ϊ�ر� ����Զ��ع⿪��  EXP_TIME�������õ����ݽ����Ϊ����ع�ʱ�䣬Ҳ�����Զ��ع�ʱ�������
	//һ������ǲ���Ҫ����������ܣ���Ϊ�������ع���һ�㶼�ȽϾ��ȣ�����������߷ǳ������ȵ�������Գ������ø�ֵ������ͼ���ȶ���
	{ EXP_TIME, 300 }, //�ع�ʱ��          ����ͷ�յ�����Զ����������ع�ʱ�䣬������ù���������Ϊ�������������ع�ֵ
	{ FPS, 50 },  //ͼ��֡��          ����ͷ�յ�����Զ���������FPS���������������Ϊ������������FPS
	{ SET_COL, COL }, //ͼ��������        ��Χ1-752     K60�ɼ���������188
	{ SET_ROW, ROW }, //ͼ��������        ��Χ1-480
	{ LR_OFFSET, 0 },   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ188 376 752ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
	{ UD_OFFSET, 0 },   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ120 240 480ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
	{ GAIN, 32 },  //ͼ������          ��Χ16-64     ����������ع�ʱ��̶�������¸ı�ͼ�������̶�


	{ INIT, 0 }    //����ͷ��ʼ��ʼ��
};

//������ͷ�ڲ���ȡ������������
int16 GET_CFG[CONFIG_FINISH - 1][2] =
{
	{ AUTO_EXP, 0 },   //�Զ��ع�����      
	{ EXP_TIME, 0 },   //�ع�ʱ��          
	{ FPS, 0 },   //ͼ��֡��          
	{ SET_COL, 0 },   //ͼ��������        
	{ SET_ROW, 0 },   //ͼ��������        
	{ LR_OFFSET, 0 },   //ͼ������ƫ����    
	{ UD_OFFSET, 0 },   //ͼ������ƫ����    
	{ GAIN, 0 },   //ͼ������          
};
uint16 MT9V032_temp;
uint8  send_buffer[4];

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ����ͷ�ڲ�������Ϣ
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				���øú���ǰ���ȳ�ʼ��uart3
//-------------------------------------------------------------------------------------------------------------------
void get_config(void)
{
	uint16 temp, i;
	uint8  send_buffer[4];

	for (i = 0; i<CONFIG_FINISH - 1; i++)
	{
		send_buffer[0] = 0xA5;
		send_buffer[1] = GET_STATUS;
		temp = GET_CFG[i][0];
		send_buffer[2] = temp >> 8;
		send_buffer[3] = (uint8)temp;

		UART_Put_Str(MT9V032_COF_UART, send_buffer);

		//�ȴ����ܻش�����
		while (!uart_receive_flag);
		uart_receive_flag = 0;

		GET_CFG[i][1] = receive[1] << 8 | receive[2];

	}
}
void MT9V032_Init()
{
	int i = 0;
	UART_Init(UART_3, 9600);
	UART_Irq_En(UART_3);

	LPTMR_delay_ms(1000);
	uart_receive_flag = 0;

	////��ʼ��������ͷ�����³�ʼ��
	//for (i = 0; i<CONFIG_FINISH; i++)
	//{
	//	send_buffer[0] = 0xA5;
	//	send_buffer[1] = MT9V032_CFG[i][0];
	//	MT9V032_temp = MT9V032_CFG[i][1];
	//	send_buffer[2] = MT9V032_temp >> 8;
	//	send_buffer[3] = (uint8)MT9V032_temp;
	//	UART_Put_Str(MT9V032_COF_UART, send_buffer);
	//	LPTMR_delay_ms(2);
	//}
	////�ȴ�����ͷ��ʼ���ɹ�
	//while (!uart_receive_flag);
	//uart_receive_flag = 0;
	//while ((0xff != receive[1]) || (0xff != receive[2]));
	////���ϲ��ֶ�����ͷ���õ�����ȫ�����ᱣ��������ͷ��51��Ƭ����eeprom��
	////����set_exposure_time�����������õ��ع����ݲ��洢��eeprom��
	get_config();
}

//������
int count_1ms = 0;
void main(void) 
{   
   DisableInterrupts;           //�ر��ж�
   PLL_Init(PLL180);            //��ʼ��PLLΪ200M,����Ϊ40M  
   //PIT_Init(PIT0, 1);
   /*******************GPIO***************************/
   //LED_Init();                  //LED��ʼ��    
   TFT_init(SPI_1, SPIn_PCS0);
   //MT9V032_Init();

   FTM_PWM_Init(FTM0, FTM_CH0, 65535, 0);
   FTM_PWM_Init(FTM0, FTM_CH1, 65535, 0);
   FTM_PWM_Init(FTM0, FTM_CH2, 65535, 0);
   FTM_PWM_Init(FTM0, FTM_CH3, 65535, 0);

   EnableInterrupts;
   dsp_single_colour(RED);
   //UART_Put_Str(UART_3, "33333333\n");

   LPTMR_delay_ms(5000);


   FTM_PWM_Duty(FTM0, FTM_CH0, 0);
   FTM_PWM_Duty(FTM0, FTM_CH1, 58000);//58000
   FTM_PWM_Duty(FTM0, FTM_CH2, 0);
   FTM_PWM_Duty(FTM0, FTM_CH3, 58000);

   LPTMR_delay_ms(2000);

   while(1)
   {
	   FTM_PWM_Duty(FTM0, FTM_CH0, 0);
	   FTM_PWM_Duty(FTM0, FTM_CH1, 0);
	   FTM_PWM_Duty(FTM0, FTM_CH2, 0);
	   FTM_PWM_Duty(FTM0, FTM_CH3, 0);

	  //dsp_single_colour(RED);

      //LED_Ctrl(LED3, RVS);      //LEDָʾ��������״̬  
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