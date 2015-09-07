/*************************************************
Project:                GM8804C-2_ARM
File name:              IO.c
Description:            ��������غ���
Author:                 �Ժ���
Version:                1.0
Date:                   2013-12-4
Others: 
History:
*************************************************/
#include "include.h"
#include "Adaptation.h"

//һЩ��ADת���ٶ���ر�����ʹ�ã����Ա���
u8 const cu8_MultiAd[4] = {1,2,4,8};

u32 gu32_IoInBuf_BINYES[9];              //�����������Զ���  gu32_IoInBuf_BINYES[1~8]
u32 gu32_IoOutBuf_BINYES[13];             //����������Զ���  gu32_IoOutBuf_BINYES[1~12]
u32 gu32_IoInBuf_BINNO[9];              //�����������Զ���
u32 gu32_IoOutBuf_BINNO[13];             //����������Զ���
u32 gu32_IoInBuf_BIN_2[9];              //�����������Զ���
u32 gu32_IoOutBuf_BIN_2[13];             //����������Զ���
u32 gu32_IoInBuf_NO_2[9];              //�����������Զ���
u32 gu32_IoOutBuf_NO_2[13];             //����������Զ���

u32 *gu32p_IoInBuf[9];     //�����������Զ�������ָ��
u32 *gu32p_IoOutBuf[13];    //����������Զ�������ָ��

bool  gb_JSDDelayFlg;               //���ɴ���ʱ������־
bool  gb_SDDelayFlg;                //�ɴ���ʱ������־
bool  gb_SDBDelayFlg;               //�ɴ�ǰ��ʱ������־
u32 gu32_JSDTime;                  //���ɴ���ʱʱ��Ĵ���

u32 gu32_FlgBright;
u32 gu32_IoTestCode;        //��������������
u32 gu32_IoTestCodeSwitch;
u32 gu8_IoTestInTime;
u32 gu32_IoDefCode;        //��������������
u32 gu32_IoDefCodeSwitch;
u32 gu8_IoDefInTime;
u32 gu32_SmallPluseTimeBuf;           //СͶ�㶯��ʱ��Ĵ���
u32 gu32_AutoClrZeroCnt;         //�Զ�������������
u32 gu32_CorrectFallTimeCnt;     //�����������������
u32 gu32_CorrectFallWt;          //��������ۼ�ֵ
bool gb_DiscShakeFlg;           //ж��������
bool gb_DiscShakeStartFlg;      //ж�����ʼ
bool  gb_DiscSumOnFlg;                //�ֶ�ж���ۼƿ���ж�ϱ�־λ
bool  gb_DiscSumOffFlg;               //�ֶ�ж���ۼƹر�ж�ϱ�־λ
u32 gu32_TestTime;          //��ʾ����ʱ�õ�ʱ��Ĵ���



bool gb_RunFlg;
bool gb_Sp1Flg;
bool gb_Sp2Flg;
bool gb_Sp3Flg;
bool gb_CompFlg;
bool gb_OverFlg;
bool gb_UnderFlg;
bool gb_OUOverFlg;            //��Ƿ����ͣ�ر�ʱ��Ƿ��ı�����־ OVER
bool gb_OUUnderFlg;           //��Ƿ����ͣ�ر�ʱ��Ƿ��ı�����־ UNDER
bool gb_PackFlg;
bool gb_DiscFlg;
bool gb_FillFlg;
bool gb_BatchOverFlg;
bool gb_LackFlg;
bool gb_KeyLockFlg;
bool gb_DisRunFlg;
bool gb_FirstStartFlg;           //�������һ�ӱ�־λ
bool gb_OflDelayFlg;             //����ʱ�����־
bool  gb_HighDefineFlg;             //����λ�Ѷ����־
bool  gb_LowDefineFlg;              //����λ�Ѷ����־
bool  gb_MiddleDefineFlg;           //����λ�Ѷ����־
bool  gb_HighFlg;                   //����λ
bool  gb_LowFlg;                    //����λ
bool  gb_MiddleFlg;                 //����λ
bool  gb_LackFlg;                   //ȱ��
bool gb_PrintCodeOutFlg;        //�������
bool gb_EndFlg;                 //ֹͣ����
bool  gb_DiscCloseOKFlg;          //ж���Ź��ŵ�λ����
bool  gb_EnDiscCloseOKFlg;        //ж���Ź��ŵ�λ�Ѷ����־
bool  gb_PackOKFlg;             //�д���λ����
bool  gb_EnPackOKFlg;           //�д���λ�Ѷ����־
bool gb_LiftBagFlg;             //����ź�
bool gb_PushBagFlg;             //�ƴ��ź�
bool gb_DiscEnableOutFlg;       //˫�ӻ������ ������һ��ж��
bool gb_DiscEnableInFlg;        //˫�ӻ������� ����ж��
bool gb_AddingInFlg;            //�޶�˫�ӻ������� ���Ϲ���
bool gb_AddingOutFlg;           //�޶�˫�ӻ������ ���Ϲ������
bool gb_GoFlg;                  //�ֶ�����һ�α�־��
bool gb_ConveyorRunFlg;         //���ͻ�����
bool gb_No2PackOffAnother;      //��һ���Ѿ��ɴ���־
bool gb_No2AddAgainDelay;        //˫���޶���ʱ�������ϱ�־
bool gb_CalLockDefFlg;          //�궨���Ѷ����־λ
bool gb_CalLockFlg;             //�궨������


/*********************************************************************
��������: void IoDefPointerRefresh(u32 fu32_TareMode)
��    ��: ˢ��IO�Զ�������ָ�룬��ͬ����ģʽָ��ͬ����
˵    ��: �ı����ģʽ��Ҫ���øú���
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-3-11
��    ��:                      ʱ    ��: 
*********************************************************************/
void IoDefPointerRefresh(u32 fu32_TareMode)
{
    u8 i;
    
    switch (fu32_TareMode)
    {
        case BINYES:
        default:
            for (i = 0; i <= 8; i++)
                gu32p_IoInBuf[i] = &gu32_IoInBuf_BINYES[i];
            for (i = 0; i <= 12; i++)
                gu32p_IoOutBuf[i] = &gu32_IoOutBuf_BINYES[i];
            break;
        case BINNO:
            for (i = 0; i <= 8; i++)
                gu32p_IoInBuf[i] = &gu32_IoInBuf_BINNO[i];
            for (i = 0; i <= 12; i++)
                gu32p_IoOutBuf[i] = &gu32_IoOutBuf_BINNO[i];
            break;
        case BIN2_A:
        case BIN2_B:
            for (i = 0; i <= 8; i++)
                gu32p_IoInBuf[i] = &gu32_IoInBuf_BIN_2[i];
            for (i = 0; i <= 12; i++)
                gu32p_IoOutBuf[i] = &gu32_IoOutBuf_BIN_2[i];
            break;
        case NO2_A:
        case NO2_B:
            for (i = 0; i <= 8; i++)
                gu32p_IoInBuf[i] = &gu32_IoInBuf_NO_2[i];
            for (i = 0; i <= 12; i++)
                gu32p_IoOutBuf[i] = &gu32_IoOutBuf_NO_2[i];
            break;
    }
}


/*********************************************************************
��������: u16 GetIoAddr(u8 fu8_i, u8 fu8_Num, u32 fu32_TareMode)
��    ��: ����IO�����ַ
˵    ��: 
��ڲ���: ע�� fu8_iֻ�ܵ���0�������룬1�������������ʱfu8_Num���12�����ʱfu8_Num���16
          ����������������
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-1-23
��    ��:                      ʱ    ��: 
*********************************************************************/
u16 GetIoAddr(u8 fu8_i, u8 fu8_Num, u32 fu32_TareMode)
{
    u16 lu16_Addr = FMAddr_IoInBuf1;
    
    switch (fu32_TareMode)
    {
        case BINYES:
        default:
            if (fu8_i == IO_IN)     //���뿪������ַ
                lu16_Addr = FMAddr_IoInBuf1;
            else if (fu8_i == IO_OUT)
                lu16_Addr = FMAddr_IoOutBuf1;
            break;
        case BINNO:
            if (fu8_i == IO_IN)     //���뿪������ַ
                lu16_Addr = FMAddr_IoInBuf1_BINNO;
            else if (fu8_i == IO_OUT)
                lu16_Addr = FMAddr_IoOutBuf1_BINNO;
            break;
        case BIN2_A:
        case BIN2_B:
            if (fu8_i == IO_IN)     //���뿪������ַ
                lu16_Addr = FMAddr_IoInBuf1_BIN_2;
            else if (fu8_i == IO_OUT)
                lu16_Addr = FMAddr_IoOutBuf1_BIN_2;
            break;
    }
    lu16_Addr += ((fu8_Num - 1) * 4);
    return lu16_Addr;
}

/*********************************************************************
��������: void Clr_Alarm(void)
��    ��: �屨������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-15
��    ��:                      ʱ    ��: 
*********************************************************************/
void Clr_Alarm(void)
{
    gb_OUOverFlg = false;
    gb_OUUnderFlg = false;
    if (gb_DispErrorFlg)
    {
        gb_DispErrorFlg = false;
//        gu8_DispErrorNumberBackup = 0;
        gu8_DispErrorNumber = 0;
    }
    gb_AlarmFlg = false;
    if (gb_OverFlg || gb_UnderFlg)          //��Ƿ�� error8
    {
        gb_OverFlg = false;
        gb_UnderFlg = false;
        gu32_Process = T4PROCESS;
        gu32_TimeBuf = gs_Rec.TimeT4 * 10;
        gb_TimeRunFlg = true;                //��ֵ����ʱ��t4�Ѿ�����
        gu32_Time1_5 = gu32_Sys10ms;        //ȡ��ǰʱ��
    }
    if (gb_Error9Flg)       //ж��δ�ɾ����� error9
    {
        gb_Error9Flg = false;
        gb_RunFlg = true;
        RunStopInit(false);
    }
    if (gb_BatchOverFlg)
    {
        gb_BatchOverFlg = false;
        gb_RunFlg = true;
        RunStopInit(false);
    }
}

/*********************************************************************
��������: void JSD_Init(void)
��    ��: ����ʱ�ļ��ɴ�����־��ʼ��
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-4-15
��    ��:                      ʱ    ��: 
*********************************************************************/
void JSD_Init(void)
{
    if (gb_PackFlg)     //�д���Ч
    {
        gb_JSDDelayFlg = false;
        gb_SDBDelayFlg = false;
        gb_SDDelayFlg = true;
    }
    else
    {
        gb_JSDDelayFlg = false;
        gb_SDDelayFlg = false;
        gb_SDBDelayFlg = false;
    }
}

