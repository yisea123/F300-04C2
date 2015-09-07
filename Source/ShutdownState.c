/*
Description:            ��ʱ������ع���
Author:                 �Ժ���
Date:                   2013-12-9
*/

#include "include.h"

const u8 gu8_MonthDay[2][14]=
{
 {0,31,28,31,30,31,30,31,31,30,31,30,31,30},
 {0,31,29,31,30,31,30,31,31,30,31,30,31,30}
};

const u32 IDSFA[101]=
{      1111,  // 2      3     4      5      6     7      8       9      10
/*0*/  2477,  2503,  2521,  2531,  2539,  2543,  2549,  2551,  2557,  2579,//0
/*1*/  2591,  2593,  2609,  2617,  2621,  2633,  2647,  2657,  2659,  2663,//1
/*2*/  2671,  2677,  2683,  2687,  2689,  2693,  2699,  2707,  2711,  2713,//2
/*3*/  2719,  2729,  2731,  2741,  2749,  2753,  2767,  2777,  2789,  2791,//3
/*4*/  2797,  2801,  2803,  2819,  2833,  2837,  2843,  2851,  2857,  2861,//4
/*5*/  2879,  2887,  2897,  2903,  2909,  2917,  2927,  2939,  2953,  2957,//5
/*6*/  2963,  2969,  2971,  2999,  3001,  3011,  3019,  3023,  3037,  3041,//6
/*7*/  3049,  3061,  3067,  3079,  3083,  3089,  3109,  3119,  3121,  3137,//7
/*8*/  3163,  3167,  3169,  3181,  3187,  3191,  3203,  3209,  3217,  3221,//8
/*9*/  3229,  3251,  3253,  3257,  3259,  3271,  3299,  3301,  3313,  3307 //9
};  //2591~3313 ����

const u32 IDSFB[101]=
{
     1,     //   2      3      4      5      6     7      8       9     10
/*0*/106751,106753,106759,106781,106783,106787,106801,106823,106853,106859,//0
/*1*/106861,106867,106871,106877,106903,106907,106921,106937,106949,106957,//1
/*2*/106961,106963,106979,106993,107021,107033,107053,107057,107069,107071,//2
/*3*/107077,107089,107099,107101,107119,107123,107137,107171,107183,107197,//3
/*4*/107201,107209,107227,107243,107251,107269,107273,107279,107309,107323,//4
/*5*/107339,107347,107351,107357,107377,107441,107449,107453,107467,107473,//5
/*6*/107507,107509,107563,107581,107599,107603,107609,107621,107641,107647,//6
/*7*/107671,107687,107693,107699,107713,107717,107719,107741,107747,107761,//7
/*8*/107773,107777,107791,107827,107837,107839,107843,107857,107867,107873,//8
/*9*/107881,107897,107903,107923,107927,107941,107951,107971,107999,107981//9
}; //106861~107999

u8  gu8_ShutDownInTime;         //��������������
u32 gu32_BuyerID;               //�ͻ����� 00~99 ��Ӧ��ͬ��ID�㷨.
u32 gu32_ShutDownCode;          //��ʱ�����û�����
u32 gu32_RandomID;              //�����ID
u32 gu32_RandomCode;            //���Ӧ������
u32 gu32_RandomUnlockCode;      //�����������
u32 gu32_Random30DayCode;       //���30������
u32 gu32_Random60DayCode;       //���60������
u32 gu32_ShutDownSwitch;        //��ʱ��������
u32 gu32_LeaveDays;             //ʣ����������
u32 gu32_CmpYear;               //�����Ƚ���
u32 gu32_CmpMonth;              //�����Ƚ��·�
u32 gu32_CmpDate;               //�����Ƚ�����
bool gb_SysClosedFlg;           //ϵͳ�Ѿ�������־
bool gb_JudgeShutDownFlg;       //�ж�������־λ
u32 gu32_GetedRandom;           //������Ѿ���ȡ��־
bool gb_ReCmpFlg;               //��������־�����±Ƚ�����ʱ��



