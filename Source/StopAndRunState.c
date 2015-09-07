/*
Description:            ֹͣ������״̬����ع��ܺ���
Author:                 �Ժ���
Date:                   2013-12-9
*/
#include "include.h"

bool gb_FastSetFlg;         //�������ñ�־λ
u32 gu32_FastSetTemp[6];    //���������䷽�������ݴ�
u8 gu8_FastSetSigTemp;      //���������޸Ĳ����ı�־
//gu8_FastSetSigTemp^0 = 1       F1.1���޸�
//gu8_FastSetSigTemp^1 = 1       F1.2���޸�
//gu8_FastSetSigTemp^2 = 1       F1.3���޸�
//gu8_FastSetSigTemp^3 = 1       F1.4���޸�
//gu8_FastSetSigTemp^4 = 1       F1.5���޸�
//gu8_FastSetSigTemp^5 = 1       F1.6���޸�
/*
����ʱ���п������ã�
1.T1����֮ǰ�����޸ĵĻ����ϸ��¡�
2.F1.5����ֵ�޸����ϸ���
3.����ֵ����һ�μ������̿�ʼ֮ǰ����
4.��ֹͣ�źź��������û�и��µ�ֵ�����ϸ���
*/
bool gb_FastCalFlg;         //���ٱ궨��־λ




/*********************************************************************
��������: void Key_FastSetState(void)
��    ��: ��������״̬��������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-17
��    ��:                      ʱ    ��: 
*********************************************************************/
void Key_FastSetState(void)
{
    u8 i = 0;
    
    if (gu32_KeyCode == K_RIGHT)
    {
        if (++gu8_Item > REC_F1_6)
            gu8_Item = REC_F1_1;
        gb_FirstNumKeyFlg = true;
        ulParameter.ul = gu32_FastSetTemp[ gu8_Item - 3 ];        //��ȡ��Ӧ��Ŀ�Ĳ���ֵ
    }
    
    //��������
    ulParameter.ul = Key_NumInput(ulParameter.ul, 6);
    
    //ÿһ���µİ�����������
    switch (gu32_KeyCode)
    {
        case K_ESC:             //�˳�������
            gb_FlashFlg = false;
            gb_SetFlg = false;
            gb_FirstNumKeyFlg = true;
            gu8_DataInLength = 0;
            gb_FastSetFlg = false;
            
            if (gu8_FastSetSigTemp != 0)
            {
                if (gb_RunFlg == false)     //��escʱ�Ǳ��Ѿ�����ֹͣ״̬��������δ���µ��䷽��������������
                {
                    for (i = 0; i <= 5; i++)
                    {
                        if (gu8_FastSetSigTemp & (0x01 << i))
                        {
                            ulParameter.ul = gu32_FastSetTemp[i];
                            FRAM_WriteDW(GetRecipePort(i + 3), ulParameter.ul);
                        }
                        gu8_FastSetSigTemp = 0;
                    }
                }
            }
            break;
        case K_ENTER:           //ȷ�ϼ�����
            gb_FirstNumKeyFlg = true;
            gu8_DataInLength = 0;
            if (RecDataInputCheck() || (gu8_Item == REC_F1_1 && ulParameter.ul == 0))            //�������ݷ�Χ���
            {
                ErrorDeal(0, 100);
                ulParameter.ul =  gu32_FastSetTemp[gu8_Item - 3];
                return;
            }
            
            if (gb_RunFlg == false)         //ֹͣ״̬�����̸����䷽
            {
                gu32_FastSetTemp[gu8_Item - 3] = ulParameter.ul;
                FRAM_WriteDW(GetRecipePort(gu8_Item), ulParameter.ul);
            }
            else                //����״̬��
            {
                if (gu32_Process <= T1PROCESS)
                {   //T1��ʱ״̬ʱ���̸����䷽�������޶�δ�д�״̬��
                    gu32_FastSetTemp[gu8_Item - 3] = ulParameter.ul;
                    FRAM_WriteDW(GetRecipePort(gu8_Item), ulParameter.ul);
                }
                else if (gu8_Item == REC_F1_5)       
                {   //����ʱ�޸�����ֵʵʱ���棬����ֵ��һ������ʱ����
                    gu32_FastSetTemp[4] = ulParameter.ul;
                    FRAM_WriteDW(GetRecipePort(REC_F1_5), ulParameter.ul);
                }
                else
                {
                    //����������ݸı�������Ӧ����ݸı��־λ
                    if (ulParameter.ul != gu32_FastSetTemp[gu8_Item-3])
                    {
                        //������Ĳ����ȴ�����������ݴ�������   ע��REC_F1_1 = 3
                        gu8_FastSetSigTemp |= (0x01 << (gu8_Item - 3));
                        gu32_FastSetTemp[gu8_Item-3] = ulParameter.ul;
                    }
                }
            }
            if (++gu8_Item > REC_F1_6)
                gu8_Item = REC_F1_1;
            ulParameter.ul = gu32_FastSetTemp[ gu8_Item - 3 ];           //�õ���Ӧ������ֵ
            break;
        default:
            break;
    }
}

