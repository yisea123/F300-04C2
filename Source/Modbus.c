/*
Description:            ModbusͨѶ���
Author:                 �Ժ���
Date:                   2013-12-9
*/


#include "include.h"

#define OFLVAL_MB       0xFFFFFFFF


#define READREGISTER   0x03         //���Ĵ���
#define WRITEREGISTER  0x06         //д˫�ֽڼĴ���
#define WRITEREGISTERS 0x10         //д���ֽڼĴ���
#define READCOIL       0x01         //����Ȧ
#define WRITECOIL      0x05         //д��Ȧ

#define FUNCTIONERRO   0x01       //�Ƿ��Ĺ�����
#define DATAPLACEERRO  0x02       //�Ƿ�������λ��
#define DATAERRO       0x03       //�Ƿ������� 
#define SLAVEBROKEN    0x04       //�ӻ�����
#define NOSUCCESS      0x07       //���ɹ��ı������
#define RESPONSEOK     0x00       //������Ӧ

#define STARTADS 0               //��ʼ���ܵ�ַ
#define RW2BYTESTARTADS 12       //��д˫�ֽ���ʼ���ܵ�ַ 
#define RW2BYTEENDADS 276        //��д˫�ֽڽ������ܵ�ַ 
#define RW4BYTESTARTADS 16       //��д���ֽ���ʼ���ܵ�ַ 
#define RW4BYTEENDADS 43         //��д���ֽڽ������ܵ�ַ 
#define RW4BYTESTARTADS_1 178     //��д���ֽ���ʼ���ܵ�ַ 
#define RW4BYTEENDADS_1   268     //��д���ֽڽ������ܵ�ַ 
#define R2BYTETOTAL    (RW2BYTEENDADS+1)       //�ɶ����ֵ����� 
#define RWCOILSTARTADSEE 64     //��д��Ȧ��ʼ���ܵ�ַ
#define RWCOILENDADSEE   95     //��д��Ȧ�������ܵ�ַ
#define RWCOILSTARTADSDEAL 96   //��д��Ȧ���⴦����ʼ��ַ 
#define RWCOILENDADSDEAL   127  //��д��Ȧ���⴦��������ַ
#define READMAXNUM     50      //һ���Զ�ȡ�ֳ�Ϊ50,��100���ֽ�
//for test
#define F1_1ADDRESS         28      //F1.1��ַ
#define F1_6ADDRESS         38      //F1.6��ַ



#define YEAR    0
#define MONTH   1
#define DATE    2
#define WEEK    3
#define HOUR    4
#define MINUTE  5
#define SECOND  6

/* CRC ��λ�ֽ�ֵ�� */ 
const u8 auchCRCHi[] = { 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40 
} ; 
/* CRC��λ�ֽ�ֵ��*/ 
const u8 auchCRCLo[] = { 
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 
0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 
0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 
0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 
0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 
0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 
0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 
0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 
0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 
0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 
0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 
0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 
0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 
0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 
0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 
0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 
0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 
0x43, 0x83, 0x41, 0x81, 0x80, 0x40 
} ;



/*
ϵͳ�е�gs_Cal.Point����˳����
#define     UNIT_g      0
#define     UNIT_kg     1
#define     UNIT_t      2
#define     UNIT_lb     3
Modbus�ĵ�λ˳����
t       0
g       1
kg      2
lb      3
���Զ�дModbusʱҪ����ת��
*/
const u8 cu8_ReadUnit[] = {1, 2, 0, 3};
const u8 cu8_WriteUnit[] = {UNIT_t, UNIT_g, UNIT_kg, UNIT_lb};

bool (*FpCheckCrcLrc)(u8 *fu8p_Arry, u32 fu32_Num); //ModbusУ���麯����ָ��
void (*FpBuildCrcLrc)(u8 *fu8p_Arry, u32 fu32_Num); //Modbus����У�麯����ָ��
bool (*FpSendRtuAscII)(u8 *fu8p_Data, u32 fu32_Num);    //Modbus���ͺ�����ָ��



//uart0���modbusͨѶ����
u32 ulTBUFAvailNum_UART0;   //���ͻ������е���Ч���ݸ���
u32 ulTBUFBegin_UART0;      //���ͻ���������Ч��ʼ��ַ
ISPDelay DelayType_UART0;       //��ʱ����
bool bOverT15_UART0=false;      //T1.5��ʱ��־
bool bOverT35_UART0=false;      //T3.5��ʱ��־
bool bBeginReceive_UART0=false; //��ʼ��������
bool bFinishReceive_UART0;//��ʼ��������
u32 ulInsertPos_UART0;          //���ݲ���ָ���
u32 ulFrameLength_UART0;        //���ݳ���(���ջ��峤��)
u8  u8ModbusAddr_UART0;
bool bUARTSending_UART0=false;        //����û�з��Ͳ���
u16 gu16_ModBusReadNumber_UART0;

//uart1���modbusͨѶ����
u32 ulTBUFAvailNum_UART1;   //���ͻ������е���Ч���ݸ���
u32 ulTBUFBegin_UART1;      //���ͻ���������Ч��ʼ��ַ
ISPDelay DelayType_UART1;       //��ʱ����
bool bOverT15_UART1=false;      //T1.5��ʱ��־
bool bOverT35_UART1=false;      //T3.5��ʱ��־
bool bBeginReceive_UART1=false; //��ʼ��������
bool bFinishReceive_UART1;//��ʼ��������
u32 ulInsertPos_UART1;          //���ݲ���ָ���
u32 ulFrameLength_UART1;        //���ݳ���(���ջ��峤��)
u8  u8ModbusAddr_UART1;
bool bUARTSending_UART1=false;        //����û�з��Ͳ���
u16 gu16_ModBusReadNumber_UART1;


u16 gu16_MbIoTestSwitch;        //���������Կ���
u16 gu16_MbIoOutTest;           //������������ԼĴ���
u16 gu16_MbIoInState;           //����������״̬
u16 gu16_MbIoOutState;          //���������״̬
u32 gu32_GainMv = 0;              //A��MODBUS�ֶ��궨����mv��
u32 gu32_ReadCoilIo;            //��д�������洢
u32 gu32_ReadCoilSwitch;        //��д��Ȧ�洢
bool gb_MbKeyLockFlg;           //���ڲ���������
bool gb_S485Recieve = false;
u16 gu16_MbIOOutInit;       //�����������ʼ��0  δ��ʼ��1 0093
u16 gu16_MbIoOutDebug;      //94~105
u32 gu32_MbLastResult = 0;      //�ϳӰ�װ���

u8 BuildModbusLrc(u8 *fuc_Msg, u8 fuc_DataLen);

/***********************************************************************
�� �� ����void DisableRecIRQ_UART0(void)
��    �ܣ���ֹ�����ж�
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ�jzt                  ��    �ڣ�2007-8-2 14:42
��    �ģ�                     ��    �ڣ�
***********************************************************************/
void DisableRecIRQ_UART0(void)
{
    //�رշǿ��ж�
    UART_ItConfig(UART0,UART_RxBufNotEmpty,DISABLE);
}

/***********************************************************************
�� �� ����void DisableRecIRQ_UART1(void)
��    �ܣ���ֹ�����ж�
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ�jzt                  ��    �ڣ�2007-8-2 14:42
��    �ģ�                     ��    �ڣ�
***********************************************************************/
void DisableRecIRQ_UART1(void)
{
    //�رշǿ��ж�
    UART_ItConfig(UART1,UART_RxBufNotEmpty,DISABLE);
}

/***********************************************************************
�� �� ����void EnableRecIRQ_UART0(void)
��    �ܣ����������ж�
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ�jzt                  ��    �ڣ�2007-8-2 14:43
��    �ģ�                     ��    �ڣ�
***********************************************************************/
void EnableRecIRQ_UART0(void)
{
    //�����ǿ��ж�
    UART_ItConfig(UART0,UART_RxBufNotEmpty,ENABLE);
}

/***********************************************************************
�� �� ����void EnableRecIRQ_UART1(void)
��    �ܣ����������ж�
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ�jzt                  ��    �ڣ�2007-8-2 14:43
��    �ģ�                     ��    �ڣ�
***********************************************************************/
void EnableRecIRQ_UART1(void)
{
    //�����ǿ��ж�
    UART_ItConfig(UART1,UART_RxBufNotEmpty,ENABLE);
}

/***********************************************************************
�� �� ����void DisableSendIRQ_UART0(void)
��    �ܣ����������ж�
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ�jzt                  ��    �ڣ�2007-8-2 16:30
��    �ģ�                     ��    �ڣ�
***********************************************************************/
void DisableSendIRQ_UART0(void)
{
    //�رշ��ͻ���������жϺͿ��ж�
    UART_ItConfig(UART0,UART_TxHalfEmpty,DISABLE);
    UART_ItConfig(UART0,UART_TxEmpty,DISABLE);
}

/***********************************************************************
�� �� ����void DisableSendIRQ_UART1(void)
��    �ܣ����������ж�
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ�jzt                  ��    �ڣ�2007-8-2 16:30
��    �ģ�                     ��    �ڣ�
***********************************************************************/
void DisableSendIRQ_UART1(void)
{
    //�رշ��ͻ���������жϺͿ��ж�
    UART_ItConfig(UART1,UART_TxHalfEmpty,DISABLE);
    UART_ItConfig(UART1,UART_TxEmpty,DISABLE);
}

/***********************************************************************
�� �� ����void EnableSendIRQ_UART0(void)
��    �ܣ����������ж�
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ�jzt                  ��    �ڣ�2007-8-2 16:30
��    �ģ�                     ��    �ڣ�
***********************************************************************/
void EnableSendIRQ_UART0(void)
{
    //�������ͻ���������жϺͿ��ж�
    UART_ItConfig(UART0,UART_TxHalfEmpty,ENABLE);
    UART_ItConfig(UART0,UART_TxEmpty,ENABLE);
}

/***********************************************************************
�� �� ����void EnableSendIRQ_UART1(void)
��    �ܣ����������ж�
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ�jzt                  ��    �ڣ�2007-8-2 16:30
��    �ģ�                     ��    �ڣ�
***********************************************************************/
void EnableSendIRQ_UART1(void)
{
    //�������ͻ���������жϺͿ��ж�
    UART_ItConfig(UART1,UART_TxHalfEmpty,ENABLE);
    UART_ItConfig(UART1,UART_TxEmpty,ENABLE);
}

/***********************************************************************
�� �� ����void UartModbusInit_UART0(UartSet_Typedef *pUartSet)
��    �ܣ���ʼ��Modebusʹ�õĴ���
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ��Ժ���               ��    �ڣ�2014-1-22
��    �ģ�                     ��    �ڣ�
***********************************************************************/
void UartModbusInit_UART0(void)
{
    UART_Init(UART0);
    Sio_485_Enable();
    
    //������ʱ�򣬷��Ͷ�����Ч����Ϊ0����ָ�붼ָ�������ͷ����
    ulTBUFAvailNum_UART0=0;
    ulTBUFBegin_UART0=0;
    
    DelayType_UART0=DelayNo;        //��ʼ����ʱ����Ϊ����ʱ
    bOverT15_UART0=true;            //T1.5��ʱ��־
    bOverT35_UART0=true;            //T3.5��ʱ��־
    bBeginReceive_UART0=false;      //��ʼ��������
    bFinishReceive_UART0=false;     //��ʼ��������
    
    u8ModbusAddr_UART0=gs_Setup.TareNumber_2;      //���Ȱ�Modbus��ַ����Ϊͨ�õ�ַ
    ulInsertPos_UART0=0;            //���ݲ���ָ���
    ulFrameLength_UART0=0;          //���ݳ���
    ulTBUFAvailNum_UART0=0;         //�������ݵ��ܳ���
    ulTBUFBegin_UART0=0;            //�������ݵĿ�ʼ��
    bUARTSending_UART0=false;       //����û�з��Ͳ���
    
    //ʹ��UART0����ս���FIFO����շ���FIFO��ʹ��UART0��FIFO
    UART_OnOffConfig(UART0,ENABLE);
    UART_FifoReset(UART0,UART_RxFIFO);
    UART_FifoReset(UART0,UART_TxFIFO);
    UART_FifoConfig(UART0,ENABLE);
    
    //��д��ʽ��
    UART_LoopBackConfig(UART0,DISABLE);
    
    //����0�����ʣ�У�鷽ʽ������
    UART_Config(UART0,gu32_BaudRateArry[gs_Setup.BaudRate_2],g_ParityArry[gs_Setup.ParityMode_2],g_StopBitsArry[gs_Setup.ParityMode_2],g_DataLenArry[gs_Setup.ParityMode_2]);
    
    //��������
    UART_RxConfig(UART0,ENABLE);
    
    //���ó�ʱ�ǿ��жϵĳ�ʱ����
//  CLR485S;
    EnableRecIRQ_UART0(); 
    DisableSendIRQ_UART0();
    
    //�����жϵ����ȼ�������ʹ��UART0�ж�
    EIC_IRQChannelPriorityConfig(UART0_IRQChannel,UART0_SIPL);
    EIC_IRQChannelConfig(UART0_IRQChannel,ENABLE);//
}

/***********************************************************************
�� �� ����void UartModbusInit_UART1(UartSet_Typedef *pUartSet)
��    �ܣ���ʼ��Modebusʹ�õĴ���
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ��Ժ���               ��    �ڣ�2014-1-22
��    �ģ�                     ��    �ڣ�
***********************************************************************/
void UartModbusInit_UART1(void)
{
    UART_Init(UART1);
        
    //������ʱ�򣬷��Ͷ�����Ч����Ϊ0����ָ�붼ָ�������ͷ����
    ulTBUFAvailNum_UART1=0;
    ulTBUFBegin_UART1=0;
    
    DelayType_UART1=DelayNo;        //��ʼ����ʱ����Ϊ����ʱ
    bOverT15_UART1=true;            //T1.5��ʱ��־
    bOverT35_UART1=true;            //T3.5��ʱ��־
    bBeginReceive_UART1=false;      //��ʼ��������
    bFinishReceive_UART1=false;     //��ʼ��������
    
    u8ModbusAddr_UART1=gs_Setup.TareNumber_1;      //���Ȱ�Modbus��ַ����Ϊͨ�õ�ַ
    ulInsertPos_UART1=0;            //���ݲ���ָ���
    ulFrameLength_UART1=0;          //���ݳ���
    ulTBUFAvailNum_UART1=0;         //�������ݵ��ܳ���
    ulTBUFBegin_UART1=0;            //�������ݵĿ�ʼ��
    bUARTSending_UART1=false;       //����û�з��Ͳ���
    
    //ʹ��UART0����ս���FIFO����շ���FIFO��ʹ��UART0��FIFO
    UART_OnOffConfig(UART1,ENABLE);
    UART_FifoReset(UART1,UART_RxFIFO);
    UART_FifoReset(UART1,UART_TxFIFO);
    UART_FifoConfig(UART1,ENABLE);
    
    //��д��ʽ��
    UART_LoopBackConfig(UART1,DISABLE);
    
    //����0�����ʣ�У�鷽ʽ������
    UART_Config(UART1,gu32_BaudRateArry[gs_Setup.BaudRate_1],g_ParityArry[gs_Setup.ParityMode_1],g_StopBitsArry[gs_Setup.ParityMode_1],g_DataLenArry[gs_Setup.ParityMode_1]);
    
    //��������
    UART_RxConfig(UART1,ENABLE);
    
    //���ó�ʱ�ǿ��жϵĳ�ʱ����
//  CLR485S;
    EnableRecIRQ_UART1(); 
    DisableSendIRQ_UART1();
    
    //�����жϵ����ȼ�������ʹ��UART0�ж�
    EIC_IRQChannelPriorityConfig(UART1_IRQChannel,UART1_SIPL);
    EIC_IRQChannelConfig(UART1_IRQChannel,ENABLE);//
}

/***********************************************************
�� �� ����u16 BuildModbusCrc16(u8 *puchMsg, u32 usDataLen) 
��    �ܣ�����У��(MODBUSЭ����У���㷨)
˵    ����
��ڲ�������
���ó���: 
�� �� ֵ����
��    �ƣ�wbj                  ��    �ڣ�2008-1-24 9:26
��    �ģ��Ժ���               ��    �ڣ�2014-1-22
***********************************************************/
u16 BuildModbusCrc16(u8 *puchMsg, u32 ulDataLen) 
{ 
    u8 uchCRCHi = 0xFF ; /* ��CRC�ֽڳ�ʼ�� */ 
    u8 uchCRCLo = 0xFF ; /* ��CRC �ֽڳ�ʼ�� */ 
    u32 ulIndex ; /* CRCѭ���е����� */ 
    
    while (ulDataLen--) /* ������Ϣ������ */ 
    { 
        ulIndex = uchCRCHi ^ *puchMsg++ ; /* ����CRC */ 
        uchCRCHi = uchCRCLo ^ auchCRCHi[ulIndex] ; 
        uchCRCLo = auchCRCLo[ulIndex] ; 
    } 
    return (uchCRCHi << 8 | uchCRCLo) ; 
}

/***********************************************************
�� �� ����void BuildCrc16(u8 *fu8p_Arry, u32 fu32_Num) 
��    �ܣ�����У��(MODBUSЭ����У���㷨)
˵    ����
��ڲ�������
���ó���: 
�� �� ֵ����
��    �ƣ��Ժ���               ��    �ڣ�2014-3-31
��    �ģ�                     ��    �ڣ�
***********************************************************/
void BuildCrc16(u8 *fu8p_Arry, u32 fu32_Num) 
{
    u16 lu16_CRCData;
    
    lu16_CRCData = BuildModbusCrc16(fu8p_Arry, fu32_Num);
    fu8p_Arry[fu32_Num] = (u8)(lu16_CRCData >> 8);
    fu8p_Arry[fu32_Num+1] = (u8)(lu16_CRCData & 0xFF);
}


/***********************************************************
�� �� ����void BuildLrc(u8 *fu8p_Arry, u32 fu32_Num) 
��    �ܣ�LRCУ��(MODBUSЭ����У���㷨)
˵    ����
��ڲ�������
���ó���: 
�� �� ֵ����
��    �ƣ��Ժ���               ��    �ڣ�2014-4-1
��    �ģ�                     ��    �ڣ�
***********************************************************/
void BuildLrc(u8 *fu8p_Arry, u32 fu32_Num)
{
    fu8p_Arry[fu32_Num] = BuildModbusLrc(fu8p_Arry, fu32_Num);
}

