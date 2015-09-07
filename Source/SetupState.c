/*
Description:            ��������������غ���
Author:                 �Ժ���
Date:                   2013-12-9
*/
#include "include.h"


#define SETUP_CHECKCODE     0           //����������������У��
#define DISP_SETUP          1           //��ʾ"SEtUP"
#define SETUP_B1            2           //Mode ���幤��ģʽ��ز���
#define SETUP_B1_1          3           //����ģʽ
#define SETUP_B1_2          4           //�޶�ë����
#define SETUP_B1_3          5           //���Ϸ�ʽ
#define SETUP_B1_4          6           //�Զ�������  
#define SETUP_B1_5          7           //���ȳ�ʱʱ��
#define SETUP_B1_6          8           //����ʾ����
#define SETUP_B2            9           //Base ���������������
#define SETUP_B2_1          10          //���㷶Χ      
#define SETUP_B2_2          11          //���ȷ�Χ      
#define SETUP_B2_3          12          //�����ٷ�Χ  
#define SETUP_B2_4          13          //AD�����˲����� 
#define SETUP_B2_5          14          //ж���˲�����   
#define SETUP_B2_6          15          //��ֵ�˲�����   
#define SETUP_B2_7          16          //AD��������
#define SETUP_B2_8          17          //��չ�ӿ����� 
#define SETUP_B3            18          //Switch ���ܿ��ز���        
#define SETUP_B3_1          19          //�ϵ��Զ����㿪��      
#define SETUP_B3_2          20          //�ֶ�ж���ۼƿ���      
#define SETUP_B3_3          21          //��ֵ�������ֿ���      
#define SETUP_B3_4          22          //�ۼƲ�ѯ���뿪��      
#define SETUP_B3_5          23          //�ۼ�������뿪��      
#define SETUP_B3_6          24          //�ۼƷ�Χ��չ����
#define SETUP_B4            25          //Et1 ��չ��1����       
#define SETUP_B4_1          26          //ͨѶ��ʽ              
#define SETUP_B4_2          27          //�豸��                
#define SETUP_B4_3          28          //������                
#define SETUP_B4_4          29          //���ݸ�ʽ              
#define SETUP_B4_5          30          //modbus�ߵ���˳��      
#define SETUP_B4_6          31          //�Զ���ӡ����          
#define SETUP_B4_7          32          //��ӡ��ʽ
#define SETUP_B4_8          33          //��ӡ����  
#define SETUP_B4_9          34          //��ӡ��ֽ����
#define SETUP_B5            35          //Et2 ��չ��2����       
#define SETUP_B5_1          36          //ͨѶ��ʽ              
#define SETUP_B5_2          37          //�豸��                
#define SETUP_B5_3          38          //������                
#define SETUP_B5_4          39          //���ݸ�ʽ              
#define SETUP_B5_5          40          //modbus�ߵ���˳��      
#define SETUP_B5_6          41          //�Զ���ӡ����          
#define SETUP_B5_7          42          //��ӡ��ʽ
#define SETUP_B5_8          43          //��ӡ����  
#define SETUP_B5_9          44          //��ӡ����  
#define SETUP_B6            45          //no2 ˫�޶�����ģʽ��ز���
#define SETUP_B6_1          46          //˫�޶��ӻ���ģʽͬʱ�ɴ�����
#define SETUP_B6_2          47          //���ͻ�������ʱʱ��
#define SETUP_B6_3          48          //���ͻ�����ʱ��
#define SETUP_B6_4          49          //�ٴμд���ʱ��������ʱ��
#define SETUP_B7            50          //����Ӧ����
#define SETUP_B7_1          51          //��Ͷ����Ӧ����
#define SETUP_B7_2          52          //��Ͷ����������� %
#define SETUP_B7_3          53          //��Ͷ�����ȼ� 1~8
#define SETUP_B7_4          54          //��Ͷ����ʱ��ֲ���Χ
#define SETUP_B7_5          55          //СͶ����Ӧ����
#define SETUP_B7_6          56          //СͶ����������� %
#define SETUP_B7_7          57          //СͶ�������� 1~3
#define SETUP_B7_8          58          //
#define SETUP_B7_9          59          //
#define SETUP_B8            60          //�����������뿪��      
#define SETUP_B8_1          61          //������������          
#define SETUP_END           62




struct SETUP gs_Setup;

u32 gu32_SetupCodeSwitch;              //�����������뿪��
u32 gu32_SetupCode;                    //������������

u8 gu8_SetupInTime = 0;                //����������������������


const u16 gu16_SetupRealItem[]=       //������ʾ�����½Ǳ�
//�������� setup     
  {0,      1,        
// B1   B1.1 B1.2 B1.3 B1.4 B1.5 B1.6
   10,  11,  12,  13,  14,  15,  16, 
// B2   B2.1  B2.2  B2.3  B2.4  B2.5  B2.6  B2.7  B2.8
   20,  21,   22 ,  23,   24,   25,   26,   27,   28,
// B3   B3.1  B3.2  B3.3  B3.4  B3.5  B3.6
   30,  31,   32,   33,   34,   35,   36, 
// B4   B4.1  B4.2  B4.3  B4.4  B4.5  B4.6  B4.7  B4.8  B4.9
   40,  41,   42,   43,   44,   45,   46,   47,   48,   49,
// B5   B5.1  B5.2  B5.3  B5.4  B5.5  B5.6  B5.7  B5.8  B5.9
   50,  51,   52,   53,   54,   55,   56,   57,   58,   59,
// B6   B6.1  B6.2  B6.3  B6.4
   60,  61,   62,   63,   64,
// B7   B7.1  B7.2  B7.3  B7.4  B7.5  B7.6  B7.7  B7.8  B7.9
   70,  71,   72,   73,   74,   75,   76,   77,   78,   79,
// B8   B8.1
   80,  81};


