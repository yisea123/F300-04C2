/*************************************************
Project:                GM8804C-2_ARM
File name:              IO.c
Description:            开关量相关函数
Author:                 丛海旭
Version:                1.0
Date:                   2013-12-4
Others: 
History:
*************************************************/
#include "include.h"
#include "Adaptation.h"

//一些跟AD转换速度相关变量中使用，乘以倍数
u8 const cu8_MultiAd[4] = {1,2,4,8};

u32 gu32_IoInBuf_BINYES[9];              //开关量输入自定义  gu32_IoInBuf_BINYES[1~8]
u32 gu32_IoOutBuf_BINYES[13];             //开关量输出自定义  gu32_IoOutBuf_BINYES[1~12]
u32 gu32_IoInBuf_BINNO[9];              //开关量输入自定义
u32 gu32_IoOutBuf_BINNO[13];             //开关量输出自定义
u32 gu32_IoInBuf_BIN_2[9];              //开关量输入自定义
u32 gu32_IoOutBuf_BIN_2[13];             //开关量输出自定义
u32 gu32_IoInBuf_NO_2[9];              //开关量输入自定义
u32 gu32_IoOutBuf_NO_2[13];             //开关量输出自定义

u32 *gu32p_IoInBuf[9];     //开关量输入自定义数组指针
u32 *gu32p_IoOutBuf[13];    //开关量输出自定义数组指针

bool  gb_JSDDelayFlg;               //夹松袋延时启动标志
bool  gb_SDDelayFlg;                //松袋延时启动标志
bool  gb_SDBDelayFlg;               //松袋前延时启动标志
u32 gu32_JSDTime;                  //夹松袋延时时间寄存器

u32 gu32_FlgBright;
u32 gu32_IoTestCode;        //开关量测试密码
u32 gu32_IoTestCodeSwitch;
u32 gu8_IoTestInTime;
u32 gu32_IoDefCode;        //开关量测试密码
u32 gu32_IoDefCodeSwitch;
u32 gu8_IoDefInTime;
u32 gu32_SmallPluseTimeBuf;           //小投点动用时间寄存器
u32 gu32_AutoClrZeroCnt;         //自动清零间隔计数器
u32 gu32_CorrectFallTimeCnt;     //落差修正次数计数器
u32 gu32_CorrectFallWt;          //落差修正累计值
bool gb_DiscShakeFlg;           //卸料震打输出
bool gb_DiscShakeStartFlg;      //卸料震打开始
bool  gb_DiscSumOnFlg;                //手动卸料累计开启卸料标志位
bool  gb_DiscSumOffFlg;               //手动卸料累计关闭卸料标志位
u32 gu32_TestTime;          //显示测试时用的时间寄存器



bool gb_RunFlg;
bool gb_Sp1Flg;
bool gb_Sp2Flg;
bool gb_Sp3Flg;
bool gb_CompFlg;
bool gb_OverFlg;
bool gb_UnderFlg;
bool gb_OUOverFlg;            //超欠差暂停关闭时超欠差的报警标志 OVER
bool gb_OUUnderFlg;           //超欠差暂停关闭时超欠差的报警标志 UNDER
bool gb_PackFlg;
bool gb_DiscFlg;
bool gb_FillFlg;
bool gb_BatchOverFlg;
bool gb_LackFlg;
bool gb_KeyLockFlg;
bool gb_DisRunFlg;
bool gb_FirstStartFlg;           //启动后第一秤标志位
bool gb_OflDelayFlg;             //运行时溢出标志
bool  gb_HighDefineFlg;             //上料位已定义标志
bool  gb_LowDefineFlg;              //下料位已定义标志
bool  gb_MiddleDefineFlg;           //中料位已定义标志
bool  gb_HighFlg;                   //上料位
bool  gb_LowFlg;                    //下料位
bool  gb_MiddleFlg;                 //中料位
bool  gb_LackFlg;                   //缺料
bool gb_PrintCodeOutFlg;        //打码输出
bool gb_EndFlg;                 //停止输入
bool  gb_DiscCloseOKFlg;          //卸料门关门到位输入
bool  gb_EnDiscCloseOKFlg;        //卸料门关门到位已定义标志
bool  gb_PackOKFlg;             //夹袋到位输入
bool  gb_EnPackOKFlg;           //夹带到位已定义标志
bool gb_LiftBagFlg;             //提袋信号
bool gb_PushBagFlg;             //推袋信号
bool gb_DiscEnableOutFlg;       //双秤互锁输出 允许另一秤卸料
bool gb_DiscEnableInFlg;        //双秤互锁输入 允许卸料
bool gb_AddingInFlg;            //无斗双秤互锁输入 加料过程
bool gb_AddingOutFlg;           //无斗双秤互锁输出 加料过程输出
bool gb_GoFlg;                  //手动运行一次标志灯
bool gb_ConveyorRunFlg;         //输送机运行
bool gb_No2PackOffAnother;      //另一秤已经松袋标志
bool gb_No2AddAgainDelay;        //双秤无斗延时启动加料标志
bool gb_CalLockDefFlg;          //标定锁已定义标志位
bool gb_CalLockFlg;             //标定锁输入


/*********************************************************************
函数名称: void IoDefPointerRefresh(u32 fu32_TareMode)
功    能: 刷新IO自定义数组指针，不同秤体模式指向不同数据
说    明: 改变秤体模式后要调用该函数
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-11
修    改:                      时    间: 
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
函数名称: u16 GetIoAddr(u8 fu8_i, u8 fu8_Num, u32 fu32_TareMode)
功    能: 返回IO数组地址
说    明: 
入口参数: 注意 fu8_i只能等于0代表输入，1代表输出。输入时fu8_Num最大12，输出时fu8_Num最大16
          不按上述规则会出错
返 回 值: 
设    计: 丛海旭               时    间: 2013-1-23
修    改:                      时    间: 
*********************************************************************/
u16 GetIoAddr(u8 fu8_i, u8 fu8_Num, u32 fu32_TareMode)
{
    u16 lu16_Addr = FMAddr_IoInBuf1;
    
    switch (fu32_TareMode)
    {
        case BINYES:
        default:
            if (fu8_i == IO_IN)     //输入开关量地址
                lu16_Addr = FMAddr_IoInBuf1;
            else if (fu8_i == IO_OUT)
                lu16_Addr = FMAddr_IoOutBuf1;
            break;
        case BINNO:
            if (fu8_i == IO_IN)     //输入开关量地址
                lu16_Addr = FMAddr_IoInBuf1_BINNO;
            else if (fu8_i == IO_OUT)
                lu16_Addr = FMAddr_IoOutBuf1_BINNO;
            break;
        case BIN2_A:
        case BIN2_B:
            if (fu8_i == IO_IN)     //输入开关量地址
                lu16_Addr = FMAddr_IoInBuf1_BIN_2;
            else if (fu8_i == IO_OUT)
                lu16_Addr = FMAddr_IoOutBuf1_BIN_2;
            break;
    }
    lu16_Addr += ((fu8_Num - 1) * 4);
    return lu16_Addr;
}