/***********************************************************
�� �� ����bool CheckModBusCrc16(u8 *puchMsg, u32 ulDataLen)
��    �ܣ��ж�CRCУ��
˵    ����
��ڲ�������
���ó���: 
�� �� ֵ����
��    �ƣ�wbj                  ��    �ڣ�2008-1-24 9:26
��    �ģ��Ժ���               ��    �ڣ�2014-1-22
***********************************************************/
bool CheckModBusCrc16(u8 *puchMsg, u32 ulDataLen)
{
    u16 uiCRC;
        
    uiCRC=BuildModbusCrc16(puchMsg,ulDataLen);
    
    if (uiCRC == (puchMsg[ulDataLen+1] + (puchMsg[ulDataLen] << 8)))
    {
        if (puchMsg == gu8_TxdArray_UART0)       //uart0modbusͨѶ
            gb_ModbusAnswerFlg_Uart0 = true;      //���ڲ����Զ�ƥ�书����ʹ��
        else                                        //uart1modbusͨѶ
            gb_ModbusAnswerFlg_Uart1 = true;      //���ڲ����Զ�ƥ�书����ʹ��
        return(true);
    }
    else
    {
        return(false);
    }
}

/*************************************************************
�� �� ����bool Modbus_Send_RTU(u8 *fu8p_Data, u32 fu32_Num)
��    �ܣ����ͺ���
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ��Ժ���               ��    �ڣ�2014-1-22
��    �ģ�                     ��    �ڣ�
*************************************************************/
bool Modbus_Send_RTU(u8 *fu8p_Data, u32 fu32_Num)
{
    if (fu8p_Data == gu8_TxdArray_UART0)
    {
        if (true==bUARTSending_UART0){
            return(false);
        }
        
        //����������ڷ��͵Ļ��������ǲ����н������ݵ�
        DisableSendIRQ_UART0();
        DisableRecIRQ_UART0();      //�رս����ж�
    
        Sio_485_Disable();
        gb_S485Recieve = false;     //����RS485����Modbus ASCII��ʽͨѶʱż�������жϵ����⡣ 
    
        ulTBUFAvailNum_UART0 = fu32_Num; //�������ݸ����Ĵ���   
        ulTBUFBegin_UART0 = 0; 
        
        ulFrameLength_UART0=0;
        
        bUARTSending_UART0=true;          //�������ڷ���֮��
        
        //ע��һ�����⣬ǧ��Ҫ��bUARTSending_UART0��λ��true֮ǰ���ж�
        //�����ж�һ����Ȼ�����Ͻ����պͿ��жϣ�bUARTSending_UART0
        //û�����ϣ������ϱ��ж���λFalse�ˣ��൱��û�п���
        //ͬ����ulTBUFAvailNum_UART0��ulTBUFBegin_UART0Ҳһ����
        
        EnableSendIRQ_UART0();      //�򿪷����ж�
        
        return(true);
    }
    else
    {
        if (true==bUARTSending_UART1)
            return(false);
        
        //����������ڷ��͵Ļ��������ǲ����н������ݵ�
        DisableSendIRQ_UART1();
        DisableRecIRQ_UART1();      //�رս����ж�
    
    
        ulTBUFAvailNum_UART1 = fu32_Num; //�������ݸ����Ĵ���   
        ulTBUFBegin_UART1 = 0; 
        
        ulFrameLength_UART1=0;
        
        bUARTSending_UART1=true;          //�������ڷ���֮��
        
        //ע��һ�����⣬ǧ��Ҫ��bUARTSending_UART0��λ��true֮ǰ���ж�
        //�����ж�һ����Ȼ�����Ͻ����պͿ��жϣ�bUARTSending_UART0
        //û�����ϣ������ϱ��ж���λFalse�ˣ��൱��û�п���
        //ͬ����ulTBUFAvailNum_UART0��ulTBUFBegin_UART0Ҳһ����
        
        EnableSendIRQ_UART1();      //�򿪷����ж�
        
        return(true);
    }
}

/*************************************************************
�� �� ����bool Modbus_Send_ASCII(u8 *fu8p_Data, u32 fu32_Num)
��    �ܣ����ͺ���
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ��Ժ���               ��    �ڣ�2014-4-1
��    �ģ�                     ��    �ڣ�
*************************************************************/
bool Modbus_Send_ASCII(u8 *fu8p_Data, u32 fu32_Num)
{
    if (fu8p_Data == gu8_TxdArray_UART0)
    {
        if (true==gvb_SioTxingFlg_UART0){
            return(false);
        }
    }
    else
    {
        if (true==gvb_SioTxingFlg_UART1)
            return(false);
    }
    //fu32_Num - 1 ��ΪASCII��ʽ��LRCУ��ֻռ��һ���ֽ�
    HextoASC(fu8p_Data, fu8p_Data + 1, fu32_Num - 1);
    fu8p_Data[0] = ':';   //��ʼ��
    fu8p_Data[fu32_Num*2-1] = ENDCHAR1;
    fu8p_Data[fu32_Num*2] = ENDCHAR2;
    StartSend_Com(fu8p_Data);
    return true;
}

/*********************************************************************
��������: void Modbus_Error(u8 fu8_ErrorCode, u8 *fu8p_Data)
��    ��: ModbusͨѶ�����뷵�ش���
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-22
��    ��:                      ʱ    ��: 
*********************************************************************/
void Modbus_Error(u8 fu8_ErrorCode, u8 *fu8p_Data)
{
    fu8p_Data[1] += 0x80;
    fu8p_Data[2] = fu8_ErrorCode;
    FpBuildCrcLrc(fu8p_Data, 3);
    
    FpSendRtuAscII(fu8p_Data, 5);
}

/***********************************************************
�� �� ����bool ModBus_2BinBCD(u8 *fu8p_Data, u8 *fu8p_Place, u32 fu32_Value)
��    �ܣ�MODBUSЭ���ȡҪ���͵�2�ֽ�����
˵    ����
��ڲ�������
���ó���: 
�� �� ֵ����
��    �ƣ�wbj                  ��    �ڣ�2008-1-28 14:05
��    �ģ��Ժ���               ��    �ڣ�2011-5-12
***********************************************************/
bool ModBus_2BinBCD(u8 *fu8p_Data, u8 *fu8p_Place, u32 fu32_Value)
{
    fu8p_Data[(*fu8p_Place)++] = (u8)(fu32_Value >> 8);
    fu8p_Data[(*fu8p_Place)++] = (u8)(fu32_Value & 0xff);
    gu16_ModBusReadNumber_UART0 += 2;
    if (gu16_ModBusReadNumber_UART0 >= fu8p_Data[2])
    {
        return true;
    }
    return false;
}

/***********************************************************
�� �� ����uint Modbus_ReadStateflg(u8 statetype)
��    �ܣ�Modbus�����Ǳ�״̬
˵    ��������״̬���������ش���״ֵ̬
��ڲ�����
���ó���:
�� �� ֵ��uint
��    �ƣ��Ժ���               ��    �ڣ�2014-1-22
��    �ģ�                     ��    �ڣ�
***********************************************************/
u16 Modbus_ReadStateflg(u8 statetype)
{
    u16 lu16_State = 0;

    if(statetype == 1)
    {
/*����    */ lu16_State |=(gb_RunFlg)      ?(0x0001):(0);
/*����ǰ  */ lu16_State |=(gu32_Process == T1PROCESS && gb_RunFlg == true)      ?(0x0002):(0);
/*��Ͷ    */ lu16_State |=(Sp_Disc_State(SP1_STATE))        ?(0x0004):(0);
/*��Ͷ    */ lu16_State |=(Sp_Disc_State(SP2_STATE))        ?(0x0008):(0);
/*СͶ    */ lu16_State |=(Sp_Disc_State(SP3_STATE))        ?(0x0010):(0);
/*��ֵ    */ lu16_State |=(gb_CompFlg)     ?(0x0020):(0);
/*��Ƿ��  */ lu16_State |=(gb_OverFlg || gb_UnderFlg || gb_OUOverFlg || gb_OUUnderFlg)   ?(0x0040):(0);
/*����    */ lu16_State |=(gb_AlarmFlg)          ?(0x0080):(0);
/*�д�    */ lu16_State |=(gb_PackFlg)           ?(0x0100):(0);
/*�Ĵ�    */ lu16_State |=(gb_FlapBagOutFlg || gb_FlapAllHighFlg)    ?(0x0200):(0);
/*ж��    */ lu16_State |=(Sp_Disc_State(DISC_STATE))    ?(0x0400):(0);
/*����    */ lu16_State |=(gb_NzFlg)             ?(0x0800):(0);
/*����    */ lu16_State |=(gb_FillFlg)           ?(0x1000):(0);
/*�������*/ lu16_State |=(gb_BatchOverFlg)      ?(0x2000):(0);
/*ȱ��    */ lu16_State |=(gb_LackFlg)           ?(0x4000):(0);
/*ë����  */ lu16_State |=(gb_DispNetFlg)        ?(0x8000):(0);
    }
    else if(statetype == 2)
    {
/*�ȶ�   */ lu16_State |=(gb_StabFlg)      ?(0x0001):(0);
/*���   */ lu16_State |=(gb_OflFlg)       ?(0x0002):(0);
/*����   */ lu16_State |=(gb_SigWtFlg)       ?(0x0004):(0);
/*����λ */ lu16_State |=(gb_HighFlg)      ?(0x0008):(0);
/*����λ */ lu16_State |=(gb_MiddleFlg)       ?(0x0010):(0);
/*����λ */ lu16_State |=(gb_LowFlg)    ?(0x0020):(0);
/*ж��λ */ lu16_State |=(gb_DiscCloseOKFlg)    ?(0x0040):(0);
/*�е�λ */ lu16_State |=(gb_PackOKFlg)    ?(0x0080):(0);
/*���   */ lu16_State |=(gb_DiscShakeFlg) ?(0x0100):(0);
/*����   */ lu16_State |=(gb_PrintCodeOutFlg)   ?(0x0200):(0);
/*����   */ lu16_State |=(gb_Sp3Flg)       ?(0x0400):(0);
/*���   */ lu16_State |=(gb_LiftBagFlg)   ?(0x0800):(0);
/*�ƴ�   */ lu16_State |=(gb_PushBagFlg)   ?(0x1000):(0);
    }

    return lu16_State;
}


/***********************************************************
�� �� ����u32 Modbus_WtOrMvData(BusWtType WtType)
��    �ܣ����������ͺ�����������
˵    ����
��ڲ�����
�� �� ֵ����
��    �ƣ��Ժ���               ��    �ڣ�2014-1-22
��    �ģ�                     ��    �ڣ�
***********************************************************/
u32 Modbus_WtOrMvData(BusWtType WtType)
{
    u32 lu32_Data = 0;

    switch(WtType)
    {
        case CurWt:       //��ǰ����
            lu32_Data = (gb_OflFlg == true) ? OFLVAL_MB : gu32_Wt;
            break;
        case ZeroMV:      //��������
            lu32_Data = AdToMv(gs_Cal.Zero);
            break;
        case LoadMV:      //���������
            if (gb_NetAdFlg)
                lu32_Data = 0;
            else
                lu32_Data = (gb_AdOflFlg == true) ? (OFLVAL_MB) : (AdToMv(gu32_NetAdFedValue));
            break;
        case RealMV:      //���Ժ�����
            lu32_Data = (gb_AdOflFlg == true) ? (OFLVAL_MB) : (AdToMv(gu32_AdFedValue));
            break;
        default:
            break;
    }
    return lu32_Data;
}

/*********************************************************************
��������: u8 week_day(u16 fu16_Year, u16 fu16_Month, u16 fu16_Day)
��    ��: �������ڼ�������
˵    ��: 
��    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2010-2-1
��    ��:                      ʱ    ��: 
*********************************************************************/
u8 week_day(u16 fu16_Year, u16 fu16_Month, u16 fu16_Day)
{
    u8 monthday[]={0,3,3,6,1,4,6,2,5,0,3,5};
    u16 lu16_Days = (fu16_Year-1)%7 + (fu16_Year-1)/4 - (fu16_Year-1)/100 +(fu16_Year-1)/400;
    lu16_Days += (monthday[fu16_Month-1] + fu16_Day) ;
    
    if (LeapYear(fu16_Year) && fu16_Month>2)
        lu16_Days++;
    
    return lu16_Days%7;
}

/*********************************************************************
��������: u8 get_week(void)
��    ��: 
˵    ��: 
��    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2010-2-1
��    ��:                      ʱ    ��: 
*********************************************************************/
u8 get_week(void)
{
    u16 lu16_Year = Date_Time_Read(YEAR);
    u16 lu16_Month = Date_Time_Read(MONTH);
    u16 lu16_Date = Date_Time_Read(DATE);
    
    return week_day(lu16_Year, lu16_Month, lu16_Date);
}

/*********************************************************************
��������: u8 Date_Time_Read(u8 fu8_Type)
��    ��: modbus�������ں�ʱ��
˵    ��: 
��    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2010-3-2
��    ��:                      ʱ    ��: 
*********************************************************************/
u16 Date_Time_Read(u8 fu8_Type)
{
    u16 lu16_Result;
    sTime ls_Time;
    
    RTC_ReadDateTime(&ls_Time);
    switch(fu8_Type)
    {
        case YEAR:
            lu16_Result = (ls_Time.year >> 4) * 10 + (ls_Time.year & 0x0F);
            break;
        
        case MONTH:
            lu16_Result = ((ls_Time.month & 0x1F) >> 4) * 10 + (ls_Time.month & 0x0F);
            break;
        
        case DATE:
            lu16_Result = ((ls_Time.date & 0x3F) >> 4) * 10 + (ls_Time.date & 0x0F);
            break;
            
        case WEEK:
            lu16_Result = (ls_Time.day & 0x07);
            break;
            
        case HOUR:
            lu16_Result = ((ls_Time.hour & 0x3F) >> 4) * 10 + (ls_Time.hour & 0x0F);
            break;
            
        case MINUTE:
            lu16_Result = ((ls_Time.min & 0x7F) >> 4) * 10 + (ls_Time.min & 0x0F);
            break;
            
        case SECOND:
            lu16_Result = ((ls_Time.sec & 0x7F) >> 4) * 10 + (ls_Time.sec & 0x0F);
            break;
        
        default:
            lu16_Result = 0;
            break;
    }
    
    return lu16_Result;
}

/*********************************************************************
��������: void Date_Time_Write(u8 fu8_Type, u16 fu16_Data)
��    ��: modbusд���ں�ʱ��
˵    ��: 
��    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-17
��    ��:                      ʱ    ��: 
*********************************************************************/
void Date_Time_Write(u8 fu8_Type, u16 fu16_Data)
{
    sTime ls_Time;
    
    RTC_ReadDateTime(&ls_Time);
    switch(fu8_Type)
    {
        case YEAR:
            ls_Time.year = ((fu16_Data / 10) << 4) | (fu16_Data % 10);
//            ls_Time.chWeek = get_week();                     //����ʱ�����޸�����
            break;
        
        case MONTH:
            ls_Time.month = ((fu16_Data / 10) << 4) | (fu16_Data % 10);
//            ls_Time.chWeek = get_week();                     //����ʱ�����޸�����
            break;
        
        case DATE:
            ls_Time.date = ((fu16_Data / 10) << 4) | (fu16_Data % 10);
//            ls_Time.chWeek = get_week();                     //����ʱ�����޸�����
            break;
            
        case WEEK:
            break;
            
        case HOUR:
            ls_Time.hour = ((fu16_Data / 10) << 4) | (fu16_Data % 10);
            break;
            
        case MINUTE:
            ls_Time.min = ((fu16_Data / 10) << 4) | (fu16_Data % 10);
            break;
            
        case SECOND:
            ls_Time.sec = ((fu16_Data / 10) << 4) | (fu16_Data % 10);
            break;
        
        default:
            break;
    }
    RTC_WriteDateTime(&ls_Time);
}

/*********************************************************************
��������: bool Judge_Date(u16 fu16_Date)
��    ��: �ж����������Ƿ����
˵    ��: 
��    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2010-2-1
��    ��:                      ʱ    ��: 
*********************************************************************/
bool Judge_Date(u16 fu16_Date)
{
    bool i;
    u16 lu16_Year, lu16_Month;
    //ÿ�µ�����������������
    u8 judgedate[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};           //chx 100201

    lu16_Year = 2000 + Date_Time_Read(YEAR);
    lu16_Month = Date_Time_Read(MONTH);
    
    if (fu16_Date > judgedate[lu16_Month])
    {
        i = false;
    }
    else
    {
        i = true;
    }
    
    if (LeapYear(lu16_Year) && lu16_Month == 2 && fu16_Date == 29)        //����2��29�źϷ�
    {
        i = true;
    }
    
    return i;
}

/*********************************************************************
��������: void ModBus_Write_2ByteOk(u16 *fu8p_Data)
��    ��: modbusд���Ĵ�������OK
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-16
��    ��:                      ʱ    ��: 
*********************************************************************/
void ModBus_Write_2ByteOk(u8 *fu8p_Data)
{
    FpSendRtuAscII(fu8p_Data, 8);
}