const u8 gu8_SetupRightItem[] =        //�����������һ����
//�������� setup     
  {0,      SETUP_B1, 
// B1        B1.1        B1.2        B1.3        B1.4        B1.5        B1.6       
   SETUP_B2, SETUP_B1_2, SETUP_B1_3, SETUP_B1_4, SETUP_B1_5, SETUP_B1_6, SETUP_B1_1,
// B2        B2.1        B2.2        B2.3        B2.4        B2.5        B2.6        B2.7        B2.8      
   SETUP_B3, SETUP_B2_2, SETUP_B2_3, SETUP_B2_4, SETUP_B2_5, SETUP_B2_6, SETUP_B2_7, SETUP_B2_1, SETUP_B2_1,
// B3        B3.1        B3.2        B3.3        B3.4        B3.5        B3.6       
   SETUP_B4, SETUP_B3_2, SETUP_B3_3, SETUP_B3_4, SETUP_B3_5, SETUP_B3_6, SETUP_B3_1,
// B4        B4.1        B4.2        B4.3        B4.4        B4.5        B4.6        B4.7        B4.8        B4.9
   SETUP_B5, SETUP_B4_2, SETUP_B4_3, SETUP_B4_4, SETUP_B4_5, SETUP_B4_6, SETUP_B4_7, SETUP_B4_8, SETUP_B4_9, SETUP_B4_1,
// B5        B5.1        B5.2        B5.3        B5.4        B5.5        B5.6        B5.7        B5.8        B5.9
   SETUP_B6, SETUP_B5_2, SETUP_B5_3, SETUP_B5_4, SETUP_B5_5, SETUP_B5_6, SETUP_B5_7, SETUP_B5_8, SETUP_B5_9, SETUP_B5_1,
// B6        B6.1        B6.2        B6.3        B6.4
   SETUP_B8, SETUP_B6_2, SETUP_B6_3, SETUP_B6_4, SETUP_B6_1,
// B7        B7.1        B7.2        B7.3        B7.4        B7.5        B7.6        B7.7        B7.8        B7.9
   SETUP_B8, SETUP_B7_2, SETUP_B7_3, SETUP_B7_4, SETUP_B7_5, SETUP_B7_6, SETUP_B7_7, SETUP_B7_8, SETUP_B7_9, SETUP_B7_1,
// B8        B8.1
   SETUP_B1, SETUP_B8_1};
   
const u8 gu8_SetupEnterItem[] =        //��ENTER�������һ����
//��������     setup     
  {DISP_SETUP, SETUP_B1, 
// B1          B1.1        B1.2        B1.3        B1.4        B1.5        B1.6       
   SETUP_B1_1, SETUP_B1_2, SETUP_B1_3, SETUP_B1_4, SETUP_B1_5, SETUP_B1_6, SETUP_B1_1,
// B2          B2.1        B2.2        B2.3        B2.4        B2.5        B2.6        B2.7        B2.8      
   SETUP_B2_1, SETUP_B2_2, SETUP_B2_3, SETUP_B2_4, SETUP_B2_5, SETUP_B2_6, SETUP_B2_7, SETUP_B2_1, SETUP_B2_1,
// B3          B3.1        B3.2        B3.3        B3.4        B3.5        B3.6       
   SETUP_B3_1, SETUP_B3_2, SETUP_B3_3, SETUP_B3_4, SETUP_B3_5, SETUP_B3_6, SETUP_B3_1,
// B4          B4.1        B4.2        B4.3        B4.4        B4.5        B4.6        B4.7        B4.8        B4.9       
   SETUP_B4_1, SETUP_B4_2, SETUP_B4_3, SETUP_B4_4, SETUP_B4_5, SETUP_B4_6, SETUP_B4_7, SETUP_B4_8, SETUP_B4_9, SETUP_B4_1,
// B5          B5.1        B5.2        B5.3        B5.4        B5.5        B5.6        B5.7        B5.8        B5.9       
   SETUP_B5_1, SETUP_B5_2, SETUP_B5_3, SETUP_B5_4, SETUP_B5_5, SETUP_B5_6, SETUP_B5_7, SETUP_B5_8, SETUP_B5_9, SETUP_B5_1,
// B6          B6.1        B6.2        B6.3        B6.4
   SETUP_B6_1, SETUP_B6_2, SETUP_B6_3, SETUP_B6_4, SETUP_B6_1,
// B7          B7.1        B7.2        B7.3        B7.4        B7.5        B7.6        B7.7        B7.8        B7.9
   SETUP_B7_1, SETUP_B7_2, SETUP_B7_3, SETUP_B7_4, SETUP_B7_5, SETUP_B7_6, SETUP_B7_7, SETUP_B7_8, SETUP_B7_9, SETUP_B7_1,
// B8          B8.1
   SETUP_B8_1, SETUP_B8};



