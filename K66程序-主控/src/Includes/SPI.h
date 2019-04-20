
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�MK66FX�����˿���ƽ̨���ذ�
����    �ġ�CHIUSIR
����    ע����ģ��ο�@author ɽ��Ƽ�
������汾��V1.0
�������¡�2016��08��20��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
���������䡿chiusir@163.com
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef __MK66_SPI_H__
#define __MK66_SPI_H__

extern uint32 core_clk_M;//��λMHZ
extern uint32 bus_clk_M;//��λMHZ

/**********************************  SPI   ***************************************/
//PCS�ӿڣ����õ�ʱ����Ҫע�ͣ��Ͳ�����г�ʼ����Ӧ�Ĺܽ�
//      ģ��ͨ��    �˿�          ��ѡ��Χ                  ����

#define SPI0_SCK    PTD1       // PTA15��PTC5��PTD1        ȫ������ ALT2
#define SPI0_SOUT   PTD2       // PTA16��PTC6��PTD2        ȫ������ ALT2
#define SPI0_SIN    PTA17       // PTA17��PTC7��PTD3        ȫ������ ALT2

#define SPI0_PCS0   PTD0      // PTA14��PTC4��PTD0��      ȫ������ ALT2
//һ��������ò�����ô��Ĵӻ�������Ƭѡ�ܽ�ע�͵����������Ҫ���Կ���
#define SPI0_PCS1   PTC3        // PTC3��PTD4               ȫ������ ALT2
#define SPI0_PCS2   PTC2        // PTC2��PTD5               ȫ������ ALT2
#define SPI0_PCS3   PTC1        // PTC1��PTD6               ȫ������ ALT2
#define SPI0_PCS4   PTC0        // PTC0��                   ȫ������ ALT2
#define SPI0_PCS5   PTB23       // PTB23                    ALT3


#define SPI1_SCK    PTE2       // PTE2��PTB11��            ȫ������ ALT2
#define SPI1_SOUT   PTE1       // PTE1��PTB16��            ȫ������ ALT2
#define SPI1_SIN    PTB17       // PTE3��PTB17��            ȫ������ ALT2

#define SPI1_PCS0   PTE4   

// PTE4��PTB10��            ȫ������ ALT2
#define SPI1_PCS1   PTE0        // PTE0��PTB9��             ȫ������ ALT2
#define SPI1_PCS2   PTE5        // PTE5��                   ȫ������ ALT2
#define SPI1_PCS3   PTE6        // PTE6��                   ȫ������ ALT2


#define SPI2_SCK    PTB21       // PTB21��PTD12             ȫ������ ALT2
#define SPI2_SOUT   PTB22       // PTB22��PTD13             ȫ������ ALT2
#define SPI2_SIN    PTB23       // PTB23��PTD14             ȫ������ ALT2
#define SPI2_PCS0   PTB20       // PTB20��PTD11             ȫ������ ALT2
#define SPI2_PCS1   PTD15       // PTD15                    ȫ������ ALT2

//�������ӻ�ģʽ
typedef enum
{
    MASTER,    //����ģʽ
    SLAVE      //����ģʽ
} SPI_CFG;

//����SPIģ���
typedef enum
{
    SPI_0,
    SPI_1,
    SPI_2
} SPIn_e;

//����SPIģ��Ƭѡ��
typedef enum
{
    SPIn_PCS0 = 1 << 0,
    SPIn_PCS1 = 1 << 1,
    SPIn_PCS2 = 1 << 2,
    SPIn_PCS3 = 1 << 3,
    SPIn_PCS4 = 1 << 4,
    SPIn_PCS5 = 1 << 5,
} SPIn_PCSn_e;


uint32 spi_init       (SPIn_e, SPIn_PCSn_e , SPI_CFG,uint32 baud);                                        //SPI��ʼ��������ģʽ

//�������շ��ͺ���
void spi_mosi       (SPIn_e spin, SPIn_PCSn_e pcs,                              uint8 *modata, uint8 *midata,               uint32 len);    //SPI���ͽ��պ���,����databuff���ݣ����ѽ��յ������ݴ����databuff��(ע�⣬�Ḳ��ԭ����databuff)
void spi_mosi_cmd   (SPIn_e spin, SPIn_PCSn_e pcs, uint8 *mocmd , uint8 *micmd , uint8 *modata, uint8 *midata, uint32 cmdlen , uint32 len); //SPI���ͽ��պ���,��spi_mosi��ȣ������ȷ���cmd �������Ĳ��裬���ֿ������ַ���



#endif  // __MK60_SPI_H__