/***********************************************************
�� �� ����void ModBus_Read_RegisterDeal(u8 *fu8p_Data, fu16_Address, u16 fu16_ReadLenth)
��    �ܣ�MODBUSЭ��Ҫ��ȡ���������
˵    �����ú����Ĺ����ǿ����������Ȱ����������ú��ٷ���
��ڲ�������
���ó���: 
�� �� ֵ����
��    �ƣ��Ժ���               ��    �ڣ�2014-1-22
��    �ģ�                     ��    �ڣ�
***********************************************************/
void ModBus_Read_RegisterDeal(u8 *fu8p_Data, u16 fu16_Address, u16 fu16_ReadLenth)
{
    u8 lu8_Place;
    ULIDATA MBTemp;
    bool i, j;                 //chx 090908
        
    fu8p_Data[2] = fu16_ReadLenth * 2;
    gu16_ModBusReadNumber_UART0 = 0;
    lu8_Place = 3;
    
    if (fu8p_Data == gu8_TxdArray_UART0)
    {
        //ע��armС��ģʽ˳��
        if (gs_Setup.HiLo_2 == 1)               //������ǰ  chx 090908
        {
            i = 0;
            j = 1;
        }
        else                            //������ǰ  chx 090908
        {
            i = 1;
            j = 0;
        }
    }
    else
    {
        if (gs_Setup.HiLo_1 == 1)               //������ǰ  chx 090908
        {
            i = 0;
            j = 1;
        }
        else                            //������ǰ  chx 090908
        {
            i = 1;
            j = 0;
        }
    }
    
    switch(fu16_Address)
    {
        //RO�Ĵ���
        case 0:     //״̬1
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,Modbus_ReadStateflg(1))) break;
        case 1:     //״̬2
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,Modbus_ReadStateflg(2))) break;
        case 2:     //��ǰ����
            if ((gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gs_Setup.ResultHoldSwitch != 0 && gb_DiscWtGetedFlg == true && gb_RunFlg == true)
                MBTemp.ul = gu32_HoldWt;    //��ֵ��������ʱ��ʾ������
            else
                MBTemp.ul = Modbus_WtOrMvData(CurWt);
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 3:
            if ((gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gs_Setup.ResultHoldSwitch != 0 && gb_DiscWtGetedFlg == true && gb_RunFlg == true)
                MBTemp.ul = gu32_HoldWt;    //��ֵ��������ʱ��ʾ������
            else
            MBTemp.ul = Modbus_WtOrMvData(CurWt);
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 4:     //�ۼƴ���
            MBTemp.ul = gu32_SumNum;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 5:
            MBTemp.ul = gu32_SumNum;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 6:     //�ۼ�����
            MBTemp.ul = gu32_SumWt;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 7:
            MBTemp.ul = gu32_SumWt;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 8:    //������Ϣ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gu8_DispErrorNumber)) break;
        case 9:     //���ۼƵ�λ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)cu8_ReadUnit[gu32_SumWtUnit])) break;
        case 10:    //���ۼ�С����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gu32_SumWtPoint)) break;
        case 11:    //ʣ��������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gu32_BatchTimeCnt)) break;
        //R/W�Ĵ���
        case 12:    //��λ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)cu8_ReadUnit[gs_Cal.Unit])) break;
        case 13:    //С����λ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Cal.Point)) break;
        case 14:    //��С�ֶ�ֵ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Cal.Div)) break;
        case 15:    //������������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Cal.Sensor)) break;
        case 16:    //�������
            MBTemp.ul = gs_Cal.Cap;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i]))  break;
        case 17:
            MBTemp.ul = gs_Cal.Cap;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j]))  break;
        case 18:    //���������궨,���ص�ǰ��������
            MBTemp.ul = Modbus_WtOrMvData(ZeroMV);
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i]))  break;
        case 19:
            MBTemp.ul = Modbus_WtOrMvData(ZeroMV);
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j]))  break;
        case 20:    //����������궨�����ص�ǰ���������
            MBTemp.ul = Modbus_WtOrMvData(LoadMV);
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i]))  break;
        case 21:
            MBTemp.ul = Modbus_WtOrMvData(LoadMV);
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j]))  break;
        case 22:    //���������궨�����ص�ǰ��������
            MBTemp.ul = Modbus_WtOrMvData(ZeroMV);
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i]))  break;
        case 23:
            MBTemp.ul = Modbus_WtOrMvData(ZeroMV);
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j]))  break;
        case 24:    //����������궨��������������������ص�ǰ���Ժ�����
            MBTemp.ul = Modbus_WtOrMvData(RealMV);
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i]))  break;
        case 25:
            MBTemp.ul = Modbus_WtOrMvData(RealMV);
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j]))  break;
        case 26:    //����������궨��������������������0
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 27:
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 28:    //Ŀ��ֵ
            MBTemp.ul = gs_Rec.Target;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 29:
            MBTemp.ul = gs_Rec.Target;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 30:    //��Ͷ��ǰ��
            MBTemp.ul = gs_Rec.Large;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 31:
            MBTemp.ul = gs_Rec.Large;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 32:    //��Ͷ��ǰ��
            MBTemp.ul = gs_Rec.Middle;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 33:
            MBTemp.ul = gs_Rec.Middle;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 34:    //���ֵ
            MBTemp.ul = gs_Rec.Small;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 35:
            MBTemp.ul = gs_Rec.Small;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 36:    //����ֵ
            MBTemp.ul = gs_Rec.NearZero;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 37:
            MBTemp.ul = gs_Rec.NearZero;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 38:    //�Ĵ���ʼ����
            MBTemp.ul = gs_Rec.FlapBagWt;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 39:
            MBTemp.ul = gs_Rec.FlapBagWt;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 40:    //����ֵ
            MBTemp.ul = gs_Rec.OverValue;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 41:
            MBTemp.ul = gs_Rec.OverValue;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 42:    //Ƿ��ֵ
            MBTemp.ul = gs_Rec.UnderValue;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 43:
            MBTemp.ul = gs_Rec.UnderValue;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 44:    //T1
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.TimeT1)) break;
        case 45:    //T2b
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.TimeT2b)) break;
        case 46:    //T3
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.TimeT3)) break;
        case 47:    //T4
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.TimeT4)) break;
        case 48:    //T5
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.TimeT5)) break;
        case 49:    //T6
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.TimeT6)) break;
        case 50:    //T7
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.TimeT7)) break;
        case 51:    //�����������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.CorrectFallTime)) break;
        case 52:    //���������Χ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.CorrectFallRng1)) break;
        case 53:    //�����������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.CorrectFallRng2)) break;
        case 54:    //�Ĵ�����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.FlapBagSwitch)) break;
        case 55:    //�������Ĵ�����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.FlapBagAddNum)) break;
        case 56:    //��ֵ���Ĵ�����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.FlapBagNum)) break;
        case 57:    //�Ĵ���ʱ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.FlapBagDelay)) break;
        case 58:    //�Ĵ���Ч��ƽ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.FlapBagTimeHi)) break;
        case 59:    //�Ĵ���Ч��ƽ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.FlapBagTimeLow)) break;
        case 60:    //СͶ�㶯��Ч��ƽʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.SmallPluseHi)) break;
        case 61:    //СͶ�㶯��Ч��ƽʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.SmallPluseLow)) break;
        case 62:    //������ϴ���
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.CombinedNum)) break;
        case 63:    //�Զ�������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Setup.AutoClrZeroInterval)) break;
        case 64:    //AD�����˲�����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Setup.AdFilterLevel)) break;
        case 65:    //���ȷ�Χ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Setup.JudgeStabRng)) break;
        case 66:    //���㷶Χ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Setup.ClrZeroRng)) break;
        case 67:    //�����ٷ�Χ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Setup.TraceZeroRng)) break;
        case 68:    //�䷽��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gu32_RecNum)) break;
        case 69:    //������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gu32_BatchTime)) break;
        case 70:    //�����Ĵ������Чʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,(u16)gs_Rec.FlapBagExtTime)) break;
        case 71:    //��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,Date_Time_Read(YEAR))) break;
        case 72:    //��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,Date_Time_Read(MONTH))) break;
        case 73:    //��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,Date_Time_Read(DATE))) break;
        case 74:    //����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,get_week())) break;
        case 75:   //ʱ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,Date_Time_Read(HOUR))) break;
        case 76:   //��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,Date_Time_Read(MINUTE))) break;
        case 77:   //��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,Date_Time_Read(SECOND))) break;
        case 78:       //����/��������������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gu16_MbIoTestSwitch)) break;
        case 79:       //���뿪��������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gu16_MbIoInState)) break;
        case 80:       //�������������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gu16_MbIoOutState)) break;
        case 81:       //IN1
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoInBuf[1])) break;
        case 82:       //IN2
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoInBuf[2])) break;
        case 83:       //IN3
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoInBuf[3])) break;
        case 84:       //IN4
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoInBuf[4])) break;
        case 85:       //IN5
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoInBuf[5])) break;
        case 86:       //IN6
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoInBuf[6])) break;
        case 87:       //IN7
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoInBuf[7])) break;
        case 88:       //IN8
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoInBuf[8])) break;
        case 89:       //OUT1
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[1])) break;
        case 90:       //OUT2
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[2])) break;
        case 91:       //OUT3
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[3])) break;
        case 92:       //OUT4
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[4])) break;
        case 93:       //OUT5
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[5])) break;
        case 94:       //OUT6
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[6])) break;
        case 95:       //OUT7
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[7])) break;
        case 96:       //OUT8
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[8])) break;
        case 97:       //OUT9
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[9])) break;
        case 98:       //OUT10
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[10])) break;
        case 99:       //OUT11
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[11])) break;
        case 100:       //OUT12
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,*gu32p_IoOutBuf[12])) break;
        case 101:    //����ģʽ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.TareMode)) break;
        case 102:    //�޶�ë����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.GorNMode)) break;
        case 103:    //���Ϸ�ʽ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.FeedMode)) break;
        case 104:    //����״̬���ȳ�ʱʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.JudgeStabOverTime)) break;
        case 105:    //����ʾ����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.AuxDispType)) break;
        case 106:    //ж���˲�����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.AdFilterLevelDisc)) break;
        case 107:    //��ֵ�˲�����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.AdFilterLevelComp)) break;
        case 108:    //AD�����ٶ�
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.AdSamplingRate)) break;
        case 109:    //�ϵ��Զ����㿪��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.PowerOnZeroSwitch)) break;
        case 110:    //�ֶ�ж���ۼƿ���
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.DiscSumSwitch)) break;
        case 111:    //�ж���ֵ�������ֿ���
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.ResultHoldSwitch)) break;
        case 112:    //�ۼƲ�ѯ���뿪��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.SumCheckCodeSwitch)) break;
        case 113:    //�ۼ�������뿪��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.SumClrCodeSwitch)) break;
        case 114:    //�ۼƷ�Χ��չ����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.SumExtendSwitch)) break;
        case 115:    //���п�1�Զ���ӡ����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.PrintSwitch_1)) break;
        case 116:    //���п�1��ӡ������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.PrintType_1)) break;
        case 117:    //���п�1��ӡ����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.PrintLanguage_1)) break;
        case 118:    //���п�1��ӡ��ֽ����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.PrintBlankRows_1)) break;
        case 119:    //���п�2�Զ���ӡ����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.PrintSwitch_2)) break;
        case 120:    //���п�2��ӡ������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.PrintType_2)) break;
        case 121:    //���п�2��ӡ����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.PrintLanguage_2)) break;
        case 122:    //���п�2��ӡ��ֽ����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.PrintBlankRows_2)) break;
        case 123:    //˫�޶��ӻ���ģʽͬʱ�ɴ�����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.No2PackOffTwoSwitch)) break;
        case 124:    //���ͻ�������ʱʱ��t13
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.No2ConveyorDelayTime)) break;
        case 125:    //���ͻ�����ʱ��t14
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.No2ConveyorRunTime)) break;
        case 126:    //�ٴμд���ʱ��������ʱ��t15
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Setup.No2AddAgainDelayTime)) break;
        case 127:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 128:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 129:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 130:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 131:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 132:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 133:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 134:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 135:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 136:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 137:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 138:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 139:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 140:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 141:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 142:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 143:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
                
        case 144:    //T2_a
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.TimeT2a)) break;
        case 145:    //T9�����ʱʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.TimeT9)) break;
        case 146:    //T10��������Чʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.TimeT10)) break;
        case 147:    //T11�ƴ���ʱʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.TimeT11)) break;
        case 148:    //T12�ƴ������Чʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.TimeT12)) break;
        case 149:    //ж����򿪹�
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.DiscShakeSwitch)) break;
        case 150:    //ж�ϳ�ʱʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.DiscEffTime)) break;
        case 151:    //ж�������Чʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.DiscShakeTimeHi)) break;
        case 152:    //ж�������Чʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.DiscShakeTimeLow)) break;
        case 153:    //ж��������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.DiscShakeNum)) break;
        case 154:    //������ƹ��ܿ���
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.PrintCodeSwitch)) break;
        case 155:    //����������ʱTP1
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.PrintCodeRunDelay)) break;
        case 156:    //���������Чʱ��TP2
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.PrintCodeTime)) break;
        case 157:    //����ʱ������ж��/���� ����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.SheildDiscSwitch)) break;
        case 158:    //��Ƿ�������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.OUSwitch)) break;
        case 159:    //��Ƿ����ͣ����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.OUStopSwitch)) break;
        case 160:    //�����������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.CorrectFallSwitch)) break;
        case 161:    //СͶ�㶯����
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_Rec.SmallPluseSwitch)) break;
                
        case 162:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 163:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 164:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 165:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 166:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 167:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 168:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 169:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 170:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 171:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 172:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 173:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 174:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 175:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 176:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 177:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 178:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 179:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 180:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 181:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 182:    //
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
                
        case 183:    //���ۼ����ݴ�ӡ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 184:    //�䷽���ñ���ӡ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 185:    //�䷽�ۼƱ�����ӡ
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 186:    //�ָ���������
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 187:
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
        case 188:    //�ϴΰ�װ���
            MBTemp.ul = gu32_MbLastResult;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 189:
            MBTemp.ul = gu32_MbLastResult;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 190:   //�䷽1�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[1];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 191:
            MBTemp.ul = gu32_SumNum_Rec[1];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 192:   //�䷽1�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[1];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 193:
            MBTemp.ul = gu32_SumWt_Rec[1];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 194:   //�䷽2�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[2];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 195:
            MBTemp.ul = gu32_SumNum_Rec[2];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 196:   //�䷽2�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[2];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 197:
            MBTemp.ul = gu32_SumWt_Rec[2];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 198:   //�䷽3�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[3];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 199:
            MBTemp.ul = gu32_SumNum_Rec[3];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 200:   //�䷽3�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[3];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 201:
            MBTemp.ul = gu32_SumWt_Rec[3];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 202:   //�䷽4�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[4];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 203:
            MBTemp.ul = gu32_SumNum_Rec[4];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 204:   //�䷽4�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[4];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 205:
            MBTemp.ul = gu32_SumWt_Rec[4];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 206:   //�䷽5�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[5];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 207:
            MBTemp.ul = gu32_SumNum_Rec[5];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 208:   //�䷽5�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[5];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 209:
            MBTemp.ul = gu32_SumWt_Rec[5];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 210:   //�䷽6�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[6];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 211:
            MBTemp.ul = gu32_SumNum_Rec[6];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 212:   //�䷽6�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[6];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 213:
            MBTemp.ul = gu32_SumWt_Rec[6];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 214:   //�䷽7�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[7];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 215:
            MBTemp.ul = gu32_SumNum_Rec[7];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 216:   //�䷽7�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[7];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 217:
            MBTemp.ul = gu32_SumWt_Rec[7];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 218:   //�䷽8�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[8];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 219:
            MBTemp.ul = gu32_SumNum_Rec[8];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 220:   //�䷽8�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[8];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 221:
            MBTemp.ul = gu32_SumWt_Rec[8];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 222:   //�䷽9�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[9];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 223:
            MBTemp.ul = gu32_SumNum_Rec[9];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 224:   //�䷽9�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[9];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 225:
            MBTemp.ul = gu32_SumWt_Rec[9];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 226:   //�䷽10�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[10];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 227:
            MBTemp.ul = gu32_SumNum_Rec[10];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 228:   //�䷽10�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[10];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 229:
            MBTemp.ul = gu32_SumWt_Rec[10];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 230:   //�䷽11�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[11];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 231:
            MBTemp.ul = gu32_SumNum_Rec[11];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 232:   //�䷽11�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[11];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 233:
            MBTemp.ul = gu32_SumWt_Rec[11];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 234:   //�䷽12�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[12];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 235:
            MBTemp.ul = gu32_SumNum_Rec[12];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 236:   //�䷽12�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[12];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 237:
            MBTemp.ul = gu32_SumWt_Rec[12];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 238:   //�䷽13�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[13];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 239:
            MBTemp.ul = gu32_SumNum_Rec[13];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 240:   //�䷽13�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[13];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 241:
            MBTemp.ul = gu32_SumWt_Rec[13];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 242:   //�䷽14�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[14];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 243:
            MBTemp.ul = gu32_SumNum_Rec[14];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 244:   //�䷽14�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[14];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 245:
            MBTemp.ul = gu32_SumWt_Rec[14];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 246:   //�䷽15�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[15];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 247:
            MBTemp.ul = gu32_SumNum_Rec[15];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 248:   //�䷽15�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[15];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 249:
            MBTemp.ul = gu32_SumWt_Rec[15];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 250:   //�䷽16�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[16];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 251:
            MBTemp.ul = gu32_SumNum_Rec[16];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 252:   //�䷽16�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[16];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 253:
            MBTemp.ul = gu32_SumWt_Rec[16];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 254:   //�䷽17�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[17];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 255:
            MBTemp.ul = gu32_SumNum_Rec[17];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 256:   //�䷽17�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[17];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 257:
            MBTemp.ul = gu32_SumWt_Rec[17];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 258:   //�䷽18�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[18];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 259:
            MBTemp.ul = gu32_SumNum_Rec[18];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 260:   //�䷽18�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[18];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 261:
            MBTemp.ul = gu32_SumWt_Rec[18];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 262:   //�䷽19�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[19];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 263:
            MBTemp.ul = gu32_SumNum_Rec[19];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 264:   //�䷽19�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[19];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 265:
            MBTemp.ul = gu32_SumWt_Rec[19];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 266:   //�䷽20�ۼƴ���
            MBTemp.ul = gu32_SumNum_Rec[20];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 267:
            MBTemp.ul = gu32_SumNum_Rec[20];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 268:   //�䷽20�ۼ�����
            MBTemp.ul = gu32_SumWt_Rec[20];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 269:
            MBTemp.ul = gu32_SumWt_Rec[20];
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        case 270:   //���ʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_DebugRunTime.u32Sp1Time)) break;
        case 271:   //�м�ʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_DebugRunTime.u32Sp2Time)) break;
        case 272:   //����ʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_DebugRunTime.u32Sp3Time)) break;
        case 273:   //��������ֵʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_DebugRunTime.u32RunCmpTime)) break;
        case 274:   //һ�μ��Ϲ���ʱ��
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,gs_DebugRunTime.u32OneTareTime)) break;
        case 275:   //��ֵʱ������
            MBTemp.ul = gu32_HoldWt;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[i])) break;
        case 276:   //��ֵʱ������
            MBTemp.ul = gu32_HoldWt;
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,MBTemp.ui[j])) break;
        default:
            if (ModBus_2BinBCD(fu8p_Data,&lu8_Place,0)) break;
            break;
    }
    FpBuildCrcLrc(fu8p_Data, (fu8p_Data[2] + 3));
    
    FpSendRtuAscII(fu8p_Data, fu8p_Data[2] + 5);
}

