/*!
* @file       DebugFuction.c
* @brief      ���ڵ����õĺ�����
* @details
* @author     pig's grief
* @version    v1.0
* @date       2019-2-26
* @to do
*             
*/
# include "include.h"
/*************************************************************/
/*****************����ʾ��������************/
/*************************************************************/
float OutData[4] = { 0 };//����Ὣ�����е��ĸ������͸�����ʾ����
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
  
  UART_Put_Buff(CRC_Uart_Port, (char *)(databuf), 10);
}
/// <summary>
///������ʾ��������a,b,c,dȡ��֮���ֵ
///<para>example:  SEND(a,b,c,d);</para>
///</summary>
/// <param name="a">�����͵ı���1</param>
/// <param name="b">�����͵ı���2</param>
/// <param name="c">�����͵ı���3</param>
/// <param name="d">�����͵ı���4</param>
void SEND(float a,float b,float c,float d)
{       
       OutData[0] = a;                   
       OutData[1] = b;                    
       OutData[2] = c;                
       OutData[3] = d;
       OutPut_Data();
}
/*************************************************************/
/*****************���ݲɼ�����************/
/*************************************************************/
/*===================================================================
���ܣ����ڷ�����������Matlab���ݴ���
===================================================================*/
//void DATA_SEND(long num)
//{
//    int weishu = 0;
//    long num_buff = num;
//    long buff = 1;
//    int index = 0;
//
//    if (num < 0)
//    {
//        UART_Put_Buff(CRC_Uart_Port, "-", 1);
//        num = -num;
//    }
//
//    if (num_buff == 0)
//    {
//        weishu = 1;
//        buff = 10;
//    }
//
//    while (num_buff != 0)
//    {
//        num_buff /= 10;
//        weishu++;
//        buff *= 10;
//    }
//    buff /= 10;
//
//    for (index = 0; index < weishu; index++)
//    {
//        UART_Put_Buff(CRC_Uart_Port, ((num / buff) % 10) + '0', 1);
//
//        buff /= 10;
//    }
//    UART_Put_Buff(CRC_Uart_Port, ' ', 1);
//}

/*************************************************************/
/*****************OLED���Բ���************/
/*************************************************************/
//�������������δд
void LCD_DrawAxis()
{

}

int Axis_t = 0;//����ͼʱ��
int ShowX = 0, ShowY = 0;
/// <summary>
///��OLED�ϻ�������ͼ(�൱����OLED��ʹ������ʾ����)
///����û����һ��ʱ�̵���1ֱ������t_refresh֮������´�0ʱ�̿�ʼ
///<para>example:  LCD_ShowGraphs(data, 126, 0, 100, 0);</para>
///</summary>
/// <param name="data">����ʱ�̶�Ӧ������ֵ(y���ֵ)</param>
/// <param name="t_refresh">ˢ��ʱ�̵����ֵ����󲻳���126</param>
/// <param name="data_low">Ҫ��ʾ�����ݵķ�Χ������</param>
/// <param name="data_high">Ҫ��ʾ�����ݵķ�Χ������</param>
/// <param name="WhetherClear">ˢ��ʱ�̵�֮���Ƿ�������1��ʾ������0��ʾ��</param>
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
            LCD_CLS();  //����
        }
    }

    ShowY = 63-(int)((data - data_low) * (63.0/(data_high - data_low)));
    ShowX = Axis_t;

    LCD_PutPixel(ShowX, ShowY);
    Axis_t++;
}