/*********************************************************************
��������: void Sys_Closed_Set(void)
��    ��: ��ʱ�ػ���Ĵ���������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-23
��    ��:                      ʱ    ��: 
*********************************************************************/
void Sys_Closed_Set(void)
{
    bool lb_ShutDownSetFlg = false;
  
    BuzzerOff();
    while (gb_SysClosedFlg)     //���ϵͳ�Ѿ��ر�
    {
        gu32_KeyCode = Key_Deal();
        OPBuzzer();
        VFD_ClrDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);       //����ʾ����
        
        gu32_SystemState = SHUTDOWNSTATE;
        UpdataGrandShutCode();
        gb_KeyLockFlg = false;              //��״̬��,����������Ч
        if (lb_ShutDownSetFlg)          //��ʱ�ػ�����״̬
        {
            gb_ReCmpFlg = true;
            Key_ShutdownState();
            Disp_ShutdownState();
            if(gu32_SystemState != SHUTDOWNSTATE)
            {
                gb_SysClosedFlg = false;
                gu32_KeyCode = 0;
            }
        }
        else
        {
            switch (gu32_KeyCode)
            {
                case K_5_5S:
                    lb_ShutDownSetFlg = true;
                    gu32_SystemState = SHUTDOWNSTATE;
                    gb_SetFlg = false;
                    gu8_Item = 0;
                    gu32_KeyCode = 0;
                    ulParameter.ul = 0xFFFFFFFA;        //Ϊ����6λ��7λ��������ʮ���Ƶ�0xFFFFFFFA���һλ��0������6λ����ʱ���λ��0��Ӱ��6λ�������ֵ
                    gu8_DataInLength = 0;
                    break;
            }
            VFD_MainDisp_Str("    TE");
        }
        VFD_CopyDispArryToDispRam();         //����ʾ���������ʾ����
        VFD_WriteDispRamArry();                    //д��ʾ���� 
    }

    gu32_KeyCode = 0;
    gb_JudgeShutDownFlg = true;//��λ�ж����־λ
}

/*********************************************************************
��������:Count_Day()
��    ��:���������ĳ�����ĳ�쵽��ĩ������
��ڲ���:
���ó���:
�� �� ֵ:
��    ��:�Ժ���               ʱ    ��: 2011-5-23
��    ��:                     ʱ    ��:
*********************************************************************/
u16 Count_Day(u8 fu8_Year, u8 fu8_Month, u8 fu8_Date, bool flag)
{
    u8 i, p;
    u16 lu16_Days;

    if (LeapYear(fu8_Year))
        p = 1;
    else
        p = 0;

    if (flag)           //����һ��Ŀ�ʼ��ĳ�������
    {
        lu16_Days = fu8_Date;
        for (i = 1; i< fu8_Month; i++)
            lu16_Days += gu8_MonthDay[p][i];
    }
    else                //����һ���ĳ�쵽��ĩ������
    {
        lu16_Days = gu8_MonthDay[p][fu8_Month] - fu8_Date;
        for (i = fu8_Month + 1;i <= 12; i++)
            lu16_Days += gu8_MonthDay[p][i];
    }
    return (lu16_Days);
}

