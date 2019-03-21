/*!
* @file       image_deal.c
* @brief      ���ڵ����õĺ�����
* @details
* @author     lvؼfox
* @version    v1.0
* @date       2019-2-26
* @to do
*
*/


#include "include.h"
#include "image_deal.h"


#define Height              ROW
#define Wide                COL

uint8 top_row;
uint8 bottom_row;
uint8 First_Find[ROW];
uint8 Left[ROW];
uint8 Mid[ROW];
uint8 Right[ROW];
uint8 Left_Flag[ROW];            //��߽�ȷ�ϱ�־���ҵ���߽�
uint8 Right_Flag[ROW];           //�ұ߽�ȷ�ϱ�־���ҵ���߽�
uint8 Mid_Flag[ROW];
uint8 found_flag;
uint8 light_delay_flag;
uint8 find_loop_flag;
uint8 light_flag;
int time = 1;
float temp_piancha = 0;
float everage_piancha = 0;

/***************************������ֵ���˲�**********************************/
void MedianFilter()
{
	int Pic[ROW][COL];
	int a, b, c, d;
	int i,j;
	for (j = 0; j < ROW; j++)
	{
		Pic[0][j] = image[0][j];
		Pic[Height - 1][j] = image[Height - 1][j];
	}
	for (i = 1; i < Height - 1; i++)
	{
		Pic[i][0] = image[i][0];
		Pic[i][Wide - 1] = image[i][Wide - 1];
	}
	for (i = 1; i < Height - 1; i++)
	{
		j = 1;
		a = qic_Sort(image[i - 1][j - 1], image[i - 1][j], image[i - 1][j + 1]);
		b = qic_Sort(image[i][j - 1], image[i][j], image[i][j + 1]);
		c = qic_Sort(image[i + 1][j - 1], image[i + 1][j], image[i + 1][j + 1]);
		d = qic_Sort(a, b, c);
		Pic[i][1] = d;
		for (j = 2; j < Wide - 1; j++)
		{
			if (image[i - 1][j + 1] == image[i - 1][j - 2] && image[i][j + 1] == image[i][j - 2] && image[i + 1][j + 1] == image[i + 1][j - 2])
			{
				Pic[i][j] = d;
			}
			else
			{
				a = qic_Sort(image[i - 1][j - 1], image[i - 1][j], image[i - 1][j + 1]);
				b = qic_Sort(image[i][j - 1], image[i][j], image[i][j + 1]);
				c = qic_Sort(image[i + 1][j - 1], image[i + 1][j], image[i + 1][j + 1]);
				d = qic_Sort(a, b, c);
				Pic[i][j] = d;
			}
		}
	}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			image[i][j] = Pic[i][j];
		}
	}
}
/*************************������Ԫ��������˳������***************************************/
int qic_Sort(int a, int b, int c)
{
	if ((b >= a && b <= c) || (b <= a && b >= c))
	{
		return b;
	}
	else if ((a >= b && a >= c) || (a <= b && a <= c))
	{
		return c;
	}
	else if ((c >= a && c >= b) || (c <= a && c <= b))
	{
		return a;
	}
}
/********************************
             ��ʼ��
********************************/
void Reset()
{
    found_flag = 0;
	find_loop_flag = 0;
	time = 0;
	everage_piancha = 0;

    for (int i = 0; i < ROW; i++)
    {
	  Left_Flag[i] = 0;
	  Mid_Flag[i] = 0;
	  Right_Flag[i] = 0;
     }
}

/**************************************
                  �ҵ�
***************************************/
void find_light()
{
	for (int i = 0; i < ROW;i++)
		{
			for (int j = 1; j < COL; j++)
			{
				if (image[i][j] > ThreasHold)
				{
					if (image[i + 1][j] > ThreasHold)
					{
						found_flag = 1;
						light_delay_flag = 0;
						top_row = i;
						First_Find[i] = j;

						return ;
					}
				}

			}
		}
	if (found_flag == 0)
	{
		find_loop_flag = 1;
		light_delay_flag += 1;
	}
}
/**************************************
			  ��ֵ�ҵ�
**************************************/
void mid_findlight()
{
	int i, j, k;
	if (found_flag == 1)
	{
		for (i = top_row + 1; i < ROW; i++)
		{
			for (j = First_Find[i - 1]; j > 0; j--)
			{
				if (image[i][j] > ThreasHold)
				{

				}
				else
				{
					Left[i] = j;
					Left_Flag[i] = 1;
					break;
				}
			}
			if (Left_Flag[i] == 0)//����
			{
				Left[i] = 0;
				Left_Flag[i] = 1;
			}
			for (k = First_Find[i - 1]; k < COL; k++)
			{
				if (image[i][k] > ThreasHold)
				{

				}
				else
				{
					Right[i] = j;
					Right_Flag[i] = 1;
					break;
				}
			}
			if (Right_Flag[i] == 0)
			{
				Right[i] = COL;
				Right_Flag[i] = 1;
			}
			if (Left_Flag[i] == 1 && Right_Flag[i] == 1)
			{
				Mid_Flag[i] = 1;
				Mid[i] = (Left[i] + Right[i]) / 2;
				bottom_row = i;
			}
			if (image[i + 1][First_Find[i]] < ThreasHold)
				break;
		}
	}
/****************************************
			   ����ƫ��
*****************************************/
	if (find_loop_flag == 1)
	{
          everage_piancha = temp_piancha;
          temp_piancha = everage_piancha;
          
          return;
        }
	
        float piancha = 0;
	time = 1;
	for (int i = top_row; i <= bottom_row; i++)
	{
		if (Mid_Flag[i] == 1)
		{
			piancha += Mid[i];
			time += 1;
		}
		everage_piancha = piancha / time;
		temp_piancha = everage_piancha;//piancha / time;

	}



}

/****************************************
			   �ظ��ҵ�
*****************************************/
void find_loop()
{
	if (find_loop_flag = 1)
	{
		find_light;
	}
	if (light_delay_flag > 7)
	{
		light_flag = 0;//�����־
		find_loop_flag = 0;
		light_delay_flag = 0;
	}
}