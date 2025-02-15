/*!
* @file       DebugFuction.c
* @brief      用于调试用的函数库
* @details
* @author     pig's grief
* @version    v1.0
* @date       2019-2-26
* @to do
*             
*/
# include "include.h"
/*************************************************************/
/*****************虚拟示波器部分************/
/*************************************************************/
float OutData[4] = { 0 };//程序会将数组中的四个数发送给虚拟示波器
//float temp = 0.0;
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

void OutPut_Data(void)
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0;
  for(i=0;i<4;i++)
   {
    temp[i]  = (int)OutData[i];
    temp1[i] = (unsigned int)temp[i];
    
   }
   
  for(i=0;i<4;i++) 
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
  }
  
  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;
  
  UART_Put_Buff(CRC_Uart_Port, databuf, 10);
}
/// <summary>
///给虚拟示波器发送a,b,c,d取整之后的值
///<para>example:  SEND(a,b,c,d);</para>
///</summary>
/// <param name="a">待发送的变量1</param>
/// <param name="b">待发送的变量2</param>
/// <param name="c">待发送的变量3</param>
/// <param name="d">待发送的变量4</param>
void SEND(float a,float b,float c,float d)
{       
       OutData[0] = a;                   
       OutData[1] = b;                    
       OutData[2] = c;                
       OutData[3] = d;
       OutPut_Data();
}
/*************************************************************/
/*****************数据采集部分************/
/*************************************************************/
/*===================================================================
功能：串口发送数据用于Matlab数据处理
===================================================================*/
void DATA_SEND(long num)
{
    int weishu = 0;
    long num_buff = num;
    long buff = 1;
    int index = 0;

    if (num < 0)
    {
        UART_Put_Buff(CRC_Uart_Port, "-", 1);
        num = -num;
    }

    if (num_buff == 0)
    {
        weishu = 1;
        buff = 10;
    }

    while (num_buff != 0)
    {
        num_buff /= 10;
        weishu++;
        buff *= 10;
    }
    buff /= 10;

    for (index = 0; index < weishu; index++)
    {
        //UART_Put_Buff(CRC_Uart_Port, ((num / buff) % 10) + '0', 1);

        buff /= 10;
    }
    UART_Put_Buff(CRC_Uart_Port, " ", 1);
}

/*************************************************************/
/*****************OLED调试部分************/
/*************************************************************/
//画坐标轴程序，暂未写
void LCD_DrawAxis()
{

}

int Axis_t = 0;//曲线图时刻
int ShowX = 0, ShowY = 0;
/// <summary>
///在OLED上绘制曲线图(相当于在OLED上使用虚拟示波器)
///程序没运行一次时刻点会加1直至超过t_refresh之后会重新从0时刻开始
///<para>example:  LCD_ShowGraphs(data, 126, 0, 100, 0);</para>
///</summary>
/// <param name="data">本次时刻对应的数据值(y轴的值)</param>
/// <param name="t_refresh">刷新时刻点的阈值，最大不超过126</param>
/// <param name="data_low">要显示的数据的范围的下限</param>
/// <param name="data_high">要显示的数据的范围的上限</param>
/// <param name="WhetherClear">刷新时刻点之后是否清屏，1表示清屏，0表示否</param>
void LCD_ShowGraphs(float data, float t_refresh, float data_low, float data_high, int WhetherClear)
{

    if (data < data_low)
        data = data_low;
    if (data_low > data_high)
        data = data_high;

    if (Axis_t > t_refresh)
    {
        Axis_t = 0;
        if (WhetherClear)
        {
            LCD_CLS();  //清屏
        }
    }

    ShowY = 63-(int)((data - data_low) * (63.0/(data_high - data_low)));
    ShowX = Axis_t;

    LCD_PutPixel(ShowX, ShowY);
    Axis_t++;
}

