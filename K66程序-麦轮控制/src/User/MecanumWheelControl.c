/*!
* @file       MecanumWheelControl.c
* @brief      �������ֿ��Ʋ��ֵĳ���
* @details
* @author     pig's grief
* @version    v1.0
* @date       2019-2-12
* @to do      
*             ������������ٳ����DMA�޷���������
*/

# include "include.h"
//�涨��ÿ�����Ӷ�Ӧ��FTM���ͨ����������תӦ���������
FTM_CHn_e Wheels_FTMChannel[4][2] = { { FTMChannel_Use_W1_1, FTMChannel_Use_W1_2 },
                                      { FTMChannel_Use_W2_1, FTMChannel_Use_W2_2 },
                                      { FTMChannel_Use_W3_2, FTMChannel_Use_W3_1 },
                                      { FTMChannel_Use_W4_2, FTMChannel_Use_W4_1 } };


///<summary>��ӦPIDControl�ṹ���ڵ�f_Constructor</summary>
void PIDControl_Constructor(struct PIDControl* PID, float P_set, float D_set, float I_set,
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
///<summary>��ӦPIDControl�ṹ���ڵ�f_GetPIDControlValue</summary>
float GetPIDControlValue(struct PIDControl* PID, PIDControlModel PIDModel, float MeasuredValue)
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
///<summary>��ӦPIDControl�ṹ���ڵ�f_para_Refresh</summary>
void Para_Refresh(struct PIDControl* PID, float kp, float kd, float ki)
{
    PID->KP = kp;
    PID->KD = kd;
    PID->KI = ki;
}

/// <summary>
///ʹ�ṹ��PIDControl�еĺ���ָ��ָ����嶨��ĺ���
///<para>example:  PIDControl_FunctionDefine(&amp;PIDTest);</para>
///</summary>
/// <param name="PID">PIDControl�ṹ��</param>
void PIDControl_FunctionDefine(struct PIDControl* PID)
{
    PID->f_Constructor = PIDControl_Constructor;
    PID->f_GetPIDControlValue = GetPIDControlValue;
    PID->f_para_Refresh = Para_Refresh;
}
struct PIDControl WheelControl[4];//�ĸ����ӵ�PID��������

///���ֿ��Ʋ���

/// <summary>
///�趨�����˶��ٶȣ�x��y��ƽ���ٶȺ���ת�ٶȣ�
///<para>example:  SetTargetSpeed_Car(&amp;PIDTest, 10, 15, 20);</para>
///</summary>
/// <param name="TargetSpeed">�����洢�����ٶȵĽṹ��</param>
/// <param name="Vx">x��ƽ���ٶ�</param>
/// <param name="Vy">y��ƽ���ٶ�</param>
/// <param name="W_yaw">��ת���ٶ�</param>
void SetTargetSpeed_Car(struct RunSpeed * TargetSpeed, float Vx, float Vy, float W_yaw)
{
    TargetSpeed->XSpeed = Vx;
    TargetSpeed->YSpeed = Vy;
    TargetSpeed->YawSpeed = W_yaw;
}
/// <summary>
///�����������˶�״̬������ÿ��������Ҫ������ٶ�ֵ
///<para>example:  CalTargetSpeed_EachWheel(&amp;TargetSpeed);</para>
///</summary>
/// <param name="TargetSpeed">������������˶��ٶȽṹ��</param>
void CalTargetSpeed_EachWheel(struct RunSpeed * TargetSpeed)
{
    ///O-���������ֵ��̵����˶�ѧģ��
    ///�õ����˶�״̬�����ĸ�����Ӧ�е��ٶ�
    WheelControl[0].TargetValue = TargetSpeed->YSpeed - TargetSpeed->XSpeed + TargetSpeed->YawSpeed;
    WheelControl[1].TargetValue = TargetSpeed->YSpeed + TargetSpeed->XSpeed - TargetSpeed->YawSpeed;
    WheelControl[2].TargetValue = TargetSpeed->YSpeed - TargetSpeed->XSpeed - TargetSpeed->YawSpeed;
    WheelControl[3].TargetValue = TargetSpeed->YSpeed + TargetSpeed->XSpeed + TargetSpeed->YawSpeed;
}


///<summary>�����ĸ�������ControlValue������ĸ������ռ�ձ�</summary>
void MotorOutput(float * ControlValue)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        if (ControlValue[i] >= 0)
        {
            FTM_PWM_Duty(FTMType_Use, Wheels_FTMChannel[i][1], 0);
            FTM_PWM_Duty(FTMType_Use, Wheels_FTMChannel[i][0], ControlValue[i]);
        }
        else
        {
            FTM_PWM_Duty(FTMType_Use, Wheels_FTMChannel[i][1], 0);
            FTM_PWM_Duty(FTMType_Use, Wheels_FTMChannel[i][0], -ControlValue[i]);
        }
    }
}
long temp_Speed[4] = { 0 };
long SpeedCount[4] = { 0 };
//�����������õ�DMAͨ����
DMA_CHn Encoder_DMAChannel[4] = { DMA_CH5, DMA_CH6, DMA_CH7, DMA_CH8 };
//�����������õĲ�������Port�˿�
PTXn_e  Encoder_PORT[4] = { PTC5, PTD12, PTA26, PTE27 };
//�����������õ���ת����Port�ܶ˿�
GPIO_Type* EncoderDirectionPort[4] = { PTC, PTD, PTA, PTE };
//�����������õ���ת����Port�˿�����
int Encoder_PORTIndex_Direction[4] = { 7, 13, 27, 28 };
PTXn_e Encoder_Direction[4] = {PTC7, PTD13, PTA27, PTE28};