/*********************************************************************
��������: void Deal_Pack(void)
��    ��: ���ɴ�����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-7
��    ��:                      ʱ    ��: 
*********************************************************************/
void Deal_Pack(void)
{
    if (gb_JSDDelayFlg)         //���ɴ�������ʱ��־λ��Ч��Ϊ�м��ɴ�����
    {
        if (gb_SDDelayFlg && (gb_PackFlg == false))         //ԭ���������ȶ��д�״̬�������ɴ���ʱ
        {
            if (gu32_Sys10ms - gu32_JSDTime >= 30)   //�̶����ɴ������ʱΪ300ms
            {
                gb_PackFlg = false;
                gb_JSDDelayFlg = false;                 //������ɴ���ʱ��־
                gb_SDDelayFlg = false;
                gb_SDBDelayFlg = false;
                if (gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                    gb_DiscEnableOutFlg = true; //�ɴ����������һ�Ӽд�
            }
        }
        else if (gb_SDBDelayFlg && gb_PackFlg)      //�ɴ�ǰ��ʱ����
        {
            if (gu32_Sys10ms - gu32_JSDTime >= gs_Rec.TimeT7 * 10)   //�ɴ�ǰ��ʱʱ�䵽
            {
                //�Ĵ���ж�ϡ�����ʱ�ȴ�
                if (((gb_FlapStartFlg || gb_FlapWaitFlg) && (gb_ExtFlapBagFlg == false))
                    || gb_DiscFlg || gb_PrintCodeIngFlg)
                    gu32_JSDTime = gu32_Sys10ms - gs_Rec.TimeT7 * 10;
                else
                {
                    gb_PackFlg = false;         //�ɴ�ǰ��ʱ����д������Ч
                    gb_SDBDelayFlg = false;
                    gb_JSDDelayFlg = true;
                    gb_SDDelayFlg = true;      //�����ɴ���ʱ
                    gu32_JSDTime = gu32_Sys10ms;
                }
            }
        }
        else            //ԭ�������ɴ�״̬�������д���ʱ
        {
            if (gu32_Sys10ms - gu32_JSDTime >= gs_Rec.TimeT6 * 10)        //�д���ʱʱ�䵽
            {
                gb_JSDDelayFlg = false;
                gb_SDDelayFlg = true;          //�д���ɿ����ɴ�
            }
        }
    }
    if ((gs_Setup.TareMode == BINNO || gs_Setup.TareMode == NO2_A || gs_Setup.TareMode == NO2_B) && gs_Setup.GorNMode == NET && gb_PackFlg == false)
    {
        //�д������Чʱ���Ƥ���ѻ�ȡ����־
        gb_TareGetedFlg = false;
    }
}

/*********************************************************************
��������: void IO_Init(void)
��    ��: ���������������ʼ��
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-4
��    ��:                      ʱ    ��: 
*********************************************************************/
void IO_Init(void)
{
    //8���뿪����IO�������Ͷ���
    GPIO_Config(GPIO2, (1<<15), GPIO_IN_TRI_TTL); //IN0_READ
    GPIO_Config(GPIO2, (1<<14), GPIO_IN_TRI_TTL); //IN1_READ
    GPIO_Config(GPIO2, (1<<13), GPIO_IN_TRI_TTL); //IN2_READ
    GPIO_Config(GPIO2, (1<<12), GPIO_IN_TRI_TTL); //IN3_READ
    GPIO_Config(GPIO2, (1<<11), GPIO_IN_TRI_TTL); //IN4_READ
    GPIO_Config(GPIO2, (1<<10), GPIO_IN_TRI_TTL); //IN5_READ
    GPIO_Config(GPIO2, (1<<7) , GPIO_IN_TRI_TTL); //IN6_READ
    GPIO_Config(GPIO2, (1<<6) , GPIO_IN_TRI_TTL); //IN7_READ
    //12���������IO�������Ͷ���
    GPIO_Config(GPIO2, (1<<5) , GPIO_OUT_PP);      //OUT0
    GPIO_Config(GPIO2, (1<<4) , GPIO_OUT_PP);      //OUT1
    GPIO_Config(GPIO2, (1<<3) , GPIO_OUT_PP);      //OUT2
    GPIO_Config(GPIO2, (1<<2) , GPIO_OUT_PP);      //OUT3
    GPIO_Config(GPIO0, (1<<14), GPIO_OUT_PP);      //OUT4
    GPIO_Config(GPIO0, (1<<13), GPIO_OUT_PP);      //OUT5
    GPIO_Config(GPIO2, (1<<1) , GPIO_OUT_PP);      //OUT6
    GPIO_Config(GPIO2, (1<<0) , GPIO_OUT_PP);      //OUT7
    GPIO_Config(GPIO0, (1<<12), GPIO_OUT_PP);      //OUT8
    GPIO_Config(GPIO0, (1<<7) , GPIO_OUT_PP);      //OUT9
    GPIO_Config(GPIO0, (1<<6) , GPIO_OUT_PP);      //OUT10
    GPIO_Config(GPIO0, (1<<5) , GPIO_OUT_PP);      //OUT11
    //���������ȫ����Ϊ��Ч
    OUT1_CLR;
    OUT2_CLR;
    OUT3_CLR;
    OUT4_CLR;
    OUT5_CLR;
    OUT6_CLR;
    OUT7_CLR;
    OUT8_CLR;
    OUT9_CLR;
    OUT10_CLR;
    OUT11_CLR;
    OUT12_CLR;
}

/*********************************************************************
��������: void IO_Outport(u8 PortId, bool Port_Val)
��    ��: ���������������״̬
˵    ��: 
��ڲ���: PortId = 1~16 ��Ӧ out 1~16���������
          Port_Val = 1 ��Ч  0 ��Ч
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-21
��    ��:                      ʱ    ��: 
*********************************************************************/
void IO_Outport(u8 PortId, bool Port_Val)
{
    u16 i = 0x0001;
    
    switch (PortId)
    {
        case 1:
            if (Port_Val == false)
            {
                gu16_MbIoOutState &= (~i);
                OUT1_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= i;
                OUT1_SET;
            }
            break;
        case 2:
            if (Port_Val == false) 
            {
                gu16_MbIoOutState &= (~(i<<1));
                OUT2_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= (i<<1);
                OUT2_SET;
            }
            break;
        case 3:
            if (Port_Val == false) 
            {
                gu16_MbIoOutState &= (~(i<<2));
                OUT3_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= (i<<2);
                OUT3_SET;
            }
            break;
        case 4:
            if (Port_Val == false) 
            {
                gu16_MbIoOutState &= (~(i<<3));
                OUT4_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= (i<<3);
                OUT4_SET;
            }
            break;
        case 5:
            if (Port_Val == false) 
            {
                gu16_MbIoOutState &= (~(i<<4));
                OUT5_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= (i<<4);
                OUT5_SET;
            }
            break;
        case 6:
            if (Port_Val == false) 
            {
                gu16_MbIoOutState &= (~(i<<5));
                OUT6_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= (i<<5);
                OUT6_SET;
            }
            break;
        case 7:
            if (Port_Val == false) 
            {
                gu16_MbIoOutState &= (~(i<<6));
                OUT7_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= (i<<6);
                OUT7_SET;
            }
            break;
        case 8:
            if (Port_Val == false) 
            {
                gu16_MbIoOutState &= (~(i<<7));
                OUT8_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= (i<<7);
                OUT8_SET;
            }
            break;
        case 9:
            if (Port_Val == false) 
            {
                gu16_MbIoOutState &= (~(i<<8));
                OUT9_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= (i<<8);
                OUT9_SET;
            }
            break;
        case 10:
            if (Port_Val == false) 
            {
                gu16_MbIoOutState &= (~(i<<9));
                OUT10_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= (i<<9);
                OUT10_SET;
            }
            break;
        case 11:
            if (Port_Val == false) 
            {
                gu16_MbIoOutState &= (~(i<<10));
                OUT11_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= (i<<10);
                OUT11_SET;
            }
            break;
        case 12:
            if (Port_Val == false) 
            {
                gu16_MbIoOutState &= (~(i<<11));
                OUT12_CLR;
            }
            else 
            {
                gu16_MbIoOutState |= (i<<11);
                OUT12_SET;
            }
            break;
        default:
            break;
    }
}


/*********************************************************************
��������: void ConveyorDeal(bool *fbp_ConveyorStart)
��    ��: ����ƴ�����
˵    ��: 
��ڲ���: *fbp_ConveyorStart ���������־λ
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2015-2-3
��    ��:                      ʱ    ��: 
*********************************************************************/
void ConveyorDeal(bool *fbp_ConveyorStart)
{
    static bool sb_CStartFlg = false;
    static bool sb_CStartAgainFlg = false;
    static u32 su32_ConveyorDelayTemp;
    static u32 su32_ConveyorRunTemp;
    static bool sb_ConveyorDelayFlg = false;    //���ͻ�������ʱ������
    
    if (*fbp_ConveyorStart == true)
    {   //���ͻ�����
        *fbp_ConveyorStart = false;
        if (sb_CStartFlg) 
        {   //���ڴ�����һ�����ͻ���δ�������������һ�εĴ���
            sb_CStartAgainFlg = true;
        }
        else
        {
            gb_ConveyorRunFlg = false;
        }
        sb_CStartFlg = true;
        sb_ConveyorDelayFlg = true;
        su32_ConveyorDelayTemp = gu32_Sys10ms;
    }
    
    //���ͻ�����
    if (sb_CStartFlg == true)
    {   //���ͻ������Чʱ�䲻Ϊ0 ���ͻ���������
        if (gs_Setup.No2ConveyorRunTime != 0)
        {
            if (gb_ConveyorRunFlg)
            {   //���ͻ�����Ѿ���Ч
                if (gu32_Sys10ms - su32_ConveyorRunTemp >= gs_Setup.No2ConveyorRunTime * 10)
                {   //���ͻ��������
                    gb_ConveyorRunFlg = false;
                    if (sb_CStartAgainFlg == false) //���ͻ��������ǰû����һ�������źţ���������ͻ����
                        sb_CStartFlg = false;
                    else    //����һ��������������
                        sb_CStartAgainFlg = false;
                    gb_No2AddAgainDelay = false;   //���ͻ���ֹͣ���ϵȴ�ʱ�仹û�����Զ�ȡ���ȴ�
                }
                if (gu32_Sys10ms - su32_ConveyorRunTemp >= gs_Setup.No2AddAgainDelayTime * 10)
                {   //�ٴ������ļ��ϵȴ�ʱ��
                    gb_No2AddAgainDelay = false;
                }
            }
            else if (sb_ConveyorDelayFlg)
            {   //���ͻ�������ʱ�Ѿ�����
                if (gu32_Sys10ms - su32_ConveyorDelayTemp >= gs_Setup.No2ConveyorDelayTime * 10)
                {   //���ͻ���ʱʱ�䵽�������ͻ����
                    sb_ConveyorDelayFlg = false;
                    gb_ConveyorRunFlg = true;
                    //�˴�û��ʹ��su32_ConveyorRunTemp = gu32_Sys10ms��Ϊ��֧���ϴ�û�����ͻ����û�н���
                    //��һ�����ͻ������Ч��Ϊ�˼����ϴν�����Ҫ�ټ�������೤ʱ�䡣
                    su32_ConveyorRunTemp = su32_ConveyorDelayTemp + gs_Setup.No2ConveyorDelayTime * 10;
                }
            }
        }
        else
            sb_CStartFlg = false;
    }
}


/*********************************************************************
��������: void IO_OutPut(void)
��    ��: �������������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-7
��    ��:                      ʱ    ��: 
*********************************************************************/
void IO_OutPut(void)
{
    u8 i;
    bool lb_State;
    u16  lu16_Temp = 0x0001;
    
    for (i = 1; i <= 12; i++)
    {
        lb_State = false;
        switch (*gu32p_IoOutBuf[i])
        {
            case 1:         //����
                lb_State = gb_RunFlg;
                break;
            case 2:         //ֹͣ
                lb_State = (!gb_RunFlg);
                break;
            case 3:         //��Ͷ
                lb_State = Sp_Disc_State(SP1_STATE);
                break;
            case 4:         //��Ͷ
                if (gs_Setup.ResultHoldSwitch != 0)
                {
                    if (gb_Sp2StopTimeRunFlg == false)  //��Ͷ����Ԥ���ֹ���ʱ���ʱ���� ������ȥ������Ͷ�����
                        lb_State = Sp_Disc_State(SP2_STATE);
                }
                else
                {
                    lb_State = Sp_Disc_State(SP2_STATE);
                }
                break;
            case 5:         //СͶ
                lb_State = Sp_Disc_State(SP3_STATE);
                break;
            case 6:         //��ֵ
                lb_State = gb_CompFlg;
                break;
            case 7:         //��Ƿ��
                lb_State = (gb_OverFlg || gb_UnderFlg || gb_OUOverFlg || gb_OUUnderFlg);
                break;
            case 8:         //����
                lb_State = gb_AlarmFlg;
                break;
            case 9:        //�д�
                lb_State = gb_PackFlg;
                break;
            case 10:        //�Ĵ�
                lb_State = (gb_FlapBagOutFlg || gb_FlapAllHighFlg);
                break;
            case 11:        //ж��
                lb_State = Sp_Disc_State(DISC_STATE);
                break;
            case 12:        //����
                lb_State = gb_NzFlg;
                break;
            case 13:        //����
                lb_State = gb_FillFlg;
                break;
            case 14:        //�������
                lb_State = gb_BatchOverFlg;
                break;
            case 15:        //ȱ��
                lb_State = gb_LackFlg;
                break;
            case 16:        //ж�����
                lb_State = gb_DiscShakeFlg;
                break;
            case 17:        //�������
                lb_State = gb_PrintCodeOutFlg;
                break;
            case 18:        //����
                lb_State = gb_Sp3Flg;
                break;
            case 19:        //���
                lb_State = gb_LiftBagFlg;
                break;
            case 20:        //�ƴ�
                lb_State = gb_PushBagFlg;
                break;
            case 21:        //˫����������
                if (gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                {   //������һ��ж��
                    lb_State = gb_DiscEnableOutFlg;
                }
                else
                {
                    lb_State = gb_AddingOutFlg;
                }
                break;
            case 22:        //���ͻ����
                lb_State = gb_ConveyorRunFlg;
                break;
            default:
                break;
        }
        if (gu16_MbIoTestSwitch != 0)
        {   //modbus���������Դ�
            IO_Outport(i, gu16_MbIoOutTest & lu16_Temp);
            lu16_Temp = lu16_Temp << 1;
        }
        else if (gu16_MbIOOutInit)
        {   //modbus������debug�� 0093��ַ
            IO_Outport(i, gu16_MbIoOutDebug & lu16_Temp);
            lu16_Temp = lu16_Temp << 1;
        }
        else
        {
            if (gs_Setup.ResultHoldSwitch != 0)
            {
                if ((*gu32p_IoOutBuf[i] != 4) || gb_Sp2StopTimeRunFlg == false)  
                    //��Ͷ����Ԥ���ֹ���ʱ���ʱ���� ������ȥ������Ͷ�����
                    IO_Outport(i, lb_State);          //lb_State = 0�����������Ч  1�����������Ч
            }
            else
            {
                IO_Outport(i, lb_State);          //lb_State = 0�����������Ч  1�����������Ч
            }
        }
    }
}

/*********************************************************************
��������: bool IO_Inport(u8 PortId)
��    ��: ��ȡ�����������״̬
˵    ��: 
��ڲ���: PortId = 1~5 ��Ӧ in 1~8����������
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-21
��    ��:                      ʱ    ��: 
*********************************************************************/
bool IO_Inport(u8 PortId)
{
    bool lb_State = false;
    
    switch (PortId)
    {
        case 1:
            lb_State = (IN1_READ) ? false : true;
            break;                              
        case 2:                                 
            lb_State = (IN2_READ) ? false : true;
            break;                              
        case 3:                                 
            lb_State = (IN3_READ) ? false : true;
            break;                              
        case 4:                                 
            lb_State = (IN4_READ) ? false : true;
            break;                              
        case 5:                                 
            lb_State = (IN5_READ) ? false : true;
            break;                              
        case 6:                                 
            lb_State = (IN6_READ) ? false : true;
            break;                              
        case 7:                                 
            lb_State = (IN7_READ) ? false : true;
            break;                              
        case 8:                                 
            lb_State = (IN8_READ) ? false : true;
            break;
        default:
            break;
    }
    return lb_State;
}

/*********************************************************************
��������: void IO_CloseOut(void)
��    ��: ������п��������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-21
��    ��:                      ʱ    ��: 
*********************************************************************/
void IO_CloseOut(void)
{
    u8 i;
    
    for (i = 1; i <= 12; i++)
    {
        IO_Outport(i, false);          //true�����������Ч  false�����������Ч
    }
}


/*********************************************************************
��������: void Key_IoTestState(void)
��    ��: IO����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-21
��    ��:                      ʱ    ��: 
*********************************************************************/
void Key_IoTestState(void)
{
    u32 i = 1;
    u8 luc_DataLen = 0;      //��������λ��
    
    gb_FlashFlg = false;
    
    if (gu8_Item == IOTEST_CHECKCODE)  //������֤
    {
        luc_DataLen = 6;
        gb_FirstNumKeyFlg = false;
        ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
        if (gu32_KeyCode == K_ENTER)           //ȷ�ϼ�����
        {
            gb_FirstNumKeyFlg = true;
            gu8_IoTestInTime++;
            if ((ulParameter.ul == gu32_IoTestCode && gu8_DataInLength ==6) || 
                (ulParameter.ul == SUPERCODE && gu8_DataInLength ==6))        //������������趨����򳬼�����
            {
                gu8_IoTestInTime = 0;            //�����������������������
                ulParameter.ul = 0;
                gu8_Item = IOTEST;  //�������״̬
            }
            else if (gu8_IoTestInTime >= 3)      //����������󳬹�3��
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
        }
        if (gu32_KeyCode == K_ESC)
        {
            gu32_SystemState = STOPSTATE;
        }
    }
    else if (gu8_Item == IOTEST)  //����������״̬
    {
        switch (gu32_KeyCode)            //��������Ӧ�Ŀ����������Ч
        {
            case K_1:
                if (gu32_FlgBright & (i << 17))
                    gu32_FlgBright &= (~(i << 17));
                else 
                    gu32_FlgBright |= (i << 17);
                IO_Outport(1, gu32_FlgBright & (i << 17));
                break;
            case K_2:
                if (gu32_FlgBright & (i << 16))
                    gu32_FlgBright &= (~(i << 16));
                else 
                    gu32_FlgBright |= (i << 16);
                IO_Outport(2, gu32_FlgBright & (i << 16));
                break;
            case K_3:
                if (gu32_FlgBright & (i << 15))
                    gu32_FlgBright &= (~(i << 15));
                else 
                    gu32_FlgBright |= (i << 15);
                IO_Outport(3, gu32_FlgBright & (i << 15));
                break;
            case K_4:
                if (gu32_FlgBright & (i << 14))
                    gu32_FlgBright &= (~(i << 14));
                else 
                    gu32_FlgBright |= (i << 14);
                IO_Outport(4, gu32_FlgBright & (i << 14));
                break;
            case K_5:
                if (gu32_FlgBright & (i << 13))
                    gu32_FlgBright &= (~(i << 13));
                else 
                    gu32_FlgBright |= (i << 13);
                IO_Outport(5, gu32_FlgBright & (i << 13));
                break;
            case K_6:
                if (gu32_FlgBright & (i << 12))
                    gu32_FlgBright &= (~(i << 12));
                else 
                    gu32_FlgBright |= (i << 12);
                IO_Outport(6, gu32_FlgBright & (i << 12));
                break;
            case K_7:
                if (gu32_FlgBright & (i << 11))
                    gu32_FlgBright &= (~(i << 11));
                else 
                    gu32_FlgBright |= (i << 11);
                IO_Outport(7, gu32_FlgBright & (i << 11));
                break;
            case K_8:
                if (gu32_FlgBright & (i << 10))
                    gu32_FlgBright &= (~(i << 10));
                else 
                    gu32_FlgBright |= (i << 10);
                IO_Outport(8, gu32_FlgBright & (i << 10));
                break;
            case K_9:
                if (gu32_FlgBright & (i << 9))
                    gu32_FlgBright &= (~(i << 9));
                else 
                    gu32_FlgBright |= (i << 9);
                IO_Outport(9, gu32_FlgBright & (i << 9));
                break;
            case K_0:
                if (gu32_FlgBright & (i << 8))
                    gu32_FlgBright &= (~(i << 8));
                else 
                    gu32_FlgBright |= (i << 8);
                IO_Outport(10, gu32_FlgBright & (i << 8));
                break;
            case K_INC:
                if (gu32_FlgBright & (i << 7))
                    gu32_FlgBright &= (~(i << 7));
                else 
                    gu32_FlgBright |= (i << 7);
                IO_Outport(11, gu32_FlgBright & (i << 7));
                break;
            case K_RIGHT:
                if (gu32_FlgBright & (i << 6))
                    gu32_FlgBright &= (~(i << 6));
                else 
                    gu32_FlgBright |= (i << 6);
                IO_Outport(12, gu32_FlgBright & (i << 6));
                break;
            case K_ESC:
                gu32_SystemState = STOPSTATE;
                gu32_FlgBright = 0;
                break;
            case K_SET:
                gu8_Item = IOTEST_SWITCH;
                ulParameter.ul = gu32_IoTestCodeSwitch;
                break;
            case K_8_2S:    //����8������ʾ������״̬��������������
                gu8_Item = IOTEST_TESTDISP;
                ulParameter.ul = 0;
                gu32_TestTime = gu32_Sys10ms;
            default:
                break;
        }
    }
    else if (gu8_Item == IOTEST_SWITCH)     //���뿪��
    {
        ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 1);      //�����л����á����޸�
        switch (gu32_KeyCode)
        {
            case K_ESC:
                gu8_Item = IOTEST;
                break;
            case K_ENTER:
                if (ulParameter.ul == 0)
                    gu8_Item = IOTEST;
                else
                    gu8_Item = IOTEST_SETCODE;
                gu32_IoTestCodeSwitch = ulParameter.ul;
                FRAM_WriteDW(FMAddr_IoTestCodeSwitch, gu32_IoTestCodeSwitch);
                gu8_DataInLength = 0;
                break;
        }
    }
    else if (gu8_Item == IOTEST_SETCODE)        //��������
    {
        gb_FirstNumKeyFlg = false;
        luc_DataLen = 0;
        if (gu32_KeyCode == K_SET)           //������������״̬
            gb_SetFlg = true;
        if (gb_SetFlg)
        {
            if (gu32_KeyCode == K_ESC)       //�˳���������״̬
            {
                gb_SetFlg = false;
                gu32_KeyCode = 0;
                gu8_IoTestInTime = 0;
                gu8_DataInLength = 0;
            }
            else
                luc_DataLen = 6;
        }
        if (gu32_KeyCode == K_ESC)
        {
            gu8_Item = IOTEST_SWITCH;
            ulParameter.ul = gu32_IoTestCodeSwitch;
        }
        if (gu32_KeyCode == K_ENTER)
        {
            if (gb_SetFlg == true)
            {
                gu8_IoTestInTime++;
                if (gu8_IoTestInTime >= 2)
                {
                    if (ulParameter.ul == gu32_DataTemp && gu8_DataInLength == 6)         //�������������һ��
                    {
                        gu8_IoTestInTime = 0;
                        gb_SetFlg = false;
                        gu32_IoTestCode = ulParameter.ul;
                        FRAM_WriteDW(FMAddr_IoTestCode, gu32_IoTestCode);          //��������
                        gu8_Item = IOTEST_SWITCH;
                        ulParameter.ul = gu32_IoTestCodeSwitch;
                    }
                    else
                    {
                        gu8_IoTestInTime = 0;
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
                        gu8_IoTestInTime = 0;
                        ErrorDeal(0, 100);
                        gb_FirstNumKeyFlg = true;
                        ulParameter.ul = 0;
                        gu8_DataInLength = 0;
                        return;
                    }
                }
            }
        }
        ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
    }
    else
    {
        if (gu32_KeyCode == K_INC)
        {
            if (++ulParameter.ul > 1)
                ulParameter.ul = 0;
        }
        if (gu32_KeyCode == K_ZERO)
            ulParameter.ul = 0;
        
        if (gu32_KeyCode == K_ESC)
        {
            ulParameter.ul = 0;
            gu8_Item = IOTEST;  //�������״̬
        }
    }
}

/*********************************************************************
��������: void Disp_IoTestState(void)
��    ��: IO������ʾ����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-21
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_IoTestState(void)
{
    u8 i;
    
    if (gu8_Item == IOTEST_CHECKCODE)  //������֤
    {
        Disp_InputCode();
        gb_FlashFlg = true;
        Flash_MainDisp(0x01);                //��˸����
    }
    else if (gu8_Item == IOTEST)
    {
        //���뿪������Ч��ʾF����Ч��ʾo��8��F��Ӧ8������������
        VFD_MainDisp_Str("FFFFFF");
        VFD_AuxDisp_Str("FF ");
        
        for (i = 1; i <= 8; i++)           //IN1~IN8
        {
            if (IO_Inport(i) == true)        //������Ч��Ӧλ����ʾo
            {
                if (i <= 6)
                    gu8_MainDispArray[i-1] = SEG_o;
                else
                    gu8_AuxDispArray[i-7] = SEG_o;
            }
        }
        VFD_FlgDisp(gu32_FlgBright);    //��־����ʾ
    }
    else if (gu8_Item == IOTEST_SWITCH)
    {
        Disp_OnOff(ulParameter.ul);           //��ʾ����
        VFD_AuxDisp_Str("PAS");
    }
    else if (gu8_Item == IOTEST_SETCODE)
    {
        Disp_InputCode();       //����������ʾ����
        if (gb_SetFlg == true)
            gb_FlashFlg = true;
        else
            gb_FlashFlg = false;
        Flash_MainDisp(0x01);                //��˸����
    }
    else    //��ʾ����
    {
        if (ulParameter.ul == 0)
        {   //��˸״̬
            if(gu32_Sys10ms - gu32_TestTime > 60)
            {   //����ʾ
                VFD_ClrDispRam(1, 0);
                if (gu32_Sys10ms - gu32_TestTime > 120)
                    gu32_TestTime = gu32_Sys10ms;
            }
            else
            {   //�����ʾ
                VFD_FillDispRam(0,1);
            }
        }
        else
        {   //����״̬
            VFD_FillDispRam(0,1);
        }
    }
}


/*********************************************************************
��������: void Key_IoDefState(void)
��    ��: Io�Զ��尴������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-25
��    ��:                      ʱ    ��: 
*********************************************************************/
void Key_IoDefState(void)
{
    u8 luc_DataLen = 2;      //��������λ��
    static u8 su8_ItemBak;
    
    if (gu8_Item == IODEF_CHECKCODE)    //��������
    {
        luc_DataLen = 6;
        gb_FirstNumKeyFlg = false;
        ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
        if (gu32_KeyCode == K_ENTER)           //ȷ�ϼ�����
        {
            gb_FirstNumKeyFlg = true;
            gu8_IoDefInTime++;
            if ((ulParameter.ul == gu32_IoDefCode && gu8_DataInLength ==6) || 
                (ulParameter.ul == SUPERCODE && gu8_DataInLength ==6))        //������������趨����򳬼�����
            {
                gu8_IoDefInTime = 0;            //�����������������������
                gu8_Item = IODEF_IN1;  //�����Զ���״̬
                ulParameter.ul = *gu32p_IoInBuf[1];
            }
            else if (gu8_IoDefInTime >= 3)      //����������󳬹�3��
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
        }
        if (gu32_KeyCode == K_ESC)
        {
            gu32_SystemState = STOPSTATE;
        }
    }
    else if (gu8_Item >= IODEF_IN1 && gu8_Item <= IODEF_OUT12)     //�������Զ���
    {
        //��������
        ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
        //�����������ݳ����Զ��巶Χ����ʾ������˸
        if (gu8_Item <= 8)
        {
            if (ulParameter.ul > IO_INMAX)  //�������Զ��峬����Χ
                gb_FlashFlg = true;
            else
                gb_FlashFlg = false;
        }
        else
        {
            if (ulParameter.ul > IO_OUTMAX)  //������Զ��峬����Χ
                gb_FlashFlg = true;
            else
                gb_FlashFlg = false;
        }
        switch(gu32_KeyCode)
        {
            case K_SET:
                su8_ItemBak = gu8_Item;
                gu8_Item = IODEF_SWITCH;
                ulParameter.ul = gu32_IoDefCodeSwitch;
                break;
            case K_ZERO:
                ulParameter.ul = 0;
                break;
            case K_ESC:
                gu32_SystemState = STOPSTATE;
                break;
            case K_RIGHT:
                gu8_Item++;
                gb_FlashFlg = false;
                gb_FirstNumKeyFlg = true;
                if (gu8_Item > 20)
                    gu8_Item = 1;
                ulParameter.ul = (gu8_Item > IODEF_IN8) ? *gu32p_IoOutBuf[gu8_Item - 8] : *gu32p_IoInBuf[gu8_Item];
                break;
            case K_INC:
                if (gb_FlashFlg == true)    //���������˸״̬��δ����״̬�����������¶�ȡδ�޸�ǰ��ֵ��++
                {
                    gb_FlashFlg = false;
                ulParameter.ul = (gu8_Item > IODEF_IN8) ? *gu32p_IoOutBuf[gu8_Item - 8] : *gu32p_IoInBuf[gu8_Item];
                }
                ulParameter.ul++;
                if (gu8_Item <= 8)
                {
                    if (ulParameter.ul > IO_INMAX)
                        ulParameter.ul = 0;
                }
                else
                {
                    if (ulParameter.ul > IO_OUTMAX)
                        ulParameter.ul = 0;
                }
                break;
            case K_ENTER:
                if (gb_FlashFlg)    //���������˸״̬��˵����ǰ�������ݲ����Ϸ�Χ
                {
                    ErrorDeal(0, 100);
                    ulParameter.ul = (gu8_Item > IODEF_IN8) ? *gu32p_IoOutBuf[gu8_Item - 8] : *gu32p_IoInBuf[gu8_Item];
                    gb_FlashFlg = false;
                    gb_FirstNumKeyFlg = true;
                    return;
                }
                gb_FlashFlg = false;
                gb_FirstNumKeyFlg = true;
                if (gu8_Item <= 8)             //�������뿪����
                {
                    *gu32p_IoInBuf[gu8_Item] = ulParameter.ul;
                    FRAM_WriteDW(GetIoAddr( IO_IN, 1, gs_Setup.TareMode) + (gu8_Item - 1) * 4, *gu32p_IoInBuf[gu8_Item]);
                }
                else                            //�������������
                {
                    *gu32p_IoOutBuf[gu8_Item - 8] = ulParameter.ul;
                    FRAM_WriteDW(GetIoAddr( IO_OUT, 1, gs_Setup.TareMode) + (gu8_Item - 9) * 4, *gu32p_IoOutBuf[gu8_Item - 8]);
                }
                gu8_Item++;
                if (gu8_Item > 20)
                    gu8_Item = 1;
                ulParameter.ul = (gu8_Item > IODEF_IN8) ? *gu32p_IoOutBuf[gu8_Item - 8] : *gu32p_IoInBuf[gu8_Item];
                break;
            default:
                break;
        }
    }
    else if (gu8_Item == IODEF_SWITCH)  //���뿪��
    {
        ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 1);      //�����л����á����޸�
        switch (gu32_KeyCode)
        {
            case K_ESC:
                gu8_Item = su8_ItemBak;
                ulParameter.ul = (su8_ItemBak > IODEF_IN8) ? *gu32p_IoOutBuf[gu8_Item - 8] : *gu32p_IoInBuf[gu8_Item];
                break;
            case K_ENTER:
                if (ulParameter.ul == 0)
                    gu8_Item = su8_ItemBak;
                else
                    gu8_Item = IODEF_SETCODE;
                gu32_IoDefCodeSwitch = ulParameter.ul;
                FRAM_WriteDW(FMAddr_IoDefCodeSwitch, gu32_IoDefCodeSwitch);
                ulParameter.ul = (gu8_Item > IODEF_IN8) ? *gu32p_IoOutBuf[gu8_Item - 8] : *gu32p_IoInBuf[gu8_Item];
                gu8_DataInLength = 0;
                break;
        }
    }
    else //��������
    {
        gb_FirstNumKeyFlg = false;
        luc_DataLen = 0;
        if (gu32_KeyCode == K_SET)           //������������״̬
            gb_SetFlg = true;
        if (gb_SetFlg)
        {
            if (gu32_KeyCode == K_ESC)       //�˳���������״̬
            {
                gb_SetFlg = false;
                gu32_KeyCode = 0;
                gu8_IoDefInTime = 0;
                gu8_DataInLength = 0;
            }
            else
                luc_DataLen = 6;
        }
        if (gu32_KeyCode == K_ESC)
        {
            gu8_Item = IODEF_SWITCH;
            ulParameter.ul = gu32_IoDefCodeSwitch;
        }
        if (gu32_KeyCode == K_ENTER)
        {
            if (gb_SetFlg == true)
            {
                gu8_IoDefInTime++;
                if (gu8_IoDefInTime >= 2)
                {
                    if (ulParameter.ul == gu32_DataTemp && gu8_DataInLength == 6)         //�������������һ��
                    {
                        gu8_IoDefInTime = 0;
                        gb_SetFlg = false;
                        gu32_IoDefCode = ulParameter.ul;
                        FRAM_WriteDW(FMAddr_IoDefCode, gu32_IoDefCode);          //��������
                        gu8_Item = IODEF_SWITCH;
                        ulParameter.ul = gu32_IoDefCodeSwitch;
                    }
                    else
                    {
                        gu8_IoDefInTime = 0;
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
                        gu8_IoDefInTime = 0;
                        ErrorDeal(0, 100);
                        gb_FirstNumKeyFlg = true;
                        ulParameter.ul = 0;
                        gu8_DataInLength = 0;
                        return;
                    }
                }
            }
        }
        ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
    }
}