/*********************************************************************
��������: void CmpDay(void)
��    ��: ��ʱ�����Ƚ�ʣ������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-23
��    ��:                      ʱ    ��: 
*********************************************************************/
void CmpDay(void)
{
    u16 lu16_Day, lu16_Year;
  
    gb_SysClosedFlg = false;
    gb_ReCmpFlg = false;
    if ((gu32_ShutDownSwitch != 0) && (gu32_BuyerID!=0))     //�����ʱ�ػ����ܴ�
    {
        RTC_ReadDateTime(&SysDataTime);      //��ȡ��ǰ����
        SysDataTime.year = (SysDataTime.year >> 4) * 10 + (SysDataTime.year & 0x0F);
        SysDataTime.month = (SysDataTime.month >> 4) * 10 + (SysDataTime.month & 0x0F);
        SysDataTime.date = (SysDataTime.date >> 4) * 10 + (SysDataTime.date & 0x0F);
        
        //������һ�αȽ�����
        gu32_CmpYear = FRAM_ReadDW(FMAddr_CmpYear);
        gu32_CmpMonth = FRAM_ReadDW(FMAddr_CmpMonth);
        gu32_CmpDate = FRAM_ReadDW(FMAddr_CmpDate);

        //��ʣ������
        gu32_LeaveDays = FRAM_ReadDW(FMAddr_LeaveDays);

        //�Ƚ�ʣ��������(��ǰ����-���һ�αȽ�����)
        if (gu32_CmpYear < SysDataTime.year)
        {
            lu16_Day = Count_Day(gu32_CmpYear, gu32_CmpMonth, gu32_CmpDate, false);//����һ���ĳ�쵽��ĩ������
            for (lu16_Year = gu32_CmpYear+1; lu16_Year<SysDataTime.year; lu16_Year++)
            {
                if (LeapYear(lu16_Year))
                    lu16_Day+=366;
                else
                    lu16_Day+=365;
            }
            lu16_Day += Count_Day(SysDataTime.year, SysDataTime.month, SysDataTime.date, true);//����һ��Ŀ�ʼ��ĳ�������
        }
        else if(gu32_CmpYear == SysDataTime.year)
        {
            lu16_Day = Count_Day(SysDataTime.year, SysDataTime.month, SysDataTime.date, true) - Count_Day(gu32_CmpYear, gu32_CmpMonth, gu32_CmpDate, true);
        }
        else
            lu16_Day=0;

        if (gu32_LeaveDays > lu16_Day)//����趨��ʣ��������,�����ʣ������,�������һ�αȽ�����
        {
            if(lu16_Day!=0)
            {
                lu16_Day = gu32_LeaveDays - lu16_Day;
                gu32_LeaveDays = lu16_Day;
                FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
                FRAM_WriteDW(FMAddr_CmpYear, SysDataTime.year);
                FRAM_WriteDW(FMAddr_CmpMonth, SysDataTime.month);
                FRAM_WriteDW(FMAddr_CmpDate, SysDataTime.date); 
            }
        }
        else//����,ʣ������Ϊ0,�ر�ϵͳ
        {
            gu32_LeaveDays = 0;
            FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
            BuzzerOff();
            gb_SysClosedFlg = true;
        }
    }
    else
    {
        gu32_LeaveDays = 65535;
        FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
        gb_SysClosedFlg = false;
    }
}

/*********************************************************************
��������: u32 GetShutItemValue(u8 fuc_Item)
��    ��: ���ض�Ӧ��Ŀֵ
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-3
��    ��:                      ʱ    ��: 
*********************************************************************/
u32 GetShutItemValue(u8 fuc_Item)
{
    u32 fu32_Value;
    switch (fuc_Item)
    {
        case SHUTDOWN_SWITCH:           //��������
            fu32_Value = gu32_ShutDownSwitch;
            break;
        case SHUTDOWN_DAYNUM:           //ʣ����������
            fu32_Value = gu32_LeaveDays;
            break;
        case SHUTDOWN_BUYID:            //�û�ID
           fu32_Value = gu32_BuyerID;
           break;
        default:
            fu32_Value = 0;
            break;
    }
    return fu32_Value;
}

/*********************************************************************
��������: u16 GetShutDownPort(u8 fuc_Item)
��    ��: ���ض�ʱ���������洢��ַ
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-20
��    ��:                      ʱ    ��: 
*********************************************************************/
u16 GetShutDownPort(u8 fuc_Item)
{
    u16 lui_FMAddress = 0;
    
    switch (fuc_Item)
    {
        case SHUTDOWN_SWITCH:
            gu32_ShutDownSwitch = ulParameter.ul;
            lui_FMAddress = FMAddr_ShutDownSwitch;
            break;
        case SHUTDOWN_DAYNUM:
            gu32_LeaveDays = ulParameter.ul;
            lui_FMAddress = FMAddr_LeaveDays;
            break;
        case SHUTDOWN_INPUTCODE:
            gu32_ShutDownCode = ulParameter.ul;
            lui_FMAddress = FMAddr_ShutDownCode;
            break;
        case SHUTDOWN_BUYID:
            gu32_BuyerID = ulParameter.ul;
            lui_FMAddress = FMAddr_BuyerID;
            break;
        default:
            break;
    }
    return lui_FMAddress;
}