///<summary>�ĸ���������ʼ��</summary>
void EncoderMeasure_Init(void)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        GPIO_Init(EncoderDirectionPort[i], Encoder_PORTIndex_Direction[i], GPI, 0);
        DMA_Count_Init(Encoder_DMAChannel[i], Encoder_PORT[i], 65535, DMA_rising_down);

        SpeedCount[i] = 0;
        temp_Speed[i] = 0;
    }
}


//�ĸ����ӷ�תʱ����ת����IO
u8 Flag_Reverse[4] = { 0, 0, 0, 0 };

///<summary>��õ�index�����ӵ�ת��</summary>
void GetSpeed(int index)
{
    u8 flag_temp = 0;
    index--;

    temp_Speed[index] = DMA_Count_Get(Encoder_DMAChannel[index]);
    
    flag_temp = GPIO_Get(Encoder_Direction[index]);
    if (flag_temp == Flag_Reverse[index])
    {
        temp_Speed[index] *= -1;
    }
    SpeedCount[index] += temp_Speed[index];

    DMA_Count_Reset(Encoder_DMAChannel[index]);

}

///<summary>�ٶȼ�������</summary>
void SpeedClean(void)
{
    int i = 0;
    for (i = 0; i < 4; i++)
        SpeedCount[i] = 0;
}

struct RunSpeed RS_Now;
int Remote_Speed = 1000;
void SetSpeed_FromRemote(RemoteCMDMode mode)
{
    float ControlValue_Openloop[4];
    switch (mode)
    {
    case Left_Left:
        SetTargetSpeed_Car(&RS_Now, Remote_Speed, 0, 0);
        break;
    case Left_Right:
        SetTargetSpeed_Car(&RS_Now, -Remote_Speed, 0, 0);
        break;
    case Left_Up:
        SetTargetSpeed_Car(&RS_Now, 0, Remote_Speed, 0);
        break;
    case Left_Down:
        SetTargetSpeed_Car(&RS_Now, 0, -Remote_Speed, 0);
        break;
    case Left_Return0:
        SetTargetSpeed_Car(&RS_Now, 0, 0, 0);
        break;
    default:
        SetTargetSpeed_Car(&RS_Now, 0, 0, 0);
        break;
    }

    CalTargetSpeed_EachWheel(&RS_Now);

    for (int i = 0; i < 4; i++)
    {
        ControlValue_Openloop[i] = WheelControl[i].TargetValue;
    }
    MotorOutput(ControlValue_Openloop);
}