/*********************************************************************
��������: u32 GetSetupItemValue(u8 fuc_Item)
��    ��: �õ���Ӧ�����Ĳ���ֵ
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-3-11
��    ��:                      ʱ    ��: 
*********************************************************************/
u32 GetSetupItemValue(u8 fuc_Item)
{
    u32 ful_Value;
    
    switch(fuc_Item)
    {
        case SETUP_B1_1:
            ful_Value = gs_Setup.TareMode; break;
        case SETUP_B1_2:
            ful_Value = gs_Setup.GorNMode; break;
        case SETUP_B1_3:
            ful_Value = gs_Setup.FeedMode; break;
        case SETUP_B1_4:
            ful_Value = gs_Setup.AutoClrZeroInterval; break;
        case SETUP_B1_5:
            ful_Value = gs_Setup.JudgeStabOverTime; break;
        case SETUP_B1_6:
            ful_Value = gs_Setup.AuxDispType; break;
        case SETUP_B2_1:
            ful_Value = gs_Setup.ClrZeroRng; break;
        case SETUP_B2_2:
            ful_Value = gs_Setup.JudgeStabRng; break;
        case SETUP_B2_3:
            ful_Value = gs_Setup.TraceZeroRng; break;
        case SETUP_B2_4:
            ful_Value = gs_Setup.AdFilterLevel; break;
        case SETUP_B2_5:
            ful_Value = gs_Setup.AdFilterLevelDisc; break;
        case SETUP_B2_6:
            ful_Value = gs_Setup.AdFilterLevelComp; break;
        case SETUP_B2_7:
            ful_Value = gs_Setup.AdSamplingRate; break;
        case SETUP_B2_8:
            ful_Value = gs_Setup.ExtType; break;
        case SETUP_B3_1:
            ful_Value = gs_Setup.PowerOnZeroSwitch; break;
        case SETUP_B3_2:
            ful_Value = gs_Setup.DiscSumSwitch; break;
        case SETUP_B3_3:
            ful_Value = gs_Setup.ResultHoldSwitch; break;
        case SETUP_B3_4:
            ful_Value = gs_Setup.SumCheckCodeSwitch; break;
        case SETUP_B3_5:
            ful_Value = gs_Setup.SumClrCodeSwitch; break;
        case SETUP_B3_6:
            ful_Value = gs_Setup.SumExtendSwitch; break;
        case SETUP_B4_1:
            ful_Value = gs_Setup.ComMode_1; break;
        case SETUP_B4_2:
            ful_Value = gs_Setup.TareNumber_1; break;
        case SETUP_B4_3: 
            if (gu8_ExtType == PBUS_UART)
                ful_Value = gu32_GSDType;
            else
                ful_Value = gs_Setup.BaudRate_1; break;
        case SETUP_B4_4:
            if (gu8_ExtType == PBUS_UART)
                ful_Value = gu32_FollowMasterSwitch; 
            else
                ful_Value = gs_Setup.ParityMode_1; break;
        case SETUP_B4_5:
            ful_Value = gs_Setup.HiLo_1; break;
        case SETUP_B4_6:
            ful_Value = gs_Setup.PrintSwitch_1; break;
        case SETUP_B4_7:
            ful_Value = gs_Setup.PrintType_1; break;
        case SETUP_B4_8:
            ful_Value = gs_Setup.PrintLanguage_1; break;
        case SETUP_B4_9:
            ful_Value = gs_Setup.PrintBlankRows_1; break;
        case SETUP_B5_1:
            ful_Value = gs_Setup.ComMode_2; break;
        case SETUP_B5_2:
            ful_Value = gs_Setup.TareNumber_2; break;
        case SETUP_B5_3:
            ful_Value = gs_Setup.BaudRate_2; break;
        case SETUP_B5_4:
            ful_Value = gs_Setup.ParityMode_2; break;
        case SETUP_B5_5:
            ful_Value = gs_Setup.HiLo_2; break;
        case SETUP_B5_6:
            ful_Value = gs_Setup.PrintSwitch_2; break;
        case SETUP_B5_7:
            ful_Value = gs_Setup.PrintType_2; break;
        case SETUP_B5_8:
            ful_Value = gs_Setup.PrintLanguage_2; break;
        case SETUP_B5_9:
            ful_Value = gs_Setup.PrintBlankRows_2; break;
        case SETUP_B6_1:
            ful_Value = gs_Setup.No2PackOffTwoSwitch; break;
        case SETUP_B6_2:
            ful_Value = gs_Setup.No2ConveyorDelayTime; break;
        case SETUP_B6_3:
            ful_Value = gs_Setup.No2ConveyorRunTime; break;
        case SETUP_B6_4:
            ful_Value = gs_Setup.No2AddAgainDelayTime; break;
        case SETUP_B7:
            ful_Value = gs_Setup.AdaptSW; break;
        case SETUP_B7_1:
            ful_Value = gs_Setup.AdaptSP2SW; break;
        case SETUP_B7_2:
            ful_Value = gs_Setup.AdaptSP2LimitRng; break;
        case SETUP_B7_3:
            ful_Value = gs_Setup.AdaptSP2Level; break;
        case SETUP_B7_4:
            ful_Value = gs_Setup.AdaptSP2TimeThreshold; break;
        case SETUP_B7_5:
            ful_Value = gs_Setup.AdaptSP3SW; break;
        case SETUP_B7_6:
            ful_Value = gs_Setup.AdaptSP3LimitRng; break;
        case SETUP_B7_7:
            ful_Value = gs_Setup.AdaptSP3Scope; break;
        case SETUP_B7_8:
            ful_Value = gs_Setup.AdaptSP2Scope; break;
        case SETUP_B7_9:
            ful_Value = gs_Setup.Adapt7_9; break;
        case SETUP_B8:      //�����������뿪��             
            ful_Value = gu32_SetupCodeSwitch; break;
        case SETUP_B8_1:    //������������                 
            ful_Value = gu32_SetupCode; break;
        default:
            ful_Value = 0; break;
    }
    
    return ful_Value;
}