/*********************************************************************
��������: void Update_ShutDown_data(u8 fu8_Type)
��    ��: ���¶�ʱ��������
˵    ��: 
��ڲ���: fu8_Type = 0 �ر��������� 1д��30�� 2д��60��
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 
��    ��:                      ʱ    ��: 
*********************************************************************/
void Update_ShutDown_data(u8 fu8_Type)
{
    RTC_ReadDateTime(&SysDataTime);      //��ȡ��ǰ����
    gu32_CmpYear = (SysDataTime.year >> 4) * 10 + (SysDataTime.year & 0x0F);
    gu32_CmpMonth = (SysDataTime.month >> 4) * 10 + (SysDataTime.month & 0x0F);
    gu32_CmpDate = (SysDataTime.date >> 4) * 10 + (SysDataTime.date & 0x0F);
    FRAM_WriteDW(FMAddr_CmpYear, gu32_CmpYear);
    FRAM_WriteDW(FMAddr_CmpMonth, gu32_CmpMonth);
    FRAM_WriteDW(FMAddr_CmpDate, gu32_CmpDate); 

    if (fu8_Type > 2)
        fu8_Type=0;

    if(fu8_Type!=0)     //������������Ϊ30���60��
    {
        gu32_LeaveDays = 30 * fu8_Type;
        FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
        gb_SysClosedFlg = false;        //���������־
    }
    else        //�ر���������
    {
        gu32_ShutDownSwitch = 0;
        gu32_LeaveDays = 65535;
        FRAM_WriteDW(FMAddr_ShutDownSwitch, gu32_ShutDownSwitch);
        FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
        gb_SysClosedFlg = false;        //���������־
        gb_JudgeShutDownFlg = true;
    }
}

/*********************************************************************
��������: u32 GetRandom(void)
��    ��: ��ȡ�����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-20
��    ��:                      ʱ    ��: 
*********************************************************************/
u32 GetRandom(void)
{
    srand(gu32_Sys10ms);
    return((u32)(129643 * (u32)rand() + 32189) % 1000000);
}

/*********************************************************************
��������: bool GradeShutCodeEQ(void)
��    ��: ����������������룬����������룬���30��60�����룬Ӧ������
˵    ��: 
��ڲ���: 
�� �� ֵ: 1���벻���������¼���
��    ��: �Ժ���               ʱ    ��: 2011-5-20
��    ��:                      ʱ    ��: 
*********************************************************************/
bool GradeShutCodeEQ(void)
{
    if (gu32_BuyerID == 99)
    {
        gu32_RandomCode = (gu32_RandomID * 3313 + 107999) % 998989;         //���Ӧ������
        gu32_Random30DayCode = (gu32_RandomID * 3221 + 107071) % 998989;
        gu32_Random60DayCode = (gu32_RandomID * 3137 + 106367) % 998989;
        gu32_RandomUnlockCode = (gu32_RandomID * 3041 + 104827) % 998989;
    }
    else
    {
        gu32_RandomCode  =(gu32_RandomID * IDSFA[gu32_BuyerID] + IDSFB[gu32_BuyerID]) % 1000000;     //����������
        if (gu32_RandomCode > 999800)
            return true;
        gu32_Random30DayCode = (gu32_RandomCode + 30) % 1000000;          //��ȡ��������
        gu32_Random60DayCode = (gu32_RandomCode + 60) % 1000000;           //��ȡ30������
        gu32_RandomUnlockCode = (gu32_RandomCode + 100) % 1000000;          //��ȡ60������
    }

    if ((gu32_RandomCode == gu32_RandomUnlockCode)||\
       (gu32_RandomCode == gu32_Random30DayCode)||\
       (gu32_RandomCode == gu32_Random60DayCode))
        return true;
    else if ((gu32_RandomUnlockCode == gu32_Random30DayCode)|| \
            (gu32_RandomUnlockCode == gu32_Random60DayCode))
        return true;
    else if (gu32_Random30DayCode == gu32_Random60DayCode)
        return true;

    if ((gu32_RandomUnlockCode == gu32_ShutDownCode)||
       (gu32_Random30DayCode == gu32_ShutDownCode)||
       (gu32_Random60DayCode == gu32_ShutDownCode))
        return true;
    return false;
}

