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

# ifndef _MECANUMWHEELCONTROL_H
# define _MECANUMWHEELCONTROL_H

/*
��������˳��Ϊ��
                1����ǰ��
                2����ǰ��
                3�������
                4���Һ���
*/
# define FTMType_Use FTM0
# define FTMChannel_Use_W1_1 FTM_CH0
# define FTMChannel_Use_W1_2 FTM_CH1
# define FTMChannel_Use_W2_1 FTM_CH2
# define FTMChannel_Use_W2_2 FTM_CH3
# define FTMChannel_Use_W3_1 FTM_CH4
# define FTMChannel_Use_W3_2 FTM_CH5
# define FTMChannel_Use_W4_1 FTM_CH6
# define FTMChannel_Use_W4_2 FTM_CH7

//RunState���ֳ��˶��ٶ�
//�������ٶ�����ʾ���ֳ����˶��ٶ�
typedef struct 
{
    float XSpeed;   //x��(����)ƽ���ٶ�
    float YSpeed;   //y��(ǰ��)ƽ���ٶ�
    float YawSpeed; //yaw��ת���Ľ��ٶ�
}RunSpeed;

typedef enum
{
    P_Control,
    PD_Control,
    PI_Control,
    PID_Control
}PIDControlModel;

typedef struct
{
    float KP;               
    float KD;               
    float KI;               

    float P_Output;         
    float D_Output;         
    float I_Output;
    float Output;
    float Last_Output;

    float MeasuredValue;
    float TargetValue;
    float Error;
    float Last_Error;

    float IntegralLimit;
    float MaxOutput;
    float DeadBand;

    ///<summary>PIDControl�ṹ��Ĺ��캯�������ڳ�ʼ���ýṹ��</summary>
    void(*f_Constructor)(PIDControl* PID, float P_set, float D_set, float I_set,
                         float I_Limit_Set, float MaxOutput_Set, float DeadBand_Set);
    //���PID������
    float(*f_GetPIDControlValue)(PIDControl* PID, PIDControlModel PIDModel,float MeasuredValue);
    //PID������ˢ��
    void(*f_para_Refresh)(PIDControl* PID, float kp, float kd, float ki);
}PIDControl;

#endif