/*********************************************************************
��������: u16 GetSetupPort(fuc_Item)
��    ��: �õ�����������Ӧ�Ĵ洢��ַ
˵    ��: 
��ڲ���: fuc_Item = ������
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-3-11
��    ��:                      ʱ    ��: 
*********************************************************************/
u16 GetSetupPort(u8 fuc_Item)
{
    u16 lui_FMAddress = 0;
    
    switch (fuc_Item)
    {
        case SETUP_B1_1:
            gs_Setup.TareMode = ulParameter.ul;
            lui_FMAddress = FMAddr_TareMode;
            break;
        case SETUP_B1_2:
            gs_Setup.GorNMode = ulParameter.ul;
            lui_FMAddress = FMAddr_GorNMode;
            break;
        case SETUP_B1_3:
            gs_Setup.FeedMode = ulParameter.ul;
            lui_FMAddress = FMAddr_FeedMode;
            break;
        case SETUP_B1_4:
            gs_Setup.AutoClrZeroInterval = ulParameter.ul;
            lui_FMAddress = FMAddr_AutoClrZeroInterval;
            break;
        case SETUP_B1_5:
            gs_Setup.JudgeStabOverTime = ulParameter.ul;
            lui_FMAddress = FMAddr_JudgeStabOverTime;
            break;
        case SETUP_B1_6:
            gs_Setup.AuxDispType = ulParameter.ul;
            lui_FMAddress = FMAddr_AuxDispType;
            break;
        case SETUP_B2_1:
            gs_Setup.ClrZeroRng = ulParameter.ul;
            lui_FMAddress = FMAddr_ClrZeroRng;
            break;
        case SETUP_B2_2:
            gs_Setup.JudgeStabRng = ulParameter.ul;
            lui_FMAddress = FMAddr_JudgeStabRng;
            break;
        case SETUP_B2_3:
            gs_Setup.TraceZeroRng = ulParameter.ul;
            lui_FMAddress = FMAddr_TraceZeroRng;
            break;
        case SETUP_B2_4:
            gs_Setup.AdFilterLevel = ulParameter.ul;
            lui_FMAddress = FMAddr_AdFilterLevel;
            break;
        case SETUP_B2_5:
            gs_Setup.AdFilterLevelDisc = ulParameter.ul;
            lui_FMAddress = FMAddr_AdFilterLevelDisc;
            break;
        case SETUP_B2_6:
            gs_Setup.AdFilterLevelComp = ulParameter.ul;
            lui_FMAddress = FMAddr_AdFilterLevelComp;
            break;
        case SETUP_B2_7:
            gs_Setup.AdSamplingRate = ulParameter.ul;
            lui_FMAddress = FMAddr_AdSamplingRate;
            break;
        case SETUP_B2_8:
            gs_Setup.ExtType = ulParameter.ul;
            lui_FMAddress = FMAddr_ExtType;
            break;
        case SETUP_B3_1:
            gs_Setup.PowerOnZeroSwitch = ulParameter.ul;
            lui_FMAddress = FMAddr_PowerOnZeroSwitch;
            break;
        case SETUP_B3_2:
            gs_Setup.DiscSumSwitch = ulParameter.ul;
            lui_FMAddress = FMAddr_DiscSumSwitch;
            break;
        case SETUP_B3_3:
            gs_Setup.ResultHoldSwitch = ulParameter.ul;
            lui_FMAddress = FMAddr_ResultHoldSwitch;
            break;
        case SETUP_B3_4:
            gs_Setup.SumCheckCodeSwitch = ulParameter.ul;
            lui_FMAddress = FMAddr_SumCheckCodeSwitch;
            break;
        case SETUP_B3_5:
            gs_Setup.SumClrCodeSwitch = ulParameter.ul;
            lui_FMAddress = FMAddr_SumClrCodeSwitch;
            break;
        case SETUP_B3_6:
            gs_Setup.SumExtendSwitch = ulParameter.ul;
            lui_FMAddress = FMAddr_SumExtendSwitch;
            break;
        case SETUP_B4_1:
            gs_Setup.ComMode_1 = ulParameter.ul;
            lui_FMAddress = FMAddr_ComMode_1;
            break;
        case SETUP_B4_2:
            gs_Setup.TareNumber_1 = ulParameter.ul;
            lui_FMAddress = FMAddr_TareNumber_1;
            break;
        case SETUP_B4_3:
            if (gu8_ExtType == PBUS_UART)
            {
                gu32_GSDType = ulParameter.ul;
                lui_FMAddress = FMAddr_GSDType;
            }
            else
            {
                gs_Setup.BaudRate_1 = ulParameter.ul;
                lui_FMAddress = FMAddr_BaudRate_1;
            }
            break;
        case SETUP_B4_4:
            if (gu8_ExtType == PBUS_UART)
            {
                gu32_FollowMasterSwitch = ulParameter.ul;
                lui_FMAddress = FMAddr_FollowMasterSwitch;
            }
            else
            {
                gs_Setup.ParityMode_1 = ulParameter.ul;
                lui_FMAddress = FMAddr_ParityMode_1;
            }
            break;
        case SETUP_B4_5:
            gs_Setup.HiLo_1 = ulParameter.ul;
            lui_FMAddress = FMAddr_HiLo_1;
            break;
        case SETUP_B4_6:
            gs_Setup.PrintSwitch_1 = ulParameter.ul;
            lui_FMAddress = FMAddr_PrintSwitch_1;
            break;
        case SETUP_B4_7:
            gs_Setup.PrintType_1 = ulParameter.ul;
            lui_FMAddress = FMAddr_PrintType_1;
            break;
        case SETUP_B4_8:
            gs_Setup.PrintLanguage_1 = ulParameter.ul;
            lui_FMAddress = FMAddr_PrintLanguage_1;
            break;
        case SETUP_B4_9:
            gs_Setup.PrintBlankRows_1 = ulParameter.ul;
            lui_FMAddress = FMAddr_PrintBlankRows_1;
            break;
        case SETUP_B5_1:
            gs_Setup.ComMode_2 = ulParameter.ul;
            lui_FMAddress = FMAddr_ComMode_2;
            break;
        case SETUP_B5_2:
            gs_Setup.TareNumber_2 = ulParameter.ul;
            lui_FMAddress = FMAddr_TareNumber_2;
            break;
        case SETUP_B5_3:
            gs_Setup.BaudRate_2 = ulParameter.ul;
            lui_FMAddress = FMAddr_BaudRate_2;
            break;
        case SETUP_B5_4:
            gs_Setup.ParityMode_2 = ulParameter.ul;
            lui_FMAddress = FMAddr_ParityMode_2;
            break;
        case SETUP_B5_5:
            gs_Setup.HiLo_2 = ulParameter.ul;
            lui_FMAddress = FMAddr_HiLo_2;
            break;
        case SETUP_B5_6:
            gs_Setup.PrintSwitch_2 = ulParameter.ul;
            lui_FMAddress = FMAddr_PrintSwitch_2;
            break;
        case SETUP_B5_7:
            gs_Setup.PrintType_2 = ulParameter.ul;
            lui_FMAddress = FMAddr_PrintType_2;
            break;
        case SETUP_B5_8:
            gs_Setup.PrintLanguage_2 = ulParameter.ul;
            lui_FMAddress = FMAddr_PrintLanguage_2;
            break;
        case SETUP_B5_9:
            gs_Setup.PrintBlankRows_2 = ulParameter.ul;
            lui_FMAddress = FMAddr_PrintBlankRows_2;
            break;
        case SETUP_B6_1:
            gs_Setup.No2PackOffTwoSwitch = ulParameter.ul;
            lui_FMAddress = FMAddr_No2PackOffTwoSwitch;
            break;
        case SETUP_B6_2:
            gs_Setup.No2ConveyorDelayTime = ulParameter.ul;
            lui_FMAddress = FMAddr_No2ConveyorDelayTime;
            break;
        case SETUP_B6_3:
            gs_Setup.No2ConveyorRunTime = ulParameter.ul;
            lui_FMAddress = FMAddr_No2ConveyorRunTime;
            break;
        case SETUP_B6_4:
            gs_Setup.No2AddAgainDelayTime = ulParameter.ul;
            lui_FMAddress = FMAddr_No2AddAgainDelayTime;
            break;
        case SETUP_B7:
            gs_Setup.AdaptSW = ulParameter.ul;
            lui_FMAddress = FMAddr_AdaptSW;
            break;
        case SETUP_B7_1:
            gs_Setup.AdaptSP2SW = ulParameter.ul;
            lui_FMAddress = FMAddr_AdaptSP2SW;
            break;
        case SETUP_B7_2:
            gs_Setup.AdaptSP2LimitRng = ulParameter.ul;
            lui_FMAddress = FMAddr_AdaptSP2LimitRng;
            break;
        case SETUP_B7_3:
            gs_Setup.AdaptSP2Level = ulParameter.ul;
            lui_FMAddress = FMAddr_AdaptSP2Level;
            break;
        case SETUP_B7_4:
            gs_Setup.AdaptSP2TimeThreshold = ulParameter.ul;
            lui_FMAddress = FMAddr_AdaptSP2TimeThreshold;
            break;
        case SETUP_B7_5:
            gs_Setup.AdaptSP3SW = ulParameter.ul;
            lui_FMAddress = FMAddr_AdaptSP3SW;
            break;
        case SETUP_B7_6:
            gs_Setup.AdaptSP3LimitRng = ulParameter.ul;
            lui_FMAddress = FMAddr_AdaptSP3LimitRng;
            break;
        case SETUP_B7_7:
            gs_Setup.AdaptSP3Scope = ulParameter.ul;
            lui_FMAddress = FMAddr_AdaptSP3Scope;
            break;
        case SETUP_B7_8:
            gs_Setup.AdaptSP2Scope = ulParameter.ul;
            lui_FMAddress = FMAddr_AdaptSP2Scope;
            break;
        case SETUP_B7_9:
            gs_Setup.Adapt7_9 = ulParameter.ul;
            lui_FMAddress = FMAddr_Adapt7_9;
            break;
        case SETUP_B8:      //�����������뿪��             
            gu32_SetupCodeSwitch = ulParameter.ul;
            lui_FMAddress = FMAddr_SetupCodeSwitch;
            break;
        case SETUP_B8_1:    //������������                 
            gu32_SetupCode = ulParameter.ul;
            lui_FMAddress = FMAddr_SetupCode;
            break;
        default:
            break;
    }
    return lui_FMAddress;
}

