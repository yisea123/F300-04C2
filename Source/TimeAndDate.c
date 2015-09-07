/*
Description:            ʱ������ڵ���ع���
Author:                 �Ժ���
Date:                   2013-12-9
*/
#include "include.h"

sTime  SysDataTime;             //ϵͳ���ں�ʱ��

/*********************************************************************
��������: void Input_DateTime(u8 fuc_Data, u8 fuc_Place, sTime fs_DT)
��    ��: ����ʱ�����ڴ���ṹ��
˵    ��: 
��ڲ���: fuc_Data = ����ֵ��fuc_Place = ����λ�ã�fs_DT = �����ʱ��ṹ��
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-23
��    ��:                      ʱ    ��: 
*********************************************************************/
void Input_DateTime(u8 fuc_Data, u8 fuc_Place, u8 *p)
{
    if (fuc_Place <= 5)                 //ע��sTime�ṹ������һ�� .day û��ʹ�ã����Դ���5�Ժ�ָ��Ҫ+1���� .day
        p = (p + fuc_Place / 2);
        
    if (fuc_Place % 2 == 0)
    {
        *p &= 0x0F;
        *p |= (fuc_Data << 4);
    }
    else
    {
        *p &= 0xF0;
        *p |= fuc_Data;
    }
}

/*********************************************************************
��������: void Key_DateTimeState(void)
��    ��: ʱ����ʾ��������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-23
��    ��:                      ʱ    ��: 
*********************************************************************/
void Key_DateTimeState(void)
{
    sTime ls_Time;
    
    if (gb_SetFlg == true)         //����ʱ������״̬
    {
        switch (gu32_KeyCode)       //��������
        {
            case K_1:
            case K_2:
            case K_3:
            case K_4:
            case K_5:
            case K_6:
            case K_7:
            case K_8:
            case K_9:
            case K_0: 
                if (gu32_SystemState == TIMESTATE)          //�����µ�ʱ��
                    Input_DateTime(VFD_KeyCode_To_Value(gu32_KeyCode), gu8_Item, &SysDataTime.hour);
                else          //�����µ�����
                    Input_DateTime(VFD_KeyCode_To_Value(gu32_KeyCode), gu8_Item, &SysDataTime.year);
                gu8_Item++;
                break;
            case K_RIGHT:
                gu8_Item++;
                break;
            case K_ESC:
                gb_FlashFlg = false;
                gb_SetFlg = false;
                break;
            case K_ENTER:           //�ж������ʱ��������Ƿ���ϸ�ʽ ��������ʾerror
                if ((gu32_SystemState == TIMESTATE && RTC_FrameTime(SysDataTime) == true)
                  ||(gu32_SystemState == DATESTATE && RTC_FrameDate(SysDataTime) == true))
                {
                    RTC_WriteDateTime(&SysDataTime);         //д��ʱ�����������
                    gb_FlashFlg = false;
                    gb_SetFlg = false;
                    
                    RTC_ReadDateTime(&ls_Time);      //���¶�ʱ��,��Ϊʵʱʱ��оƬ�����Ե�������.
                    ls_Time.year = (ls_Time.year >> 4) * 10 + (ls_Time.year & 0x0F);
                    ls_Time.month = (ls_Time.month >> 4) * 10 + (ls_Time.month & 0x0F);
                    ls_Time.date = (ls_Time.date >> 4) * 10 + (ls_Time.date & 0x0F);
                    
                    //�������Ƚ�����,��ֹͨ���޸�ϵͳ����������Զ��ػ�.
                    //����ʱ,����ͨ�������������,��Ϊ�޸�ϵͳ������ģ��ػ�ʱ�䵽
                    FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
                    FRAM_WriteDW(FMAddr_CmpYear, ls_Time.year);
                    FRAM_WriteDW(FMAddr_CmpMonth, ls_Time.month);
                    FRAM_WriteDW(FMAddr_CmpDate, ls_Time.date); 
                    gb_JudgeShutDownFlg = true;
                }
                else
                {
                    ErrorDeal(0, 100);             //��ʾ����
                    RTC_ReadDateTime(&SysDataTime);      //��ϵͳ���ں�ʱ��
                    gu8_Item = 0;
                }
                break;
            default:
                break;
        }
        if (gu8_Item > 5)
            gu8_Item = 0;
    }
    else                        //����ʱ����ʾ״̬
    {
        RTC_ReadDateTime(&SysDataTime);        //��ϵͳ���ں�ʱ��
        
        switch (gu32_KeyCode)       //��������
        {
            case K_5_5S:
                gu32_KeyCode = 0;
                ulParameter.ul = 0xFFFFFFFA;//Ϊ����6λ��7λ��������ʮ���Ƶ�0xFFFFFFFA���һλ��0������6λ����ʱ���λ��0��Ӱ��6λ�������ֵ
                gu8_Item = 0;
                gu8_DataInLength = 0;
                gb_SetFlg = false;
                gb_FirstNumKeyFlg = true;
                gb_FlashFlg = false;
                gu32_SystemState = SHUTDOWNSTATE;
                Key_ShutdownState();
                break;
            case K_ESC:
                gu32_SystemState = STOPSTATE;
                break;
            case K_SET:
                gb_FlashFlg = true;
                gb_SetFlg = true;
                gu8_Item = 0;
                break;
            default:
                break;
        }
    }
}

/*********************************************************************
��������: void Disp_DateTimeState(void)
��    ��: ʱ����ʾ������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-23
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_DateTimeState(void)
{
    if (gu32_SystemState == TIMESTATE)
    {   //ϵͳʱ��תΪASCII���������ʾ����
        RTC_sTimetoASC(&SysDataTime, gu8_MainDispArray);
        VFD_AuxDisp_Str("CL ");
    }
    else
    {  //ϵͳ����תΪASCII���������ʾ����
        RTC_sDatetoASC(&SysDataTime, gu8_MainDispArray);
        VFD_AuxDisp_Str("DA ");
    }
    //ASCII��תΪ��ʾ����
    VFD_MainDisp_ASCII(gu8_MainDispArray);
    gu8_MainDispArray[1] |= 0x80;
    gu8_MainDispArray[3] |= 0x80;
    
    Flash_MainDisp(0x20 >> gu8_Item);              //����ʱ������ʱ��λ��˸����
}



