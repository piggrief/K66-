/*!
* @file       MPU6050Drive.h
* @brief      MPU6050�������ֵĳ���ͷ�ļ�
* @details    
* @author     pig's grief
* @version    v1.0
* @date       2019-2-23
* @to do      
*/

# ifndef _MPU6050DRIVE_H
# define _MPU6050DRIVE_H

//#define MPU6050UseDMP 1


//����Ǽ��ٶ�
struct GYROData
{
    float X;
    float Y;
    float Z;
    float Offset_X;
    float Offset_Y;
    float Offset_Z;
};

//������ٶ�
struct AccelData
{
    float X;
    float Y;
    float Z;
    float Offset_X;
    float Offset_Y;
    float Offset_Z;

};

//����Ƕ�
struct AngleData
{
    float X;
    float Y;
    float Z;

};

extern struct GYROData GYRO_OriginData;
extern struct AccelData Accel_OriginData;

// ����MPU6050�ڲ���ַ
#define	MPU6050_DEV_ADDR	    0xD0>>1	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ

#define	SMPLRT_DIV				0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG					0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG				0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	        0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define INT_PIN_CFG	  			0x37    //����6050����I2CΪֱͨģʽ�Ĵ���
#define	ACCEL_XOUT_H	        0x3B
#define	ACCEL_XOUT_L	        0x3C
#define	ACCEL_YOUT_H	        0x3D
#define	ACCEL_YOUT_L	        0x3E
#define	ACCEL_ZOUT_H	        0x3F
#define	ACCEL_ZOUT_L	        0x40
#define	GYRO_XOUT_H				0x43
#define	GYRO_XOUT_L				0x44	
#define	GYRO_YOUT_H				0x45
#define	GYRO_YOUT_L				0x46
#define	GYRO_ZOUT_H				0x47
#define	GYRO_ZOUT_L				0x48
#define User_Control 			0x6A    //�ر�6050�Ը���I2C�豸�Ŀ���
#define	PWR_MGMT_1				0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I				0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)

///DMP////////////////////////////////////////
#ifdef MPU6050UseDMP


#endif

void InitMPU6050(void);
void Get_AccData(struct AccelData * Accel_Data);
void Get_Gyro(struct GYROData * GYRO_Data);
void Get_Offset(struct AccelData * Accel_Data, struct GYROData * GYRO_Data);
int MPU6050DMP_Init();
extern int dmp_read_fifo(short *gyro, short *accel, long *quat,
unsigned long *timestamp, short *sensors, unsigned char *more);


#endif