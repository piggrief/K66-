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
extern float everage_piancha;
extern uint8 Left_Flag[ROW];
extern uint8 found_flag;
extern int time;
extern float temp_piancha;
extern uint8 light_flag;
extern uint8 light_delay_flag;
extern uint8 find_loop_flag;

float Data_Test[21] = { 0 };
float Weight_FIR1[21] = { 0, -0.0007, -0.0015, 0.0006, 0.0092, 0.0269, 0.0534, 0.0852, 0.1158, 0.1380, 0.1461
, 0.1380, 0.1158, 0.0852, 0.0534, 0.0269, 0.0092, 0.0006, -0.0015, -0.0007, 0 };
int32 ttt = 0;

extern int time;
extern uint32 SpeedCount[4];

void Init_All();

void main(void)
{
    Init_All();
    PID_init(160, 0, 1, 9000, 9500, 0);//80, 0, 0.1, 100000, 9500, 0

	while (1)
	{
        if (ImageDealState_Now == Image_CollectFinish)
        {
            ImageDealState_Now = Image_Dealing;
            LED_Ctrl(LED3, ON);      //LEDָʾ��������״̬  
            
	        //MedianFilter();
	        displayimage032(image[0], ThreasHold);
            //OLED_ShowImage(128, 64, 120, 188, ThreasHold, image);
	        Reset();
	        find_light();
	        mid_findlight();
	        find_loop();
                                          
            //seekfree_sendimg_032();                         
            ImageDealState_Now = Image_DealingFinsh;
        }
        else
            LED_Ctrl(LED3, OFF);      //LEDָʾ��������״̬  
        LCD_PrintFloat_31(0,0,everage_piancha);


	}
}

void Init_All()
{
    DisableInterrupts;           //�ر��ж�
    PLL_Init(PLL200);            //��ʼ��PLLΪ200M,����Ϊ40M  

    /*******************GPIO***************************/
    LED_Init();                  //LED��ʼ��    
    TFT_init(SPI_1, SPIn_PCS0);
    LCD_Init();
    ButtonMenu();
    UART_Init(UART_3, 115200);
    
    EncoderMeasure_Init();
    RemoteInit();

    FTM_PWM_Init(FTMType_Use1, FTMChannel_Use_W1_1, 100000, 0);
    FTM_PWM_Init(FTMType_Use1, FTMChannel_Use_W1_2, 100000, 0);
    FTM_PWM_Init(FTMType_Use2, FTMChannel_Use_W2_1, 100000, 0);
    FTM_PWM_Init(FTMType_Use2, FTMChannel_Use_W2_2, 100000, 0);
    FTM_PWM_Init(FTMType_Use3, FTMChannel_Use_W3_1, 100000, 0);
    FTM_PWM_Init(FTMType_Use3, FTMChannel_Use_W3_2, 100000, 0);
    FTM_PWM_Init(FTMType_Use4, FTMChannel_Use_W4_1, 100000, 0);
    FTM_PWM_Init(FTMType_Use4, FTMChannel_Use_W4_2, 100000, 0);

    PIT_Init(PIT0, 8);
    EnableInterrupts;

    TFT_showstr(0, 0, "Initing!", BLACK, WHITE);
    camera_init();
    TFT_showstr(0, 0, "Success!", BLACK, WHITE);

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            image[i][j] = 0xff;
        }
    }


}

extern uint32 Speed_get[4];
void PIT0_Interrupt()
{
    SpeedClean();
    int i = 0;
    //count_1ms++;
    //if (count_1ms >= 500)
    //{
    //	count_1ms = 0;
    //	Count++;
    //	TFT_showint16(0, 0, Count, BLACK, WHITE);
    //	TFT_showstr(0, 20, "S", BLACK, WHITE);
    //}
    for (i = 0; i < 4; i++)
    {
        GetSpeed(i);
        Speed_get[i] = SpeedCount[i];
    }
    SEND(Speed_get[0], Speed_get[1], Speed_get[2], Speed_get[3]);
        SetSpeed_FromRemote(RunMode);

    PIT_Flag_Clear(PIT0);       //???D??�I��????


}
uint32 TimeCount_test = 0;
void PIT1_Interrupt()
{
	PIT_Flag_Clear(PIT1);       //���жϱ�־λ
   /*�û�����������*/
	TimeCount_test++;
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