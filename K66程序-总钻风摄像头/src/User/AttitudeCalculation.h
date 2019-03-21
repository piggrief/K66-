#ifndef _ATTITUDECALCULATION_H_
#define _ATTITUDECALCULATION_H_

//˵����my_atan(x,y)   ->    arctan(y/x)�Ľ���ֵ
//���䣺y<0��ʾ���ǣ�x<0���+180�ȣ�û�и��ǣ����x<0��<0����Ϊ-arctan(y/x)+180

float my_atan(float x, float y);
float GetAngle_FromAcc(float Ax, float Ay, float Az);
/// <summary>
///����ʽFIR�˲���
///<para>example:  FIRFilter_ToFloat(Num1, Num, Weight, 5);</para>
///</summary>
/// <param name="Data">���βɼ�������</param>
/// <param name="DataArr">���ݻ�������</param>
/// <param name="weight">FIR�˲���ϵ��(���Ӷ���ʽϵ��Num)</param>
/// <param name="size">FIR�˲�������+1(���ݻ��������С)</param>
float FIRFilter_ToFloat(float Data, float * DataArr, float * weight, int size);

#endif