/*********************************************************************
��������: u8 GetSetupNextItem(u8 fu8_Item, bool fb_RightEnterFlg)
��    ��: �������������һ��
˵    ��: 
��ڲ���: fu8_Item:��ǰItem   fb_RightEnterFlg:0-Right�� 1-Enter��
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-4-8
��    ��:                      ʱ    ��: 
*********************************************************************/
u8 GetSetupNextItem(u8 fu8_Item, bool fb_RightEnterFlg)
{
    if (fb_RightEnterFlg == false)
    {   //�Ҽ�������Ŀ����
        fu8_Item = gu8_SetupRightItem[fu8_Item];    //��ȡ����������Ŀ
    }
    else
    {
        //Enter��������Ŀ����
        fu8_Item = gu8_SetupEnterItem[fu8_Item];         //������һ��
    }
    if (gs_Setup.TareMode != NO2_A && gs_Setup.TareMode != NO2_B)
    {   //���޶�ģʽ��û��B6ѡ��
        if (fu8_Item >= SETUP_B6 && fu8_Item < SETUP_B7)
        {
            fu8_Item = SETUP_B7;
        }
    }
    
//COM_PRINT       0   //��ӡ
//COM_CONT        1   //cont������ʽ
//COM_READ        2   //read���ʽ
//COM_READ_O      3   //read���ʽ
//COM_BUS_R       4   //Modbus RTU��ʽ
//COM_BUS_A       5   //Modbus ASCII��ʽ
//COM_PBUS        6   //PROFIBUSͨѶ
    if (fu8_Item == SETUP_B4_5)
    {   //PROFIBUSͨѶֻ��ǰ4��
        if (gs_Setup.ComMode_1 == COM_PBUS)
            fu8_Item = SETUP_B4_1;
    }
    if (fu8_Item == SETUP_B4_5)
    {   //Modbus��ʽ����ѡ�ߵ��ִ洢˳�� Print����ѡ��ӡ��ز���
        if (gs_Setup.ComMode_1 == COM_CONT || gs_Setup.ComMode_1 == COM_READ || gs_Setup.ComMode_1 == COM_READ_O)
            fu8_Item = SETUP_B4_1;
        if (gs_Setup.ComMode_1 == COM_PRINT)
            fu8_Item = SETUP_B4_6;
    }
    if (fu8_Item == SETUP_B4_6)
    {
        if (gs_Setup.ComMode_1 != COM_PRINT)
            fu8_Item = SETUP_B4_1;
    }
    if (fu8_Item == SETUP_B5_5)
    {   //Modbus��ʽ����ѡ�ߵ��ִ洢˳�� Print����ѡ��ӡ��ز���
        if (gs_Setup.ComMode_2 == COM_CONT || gs_Setup.ComMode_2 == COM_READ || gs_Setup.ComMode_2 == COM_READ_O)
            fu8_Item = SETUP_B5_1;
        if (gs_Setup.ComMode_2 == COM_PRINT)
            fu8_Item = SETUP_B5_6;
    }
    if (fu8_Item == SETUP_B5_6)
    {
        if (gs_Setup.ComMode_2 != COM_PRINT)
            fu8_Item = SETUP_B5_1;
    }
    
    return fu8_Item;
}