/*********************************************************************
��������: void Disp_IoDefState(void)
��    ��: IO�Զ�����ʾ����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-25
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_IoDefState(void)
{
    u8 i;
    
    if (gu8_Item == IODEF_CHECKCODE)    //������֤
    {
        Disp_InputCode();
        gb_FlashFlg = true;
        Flash_MainDisp(0x01);                //��˸����
    }
    else if (gu8_Item >= IODEF_IN1 && gu8_Item <= IODEF_OUT12)
    {
        if (gu8_Item <= 8)             //�����Զ���
        {
            gu8_MainDispArray[2] = SEG_I;
            gu8_MainDispArray[3] = SEG_N;
            gu8_AuxDispArray[0] = SEG_I;
            i = gu8_Item;
        }
        else                            //����Զ���
        {
            gu8_MainDispArray[1] = SEG_O;
            gu8_MainDispArray[2] = SEG_U;
            gu8_MainDispArray[3] = SEG_T;
            gu8_AuxDispArray[0] = SEG_O;
            i = gu8_Item - 8;
        }
        gu8_MainDispArray[4] = Value_To_SEG[i / 10];
        gu8_MainDispArray[5] = Value_To_SEG[i % 10];
        gu8_AuxDispArray[1] = Value_To_SEG[ulParameter.ul / 10];
        gu8_AuxDispArray[2] = Value_To_SEG[ulParameter.ul % 10];
        Flash_AuxDisp(0x03);                //��˸����
    }
    else if (gu8_Item == IODEF_SWITCH)  //
    {
        Disp_OnOff(ulParameter.ul);           //��ʾ����
        VFD_AuxDisp_Str("PAS");
    }
    else
    {
        Disp_InputCode();       //����������ʾ����
        if (gb_SetFlg == true)
            gb_FlashFlg = true;
        else
            gb_FlashFlg = false;
        Flash_MainDisp(0x01);                //��˸����
    }
}

/*********************************************************************
��������: void RunStopInit(bool fb_RunStop)
��    ��: ���л�ֹͣ�Ĵ���
˵    ��: 
��ڲ���: fb_RunStop = 1 ����   0 ֹͣ
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-7
��    ��:                      ʱ    ��: 
*********************************************************************/
void RunStopInit(bool fb_RunStop)
{
    if ((fb_RunStop == false) || (gb_AlarmFlg == false))
    {
        if (fb_RunStop)             //���д���
        {
            fb_RunStop = false;
            if (gb_RunFlg == false)      //ԭ��ֹͣ״̬��������
            {
                if (gs_Rec.Target != 0)          //����Ŀ��ֵ��Ϊ0ʱ����������������ʾerror6
                {
                    gb_RunFlg = true;      //����
                    fb_RunStop = true;
                    gu32_SystemState = RUNSTATE;
                    gu32_Process = T1PROCESS;   //������A����T1��ʱ�׶�
                    gu32_TimeBuf = gs_Rec.TimeT1 * 10;
                    gu32_Time1_5 = gu32_Sys10ms;
                    JSD_Init();
                    if (gu32_BatchTimeCnt == 0)
                    {
                        gu32_BatchTimeCnt = gu32_BatchTime;
                        FRAM_WriteDW(FMAddr_BatchTimeCnt, gu32_BatchTimeCnt);
                    }
                    gu32_TargetTemp = gs_Rec.Target;
                    gu32_WeighTimeCnt = gs_Rec.CombinedNum;              //������ϴ���
                    gb_FirstPrintFlg_UART0 = true;    //���к��һ�δ�ӡҪ��ӡ̨ͷ
                    gb_FirstPrintFlg_UART1 = true;    //���к��һ�δ�ӡҪ��ӡ̨ͷ
                    if (gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) //˫�ӻ���ģʽ������ʱ������һ��ж��
                        gb_DiscEnableOutFlg = true;
                    gb_DiscWtGetedFlg = false;
                    //������ʱ��ṹ�����
                    gs_DebugRunTime.u32Sp1Time = 0;
                    gs_DebugRunTime.u32Sp2Time = 0;
                    gs_DebugRunTime.u32Sp3Time = 0;
                    gs_DebugRunTime.u32RunCmpTime = 0;
                    gs_DebugRunTime.bGetRunCmpTimeFlg = false;
                    gs_DebugRunTime.u32OneTareTime = 0;
                    gs_DebugRunTime.u32RunStartTimeTemp = gu32_Sys1ms; //��¼����ʱ��
                    gs_DebugRunTime.u32SumCnt = 0;
                    gs_DebugRunTime.u32TotalTime = 0;
                    gs_DebugRunTime.u32FirstRunTimeTemp = gu32_Sys1ms;
                    gs_DebugRunTime.u32HadPrintedMin = false;
                    gs_DebugRunTime.u32PredictSp2StopTime = 0;
                #ifdef DEBUG_WT_SEND
                    gu8_DebugState2 = T1START;
                #endif
                    PredictSp3_Init();
                    gu32_DebugSumNum = 1;
                    StatisticClrStruct();
                    StatisticSaveStartTime(gu32_Sys10ms);
                    Adapt_InitDataFirstRun(&gs_Adapt);   //����Ӧ��������
                }
                else
                {
                    ErrorDeal(6, 100);     //��ʾ����6
                    gb_AlarmFlg = true;
                    gb_GoFlg = false;
                }
            }
        }
        else                        //ֹͣ����
        {
            if (gb_RunFlg)
            {
                gb_DiscShakeFlg = false;     //ж��������
                gb_DispNetFlg = false;
                gb_RunFlg = false;
                fb_RunStop = true;
                gb_FirstPrintFlg_UART0 = false;
                gb_FirstPrintFlg_UART1 = false;
                UpdateFastSetRec();
                if (gb_EndFlg == false)     //��������ֹͣ���ܳ�ʼ���д�״̬����������һ�Ӳ��ɴ�
                    JSD_Init();
            }
            gu32_SystemState = STOPSTATE;
            gb_GoFlg = false;
            //ֹͣ����ʱ����ֹͣ����
            if((gs_Rec.PrintCodeSwitch != 0)&&(gs_Rec.PrintCodeTime != 0))
                gb_StopPrintCodeFlg = true;
            gu32_DebugSumNum = 0;
            PrintStart(PRINT_STATISTIC, 0, 0);
        }
    }
    
    if (fb_RunStop)
    {
        gb_EndFlg = false;              //��������
        gb_DiscFlg = false;           //��ж���ź�
        gb_CompFlg = false;           //�嶨ֵ�ź�
        gb_Sp1Flg = false;          //���Ͷ�ź�
        gb_Sp2Flg = false;         //����Ͷ�ź�
        gb_Sp3Flg = false;          //��СͶ�ź�
        gb_ZeroKeyFlg = false;        //�����־λ
        gb_SumFlg = false;
        
        gb_FlapWaitFlg = false;         //�Ĵ���ʱ������
        gb_FlapStartFlg = false;        //�Ĵ��Ѿ�����
        gb_FlapBagOutFlg = false;       //�Ĵ�����ź�
        gb_FlapAllHighFlg = false;
        gb_OflDelayFlg = false;
        gu32_DiscShakeCnt = 0;
        gb_DiscShakeStartFlg = false;
        gb_DiscShakeFlg = false;
        gu32_SumTemp = 0;
        gb_No2PackOffAnother = false;
        //����޶�˫�ӻ������
        gb_AddingOutFlg = false;
        gb_No2AddAgainDelay = false;
        
        gu32_AutoClrZeroCnt = gs_Setup.AutoClrZeroInterval;         //��ʼ��������������
        gu32_CorrectFallTimeCnt = gs_Rec.CorrectFallTime;         //��ʼ���������������
        gu32_CorrectFallWt = 0;                //��ʼ����������ۼ�ֵ
        if (gb_PackFlg == false)            //�ɴ�״̬�����ɴ���ʱ״̬���������̼д�
        {
            gb_JSDDelayFlg = false;
            gb_SDDelayFlg = false;
        }
        gb_FirstStartFlg = true;
        gb_AddFlapBagFlg = false;                //�������Ĵ���־λ
        gb_ExtFlapBagFlg = false;                //�����Ĵ������־λ
        gb_TimeRunFlg = false;
        StabOver(true);
        Clr_Alarm();
    }
}