/*************************************************************/
/*****************遥控部分************/
/*************************************************************/
/// <summary>
///初始化遥控器的串口
///</summary>
void RemoteInit()
{
    UART_Init(Remote_Uart_Port, 9600);
    UART_Irq_En(Remote_Uart_Port);
}
int ReceiveIndex = 0;
char ReceiveBuff[3] = {0};
unsigned char StartReceive = 0;
int flag_remote = 0;
int flag_remote_last = 0;
RemoteCMDMode RunMode;//遥控模式
/// <summary>
///接受遥控指令程序，应放入对应的串口中断内
///</summary>
void ReceiveCMD_Remote()
{
    char buff = 0;
    buff = UART_Get_Char(Remote_Uart_Port);

    if (buff == 0xFF && StartReceive == 0)
    {
        StartReceive = 1;
        return;
    }
    else
    {
      if(StartReceive == 0)
        	ReceiveIndex = 0;
    }
    if (StartReceive == 1)
    {
        if (ReceiveIndex < 3)
        {
            ReceiveBuff[ReceiveIndex] = buff;
            ReceiveIndex++;
        }
        else
        {
            if (buff == 0xFF)
            {
                StartReceive = 0;
		ReceiveIndex = 0;
                if (ReceiveBuff[0] == 0x00)//左摇杆
                {
                    switch (ReceiveBuff[1])
                    {
                    case 0x00:
                        RunMode = Left_Return0;
                        flag_remote = 00;
                        break;
                    case 0x01:
                        RunMode = Left_Up;
                        flag_remote = 01;
                        break;
                    case 0x02:
                        RunMode = Left_Down;
                        flag_remote = 02;
                        break;
                    case 0x03:
                        RunMode = Left_Left;
                        flag_remote = 03;
                        break;
                    case 0x04:
                        RunMode = Left_Right;
                        flag_remote = 04;
                        break;
                    default:
                        break;
                    }
                }
                else if (ReceiveBuff[0] == 0x35)//左摇杆
                {
                    switch (ReceiveBuff[1])
                    {
                    case 0x00:
                        RunMode = Right_Return0;
                        flag_remote = 10;
                        break;
                    case 0x01:
                        RunMode = Right_Up;
                        flag_remote = 11;
                        break;
                    case 0x02:
                        RunMode = Right_Down;
                        flag_remote = 12;
                        break;
                    case 0x03:
                        RunMode = Right_Left;
                        flag_remote = 13;
                        break;
                    case 0x04:
                        RunMode = Right_Right;
                        flag_remote = 14;
                        break;
                    default:
                        break;
                    }
                }
                else if (ReceiveBuff[0] == 0xAA)
                {
                    RunMode = Start;
                }
            }
        }
    }

}

///<summary>按键初始化</summary>
void ButtonInit()
{
    EXTI_Init(PTE, 10, either);
    EXTI_Init(PTE, 11, either);
    EXTI_Init(PTE, 12, either);
}
ButtonStatus Button[3] = { NotPress, NotPress, NotPress };//PTE12,PTE11,PTE10

///<summary>按键扫描中断</summary>
void ButtonScan_interrupt()
{
    //Key1
    int n = 10;
    u8 keybuff = 0;
    if ((PORTE_ISFR & (1 << n)))
    {
        PORTE_ISFR |= (1 << n);
        //用户自行添加中断内程序
        keybuff = GPIO_Get(PTE10);
        if (keybuff == 0)
        {
            Button[2] = Press;
        }
        else
        {
            Button[2] = NotPress;
        }
        TFT_showint8(0, 2, Button[2], BLACK, WHITE);
    }
    n = 11;
    if ((PORTE_ISFR & (1 << n)))
    {
        PORTE_ISFR |= (1 << n);
        //用户自行添加中断内程序
        keybuff = GPIO_Get(PTE11);
        if (keybuff == 0)
        {
            Button[1] = Press;
        }
        else
        {
            Button[1] = NotPress;
        }
        TFT_showint8(0, 1, Button[1], BLACK, WHITE);
    }
    n = 12;
    if ((PORTE_ISFR & (1 << n)))
    {
        PORTE_ISFR |= (1 << n);
        //用户自行添加中断内程序
        keybuff = GPIO_Get(PTE12);
        if (keybuff == 0)
        {
            Button[0] = Press;
        }
        else
        {
            Button[0] = NotPress;
        }
        TFT_showint8(0, 0, Button[0], BLACK, WHITE);
    }
}

int ButtonOnceBuffFlag[3] = { 0 };//按键按下一次缓存标志
int ButtonOnceFlag[3] = { 0 };//按键按下一次的标志
int QuitSetFlag = 0;
/// <summary>
///按键菜单程序，用于参数设定等功能，放于主函数的主要功能前
///<para>注：一定要放在TFT初始化后，另外其他有中断的模块初始化都必须放在这个函数后面</para>
///</summary>
void ButtonMenu()
{
    ButtonInit();
    EnableInterrupts;
    while (1)
    {
        for (int i = 0; i < 3; i++)
        {
            if (Button[i] == Press)
            {
                ButtonOnceBuffFlag[i] = 1;
            }
            if ((Button[i] == NotPress) && (ButtonOnceBuffFlag[i] == 1))
            {
                ButtonOnceFlag[i] = 1;
                ButtonOnceBuffFlag[i] = 0;
            }
        }

        if (ButtonOnceFlag[0] == 1)
        {
            ButtonOnceFlag[0] = 0;
            /* 在此编写按下按键1的处理程序 */

        }
        if (ButtonOnceFlag[1] == 1)
        {
            ButtonOnceFlag[0] = 0;
            /* 在此编写按下按键2的处理程序 */

        }
        if (ButtonOnceFlag[2] == 1)
        {
            ButtonOnceFlag[0] = 0;
            /* 在此编写按下按键3的处理程序 */
            QuitSetFlag = 1;
        }
        if (QuitSetFlag == 1)
        {
            dsp_single_colour(WHITE);
            TFT_showstr(0, 0, "QuitButtonSet", RED, WHITE);
            DisableInterrupts;
            break;
        }
    }
}