/*********************************************************************
��������: void Key_SetupState(void)
��    ��: �����������ô���
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-19
��    ��:                      ʱ    ��: 
*********************************************************************/
void Key_SetupState(void)
{
    u8 luc_DataLen = 0;      //��������λ��
    
    gb_FlashFlg = false;
    
    if (gu32_KeyCode == K_RIGHT)
    {
        gu8_Item = GetSetupNextItem(gu8_Item, false);  //��ȡ����������Ŀ
        ulParameter.ul = GetSetupItemValue(gu8_Item);
        gu8_DataInLength = 0;
        gb_FirstNumKeyFlg = true;
    }
    switch (gu8_Item)
    {
        case SETUP_CHECKCODE:       //��������
            luc_DataLen = 6;
            gb_FirstNumKeyFlg = false;
            break;
        case DISP_SETUP:
            if (gu32_Sys10ms - gu32_TimeDelay >= 100)
            {
                gb_FirstNumKeyFlg = true;
                gu8_Item = SETUP_B1;
            }
            break;
        case SETUP_B2_2:              //���ȷ�Χ
        case SETUP_B4_2:           //���п�1�豸��
        case SETUP_B5_2:           //���п�2�豸��
        case SETUP_B2_1:           //���㷶Χ
        case SETUP_B1_4:           //�Զ�������
            luc_DataLen = 2;        //����
            break;
        case SETUP_B1_5:           //���ȳ�ʱʱ��
        case SETUP_B6_2:            //���ͻ�������ʱʱ��
        case SETUP_B6_3:            //���ͻ�����ʱ��
        case SETUP_B6_4:            //�ٴμд���ʱ��������ʱ��
        case SETUP_B7_2:
        case SETUP_B7_6:
        case SETUP_B7_3:
        case SETUP_B7_7:
        case SETUP_B7_8:
        case SETUP_B7_9:
            luc_DataLen = 3;        //����
            break;
        case SETUP_B7_4:
            luc_DataLen = 4;
            break;
        case SETUP_B4_8:            //��ӡ����
        case SETUP_B5_8:            //��ӡ����
        case SETUP_B4_5:           //���п�1 HiLo
        case SETUP_B5_5:           //���п�2 HiLo
        case SETUP_B4_6:           //���п�1�Զ���ӡ����
        case SETUP_B5_6:           //���п�2�Զ���ӡ����
        case SETUP_B3_1:              //�ϵ��Զ����㿪��
        case SETUP_B3_2:             //�ֶ�ж���ۼƿ���
        case SETUP_B3_3:        //��ֵ�������ֿ���
        case SETUP_B3_4:        //�ۼƲ�ѯ���뿪��
        case SETUP_B3_5:        //�ۼ�������뿪��
        case SETUP_B3_6:        //�ۼƷ�Χ��չ����
        case SETUP_B1_3:              //Ͷ�Ϸ�ʽ
        case SETUP_B1_2:             //ë����ģʽ
        case SETUP_B8:             //���뿪��
        case SETUP_B7:
        case SETUP_B7_1:
        case SETUP_B7_5:
            ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 1);      //�����л����á����޸�
            break;
        case SETUP_B1_6:            //����ʾ���� 0~2�ò��������������ּ�����Ҳ�����á�����
            luc_DataLen = 1;        //����
        case SETUP_B4_7:            //��ӡ��ʽ
        case SETUP_B5_7:            //��ӡ��ʽ
        case SETUP_B6_1:            //˫�޶��ӻ���ģʽͬʱ�ɴ�����
            ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 2);      //3���л����á����޸�
            break;
        case SETUP_B2_7:             //AD��������
        case SETUP_B2_8:             //��չ�ӿ�����
            ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 3);      //4���л����á����޸�
            break;
        case SETUP_B4_1:           //���п�1ͨѶ��ʽ
            if (gs_Setup.ComMode_1 == COM_PBUS)
            {   //PROFIBUSͨѶʱ�̶�ΪPBUS�����ܵ�
                break;
            }
        case SETUP_B5_1:           //���п�2ͨѶ��ʽ
        case SETUP_B1_1:             //����ģʽ
            ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 5);      //5���л����á����޸�
            break;
        case SETUP_B4_3:           //���п�1������
            if (gu8_ExtType == PBUS_UART)
            {   //PROFIBUSֻ��GSD-1��GSD-2����ѡ��
                ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 1);      //2���л����á����޸�
                break;
            }
        case SETUP_B5_3:           //���п�2������
            ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 10);      //8���л����á����޸�
            break;
        case SETUP_B4_4:           //���п�1У�鷽ʽ
            if (gu8_ExtType == PBUS_UART)
            {   
                ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 1);      //
                break;
            }
            if (gs_Setup.ComMode_1 >= COM_BUS_R)
                ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 3);      //modbusͨѶֻ��ѡ������λ��8λ�ļ��鷽ʽ
            else
                ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 6);
            break;  
        case SETUP_B5_4:           //���п�2У�鷽ʽ
            if (gs_Setup.ComMode_2 >= COM_BUS_R)
                ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 3);      //modbusͨѶֻ��ѡ������λ��8λ�ļ��鷽ʽ
            else
                ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 6);
            break;  
        case SETUP_B2_3:              //�����ٷ�Χ
        case SETUP_B2_4:              //AD�����˲�����
        case SETUP_B2_5:              //ж���˲�����
        case SETUP_B2_6:              //��ֵ�˲�����
        case SETUP_B4_9:              //���п�1��ӡ��ֽ����
        case SETUP_B5_9:              //���п�2��ӡ��ֽ����
            luc_DataLen = 1;
            break;
        case SETUP_B8_1:
            gb_FirstNumKeyFlg = false;
            if (gu32_KeyCode == K_SET)           //������������״̬
                gb_SetFlg = true;
            if (gb_SetFlg)
            {
                if (gu32_KeyCode == K_ESC)       //�˳���������״̬
                {
                    gb_SetFlg = false;
                    gu32_KeyCode = 0;
                    gu8_SetupInTime = 0;
                    gu8_DataInLength = 0;
                }
                else
                    luc_DataLen = 6;
            }
            break;
        default:
            break;
    }
    
    //��������
    ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
    if (gu8_Item == SETUP_B1_6 && ulParameter.ul > 2)
    {   //B1.6����ʾ����ֻ��0~2 ������Χ�Զ���Ϊԭֵ
        ulParameter.ul = gs_Setup.AuxDispType;
    }
    
    //ÿһ���µİ�����������
    switch(gu32_KeyCode)
    {
        case K_ESC:             //�˳�������
            gb_SetFlg = false;
            gb_FirstNumKeyFlg = true;
            if (gu8_Item == SETUP_B8_1)        //��
            {
                gu8_SetupInTime = 0;                //�����������������������
                gu8_DataInLength = 0;               //�����������λ��
                gu8_Item = SETUP_B8;
            }
            else if (gu8_Item > SETUP_B7 && gu8_Item < SETUP_B8)
                gu8_Item = SETUP_B7;
            else if (gu8_Item > SETUP_B6 && gu8_Item < SETUP_B7)
                gu8_Item = SETUP_B6;
            else if (gu8_Item > SETUP_B5 && gu8_Item < SETUP_B6)
                gu8_Item = SETUP_B5;
            else if (gu8_Item > SETUP_B4 && gu8_Item < SETUP_B5)
                gu8_Item = SETUP_B4;
            else if (gu8_Item > SETUP_B3 && gu8_Item < SETUP_B4)
                gu8_Item = SETUP_B3;
            else if (gu8_Item > SETUP_B2 && gu8_Item < SETUP_B3)
                gu8_Item = SETUP_B2;
            else if (gu8_Item > SETUP_B1 && gu8_Item < SETUP_B2)
                gu8_Item = SETUP_B1;
            else
            {
                gu32_SystemState = STOPSTATE;
            }
            ulParameter.ul = GetSetupItemValue(gu8_Item);
            break;
        case K_ENTER:           //ȷ�ϼ�����
            gb_FirstNumKeyFlg = true;
            switch(gu8_Item)
            {
                case SETUP_CHECKCODE:       //��������
                    gu8_SetupInTime++;
                    if ((ulParameter.ul == gu32_SetupCode && gu8_DataInLength ==6) || 
                        (ulParameter.ul == SUPERCODE && gu8_DataInLength ==6))        //������������趨����򳬼�����
                    {
                        gu8_SetupInTime = 0;            //�����������������������
                        ulParameter.ul = 0;
                        gu32_TimeDelay = gu32_Sys10ms;
                    }
                    else if (gu8_SetupInTime >= 3)      //����������󳬹�3��
                    {
                        ErrorDeal(4, 0);        //��ʾerror4
                        Disp_Error();
                        VFD_CopyDispArryToDispRam();
                        VFD_WriteDispRamArry();
                        while(1);
                    }
                    else            //�������������ʾerror
                    {
                        ErrorDeal(0, 100);
                        ulParameter.ul = 0;
                        gu8_DataInLength = 0;
                        return;
                    }
                    break;
                case SETUP_B8_1:           //��������״̬
                    if (gb_SetFlg == true)
                    {
                        gu8_SetupInTime++;
                        if (gu8_SetupInTime >= 2)
                        {
                            if (ulParameter.ul == gu32_DataTemp && gu8_DataInLength == 6)         //�������������һ��
                            {
                                gu8_SetupInTime = 0;
                                gb_SetFlg = false;
                                gu32_SetupCode = ulParameter.ul;
                                FRAM_WriteDW(FMAddr_SetupCode, gu32_SetupCode);          //��������
                            }
                            else
                            {
                                gu8_SetupInTime = 0;
                                ErrorDeal(0, 100);
                                gb_FirstNumKeyFlg = true;
                                ulParameter.ul = 0;
                                gu8_DataInLength = 0;
                                return;
                            }
                        }
                        else
                        {
                            if (gu8_DataInLength == 6)      //�����������6λ
                            {
                                gu32_DataTemp = ulParameter.ul;      //�ݴ��һ����������ֵ
                                ulParameter.ul = 0;
                                gu8_DataInLength = 0;
                                return;
                            }
                            else
                            {
                                gu8_SetupInTime = 0;
                                ErrorDeal(0, 100);
                                gb_FirstNumKeyFlg = true;
                                ulParameter.ul = 0;
                                gu8_DataInLength = 0;
                                return;
                            }
                        }
                    }
                    break;
                case SETUP_B4_2:           //���п�1�Ӻ�
                case SETUP_B5_2:           //���п�1�Ӻ�
                case SETUP_B2_1:              //���㷶Χ
                    if (ulParameter.ul == 0)            //��Щ����ֵ����Ϊ0
                    {
                        ErrorDeal(0, 100);    //��ʾerror
                        return;
                    }
                    break;
                case SETUP_B4_1:      //ͨѶ��ʽ��Print,read��cont��Ϊbus��У������7λ�Ļ�Ĭ�ϸ�Ϊ18E1
                    if (ulParameter.ul == COM_BUS_R && gs_Setup.ComMode_1 != COM_BUS_R)
                    {
                        if (gs_Setup.ParityMode_1 > 3)
                        {
                            gs_Setup.ParityMode_1 = 1;
                            FRAM_WriteDW(FMAddr_ParityMode_1, gs_Setup.ParityMode_1);
                        }
                    }
                    break;
                case SETUP_B5_1:      //ͨѶ��ʽ��Print,read��cont��Ϊbus��У������7λ�Ļ�Ĭ�ϸ�Ϊ18E1
                    if (ulParameter.ul == COM_BUS_R && gs_Setup.ComMode_2 != COM_BUS_R)
                    {
                        if (gs_Setup.ParityMode_2 > 3)
                        {
                            gs_Setup.ParityMode_2 = 1;
                            FRAM_WriteDW(FMAddr_ParityMode_2, gs_Setup.ParityMode_2);
                        }
                    }
                    break;
                case SETUP_B1_1:
                    if (ulParameter.ul != gs_Setup.TareMode)
                    {   
                        TareModeChange(ulParameter.ul);
                    }
                    break;
                default:
                    break;
            }
            if ((gu8_Item != SETUP_CHECKCODE) && (gu8_Item != SETUP_B1) &&
                (gu8_Item != SETUP_B2) && (gu8_Item != SETUP_B3) && 
                (gu8_Item != SETUP_B4) && (gu8_Item != SETUP_B5) && (gu8_Item != SETUP_B6))
                FRAM_WriteDW(GetSetupPort(gu8_Item), ulParameter.ul);         //�������õĹ�������ֵ
            //�޸Ĵ�����ز���Ҫ���³�ʼ������
            if (gu8_Item == SETUP_B4_1 || gu8_Item == SETUP_B4_2 || gu8_Item == SETUP_B4_3 || gu8_Item == SETUP_B4_4)
                Uart1_Init();
            if (gu8_Item == SETUP_B5_1 || gu8_Item == SETUP_B5_2 || gu8_Item == SETUP_B5_3 || gu8_Item == SETUP_B5_4)
                Uart0_Init();
            //�޸�ADת���ٶ�Ҫ���³�ʼ��AD
            if (gu8_Item == SETUP_B2_7)
                gb_AdOKFlg = AD_Init(gs_Setup.AdSamplingRate);
            //�����������뱣�����عر�ʱ����B1��
            if (gu8_Item == SETUP_B8 && ulParameter.ul == 0)
                gu8_Item = SETUP_B1;
            else
                gu8_Item = GetSetupNextItem(gu8_Item, true);         //������һ��
            ulParameter.ul = GetSetupItemValue(gu8_Item);
            gu8_DataInLength = 0;
            gb_FirstNumKeyFlg = true;
            break;
        default:
            break;
    }
}

