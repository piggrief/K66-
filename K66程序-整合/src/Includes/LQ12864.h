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

#ifndef _LQOLED_H
#define _LQOLED_H
#include "include.h"
extern void LCD_Init(void);
extern void LCD_CLS(void);
extern void LCD_P6x8Str(unsigned char x, unsigned char y, unsigned char ch[]);
extern void LCD_P8x16Str(unsigned char x, unsigned char y, unsigned char ch[]);
extern void LCD_P14x16Str(unsigned char x, unsigned char y, unsigned char ch[]);
extern void LCD_Print(unsigned char x, unsigned char y, unsigned char ch[]);
extern void LCD_PutPixel(unsigned char x, unsigned char y);
extern void LCD_Rectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char gif);
extern void Draw_LQLogo(void);
extern void Draw_LibLogo(void);
extern void Draw_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char * bmp);
//extern void Draw_Road(void);
void Draw_Frame(void);
//��ʾ3λ������1λС���������ã���������ѭ������һֱ�ܵĻ����Ƚ�ռ��Ƭ����Դ��
void LCD_PrintFloat_31(unsigned char x, unsigned char y, float num);
//��ʾ5λ����
void LCD_PrintInt5(unsigned char x, unsigned char y, int num);
//��ʾ4λ����
void LCD_PrintInt4(unsigned char x, unsigned char y, int num);
//��ʾ3λ����
void LCD_PrintInt3(unsigned char x, unsigned char y, int num);
//OLEDͼ�����
void OLED_Refresh_Gram(void);
//OLED�������
void OLED_DrawPoint(uint8 x, uint8 y, uint8 t);
/// <summary>
///OLED��ʾ��ֵ��ͼ��
///<para>example:  OLED_ShowImage(128,64,120,188,10,image);</para>
///</summary>
/// <param name="ShowSizeX">OLED��ʾ�����С��Xֵ</param>
/// <param name="ShowSizeY">OLED��ʾ�����С��Yֵ</param>
/// <param name="ImageSizeHeight">����ʾͼ��ĸ߶�</param>
/// <param name="ImageSizeWidth">����ʾͼ��Ŀ��</param>
void OLED_ShowImage(int ShowSizeX, int ShowSizeY, int ImageSizeHeight, int ImageSizeWidth, int Gate_To2, unsigned char imagebuff[120][188]);
#endif