/*********************************************************************
��������: void ModBus_Read_Register(u8 *fu8p_Data)
��    ��: modbus�����ּĴ����ĺ������ж�
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-22
��    ��:                      ʱ    ��: 
*********************************************************************/
void ModBus_Read_Register(u8 *fu8p_Data)
{
    u16 lu16_Address;
    u16 lu16_ReadLenth;
    u16 lu16_ReadNum;
    
    lu16_Address = (fu8p_Data[2] << 8) + fu8p_Data[3];
    lu16_ReadLenth = (fu8p_Data[4] << 8) + fu8p_Data[5];
    lu16_ReadNum = R2BYTETOTAL - lu16_Address;
    
    //�ɶ���ַ��Χ�ĺ������ж�
    if ((lu16_Address <= R2BYTETOTAL - 1)
        && (lu16_ReadLenth <= lu16_ReadNum) && (lu16_ReadLenth <= READMAXNUM))
    {
        ModBus_Read_RegisterDeal(fu8p_Data, lu16_Address, lu16_ReadLenth);
    }
    else
    {
        Modbus_Error(DATAPLACEERRO, fu8p_Data);
    }
}


/*********************************************************************
��������: u16 ModBus_Write_2ByteDeal(u16 *fu8p_Data)
��    ��: modbusд���Ĵ�����ַ����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-22
��    ��:                      ʱ    ��: 
*********************************************************************/
u16 ModBus_Write_2ByteDeal(u8 *fu8p_Data)
{
    u16 lu16_Address;
    u16 lu16_WriteData;
    u32 lu32_Temp;
    
    //д��ĵ�ַ
    lu16_Address = fu8p_Data[2];
    lu16_Address <<= 8;
    lu16_Address += fu8p_Data[3];   
    //д�������
    lu16_WriteData = fu8p_Data[4];
    lu16_WriteData <<= 8;
    lu16_WriteData += fu8p_Data[5];

    switch (lu16_Address)
    {
        case 12:        //�궨��λ
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if (lu16_WriteData  <= 3)
            {
                if (lu16_WriteData != cu8_ReadUnit[gs_Cal.Unit])
                {
                    gs_Cal.Unit = cu8_WriteUnit[lu16_WriteData];
                    FRAM_WriteDW(FMAddr_CalUnit, gs_Cal.Unit);
                    ClrSum();
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 13:        //�궨С����
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if (lu16_WriteData <= 4)
            {
                if (lu16_WriteData != gs_Cal.Point)
                {
                    gs_Cal.Point = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_CalPoint, gs_Cal.Point);
                    ClrSum();
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 14:        //��С�ֶ�ֵ
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if ((lu16_WriteData==1)||(lu16_WriteData==2)||(lu16_WriteData==5)||
               (lu16_WriteData==10)||(lu16_WriteData==20)|(lu16_WriteData==50))
            {
                if (lu16_WriteData != gs_Cal.Div)
                {
//                    UpdateRecF1(lu16_WriteData);  //�ֶ��޸ĸ����䷽F1  //for test
                    lu32_Temp = FRAM_ReadDW(FMAddr_CalDiv);
                    //��Ҫ�����ֶ�,��׷�����
                    gs_Cal.ADK *= (float)lu16_WriteData;    //�·ֶ�ֵ=ԭ�ֶ�ֵ*new dd/old dd
                    gs_Cal.ADK /= (float)gs_Cal.Div;
                    FRAM_WriteFloat(FMAddr_CalADK, gs_Cal.ADK);
                
                    //����׷�����:�����ֶ�ֵ��,�����0,��Ȼ��ʾ��
                    gu32_FloatZero *= gs_Cal.Div;
                    gu32_FloatZero /= lu16_WriteData;
                    //�����µķֶ�ֵ
                    gs_Cal.Div = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_CalDiv, gs_Cal.Div);
    
                    //�ֶ�ֵ��С���������̴���
                    if (gs_Cal.Div < lu32_Temp)                        //�ֶ�ֵ�ɴ��Сʱ���������Ҫ����
                    {
                        if (gs_Cal.Cap > (gs_Cal.Div * 100000))
                        {
                            gs_Cal.Cap = gs_Cal.Div * 100000;
                            FRAM_WriteDW(FMAddr_CalCap, gs_Cal.Cap);
                        }
                    }
                    else if (gs_Cal.Div > gs_Cal.Cap)            //�޸ķֶȺ�����С�ڷֶȣ����޸�����Ϊ�ֶ�ֵ
                    {
                        gs_Cal.Cap = gs_Cal.Div;
                        FRAM_WriteDW(FMAddr_CalCap, gs_Cal.Cap);
                    }
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 15:        //������������
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if ((lu16_WriteData >= 1) && (lu16_WriteData <= 3))
            {
                if (lu16_WriteData != gs_Cal.Sensor)
                {
                    gs_Cal.Sensor = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_CalSensor, gs_Cal.Sensor);
                }
                return RESPONSEOK;
            }
            else 
                return DATAERRO;
        case 44:        //T1
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT1)
                {
                    gs_Rec.TimeT1 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT1(gu32_RecNum), gs_Rec.TimeT1);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 45:        //T2b
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT2b)
                {
                    gs_Rec.TimeT2b = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT2b(gu32_RecNum), gs_Rec.TimeT2b);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 46:        //T3
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT3)
                {
                    gs_Rec.TimeT3 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT3(gu32_RecNum), gs_Rec.TimeT3);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 47:        //T4
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT4)
                {
                    gs_Rec.TimeT4 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT4(gu32_RecNum), gs_Rec.TimeT4);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 48:        //T5
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT5)
                {
                    gs_Rec.TimeT5 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT5(gu32_RecNum), gs_Rec.TimeT5);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 49:        //T6
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT6)
                {
                    gs_Rec.TimeT6 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT6(gu32_RecNum), gs_Rec.TimeT6);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 50:        //T7
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT7)
                {
                    gs_Rec.TimeT7 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT7(gu32_RecNum), gs_Rec.TimeT7);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 51:        //�����������
            if (lu16_WriteData <= 99)
            {
                if (lu16_WriteData != gs_Rec.CorrectFallTime)
                {
                    gs_Rec.CorrectFallTime = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_CorrectFallTime(gu32_RecNum), gs_Rec.CorrectFallTime);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 52:        //���������Χ
            if (lu16_WriteData <= 99)
            {
                if (lu16_WriteData != gs_Rec.CorrectFallRng1)
                {
                    gs_Rec.CorrectFallRng1 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_CorrectFallRng1(gu32_RecNum), gs_Rec.CorrectFallRng1);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 53:        //�����������
            if ((lu16_WriteData >= 1) && (lu16_WriteData <= 3))
            {
                if (lu16_WriteData != gs_Rec.CorrectFallRng2)
                {
                    gs_Rec.CorrectFallRng2 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_CorrectFallRng2(gu32_RecNum), gs_Rec.CorrectFallRng2);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 54:        //�Ĵ�����
            if (lu16_WriteData <= 3)
            {
                if (lu16_WriteData != gs_Rec.FlapBagSwitch)
                {
                    gs_Rec.FlapBagSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_FlapBagSwitch(gu32_RecNum), gs_Rec.FlapBagSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 55:        //�������Ĵ�����
            if (lu16_WriteData <= 99)
            {
                if (lu16_WriteData != gs_Rec.FlapBagAddNum)
                {
                    gs_Rec.FlapBagAddNum = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_FlapBagAddNum(gu32_RecNum), gs_Rec.FlapBagAddNum);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 56:        //��ֵ���Ĵ�����
            if (lu16_WriteData <= 99)
            {
                if (lu16_WriteData != gs_Rec.FlapBagNum)
                {
                    gs_Rec.FlapBagNum = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_FlapBagNum(gu32_RecNum), gs_Rec.FlapBagNum);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 57:        //�Ĵ���ʱ
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.FlapBagDelay)
                {
                    gs_Rec.FlapBagDelay = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_FlapBagDelay(gu32_RecNum), gs_Rec.FlapBagDelay);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 58:        //�Ĵ���Ч��ƽʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.FlapBagTimeHi)
                {
                    gs_Rec.FlapBagTimeHi = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_FlapBagTimeHi(gu32_RecNum), gs_Rec.FlapBagTimeHi);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 59:        //�Ĵ���Ч��ƽʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.FlapBagTimeLow)
                {
                    gs_Rec.FlapBagTimeLow = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_FlapBagTimeLow(gu32_RecNum), gs_Rec.FlapBagTimeLow);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 60:        //СͶ�㶯��Чʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.SmallPluseHi)
                {
                    gs_Rec.SmallPluseHi = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_SmallPluseHi(gu32_RecNum), gs_Rec.SmallPluseHi);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 61:        //СͶ�㶯��Чʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.SmallPluseLow)
                {
                    gs_Rec.SmallPluseLow = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_SmallPluseLow(gu32_RecNum), gs_Rec.SmallPluseLow);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 62:        //������ϴ���
            if (lu16_WriteData <= 99)
            {
                if (lu16_WriteData != gs_Rec.CombinedNum)
                {
                    gs_Rec.CombinedNum = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_CombinedNum(gu32_RecNum), gs_Rec.CombinedNum);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 63:        //�Զ�������
            if (lu16_WriteData <= 99)
            {
                if (lu16_WriteData != gs_Setup.AutoClrZeroInterval)
                {
                    gs_Setup.AutoClrZeroInterval = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_AutoClrZeroInterval, gs_Setup.AutoClrZeroInterval);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 64:        //AD�����˲�����
            if (lu16_WriteData <= 9)
            {
                if (lu16_WriteData != gs_Setup.AdFilterLevel)
                {
                    gs_Setup.AdFilterLevel = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_AdFilterLevel, gs_Setup.AdFilterLevel);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 65:        //���ȷ�Χ
            if (lu16_WriteData <= 99)
            {
                if (lu16_WriteData != gs_Setup.JudgeStabRng)
                {
                    gs_Setup.JudgeStabRng = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_JudgeStabRng, gs_Setup.JudgeStabRng);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 66:        //���㷶Χ
            if ((lu16_WriteData >= 1) && (lu16_WriteData <= 99))
            {
                if (lu16_WriteData != gs_Setup.ClrZeroRng)
                {
                    gs_Setup.ClrZeroRng = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_ClrZeroRng, gs_Setup.ClrZeroRng);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 67:        //�����ٷ�Χ
            if (lu16_WriteData <= 9)
            {
                if (lu16_WriteData != gs_Setup.TraceZeroRng)
                {
                    gs_Setup.TraceZeroRng = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TraceZeroRng, gs_Setup.TraceZeroRng);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 68:        //�䷽��
            if (lu16_WriteData <= 20 && lu16_WriteData >= 1)
            {
                if (lu16_WriteData != gu32_RecNum)
                {
                    gu32_RecNum = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_RecNum, gu32_RecNum);
                    Read_RecipeData(gu32_RecNum);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 69:        //������
            if (lu16_WriteData <= 9999)
            {
                if (lu16_WriteData != gu32_BatchTime)
                {
                    gu32_BatchTime = lu16_WriteData;
                    gu32_BatchTimeCnt = gu32_BatchTime;
                    FRAM_WriteDW(FMAddr_BatchTime, gu32_BatchTime);
                    FRAM_WriteDW(FMAddr_BatchTimeCnt, gu32_BatchTimeCnt);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 70:        //�����Ĵ������Чʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.FlapBagExtTime)
                {
                    gs_Rec.FlapBagExtTime = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_FlapBagExtTime(gu32_RecNum), gs_Rec.FlapBagExtTime);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 71:        //��
            if (lu16_WriteData <= 99)
            {
                Date_Time_Write(YEAR, lu16_WriteData);
                FRAM_WriteDW(FMAddr_CmpYear, lu16_WriteData);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 72:        //��
            if ((lu16_WriteData >= 1) && (lu16_WriteData <= 12))
            {
                Date_Time_Write(MONTH, lu16_WriteData);
                FRAM_WriteDW(FMAddr_CmpMonth, lu16_WriteData);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 73:        //�� 
            if (Judge_Date(lu16_WriteData))
            {
                Date_Time_Write(DATE, lu16_WriteData);
                FRAM_WriteDW(FMAddr_CmpDate, lu16_WriteData);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 74:        //����
            return RESPONSEOK;
        case 75:       //ʱ
            if (lu16_WriteData <= 23)
            {
                Date_Time_Write(HOUR, lu16_WriteData);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 76:       //��
            if (lu16_WriteData <= 59)
            {
                Date_Time_Write(MINUTE, lu16_WriteData);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 77:       //��
            if (lu16_WriteData <= 59)
            {
                Date_Time_Write(SECOND, lu16_WriteData);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 78:       //����/��������������
            if (lu16_WriteData <= 1)
            {
                if (gb_RunFlg == false)
                {
                    if (lu16_WriteData != gu16_MbIoTestSwitch)
                    {
                        gu16_MbIoOutTest = 0;
                        gu16_MbIoTestSwitch = lu16_WriteData;
                    }
                    return RESPONSEOK;
                }
                else
                    return NOSUCCESS;
            }
            else
                return DATAERRO;
        case 79:       //���뿪��������
            return NOSUCCESS;
        case 80:       //�������������
            if (gu16_MbIoTestSwitch == 1)
            {
                gu16_MbIoOutTest = lu16_WriteData;
                return RESPONSEOK;
            }
            else
            {
                gu16_MbIoOutTest = 0;
                return NOSUCCESS;
            }
        //�������Զ���
        case 81:       //IN1
            if (lu16_WriteData <= IO_INMAX)
            {
                *gu32p_IoInBuf[1] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_IN, 1, gs_Setup.TareMode), *gu32p_IoInBuf[1]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 82:       //IN2
            if (lu16_WriteData <= IO_INMAX)
            {
                *gu32p_IoInBuf[2] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_IN, 2, gs_Setup.TareMode), *gu32p_IoInBuf[2]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 83:       //IN3
            if (lu16_WriteData <= IO_INMAX)
            {
                *gu32p_IoInBuf[3] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_IN, 3, gs_Setup.TareMode), *gu32p_IoInBuf[3]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 84:       //IN4
            if (lu16_WriteData <= IO_INMAX)
            {
                *gu32p_IoInBuf[4] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_IN, 4, gs_Setup.TareMode), *gu32p_IoInBuf[4]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 85:       //IN5
            if (lu16_WriteData <= IO_INMAX)
            {
                *gu32p_IoInBuf[5] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_IN, 5, gs_Setup.TareMode), *gu32p_IoInBuf[5]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 86:       //IN6
            if (lu16_WriteData <= IO_INMAX)
            {
                *gu32p_IoInBuf[6] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_IN, 6, gs_Setup.TareMode), *gu32p_IoInBuf[6]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 87:       //IN7
            if (lu16_WriteData <= IO_INMAX)
            {
                *gu32p_IoInBuf[7] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_IN, 7, gs_Setup.TareMode), *gu32p_IoInBuf[7]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 88:       //IN8
            if (lu16_WriteData <= IO_INMAX)
            {
                *gu32p_IoInBuf[8] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_IN, 8, gs_Setup.TareMode), *gu32p_IoInBuf[8]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 89:       //OUT1
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[1] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 1, gs_Setup.TareMode), *gu32p_IoOutBuf[1]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 90:       //OUT2
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[2] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 2, gs_Setup.TareMode), *gu32p_IoOutBuf[2]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 91:       //OUT3
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[3] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 3, gs_Setup.TareMode), *gu32p_IoOutBuf[3]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 92:       //OUT4
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[4] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 4, gs_Setup.TareMode), *gu32p_IoOutBuf[4]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 93:       //OUT5
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[5] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 5, gs_Setup.TareMode), *gu32p_IoOutBuf[5]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 94:       //OUT6
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[6] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 6, gs_Setup.TareMode), *gu32p_IoOutBuf[6]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 95:       //OUT7
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[7] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 7, gs_Setup.TareMode), *gu32p_IoOutBuf[7]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 96:       //OUT8
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[8] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 8, gs_Setup.TareMode), *gu32p_IoOutBuf[8]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 97:       //OUT9
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[9] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 9, gs_Setup.TareMode), *gu32p_IoOutBuf[9]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 98:       //OUT10
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[10] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 10, gs_Setup.TareMode), *gu32p_IoOutBuf[10]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 99:       //OUT11
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[11] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 11, gs_Setup.TareMode), *gu32p_IoOutBuf[11]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 100:       //OUT12
            if (lu16_WriteData <= IO_OUTMAX)
            {
                *gu32p_IoOutBuf[12] = lu16_WriteData;
                FRAM_WriteDW(GetIoAddr( IO_OUT, 12, gs_Setup.TareMode), *gu32p_IoOutBuf[12]);
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 101:        //����ģʽ
            if (lu16_WriteData <= 5)
            {
                if (lu16_WriteData != gs_Setup.TareMode)
                {
                    gs_Setup.TareMode = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TareMode, gs_Setup.TareMode);
                    TareModeChange(gs_Setup.TareMode);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 102:        //�޶�ë����ģʽ
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.GorNMode)
                {
                    gs_Setup.GorNMode = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_GorNMode, gs_Setup.GorNMode);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 103:        //���Ϸ�ʽѡ��
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.FeedMode)
                {
                    gs_Setup.FeedMode = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_FeedMode, gs_Setup.FeedMode);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 104:        //����״̬���ȳ�ʱʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Setup.JudgeStabOverTime)
                {
                    gs_Setup.JudgeStabOverTime = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_JudgeStabOverTime, gs_Setup.JudgeStabOverTime);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 105:        //����ʾ����
            if (lu16_WriteData <= 2)
            {
                if (lu16_WriteData != gs_Setup.AuxDispType)
                {
                    gs_Setup.AuxDispType = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_AuxDispType, gs_Setup.AuxDispType);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 106:        //ж���˲�����
            if (lu16_WriteData <= 9)
            {
                if (lu16_WriteData != gs_Setup.AdFilterLevelDisc)
                {
                    gs_Setup.AdFilterLevelDisc = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_AdFilterLevelDisc, gs_Setup.AdFilterLevelDisc);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 107:        //��ֵ�˲�����
            if (lu16_WriteData <= 9)
            {
                if (lu16_WriteData != gs_Setup.AdFilterLevelComp)
                {
                    gs_Setup.AdFilterLevelComp = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_AdFilterLevelComp, gs_Setup.AdFilterLevelComp);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 108:        //AD�����ٶ�
            if (lu16_WriteData <= 3)
            {
                if (lu16_WriteData != gs_Setup.AdSamplingRate)
                {
                    gs_Setup.AdSamplingRate = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_AdSamplingRate, gs_Setup.AdSamplingRate);
                    gb_AdOKFlg = AD_Init(gs_Setup.AdSamplingRate);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 109:        //�ϵ��Զ����㿪��
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.PowerOnZeroSwitch)
                {
                    gs_Setup.PowerOnZeroSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PowerOnZeroSwitch, gs_Setup.PowerOnZeroSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 110:        //�ֶ�ж���ۼƿ���
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.DiscSumSwitch)
                {
                    gs_Setup.DiscSumSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_DiscSumSwitch, gs_Setup.DiscSumSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 111:        //�ֶ�ж���ۼƿ���
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.ResultHoldSwitch)
                {
                    gs_Setup.ResultHoldSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_ResultHoldSwitch, gs_Setup.ResultHoldSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 112:        //�ۼƲ�ѯ���뿪��
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.SumCheckCodeSwitch)
                {
                    gs_Setup.SumCheckCodeSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_SumCheckCodeSwitch, gs_Setup.SumCheckCodeSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 113:        //�ۼ�������뿪��
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.SumClrCodeSwitch)
                {
                    gs_Setup.SumClrCodeSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_SumClrCodeSwitch, gs_Setup.SumClrCodeSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 114:        //�ۼƷ�Χ��չ����
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.SumExtendSwitch)
                {
                    gs_Setup.SumExtendSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_SumExtendSwitch, gs_Setup.SumExtendSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 115:        //���п�1�Զ���ӡ����
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.PrintSwitch_1)
                {
                    gs_Setup.PrintSwitch_1 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PrintSwitch_1, gs_Setup.PrintSwitch_1);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 116:        //���п�1��ӡ����ʽ
            if (lu16_WriteData <= 2)
            {
                if (lu16_WriteData != gs_Setup.PrintType_1)
                {
                    gs_Setup.PrintType_1 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PrintType_1, gs_Setup.PrintType_1);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 117:        //���п�1��ӡ����
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.PrintLanguage_1)
                {
                    gs_Setup.PrintLanguage_1 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PrintLanguage_1, gs_Setup.PrintLanguage_1);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 118:        //���п�1��ӡ��ֽ����
            if (lu16_WriteData <= 9)
            {
                if (lu16_WriteData != gs_Setup.PrintBlankRows_1)
                {
                    gs_Setup.PrintBlankRows_1 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PrintBlankRows_1, gs_Setup.PrintBlankRows_1);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 119:        //���п�2�Զ���ӡ����
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.PrintSwitch_2)
                {
                    gs_Setup.PrintSwitch_2 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PrintSwitch_2, gs_Setup.PrintSwitch_2);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 120:        //���п�2��ӡ����ʽ
            if (lu16_WriteData <= 2)
            {
                if (lu16_WriteData != gs_Setup.PrintType_2)
                {
                    gs_Setup.PrintType_2 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PrintType_2, gs_Setup.PrintType_2);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 121:        //���п�2��ӡ����
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Setup.PrintLanguage_2)
                {
                    gs_Setup.PrintLanguage_2 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PrintLanguage_2, gs_Setup.PrintLanguage_2);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 122:        //���п�2��ӡ��ֽ����
            if (lu16_WriteData <= 9)
            {
                if (lu16_WriteData != gs_Setup.PrintBlankRows_2)
                {
                    gs_Setup.PrintBlankRows_2 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PrintBlankRows_2, gs_Setup.PrintBlankRows_2);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 123:        //˫�޶��ӻ���ģʽͬʱ�ɴ�����
            if (lu16_WriteData <= 2)
            {
                if (lu16_WriteData != gs_Setup.No2PackOffTwoSwitch)
                {
                    gs_Setup.No2PackOffTwoSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_No2PackOffTwoSwitch, gs_Setup.No2PackOffTwoSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 124:        //���ͻ�������ʱʱ��t13
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Setup.No2ConveyorDelayTime)
                {
                    gs_Setup.No2ConveyorDelayTime = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_No2ConveyorDelayTime, gs_Setup.No2ConveyorDelayTime);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 125:        //���ͻ�����ʱ��t14
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Setup.No2ConveyorRunTime)
                {
                    gs_Setup.No2ConveyorRunTime = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_No2ConveyorRunTime, gs_Setup.No2ConveyorRunTime);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 126:        //�ٴμд���ʱ��������ʱ��t15
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Setup.No2AddAgainDelayTime)
                {
                    gs_Setup.No2AddAgainDelayTime = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_No2AddAgainDelayTime, gs_Setup.No2AddAgainDelayTime);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
                
        case 144:        //T2_a
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT2a)
                {
                    gs_Rec.TimeT2a = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT2a(gu32_RecNum), gs_Rec.TimeT2a);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 145:        //T9�����ʱʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT9)
                {
                    gs_Rec.TimeT9 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT9(gu32_RecNum), gs_Rec.TimeT9);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 146:        //T10��������Чʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT10)
                {
                    gs_Rec.TimeT10 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT10(gu32_RecNum), gs_Rec.TimeT10);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 147:        //T11�ƴ���ʱʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT11)
                {
                    gs_Rec.TimeT11 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT11(gu32_RecNum), gs_Rec.TimeT11);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 148:        //T12�ƴ������Чʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.TimeT12)
                {
                    gs_Rec.TimeT12 = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_TimeT12(gu32_RecNum), gs_Rec.TimeT12);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 149:        //ж����򿪹�
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Rec.DiscShakeSwitch)
                {
                    gs_Rec.DiscShakeSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_DiscShakeSwitch(gu32_RecNum), gs_Rec.DiscShakeSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 150:        //ж�ϳ�ʱʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.DiscEffTime)
                {
                    gs_Rec.DiscEffTime = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_DiscEffTime(gu32_RecNum), gs_Rec.DiscEffTime);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 151:        //ж�������Чʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.DiscShakeTimeHi)
                {
                    gs_Rec.DiscShakeTimeHi = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_DiscShakeTimeHi(gu32_RecNum), gs_Rec.DiscShakeTimeHi);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 152:        //ж�������Чʱ��
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.DiscShakeTimeLow)
                {
                    gs_Rec.DiscShakeTimeLow = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_DiscShakeTimeLow(gu32_RecNum), gs_Rec.DiscShakeTimeLow);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 153:        //ж��������
            if (lu16_WriteData <= 99)
            {
                if (lu16_WriteData != gs_Rec.DiscShakeNum)
                {
                    gs_Rec.DiscShakeNum = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_DiscShakeNum(gu32_RecNum), gs_Rec.DiscShakeNum);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 154:        //������ƹ��ܿ���
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Rec.PrintCodeSwitch)
                {
                    gs_Rec.PrintCodeSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PrintCodeSwitch(gu32_RecNum), gs_Rec.PrintCodeSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 155:        //����������ʱTP1
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.PrintCodeRunDelay)
                {
                    gs_Rec.PrintCodeRunDelay = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PrintCodeRunDelay(gu32_RecNum), gs_Rec.PrintCodeRunDelay);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 156:        //���������Чʱ��TP2
            if (lu16_WriteData <= 999)
            {
                if (lu16_WriteData != gs_Rec.PrintCodeTime)
                {
                    gs_Rec.PrintCodeTime = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_PrintCodeTime(gu32_RecNum), gs_Rec.PrintCodeTime);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 157:        //����ʱ������ж��/���� ����
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Rec.SheildDiscSwitch)
                {
                    gs_Rec.SheildDiscSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_SheildDiscSwitch(gu32_RecNum), gs_Rec.SheildDiscSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 158:        //��Ƿ�������
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Rec.OUSwitch)
                {
                    gs_Rec.OUSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_OUSwitch(gu32_RecNum), gs_Rec.OUSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 159:        //��Ƿ����ͣ����
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Rec.OUStopSwitch)
                {
                    gs_Rec.OUStopSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_OUStopSwitch(gu32_RecNum), gs_Rec.OUStopSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 160:        //�����������
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Rec.CorrectFallSwitch)
                {
                    gs_Rec.CorrectFallSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_CorrectFallSwitch(gu32_RecNum), gs_Rec.CorrectFallSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 161:        //СͶ�㶯����
            if (lu16_WriteData <= 1)
            {
                if (lu16_WriteData != gs_Rec.SmallPluseSwitch)
                {
                    gs_Rec.SmallPluseSwitch = lu16_WriteData;
                    FRAM_WriteDW(FMAddr_SmallPluseSwitch(gu32_RecNum), gs_Rec.SmallPluseSwitch);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
                
        case 183:        //���ۼ����ݴ�ӡ
            if (lu16_WriteData == 1)
            {
                if (gb_RunFlg == false)
                {
                    gb_PrintAllRecFlg_UART0 = false;
                    gb_PrintAllRecFlg_UART1 = false;//����Modbus��ӡ�����䷽�ۼƺ��ٴ�ӡ���ۼƻ��ӡ�������ݵ����� v1.01
                    PrintStart(PRINT_TOTAL_REPORT, 0, 0);
                    return RESPONSEOK;
                }
                else
                    return NOSUCCESS;
            }
            else
                return DATAERRO;
        case 184:        //�䷽���ñ���ӡ
            if (lu16_WriteData <= 21)
            {
                if (gb_RunFlg == false)
                {
                    if (lu16_WriteData == 0)
                    {   //��ӡ��ǰ�䷽���ñ�
                        gb_FirstPrintFlg_UART0 = true;
                        gb_PrintAllRecFlg_UART0 = false;
                        gb_FirstPrintFlg_UART1 = true;
                        gb_PrintAllRecFlg_UART1 = false;
                        PrintStart(PRINT_REC_SET, gu32_RecNum, 0);
                    }
                    else if (lu16_WriteData >= 1 && lu16_WriteData <= 20)
                    {   //��ӡ��Ӧ�䷽���ñ�
                        gb_FirstPrintFlg_UART0 = true;
                        gb_PrintAllRecFlg_UART0 = false;
                        gb_FirstPrintFlg_UART1 = true;
                        gb_PrintAllRecFlg_UART1 = false;
                        PrintStart(PRINT_REC_SET, lu16_WriteData, 0);
                    }
                    else
                    {   //��ӡ�����䷽���ñ�
                        gb_FirstPrintFlg_UART0 = true;
                        gb_PrintAllRecFlg_UART0 = true;
                        gb_FirstPrintFlg_UART1 = true;
                        gb_PrintAllRecFlg_UART1 = true;
                        gu8_Item = PRINT_REC_SET;
                        //��ӡ����Ŀ��ֵ��Ϊ0���䷽
                        if (gs_Rec.Target != 0)
                        {
                            gu32_PrintRecNumStart = gu32_RecNum;    //������ʼ�䷽�ţ������ж��Ƿ������䷽����ӡ���
                            PrintStart(PRINT_REC_SET, gu32_RecNum, 0);  //�ӵ�ǰ�䷽��ʼ��ӡ
                        }
                        else
                        {   //��ǰ�䷽Ŀ��ֵΪ0����ȡ��һ��Ŀ��ֵ��Ϊ0���䷽��
                            gu32_PrintRecNumStart = NextRecNum(gu32_RecNum);
                            if (gu32_PrintRecNumStart != gu32_RecNum)
                            {   //�����ȡ������һ����Ϊ0���䷽�ź�Ŀǰ�䷽����ȣ����������䷽Ŀ��ֵ��Ϊ0������ӡ
                                PrintStart(PRINT_REC_SET, gu32_PrintRecNumStart, 0);  //��Ŀ��ֵ��Ϊ0���䷽�ſ�ʼ��ӡ
                            }
                        }
                    }
                }
                else
                    return NOSUCCESS;
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 185:        //�䷽�ۼƱ�����ӡ
            if (lu16_WriteData <= 21)
            {
                if (gb_RunFlg == false)
                {
                    if (lu16_WriteData == 0)
                    {   //��ӡ��ǰ�䷽�ۼƱ���
                        gb_FirstPrintFlg_UART0 = true;
                        gb_PrintAllRecFlg_UART0 = false;
                        gb_FirstPrintFlg_UART1 = true;
                        gb_PrintAllRecFlg_UART1 = false;
                        PrintStart(PRINT_REC_REPORT, gu32_RecNum, 0);
                    }
                    else if (lu16_WriteData >= 1 && lu16_WriteData <= 20)
                    {   //��ӡ��Ӧ�䷽�ۼƱ���
                        gb_FirstPrintFlg_UART0 = true;
                        gb_PrintAllRecFlg_UART0 = false;
                        gb_FirstPrintFlg_UART1 = true;
                        gb_PrintAllRecFlg_UART1 = false;
                        PrintStart(PRINT_REC_REPORT, lu16_WriteData, 0);
                    }
                    else
                    {   //��ӡ�����䷽�ۼƱ���
                        gb_FirstPrintFlg_UART0 = true;
                        gb_PrintAllRecFlg_UART0 = true;
                        gb_FirstPrintFlg_UART1 = true;
                        gb_PrintAllRecFlg_UART1 = true;
                        gu8_Item = PRINT_REC_REPORT;
                        //��ӡ����Ŀ��ֵ��Ϊ0���䷽
                        if (gs_Rec.Target != 0)
                        {
                            gu32_PrintRecNumStart = gu32_RecNum;    //������ʼ�䷽�ţ������ж��Ƿ������䷽����ӡ���
                            PrintStart(PRINT_REC_REPORT, gu32_RecNum, 0);  //�ӵ�ǰ�䷽��ʼ��ӡ
                        }
                        else
                        {   //��ǰ�䷽Ŀ��ֵΪ0����ȡ��һ��Ŀ��ֵ��Ϊ0���䷽��
                            gu32_PrintRecNumStart = NextRecNum(gu32_RecNum);
                            if (gu32_PrintRecNumStart != gu32_RecNum)
                            {   //�����ȡ������һ����Ϊ0���䷽�ź�Ŀǰ�䷽����ȣ����������䷽Ŀ��ֵ��Ϊ0������ӡ
                                PrintStart(PRINT_REC_REPORT, gu32_PrintRecNumStart, 0);  //��Ŀ��ֵ��Ϊ0���䷽�ſ�ʼ��ӡ
                            }
                        }
                    }
                }
                else
                    return NOSUCCESS;
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 186:       //���ݻ�ԭ�ָ���������
            if ((lu16_WriteData >= 8800) && (lu16_WriteData <= 8806))
            {
                switch (lu16_WriteData)
                {
                    case 8800:              //�ָ���������
                        Reset_Cal();
                        Reset_Setup(true);
                        Reset_Rec();
                        Reset_IoDef();
                        FRAM_WriteDW(FMAddr_BatchTime, 0);
                        FRAM_WriteDW(FMAddr_BatchTimeCnt, 0);
                        break;
                    case 8801:              //�ָ��궨
                        Reset_Cal();
                        break;
                    case 8802:              //�ָ���������
                        Reset_Setup(true);
                        break;
                    case 8803:              //�ָ��䷽
                        Reset_Rec();
                        break;
                    case 8804:              //�ָ�IO����
                        Reset_IoDef();
                        break;
                    case 8805:              //ִ�б���
                        Backup_Parameter();
                        break;
                    case 8806:              //ִ�лָ�
                        Reload_Parameter();
                        break;
                }
                Init_Parameter();
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        default:
            return DATAPLACEERRO;
    }
}

/*********************************************************************
��������: void ModBus_Write_2Byte(u8 *fu8p_Data)
��    ��: modbusд���Ĵ�������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-22
��    ��:                      ʱ    ��: 
*********************************************************************/
void ModBus_Write_2Byte(u8 *fu8p_Data)
{
    u16 lu16_Address;
    u16 lu16_ErrCode;
    
    lu16_Address = (fu8p_Data[2] << 8) + fu8p_Data[3];
    
    //д˫�ֽڵĵ�ַ��Χ��
    if ((lu16_Address >= RW2BYTESTARTADS) && (lu16_Address <= RW2BYTEENDADS))
    {
        if (gb_RunFlg == false)       //��������״̬������д��
            lu16_ErrCode = ModBus_Write_2ByteDeal(fu8p_Data);
        else
            lu16_ErrCode = NOSUCCESS;
        if (lu16_ErrCode == RESPONSEOK)
        {
            //����д��ɹ�
            ModBus_Write_2ByteOk(fu8p_Data);
        }
        else
        {
            //���ݷ�Χ�������ʹ���
            Modbus_Error(lu16_ErrCode, fu8p_Data);
        }
    }
    else
    {
        //���ܵ�ַ����
        Modbus_Error(DATAPLACEERRO, fu8p_Data);
    }
}

/***********************************************************
�� �� ����void ModBus_Write_4ByteOk(void)
��    �ܣ�MODBUSЭ���µ����ֽ�д���������ȷ
˵    ����
��ڲ�������
���ó���: 
�� �� ֵ����
��    �ƣ��Ժ���               ��    �ڣ�2011-5-17
��    �ģ�                     ��    �ڣ�
***********************************************************/
void ModBus_Write_4ByteOk(u8 *fu8p_Data)
{
    FpBuildCrcLrc(fu8p_Data, 6);
    FpSendRtuAscII(fu8p_Data, 8);
}


/***********************************************************
�� �� ����bit ModBus_Write_4ByteDeal(u8 *fu8p_Data)
��    �ܣ�MODBUSЭ���µ�4�ֽ�д�������
˵    ����
��ڲ�������
�� �� ֵ����
��    �ƣ�wbj                  ��    �ڣ�2008-1-28 9:15
��    �ģ��Ժ���               ��    �ڣ�2011-5-17
***********************************************************/
u8 ModBus_Write_4ByteDeal(u8 *fu8p_Data)
{
    u16 lu16_Address;
    ULDATA ulWriteData;
    u32 lu32_Temp;
    
    //д��ĵ�ַ
    lu16_Address = fu8p_Data[2];
    lu16_Address <<= 8;
    lu16_Address += fu8p_Data[3]; 
  
    //д�������
    if ((fu8p_Data == gu8_TxdArray_UART0 ? gs_Setup.HiLo_2 : gs_Setup.HiLo_1) == 0)                      //������ǰ      chx 090908
    {
        ulWriteData.uc[3] = fu8p_Data[7];
        ulWriteData.uc[2] = fu8p_Data[8];
        ulWriteData.uc[1] = fu8p_Data[9];
        ulWriteData.uc[0] = fu8p_Data[10];
    }
    else                                    //������ǰ      chx 090908
    {
        ulWriteData.uc[3] = fu8p_Data[9];
        ulWriteData.uc[2] = fu8p_Data[10];
        ulWriteData.uc[1] = fu8p_Data[7];
        ulWriteData.uc[0] = fu8p_Data[8];
    }
    
    switch (lu16_Address)
    {
        case 16:        //�������
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if ((ulWriteData.ul % gs_Cal.Div) !=0)
                lu32_Temp = 1;
            else
                lu32_Temp = 0;
            if ((ulWriteData.ul <= 999999) && ((ulWriteData.ul / gs_Cal.Div + lu32_Temp) <= 100000) && (ulWriteData.ul >= gs_Cal.Div))  //������̴��ڵ�����С�ֶ�ֵ
            {
                if (ulWriteData.ul != gs_Cal.Cap)
                {
                    gs_Cal.Cap = ulWriteData.ul;
                    FRAM_WriteDW(FMAddr_CalCap, gs_Cal.Cap);
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 18:        //���������궨
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if (ulWriteData.ul == 1)
            {
                //�ȶ�����AD����������������
                if (AdToMv(gu32_AdFedValue) <= 12000 * gs_Cal.Sensor && 
                    gb_AdOflFlg == false && gb_MvStabFlg == true)
                {
                    gs_Cal.Zero = gu32_AdFedValue;
                    FRAM_WriteDW(FMAddr_CalZero, gs_Cal.Zero);
                    gu32_FloatZero = 0;
                    gb_SigFZeroFlg = false;
                    return RESPONSEOK;
                }
                else
                    return NOSUCCESS;
            }
            else
                return DATAERRO;
        case 20:        //����������궨(������������ֵ)
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if (ulWriteData.ul <= 999999 && ulWriteData.ul > 0)
            {
                //�ȶ���AD��������ҵ�ǰAD�������ADֵ�������궨����
                if (gb_AdOflFlg == false && gb_MvStabFlg == true && AdToMv(gu32_AdFedValue) > AdToMv(gs_Cal.Zero))
                {
                    //         ADc * (2^13)
                    //  ADK = ------------------
                    //         (Wc / dd) * 4
                    gs_Cal.ADK = ((float)(gu32_AdFedValue - gs_Cal.Zero))/((float)ulWriteData.ul * 4.0f) * (float)gs_Cal.Div;
                    FRAM_WriteFloat(FMAddr_CalADK, gs_Cal.ADK);    //����ADK
                    gu32_FloatZero = 0;
                    gb_SigFZeroFlg = false;
                    return RESPONSEOK;
                }
                else
                    return NOSUCCESS;
            }
            else
                return DATAERRO;
        case 22:        //���������궨 ����ĺ�����ת����ADcode
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if (ulWriteData.ul <= 12000 * gs_Cal.Sensor)
            {
                gs_Cal.Zero = MvToAd(ulWriteData.ul);      //MvֵתΪAD��
                FRAM_WriteDW(FMAddr_CalZero, gs_Cal.Zero);
                gu32_FloatZero = 0;
                gb_SigFZeroFlg = false;
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 24:        //����������궨(���������ֵ)
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if (ulWriteData.ul <= gs_Cal.Sensor * 12000)
            {
                gu32_GainMv = ulWriteData.ul;
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 26:        //����������궨(��������ֵ) (A��)
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if (ulWriteData.ul <= 999999 && gu32_GainMv != 0)
            {
                //         ADc * (2^13)
                //  ADK = ------------------
                //         (Wc / dd) * 4
                gs_Cal.ADK = ((float)MvToAd(gu32_GainMv))/((float)ulWriteData.ul * 4.0f) * (float)gs_Cal.Div;
                FRAM_WriteFloat(FMAddr_CalADK, gs_Cal.ADK);    //����ADK
                gu32_FloatZero = 0;
                gb_SigFZeroFlg = false;
                gu32_GainMv = 0;
                return RESPONSEOK;
            }
            else
                return NOSUCCESS;
        case 28:        //Ŀ��ֵ
            if (ulWriteData.ul  <= gs_Cal.Cap)
            {
                if (ulWriteData.ul != gs_Rec.Target)
                {
                    if (gb_RunFlg == false)     //ֹͣ״̬�������޸��䷽
                    {
                        gs_Rec.Target = ulWriteData.ul;   
                        FRAM_WriteDW(FMAddr_Target(gu32_RecNum), gs_Rec.Target);
                    }
                    else        //����ʱ�޸�
                    {
                        gu32_FastSetTemp[0] = ulWriteData.ul;
                        gu8_FastSetSigTemp |= 0x01;
                    }
                }
                return RESPONSEOK;
            }       
            else
                return DATAERRO;
        case 30:        //��Ͷ��ǰ��
            if (ulWriteData.ul  <= gs_Cal.Cap)
            {
                if (ulWriteData.ul != gs_Rec.Large)
                {
                    if (gb_RunFlg == false)
                    {
                        gs_Rec.Large = ulWriteData.ul;
                        FRAM_WriteDW(FMAddr_Large(gu32_RecNum), gs_Rec.Large);
                    }
                    else        //����ʱ�޸�
                    {
                        gu32_FastSetTemp[1] = ulWriteData.ul;
                        gu8_FastSetSigTemp |= 0x02;
                    }
                }
                return RESPONSEOK;
            }   
            else
                return DATAERRO;    
        case 32:        //��Ͷ��ǰ��
            if (ulWriteData.ul  <= gs_Cal.Cap)
            {
                if (ulWriteData.ul != gs_Rec.Middle)
                {
                    if (gb_RunFlg == false)
                    {
                        gs_Rec.Middle = ulWriteData.ul;
                        FRAM_WriteDW(FMAddr_Middle(gu32_RecNum), gs_Rec.Middle);
                    }
                    else        //����ʱ�޸�
                    {
                        gu32_FastSetTemp[2] = ulWriteData.ul;
                        gu8_FastSetSigTemp |= 0x04;
                    }
                }
                return RESPONSEOK;
            }       
            else
                return DATAERRO;
        case 34:        //���ֵ
            if (ulWriteData.ul  <= gs_Cal.Cap)
            {
                if (ulWriteData.ul != gs_Rec.Small)
                {
                    if (gb_RunFlg == false)
                    {
                        gs_Rec.Small = ulWriteData.ul;
                        FRAM_WriteDW(FMAddr_Small(gu32_RecNum), gs_Rec.Small);
                    }
                    else        //����ʱ�޸�
                    {
                        gu32_FastSetTemp[3] = ulWriteData.ul;
                        gu8_FastSetSigTemp |= 0x08;
                    }
                }
                return RESPONSEOK;
            }       
            else
                return DATAERRO;
        case 36:        //����ֵ
            if (ulWriteData.ul  <= gs_Cal.Cap)
            {
                if (ulWriteData.ul != gs_Rec.NearZero)
                {
                    gs_Rec.NearZero = ulWriteData.ul;
                    FRAM_WriteDW(FMAddr_NearZero(gu32_RecNum), gs_Rec.NearZero);
                }
                return RESPONSEOK;
            }       
            else
                return DATAERRO;
        case 38:        //�Ĵ���ʼ����
            if (ulWriteData.ul  <= gs_Cal.Cap)
            {
                if (ulWriteData.ul != gs_Rec.FlapBagWt)
                {
                    if (gb_RunFlg == false)
                    {
                        gs_Rec.FlapBagWt = ulWriteData.ul;
                        FRAM_WriteDW(FMAddr_FlapBagWt(gu32_RecNum), gs_Rec.FlapBagWt);
                    }
                    else        //����ʱ�޸�
                    {
                        gu32_FastSetTemp[5] = ulWriteData.ul;
                        gu8_FastSetSigTemp |= 0x20;
                    }
                }
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 40:        //����ֵ
            if (ulWriteData.ul  <= gs_Cal.Cap)
            {
                if (ulWriteData.ul != gs_Rec.OverValue)
                {
                    gs_Rec.OverValue = ulWriteData.ul;
                    FRAM_WriteDW(FMAddr_OverValue(gu32_RecNum), gs_Rec.OverValue);
                }
                return RESPONSEOK;
            }       
            else
                return DATAERRO;
        case 42:        //Ƿ��ֵ
            if (ulWriteData.ul  <= gs_Cal.Cap)
            {
                if (ulWriteData.ul != gs_Rec.UnderValue)
                {
                    gs_Rec.UnderValue = ulWriteData.ul;
                    FRAM_WriteDW(FMAddr_UnderValue(gu32_RecNum), gs_Rec.UnderValue);
                }
                return RESPONSEOK;
            }   
            else
                return DATAERRO;
        case 178:    //����У׼ǰ���� v1.01
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if (ulWriteData.ul <= 999999)
            {
                gu32_CalDispWt = ulWriteData.ul;
                return RESPONSEOK;
            }
            else
                return DATAERRO;
        case 180:    //����У׼������ v1.01
            if (gb_CalLockDefFlg && gb_CalLockFlg == false)
            {   //�궨���ж��嵫��������Ч�����ܱ궨
                return NOSUCCESS;
            }
            if (ulWriteData.ul <= 999999 && gu32_CalDispWt != 0)
            {
                gs_Cal.ADK = ((float)gu32_CalDispWt*gs_Cal.ADK)/(float)ulWriteData.ul;
                FRAM_WriteFloat( FMAddr_CalADK, gs_Cal.ADK );    //����ADK
                gu32_FloatZero = RoundOff(gu32_FloatZero * ulWriteData.ul, gu32_CalDispWt);
                gu32_CalDispWt = 0;
                return RESPONSEOK;
            }
            else
                return DATAERRO;    
                
	    case 190:   //�䷽1�ۼƴ���
	    case 192:   //�䷽1�ۼ�����
	    case 194:   //�䷽2�ۼƴ���
	    case 196:   //�䷽2�ۼ�����
	    case 198:   //�䷽3�ۼƴ���
	    case 200:   //�䷽3�ۼ�����
	    case 202:   //�䷽4�ۼƴ���
	    case 204:   //�䷽4�ۼ�����
	    case 206:   //�䷽5�ۼƴ���
	    case 208:   //�䷽5�ۼ�����
	    case 210:   //�䷽6�ۼƴ���
	    case 212:   //�䷽6�ۼ�����
	    case 214:   //�䷽7�ۼƴ���
	    case 216:   //�䷽7�ۼ�����
	    case 218:   //�䷽8�ۼƴ���
	    case 220:   //�䷽8�ۼ�����
	    case 222:   //�䷽9�ۼƴ���
	    case 224:   //�䷽9�ۼ�����
	    case 226:   //�䷽10�ۼƴ���
	    case 228:   //�䷽10�ۼ�����
	    case 230:   //�䷽11�ۼƴ���
	    case 232:   //�䷽11�ۼ�����
	    case 234:   //�䷽12�ۼƴ���
	    case 236:   //�䷽12�ۼ�����
	    case 238:   //�䷽13�ۼƴ���
	    case 240:   //�䷽13�ۼ�����
	    case 242:   //�䷽14�ۼƴ���
	    case 244:   //�䷽14�ۼ�����
	    case 246:   //�䷽15�ۼƴ���
	    case 248:   //�䷽15�ۼ�����
	    case 250:   //�䷽16�ۼƴ���
	    case 252:   //�䷽16�ۼ�����
	    case 254:   //�䷽17�ۼƴ���
	    case 256:   //�䷽17�ۼ�����
	    case 258:   //�䷽18�ۼƴ���
	    case 260:   //�䷽18�ۼ�����
	    case 262:   //�䷽19�ۼƴ���
	    case 264:   //�䷽19�ۼ�����
	    case 266:   //�䷽20�ۼƴ���
	    case 268:   //�䷽20�ۼ�����
	        if (ulWriteData.ul == 0)    //д��0�������Ӧ���䷽�ۼƴ���������
	        {
	            ClrSum_Rec((lu16_Address - 190)/4 + 1);
				return RESPONSEOK;
	        }
	        else
    			return DATAERRO;
        default:
            return DATAPLACEERRO;
    }
}

/***********************************************************
�� �� ����void ModBus_Write_4Byte(u8 *fu8p_Data)
��    �ܣ�MODBUSЭ���µ����ֽ�д��
˵    ����
��ڲ�������
���ó���: 
�� �� ֵ����
��    �ƣ�wbj                  ��    �ڣ�2008-1-28 9:15
��    �ģ�                     ��    �ڣ�
***********************************************************/
void ModBus_Write_4Byte(u8 *fu8p_Data)
{
    u16 lu16_Address;
    u16 lu16_ErrCode;
    
    lu16_Address = (fu8p_Data[2] << 8) + fu8p_Data[3];
    //�ɶ����ĵ�ַ��Χ�� for test
    if (((lu16_Address >= RW4BYTESTARTADS) && (lu16_Address <= RW4BYTEENDADS) || 
         (lu16_Address >= RW4BYTESTARTADS_1) && (lu16_Address <= RW4BYTEENDADS_1)) &&
         (lu16_Address % 2 == 0))
    {
        //ֻ����д�����ֽ�
        if (fu8p_Data[6] != 4)
        {
            //���ݷ�Χ�������ʹ���
            Modbus_Error(DATAPLACEERRO, fu8p_Data);
        }
        else
        {
            //��������״̬������д�� ����ʱֻ�����޸�F1.x
            if ((gb_RunFlg == false) || (lu16_Address >= F1_1ADDRESS && lu16_Address <= F1_6ADDRESS))
                lu16_ErrCode = ModBus_Write_4ByteDeal(fu8p_Data);
            else
                lu16_ErrCode = NOSUCCESS;
            if (lu16_ErrCode == RESPONSEOK)
            {
                //����д��ɹ�
                ModBus_Write_4ByteOk(fu8p_Data);
            }
            else
            {
                //���ݷ�Χ�������ʹ���
                Modbus_Error(lu16_ErrCode, fu8p_Data);
            }
        }
    }
    else
    {
        //���ܵ�ַ����
        Modbus_Error(DATAPLACEERRO, fu8p_Data);
    }
}


/***********************************************************************
�� �� ����void Deal8byteShift(u32 *fu32_Buf,u8 fu8_Lenth,bool fb_ShiftMode)
��    �ܣ�������������λ����С�ڵ���32
          shiftmode:0 ����   shiftmode:1 ����
˵    ����
��ڲ�����
�� �� ֵ��
��    �ƣ�                     ��    �ڣ�
��    �ģ��Ժ���               ��    �ڣ�2011-5-17
***********************************************************************/
void Deal8byteShift(u32 *fu32_Buf, u8 fu8_Lenth, bool fb_ShiftMode)
{
    u32 lu32_TempBit0, lu32_TempBit1;

    lu32_TempBit0 = fu32_Buf[0];
    lu32_TempBit1 = fu32_Buf[1];

    if ((fu8_Lenth > 32) && (fb_ShiftMode==0)) return;
    if ((fu8_Lenth > 64) && (fb_ShiftMode == 1)) return;
        
    if (fb_ShiftMode==0)
    {
        lu32_TempBit1 <<= fu8_Lenth;
        lu32_TempBit1 |= (lu32_TempBit0 >> (32 - fu8_Lenth));
        lu32_TempBit0 <<= fu8_Lenth;
    }
    else
    {
        if (fu8_Lenth <= 32)
        {
            lu32_TempBit0 >>= fu8_Lenth;
            lu32_TempBit0 |= (lu32_TempBit1 << (32 - fu8_Lenth));
            lu32_TempBit1 >>= fu8_Lenth;
        }
        else
        {
            lu32_TempBit0 = lu32_TempBit1;
            lu32_TempBit0 >>= (fu8_Lenth - 32);
            lu32_TempBit1 = 0;
        }
    }

    fu32_Buf[0] = lu32_TempBit0;
    fu32_Buf[1] = lu32_TempBit1;
}

/*********************************************************************
��������: void Modbus_Read_CoilDeal(void)
��    ��: ��ȡ��Ȧ��������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-17
��    ��:                      ʱ    ��: 
*********************************************************************/
void Modbus_Read_CoilDeal(void)
{
    u32 i = 0x01;
    
    #define SumWt0    ((gu32_SumNum == 0)&&(gu32_SumWt == 0))
        
    //===========��д�洢����=======================
    //ǰ32����Ȧ
    //64~76 ȫ�� = 0 
    gu32_ReadCoilSwitch = 0;
    gu32_ReadCoilSwitch |=((gs_Setup.PowerOnZeroSwitch != 0)     ? (i << 13) : 0x00);      //0077
    //�˴�Ϊ�����ϵ�Ƭ�������ж�=1���޶�=0���˳������ж�=0���޶�=1
    gu32_ReadCoilSwitch |=((gs_Setup.TareMode != 1)              ? (i << 14) : 0x00);      //0078
    gu32_ReadCoilSwitch |=((gs_Setup.PrintSwitch_1 != 0)         ? (i << 15) : 0x00);      //0079 v1.01
    gu32_ReadCoilSwitch |=((gs_Rec.OUSwitch != 0)                ? (i << 16) : 0x00);      //0080
    gu32_ReadCoilSwitch |=((gs_Rec.OUStopSwitch != 0)            ? (i << 17) : 0x00);      //0081
    gu32_ReadCoilSwitch |=((gs_Rec.CorrectFallSwitch != 0)       ? (i << 18) : 0x00);      //0082
    gu32_ReadCoilSwitch |=((gs_Rec.SmallPluseSwitch != 0)        ? (i << 19) : 0x00);      //0083
    gu32_ReadCoilSwitch |=((gs_Setup.GorNMode == NET)            ? (i << 20) : 0x00);      //0084
    gu32_ReadCoilSwitch |=((gs_Setup.FeedMode != 0)              ? (i << 21) : 0x00);      //0085
                    
    gu32_ReadCoilSwitch |=((gu16_MbIOOutInit == 0) ? (i << 29) : 0x00);    //0093
    gu32_ReadCoilSwitch |=(((gu16_MbIoOutState&0x01)!=0)     ? (i << 30) :(0x00));     //0094
    gu32_ReadCoilSwitch |=(((gu16_MbIoOutState&0x02)!=0)     ? (i << 31) :(0x00));     //0095
        
    //��32����Ȧ
    gu32_ReadCoilIo = 0;
    gu32_ReadCoilIo |= (((gu16_MbIoOutState&0x04)!=0)     ? (i):(0x00));          //0096
    gu32_ReadCoilIo |= (((gu16_MbIoOutState&0x08)!=0)     ? (i<<1):(0x00));       //0097
    gu32_ReadCoilIo |= (((gu16_MbIoOutState&0x10)!=0)     ? (i<<2):(0x00));       //0098
    gu32_ReadCoilIo |= (((gu16_MbIoOutState&0x20)!=0)     ? (i<<3):(0x00));       //0099
    gu32_ReadCoilIo |= (((gu16_MbIoOutState&0x40)!=0)     ? (i<<4):(0x00));       //0100
    gu32_ReadCoilIo |= (((gu16_MbIoOutState&0x80)!=0)     ? (i<<5):(0x00));       //0101
    gu32_ReadCoilIo |= (((gu16_MbIoOutState&0x100)!=0)    ? (i<<6):(0x00));       //0102
    gu32_ReadCoilIo |= (((gu16_MbIoOutState&0x200)!=0)    ? (i<<7):(0x00));       //0103
    gu32_ReadCoilIo |= (((gu16_MbIoOutState&0x400)!=0)    ? (i<<8):(0x00));       //0104
    gu32_ReadCoilIo |= (((gu16_MbIoOutState&0x800)!=0)    ? (i<<9):(0x00));       //0105
        
    gu32_ReadCoilIo |= ((gb_RunFlg)          ? i<<10 : 0x00);    //0106
    gu32_ReadCoilIo |= ((!gb_RunFlg)         ? i<<11 : 0x00);    //0107
    gu32_ReadCoilIo |= ((gb_ZeroPosition)    ? i<<12 : 0x00);    //0108
    gu32_ReadCoilIo |= ((gb_AlarmFlg == false)         ? i<<13 : 0x00);    //0109
  //gu32_ReadCoilIo |= 0x00;           //i<<14            //0110ѡ�䷽,�㶨����0
    gu32_ReadCoilIo |= ((gb_PackFlg)         ? i<<15 : 0x00);    //0111
    gu32_ReadCoilIo |= ((Sp_Disc_State(DISC_STATE))    ? i<<16 : 0x00);    //0112
    gu32_ReadCoilIo |= ((Sp_Disc_State(SP3_STATE))     ? i<<17 : 0x00);    //0113  
    //gu32_ReadCoilIo |= 0x00;         //i<<18            //0114��ӡ,�㶨����0
    gu32_ReadCoilIo |= ((gb_MbKeyLockFlg)              ? i<<19 : 0x00);    //0115
    gu32_ReadCoilIo |= ((SumWt0)             ? i<<20 : 0x00);    //0116
    gu32_ReadCoilIo |= ((gb_DispNetFlg)      ? i<<21 : 0x00);    //0117
    gu32_ReadCoilIo |= ((gb_GoFlg)           ? i<<22 : 0x00);    //0118
    gu32_ReadCoilIo |= ((gb_EndFlg)         ? i<<23 : 0x00);    //0119
    gu32_ReadCoilIo |= ((gb_Sp1Flg)          ? i<<24 : 0x00);    //0120
}

/***********************************************************
�� �� ����void Modbus_Read_Coil(u8 *fu8p_Data)
��    �ܣ�����Ȧ״̬,�����ulOnlyReadCollλ��
          ����λ����Ŀ������64
˵    ��: �Ƚ�Ҫ����λ�����ú�,�������Ӧ�Ĵ洢������,Ȼ��
          ����������8,������ٸ��ֽ�,�����ÿ8λ�Ƴ�һ�ε�
          ��ʽ��λȫ������,����8λ��,�Ͷ˲���.
��ڲ�����
�� �� ֵ��
��    �ƣ�wbj                  ��    �ڣ�2008-1-28 9:15
��    �ģ��Ժ���               ��    �ڣ�2011-5-17
***********************************************************/
void Modbus_Read_Coil(u8 *fu8p_Data)
{
    u8  i;
    u8  lu8_ByteNum;
    u32 lu32_DataBuf[2] = {0,0};
    u16 lu16_Address;
    u16 lu16_ReadLenth;
    u8 lu8_EmptyBit;     //δ����Ȧ�Ŀ�λ
    
    lu16_Address = (fu8p_Data[2] << 8) + fu8p_Data[3];
    lu16_ReadLenth = (fu8p_Data[4] << 8) + fu8p_Data[5];
    
    //��������Ȧ����λ��ַ����64λ��32λ��������
    lu32_DataBuf[0] = gu32_ReadCoilIo;
    //��64λ����������ReadBitEEProm��ַ����,�ڳ��ռ��ReadBitEEProm��ַ���
    Deal8byteShift(lu32_DataBuf,(RWCOILENDADSEE-RWCOILSTARTADSEE+1),false);
    //����ַ����64λ��������32λ��
    lu32_DataBuf[0] |= gu32_ReadCoilSwitch;
    //�����������Ƴ� ��ǰ��ַ-��Ȧ�ɶ��׵�ַ ����(���ӵ�ǰ��ַ����,��������λ���޳�) 
    Deal8byteShift(lu32_DataBuf,(u8)(lu16_Address-RWCOILSTARTADSEE),true);
    
    if ((lu16_ReadLenth % 8) == 0)
    {
        lu8_ByteNum = lu16_ReadLenth / 8;
        lu8_EmptyBit = 0;
    }
    else
    {
        lu8_ByteNum = (lu16_ReadLenth / 8) + 1;
        lu8_EmptyBit = 8 - lu16_ReadLenth % 8;     //ȡ��δ����Ȧ��λ�ĸ���
    }

    if ((lu16_Address <= RWCOILENDADSDEAL) && (lu16_Address >= RWCOILSTARTADSEE) &&
       (lu16_ReadLenth != 0) &&
       (lu16_ReadLenth <= (RWCOILENDADSDEAL - lu16_Address + 1)))
    {
        fu8p_Data[2] = lu8_ByteNum;
        for (i = 0; i < lu8_ByteNum; i++)
        {
            fu8p_Data[3 + i] = (u8)(lu32_DataBuf[0]);
            Deal8byteShift(lu32_DataBuf,8,true);
        }
        
        //��û�ж�����Ȧ��0
        fu8p_Data[3+i-1] <<= lu8_EmptyBit;
        fu8p_Data[3+i-1] >>= lu8_EmptyBit;
        
        FpBuildCrcLrc(fu8p_Data, lu8_ByteNum + 3);
        FpSendRtuAscII(fu8p_Data, lu8_ByteNum + 5);
    }
    else
    {
        Modbus_Error(DATAPLACEERRO, fu8p_Data);
    }
}


/*********************************************************************
��������: void ModBus_Write_CoilOk(u8 *fu8p_Data)
��    ��: modbusд��Ȧ�ɹ�����OK
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-18
��    ��:                      ʱ    ��: 
*********************************************************************/
void ModBus_Write_CoilOk(u8 *fu8p_Data)
{    
    FpBuildCrcLrc(fu8p_Data, 6);
    FpSendRtuAscII(fu8p_Data, 8);
}

/***********************************************************
��������: void Modbus_Write_CoilDeal(u8 *fu8p_Data)
��    ��: д��Ȧ(��������)
˵    ��: ��
��ڲ���: 
�� �� ֵ: ��
��    ��:                      ��    �ڣ�
��    ��: �Ժ���               ��    �ڣ�2011-5-18
***********************************************************/
void Modbus_Write_CoilDeal(u8 *fu8p_Data)
{
    bool lb_ResultOKFlg = false;
    bool lb_ErrorFlg = false;
    u16 lu16_Address;
    u16 lu16_WriteData;

    lu16_Address = (fu8p_Data[2] << 8) + fu8p_Data[3];
    lu16_WriteData = (fu8p_Data[4] << 8) + fu8p_Data[5];

    //��д��Ȧ��ʼ����~��д��Ȧ���⴦�����ܽ���
    if (lu16_Address <= RWCOILENDADSDEAL)
    {
        if ((lu16_Address <= 93) && (gb_RunFlg == true))     //����ʱ�������޸Ŀ���
        {
            lb_ErrorFlg = true;
        }
        //���������Դ�ʱ���������������������ع���
        else if(lu16_Address >= 94 && gu16_MbIoTestSwitch == 1)
        {
            lb_ErrorFlg = true;
        }
        else
        {
            switch (lu16_Address)
            {
                case 77:       //�ϵ��Զ����㿪��
                    if ((lu16_WriteData == 0xFF00)||(lu16_WriteData == 0))
                    {
                        gs_Setup.PowerOnZeroSwitch = (lu16_WriteData == 0xFF00) ? 1 : 0;
                        FRAM_WriteDW(FMAddr_PowerOnZeroSwitch, gs_Setup.PowerOnZeroSwitch);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 78:       //����ģʽ
                    if ((lu16_WriteData == 0xFF00)||(lu16_WriteData == 0))
                    {   //�˴�Ϊ�����ϳ���0���޶�1���ж������˳����෴
                        gs_Setup.TareMode = (lu16_WriteData == 0xFF00) ? 0 : 1;
                        if (FRAM_ReadDW(FMAddr_TareMode) != gs_Setup.TareMode)
                        {
                            FRAM_WriteDW(FMAddr_TareMode, gs_Setup.TareMode);
                            TareModeChange(gs_Setup.TareMode);
                        }
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 79:       //�Զ���ӡ����
                    if ((lu16_WriteData == 0xFF00)||(lu16_WriteData == 0))
                    {
                        gs_Setup.PrintSwitch_1 = (lu16_WriteData == 0xFF00) ? 1 : 0;    //v1.01
                        FRAM_WriteDW(FMAddr_PrintSwitch_1, gs_Setup.PrintSwitch_1);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 80:       //��Ƿ�������
                    if ((lu16_WriteData == 0xFF00)||(lu16_WriteData == 0))
                    {
                        gs_Rec.OUSwitch = (lu16_WriteData == 0xFF00) ? 1 : 0;
                        FRAM_WriteDW(FMAddr_OUSwitch(gu32_RecNum), gs_Rec.OUSwitch);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 81:       //��Ƿ����ͣ����
                    if ((lu16_WriteData == 0xFF00)||(lu16_WriteData == 0))
                    {
                        gs_Rec.OUStopSwitch = (lu16_WriteData == 0xFF00) ? 1 : 0;
                        FRAM_WriteDW(FMAddr_OUStopSwitch(gu32_RecNum), gs_Rec.OUStopSwitch);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 82:       //�����������
                    if ((lu16_WriteData == 0xFF00)||(lu16_WriteData == 0))
                    {
                        gs_Rec.CorrectFallSwitch = (lu16_WriteData == 0xFF00) ? 1 : 0;
                        FRAM_WriteDW(FMAddr_CorrectFallSwitch(gu32_RecNum), gs_Rec.CorrectFallSwitch);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 83:       //СͶ�㶯����
                    if ((lu16_WriteData == 0xFF00)||(lu16_WriteData == 0))
                    {
                        gs_Rec.SmallPluseSwitch = (lu16_WriteData == 0xFF00) ? 1 : 0;
                        FRAM_WriteDW(FMAddr_SmallPluseSwitch(gu32_RecNum), gs_Rec.SmallPluseSwitch);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 84:       //�޶�ë����
                    if ((lu16_WriteData == 0xFF00)||(lu16_WriteData == 0))
                    {
                        gs_Setup.GorNMode = (lu16_WriteData == 0xFF00) ? 1 : 0;
                        FRAM_WriteDW(FMAddr_GorNMode, gs_Setup.GorNMode);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 85:       //Ͷ�Ϸ�ʽ
                    if ((lu16_WriteData == 0xFF00)||(lu16_WriteData == 0))
                    {
                        gs_Setup.FeedMode = (lu16_WriteData == 0xFF00) ? 1 : 0;
                        FRAM_WriteDW(FMAddr_FeedMode, gs_Setup.FeedMode);
                        lb_ResultOKFlg = true;
                    }
                    break;
                    
                    
                    
                case 93://DEBUG OUT INIT
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 0;
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 94://DEBUG OUT1
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & 0x0001)
                            gu16_MbIoOutDebug &= (~0x0001);
                        else
                            gu16_MbIoOutDebug |= 0x0001;
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 95://DEBUG OUT2
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & (0x0001 << 1))
                            gu16_MbIoOutDebug &= (~(0x0001 << 1));
                        else
                            gu16_MbIoOutDebug |= (0x0001 << 1);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 96://DEBUG OUT3
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & (0x0001 << 2))
                            gu16_MbIoOutDebug &= (~(0x0001 << 2));
                        else
                            gu16_MbIoOutDebug |= (0x0001 << 2);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 97://DEBUG OUT4
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & (0x0001 << 3))
                            gu16_MbIoOutDebug &= (~(0x0001 << 3));
                        else
                            gu16_MbIoOutDebug |= (0x0001 << 3);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 98://DEBUG OUT5
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & (0x0001 << 4))
                            gu16_MbIoOutDebug &= (~(0x0001 << 4));
                        else
                            gu16_MbIoOutDebug |= (0x0001 << 4);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 99://DEBUG OUT6
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & (0x0001 << 5))
                            gu16_MbIoOutDebug &= (~(0x0001 << 5));
                        else
                            gu16_MbIoOutDebug |= (0x0001 << 5);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 100://DEBUG OUT7
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & (0x0001 << 6))
                            gu16_MbIoOutDebug &= (~(0x0001 << 6));
                        else
                            gu16_MbIoOutDebug |= (0x0001 << 6);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 101://DEBUG OUT8
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & (0x0001 << 7))
                            gu16_MbIoOutDebug &= (~(0x0001 << 7));
                        else
                            gu16_MbIoOutDebug |= (0x0001 << 7);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 102://DEBUG OUT9
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & (0x0001 << 8))
                            gu16_MbIoOutDebug &= (~(0x0001 << 8));
                        else
                            gu16_MbIoOutDebug |= (0x0001 << 8);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 103://DEBUG OUT10
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & (0x0001 << 9))
                            gu16_MbIoOutDebug &= (~(0x0001 << 9));
                        else
                            gu16_MbIoOutDebug |= (0x0001 << 9);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 104://DEBUG OUT11
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & (0x0001 << 10))
                            gu16_MbIoOutDebug &= (~(0x0001 << 10));
                        else
                            gu16_MbIoOutDebug |= (0x0001 << 10);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 105://DEBUG OUT12
                    if (lu16_WriteData == 0xFF00)
                    {
                        gu16_MbIOOutInit = 1;
                        gu16_MbIoOutDebug = gu16_MbIoOutState;
                        if (gu16_MbIoOutDebug & (0x0001 << 11))
                            gu16_MbIoOutDebug &= (~(0x0001 << 11));
                        else
                            gu16_MbIoOutDebug |= (0x0001 << 11);
                        lb_ResultOKFlg = true;
                    }
                    break;
                    
                case 106://����
                    if (lu16_WriteData == 0xFF00)
                    {
                        if (gb_RunFlg == false)
                        {
                            RunStopInit(true);
                            lb_ResultOKFlg = true;
                        }
                        else
                            lb_ErrorFlg = true;
                    }
                    break;
                case 107://��ͣ
                    if (lu16_WriteData == 0xFF00)
                    {
                        Clr_Alarm();
                        RunStopInit(false);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 108://����
                    if (lu16_WriteData == 0xFF00)
                    {
                        if (gb_RunFlg == false)
                        {
                            gb_ZeroKeyFlg = true;
                            lb_ResultOKFlg = true;
                        }
                        else
                            lb_ErrorFlg = true;
                    }
                    break;
                case 109://�屨��
                    if (lu16_WriteData == 0xFF00)
                    {
                        Clr_Alarm();
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 110:   //ѡ�䷽
                    if (lu16_WriteData == 0xFF00)
                    {
                        if (gb_RunFlg == false)
                        {
                            //ѡ�䷽������Ч������Ŀ��ֵ��Ϊ0���䷽
                            gu32_RecNum = NextRecNum(gu32_RecNum);
                            FRAM_WriteDW(FMAddr_RecNum, gu32_RecNum);
                            Read_RecipeData(gu32_RecNum);
                            lb_ResultOKFlg = true;
                        }
                        else
                            lb_ErrorFlg = true;
                    }
                    break;
                case 111:   //���ɴ�
                    if (lu16_WriteData == 0xFF00)
                    {
                        PackInput();
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 112://�ֶ�ж��
                    if (lu16_WriteData == 0xFF00)
                    {
                        if (gb_RunFlg == false)
                        {
                            ManualDisc(2);
                            lb_ResultOKFlg = true;
                        }
                        else
                            lb_ErrorFlg = true;
                    }
                    break;
                case 113://��СͶ
                    if (lu16_WriteData == 0xFF00)
                    {
                        if (gb_RunFlg == false)
                        {
                            ManualSp3(2);
                            lb_ResultOKFlg = true;
                        }
                        else
                            lb_ErrorFlg = true;
                    }
                    break;
                case 114://��ӡ
                    if (lu16_WriteData == 0xFF00)
                    {
                        if (gb_RunFlg == false)
                        {
                            gb_PrintAllRecFlg_UART0 = false;
                            gb_PrintAllRecFlg_UART1 = false;//����Modbus��ӡ�����䷽�ۼƺ��ٴ�ӡ���ۼƻ��ӡ�������ݵ����� v1.01
                            PrintStart(PRINT_TOTAL_REPORT, 0, 0);
                            lb_ResultOKFlg = true;
                        }
                        else
                            lb_ErrorFlg = true;
                    }
                    break;
                case 115://������
                    if (lu16_WriteData == 0xFF00)
                    {
                        gb_MbKeyLockFlg = (!gb_MbKeyLockFlg);
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 116://����ۼ�
                    if (lu16_WriteData == 0xFF00)
                    {
                        if (gb_RunFlg == false)
                        {
                            ClrSum();
                            lb_ResultOKFlg = true;
                        }
                        else
                        {
                            lb_ErrorFlg = true;
                        }
                    }
                    break;
                case 118://�ֶ�����һ��
                    if (lu16_WriteData == 0xFF00)
                    {
                        if (gb_RunFlg == false)      //ֹͣ������Чʱ����������
                        {
                            gb_GoFlg = true;
                            RunStopInit(true);
                            lb_ResultOKFlg = true;
                        }
                        else
                        {
                            lb_ErrorFlg = true;
                        }
                    }
                    break;
                case 119://ֹͣ
                    if (lu16_WriteData == 0xFF00)
                    {
                        Clr_Alarm();
                        if (gb_RunFlg)
                            gb_EndFlg = true;
                        lb_ResultOKFlg = true;
                    }
                    break;
                case 120://�ֶ���Ͷ
                    if (lu16_WriteData == 0xFF00)
                    {
                        if (gb_RunFlg == false)
                        {
                            ManualSp123(2);
                            lb_ResultOKFlg = true;
                        }
                        else
                        {
                            lb_ErrorFlg = true;
                        }
                    }
                    break;
                    
                    
                //Ԥ����ַд����07�쳣��
                default:
                    if ((lu16_WriteData == 0xFF00)||(lu16_WriteData == 0))
                    {
                        lb_ErrorFlg = true;
                    }
                    break;
            }
        }

        if (lb_ResultOKFlg)
        {
            ModBus_Write_CoilOk(fu8p_Data);
        }
        else if (lb_ErrorFlg)
        {
            Modbus_Error(NOSUCCESS, fu8p_Data);
        }
        else
        {
            Modbus_Error(DATAERRO, fu8p_Data);
        }
    }
    else
    {
        //���ܵ�ַ����
        Modbus_Error(DATAPLACEERRO, fu8p_Data);
    }
}

/*********************************************************************
�������ƣ�u8 BuildModbusLrc(u8 *fuc_Msg, u8 fuc_DataLen)
��    �ܣ�modbus ASCII��ʽ�µ�lrcУ��
˵    ����
��    �ã�
��ڲ�����
�� �� ֵ������ֵ
��    �ƣ��Ժ���               ʱ    �䣺2009-9-3
��    �ģ�                     ʱ    �䣺
*********************************************************************/
u8 BuildModbusLrc(u8 *fuc_Msg, u8 fuc_DataLen)
{
    u8 luc_Lrc = 0;               //LRC ��ʼ��
    
    while (fuc_DataLen--)             //����������Ļ�����
    {
        luc_Lrc += *fuc_Msg++;       //�������ֽ���ӣ��޽�λ
    }
    return ((u8)(-((char)luc_Lrc))); //���ض����Ʋ���
}

/***********************************************************
�� �� ����bool CheckModbusLrc(u8 *puchMsg, u32 ulDataLen)
��    �ܣ��ж�LRCУ��
˵    ����
��ڲ�������
���ó���: 
�� �� ֵ����
��    �ƣ�wbj                  ��    �ڣ�2008-1-24 9:26
��    �ģ��Ժ���               ��    �ڣ�2014-1-22
***********************************************************/
bool CheckModbusLrc(u8 *puchMsg, u32 ulDataLen)
{
    if (BuildModbusLrc(puchMsg, ulDataLen) == *(puchMsg+ulDataLen))
    {
        if (puchMsg == gu8_TxdArray_UART0)       //uart0modbusͨѶ
            gb_ModbusAnswerFlg_Uart0 = true;      //���ڲ����Զ�ƥ�书����ʹ��
        else                                        //uart1modbusͨѶ
            gb_ModbusAnswerFlg_Uart1 = true;      //���ڲ����Զ�ƥ�书����ʹ��
        return true;
    }
    else
    {
        if (puchMsg == gu8_TxdArray_UART0)       //uart0modbusͨѶ
            gvb_EndCharFlg_UART0 = false;      //
        else                                        //uart1modbusͨѶ
            gvb_EndCharFlg_UART1 = false;      //
        
        return(false);
    }
}


/*********************************************************************
��������: void Com_Modbus(u8 *fu8p_Array)
��    ��: modbusͨѶ����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-22
��    ��:                      ʱ    ��: 
*********************************************************************/
void Com_Modbus(u8 *fu8p_Array)
{
    /*RTU��ʽֱ�Ӱ����뻺��ŵ�������壬ASCII��ʽתΪhex������������ڽ��д���
      ���Ҹ���RTU��ASCII��ʽ�������Ӧ��У�顢���͵Ⱥ���ָ��*/
    if (fu8p_Array == gu8_TxdArray_UART0)       //uart0modbusͨѶ
    {
        if (gs_Setup.ComMode_2 == COM_BUS_R)    
        {
            RxdArry_To_TxdArry(0, ulFrameLength_UART0);
            FpCheckCrcLrc = CheckModBusCrc16;
            FpBuildCrcLrc = BuildCrc16;
            FpSendRtuAscII = Modbus_Send_RTU;
        }
        else    //Modbus_ASCII��ʽת��Hex�ٽ��д��� gvu8_RxdCnt_UART0-2��Ҫȥ��':' CR LF
        {
            ASCtoHex(&gu8_RxdArray_UART0[1], &gu8_TxdArray_UART0[0], gvu8_RxdCnt_UART0-2);
            FpCheckCrcLrc = CheckModbusLrc;
            FpBuildCrcLrc = BuildLrc;
            FpSendRtuAscII = Modbus_Send_ASCII;
        }
    }
    else                                        //uart1modbusͨѶ
    {
        if (gs_Setup.ComMode_1 == COM_BUS_R)
        {
            RxdArry_To_TxdArry(1, ulFrameLength_UART1);
            FpCheckCrcLrc = CheckModBusCrc16;
            FpBuildCrcLrc = BuildCrc16;
            FpSendRtuAscII = Modbus_Send_RTU;
        }
        else    //Modbus_ASCII��ʽת��Hex�ٽ��д��� gvu8_RxdCnt_UART1-2��Ҫȥ��':' CR LF
        {
            ASCtoHex(&gu8_RxdArray_UART1[1], &gu8_TxdArray_UART1[0], gvu8_RxdCnt_UART1-2);
            FpCheckCrcLrc = CheckModbusLrc;
            FpBuildCrcLrc = BuildLrc;
            FpSendRtuAscII = Modbus_Send_ASCII;
        }
    }
    
    if ((gs_Setup.TareNumber_2 == fu8p_Array[0] && fu8p_Array == gu8_TxdArray_UART0) ||
        (gs_Setup.TareNumber_1 == fu8p_Array[0] && fu8p_Array == gu8_TxdArray_UART1))
    {
        switch (fu8p_Array[1]) 
        {
            case READREGISTER:      //���Ĵ���
                if (true == FpCheckCrcLrc(fu8p_Array, 6))        //������ȷ
                {
                    ModBus_Read_Register(fu8p_Array);
                }                
                break;
            case WRITEREGISTER:     //д���Ĵ���
                if (true == FpCheckCrcLrc(fu8p_Array, 6))        //������ȷ
                {
                    ModBus_Write_2Byte(fu8p_Array);
                }
                break;
            case WRITEREGISTERS:    //д��Ĵ���
                if (true == FpCheckCrcLrc(fu8p_Array, 11))        //������ȷ
                {
                    ModBus_Write_4Byte(fu8p_Array);
                }
                break;
            case READCOIL:          //����Ȧ
                if (true == FpCheckCrcLrc(fu8p_Array, 6))        //������ȷ
                {
                    Modbus_Read_CoilDeal();
                    Modbus_Read_Coil(fu8p_Array);
                }
                break;
            case WRITECOIL:         //д��Ȧ
                if (true == FpCheckCrcLrc(fu8p_Array, 6))        //������ȷ
                {
                    Modbus_Write_CoilDeal(fu8p_Array);
                }
                break;
            default:                //��֧�ֵĹ�����
                Modbus_Error(FUNCTIONERRO, fu8p_Array);
                break;
        }
    }
}

/***********************************************************************
�� �� ����void IRQ_ModbusRTU_UART0(void)
��    �ܣ�����0�жϷ������
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ�jzt                  ��    �ڣ�2007-7-24 14:11
��    �ģ��Ժ���               ��    �ڣ�2011-5-11
***********************************************************************/
void IRQ_ModbusRTU_UART0(void)
{
    u32 i;
    u16 UARTStatus;
    u8 u8Data=0;
    u8 u8DataHi = 0;    //�洢UART1->RxBUFR��8λ��֡�����У��λ
    
    //��ȡ״̬�Ĵ���
    UARTStatus=UART_FlagStatus(UART0);
    
    //��ʱ�ж�
    if (UARTStatus&UART_TimeOutIdle)
    {
        if (DelayT15==DelayType_UART0)
        {
            bOverT15_UART0=true;
            //���ó�ʱ�ǿ��жϵĳ�ʱ����Ϊ2���ַ�
            UART_TimeOutPeriodConfig(UART0,22);
            DelayType_UART0=DelayT35;
        }
        else if ((DelayT35==DelayType_UART0)&&(true==bOverT15_UART0))
        {
            bOverT35_UART0=true;
            if (true==bBeginReceive_UART0)
            {
                bBeginReceive_UART0=false;
                bFinishReceive_UART0=true;
                DisableRecIRQ_UART0();      //�رս����ж�
            }
            UART_ItConfig(UART0,UART_TimeOutIdle,DISABLE);
            DelayType_UART0=DelayNo;
        }
    }
    
    //�����ݽ���
    if (UARTStatus&UART_RxBufNotEmpty)
    {
        u8Data=UART0->RxBUFR;        
        u8DataHi = (UART0->RxBUFR >> 8);
        //������ʱ��ʱ�����ó�ʱ�ǿ��жϵĳ�ʱ����Ϊ1.5���ַ�
        UART_TimeOutPeriodConfig(UART0,17);
        DelayType_UART0=DelayT15;
        UART_ItConfig(UART0,UART_TimeOutIdle,ENABLE);
        
        if (true==bOverT15_UART0)
        {
            bOverT15_UART0=false;
            if (true==bOverT35_UART0)
            {
                bOverT35_UART0=false;
                bFinishReceive_UART0=false;
                //����ַ���ϻ����ǹ㲥��ַ����ʼ����
//                if ((u8Data==u8ModbusAddr_UART0)||(0==u8Data))   //Ϊ���ͨѶɾ��
//                {
                    bBeginReceive_UART0=true;
                    gu8_RxdArray_UART0[0]=u8Data;
                    gu8_DebugRxdArray_UART0[0] = u8DataHi;    //�������Զ�ƥ����ʹ��
                    ulInsertPos_UART0=1;
                    ulFrameLength_UART0=1;
//                }
            }
            else
            {
                bBeginReceive_UART0=false;
            }
        }
        else
        {
            if (true==bBeginReceive_UART0)
            {
                gu8_RxdArray_UART0[ulInsertPos_UART0]=u8Data;
                gu8_DebugRxdArray_UART0[ulInsertPos_UART0] = u8DataHi;    //�������Զ�ƥ����ʹ��
                ulInsertPos_UART0=(ulInsertPos_UART0+1)%MAX(RXDLEN_BUS_R,RXDLEN_BUS_A);
                ulFrameLength_UART0+=1;
                
//                do
//              {
//                  gu8_RxdArray_UART0[ulInsertPos]=UART0->RxBUFR;
//                  ulInsertPos=(ulInsertPos+1)%RXBUFSIZE;
//                  ulFrameLength+=1;
//              }
//              while(UART_FlagStatus(UART0)&(u16)UART_RxBufNotEmpty);
            }
        }
    }
    
    //��������պͻ�����ȫ��������ж�
    if (true==bUARTSending_UART0)
    {
        //��Ϊ�����������ж�
        if (UARTStatus&UART_TxHalfEmpty)
        {
            //���ͻ������Ƿ�������
            if (ulTBUFAvailNum_UART0>0)
            {
                if (ulTBUFAvailNum_UART0>=8)
                {
                    for(i=0;i<8;i++)
                    {
                        UART0->TxBUFR=gu8_TxdArray_UART0[ulTBUFBegin_UART0];
                        ulTBUFBegin_UART0=(ulTBUFBegin_UART0+1)%TXDLEN_BUS_R;
                    }
                    ulTBUFAvailNum_UART0-=8;
                }
                else
                {
                    for(i=0;i<ulTBUFAvailNum_UART0;i++)
                    {
                        UART0->TxBUFR=gu8_TxdArray_UART0[ulTBUFBegin_UART0];
                        ulTBUFBegin_UART0=(ulTBUFBegin_UART0+1)%TXDLEN_BUS_R;
                    }
                    ulTBUFAvailNum_UART0=0;
                    
                    UART_ItConfig(UART0,UART_TxHalfEmpty,DISABLE);
                }
            }
            else
            {
                UART_ItConfig(UART0,UART_TxHalfEmpty,DISABLE);
            }
            
            //���ڶ԰�յĲ������ܻ����״̬������Ҫ����һ��
            UARTStatus=UART_FlagStatus(UART0);
        }
        
        if (UARTStatus&UART_TxEmpty)
        {
            if (ulTBUFAvailNum_UART0==0)
            {
                bUARTSending_UART0=false; //����û�з��Ͳ���
                DisableSendIRQ_UART0();
                EnableRecIRQ_UART0();
                Sio_485_Enable();
                gb_S485Recieve = true;
            }
        }
    }
    else
    {
        DisableSendIRQ_UART0();
        EnableRecIRQ_UART0();
        Sio_485_Enable();
    }
}

/***********************************************************************
�� �� ����void IRQ_Modbus_RTU_UART1(void)
��    �ܣ�����0�жϷ������
˵    ����
��ڲ�����
������Դ��
�� �� ֵ����
��    �ƣ�jzt                  ��    �ڣ�2007-7-24 14:11
��    �ģ��Ժ���               ��    �ڣ�2011-5-11
***********************************************************************/
void IRQ_Modbus_RTU_UART1(void)
{
    u32 i;
    u16 UARTStatus;
    u8 u8Data=0;
    u8 u8DataHi = 0;    //�洢UART1->RxBUFR��8λ��֡�����У��λ
    
    //��ȡ״̬�Ĵ���
    UARTStatus=UART_FlagStatus(UART1);
    
    //��ʱ�ж�
    if (UARTStatus&UART_TimeOutIdle)
    {
        if (DelayT15==DelayType_UART1)
        {
            bOverT15_UART1=true;
            //���ó�ʱ�ǿ��жϵĳ�ʱ����Ϊ2���ַ�
            UART_TimeOutPeriodConfig(UART1,22);
            DelayType_UART1=DelayT35;
        }
        else if ((DelayT35==DelayType_UART1)&&(true==bOverT15_UART1))
        {
            bOverT35_UART1=true;
            if (true==bBeginReceive_UART1)
            {
                bBeginReceive_UART1=false;
                bFinishReceive_UART1=true;
                DisableRecIRQ_UART1();      //�رս����ж�
            }
            UART_ItConfig(UART1,UART_TimeOutIdle,DISABLE);
            DelayType_UART1=DelayNo;
        }
    }
    
    //�����ݽ���
    if (UARTStatus&UART_RxBufNotEmpty)
    {
        u8Data=UART1->RxBUFR;        
        u8DataHi = (UART1->RxBUFR >> 8);
        //������ʱ��ʱ�����ó�ʱ�ǿ��жϵĳ�ʱ����Ϊ1.5���ַ�
        UART_TimeOutPeriodConfig(UART1,17);
        DelayType_UART1=DelayT15;
        UART_ItConfig(UART1,UART_TimeOutIdle,ENABLE);
        
        if (true==bOverT15_UART1)
        {
            bOverT15_UART1=false;
            if (true==bOverT35_UART1)
            {
                bOverT35_UART1=false;
                bFinishReceive_UART1=false;
                //����ַ���ϻ����ǹ㲥��ַ����ʼ����
//                if ((u8Data==u8ModbusAddr_UART1)||(0==u8Data))   //Ϊ���ͨѶɾ��
//                {
                    bBeginReceive_UART1=true;
                    gu8_RxdArray_UART1[0]=u8Data;
                    gu8_DebugRxdArray_UART1[0] = u8DataHi;    //�������Զ�ƥ����ʹ��
                    ulInsertPos_UART1=1;
                    ulFrameLength_UART1=1;
//                }
            }
            else
            {
                bBeginReceive_UART1=false;
            }
        }
        else
        {
            if (true==bBeginReceive_UART1)
            {
                gu8_RxdArray_UART1[ulInsertPos_UART1]=u8Data;
                gu8_DebugRxdArray_UART1[ulInsertPos_UART1] = u8DataHi;    //�������Զ�ƥ����ʹ��
                ulInsertPos_UART1=(ulInsertPos_UART1+1)%MAX(RXDLEN_BUS_R,RXDLEN_BUS_A);
                ulFrameLength_UART1+=1;
                
//                do
//              {
//                  gu8_RxdArray_UART1[ulInsertPos]=UART1->RxBUFR;
//                  ulInsertPos=(ulInsertPos+1)%RXBUFSIZE;
//                  ulFrameLength+=1;
//              }
//              while(UART_FlagStatus(UART1)&(u16)UART_RxBufNotEmpty);
            }
        }
    }
    
    //��������պͻ�����ȫ��������ж�
    if (true==bUARTSending_UART1)
    {
        //��Ϊ�����������ж�
        if (UARTStatus&UART_TxHalfEmpty)
        {
            //���ͻ������Ƿ�������
            if (ulTBUFAvailNum_UART1>0)
            {
                if (ulTBUFAvailNum_UART1>=8)
                {
                    for(i=0;i<8;i++)
                    {
                        UART1->TxBUFR=gu8_TxdArray_UART1[ulTBUFBegin_UART1];
                        ulTBUFBegin_UART1=(ulTBUFBegin_UART1+1)%TXDLEN_BUS_R;
                    }
                    ulTBUFAvailNum_UART1-=8;
                }
                else
                {
                    for(i=0;i<ulTBUFAvailNum_UART1;i++)
                    {
                        UART1->TxBUFR=gu8_TxdArray_UART1[ulTBUFBegin_UART1];
                        ulTBUFBegin_UART1=(ulTBUFBegin_UART1+1)%TXDLEN_BUS_R;
                    }
                    ulTBUFAvailNum_UART1=0;
                    
                    UART_ItConfig(UART1,UART_TxHalfEmpty,DISABLE);
                }
            }
            else
            {
                UART_ItConfig(UART1,UART_TxHalfEmpty,DISABLE);
            }
            
            //���ڶ԰�յĲ������ܻ����״̬������Ҫ����һ��
            UARTStatus=UART_FlagStatus(UART1);
        }
        
        if (UARTStatus&UART_TxEmpty)
        {
            if (ulTBUFAvailNum_UART1==0)
            {
                bUARTSending_UART1=false; //����û�з��Ͳ���
                DisableSendIRQ_UART1();
                EnableRecIRQ_UART1();
//              Sio_485_Enable();
            }
        }
    }
    else
    {
        DisableSendIRQ_UART1();
        EnableRecIRQ_UART1();
//        Sio_485_Enable();
    }
}