/*********************************************************************
��������: void Disp_SetupState(void)
��    ��: ����������ʾ���
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-19
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_SetupState(void)
{
    u8 luc_DispNumber = 0;       //��ʾλ��
    u8 luc_Point = 0;
    u16 lu16_RealItem = gu16_SetupRealItem[gu8_Item];
    
    gb_FlashFlg = false;
    //Bxx����ʾ
    if (gu8_Item != DISP_SETUP)
    {
        if (lu16_RealItem % 10 == 0)  //�����B1/B2/B3...
        {
            gu8_AuxDispArray[1] = SEG_B;
            gu8_AuxDispArray[2] = Value_To_SEG[lu16_RealItem / 10];
        }
        else    //С�� ��B1.1/B1.2...
        {
            gu8_AuxDispArray[0] = SEG_B;
            gu8_AuxDispArray[1] = Value_To_SEG[lu16_RealItem % 100 / 10] | 0x80;
            gu8_AuxDispArray[2] = Value_To_SEG[lu16_RealItem % 10];
        }
    }
    
    switch (gu8_Item)
    {
        case SETUP_CHECKCODE:       //��������
            Disp_InputCode();       //����������ʾ����
            gb_FlashFlg = true;
            break;
        case DISP_SETUP:
            VFD_MainDisp_Str(" SETUP");
            break;
        case SETUP_B1:
            VFD_MainDisp_Str("  MODE");
            break;
        case SETUP_B2:
            VFD_MainDisp_Str("  BASE");
            break;
        case SETUP_B3:
            VFD_MainDisp_Str("SWITCH");
            break;
        case SETUP_B4:
            VFD_MainDisp_Str(" EXT-1");
            break;
        case SETUP_B5:
            VFD_MainDisp_Str(" EXT-2");
            break;
        case SETUP_B6:
            VFD_MainDisp_Str("   NO2");
            break;
        case SETUP_B2_2:              //���ȷ�Χ
        case SETUP_B4_2:           //���п�1�Ӻ�
        case SETUP_B5_2:           //���п�2�Ӻ�
        case SETUP_B2_1:              //���㷶Χ
        case SETUP_B1_4:              //�Զ�������
            luc_DispNumber = 2;
            gb_FlashFlg = true;
            break;
        case SETUP_B1_5:              //���ȳ�ʱʱ��
        case SETUP_B6_2:            //���ͻ�������ʱʱ��
        case SETUP_B6_3:            //���ͻ�����ʱ��
        case SETUP_B6_4:            //�ٴμд���ʱ��������ʱ��
        case SETUP_B7_2:
        case SETUP_B7_6:
            luc_Point = 1;
        case SETUP_B7_3:
        case SETUP_B7_7:
        case SETUP_B7_8:
        case SETUP_B7_9:
            luc_DispNumber = 3;
            gb_FlashFlg = true;
            break;
        case SETUP_B7_4:
            luc_DispNumber = 4;
            gb_FlashFlg = true;
            break;
        case SETUP_B2_3:              //�����ٷ�Χ
        case SETUP_B2_4:              //AD�����˲�����
        case SETUP_B2_5:              //ж���˲�����
        case SETUP_B2_6:              //��ֵ�˲�����
        case SETUP_B4_9:              //���п�1��ӡ��ֽ����
        case SETUP_B5_9:              //���п�2��ӡ��ֽ����
            luc_DispNumber = 1;
            gb_FlashFlg = true;
            break;
        case SETUP_B1_6:            //����ʾ����
            luc_DispNumber = 1;
            break;
        case SETUP_B4_6:           //���п�1��ӡ����
        case SETUP_B5_6:           //���п�2��ӡ����
        case SETUP_B3_1:              //�ϵ��Զ����㿪��
        case SETUP_B3_2:             //�ֶ�ж���ۼƿ���
        case SETUP_B3_3:        //��ֵ�������ֿ���
        case SETUP_B3_4:        //�ۼƲ�ѯ���뿪��
        case SETUP_B3_5:        //�ۼ�������뿪��
        case SETUP_B3_6:        //�ۼƷ�Χ��չ����
        case SETUP_B8:          //���뿪��
        case SETUP_B7:
        case SETUP_B7_1:
        case SETUP_B7_5:
            Disp_OnOff(ulParameter.ul);           //��ʾ����
            break;
        case SETUP_B1_1:
            Disp_TareMode(ulParameter.ul);        //��ʾbinyes binno
            break;
        case SETUP_B1_2:
            Disp_GorNMode(ulParameter.ul);        //��ʾgross net
            break;
        case SETUP_B2_7:             //AD��������
            Disp_AdSamplingRate(ulParameter.ul);        //120 240 480 960
            break;
        case SETUP_B2_8:            //��չ�ӿ�����
            Disp_ExtType(ulParameter.ul);
            break;
        case SETUP_B4_3:
            if (gu8_ExtType == PBUS_UART)
            {   //PROFIBUSͨѶ����ĿΪGSD�ļ�ѡ��
                Disp_GSDType(ulParameter.ul);
                break;
            }
        case SETUP_B5_3:
            Disp_BaudRate(ulParameter.ul);        //��������ʾ
            break;
        case SETUP_B4_1:
        case SETUP_B5_1:
            Disp_ComMode(ulParameter.ul);         //��ʾͨѶ��ʽ
            break;
        case SETUP_B1_3:
            Disp_FeedMode(ulParameter.ul);        //Ͷ�Ϸ�ʽ
            break;
        case SETUP_B4_4:
            if (gu8_ExtType == PBUS_UART)
            {
                Disp_OnOff(ulParameter.ul);           //��ʾ����
                break;
            }
        case SETUP_B5_4:
            Disp_ParityMode(ulParameter.ul);      //У�鷽ʽ
            break;
        case SETUP_B4_5:
        case SETUP_B5_5:
            Disp_HiLo(ulParameter.ul);            //HiLo
            break;
        case SETUP_B4_7:            //��ӡ��ʽ
        case SETUP_B5_7:            //��ӡ��ʽ
            Disp_PrintType(ulParameter.ul);
            break;
        case SETUP_B4_8:            //��ӡ����
        case SETUP_B5_8:            //��ӡ����
            Disp_PrintLanguage(ulParameter.ul);
            break;
        case SETUP_B6_1:            //˫�޶��ӻ���ģʽͬʱ�ɴ�����
            Disp_No2PackOffTwoSwitch(ulParameter.ul);
            break;
        case SETUP_B8_1:
            Disp_InputCode();       //����������ʾ����
            VFD_AuxDisp_Str("B71");
            gu8_AuxDispArray[1] |= 0x80;    //��ʾС����
            if (gb_SetFlg == true)
                gb_FlashFlg = true;
            break;
    }
    
    switch (gu8_Item)
    {
        case SETUP_CHECKCODE:       //��������
        case SETUP_B8_1:           //��������
            Flash_MainDisp(0x01);                //��˸����
            break;
        case SETUP_B4_2:           //���п�1�Ӻ�
        case SETUP_B5_2:           //���п�2�Ӻ�
        case SETUP_B2_1:              //���㷶Χ
        case SETUP_B1_4:              //�Զ�������
        case SETUP_B1_5:           //���ȳ�ʱʱ��
        case SETUP_B1_6:            //����ʾ����
        case SETUP_B2_3:              //�����ٷ�Χ
        case SETUP_B2_2:              //���ȷ�Χ
        case SETUP_B2_4:              //AD�����˲�����
        case SETUP_B2_5:              //ж���˲�����
        case SETUP_B2_6:              //��ֵ�˲�����
        case SETUP_B4_9:              //���п�1��ӡ��ֽ����
        case SETUP_B5_9:              //���п�2��ӡ��ֽ����
        case SETUP_B6_2:            //���ͻ�������ʱʱ��
        case SETUP_B6_3:            //���ͻ�����ʱ��
        case SETUP_B6_4:            //�ٴμд���ʱ��������ʱ��
        case SETUP_B7_2:
        case SETUP_B7_6:
        case SETUP_B7_3:
        case SETUP_B7_7:
        case SETUP_B7_8:
        case SETUP_B7_9:
        case SETUP_B7_4:
            Disp_Main_Data(ulParameter.ul, luc_Point, luc_DispNumber, false, false);       //��ʾ
            Flash_MainDisp(0x01);                //��˸����
            break;
        default:
            break;
    }
}

/*********************************************************************
��������: void TareModeChange(u32 fu32_NewTareMode)
��    ��: ����ģʽ�ı��Ҫ�����Ķ���
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-04-28
��    ��:                      ʱ    ��: 
*********************************************************************/
void TareModeChange(u32 fu32_NewTareMode)
{
    //����ģʽ�ı������ۼơ�����
    //�ۼ�
    ClrSum();
    //����
    gu32_BatchTime = 0;
    gu32_BatchTimeCnt = 0;
    FRAM_WriteDW(FMAddr_BatchTime, gu32_BatchTime);
    FRAM_WriteDW(FMAddr_BatchTimeCnt, gu32_BatchTimeCnt);
    //���¿������Զ�������ָ��
    IoDefPointerRefresh(fu32_NewTareMode);
}