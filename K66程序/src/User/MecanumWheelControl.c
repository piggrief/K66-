/*!
* @file       MecanumWheelControl.h
* @brief      �������ֿ��Ʋ��ֳ���ͷ�ļ�
* @details
* @author     pig's grief
* @version    v1.0
* @date       2019-2-12
* @History
*             v1.0:2019-2-12 ������RunSpeed��PIDControl����ṹ��
                             ��д����PIDControl_Constructor��PIDControl_FunctionDefine
                             ��д��PID���Ƶ���Ҫ������GetPIDControlValue��Para_Refresh
                             ��д����������:MotorOutput
                             !!���Ϻ�����Ϊ����
*/

# include "include.h"

FTM_CHn_e Wheels_FTMChannel[4][2] = { { FTMChannel_Use_W1_1, FTMChannel_Use_W1_2 },
                                      { FTMChannel_Use_W2_1, FTMChannel_Use_W2_2 },
                                      { FTMChannel_Use_W3_1, FTMChannel_Use_W3_2 },
                                      { FTMChannel_Use_W4_1, FTMChannel_Use_W4_2 } };


void PIDControl_Constructor(PIDControl* PID, float P_set, float D_set, float I_set,
                            float I_Limit_Set, float MaxOutput_Set, float DeadBand_Set)
{
    PID->KP = P_set;
    PID->KD = D_set;
    PID->KI = I_set;
    PID->IntegralLimit = I_Limit_Set;
    PID->MaxOutput = MaxOutput_Set;
    PID->DeadBand = DeadBand_Set;

    PID->P_Output = 0;
    PID->D_Output = 0;
    PID->I_Output = 0;
    PID->Output = 0;
    PID->Last_Error = 0;
    PID->Last_Output = 0;
}

float GetPIDControlValue(PIDControl* PID, PIDControlModel PIDModel, float MeasuredValue)
{
    PID->Last_Error = PID->Error;
    PID->Last_Output = PID->Output;

    PID->MeasuredValue = MeasuredValue;
    PID->Error = PID->TargetValue - PID->MeasuredValue;

    PID->P_Output = PID->KP * PID->Error;

    if (PIDModel == PID_Control || PIDModel == PD_Control)
        PID->D_Output = PID->KD * (PID->Error - PID->Last_Error);
    else
        PID->D_Output = 0;
    if (PIDModel == PID_Control || PIDModel == PI_Control)
    {
        PID->I_Output += (PID->KI * PID->Error);

        if (PID->I_Output > PID->IntegralLimit)
            PID->I_Output = PID->IntegralLimit;
        if (PID->I_Output < -PID->IntegralLimit)
            PID->I_Output = -PID->IntegralLimit;
    }
    else
        PID->I_Output = 0;

    PID->Output = PID->P_Output + PID->D_Output + PID->I_Output;
    PID->P_Output += PID->DeadBand;

    if (PID->Output > PID->MaxOutput)
        PID->Output = PID->MaxOutput;
    if (PID->Output < -PID->MaxOutput)
        PID->Output = -PID->MaxOutput;

    return PID->Output;
}

void Para_Refresh(PIDControl* PID, float kp, float kd, float ki)
{
    PID->KP = kp;
    PID->KD = kd;
    PID->KI = ki;
}

///<summary>ʹ�ṹ��PIDControl�еĺ���ָ��ָ����嶨��ĺ���</summary>
void PIDControl_FunctionDefine(PIDControl* PID)
{
    PID->f_Constructor = PIDControl_Constructor;
    PID->f_GetPIDControlValue = GetPIDControlValue;
    PID->f_para_Refresh = Para_Refresh;
}

///<summary>�����ĸ�������ControlValue������ĸ������ռ�ձ�</summary>
void MotorOutput(float * ControlValue)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        if (ControlValue[i] >= 0)
        {
            FTM_PWM_Duty(FTMType_Use, Wheels_FTMChannel[i][2], 0);
            FTM_PWM_Duty(FTMType_Use, Wheels_FTMChannel[i][1], ControlValue[i]);
        }
        else
        {
            FTM_PWM_Duty(FTMType_Use, Wheels_FTMChannel[i][1], 0);
            FTM_PWM_Duty(FTMType_Use, Wheels_FTMChannel[i][2], -ControlValue[i]);
        }
    }
}