/*********************************************************************
��������: void Key_StopState(void)
��    ��: ֹͣʱ��������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-12
��    ��:                      ʱ    ��: 
*********************************************************************/
void Key_StopState(void)
{
    u8 i;
    //��ֹ���������Ƿ��Ʋ�������
    if(gb_OUOverFlg)
    {
        if(gu32_Sys10ms - gu32_OUDelayTimeBuf >= 200)
            gb_OUOverFlg = false;
    }
    if(gb_OUUnderFlg)
    {
        if(gu32_Sys10ms - gu32_OUDelayTimeBuf >= 200)
            gb_OUUnderFlg = false;
    }
    if (gb_FastSetFlg)                  //���������䷽״̬
    {
        Key_FastSetState();             //�������ð�������
    }
    else        //ֹͣ״̬�°�������
    {
        if (gb_AlarmFlg)     //����״̬��ֻ�ܰ�ESC ENTER ZERO
        {
            if ((gu32_KeyCode != K_ZERO) && (gu32_KeyCode != K_ESC) && (gu32_KeyCode != K_ENTER) && (gu32_KeyCode != K_NONE))
                return;
        }
        
        switch (gu32_KeyCode)
        {
            case K_0:           //�������Զ���
                gu8_Item = 0;
                gu32_SystemState = IODEFINESTATE;
                gu32_KeyCode = 0;
                if (gu32_IoDefCodeSwitch == 0)       //���������Կ��عر���ֱ�ӽ������
                {
                    gu8_Item = IODEF_IN1;
                    ulParameter.ul = *gu32p_IoInBuf[1];
                }
                else
                    gu8_Item = IODEF_CHECKCODE;
                Key_IoDefState();
                break;
            case K_1:           //���빤����������
                gu8_Item = 0;
                gu32_SystemState = SETUPSTATE;
                gu32_KeyCode = 0;
                if (gu32_SetupCodeSwitch == 0)       //�����������뿪�عر���ֱ�ӽ���F1
                {
                    gu8_Item = 1;
                    gu32_TimeDelay = gu32_Sys10ms;
                }
                Key_SetupState();
                break;
            case K_2:           //����궨
                if (gb_CalLockDefFlg && gb_CalLockFlg == false)
                {   //�궨���ж��嵫��������Ч�����ܱ궨
                    break;
                }
                gu8_Item = 0;
                gb_FastCalFlg = false;   //�����궨����
                gu32_SystemState = CALIBSTATE;
                gu32_KeyCode = 0;
                Key_CalibState();
                break;
            case K_3:           //��������������
                gu8_Item = 0;
                gu32_SystemState = BATCHSTATE;
                ulParameter.ul = gu32_BatchTime;
                gu32_KeyCode = 0;
                Key_BatchState();
                break;
            case K_4:           //ʱ������
                gu8_Item = 0;
                gu32_SystemState = TIMESTATE;
                gu32_KeyCode = 0;
                Key_DateTimeState();
                break;
            case K_5:           //��������
                gu8_Item = 0;
                gu32_SystemState = DATESTATE;
                gu32_KeyCode = 0;
                Key_DateTimeState();
                break;
            case K_6:           //�����ۼƲ�ѯ
                gu8_Item = 0;
                gu32_SystemState = SUMSTATE;
                gu32_KeyCode = 0;
                if(gs_Setup.SumCheckCodeSwitch != 0)   //�Զ������뿪�ش�
                {
                    gu8_Item = 0;
                }
                else
                {
                    ulParameter.ul = gu32_SumWt;
                    gu8_Item = 1;
                    gb_SumFlg = true;      //sumָʾ����
                }
                Key_SumState();
                break;
            case K_7:           //��ӡ
                gu8_Item = 0;
                if (gs_Setup.ComMode_1 == COM_PRINT || gs_Setup.ComMode_2 == COM_PRINT)
                {//������Ϊ��ӡ���ܲ��ܽ����ӡ����
                    gu32_SystemState = PRINTSTATE;
                    gu32_KeyCode = 0;
                    ulParameter.ul = gu32_RecNum;
                    gb_PrintAllFlg = false;
                    gu8_Item = 1;
                    gb_FirstPrintFlg_UART0 = true;
                    gb_PrintAllRecFlg_UART0 = false;
                    gb_FirstPrintFlg_UART1 = true;
                    gb_PrintAllRecFlg_UART1 = false;
                    Key_PrintState();
                }
                else
                    ErrorDeal(10, 100);
                break;
            case K_8:           //����������
                gu8_Item = 0;
                gu32_SystemState = IOTESTSTATE;
                gu32_KeyCode = 0;
                IO_CloseOut();      //�ر����п��������
                if (gu32_IoTestCodeSwitch == 0)       //���������Կ��عر���ֱ�ӽ������
                    gu8_Item = IOTEST;
                else
                    gu8_Item = IOTEST_CHECKCODE;
                Key_IoTestState();
                break;
             case K_9:          //�䷽����
                gu8_Item = 0;
                gu32_SystemState = RECIPESTATE;
                gu32_KeyCode = 0;
                ulParameter.ul = gu32_RecNum;
                gb_FirstNumKeyFlg = true;
                Key_RecipeState();
                break;
            case K_ZERO:       //����
                if (gb_AlarmFlg == true)             //�б���ʱ�ü�����
                    break;
                gb_ZeroKeyFlg = true;
                break;
            case K_ZERO_2S:     //��������궨���  v1.01
                //�ȶ�����AD����������������
                if (AdToMv(gu32_AdFedValue) <= 12000 * gs_Cal.Sensor && 
                    gb_AdOflFlg == false && gb_MvStabFlg == true)
                {
                    gs_Cal.Zero = gu32_AdFedValue;
                    FRAM_WriteDW(FMAddr_CalZero, gs_Cal.Zero);
                    gu32_FloatZero = 0;
                    gb_SigFZeroFlg = false;
                }
                else    //������궨��������
                    ErrorDeal(0, 100);
                break;
            case K_RIGHT_2S:       //������ٱ궨��������
                if (gb_CalLockDefFlg && gb_CalLockFlg == false)
                {   //�궨���ж��嵫��������Ч�����ܱ궨
                    break;
                }
                gu8_Item = 0;
                gb_FastCalFlg = true;
                gu32_SystemState = CALIBSTATE;
                gu32_KeyCode = 0;
                Key_CalibState();
                break;
            case K_SET_2S:     //
                gu8_Item = 0;
                gu32_SystemState = DEBUGSTATE;
                gu32_KeyCode = 0;
                Key_DebugState();
                break;
            case K_ENTER:
                gu8_Item = 0;
                gb_FastSetFlg = true;
                gu32_KeyCode = 0;
                gu8_Item = REC_F1_1;       //������һ��Ϊ�Զ���ΪON�Ĳ���
                gu8_FastSetSigTemp = 0;
                for (i = 0; i <= 5; i++)        //��F1.x���뵽���������ݴ�
                    gu32_FastSetTemp[i] = GetRecipeItemValue(REC_F1_1 + i);
                ulParameter.ul = gu32_FastSetTemp[gu8_Item-3];
                break;
            case K_ESC:
                Clr_Alarm();                    //�屨��
                break;
            default:
                ulParameter.ul = 0xFFFFFFFF;
                gu8_DataInLength = 0;
                gb_SetFlg = false;
                gb_FirstNumKeyFlg = true;
                gb_FlashFlg = false;
                break;
        #ifdef DEBUG_RUN_STOP_BY_KEY
            case K_INC:     //��������
                RunStopInit(true);
                break;
        #endif
        }
    }
}