/*********************************************************************
��������: void UpdataGrandShutCode(void)
��    ��: ������������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-20
��    ��:                      ʱ    ��: 
*********************************************************************/
void UpdataGrandShutCode(void)
{
    if (gu32_BuyerID == 99)
        gu32_RandomCode = (gu32_RandomID * 3313 + 107999) % 998989;//����������
    else
        gu32_RandomCode = (gu32_RandomID * IDSFA[gu32_BuyerID] + IDSFB[gu32_BuyerID]) % 1000000;//����������

    if ((gu32_ShutDownSwitch != 0) && (gu32_LeaveDays == 0))
    {
        if (gu32_BuyerID == 99)
        {
            gu32_Random30DayCode = (gu32_RandomID * 3221 + 107071) % 998989;//��ȡһ���������
            gu32_Random60DayCode = (gu32_RandomID * 3137 + 106367) % 998989;//��ȡ�����������
            gu32_RandomUnlockCode = (gu32_RandomID * 3041 + 104827) % 998989;//��ȡ�����������
        }
        else
        {
            gu32_Random30DayCode = (gu32_RandomCode + 30) % 1000000;//��ȡһ���������
            gu32_Random60DayCode = (gu32_RandomCode + 60) % 1000000;//��ȡ�����������
            gu32_RandomUnlockCode = (gu32_RandomCode + 100) % 1000000;//��ȡ�����������
        }
    }
    else
    {
        gu32_RandomUnlockCode = 0XEFEFFFFF;
        gu32_Random30DayCode = 0XEFEFFFFF;
        gu32_Random60DayCode = 0XEFEFFFFF;
    }
}

