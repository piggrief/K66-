#include "include.h"
#define TSL1401_SIPin  PTB, 5
#define TSL1401_CLKPin PTB, 2
#define TSL1401_SI(x)   GPIO_Ctrl(TSL1401_SIPin, x)
#define TSL1401_CLK(x)  GPIO_Ctrl(TSL1401_CLKPin, x)
#define TSL1401_ADC ADC0_SE13

#define PRINT_AD        1       //���ô��ڴ�ӡ�������ͣ�0:��ӡ��ֵ�����ݣ�1����ӡADֵ
#define THRESHOLD       100     //���ö�ֵ����ֵ
#define WINDOW_WIDTH    128     //���ô��ڴ�ӡ�����ظ��������128����С0

void TSL1401_Init()
{
    GPIO_Init(TSL1401_SIPin, GPO, 0);
    GPIO_Init(TSL1401_CLKPin, GPO, 0);
    ADC_Init(TSL1401_ADC);
}

/*
* ��ʱ��΢��
*/
void TSL1401delay()
{
    unsigned int i;
    for (i = 0; i<10; i++)
    {
        asm("nop");
    }
}

void TSL1401_GetLine(uint8 *pixel)
{
    uint8 i;

    //��ʼSI
    TSL1401_SI(0);
    TSL1401_CLK(0);
    TSL1401delay();
    TSL1401_SI(1);
    TSL1401delay();
    TSL1401_CLK(1);
    TSL1401delay();
    TSL1401_SI(0);
    TSL1401delay();
    //�ɼ���1����
    pixel[0] = ADC_Once(ADC_0, TSL1401_ADC, ADC_8bit);
    TSL1401_CLK(0);

    //�ɼ���2~128����
    for (i = 1; i<128; i++)
    {
        TSL1401delay();
        TSL1401_CLK(1);
        TSL1401delay();
        pixel[i] = ADC_Once(ADC_0, TSL1401_ADC, ADC_8bit);
        TSL1401_CLK(0);
    }

    //���͵�129��clk
    TSL1401delay();
    TSL1401_CLK(1);
    TSL1401delay();
    TSL1401_CLK(0);
    TSL1401delay();

}
void TSL1401_SendLine(uint8 *LineImage)
{
    for (int i = (64 - WINDOW_WIDTH / 2); i<(64 + WINDOW_WIDTH / 2); i++)
    {
        if (LineImage[i] == 0xFF)
            LineImage[i] = 0xFE; //����FF��FE�滻����

        UART_Put_Char(TSL1401_DebugSerials, LineImage[i]);
    }
    UART_Put_Char(TSL1401_DebugSerials, 0xFF);  //���ֽ���������CCD��������ʶ����
}

void LCD_ShowOneLineImage(uint8 * image)
{
    uint8 pixbuff = 0;
    for (int i = 0; i < 128; i++)
    {
        pixbuff = image[i] * 63 / 255;
        LCD_PutPixel(i, 63-pixbuff);
    }
}

/*����CCDͼ������*/
# define Binary_GateValue 150
# define RoadBlockCheckGateValue 25
int Black_Count = 0;
int White_Count = 0;
int CheckRoadBlock(uint8 * image)
{
    Black_Count = 0;
    White_Count = 0;
    for (int i = 0; i < 128; i++)
    {
        if (image[i] >= Binary_GateValue)
        {
            White_Count++;
        }
        else
        {
            Black_Count++;
        }
    }
    LCD_PrintInt3(0, 5, White_Count);
    LCD_PrintInt3(0, 6, Black_Count);
    if (White_Count <= 25)
    {
        GPIO_Ctrl(BeepIOPortType, BeepIOPortIndex, 0);
    }
    else
    {
        GPIO_Ctrl(BeepIOPortType, BeepIOPortIndex, 1);
    }
    if (White_Count < RoadBlockCheckGateValue)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/*����CCDͼ������_����*/
# define ChangeGateValue 35
uint8 flag_leftline = 0;
uint8 flag_rightline = 0;
uint8 leftline = 0;
uint8 rightline = 0;

void lookline(uint8 * image)
{
    flag_rightline = 0;
    flag_leftline = 0;
    /*��ɨ*/
    for (int i = 64; i < 128 - 3; i++)
    {
        if ((image[i] - image[i + 3]) > ChangeGateValue)
        {
            flag_rightline = 1;
            rightline = i + 1;
            break;
        }
    }
    for (int i = 64; i >= 0+3; i--)
    {
        if ((image[i] - image[i - 3]) > ChangeGateValue)
        {
            flag_leftline = 1;
            leftline = i + 1;
            break;
        }
    }
}
float midline = 0;
float lastmidline = 0;
float CalPiancha()
{
    float errorbuff = 0;
    lastmidline = midline;
    if (flag_leftline && flag_rightline)
    {
        midline = 0.5*(leftline + rightline);
        errorbuff = midline - 64;
    }
    else if (flag_leftline)
    {
        midline = leftline + 20;
        errorbuff = 1.5*(midline - 64);
    }
    else if (flag_rightline)
    {
        midline = rightline - 20;
        errorbuff = 1.5*(midline - 64);
    }
    else//ȫ����
    {
        midline = lastmidline;
        errorbuff = 1.5*(midline - 64);
    }

    return errorbuff;
}