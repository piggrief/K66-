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

# define CRC_Uart_Port UART_3
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
//void DATA_SEND(long num);
#endif