/*********************************************************************
函数名称: void Clr_Alarm(void)
功    能: 清报警处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-15
修    改:                      时    间: 
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
    if (gb_OverFlg || gb_UnderFlg)          //超欠差 error8
    {
        gb_OverFlg = false;
        gb_UnderFlg = false;
        gu32_Process = T4PROCESS;
        gu32_TimeBuf = gs_Rec.TimeT4 * 10;
        gb_TimeRunFlg = true;                //定值保持时间t4已经启动
        gu32_Time1_5 = gu32_Sys10ms;        //取当前时间
    }
    if (gb_Error9Flg)       //卸料未干净报警 error9
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
函数名称: void JSD_Init(void)
功    能: 启动时的夹松袋各标志初始化
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2011-4-15
修    改:                      时    间: 
*********************************************************************/
void JSD_Init(void)
{
    if (gb_PackFlg)     //夹袋有效
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
函数名称: void Deal_Pack(void)
功    能: 夹松袋处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-7
修    改:                      时    间: 
*********************************************************************/
void Deal_Pack(void)
{
    if (gb_JSDDelayFlg)         //夹松袋启动延时标志位有效认为有夹松袋操作
    {
        if (gb_SDDelayFlg && (gb_PackFlg == false))         //原来处于以稳定夹袋状态，启动松袋延时
        {
            if (gu32_Sys10ms - gu32_JSDTime >= 30)   //固定夹松袋后的延时为300ms
            {
                gb_PackFlg = false;
                gb_JSDDelayFlg = false;                 //清除夹松袋延时标志
                gb_SDDelayFlg = false;
                gb_SDBDelayFlg = false;
                if (gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                    gb_DiscEnableOutFlg = true; //松袋后才允许另一秤夹袋
            }
        }
        else if (gb_SDBDelayFlg && gb_PackFlg)      //松袋前延时启动
        {
            if (gu32_Sys10ms - gu32_JSDTime >= gs_Rec.TimeT7 * 10)   //松袋前延时时间到
            {
                //拍袋或卸料、打码时等待
                if (((gb_FlapStartFlg || gb_FlapWaitFlg) && (gb_ExtFlapBagFlg == false))
                    || gb_DiscFlg || gb_PrintCodeIngFlg)
                    gu32_JSDTime = gu32_Sys10ms - gs_Rec.TimeT7 * 10;
                else
                {
                    gb_PackFlg = false;         //松袋前延时到后夹袋输出无效
                    gb_SDBDelayFlg = false;
                    gb_JSDDelayFlg = true;
                    gb_SDDelayFlg = true;      //启动松袋延时
                    gu32_JSDTime = gu32_Sys10ms;
                }
            }
        }
        else            //原来处于松袋状态，启动夹袋延时
        {
            if (gu32_Sys10ms - gu32_JSDTime >= gs_Rec.TimeT6 * 10)        //夹袋延时时间到
            {
                gb_JSDDelayFlg = false;
                gb_SDDelayFlg = true;          //夹袋完成可以松袋
            }
        }
    }
    if ((gs_Setup.TareMode == BINNO || gs_Setup.TareMode == NO2_A || gs_Setup.TareMode == NO2_B) && gs_Setup.GorNMode == NET && gb_PackFlg == false)
    {
        //夹袋输出无效时清除皮重已获取到标志
        gb_TareGetedFlg = false;
    }
}

/*********************************************************************
函数名称: void IO_Init(void)
功    能: 输入输出开关量初始化
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-4
修    改:                      时    间: 
*********************************************************************/
void IO_Init(void)
{
    //8输入开关量IO引脚类型定义
    GPIO_Config(GPIO2, (1<<15), GPIO_IN_TRI_TTL); //IN0_READ
    GPIO_Config(GPIO2, (1<<14), GPIO_IN_TRI_TTL); //IN1_READ
    GPIO_Config(GPIO2, (1<<13), GPIO_IN_TRI_TTL); //IN2_READ
    GPIO_Config(GPIO2, (1<<12), GPIO_IN_TRI_TTL); //IN3_READ
    GPIO_Config(GPIO2, (1<<11), GPIO_IN_TRI_TTL); //IN4_READ
    GPIO_Config(GPIO2, (1<<10), GPIO_IN_TRI_TTL); //IN5_READ
    GPIO_Config(GPIO2, (1<<7) , GPIO_IN_TRI_TTL); //IN6_READ
    GPIO_Config(GPIO2, (1<<6) , GPIO_IN_TRI_TTL); //IN7_READ
    //12输出开关量IO引脚类型定义
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
    //输出开关量全部置为无效
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
函数名称: void IO_Outport(u8 PortId, bool Port_Val)
功    能: 操作开关量输出口状态
说    明: 
入口参数: PortId = 1~16 对应 out 1~16开关量输出
          Port_Val = 1 有效  0 无效
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-21
修    改:                      时    间: 
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
函数名称: void ConveyorDeal(bool *fbp_ConveyorStart)
功    能: 提袋推袋处理
说    明: 
入口参数: *fbp_ConveyorStart 提袋启动标志位
返 回 值: 
设    计: 丛海旭               时    间: 2015-2-3
修    改:                      时    间: 
*********************************************************************/
void ConveyorDeal(bool *fbp_ConveyorStart)
{
    static bool sb_CStartFlg = false;
    static bool sb_CStartAgainFlg = false;
    static u32 su32_ConveyorDelayTemp;
    static u32 su32_ConveyorRunTemp;
    static bool sb_ConveyorDelayFlg = false;    //输送机启动延时已启动
    
    if (*fbp_ConveyorStart == true)
    {   //输送机启动
        *fbp_ConveyorStart = false;
        if (sb_CStartFlg) 
        {   //用于处理上一次输送机还未结束输出，又来一次的处理
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
    
    //输送机启动
    if (sb_CStartFlg == true)
    {   //输送机输出有效时间不为0 输送机才有作用
        if (gs_Setup.No2ConveyorRunTime != 0)
        {
            if (gb_ConveyorRunFlg)
            {   //输送机输出已经有效
                if (gu32_Sys10ms - su32_ConveyorRunTemp >= gs_Setup.No2ConveyorRunTime * 10)
                {   //输送机输出结束
                    gb_ConveyorRunFlg = false;
                    if (sb_CStartAgainFlg == false) //输送机输出结束前没有再一次运行信号，则结束输送机输出
                        sb_CStartFlg = false;
                    else    //有再一次运行则接着输出
                        sb_CStartAgainFlg = false;
                    gb_No2AddAgainDelay = false;   //输送机已停止加料等待时间还没到则自动取消等待
                }
                if (gu32_Sys10ms - su32_ConveyorRunTemp >= gs_Setup.No2AddAgainDelayTime * 10)
                {   //再次启动的加料等待时间
                    gb_No2AddAgainDelay = false;
                }
            }
            else if (sb_ConveyorDelayFlg)
            {   //输送机启动延时已经启动
                if (gu32_Sys10ms - su32_ConveyorDelayTemp >= gs_Setup.No2ConveyorDelayTime * 10)
                {   //输送机延时时间到启动输送机输出
                    sb_ConveyorDelayFlg = false;
                    gb_ConveyorRunFlg = true;
                    //此处没有使用su32_ConveyorRunTemp = gu32_Sys10ms是为了支持上次没有输送机输出没有结束
                    //再一次输送机输出有效，为了计算上次结束后还要再继续输出多长时间。
                    su32_ConveyorRunTemp = su32_ConveyorDelayTemp + gs_Setup.No2ConveyorDelayTime * 10;
                }
            }
        }
        else
            sb_CStartFlg = false;
    }
}


/*********************************************************************
函数名称: void IO_OutPut(void)
功    能: 开关量输出处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-7
修    改:                      时    间: 
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
            case 1:         //运行
                lb_State = gb_RunFlg;
                break;
            case 2:         //停止
                lb_State = (!gb_RunFlg);
                break;
            case 3:         //大投
                lb_State = Sp_Disc_State(SP1_STATE);
                break;
            case 4:         //中投
                if (gs_Setup.ResultHoldSwitch != 0)
                {
                    if (gb_Sp2StopTimeRunFlg == false)  //中投处于预测截止点的时间计时当中 程序不再去控制中投的输出
                        lb_State = Sp_Disc_State(SP2_STATE);
                }
                else
                {
                    lb_State = Sp_Disc_State(SP2_STATE);
                }
                break;
            case 5:         //小投
                lb_State = Sp_Disc_State(SP3_STATE);
                break;
            case 6:         //定值
                lb_State = gb_CompFlg;
                break;
            case 7:         //超欠差
                lb_State = (gb_OverFlg || gb_UnderFlg || gb_OUOverFlg || gb_OUUnderFlg);
                break;
            case 8:         //报警
                lb_State = gb_AlarmFlg;
                break;
            case 9:        //夹袋
                lb_State = gb_PackFlg;
                break;
            case 10:        //拍袋
                lb_State = (gb_FlapBagOutFlg || gb_FlapAllHighFlg);
                break;
            case 11:        //卸料
                lb_State = Sp_Disc_State(DISC_STATE);
                break;
            case 12:        //零区
                lb_State = gb_NzFlg;
                break;
            case 13:        //供料
                lb_State = gb_FillFlg;
                break;
            case 14:        //批次完成
                lb_State = gb_BatchOverFlg;
                break;
            case 15:        //缺料
                lb_State = gb_LackFlg;
                break;
            case 16:        //卸料震打
                lb_State = gb_DiscShakeFlg;
                break;
            case 17:        //打码输出
                lb_State = gb_PrintCodeOutFlg;
                break;
            case 18:        //截料
                lb_State = gb_Sp3Flg;
                break;
            case 19:        //提袋
                lb_State = gb_LiftBagFlg;
                break;
            case 20:        //推袋
                lb_State = gb_PushBagFlg;
                break;
            case 21:        //双秤组合输输出
                if (gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                {   //允许另一秤卸料
                    lb_State = gb_DiscEnableOutFlg;
                }
                else
                {
                    lb_State = gb_AddingOutFlg;
                }
                break;
            case 22:        //输送机输出
                lb_State = gb_ConveyorRunFlg;
                break;
            default:
                break;
        }
        if (gu16_MbIoTestSwitch != 0)
        {   //modbus开关量测试打开
            IO_Outport(i, gu16_MbIoOutTest & lu16_Temp);
            lu16_Temp = lu16_Temp << 1;
        }
        else if (gu16_MbIOOutInit)
        {   //modbus开关量debug打开 0093地址
            IO_Outport(i, gu16_MbIoOutDebug & lu16_Temp);
            lu16_Temp = lu16_Temp << 1;
        }
        else
        {
            if (gs_Setup.ResultHoldSwitch != 0)
            {
                if ((*gu32p_IoOutBuf[i] != 4) || gb_Sp2StopTimeRunFlg == false)  
                    //中投处于预测截止点的时间计时当中 程序不再去控制中投的输出
                    IO_Outport(i, lb_State);          //lb_State = 0开关量输出有效  1开关量输出无效
            }
            else
            {
                IO_Outport(i, lb_State);          //lb_State = 0开关量输出有效  1开关量输出无效
            }
        }
    }
}

/*********************************************************************
函数名称: bool IO_Inport(u8 PortId)
功    能: 读取开关量输入口状态
说    明: 
入口参数: PortId = 1~5 对应 in 1~8开关量输入
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-21
修    改:                      时    间: 
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
函数名称: void IO_CloseOut(void)
功    能: 清除所有开关量输出
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-21
修    改:                      时    间: 
*********************************************************************/
void IO_CloseOut(void)
{
    u8 i;
    
    for (i = 1; i <= 12; i++)
    {
        IO_Outport(i, false);          //true开关量输出有效  false开关量输出无效
    }
}


/*********************************************************************
函数名称: void Key_IoTestState(void)
功    能: IO测试
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-21
修    改:                      时    间: 
*********************************************************************/
void Key_IoTestState(void)
{
    u32 i = 1;
    u8 luc_DataLen = 0;      //输入数据位数
    
    gb_FlashFlg = false;
    
    if (gu8_Item == IOTEST_CHECKCODE)  //密码验证
    {
        luc_DataLen = 6;
        gb_FirstNumKeyFlg = false;
        ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
        if (gu32_KeyCode == K_ENTER)           //确认键处理
        {
            gb_FirstNumKeyFlg = true;
            gu8_IoTestInTime++;
            if ((ulParameter.ul == gu32_IoTestCode && gu8_DataInLength ==6) || 
                (ulParameter.ul == SUPERCODE && gu8_DataInLength ==6))        //输入密码等于设定密码或超级密码
            {
                gu8_IoTestInTime = 0;            //清除密码输入错误次数计数器
                ulParameter.ul = 0;
                gu8_Item = IOTEST;  //进入测试状态
            }
            else if (gu8_IoTestInTime >= 3)      //密码输入错误超过3次
            {
                ErrorDeal(4, 0);        //显示error4
                Disp_Error();
                VFD_CopyDispArryToDispRam();
                VFD_WriteDispRamArry();
                while(1);
            }
            else            //密码输入错误，提示error
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
    else if (gu8_Item == IOTEST)  //开关量测试状态
    {
        switch (gu32_KeyCode)            //按按键对应的开关量输出有效
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
            case K_8_2S:    //长按8进入显示屏测试状态，生产用来烧屏
                gu8_Item = IOTEST_TESTDISP;
                ulParameter.ul = 0;
                gu32_TestTime = gu32_Sys10ms;
            default:
                break;
        }
    }
    else if (gu8_Item == IOTEST_SWITCH)     //密码开关
    {
        ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 1);      //两项切换，用↑键修改
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
    else if (gu8_Item == IOTEST_SETCODE)        //密码设置
    {
        gb_FirstNumKeyFlg = false;
        luc_DataLen = 0;
        if (gu32_KeyCode == K_SET)           //进入密码设置状态
            gb_SetFlg = true;
        if (gb_SetFlg)
        {
            if (gu32_KeyCode == K_ESC)       //退出密码设置状态
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
                    if (ulParameter.ul == gu32_DataTemp && gu8_DataInLength == 6)         //两次输入的密码一致
                    {
                        gu8_IoTestInTime = 0;
                        gb_SetFlg = false;
                        gu32_IoTestCode = ulParameter.ul;
                        FRAM_WriteDW(FMAddr_IoTestCode, gu32_IoTestCode);          //保存密码
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
                    if (gu8_DataInLength == 6)      //密码输入必须6位
                    {
                        gu32_DataTemp = ulParameter.ul;      //暂存第一次密码设置值
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
            gu8_Item = IOTEST;  //进入测试状态
        }
    }
}

/*********************************************************************
函数名称: void Disp_IoTestState(void)
功    能: IO测试显示处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-21
修    改:                      时    间: 
*********************************************************************/
void Disp_IoTestState(void)
{
    u8 i;
    
    if (gu8_Item == IOTEST_CHECKCODE)  //密码验证
    {
        Disp_InputCode();
        gb_FlashFlg = true;
        Flash_MainDisp(0x01);                //闪烁处理
    }
    else if (gu8_Item == IOTEST)
    {
        //输入开关量无效显示F，有效显示o，8个F对应8个开关量输入
        VFD_MainDisp_Str("FFFFFF");
        VFD_AuxDisp_Str("FF ");
        
        for (i = 1; i <= 8; i++)           //IN1~IN8
        {
            if (IO_Inport(i) == true)        //输入有效对应位置显示o
            {
                if (i <= 6)
                    gu8_MainDispArray[i-1] = SEG_o;
                else
                    gu8_AuxDispArray[i-7] = SEG_o;
            }
        }
        VFD_FlgDisp(gu32_FlgBright);    //标志灯显示
    }
    else if (gu8_Item == IOTEST_SWITCH)
    {
        Disp_OnOff(ulParameter.ul);           //显示开关
        VFD_AuxDisp_Str("PAS");
    }
    else if (gu8_Item == IOTEST_SETCODE)
    {
        Disp_InputCode();       //密码输入显示处理
        if (gb_SetFlg == true)
            gb_FlashFlg = true;
        else
            gb_FlashFlg = false;
        Flash_MainDisp(0x01);                //闪烁处理
    }
    else    //显示测试
    {
        if (ulParameter.ul == 0)
        {   //闪烁状态
            if(gu32_Sys10ms - gu32_TestTime > 60)
            {   //清显示
                VFD_ClrDispRam(1, 0);
                if (gu32_Sys10ms - gu32_TestTime > 120)
                    gu32_TestTime = gu32_Sys10ms;
            }
            else
            {   //填充显示
                VFD_FillDispRam(0,1);
            }
        }
        else
        {   //常亮状态
            VFD_FillDispRam(0,1);
        }
    }
}


/*********************************************************************
函数名称: void Key_IoDefState(void)
功    能: Io自定义按键处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-25
修    改:                      时    间: 
*********************************************************************/
void Key_IoDefState(void)
{
    u8 luc_DataLen = 2;      //输入数据位数
    static u8 su8_ItemBak;
    
    if (gu8_Item == IODEF_CHECKCODE)    //密码输入
    {
        luc_DataLen = 6;
        gb_FirstNumKeyFlg = false;
        ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
        if (gu32_KeyCode == K_ENTER)           //确认键处理
        {
            gb_FirstNumKeyFlg = true;
            gu8_IoDefInTime++;
            if ((ulParameter.ul == gu32_IoDefCode && gu8_DataInLength ==6) || 
                (ulParameter.ul == SUPERCODE && gu8_DataInLength ==6))        //输入密码等于设定密码或超级密码
            {
                gu8_IoDefInTime = 0;            //清除密码输入错误次数计数器
                gu8_Item = IODEF_IN1;  //进入自定义状态
                ulParameter.ul = *gu32p_IoInBuf[1];
            }
            else if (gu8_IoDefInTime >= 3)      //密码输入错误超过3次
            {
                ErrorDeal(4, 0);        //显示error4
                Disp_Error();
                VFD_CopyDispArryToDispRam();
                VFD_WriteDispRamArry();
                while(1);
            }
            else            //密码输入错误，提示error
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
    else if (gu8_Item >= IODEF_IN1 && gu8_Item <= IODEF_OUT12)     //开关量自定义
    {
        //数据输入
        ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
        //如果输入的数据超过自定义范围则显示数据闪烁
        if (gu8_Item <= 8)
        {
            if (ulParameter.ul > IO_INMAX)  //输入量自定义超出范围
                gb_FlashFlg = true;
            else
                gb_FlashFlg = false;
        }
        else
        {
            if (ulParameter.ul > IO_OUTMAX)  //输出量自定义超出范围
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
                if (gb_FlashFlg == true)    //如果处于闪烁状态即未保存状态按↑键，重新读取未修改前的值并++
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
                if (gb_FlashFlg)    //如果处于闪烁状态则说明当前输入数据不符合范围
                {
                    ErrorDeal(0, 100);
                    ulParameter.ul = (gu8_Item > IODEF_IN8) ? *gu32p_IoOutBuf[gu8_Item - 8] : *gu32p_IoInBuf[gu8_Item];
                    gb_FlashFlg = false;
                    gb_FirstNumKeyFlg = true;
                    return;
                }
                gb_FlashFlg = false;
                gb_FirstNumKeyFlg = true;
                if (gu8_Item <= 8)             //保存输入开关量
                {
                    *gu32p_IoInBuf[gu8_Item] = ulParameter.ul;
                    FRAM_WriteDW(GetIoAddr( IO_IN, 1, gs_Setup.TareMode) + (gu8_Item - 1) * 4, *gu32p_IoInBuf[gu8_Item]);
                }
                else                            //保存输出开关量
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
    else if (gu8_Item == IODEF_SWITCH)  //密码开关
    {
        ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 1);      //两项切换，用↑键修改
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
    else //密码设置
    {
        gb_FirstNumKeyFlg = false;
        luc_DataLen = 0;
        if (gu32_KeyCode == K_SET)           //进入密码设置状态
            gb_SetFlg = true;
        if (gb_SetFlg)
        {
            if (gu32_KeyCode == K_ESC)       //退出密码设置状态
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
                    if (ulParameter.ul == gu32_DataTemp && gu8_DataInLength == 6)         //两次输入的密码一致
                    {
                        gu8_IoDefInTime = 0;
                        gb_SetFlg = false;
                        gu32_IoDefCode = ulParameter.ul;
                        FRAM_WriteDW(FMAddr_IoDefCode, gu32_IoDefCode);          //保存密码
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
                    if (gu8_DataInLength == 6)      //密码输入必须6位
                    {
                        gu32_DataTemp = ulParameter.ul;      //暂存第一次密码设置值
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
函数名称: void Disp_IoDefState(void)
功    能: IO自定义显示处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-25
修    改:                      时    间: 
*********************************************************************/
void Disp_IoDefState(void)
{
    u8 i;
    
    if (gu8_Item == IODEF_CHECKCODE)    //密码验证
    {
        Disp_InputCode();
        gb_FlashFlg = true;
        Flash_MainDisp(0x01);                //闪烁处理
    }
    else if (gu8_Item >= IODEF_IN1 && gu8_Item <= IODEF_OUT12)
    {
        if (gu8_Item <= 8)             //输入自定义
        {
            gu8_MainDispArray[2] = SEG_I;
            gu8_MainDispArray[3] = SEG_N;
            gu8_AuxDispArray[0] = SEG_I;
            i = gu8_Item;
        }
        else                            //输出自定义
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
        Flash_AuxDisp(0x03);                //闪烁处理
    }
    else if (gu8_Item == IODEF_SWITCH)  //
    {
        Disp_OnOff(ulParameter.ul);           //显示开关
        VFD_AuxDisp_Str("PAS");
    }
    else
    {
        Disp_InputCode();       //密码输入显示处理
        if (gb_SetFlg == true)
            gb_FlashFlg = true;
        else
            gb_FlashFlg = false;
        Flash_MainDisp(0x01);                //闪烁处理
    }
}

/*********************************************************************
函数名称: void RunStopInit(bool fb_RunStop)
功    能: 运行或停止的处理
说    明: 
入口参数: fb_RunStop = 1 运行   0 停止
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-7
修    改:                      时    间: 
*********************************************************************/
void RunStopInit(bool fb_RunStop)
{
    if ((fb_RunStop == false) || (gb_AlarmFlg == false))
    {
        if (fb_RunStop)             //运行处理
        {
            fb_RunStop = false;
            if (gb_RunFlg == false)      //原来停止状态才能启动
            {
                if (gs_Rec.Target != 0)          //单称目标值不为0时才能启动，否则提示error6
                {
                    gb_RunFlg = true;      //运行
                    fb_RunStop = true;
                    gu32_SystemState = RUNSTATE;
                    gu32_Process = T1PROCESS;   //启动后A进入T1延时阶段
                    gu32_TimeBuf = gs_Rec.TimeT1 * 10;
                    gu32_Time1_5 = gu32_Sys10ms;
                    JSD_Init();
                    if (gu32_BatchTimeCnt == 0)
                    {
                        gu32_BatchTimeCnt = gu32_BatchTime;
                        FRAM_WriteDW(FMAddr_BatchTimeCnt, gu32_BatchTimeCnt);
                    }
                    gu32_TargetTemp = gs_Rec.Target;
                    gu32_WeighTimeCnt = gs_Rec.CombinedNum;              //单秤组合次数
                    gb_FirstPrintFlg_UART0 = true;    //运行后第一次打印要打印台头
                    gb_FirstPrintFlg_UART1 = true;    //运行后第一次打印要打印台头
                    if (gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) //双秤互锁模式，启动时允许另一秤卸料
                        gb_DiscEnableOutFlg = true;
                    gb_DiscWtGetedFlg = false;
                    //调试用时间结构体清除
                    gs_DebugRunTime.u32Sp1Time = 0;
                    gs_DebugRunTime.u32Sp2Time = 0;
                    gs_DebugRunTime.u32Sp3Time = 0;
                    gs_DebugRunTime.u32RunCmpTime = 0;
                    gs_DebugRunTime.bGetRunCmpTimeFlg = false;
                    gs_DebugRunTime.u32OneTareTime = 0;
                    gs_DebugRunTime.u32RunStartTimeTemp = gu32_Sys1ms; //记录启动时刻
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
                    Adapt_InitDataFirstRun(&gs_Adapt);   //自适应启动处理
                }
                else
                {
                    ErrorDeal(6, 100);     //提示错误6
                    gb_AlarmFlg = true;
                    gb_GoFlg = false;
                }
            }
        }
        else                        //停止处理
        {
            if (gb_RunFlg)
            {
                gb_DiscShakeFlg = false;     //卸料震打输出
                gb_DispNetFlg = false;
                gb_RunFlg = false;
                fb_RunStop = true;
                gb_FirstPrintFlg_UART0 = false;
                gb_FirstPrintFlg_UART1 = false;
                UpdateFastSetRec();
                if (gb_EndFlg == false)     //结束输入停止后不能初始化夹袋状态，会造成最后一秤不松袋
                    JSD_Init();
            }
            gu32_SystemState = STOPSTATE;
            gb_GoFlg = false;
            //停止输入时立即停止打码
            if((gs_Rec.PrintCodeSwitch != 0)&&(gs_Rec.PrintCodeTime != 0))
                gb_StopPrintCodeFlg = true;
            gu32_DebugSumNum = 0;
            PrintStart(PRINT_STATISTIC, 0, 0);
        }
    }
    
    if (fb_RunStop)
    {
        gb_EndFlg = false;              //结束输入
        gb_DiscFlg = false;           //清卸料信号
        gb_CompFlg = false;           //清定值信号
        gb_Sp1Flg = false;          //清大投信号
        gb_Sp2Flg = false;         //清中投信号
        gb_Sp3Flg = false;          //清小投信号
        gb_ZeroKeyFlg = false;        //清零标志位
        gb_SumFlg = false;
        
        gb_FlapWaitFlg = false;         //拍袋延时已启动
        gb_FlapStartFlg = false;        //拍袋已经启动
        gb_FlapBagOutFlg = false;       //拍袋输出信号
        gb_FlapAllHighFlg = false;
        gb_OflDelayFlg = false;
        gu32_DiscShakeCnt = 0;
        gb_DiscShakeStartFlg = false;
        gb_DiscShakeFlg = false;
        gu32_SumTemp = 0;
        gb_No2PackOffAnother = false;
        //清除无斗双秤互锁输出
        gb_AddingOutFlg = false;
        gb_No2AddAgainDelay = false;
        
        gu32_AutoClrZeroCnt = gs_Setup.AutoClrZeroInterval;         //初始化清零间隔计数器
        gu32_CorrectFallTimeCnt = gs_Rec.CorrectFallTime;         //初始化落差修正计数器
        gu32_CorrectFallWt = 0;                //初始化落差修正累计值
        if (gb_PackFlg == false)            //松袋状态，清松袋延时状态，允许立刻夹袋
        {
            gb_JSDDelayFlg = false;
            gb_SDDelayFlg = false;
        }
        gb_FirstStartFlg = true;
        gb_AddFlapBagFlg = false;                //加料中拍袋标志位
        gb_ExtFlapBagFlg = false;                //额外拍袋输出标志位
        gb_TimeRunFlg = false;
        StabOver(true);
        Clr_Alarm();
    }
}

/*********************************************************************
函数名称: void PackInput(void)
功    能: 夹松袋处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-19
修    改:                      时    间: 
*********************************************************************/
void PackInput(void)
{
    if ((gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gb_DiscEnableInFlg == false)
        //双秤互锁运行时如果卸料允许输入无效那么不允许响应夹袋
        return;
    if (gb_JSDDelayFlg)         //夹松袋延时状态，不响应夹松袋请求
        return;
    if (gb_SDDelayFlg && gb_PackFlg)        //已经稳定夹袋
    {
        if ((gb_RunFlg && (gs_Setup.TareMode == BINNO || gs_Setup.TareMode == NO2_A || gs_Setup.TareMode == NO2_B) && gu32_Process > T1PROCESS) ||    //v1.01
           (gb_RunFlg && (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gu32_Process >= T4PROCESS) ||
           (gb_RunFlg && (gs_Setup.TareMode == BINYES) && gs_Rec.CombinedNum > 1 && gs_Rec.CombinedNum != gu32_WeighTimeCnt) )
            //无斗启动加料后不响应松袋，加料前可以松 C
            //有斗在定值保持时间启动之前都可以松袋
            //单秤组合次数大于1并且已经卸过料，不能再松袋
            gb_JSDDelayFlg = false;
        else
        {
            gb_PackFlg = false;     //清除夹袋信号
            gb_JSDDelayFlg = true;             //夹松袋延时启动标志置位
            gb_SDDelayFlg = true;              //松袋延时启动标志置位
            gb_SDBDelayFlg = false;             //清除松袋前延时启动标志
            gu32_JSDTime = gu32_Sys10ms;      //读取当前时间用作计时松袋后延时
        }
    }
    else if (gb_PackFlg == false)       //当前未夹袋，输出夹袋并启动夹袋延时
    {
        gb_PackFlg = true;             //输出夹袋
        gb_JSDDelayFlg = true;         //夹松袋延时启动标志置位
        gb_SDDelayFlg = false;          //清除松袋延时启动标志
        gb_SDBDelayFlg = false;         //清除松袋前延时启动标志
        gu32_JSDTime = gu32_Sys10ms;  //读取当前时间作计时夹袋后延时
    }
    else            //已夹袋但未稳定夹袋，不操作
        gb_JSDDelayFlg = true;
}

/*********************************************************************
函数名称: void Pack_JD(void)
功    能: 夹袋处理
说    明: PROFIBUS通讯中使用到
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-5-6
修    改:                      时    间: 
*********************************************************************/
void Pack_JD(void)
{
    if ((gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gb_DiscEnableInFlg == false)
        //双秤互锁运行时如果卸料允许输入无效那么不允许响应夹袋
        return;
    if (gb_JSDDelayFlg)         //夹松袋延时状态，不响应夹松袋请求
        return;if (gb_PackFlg == false)       //当前未夹袋，输出夹袋并启动夹袋延时
    {
        gb_PackFlg = true;             //输出夹袋
        gb_JSDDelayFlg = true;         //夹松袋延时启动标志置位
        gb_SDDelayFlg = false;          //清除松袋延时启动标志
        gb_SDBDelayFlg = false;         //清除松袋前延时启动标志
        gu32_JSDTime = gu32_Sys10ms;  //读取当前时间作计时夹袋后延时
    }
}

/*********************************************************************
函数名称: void Pack_SD(void)
功    能: 松袋处理
说    明: PROFIBUS通讯中使用到
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-5-6
修    改:                      时    间: 
*********************************************************************/
void Pack_SD(void)
{
    if ((gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gb_DiscEnableInFlg == false)
        //双秤互锁运行时如果卸料允许输入无效那么不允许响应夹袋
        return;
    if (gb_JSDDelayFlg)         //夹松袋延时状态，不响应夹松袋请求
        return;
    if (gb_SDDelayFlg && gb_PackFlg)        //已经稳定夹袋
    {
        if ((gb_RunFlg && (gs_Setup.TareMode == BINNO || gs_Setup.TareMode == NO2_A || gs_Setup.TareMode == NO2_B)) ||
           (gb_RunFlg && (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gu32_Process >= T4PROCESS) ||
           (gb_RunFlg && (gs_Setup.TareMode == BINYES) && gs_Rec.CombinedNum > 1 && gs_Rec.CombinedNum != gu32_WeighTimeCnt) )
            //无斗运行时不响应松袋
            //有斗在定值保持时间启动之前都可以松袋
            //单秤组合次数大于1并且已经卸过料，不能再松袋
            gb_JSDDelayFlg = false;
        else
        {
            gb_PackFlg = false;     //清除夹袋信号
            gb_JSDDelayFlg = true;             //夹松袋延时启动标志置位
            gb_SDDelayFlg = true;              //松袋延时启动标志置位
            gb_SDBDelayFlg = false;             //清除松袋前延时启动标志
            gu32_JSDTime = gu32_Sys10ms;      //读取当前时间用作计时松袋后延时
        }
    }
}


/*********************************************************************
函数名称: u32 NextRecNum(u32 fu32_Num)
功    能: 跳到下一个目标值不为零的配方
说    明: 开关量选配方的响应
入口参数: 
返 回 值: 配方号
设    计: 丛海旭               时    间: 2014-1-23
修    改:                      时    间: 
*********************************************************************/
u32 NextRecNum(u32 fu32_Num)
{
    u8 i;
    u8 lu8_Num;
    
    for (i = fu32_Num, lu8_Num = fu32_Num; i < fu32_Num + 20; i++)
    {
        if (++lu8_Num > 20)            //共20个配方
            lu8_Num = 1;
        if (FRAM_ReadDW(FMAddr_Target(lu8_Num)) != 0)
        {
            return lu8_Num;
        }
    }
    return fu32_Num;    //其他配方目标值全为0
}


/*********************************************************************
函数名称: void ManualDisc(u8 fu8_State)
功    能: 手动卸料处理
说    明: 
入口参数: fu8_State: 0无效 1有效 其他值：取反
返 回 值: 
设    计: 丛海旭               时    间: 2014-08-19
修    改:                      时    间: 
*********************************************************************/
void ManualDisc(u8 fu8_State)
{
//    if (gs_Setup.DiscSumSwitch != 0) //手动卸料累计开关打开
//    {
//        if (fu8_State == 0)
//        {
//            if (gb_DiscFlg == true)   //此时正在卸料则置准备关闭卸料标志位
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
//            if (gb_DiscFlg == true)   //此时正在卸料则置准备关闭卸料标志位
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
    {   //0和1之外的值取反
        gb_DiscFlg = ((fu8_State != 0 && fu8_State != 1) ? (!gb_DiscFlg): fu8_State);
    }
}

/*********************************************************************
函数名称: void ManualSp3(u8 fu8_State)
功    能: 手动小投处理
说    明: 
入口参数: fu8_State: 0无效 1有效 其他值：取反
返 回 值: 
设    计: 丛海旭               时    间: 2014-12-24
修    改:                      时    间: 
*********************************************************************/
void ManualSp3(u8 fu8_State)
{
    gb_Sp1Flg = false;
    gb_Sp2Flg = false;
    //0和1之外的值取反
    gb_Sp3Flg = ((fu8_State != 0 && fu8_State != 1) ? (!gb_Sp3Flg): fu8_State);
}

/*********************************************************************
函数名称: void ManualSp123(u8 fu8_State)
功    能: 手动大投处理
说    明: 
入口参数: fu8_State: 0无效 1有效 其他值：取反
返 回 值: 
设    计: 丛海旭               时    间: 2014-12-24
修    改:                      时    间: 
*********************************************************************/
void ManualSp123(u8 fu8_State)
{
    //0和1之外的值取反
    gb_Sp3Flg = ((fu8_State != 0 && fu8_State != 1) ? (!gb_Sp3Flg): fu8_State);
    gb_Sp1Flg = gb_Sp3Flg;
    gb_Sp2Flg = gb_Sp3Flg;
}

/*********************************************************************
函数名称: void IO_InDeal(u32 ful_In, bool fb_Mode)
功    能: 输入开关量处理
说    明: 
入口参数: gu32_In = 输入对应开关量号  fb_Mode = 1有效 0无效
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-6
修    改:                      时    间: 
*********************************************************************/
void IO_InDeal(u32 ful_In, bool fb_Mode)
{
    if (gu16_MbIoTestSwitch == 0)       //串口开关量测试开关打开时不响应开关量输入
    {
        if (fb_Mode == true)           //开关量有效处理
        {
            switch (ful_In)
            {
                case 1:             //运行
                case 14:            //电平运行
                case 24:            //电平启动/急停 v1.01
                    if (gb_DisRunFlg == false)      //停止输入无效时才允许启动
                        RunStopInit(true);
                    break;
                case 2:             //急停 
                    Clr_Alarm();
                    RunStopInit(false);
                    break;
                case 3:             //清零
                    if (gb_RunFlg == false)
                        gb_ZeroKeyFlg = true;
                    break;
                case 4:             //清报警
                    Clr_Alarm();
                    break;
                case 5:            //选配方
                    if (gb_RunFlg == false)
                    {
                        //选配方输入有效调到下目标值不为0的配方
                        gu32_RecNum = NextRecNum(gu32_RecNum);
                        FRAM_WriteDW(FMAddr_RecNum, gu32_RecNum);
                        Read_RecipeData(gu32_RecNum);
                    }
                    break;
                case 6:             //夹松袋
                    PackInput();
                    break;
                case 7:             //手动卸料
                    if (gb_RunFlg == false)
                        ManualDisc(2);
                    break;
                case 8:             //手动小投
                    if (gb_RunFlg == false)
                        ManualSp3(2);
                    break;
                case 9:            //打印总累计
                    if (gb_RunFlg == false)
                        PrintStart(PRINT_TOTAL_REPORT, 0, 0);
                    break;
                case 11:        //上料位
                    gb_HighFlg = true;
                    break;
                case 12:        //下料位
                    gb_LowFlg = true;
                    break;
                case 13:        //手动运行一次
                    if (gb_DisRunFlg == false)      //停止输入无效时才允许启动
                    {
                        gb_GoFlg = true;
                        RunStopInit(true);
                    }
                    break;
                case 15:            //电平手动小投
                    if (gb_RunFlg == false)
                        ManualSp3(1);
                    break;
                case 16:            //电平手动卸料
                    if (gb_RunFlg == false)
                        ManualDisc(1);
                    break;
                case 17:            //停止
                    Clr_Alarm();
                    if (gb_RunFlg)
                        gb_EndFlg = true;
                    break;
                case 18:            //卸料门关门到位输入
                    gb_DiscCloseOKFlg = true;
                    break;
                case 19:            //夹袋到位输入
                    gb_PackOKFlg = true;
                    break;
                case 20:            //手动大投
                    if (gb_RunFlg == false)
                        ManualSp123(2);
                    break;
                case 21:            //电平手动加料
                    if (gb_RunFlg == false)
                        ManualSp123(1);
                    break;
                case 22:        //中料位
                    gb_MiddleFlg = true;
                    break;
                case 25:        //标定锁
                    gb_CalLockFlg = true;
                    break;
                default:
                    break;
            }
        }
        else            //开关量无效处理
        {
            switch (ful_In)
            {
                case 11:        //上料位
                    gb_HighFlg = false;
                    break;
                case 12:        //下料位
                    gb_LowFlg = false;
                    break;
                case 14:            //电平运行
                    Clr_Alarm();
                    if (gb_RunFlg)
                        gb_EndFlg = true;
                    break;
                case 15:            //电平手动小投
                    if (gb_RunFlg == false)
                        ManualSp3(0);
                    break;
                case 16:            //电平手动卸料
                    if (gb_RunFlg == false)
                        ManualDisc(0);
                    break;
                case 18:            //卸料门关门到位输入
                    gb_DiscCloseOKFlg = false;
                    break;
                case 19:            //夹袋到位输入
                    gb_PackOKFlg = false;
                    break;
                case 21:            //电平手动大投
                    if (gb_RunFlg == false)
                        ManualSp123(0);
                    break;
                case 22:            //中料位
                    gb_MiddleFlg = false;
                    break;
                case 24:            //电平启动/急停 v1.01
                    Clr_Alarm();
                    RunStopInit(false);
                    break;
                case 25:        //标定锁
                    gb_CalLockFlg = false;
                    break;
                default:
                    break;
            }
        }
    }
}

/*********************************************************************
函数名称: void DoubleLock(bool fb_State)
功    能: 双秤互锁输入开关量的处理
说    明: 
入口参数: fb_State true信号有效处理 false信号无效处理
返 回 值: 
设    计: 丛海旭               时    间: 2015-02-04
修    改:                      时    间: 
*********************************************************************/
void DoubleLock(bool fb_State)
{
    if (fb_State == true)
    {
        gb_DiscEnableInFlg = true;  //有斗双秤互锁
        gb_AddingInFlg = true;      //无斗双秤互锁
    }
    else
    {
        if (gs_Setup.TareMode == NO2_A || gs_Setup.TareMode == NO2_B)
        {   //无斗双秤互锁处理
            if (gb_AddingInFlg)
            {   //如果是互锁输入由有效变为无效则认为另外一秤已经松袋
                gb_No2PackOffAnother = true;
            }
            gb_AddingInFlg = false;     //无斗双秤互锁
        }
        if (gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
        {
            gb_DiscEnableInFlg = false; //有斗双秤互锁
            if (gb_DiscEnableOutFlg == false)
            {   /*互锁输入变为无效时，正常情况下互锁输出肯定是有效的，只有两秤在小投结束后的
                互锁判断那里是同时进行的，同时置了互锁输出无效，那么才会有输入和输出同时都为
                无效的情况*/
                if (gs_Setup.TareMode == BIN2_B && gb_RunFlg)
                {/*如果是BIN2-B此时应该让BIN2-A先卸料 并清除夹袋状态*/
                    gb_DiscEnableOutFlg = true;
                    gb_PackFlg = false;
                    gb_JSDDelayFlg = false;                 //清除夹松袋延时标志
                    gb_SDDelayFlg = false;
                    gb_SDBDelayFlg = false;
                }
            }
            else
            {/*正常情况下互锁输入变为无效时，互锁输出肯定是有效的，以为着此时是另一秤
                在卸料，所以本秤要清除掉夹袋状态，由另一秤控制松袋*/
                if ((gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gb_RunFlg)
                {   //双秤互锁 运行时如果卸料允许输入无效的话清除夹袋相关变量状态
                    gb_PackFlg = false;
                    gb_JSDDelayFlg = false;                 //清除夹松袋延时标志
                    gb_SDDelayFlg = false;
                    gb_SDBDelayFlg = false;
                }
            }
        }
    }
}

/*********************************************************************
函数名称: void IO_InScan(void)
功    能: 输入开关量扫描
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-6
修    改:                      时    间: 
*********************************************************************/
void IO_InScan(void)
{   /*AD转换120次/秒时，去抖次数用4次，大概1/30秒
      转换次数修改后做响应转换*/
    #define DEWOBNUM    (cu8_MultiAd[gs_Setup.AdSamplingRate] * 4)   //脉冲信号去抖动次数
    static u8 su8_InActCnt[9]= {0,0,0,0,0,0,0,0,0};     //输入有效计数器
    static u8 su8_InNoCnt[9] = {0,0,0,0,0,0,0,0,0};     //输入无效计数器
    static u8 su8_OldIoState[9] = {0,0,0,0,0,0,0,0,0};           //上次开关量输入的状态 su8_OldIoState[1~12]

    u8 i;
    u16 j = 0x01;
    
    gb_HighDefineFlg = false;
    gb_LowDefineFlg = false;
    gb_MiddleDefineFlg = false;
    gb_EnPackOKFlg = false;
    gb_EnDiscCloseOKFlg = false;
    gb_CalLockDefFlg = false;
//    
//    //电平类信号输入，注：不同于说明书中的电平类信号说明，此处处理的是
//    //有效时每次都要执行的处理如检测是否定义了某些功能。说明书中运行（电平）等信号只是在信号
//    //有效和无效状态跳变是才执行一次，在IO_InDeal()函数中。
    for (i = 1; i <= 8; i++)
    {
        switch (*gu32p_IoInBuf[i])
        {
            case 2:     //急停
                if (IO_Inport(i) == true)
                    gb_DisRunFlg = true;               //停止输入有效时，禁止启动输入
                else 
                    gb_DisRunFlg = false;
                break;
            case 10:    //键盘锁
                if (IO_Inport(i) == true)
                    gb_KeyLockFlg = true;
                else
                    gb_KeyLockFlg = false;
                break;
            case 11:    //上料位已定义
                gb_HighDefineFlg = true;           //上料位已经定义
                break;
            case 12:    //下料位已定义
                gb_LowDefineFlg = true;            //下料位已经定义
                break;
            case 18:    //卸料门关闭到位已定义
                gb_EnDiscCloseOKFlg = true;
                break;
            case 19:    //夹袋到位已定义
                gb_EnPackOKFlg = true;
                break;
            case 22:    //中料位已定义
                gb_MiddleDefineFlg = true;            //下料位已经定义
                break;
            case 23:    //双秤互锁输入 允许卸料
                DoubleLock(IO_Inport(i));
                break;
            case 25:    //标定锁已定义
                gb_CalLockDefFlg = true;
                break;
            default:
                break;
        }
    }
    
    //开关量去抖处理
    for (i = 1; i <= 8; i++)
    {
        if (IO_Inport(i) == true)                //检测到开关量输入有效
        {
            gu16_MbIoInState |= j;   //赋值Modbus输入开关量测试的变量
            su8_InNoCnt[i] = 0;                 //开关量输入有效后清除输入无效计数器
            if (su8_OldIoState[i] == 0)         //原来处于开关量无效状态
            {
                if (++su8_InActCnt[i] >= DEWOBNUM)      //开关量连续有效次数超过去抖次数才认为此次输入有效
                {
                    su8_InActCnt[i] = 0;        //清除计数器
                    su8_OldIoState[i] = 1;      //置开关量输入有效
                    IO_InDeal(*gu32p_IoInBuf[i], true);     //对应开关量的有效处理
                }
            }
            else            //原来就处于输入有效状态则不做处理
            {
                su8_InActCnt[i] = 0;             //清除计数器
            }
        }
        else                //检测到开关量输入无效
        {
            gu16_MbIoInState &= (~j);   //赋值Modbus输入开关量测试的变量
            su8_InActCnt[i] = 0;         //清除计数器
            if (su8_OldIoState[i] == 1)         //原来处于输入有效状态
            {
                if (++su8_InNoCnt[i] >= DEWOBNUM)      //开关量连续有效次数超过去抖次数才认为此次输入有效
                {
                    su8_InNoCnt[i] = 0;         //清除计数器
                    su8_OldIoState[i] = 0;      //置开关量输入无效
                    IO_InDeal(*gu32p_IoInBuf[i], false);     //对应开关量的有效处理
                }
            }
            else            //原来就处于输入无效状态
            {
                su8_InNoCnt[i] = 0;         //清除计数器
            }
        }
        j <<= 1;
    }
    
    if (gb_HighDefineFlg && gb_LowDefineFlg && (!gb_MiddleDefineFlg))
    {   //只定义上下料位
        if (gb_LowFlg == false && gb_HighFlg == false)          //上下料位都无效
        {
            gb_LackFlg = true;         //缺料有效
            gb_FillFlg = true;         //供料有效
        }
        else if (gb_HighFlg)        //上料位有效则缺料输出无效 供料输出无效
        {
            gb_LackFlg = false;
            gb_FillFlg = false;
        }
        else if (gb_LowFlg)         //上料位无效，下料位有效，则缺料输出无效
        {
            gb_LackFlg = false;
        }
    }
    else if (gb_HighDefineFlg && gb_LowDefineFlg && gb_MiddleDefineFlg)
    {   //上中下料位都定义
        if (gb_MiddleFlg == false && gb_HighFlg == false)          //中上料位都无效
        {
            gb_LackFlg = true;         //缺料有效
            gb_FillFlg = true;         //供料有效
        }
        else if (gb_HighFlg)        //上料位有效则缺料输出无效 供料输出无效
        {
            gb_LackFlg = false;
            gb_FillFlg = false;
        }
        else if (gb_MiddleFlg)         //上料位无效，下料位有效，则缺料输出无效
        {
            gb_LackFlg = false;
        }
    }
    else if (gb_LowDefineFlg)
    {   //定义了下料位
        gb_FillFlg = false;
        if (gb_LowFlg == false)         //下料位无效，缺料有效
            gb_LackFlg = true;
        else
            gb_LackFlg = false;
    }
    else
    {   //其他情况
        gb_FillFlg = false;
        gb_LackFlg = false;
    }
}

/*********************************************************************
函数名称: bool Sp_Disc_State(u8 fu8_Item)
功    能: 加料和卸料开关量状态输出处理
说    明: 投料方式，夹袋到位，卸料门关门到位等逻辑
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-20
修    改:                      时    间: 
*********************************************************************/
bool Feed_SP(u8 fu8_Item)
{
    //投料方式处理 组合 单独
    bool  lb_Sp1Flg_Temp = gb_Sp1Flg;
    bool  lb_Sp2Flg_Temp = gb_Sp2Flg;
    bool  lb_Sp3Flg_Temp = gb_Sp3Flg;
    
    if (gs_Setup.FeedMode == SIN)           //单独投料模式
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
函数名称: bool SmallDropOut(void)
功    能: 小投开关量输出的处理
说    明: 包括点动输出程序
入口参数: 
返 回 值: 0无效 1有效
设    计: 丛海旭               时    间: 2014-1-20
修    改:                      时    间: 
*********************************************************************/
bool SmallDropOut(void)
{
    static bool lb_Small;
    //小投点动开关打开并且参数设置合理
    if ((gs_Rec.SmallPluseSwitch) && (gs_Rec.SmallPluseHi != 0) && (gs_Rec.SmallPluseLow != 0))
    {
        if (gb_Sp3Flg)
        {
            if (lb_Small == 0)        //点动无效
            {
                if (gu32_Sys10ms - gu32_SmallPluseTimeBuf >= gs_Rec.SmallPluseLow * 10)
                {
                    lb_Small = true;
                    gu32_SmallPluseTimeBuf = gu32_Sys10ms;
                }
            }
            else                        //点动有效
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
            lb_Small = true;         //此处返回0不返回lb_Small_A,置位lb_Small_A = 1，为了进入点动输出时先输出有效电平。
            return false;
        }
    }
    else
        lb_Small = gb_Sp3Flg;
    
    return lb_Small;
}

/*********************************************************************
函数名称: bool Sp_Disc_State(u8 fu8_Item)
功    能: 加料和卸料开关量状态输出处理
说    明: 投料方式，夹袋到位，卸料门关门到位等逻辑
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-20
修    改:                      时    间: 
*********************************************************************/
bool Sp_Disc_State(u8 fu8_Item)
{
    bool lb_State = false;
    
    //投料方式处理 组合 单独
    bool  lb_Sp1Flg_Temp;
    bool  lb_Sp2Flg_Temp;
    bool  lb_Sp3Flg_Temp;
    
    lb_Sp1Flg_Temp = Feed_SP(SP1_STATE);
    lb_Sp2Flg_Temp = Feed_SP(SP2_STATE);
    lb_Sp3Flg_Temp = Feed_SP(SP3_STATE);
    
    switch (fu8_Item)
    {
        case SP1_STATE:
                //有斗模式定义了卸料门关门到位信号但是关门不到位不加料（停止状态不判断关门到位）
                if (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                    lb_State = (lb_Sp1Flg_Temp && (gb_DiscCloseOKFlg || (!gb_RunFlg) || (!gb_EnDiscCloseOKFlg))) == true ? true : false;
                else    //无斗定义了夹袋到位但是夹袋没有到位不加料（停止模式下不判断夹袋到位）
                    lb_State = (lb_Sp1Flg_Temp && (gb_PackOKFlg || (!gb_RunFlg) || (!gb_EnPackOKFlg))) == true ? true : false;
                break;
        case SP2_STATE:
                //有斗模式定义了卸料门关门到位信号但是关门不到位不加料（停止状态不判断关门到位）
                if (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                    lb_State = (lb_Sp2Flg_Temp && (gb_DiscCloseOKFlg || (!gb_RunFlg) || (!gb_EnDiscCloseOKFlg))) == true ? true : false;
                else    //无斗定义了夹袋到位但是夹袋没有到位不加料（停止模式下不判断夹袋到位）
                    lb_State = (lb_Sp2Flg_Temp && (gb_PackOKFlg || (!gb_RunFlg) || (!gb_EnPackOKFlg))) == true ? true : false;
                break;
        case SP3_STATE:
                //有斗模式定义了卸料门关门到位信号但是关门不到位不加料（停止状态不判断关门到位）
                if (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                    lb_State = (lb_Sp3Flg_Temp && SmallDropOut() && (gb_DiscCloseOKFlg || (!gb_RunFlg) || (!gb_EnDiscCloseOKFlg))) == true ? true : false;
                else    //无斗定义了夹袋到位但是夹袋没有到位不加料（停止模式下不判断夹袋到位）
                    lb_State = (lb_Sp3Flg_Temp && SmallDropOut() && (gb_PackOKFlg || (!gb_RunFlg) || (!gb_EnPackOKFlg))) == true ? true : false;
                break;
        case DISC_STATE:
                //有斗定义了夹袋到位但是夹袋不到位不卸料（停止状态不判断夹袋到位）
                if (gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B)
                    lb_State = (gb_DiscFlg && (gb_PackOKFlg || (!gb_RunFlg) || (!gb_EnPackOKFlg))) == true ? true : false;
                else
                    lb_State = gb_DiscFlg;
                break;
    }
    return lb_State;
}