/*********************************************************************
��������: void Key_ShutdownState(void)
��    ��: ��ʱ��������ش���
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-3
��    ��:                      ʱ    ��: 
*********************************************************************/
void Key_ShutdownState(void)
{
    static bool sb_SuperCodeFlg = false;        //������ǳ��������־
    u8 luc_DataLen = 0;      //��������λ��
    sTime SysDataTime;
    
    if (gu32_KeyCode == K_RIGHT)     //������ʾ�л�����һ��
    {
        gb_FirstNumKeyFlg = true;
        if (gu8_Item != SHUTDOWN_CHECKCODE && gu8_Item != SHUTDOWN_UNLOCK)     //��������״̬���ܰ�����
            gu8_Item++;
        if (gu8_Item == SHUTDOWN_DAYNUM)        //�������ܽ�������ʣ����������
            gu8_Item++;
        if (gu8_Item > SHUTDOWN_INPUTCODE + sb_SuperCodeFlg)
            gu8_Item = SHUTDOWN_SWITCH;
        ulParameter.ul = GetShutItemValue(gu8_Item);
    }
    
    //����ÿһ�����ʾ��ֵ
    switch (gu8_Item)
    {
        case SHUTDOWN_CHECKCODE:        //��������
            gb_FirstNumKeyFlg = false;
            luc_DataLen = 7;
            break;
        case SHUTDOWN_SWITCH:           //��������
            ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 1);      //�����л����á����޸�
            break;
        case SHUTDOWN_DAYNUM:           //ʣ����������
            luc_DataLen = 5;
            gb_SetFlg = false;
            break;
        case SHUTDOWN_INPUTCODE:        //�����޸�
            gb_FirstNumKeyFlg = false;
            if (gu32_KeyCode == K_SET)           //������������״̬
                gb_SetFlg = true;
            if (gb_SetFlg)
            {
                if (gu32_KeyCode == K_ESC)       //�˳���������״̬
                {
                    gb_SetFlg = false;
                    gu32_KeyCode = 0;
                    gu8_ShutDownInTime = 0;
                    gu8_DataInLength = 0;
                }
                else
                    luc_DataLen = 6;
            }
            break;
        case SHUTDOWN_BUYID:            //�û�ID
            luc_DataLen = 2;
            gb_SetFlg = false;
        default:
            break;
    }
    
    //��������
    ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
    
    //ÿһ���µİ�����������
    switch(gu32_KeyCode)
    {
        case K_ESC:             //�˳�������
            gb_FlashFlg = false;
            if (gu8_Item == SHUTDOWN_DAYNUM)
                gu8_Item = SHUTDOWN_SWITCH;
            else
                gu32_SystemState = STOPSTATE;
            break;
        case K_ENTER:           //ȷ�ϼ�����
            gu8_DataInLength = 0;
            switch(gu8_Item)
            {
                case SHUTDOWN_CHECKCODE:     //��������
                    gu8_ShutDownInTime++;
                    sb_SuperCodeFlg = false;
                    if (gu32_BuyerID == 0)
                    {
                        gu32_ShutDownCode = 0xFFEFFEFE;     //������붨ʱ�ػ����ܹر�,���û�����Ϊ��������ֵ.
                        gu32_RandomCode = 0xF2EFFEFE;       //Ӧ������Ϊ��������ֵ.
                    }
    
                    if ((ulParameter.ul == gu32_RandomUnlockCode)||(ulParameter.ul == gu32_Random30DayCode)||(ulParameter.ul == gu32_Random60DayCode))
                    {
                        if (ulParameter.ul == gu32_RandomUnlockCode)
                            Update_ShutDown_data(0);
                        else if(ulParameter.ul == gu32_Random30DayCode)
                            Update_ShutDown_data(1);
                        else
                            Update_ShutDown_data(2);
    
                        gu8_ShutDownInTime = 0;         //������������
                        ulParameter.ul = 0;             //����һ�����ֵ
                        gb_SetFlg=false;//���趨����״̬
                        
                        do
                        {
                            gu32_RandomID = GetRandom();
                        }while(GradeShutCodeEQ());
                        gu32_GetedRandom = 0x55;
                        FRAM_WriteDW(FMAddr_GetedRandom, gu32_GetedRandom);
                        FRAM_WriteDW(FMAddr_RandomID, gu32_RandomID);
                        UpdataGrandShutCode();      //��������
                        
                        gu8_Item = SHUTDOWN_UNLOCK;     //��������
                        gu32_TimeDelay = gu32_Sys10ms;
                        BuzzerStart(100);
                        return;
                    }
                    //����������û�����
                    else if ((ulParameter.ul == gu32_ShutDownCode) || (ulParameter.ul == SUPERSHUTCODE))
                    {
                        if(ulParameter.ul== SUPERSHUTCODE)
                            sb_SuperCodeFlg = true;
                        gu8_ShutDownInTime = 0;         //������������
                        ulParameter.ul = 0;             //����һ�����ֵ
                        gb_SetFlg = false;                  //���趨����״̬
                    }
                    //Ӧ������
                    else if (ulParameter.ul == gu32_RandomCode)
                    {
                        gu8_ShutDownInTime=0;       //������������
                        do
                        {
                            gu32_RandomID = GetRandom();
                        }while(GradeShutCodeEQ());
                        gu32_GetedRandom=0x55;
                        FRAM_WriteDW(FMAddr_GetedRandom, gu32_GetedRandom);
                        FRAM_WriteDW(FMAddr_RandomID, gu32_RandomID);
                        UpdataGrandShutCode();      //��������
                    }
                    else if (gu8_ShutDownInTime >= 3)
                    {
                        ErrorDeal(4, 0);        //��ʾerror4
                        Disp_Error();
                        VFD_CopyDispArryToDispRam();         //����ʾ���������ʾ����
                        VFD_WriteDispRamArry();                    //д��ʾ���� 
                        while(1);
                    }
                    else        //�����������
                    {
                        ErrorDeal(0, 100);
                        ulParameter.ul = 0xFFFFFFFA;
                        return;         // ����
                    }
                    break;
                case SHUTDOWN_SWITCH:           //��������
                    FRAM_WriteDW(GetShutDownPort(gu8_Item), ulParameter.ul);
                    if (gu32_ShutDownSwitch == 0)       //��ʱ�������عرպ�Ҫ��ʣ������дΪ65535
                    {
                        gu32_LeaveDays = 65535;
                        FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
                    }
                    break;
                case SHUTDOWN_DAYNUM:
                    if (ulParameter.ul > 65535)     //�����������65535
                    {
                        ErrorDeal(0, 100);
                        return;         // ����
                    }
                    else
                    { 
                        FRAM_WriteDW(GetShutDownPort(gu8_Item), ulParameter.ul);
                        RTC_ReadDateTime(&SysDataTime);      //��ȡ��ǰ����
                        gu32_CmpYear = (SysDataTime.year >> 4) * 10 + (SysDataTime.year & 0x0F);
                        gu32_CmpMonth = (SysDataTime.month >> 4) * 10 + (SysDataTime.month & 0x0F);
                        gu32_CmpDate = (SysDataTime.date >> 4) * 10 + (SysDataTime.date & 0x0F);
                        FRAM_WriteDW(FMAddr_CmpYear, gu32_CmpYear);
                        FRAM_WriteDW(FMAddr_CmpMonth, gu32_CmpMonth);
                        FRAM_WriteDW(FMAddr_CmpDate, gu32_CmpDate);           //����Ƚ�����
                    }
                    break;
                case SHUTDOWN_INPUTCODE:
                    if (gb_SetFlg == true)
                    {
                        gu8_ShutDownInTime++;
                        if (gu8_ShutDownInTime >= 2)
                        {
                            if (ulParameter.ul == gu32_DataTemp)         //�������������һ��
                            {
                                gu8_ShutDownInTime = 0;
                                gb_SetFlg = false;
                                FRAM_WriteDW(GetShutDownPort(gu8_Item), ulParameter.ul);
                            }
                            else
                            {
                                gu8_ShutDownInTime = 0;
                                ErrorDeal(0, 100);
                                ulParameter.ul = 0xFFFFFFFF;
                                return;
                            }
                        }
                        else
                        {
                            gu32_DataTemp = ulParameter.ul;      //�ݴ��һ����������ֵ
                            ulParameter.ul = 0xFFFFFFFF;
                            return;
                        }
                    }
                    break;
                case SHUTDOWN_BUYID:
                    FRAM_WriteDW(GetShutDownPort(gu8_Item), ulParameter.ul);
                    break;
                case SHUTDOWN_UNLOCK:
                    return;
                default:
                    break;
            }
            //����Խ�紦����ʹ�ó������������������û�ID
            if (++gu8_Item > SHUTDOWN_INPUTCODE + sb_SuperCodeFlg)
                gu8_Item = SHUTDOWN_SWITCH;
            if (gu8_Item == SHUTDOWN_DAYNUM && gu32_ShutDownSwitch == 0)
                gu8_Item++;
            ulParameter.ul = GetShutItemValue(gu8_Item);
            gb_FirstNumKeyFlg = true;
            break;
        default:
            break;
    }
    
}

