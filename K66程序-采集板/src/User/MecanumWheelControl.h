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
//Forth MOTOR CHANNEL ONE PC3\FTM0_CH2 | TWO PC4\FTM0_CH3 
//THIRD MOTOR CHANNEL ONR PC1\FTM0_CH0 | TWO PC2\FTM0_CH1
//SECOND MOTOR CHANNEL ONE PA10\FTM2_CH0 | TWO PA11\FTM2_CH1
//FIRST MOTOR CHANNEL ONE PA8\FTM1_CH0 | TWO PA9\FTM1_CH1
# define FTMType_Use1 FTM1
# define FTMType_Use2 FTM2
# define FTMType_Use3 FTM0
# define FTMType_Use4 FTM0
# define FTMChannel_Use_W1_1 FTM_CH1
# define FTMChannel_Use_W1_2 FTM_CH0
# define FTMChannel_Use_W2_1 FTM_CH1
# define FTMChannel_Use_W2_2 FTM_CH0
# define FTMChannel_Use_W3_1 FTM_CH1
# define FTMChannel_Use_W3_2 FTM_CH0
# define FTMChannel_Use_W4_1 FTM_CH3
# define FTMChannel_Use_W4_2 FTM_CH2

//RunState���ֳ��˶��ٶ�
//�������ٶ�����ʾ���ֳ����˶��ٶ�
struct RunSpeed
{
    float XSpeed;   //x��(����)ƽ���ٶ�
    float YSpeed;   //y��(ǰ��)ƽ���ٶ�
    float YawSpeed; //yaw��ת���Ľ��ٶ�
};//������ο��ѿ�������ϵ

typedef enum
{
    OpenloopControl,
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


/// <summary>
///�趨�����˶��ٶȣ�x��y��ƽ���ٶȺ���ת�ٶȣ�
///<para>example:  SetTargetSpeed_Car(&amp;PIDTest, 10, 15, 20);</para>
///</summary>
/// <param name="TargetSpeed">�����洢�����ٶȵĽṹ��</param>
/// <param name="Vx">x��ƽ���ٶ�</param>
/// <param name="Vy">y��ƽ���ٶ�</param>
/// <param name="W_yaw">��ת���ٶ�</param>
void SetTargetSpeed_Car(struct RunSpeed* TargetSpeed, float Vx, float Vy, float W_yaw);


/// <summary>
///�����������˶�״̬������ÿ��������Ҫ������ٶ�ֵ
///<para>example:  CalTargetSpeed_EachWheel(&amp;TargetSpeed);</para>
///</summary>
/// <param name="TargetSpeed">������������˶��ٶȽṹ��</param>
void CalTargetSpeed_EachWheel(struct RunSpeed* TargetSpeed);



///<summary>�����ĸ�������ControlValue������ĸ������ռ�ձ�</summary>
void MotorOutput(float * ControlValue);



///<summary>�ĸ���������ʼ��</summary>
void EncoderMeasure_Init(void);


///<summary>��õ�index�����ӵ�ת��</summary>
void GetSpeed(int index);


///<summary>�ٶȼ�������</summary>
void SpeedClean(void);

void SetSpeed_FromRemote(RemoteCMDMode mode);

///<summary>PID��ʼ��</summary>
void PID_Speedloop_init( float *P_set, float *D_set, float *I_set, float I_Limit_Set, float MaxOutput_Set, float *DeadBand_Set);
void PID_locationloop_init( float P_set, float D_set, float I_set, float I_Limit_Set, float MaxOutput_Set, float DeadBand_Set);
void Series_Control(float deviation);
#endif