/*********************************************************************
��������: void Disp_StopRunState(void)
��    ��: ֹͣ������״̬����ʾ����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-12
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_StopRunState(void)
{
    static u32 su32_DataTemp;
    u16 lu16_RealRecItem; 
    static u32 su32_TimeTemp = 0;
    
    if (gb_SumFlg && gb_RunFlg) //����״̬�µ��ۼ���ʾ
    {
        Disp_SumState();
    }
    else if (gb_FastSetFlg) //����������ʾ
    {
        lu16_RealRecItem = gu16_RecRealItem[gu8_Item];
        gu8_AuxDispArray[0] = SEG_F;
        gu8_AuxDispArray[1] = Value_To_SEG[lu16_RealRecItem/0x10] | 0x80;
        gu8_AuxDispArray[2] = Value_To_SEG[lu16_RealRecItem%0x10];
        gb_FlashFlg = true;
        
        Disp_Main_Data(ulParameter.ul, gs_Cal.Point,  6, false, false);       //��ʾֵ
        VFD_UnitDisp(gs_Cal.Unit);                               //��λ��ʾ
        Flash_MainDisp(0x01);            //��˸����
        //�д����ʱ����������˼д���λ���Ǽд���λ��Ч��PACK��˸
        if (gb_EnPackOKFlg && (!gb_PackOKFlg))
            VFD_LEDDisp(!gb_DispNetFlg, gb_DispNetFlg, false, Flash_Flg(gb_PackFlg));  //LED����ʾ
        else
            VFD_LEDDisp(!gb_DispNetFlg, gb_DispNetFlg, false, gb_PackFlg);  //LED����ʾ
        Disp_FlgLight();        //��־����ʾ
    }
    else        //��������ʾ
    {
        if (gb_AdOKFlg)     //AD����
        {   //���� С���� ��ʾλ�� ���� OFL
//            if ((gs_Setup.TareMode == BIN YES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gs_Setup.ResultHoldSwitch != 0 && gb_DiscWtGetedFlg == true && gb_RunFlg == true)
//                su32_DataTemp = gu32_HoldWt;
//	        else
//	        {
                if (gu32_Sys10ms - su32_TimeTemp >= 3)        //30msˢ��һ��������ʾ v1.01
                {
//	                su32_DataTemp = gu32_Wt;
	                su32_DataTemp = DISP_WT_KALMAN;
                    su32_TimeTemp = gu32_Sys10ms;
                }
//	        }
            Disp_Main_Data(su32_DataTemp, gs_Cal.Point, 6, true, gb_OflFlg);
        #ifdef DEBUG_ADCNVT_TIMES
            //���� ����ʾADת������/��
            VFD_AuxDisp_u32(gu32_AdConventTimes);
        #else   //��������ʾ
            if (gs_Setup.AuxDispType == AUX_SUM_R)      //����ʾ��ǰ�䷽�ۼƴ���
            {
                VFD_AuxDisp_u32(gu32_SumNum_Rec[gu32_RecNum] % 1000);
                if (gu32_SumNum_Rec[gu32_RecNum] < 1000)    //�ۼƴ���С��3λ����0
                    Disp_Echo0(0, gu8_AuxDispArray, 3);
            }
            else if (gs_Setup.AuxDispType == AUX_SUM)   //����ʾ���ۼƴ���
            {
                VFD_AuxDisp_u32(gu32_SumNum % 1000);
                if (gu32_SumNum < 1000) //�ۼƴ���С��3λ����0
                    Disp_Echo0(0, gu8_AuxDispArray, 3);
            }
            else    //����ʾ�䷽
                Disp_Aux_Rec(gu32_RecNum);
        #endif
        }
        else
            VFD_MainDisp_Str("AD ERR");    //��ʾAd Err
        
        VFD_UnitDisp(gs_Cal.Unit);                               //��λ��ʾ
        VFD_MainSigDisp(gb_SigWtFlg);
        //�д����ʱ����������˼д���λ���Ǽд���λ��Ч��PACK��˸
        if (gb_EnPackOKFlg && (!gb_PackOKFlg))
            VFD_LEDDisp(!gb_DispNetFlg, gb_DispNetFlg, false, Flash_Flg(gb_PackFlg));  //LED����ʾ
        else
            VFD_LEDDisp(!gb_DispNetFlg, gb_DispNetFlg, false, gb_PackFlg);  //LED����ʾ
        Disp_FlgLight();        //��־����ʾ
    }
}