/*********************************************************************
��������: void Disp_ShutdownState(void)
��    ��: ��ʱ������ʾ���洦��
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-3
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_ShutdownState(void)
{
    gb_FlashFlg = false;
    
    switch (gu8_Item)
    {
        case SHUTDOWN_CHECKCODE:        //��������
            Disp_InputCode();
            gb_FlashFlg = true;
            break;
        case SHUTDOWN_SWITCH:           //��������
            Disp_OnOff(ulParameter.ul);           //��ʾ����
            VFD_AuxDisp_Str("ATC");
            break;
        case SHUTDOWN_DAYNUM:           //ʣ����������
            gb_FlashFlg = true;
            Disp_Main_Data(ulParameter.ul, 0, 5, false, false);       //��ʾֵ
            VFD_AuxDisp_Str("DAY");
            break;
        case SHUTDOWN_INPUTCODE:        //�����޸�
            if (gb_SetFlg == true)
                gb_FlashFlg = true;
            Disp_InputCode();           //����������ʾ����
            break;
        case SHUTDOWN_BUYID:            //�û�ID
            gb_FlashFlg = true;
            Disp_Main_Data(ulParameter.ul, 0, 2, false, false);       //��ʾֵ
            VFD_AuxDisp_Str("ID ");
            break;
        case SHUTDOWN_UNLOCK:           //���������ʾ����
            if(gu32_ShutDownSwitch != 0)
            {
                gu8_MainDispArray[4] = Value_To_SEG[gu32_LeaveDays%100/10];
                gu8_MainDispArray[5] = Value_To_SEG[gu32_LeaveDays%10];
            }
            else
            {
                gu8_MainDispArray[4] = SEG_SIG;
                gu8_MainDispArray[5] = SEG_SIG;

            }
            VFD_AuxDisp_Str("DAY");
            
            if (gu32_Sys10ms - gu32_TimeDelay >= 250)
            {
                gb_FlashFlg = false;
                gu32_SystemState = STOPSTATE;
                gu32_ShutDownSwitch = FRAM_ReadDW(FMAddr_ShutDownSwitch);
            }
            break;
        default:
            break;
    }
    Flash_MainDisp(0x01);                //��˸����
}

/********************************************************************
�� �� ��:Auto_ShutDown()
��    ��:�Զ��ػ�����
˵    ��:�ж��Զ��ػ������Ƿ�,�����Զ��ػ�
��ڲ���:
�� �� ֵ:
��    ��:�Ժ���       ��    ��:2011-5-23
��    ��:             ��    ��:
***********************************************************************/
void Auto_ShutDown(void)
{
    sTime ls_Time;
    //�����ʱ�ػ�����Ϊ0,�������붨ʱ�ػ��ͻ���Ϊ0�򷵻أ�������ʱ�����ж�
    if (gu32_ShutDownSwitch == 0 || gu32_BuyerID==0)
        return;             //����
    RTC_ReadDateTime(&ls_Time);      //��ȡ��ǰ����
    if (ls_Time.hour==0 || gu32_LeaveDays == 0)     //���ʱ��Ϊ0
    {
        if(gu32_LeaveDays == 0)     //���ʣ�������Ѿ�Ϊ0
        {
            FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
            VFD_ClrDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);       //����ʾ����
            IO_CloseOut();
            VFD_MainDisp_Str("    TE");
            VFD_CopyDispArryToDispRam();         //����ʾ���������ʾ����
            VFD_WriteDispRamArry();                    //д��ʾ���� 
            BuzzerOff();
            while(1);//����
        }

        if (gb_JudgeShutDownFlg == false)       //����ж���ɱ�־Ϊ0
        {
            gb_JudgeShutDownFlg = true;//��λ�ж���ɱ�־λ
            gu32_LeaveDays--;
            if (gu32_LeaveDays == 0)//���ʣ��������1Ϊ0
            {
                FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
                VFD_ClrDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);       //����ʾ����
                IO_CloseOut();
                VFD_MainDisp_Str("    TE");
                VFD_CopyDispArryToDispRam();         //����ʾ���������ʾ����
                VFD_WriteDispRamArry();                    //д��ʾ���� 
                BuzzerOff();
                while(1);//����
            }
        }
    }
    else
      gb_JudgeShutDownFlg = false; //�ж���ɱ�־Ϊ0
}