/*********************************************************************
��������: void PackInput(void)
��    ��: ���ɴ�����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-3-19
��    ��:                      ʱ    ��: 
*********************************************************************/
void PackInput(void)
{
    if ((gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gb_DiscEnableInFlg == false)
        //˫�ӻ�������ʱ���ж������������Ч��ô��������Ӧ�д�
        return;
    if (gb_JSDDelayFlg)         //���ɴ���ʱ״̬������Ӧ���ɴ�����
        return;
    if (gb_SDDelayFlg && gb_PackFlg)        //�Ѿ��ȶ��д�
    {
        if ((gb_RunFlg && (gs_Setup.TareMode == BINNO || gs_Setup.TareMode == NO2_A || gs_Setup.TareMode == NO2_B) && gu32_Process > T1PROCESS) ||    //v1.01
           (gb_RunFlg && (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gu32_Process >= T4PROCESS) ||
           (gb_RunFlg && (gs_Setup.TareMode == BINYES) && gs_Rec.CombinedNum > 1 && gs_Rec.CombinedNum != gu32_WeighTimeCnt) )
            //�޶��������Ϻ���Ӧ�ɴ�������ǰ������ C
            //�ж��ڶ�ֵ����ʱ������֮ǰ�������ɴ�
            //������ϴ�������1�����Ѿ�ж���ϣ��������ɴ�
            gb_JSDDelayFlg = false;
        else
        {
            gb_PackFlg = false;     //����д��ź�
            gb_JSDDelayFlg = true;             //���ɴ���ʱ������־��λ
            gb_SDDelayFlg = true;              //�ɴ���ʱ������־��λ
            gb_SDBDelayFlg = false;             //����ɴ�ǰ��ʱ������־
            gu32_JSDTime = gu32_Sys10ms;      //��ȡ��ǰʱ��������ʱ�ɴ�����ʱ
        }
    }
    else if (gb_PackFlg == false)       //��ǰδ�д�������д��������д���ʱ
    {
        gb_PackFlg = true;             //����д�
        gb_JSDDelayFlg = true;         //���ɴ���ʱ������־��λ
        gb_SDDelayFlg = false;          //����ɴ���ʱ������־
        gb_SDBDelayFlg = false;         //����ɴ�ǰ��ʱ������־
        gu32_JSDTime = gu32_Sys10ms;  //��ȡ��ǰʱ������ʱ�д�����ʱ
    }
    else            //�Ѽд���δ�ȶ��д���������
        gb_JSDDelayFlg = true;
}

/*********************************************************************
��������: void Pack_JD(void)
��    ��: �д�����
˵    ��: PROFIBUSͨѶ��ʹ�õ�
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-5-6
��    ��:                      ʱ    ��: 
*********************************************************************/
void Pack_JD(void)
{
    if ((gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gb_DiscEnableInFlg == false)
        //˫�ӻ�������ʱ���ж������������Ч��ô��������Ӧ�д�
        return;
    if (gb_JSDDelayFlg)         //���ɴ���ʱ״̬������Ӧ���ɴ�����
        return;if (gb_PackFlg == false)       //��ǰδ�д�������д��������д���ʱ
    {
        gb_PackFlg = true;             //����д�
        gb_JSDDelayFlg = true;         //���ɴ���ʱ������־��λ
        gb_SDDelayFlg = false;          //����ɴ���ʱ������־
        gb_SDBDelayFlg = false;         //����ɴ�ǰ��ʱ������־
        gu32_JSDTime = gu32_Sys10ms;  //��ȡ��ǰʱ������ʱ�д�����ʱ
    }
}

/*********************************************************************
��������: void Pack_SD(void)
��    ��: �ɴ�����
˵    ��: PROFIBUSͨѶ��ʹ�õ�
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-5-6
��    ��:                      ʱ    ��: 
*********************************************************************/
void Pack_SD(void)
{
    if ((gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gb_DiscEnableInFlg == false)
        //˫�ӻ�������ʱ���ж������������Ч��ô��������Ӧ�д�
        return;
    if (gb_JSDDelayFlg)         //���ɴ���ʱ״̬������Ӧ���ɴ�����
        return;
    if (gb_SDDelayFlg && gb_PackFlg)        //�Ѿ��ȶ��д�
    {
        if ((gb_RunFlg && (gs_Setup.TareMode == BINNO || gs_Setup.TareMode == NO2_A || gs_Setup.TareMode == NO2_B)) ||
           (gb_RunFlg && (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gu32_Process >= T4PROCESS) ||
           (gb_RunFlg && (gs_Setup.TareMode == BINYES) && gs_Rec.CombinedNum > 1 && gs_Rec.CombinedNum != gu32_WeighTimeCnt) )
            //�޶�����ʱ����Ӧ�ɴ�
            //�ж��ڶ�ֵ����ʱ������֮ǰ�������ɴ�
            //������ϴ�������1�����Ѿ�ж���ϣ��������ɴ�
            gb_JSDDelayFlg = false;
        else
        {
            gb_PackFlg = false;     //����д��ź�
            gb_JSDDelayFlg = true;             //���ɴ���ʱ������־��λ
            gb_SDDelayFlg = true;              //�ɴ���ʱ������־��λ
            gb_SDBDelayFlg = false;             //����ɴ�ǰ��ʱ������־
            gu32_JSDTime = gu32_Sys10ms;      //��ȡ��ǰʱ��������ʱ�ɴ�����ʱ
        }
    }
}


/*********************************************************************
��������: u32 NextRecNum(u32 fu32_Num)
��    ��: ������һ��Ŀ��ֵ��Ϊ����䷽
˵    ��: ������ѡ�䷽����Ӧ
��ڲ���: 
�� �� ֵ: �䷽��
��    ��: �Ժ���               ʱ    ��: 2014-1-23
��    ��:                      ʱ    ��: 
*********************************************************************/
u32 NextRecNum(u32 fu32_Num)
{
    u8 i;
    u8 lu8_Num;
    
    for (i = fu32_Num, lu8_Num = fu32_Num; i < fu32_Num + 20; i++)
    {
        if (++lu8_Num > 20)            //��20���䷽
            lu8_Num = 1;
        if (FRAM_ReadDW(FMAddr_Target(lu8_Num)) != 0)
        {
            return lu8_Num;
        }
    }
    return fu32_Num;    //�����䷽Ŀ��ֵȫΪ0
}


/*********************************************************************
��������: void ManualDisc(u8 fu8_State)
��    ��: �ֶ�ж�ϴ���
˵    ��: 
��ڲ���: fu8_State: 0��Ч 1��Ч ����ֵ��ȡ��
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-08-19
��    ��:                      ʱ    ��: 
*********************************************************************/
void ManualDisc(u8 fu8_State)
{
//    if (gs_Setup.DiscSumSwitch != 0) //�ֶ�ж���ۼƿ��ش�
//    {
//        if (fu8_State == 0)
//        {
//            if (gb_DiscFlg == true)   //��ʱ����ж������׼���ر�ж�ϱ�־λ
//            {
//                gb_DiscSumOffFlg = true;
//                gb_DiscSumOnFlg = false;
//            }
//        }
//        else if (fu8_State == 1)
//        {
//            if (gb_DiscFlg == false)
//            {
//                gb_DiscSumOnFlg = true;
//                gb_DiscSumOffFlg = false;
//            }
//        }
//        else
//        {
//            if (gb_DiscFlg == true)   //��ʱ����ж������׼���ر�ж�ϱ�־λ
//            {
//                gb_DiscSumOffFlg = true;
//                gb_DiscSumOnFlg = false;
//            }
//            else
//            {
//                gb_DiscSumOnFlg = true;
//                gb_DiscSumOffFlg = false;
//            }
//        }
//    }
//    else
    {   //0��1֮���ֵȡ��
        gb_DiscFlg = ((fu8_State != 0 && fu8_State != 1) ? (!gb_DiscFlg): fu8_State);
    }
}

/*********************************************************************
��������: void ManualSp3(u8 fu8_State)
��    ��: �ֶ�СͶ����
˵    ��: 
��ڲ���: fu8_State: 0��Ч 1��Ч ����ֵ��ȡ��
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-12-24
��    ��:                      ʱ    ��: 
*********************************************************************/
void ManualSp3(u8 fu8_State)
{
    gb_Sp1Flg = false;
    gb_Sp2Flg = false;
    //0��1֮���ֵȡ��
    gb_Sp3Flg = ((fu8_State != 0 && fu8_State != 1) ? (!gb_Sp3Flg): fu8_State);
}

/*********************************************************************
��������: void ManualSp123(u8 fu8_State)
��    ��: �ֶ���Ͷ����
˵    ��: 
��ڲ���: fu8_State: 0��Ч 1��Ч ����ֵ��ȡ��
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-12-24
��    ��:                      ʱ    ��: 
*********************************************************************/
void ManualSp123(u8 fu8_State)
{
    //0��1֮���ֵȡ��
    gb_Sp3Flg = ((fu8_State != 0 && fu8_State != 1) ? (!gb_Sp3Flg): fu8_State);
    gb_Sp1Flg = gb_Sp3Flg;
    gb_Sp2Flg = gb_Sp3Flg;
}

/*********************************************************************
��������: void IO_InDeal(u32 ful_In, bool fb_Mode)
��    ��: ���뿪��������
˵    ��: 
��ڲ���: gu32_In = �����Ӧ��������  fb_Mode = 1��Ч 0��Ч
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-6
��    ��:                      ʱ    ��: 
*********************************************************************/
void IO_InDeal(u32 ful_In, bool fb_Mode)
{
    if (gu16_MbIoTestSwitch == 0)       //���ڿ��������Կ��ش�ʱ����Ӧ����������
    {
        if (fb_Mode == true)           //��������Ч����
        {
            switch (ful_In)
            {
                case 1:             //����
                case 14:            //��ƽ����
                case 24:            //��ƽ����/��ͣ v1.01
                    if (gb_DisRunFlg == false)      //ֹͣ������Чʱ����������
                        RunStopInit(true);
                    break;
                case 2:             //��ͣ 
                    Clr_Alarm();
                    RunStopInit(false);
                    break;
                case 3:             //����
                    if (gb_RunFlg == false)
                        gb_ZeroKeyFlg = true;
                    break;
                case 4:             //�屨��
                    Clr_Alarm();
                    break;
                case 5:            //ѡ�䷽
                    if (gb_RunFlg == false)
                    {
                        //ѡ�䷽������Ч������Ŀ��ֵ��Ϊ0���䷽
                        gu32_RecNum = NextRecNum(gu32_RecNum);
                        FRAM_WriteDW(FMAddr_RecNum, gu32_RecNum);
                        Read_RecipeData(gu32_RecNum);
                    }
                    break;
                case 6:             //���ɴ�
                    PackInput();
                    break;
                case 7:             //�ֶ�ж��
                    if (gb_RunFlg == false)
                        ManualDisc(2);
                    break;
                case 8:             //�ֶ�СͶ
                    if (gb_RunFlg == false)
                        ManualSp3(2);
                    break;
                case 9:            //��ӡ���ۼ�
                    if (gb_RunFlg == false)
                        PrintStart(PRINT_TOTAL_REPORT, 0, 0);
                    break;
                case 11:        //����λ
                    gb_HighFlg = true;
                    break;
                case 12:        //����λ
                    gb_LowFlg = true;
                    break;
                case 13:        //�ֶ�����һ��
                    if (gb_DisRunFlg == false)      //ֹͣ������Чʱ����������
                    {
                        gb_GoFlg = true;
                        RunStopInit(true);
                    }
                    break;
                case 15:            //��ƽ�ֶ�СͶ
                    if (gb_RunFlg == false)
                        ManualSp3(1);
                    break;
                case 16:            //��ƽ�ֶ�ж��
                    if (gb_RunFlg == false)
                        ManualDisc(1);
                    break;
                case 17:            //ֹͣ
                    Clr_Alarm();
                    if (gb_RunFlg)
                        gb_EndFlg = true;
                    break;
                case 18:            //ж���Ź��ŵ�λ����
                    gb_DiscCloseOKFlg = true;
                    break;
                case 19:            //�д���λ����
                    gb_PackOKFlg = true;
                    break;
                case 20:            //�ֶ���Ͷ
                    if (gb_RunFlg == false)
                        ManualSp123(2);
                    break;
                case 21:            //��ƽ�ֶ�����
                    if (gb_RunFlg == false)
                        ManualSp123(1);
                    break;
                case 22:        //����λ
                    gb_MiddleFlg = true;
                    break;
                case 25:        //�궨��
                    gb_CalLockFlg = true;
                    break;
                default:
                    break;
            }
        }
        else            //��������Ч����
        {
            switch (ful_In)
            {
                case 11:        //����λ
                    gb_HighFlg = false;
                    break;
                case 12:        //����λ
                    gb_LowFlg = false;
                    break;
                case 14:            //��ƽ����
                    Clr_Alarm();
                    if (gb_RunFlg)
                        gb_EndFlg = true;
                    break;
                case 15:            //��ƽ�ֶ�СͶ
                    if (gb_RunFlg == false)
                        ManualSp3(0);
                    break;
                case 16:            //��ƽ�ֶ�ж��
                    if (gb_RunFlg == false)
                        ManualDisc(0);
                    break;
                case 18:            //ж���Ź��ŵ�λ����
                    gb_DiscCloseOKFlg = false;
                    break;
                case 19:            //�д���λ����
                    gb_PackOKFlg = false;
                    break;
                case 21:            //��ƽ�ֶ���Ͷ
                    if (gb_RunFlg == false)
                        ManualSp123(0);
                    break;
                case 22:            //����λ
                    gb_MiddleFlg = false;
                    break;
                case 24:            //��ƽ����/��ͣ v1.01
                    Clr_Alarm();
                    RunStopInit(false);
                    break;
                case 25:        //�궨��
                    gb_CalLockFlg = false;
                    break;
                default:
                    break;
            }
        }
    }
}

/*********************************************************************
��������: void DoubleLock(bool fb_State)
��    ��: ˫�ӻ������뿪�����Ĵ���
˵    ��: 
��ڲ���: fb_State true�ź���Ч���� false�ź���Ч����
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2015-02-04
��    ��:                      ʱ    ��: 
*********************************************************************/
void DoubleLock(bool fb_State)
{
    if (fb_State == true)
    {
        gb_DiscEnableInFlg = true;  //�ж�˫�ӻ���
        gb_AddingInFlg = true;      //�޶�˫�ӻ���
    }
    else
    {
        if (gs_Setup.TareMode == NO2_A || gs_Setup.TareMode == NO2_B)
        {   //�޶�˫�ӻ�������
            if (gb_AddingInFlg)
            {   //����ǻ�����������Ч��Ϊ��Ч����Ϊ����һ���Ѿ��ɴ�
                gb_No2PackOffAnother = true;
            }
            gb_AddingInFlg = false;     //�޶�˫�ӻ���
        }
        if (gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
        {
            gb_DiscEnableInFlg = false; //�ж�˫�ӻ���
            if (gb_DiscEnableOutFlg == false)
            {   /*���������Ϊ��Чʱ����������»�������϶�����Ч�ģ�ֻ��������СͶ�������
                �����ж�������ͬʱ���еģ�ͬʱ���˻��������Ч����ô�Ż�����������ͬʱ��Ϊ
                ��Ч�����*/
                if (gs_Setup.TareMode == BIN2_B && gb_RunFlg)
                {/*�����BIN2-B��ʱӦ����BIN2-A��ж�� ������д�״̬*/
                    gb_DiscEnableOutFlg = true;
                    gb_PackFlg = false;
                    gb_JSDDelayFlg = false;                 //������ɴ���ʱ��־
                    gb_SDDelayFlg = false;
                    gb_SDBDelayFlg = false;
                }
            }
            else
            {/*��������»��������Ϊ��Чʱ����������϶�����Ч�ģ���Ϊ�Ŵ�ʱ����һ��
                ��ж�ϣ����Ա���Ҫ������д�״̬������һ�ӿ����ɴ�*/
                if ((gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gb_RunFlg)
                {   //˫�ӻ��� ����ʱ���ж������������Ч�Ļ�����д���ر���״̬
                    gb_PackFlg = false;
                    gb_JSDDelayFlg = false;                 //������ɴ���ʱ��־
                    gb_SDDelayFlg = false;
                    gb_SDBDelayFlg = false;
                }
            }
        }
    }
}

/*********************************************************************
��������: void IO_InScan(void)
��    ��: ���뿪����ɨ��
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-6
��    ��:                      ʱ    ��: 
*********************************************************************/
void IO_InScan(void)
{   /*ADת��120��/��ʱ��ȥ��������4�Σ����1/30��
      ת�������޸ĺ�����Ӧת��*/
    #define DEWOBNUM    (cu8_MultiAd[gs_Setup.AdSamplingRate] * 4)   //�����ź�ȥ��������
    static u8 su8_InActCnt[9]= {0,0,0,0,0,0,0,0,0};     //������Ч������
    static u8 su8_InNoCnt[9] = {0,0,0,0,0,0,0,0,0};     //������Ч������
    static u8 su8_OldIoState[9] = {0,0,0,0,0,0,0,0,0};           //�ϴο����������״̬ su8_OldIoState[1~12]

    u8 i;
    u16 j = 0x01;
    
    gb_HighDefineFlg = false;
    gb_LowDefineFlg = false;
    gb_MiddleDefineFlg = false;
    gb_EnPackOKFlg = false;
    gb_EnDiscCloseOKFlg = false;
    gb_CalLockDefFlg = false;
//    
//    //��ƽ���ź����룬ע����ͬ��˵�����еĵ�ƽ���ź�˵�����˴���������
//    //��Чʱÿ�ζ�Ҫִ�еĴ��������Ƿ�����ĳЩ���ܡ�˵���������У���ƽ�����ź�ֻ�����ź�
//    //��Ч����Ч״̬�����ǲ�ִ��һ�Σ���IO_InDeal()�����С�
    for (i = 1; i <= 8; i++)
    {
        switch (*gu32p_IoInBuf[i])
        {
            case 2:     //��ͣ
                if (IO_Inport(i) == true)
                    gb_DisRunFlg = true;               //ֹͣ������Чʱ����ֹ��������
                else 
                    gb_DisRunFlg = false;
                break;
            case 10:    //������
                if (IO_Inport(i) == true)
                    gb_KeyLockFlg = true;
                else
                    gb_KeyLockFlg = false;
                break;
            case 11:    //����λ�Ѷ���
                gb_HighDefineFlg = true;           //����λ�Ѿ�����
                break;
            case 12:    //����λ�Ѷ���
                gb_LowDefineFlg = true;            //����λ�Ѿ�����
                break;
            case 18:    //ж���Źرյ�λ�Ѷ���
                gb_EnDiscCloseOKFlg = true;
                break;
            case 19:    //�д���λ�Ѷ���
                gb_EnPackOKFlg = true;
                break;
            case 22:    //����λ�Ѷ���
                gb_MiddleDefineFlg = true;            //����λ�Ѿ�����
                break;
            case 23:    //˫�ӻ������� ����ж��
                DoubleLock(IO_Inport(i));
                break;
            case 25:    //�궨���Ѷ���
                gb_CalLockDefFlg = true;
                break;
            default:
                break;
        }
    }
    
    //������ȥ������
    for (i = 1; i <= 8; i++)
    {
        if (IO_Inport(i) == true)                //��⵽������������Ч
        {
            gu16_MbIoInState |= j;   //��ֵModbus���뿪�������Եı���
            su8_InNoCnt[i] = 0;                 //������������Ч�����������Ч������
            if (su8_OldIoState[i] == 0)         //ԭ�����ڿ�������Ч״̬
            {
                if (++su8_InActCnt[i] >= DEWOBNUM)      //������������Ч��������ȥ����������Ϊ�˴�������Ч
                {
                    su8_InActCnt[i] = 0;        //���������
                    su8_OldIoState[i] = 1;      //�ÿ�����������Ч
                    IO_InDeal(*gu32p_IoInBuf[i], true);     //��Ӧ����������Ч����
                }
            }
            else            //ԭ���ʹ���������Ч״̬��������
            {
                su8_InActCnt[i] = 0;             //���������
            }
        }
        else                //��⵽������������Ч
        {
            gu16_MbIoInState &= (~j);   //��ֵModbus���뿪�������Եı���
            su8_InActCnt[i] = 0;         //���������
            if (su8_OldIoState[i] == 1)         //ԭ������������Ч״̬
            {
                if (++su8_InNoCnt[i] >= DEWOBNUM)      //������������Ч��������ȥ����������Ϊ�˴�������Ч
                {
                    su8_InNoCnt[i] = 0;         //���������
                    su8_OldIoState[i] = 0;      //�ÿ�����������Ч
                    IO_InDeal(*gu32p_IoInBuf[i], false);     //��Ӧ����������Ч����
                }
            }
            else            //ԭ���ʹ���������Ч״̬
            {
                su8_InNoCnt[i] = 0;         //���������
            }
        }
        j <<= 1;
    }
    
    if (gb_HighDefineFlg && gb_LowDefineFlg && (!gb_MiddleDefineFlg))
    {   //ֻ����������λ
        if (gb_LowFlg == false && gb_HighFlg == false)          //������λ����Ч
        {
            gb_LackFlg = true;         //ȱ����Ч
            gb_FillFlg = true;         //������Ч
        }
        else if (gb_HighFlg)        //����λ��Ч��ȱ�������Ч ���������Ч
        {
            gb_LackFlg = false;
            gb_FillFlg = false;
        }
        else if (gb_LowFlg)         //����λ��Ч������λ��Ч����ȱ�������Ч
        {
            gb_LackFlg = false;
        }
    }
    else if (gb_HighDefineFlg && gb_LowDefineFlg && gb_MiddleDefineFlg)
    {   //��������λ������
        if (gb_MiddleFlg == false && gb_HighFlg == false)          //������λ����Ч
        {
            gb_LackFlg = true;         //ȱ����Ч
            gb_FillFlg = true;         //������Ч
        }
        else if (gb_HighFlg)        //����λ��Ч��ȱ�������Ч ���������Ч
        {
            gb_LackFlg = false;
            gb_FillFlg = false;
        }
        else if (gb_MiddleFlg)         //����λ��Ч������λ��Ч����ȱ�������Ч
        {
            gb_LackFlg = false;
        }
    }
    else if (gb_LowDefineFlg)
    {   //����������λ
        gb_FillFlg = false;
        if (gb_LowFlg == false)         //����λ��Ч��ȱ����Ч
            gb_LackFlg = true;
        else
            gb_LackFlg = false;
    }
    else
    {   //�������
        gb_FillFlg = false;
        gb_LackFlg = false;
    }
}

/*********************************************************************
��������: bool Sp_Disc_State(u8 fu8_Item)
��    ��: ���Ϻ�ж�Ͽ�����״̬�������
˵    ��: Ͷ�Ϸ�ʽ���д���λ��ж���Ź��ŵ�λ���߼�
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-20
��    ��:                      ʱ    ��: 
*********************************************************************/
bool Feed_SP(u8 fu8_Item)
{
    //Ͷ�Ϸ�ʽ���� ��� ����
    bool  lb_Sp1Flg_Temp = gb_Sp1Flg;
    bool  lb_Sp2Flg_Temp = gb_Sp2Flg;
    bool  lb_Sp3Flg_Temp = gb_Sp3Flg;
    
    if (gs_Setup.FeedMode == SIN)           //����Ͷ��ģʽ
    {
        lb_Sp1Flg_Temp = (gb_Sp1Flg && gb_Sp3Flg) == true ? true : false;
        lb_Sp2Flg_Temp = ((!gb_Sp1Flg) && gb_Sp2Flg && gb_Sp3Flg) == true ? true : false;
        lb_Sp3Flg_Temp = ((!gb_Sp1Flg) && (!gb_Sp2Flg) && gb_Sp3Flg) == true ? true : false;
    }
    
    switch (fu8_Item)
    {
        case SP1_STATE:
            return lb_Sp1Flg_Temp;
        case SP2_STATE:
            return lb_Sp2Flg_Temp;
        case SP3_STATE:
            return lb_Sp3Flg_Temp;
        default:
            return false;
    }
}

/*********************************************************************
��������: bool SmallDropOut(void)
��    ��: СͶ����������Ĵ���
˵    ��: �����㶯�������
��ڲ���: 
�� �� ֵ: 0��Ч 1��Ч
��    ��: �Ժ���               ʱ    ��: 2014-1-20
��    ��:                      ʱ    ��: 
*********************************************************************/
bool SmallDropOut(void)
{
    static bool lb_Small;
    //СͶ�㶯���ش򿪲��Ҳ������ú���
    if ((gs_Rec.SmallPluseSwitch) && (gs_Rec.SmallPluseHi != 0) && (gs_Rec.SmallPluseLow != 0))
    {
        if (gb_Sp3Flg)
        {
            if (lb_Small == 0)        //�㶯��Ч
            {
                if (gu32_Sys10ms - gu32_SmallPluseTimeBuf >= gs_Rec.SmallPluseLow * 10)
                {
                    lb_Small = true;
                    gu32_SmallPluseTimeBuf = gu32_Sys10ms;
                }
            }
            else                        //�㶯��Ч
            {
                if (gu32_Sys10ms - gu32_SmallPluseTimeBuf >= gs_Rec.SmallPluseHi * 10)
                {
                    lb_Small = false;
                    gu32_SmallPluseTimeBuf = gu32_Sys10ms;
                }
            }
        }
        else
        {
            lb_Small = true;         //�˴�����0������lb_Small_A,��λlb_Small_A = 1��Ϊ�˽���㶯���ʱ�������Ч��ƽ��
            return false;
        }
    }
    else
        lb_Small = gb_Sp3Flg;
    
    return lb_Small;
}

/*********************************************************************
��������: bool Sp_Disc_State(u8 fu8_Item)
��    ��: ���Ϻ�ж�Ͽ�����״̬�������
˵    ��: Ͷ�Ϸ�ʽ���д���λ��ж���Ź��ŵ�λ���߼�
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-20
��    ��:                      ʱ    ��: 
*********************************************************************/
bool Sp_Disc_State(u8 fu8_Item)
{
    bool lb_State = false;
    
    //Ͷ�Ϸ�ʽ���� ��� ����
    bool  lb_Sp1Flg_Temp;
    bool  lb_Sp2Flg_Temp;
    bool  lb_Sp3Flg_Temp;
    
    lb_Sp1Flg_Temp = Feed_SP(SP1_STATE);
    lb_Sp2Flg_Temp = Feed_SP(SP2_STATE);
    lb_Sp3Flg_Temp = Feed_SP(SP3_STATE);
    
    switch (fu8_Item)
    {
        case SP1_STATE:
                //�ж�ģʽ������ж���Ź��ŵ�λ�źŵ��ǹ��Ų���λ�����ϣ�ֹͣ״̬���жϹ��ŵ�λ��
                if (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                    lb_State = (lb_Sp1Flg_Temp && (gb_DiscCloseOKFlg || (!gb_RunFlg) || (!gb_EnDiscCloseOKFlg))) == true ? true : false;
                else    //�޶������˼д���λ���Ǽд�û�е�λ�����ϣ�ֹͣģʽ�²��жϼд���λ��
                    lb_State = (lb_Sp1Flg_Temp && (gb_PackOKFlg || (!gb_RunFlg) || (!gb_EnPackOKFlg))) == true ? true : false;
                break;
        case SP2_STATE:
                //�ж�ģʽ������ж���Ź��ŵ�λ�źŵ��ǹ��Ų���λ�����ϣ�ֹͣ״̬���жϹ��ŵ�λ��
                if (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                    lb_State = (lb_Sp2Flg_Temp && (gb_DiscCloseOKFlg || (!gb_RunFlg) || (!gb_EnDiscCloseOKFlg))) == true ? true : false;
                else    //�޶������˼д���λ���Ǽд�û�е�λ�����ϣ�ֹͣģʽ�²��жϼд���λ��
                    lb_State = (lb_Sp2Flg_Temp && (gb_PackOKFlg || (!gb_RunFlg) || (!gb_EnPackOKFlg))) == true ? true : false;
                break;
        case SP3_STATE:
                //�ж�ģʽ������ж���Ź��ŵ�λ�źŵ��ǹ��Ų���λ�����ϣ�ֹͣ״̬���жϹ��ŵ�λ��
                if (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                    lb_State = (lb_Sp3Flg_Temp && SmallDropOut() && (gb_DiscCloseOKFlg || (!gb_RunFlg) || (!gb_EnDiscCloseOKFlg))) == true ? true : false;
                else    //�޶������˼д���λ���Ǽд�û�е�λ�����ϣ�ֹͣģʽ�²��жϼд���λ��
                    lb_State = (lb_Sp3Flg_Temp && SmallDropOut() && (gb_PackOKFlg || (!gb_RunFlg) || (!gb_EnPackOKFlg))) == true ? true : false;
                break;
        case DISC_STATE:
                //�ж������˼д���λ���Ǽд�����λ��ж�ϣ�ֹͣ״̬���жϼд���λ��
                if (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                    lb_State = (gb_DiscFlg && (gb_PackOKFlg || (!gb_RunFlg) || (!gb_EnPackOKFlg))) == true ? true : false;
                else
                    lb_State = gb_DiscFlg;
                break;
    }
    return lb_State;
}
