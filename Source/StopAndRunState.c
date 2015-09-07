/*
Description:            停止和运行状态下相关功能函数
Author:                 丛海旭
Date:                   2013-12-9
*/
#include "include.h"

bool gb_FastSetFlg;         //快速设置标志位
u32 gu32_FastSetTemp[6];    //快速设置配方参数的暂存
u8 gu8_FastSetSigTemp;      //快速设置修改参数的标志
//gu8_FastSetSigTemp^0 = 1       F1.1已修改
//gu8_FastSetSigTemp^1 = 1       F1.2已修改
//gu8_FastSetSigTemp^2 = 1       F1.3已修改
//gu8_FastSetSigTemp^3 = 1       F1.4已修改
//gu8_FastSetSigTemp^4 = 1       F1.5已修改
//gu8_FastSetSigTemp^5 = 1       F1.6已修改
/*
运行时进行快速设置：
1.T1结束之前进行修改的话马上更新。
2.F1.5近零值修改马上更新
3.其他值在下一次加料流程开始之前更新
4.给停止信号后，如果存在没有更新的值则马上更新
*/
bool gb_FastCalFlg;         //快速标定标志位




/*********************************************************************
函数名称: void Key_FastSetState(void)
功    能: 快速设置状态按键处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-17
修    改:                      时    间: 
*********************************************************************/
void Key_FastSetState(void)
{
    u8 i = 0;
    
    if (gu32_KeyCode == K_RIGHT)
    {
        if (++gu8_Item > REC_F1_6)
            gu8_Item = REC_F1_1;
        gb_FirstNumKeyFlg = true;
        ulParameter.ul = gu32_FastSetTemp[ gu8_Item - 3 ];        //获取对应项目的参数值
    }
    
    //数据输入
    ulParameter.ul = Key_NumInput(ulParameter.ul, 6);
    
    //每一项下的按键处理程序
    switch (gu32_KeyCode)
    {
        case K_ESC:             //退出键处理
            gb_FlashFlg = false;
            gb_SetFlg = false;
            gb_FirstNumKeyFlg = true;
            gu8_DataInLength = 0;
            gb_FastSetFlg = false;
            
            if (gu8_FastSetSigTemp != 0)
            {
                if (gb_RunFlg == false)     //按esc时仪表已经处于停止状态，并且有未更新的配方数据则立即更新
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
        case K_ENTER:           //确认键处理
            gb_FirstNumKeyFlg = true;
            gu8_DataInLength = 0;
            if (RecDataInputCheck() || (gu8_Item == REC_F1_1 && ulParameter.ul == 0))            //输入数据范围检查
            {
                ErrorDeal(0, 100);
                ulParameter.ul =  gu32_FastSetTemp[gu8_Item - 3];
                return;
            }
            
            if (gb_RunFlg == false)         //停止状态下立刻更新配方
            {
                gu32_FastSetTemp[gu8_Item - 3] = ulParameter.ul;
                FRAM_WriteDW(GetRecipePort(gu8_Item), ulParameter.ul);
            }
            else                //运行状态下
            {
                if (gu32_Process <= T1PROCESS)
                {   //T1延时状态时立刻更新配方，比如无斗未夹袋状态下
                    gu32_FastSetTemp[gu8_Item - 3] = ulParameter.ul;
                    FRAM_WriteDW(GetRecipePort(gu8_Item), ulParameter.ul);
                }
                else if (gu8_Item == REC_F1_5)       
                {   //运行时修改零区值实时保存，其他值下一秤启动时更新
                    gu32_FastSetTemp[4] = ulParameter.ul;
                    FRAM_WriteDW(GetRecipePort(REC_F1_5), ulParameter.ul);
                }
                else
                {
                    //如果输入数据改变则置相应的相据改变标志位
                    if (ulParameter.ul != gu32_FastSetTemp[gu8_Item-3])
                    {
                        //将输入的参数先存入快速设置暂存数组中   注：REC_F1_1 = 3
                        gu8_FastSetSigTemp |= (0x01 << (gu8_Item - 3));
                        gu32_FastSetTemp[gu8_Item-3] = ulParameter.ul;
                    }
                }
            }
            if (++gu8_Item > REC_F1_6)
                gu8_Item = REC_F1_1;
            ulParameter.ul = gu32_FastSetTemp[ gu8_Item - 3 ];           //得到对应参数的值
            break;
        default:
            break;
    }
}

/*********************************************************************
函数名称: void Key_StopState(void)
功    能: 停止时按键处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-12
修    改:                      时    间: 
*********************************************************************/
void Key_StopState(void)
{
    u8 i;
    //防止结束输入后超欠差灯不灭问题
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
    if (gb_FastSetFlg)                  //快速设置配方状态
    {
        Key_FastSetState();             //快速设置按键处理
    }
    else        //停止状态下按键处理
    {
        if (gb_AlarmFlg)     //报警状态下只能按ESC ENTER ZERO
        {
            if ((gu32_KeyCode != K_ZERO) && (gu32_KeyCode != K_ESC) && (gu32_KeyCode != K_ENTER) && (gu32_KeyCode != K_NONE))
                return;
        }
        
        switch (gu32_KeyCode)
        {
            case K_0:           //开关量自定义
                gu8_Item = 0;
                gu32_SystemState = IODEFINESTATE;
                gu32_KeyCode = 0;
                if (gu32_IoDefCodeSwitch == 0)       //开关量测试开关关闭则直接进入测试
                {
                    gu8_Item = IODEF_IN1;
                    ulParameter.ul = *gu32p_IoInBuf[1];
                }
                else
                    gu8_Item = IODEF_CHECKCODE;
                Key_IoDefState();
                break;
            case K_1:           //进入工作参数设置
                gu8_Item = 0;
                gu32_SystemState = SETUPSTATE;
                gu32_KeyCode = 0;
                if (gu32_SetupCodeSwitch == 0)       //工作参数密码开关关闭则直接进入F1
                {
                    gu8_Item = 1;
                    gu32_TimeDelay = gu32_Sys10ms;
                }
                Key_SetupState();
                break;
            case K_2:           //进入标定
                if (gb_CalLockDefFlg && gb_CalLockFlg == false)
                {   //标定锁有定义但是输入无效，不能标定
                    break;
                }
                gu8_Item = 0;
                gb_FastCalFlg = false;   //完整标定功能
                gu32_SystemState = CALIBSTATE;
                gu32_KeyCode = 0;
                Key_CalibState();
                break;
            case K_3:           //进入批次数设置
                gu8_Item = 0;
                gu32_SystemState = BATCHSTATE;
                ulParameter.ul = gu32_BatchTime;
                gu32_KeyCode = 0;
                Key_BatchState();
                break;
            case K_4:           //时间设置
                gu8_Item = 0;
                gu32_SystemState = TIMESTATE;
                gu32_KeyCode = 0;
                Key_DateTimeState();
                break;
            case K_5:           //日期设置
                gu8_Item = 0;
                gu32_SystemState = DATESTATE;
                gu32_KeyCode = 0;
                Key_DateTimeState();
                break;
            case K_6:           //进入累计查询
                gu8_Item = 0;
                gu32_SystemState = SUMSTATE;
                gu32_KeyCode = 0;
                if(gs_Setup.SumCheckCodeSwitch != 0)   //自定义密码开关打开
                {
                    gu8_Item = 0;
                }
                else
                {
                    ulParameter.ul = gu32_SumWt;
                    gu8_Item = 1;
                    gb_SumFlg = true;      //sum指示灯亮
                }
                Key_SumState();
                break;
            case K_7:           //打印
                gu8_Item = 0;
                if (gs_Setup.ComMode_1 == COM_PRINT || gs_Setup.ComMode_2 == COM_PRINT)
                {//有设置为打印功能才能进入打印界面
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
            case K_8:           //开关量测试
                gu8_Item = 0;
                gu32_SystemState = IOTESTSTATE;
                gu32_KeyCode = 0;
                IO_CloseOut();      //关闭所有开关量输出
                if (gu32_IoTestCodeSwitch == 0)       //开关量测试开关关闭则直接进入测试
                    gu8_Item = IOTEST;
                else
                    gu8_Item = IOTEST_CHECKCODE;
                Key_IoTestState();
                break;
             case K_9:          //配方设置
                gu8_Item = 0;
                gu32_SystemState = RECIPESTATE;
                gu32_KeyCode = 0;
                ulParameter.ul = gu32_RecNum;
                gb_FirstNumKeyFlg = true;
                Key_RecipeState();
                break;
            case K_ZERO:       //清零
                if (gb_AlarmFlg == true)             //有报警时该键无用
                    break;
                gb_ZeroKeyFlg = true;
                break;
            case K_ZERO_2S:     //长按两秒标定零点  v1.01
                //稳定并且AD不溢出才允许标零点
                if (AdToMv(gu32_AdFedValue) <= 12000 * gs_Cal.Sensor && 
                    gb_AdOflFlg == false && gb_MvStabFlg == true)
                {
                    gs_Cal.Zero = gu32_AdFedValue;
                    FRAM_WriteDW(FMAddr_CalZero, gs_Cal.Zero);
                    gu32_FloatZero = 0;
                    gb_SigFZeroFlg = false;
                }
                else    //不满足标定条件报错
                    ErrorDeal(0, 100);
                break;
            case K_RIGHT_2S:       //进入快速标定零点和增益
                if (gb_CalLockDefFlg && gb_CalLockFlg == false)
                {   //标定锁有定义但是输入无效，不能标定
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
                gu8_Item = REC_F1_1;       //进入后第一项为自定义为ON的参数
                gu8_FastSetSigTemp = 0;
                for (i = 0; i <= 5; i++)        //将F1.x读入到快速设置暂存
                    gu32_FastSetTemp[i] = GetRecipeItemValue(REC_F1_1 + i);
                ulParameter.ul = gu32_FastSetTemp[gu8_Item-3];
                break;
            case K_ESC:
                Clr_Alarm();                    //清报警
                break;
            default:
                ulParameter.ul = 0xFFFFFFFF;
                gu8_DataInLength = 0;
                gb_SetFlg = false;
                gb_FirstNumKeyFlg = true;
                gb_FlashFlg = false;
                break;
        #ifdef DEBUG_RUN_STOP_BY_KEY
            case K_INC:     //↑键启动
                RunStopInit(true);
                break;
        #endif
        }
    }
}


/*********************************************************************
函数名称: void Disp_StopRunState(void)
功    能: 停止和运行状态的显示处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-12
修    改:                      时    间: 
*********************************************************************/
void Disp_StopRunState(void)
{
    static u32 su32_DataTemp;
    u16 lu16_RealRecItem; 
    static u32 su32_TimeTemp = 0;
    
    if (gb_SumFlg && gb_RunFlg) //运行状态下的累计显示
    {
        Disp_SumState();
    }
    else if (gb_FastSetFlg) //快速设置显示
    {
        lu16_RealRecItem = gu16_RecRealItem[gu8_Item];
        gu8_AuxDispArray[0] = SEG_F;
        gu8_AuxDispArray[1] = Value_To_SEG[lu16_RealRecItem/0x10] | 0x80;
        gu8_AuxDispArray[2] = Value_To_SEG[lu16_RealRecItem%0x10];
        gb_FlashFlg = true;
        
        Disp_Main_Data(ulParameter.ul, gs_Cal.Point,  6, false, false);       //显示值
        VFD_UnitDisp(gs_Cal.Unit);                               //单位显示
        Flash_MainDisp(0x01);            //闪烁处理
        //夹袋输出时，如果定义了夹袋到位但是夹袋到位无效则PACK闪烁
        if (gb_EnPackOKFlg && (!gb_PackOKFlg))
            VFD_LEDDisp(!gb_DispNetFlg, gb_DispNetFlg, false, Flash_Flg(gb_PackFlg));  //LED灯显示
        else
            VFD_LEDDisp(!gb_DispNetFlg, gb_DispNetFlg, false, gb_PackFlg);  //LED灯显示
        Disp_FlgLight();        //标志灯显示
    }
    else        //重量等显示
    {
        if (gb_AdOKFlg)     //AD正常
        {   //数据 小数点 显示位数 消隐 OFL
//            if ((gs_Setup.TareMode == BIN YES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gs_Setup.ResultHoldSwitch != 0 && gb_DiscWtGetedFlg == true && gb_RunFlg == true)
//                su32_DataTemp = gu32_HoldWt;
//	        else
//	        {
                if (gu32_Sys10ms - su32_TimeTemp >= 3)        //30ms刷新一次重量显示 v1.01
                {
//	                su32_DataTemp = gu32_Wt;
	                su32_DataTemp = DISP_WT_KALMAN;
                    su32_TimeTemp = gu32_Sys10ms;
                }
//	        }
            Disp_Main_Data(su32_DataTemp, gs_Cal.Point, 6, true, gb_OflFlg);
        #ifdef DEBUG_ADCNVT_TIMES
            //调试 副显示AD转换次数/秒
            VFD_AuxDisp_u32(gu32_AdConventTimes);
        #else   //正常副显示
            if (gs_Setup.AuxDispType == AUX_SUM_R)      //副显示当前配方累计次数
            {
                VFD_AuxDisp_u32(gu32_SumNum_Rec[gu32_RecNum] % 1000);
                if (gu32_SumNum_Rec[gu32_RecNum] < 1000)    //累计次数小于3位消隐0
                    Disp_Echo0(0, gu8_AuxDispArray, 3);
            }
            else if (gs_Setup.AuxDispType == AUX_SUM)   //副显示总累计次数
            {
                VFD_AuxDisp_u32(gu32_SumNum % 1000);
                if (gu32_SumNum < 1000) //累计次数小于3位消隐0
                    Disp_Echo0(0, gu8_AuxDispArray, 3);
            }
            else    //副显示配方
                Disp_Aux_Rec(gu32_RecNum);
        #endif
        }
        else
            VFD_MainDisp_Str("AD ERR");    //显示Ad Err
        
        VFD_UnitDisp(gs_Cal.Unit);                               //单位显示
        VFD_MainSigDisp(gb_SigWtFlg);
        //夹袋输出时，如果定义了夹袋到位但是夹袋到位无效则PACK闪烁
        if (gb_EnPackOKFlg && (!gb_PackOKFlg))
            VFD_LEDDisp(!gb_DispNetFlg, gb_DispNetFlg, false, Flash_Flg(gb_PackFlg));  //LED灯显示
        else
            VFD_LEDDisp(!gb_DispNetFlg, gb_DispNetFlg, false, gb_PackFlg);  //LED灯显示
        Disp_FlgLight();        //标志灯显示
    }
}

