/*!
* @file       MecanumWheelControl.h
* @brief      �������ֿ��Ʋ��ֵĳ���ͷ�ļ�
* @details    
* @author     pig's grief
* @version    v1.0
* @date       2019-2-12
* @to do      ��д���������ٳ��򲢲���
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
typedef struct RunSpeed
{
    float XSpeed;   //x��(����)ƽ���ٶ�
    float YSpeed;   //y��(ǰ��)ƽ���ٶ�
    float YawSpeed; //yaw��ת���Ľ��ٶ�
}RunSpeed_Now;

typedef enum
{
    P_Control,
    PD_Control,
    PI_Control,
    PID_Control
}PIDControlModel;

typedef struct PIDControl
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
    /*
    * @brirf                PIDControl�ṹ��Ĺ��캯�������ڳ�ʼ���ýṹ��
    * @param-PID            Ҫ����Ľṹ��
    * @param-P_set          KP�������趨ֵ
    * @param-D_set          KD�������趨ֵ
    * @param-I_set          KI�������趨ֵ
    * @param-I_Limit_Set    �����޷�����
    * @param-MaxOutput_Set  ����������������޷�
    * @param-DeadBand_Set   ��������趨ֵ
    * @return        void
    * @note
    * @example       PIDTest.f_Constructor(&PIDTest, 20, 0, 0, 2000, 9600, 0);
    */
    void(*f_Constructor)(struct PIDControl* PID, float P_set, float D_set, float I_set
        , float I_Limit_Set, float MaxOutput_Set, float DeadBand_Set);
    /*
    * @brirf               ���ݱ��β����˼��㲢��ñ��ε�PID������
    * @param-PID           ȷ�����ĸ�PID����
    * @param-PIDModel      ȷ������������P��PD��PI��PID
    * @param-MeasuredValue ���β���ֵ
    * @return              ����PID������
    * @note
    * @example             out = PIDTest.f_GetPIDControlValue(&PIDTest, PID_Control, Measure);
    */
    float(*f_GetPIDControlValue)(struct PIDControl* PID, PIDControlModel PIDModel, float MeasuredValue);
    /*
    * @brirf               PID���Ʋ���ˢ��
    * @param-PID           ȷ�����ĸ�PID����
    * @param-kp            Ҫ���µĲ���KP
    * @param-kd            Ҫ���µĲ���KD
    * @param-ki            Ҫ���µĲ���KI
    * @note
    * @example             PIDTest.f_para_Refresh(&PIDTest, 20, 1, 0.1);
    */
    void(*f_para_Refresh)(struct PIDControl* PID, float kp, float kd, float ki);
}PIDTest;

#endif