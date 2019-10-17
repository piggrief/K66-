/*!
* @file       DebugFuction.h
* @brief      ���ڵ����õĺ�����ͷ�ļ�
* @details
* @author     pig's grief
* @version    v1.0
* @date       2019-2-26
* @to do
*
*/
# ifndef _DEBUGFUNCTION_H_
# define _DEBUGFUNCTION_H_

# define CRC_Uart_Port UART_4
# define Series_Uart_Port UART_4
# define Remote_Uart_Port UART_0
/// <summary>
///������ʾ��������a,b,c,dȡ��֮���ֵ
///<para>example:  SEND(a,b,c,d);</para>
///</summary>
/// <param name="a">�����͵ı���1</param>
/// <param name="b">�����͵ı���2</param>
/// <param name="c">�����͵ı���3</param>
/// <param name="d">�����͵ı���4</param>
void SEND(float a,float b,float c,float d);
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
void LCD_ShowGraphs(float data, float t_refresh, float data_low, float data_high, int WhetherClear);
/*===================================================================
���ܣ����ڷ�����������Matlab���ݴ���(����)
===================================================================*/
void DATA_SEND(long num);



typedef enum
{
    Left_Return0,
    Left_Left,
    Left_Right,
    Left_Up,
    Left_Down,
    Right_Return0,
    Right_Left,
    Right_Right,
    Right_Up,
    Right_Down,
    Start
}RemoteCMDMode;
/// <summary>
///����ң��ָ�����Ӧ�����Ӧ�Ĵ����ж���
///</summary>
void ReceiveCMD_Remote();
/// <summary>
///��ʼ��ң�����Ĵ���
///</summary>
void RemoteInit();
extern RemoteCMDMode RunMode;

typedef enum
{
    Press,
    NotPress
}ButtonStatus;//������״̬��PressΪ����,NotPressΪ����

extern ButtonStatus Button1;//PTE12
extern ButtonStatus Button2;//PTE11
extern ButtonStatus Button3;//PTE10
///<summary>������ʼ��</summary>
void ButtonInit();
///<summary>����ɨ���ж�</summary>
void ButtonScan_interrupt();
/// <summary>
///�����˵��������ڲ����趨�ȹ��ܣ���������������Ҫ����ǰ
///<para>ע��һ��Ҫ����TFT��ʼ���������������жϵ�ģ���ʼ����������������������</para>
///</summary>
void ButtonMenu();

typedef enum
{
  ShowImage_1,
  ShowImage_2,
  NotShow
}TFTShowMode;
extern TFTShowMode NowTFTShowMode;
void Series_Sendout_init(void);
#endif