/*
Description:            定时锁机相关功能
Author:                 丛海旭
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
};  //2591~3313 素数

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

u8  gu8_ShutDownInTime;         //密码输入错误次数
u32 gu32_BuyerID;               //客户代码 00~99 对应不同的ID算法.
u32 gu32_ShutDownCode;          //定时锁机用户密码
u32 gu32_RandomID;              //随机数ID
u32 gu32_RandomCode;            //随机应急密码
u32 gu32_RandomUnlockCode;      //随机解锁密码
u32 gu32_Random30DayCode;       //随机30天密码
u32 gu32_Random60DayCode;       //随机60天密码
u32 gu32_ShutDownSwitch;        //定时锁机开关
u32 gu32_LeaveDays;             //剩余锁机天数
u32 gu32_CmpYear;               //锁机比较年
u32 gu32_CmpMonth;              //锁机比较月份
u32 gu32_CmpDate;               //锁机比较日期
bool gb_SysClosedFlg;           //系统已经锁机标志
bool gb_JudgeShutDownFlg;       //判断锁机标志位
u32 gu32_GetedRandom;           //随机数已经获取标志
bool gb_ReCmpFlg;               //已锁机标志，重新比较锁机时间



/*********************************************************************
函数名称: void Sys_Closed_Set(void)
功    能: 定时关机后的处理及设置
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2011-5-23
修    改:                      时    间: 
*********************************************************************/
void Sys_Closed_Set(void)
{
    bool lb_ShutDownSetFlg = false;
  
    BuzzerOff();
    while (gb_SysClosedFlg)     //如果系统已经关闭
    {
        gu32_KeyCode = Key_Deal();
        OPBuzzer();
        VFD_ClrDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);       //清显示缓存
        
        gu32_SystemState = SHUTDOWNSTATE;
        UpdataGrandShutCode();
        gb_KeyLockFlg = false;              //锁状态下,键盘锁定无效
        if (lb_ShutDownSetFlg)          //定时关机设置状态
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
                    ulParameter.ul = 0xFFFFFFFA;        //为兼容6位和7位密码输入十进制的0xFFFFFFFA最后一位是0，输入6位密码时最高位是0不影响6位密码的数值
                    gu8_DataInLength = 0;
                    break;
            }
            VFD_MainDisp_Str("    TE");
        }
        VFD_CopyDispArryToDispRam();         //将显示数组存入显示缓存
        VFD_WriteDispRamArry();                    //写显示缓存 
    }

    gu32_KeyCode = 0;
    gb_JudgeShutDownFlg = true;//置位判断完标志位
}

/*********************************************************************
函数名称:Count_Day()
功    能:计算年初到某天或者某天到年末的天数
入口参数:
调用程序:
返 回 值:
设    计:丛海旭               时    间: 2011-5-23
修    改:                     时    间:
*********************************************************************/
u16 Count_Day(u8 fu8_Year, u8 fu8_Month, u8 fu8_Date, bool flag)
{
    u8 i, p;
    u16 lu16_Days;

    if (LeapYear(fu8_Year))
        p = 1;
    else
        p = 0;

    if (flag)           //计算一年的开始到某天的天数
    {
        lu16_Days = fu8_Date;
        for (i = 1; i< fu8_Month; i++)
            lu16_Days += gu8_MonthDay[p][i];
    }
    else                //计算一年的某天到年末的天数
    {
        lu16_Days = gu8_MonthDay[p][fu8_Month] - fu8_Date;
        for (i = fu8_Month + 1;i <= 12; i++)
            lu16_Days += gu8_MonthDay[p][i];
    }
    return (lu16_Days);
}

/*********************************************************************
函数名称: void CmpDay(void)
功    能: 定时锁机比较剩余天数
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2011-5-23
修    改:                      时    间: 
*********************************************************************/
void CmpDay(void)
{
    u16 lu16_Day, lu16_Year;
  
    gb_SysClosedFlg = false;
    gb_ReCmpFlg = false;
    if ((gu32_ShutDownSwitch != 0) && (gu32_BuyerID!=0))     //如果定时关机功能打开
    {
        RTC_ReadDateTime(&SysDataTime);      //读取当前日期
        SysDataTime.year = (SysDataTime.year >> 4) * 10 + (SysDataTime.year & 0x0F);
        SysDataTime.month = (SysDataTime.month >> 4) * 10 + (SysDataTime.month & 0x0F);
        SysDataTime.date = (SysDataTime.date >> 4) * 10 + (SysDataTime.date & 0x0F);
        
        //获得最后一次比较日期
        gu32_CmpYear = FRAM_ReadDW(FMAddr_CmpYear);
        gu32_CmpMonth = FRAM_ReadDW(FMAddr_CmpMonth);
        gu32_CmpDate = FRAM_ReadDW(FMAddr_CmpDate);

        //读剩余天数
        gu32_LeaveDays = FRAM_ReadDW(FMAddr_LeaveDays);

        //比较剩余天数和(当前日期-最后一次比较日期)
        if (gu32_CmpYear < SysDataTime.year)
        {
            lu16_Day = Count_Day(gu32_CmpYear, gu32_CmpMonth, gu32_CmpDate, false);//计算一年的某天到年末的天数
            for (lu16_Year = gu32_CmpYear+1; lu16_Year<SysDataTime.year; lu16_Year++)
            {
                if (LeapYear(lu16_Year))
                    lu16_Day+=366;
                else
                    lu16_Day+=365;
            }
            lu16_Day += Count_Day(SysDataTime.year, SysDataTime.month, SysDataTime.date, true);//计算一年的开始到某天的天数
        }
        else if(gu32_CmpYear == SysDataTime.year)
        {
            lu16_Day = Count_Day(SysDataTime.year, SysDataTime.month, SysDataTime.date, true) - Count_Day(gu32_CmpYear, gu32_CmpMonth, gu32_CmpDate, true);
        }
        else
            lu16_Day=0;

        if (gu32_LeaveDays > lu16_Day)//如果设定的剩余天数大,则更新剩余天数,更新最后一次比较日期
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
        else//否则,剩余天数为0,关闭系统
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
函数名称: u32 GetShutItemValue(u8 fuc_Item)
功    能: 返回对应项目值
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-3
修    改:                      时    间: 
*********************************************************************/
u32 GetShutItemValue(u8 fuc_Item)
{
    u32 fu32_Value;
    switch (fuc_Item)
    {
        case SHUTDOWN_SWITCH:           //锁机开关
            fu32_Value = gu32_ShutDownSwitch;
            break;
        case SHUTDOWN_DAYNUM:           //剩余天数设置
            fu32_Value = gu32_LeaveDays;
            break;
        case SHUTDOWN_BUYID:            //用户ID
           fu32_Value = gu32_BuyerID;
           break;
        default:
            fu32_Value = 0;
            break;
    }
    return fu32_Value;
}

/*********************************************************************
函数名称: u16 GetShutDownPort(u8 fuc_Item)
功    能: 返回定时锁机参数存储地址
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2011-5-20
修    改:                      时    间: 
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
函数名称: void Update_ShutDown_data(u8 fu8_Type)
功    能: 更新定时锁机数据
说    明: 
入口参数: fu8_Type = 0 关闭锁机功能 1写入30天 2写入60天
返 回 值: 
设    计: 丛海旭               时    间: 
修    改:                      时    间: 
*********************************************************************/
void Update_ShutDown_data(u8 fu8_Type)
{
    RTC_ReadDateTime(&SysDataTime);      //读取当前日期
    gu32_CmpYear = (SysDataTime.year >> 4) * 10 + (SysDataTime.year & 0x0F);
    gu32_CmpMonth = (SysDataTime.month >> 4) * 10 + (SysDataTime.month & 0x0F);
    gu32_CmpDate = (SysDataTime.date >> 4) * 10 + (SysDataTime.date & 0x0F);
    FRAM_WriteDW(FMAddr_CmpYear, gu32_CmpYear);
    FRAM_WriteDW(FMAddr_CmpMonth, gu32_CmpMonth);
    FRAM_WriteDW(FMAddr_CmpDate, gu32_CmpDate); 

    if (fu8_Type > 2)
        fu8_Type=0;

    if(fu8_Type!=0)     //更改锁机天数为30天或60天
    {
        gu32_LeaveDays = 30 * fu8_Type;
        FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
        gb_SysClosedFlg = false;        //清除锁机标志
    }
    else        //关闭锁机功能
    {
        gu32_ShutDownSwitch = 0;
        gu32_LeaveDays = 65535;
        FRAM_WriteDW(FMAddr_ShutDownSwitch, gu32_ShutDownSwitch);
        FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
        gb_SysClosedFlg = false;        //清除锁机标志
        gb_JudgeShutDownFlg = true;
    }
}

/*********************************************************************
函数名称: u32 GetRandom(void)
功    能: 获取随机数
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2011-5-20
修    改:                      时    间: 
*********************************************************************/
u32 GetRandom(void)
{
    srand(gu32_Sys10ms);
    return((u32)(129643 * (u32)rand() + 32189) % 1000000);
}

/*********************************************************************
函数名称: bool GradeShutCodeEQ(void)
功    能: 产生合理的随机密码，随机解锁密码，随机30、60天密码，应急密码
说    明: 
入口参数: 
返 回 值: 1密码不合理，重新计算
设    计: 丛海旭               时    间: 2011-5-20
修    改:                      时    间: 
*********************************************************************/
bool GradeShutCodeEQ(void)
{
    if (gu32_BuyerID == 99)
    {
        gu32_RandomCode = (gu32_RandomID * 3313 + 107999) % 998989;         //获得应急密码
        gu32_Random30DayCode = (gu32_RandomID * 3221 + 107071) % 998989;
        gu32_Random60DayCode = (gu32_RandomID * 3137 + 106367) % 998989;
        gu32_RandomUnlockCode = (gu32_RandomID * 3041 + 104827) % 998989;
    }
    else
    {
        gu32_RandomCode  =(gu32_RandomID * IDSFA[gu32_BuyerID] + IDSFB[gu32_BuyerID]) % 1000000;     //获得随机密码
        if (gu32_RandomCode > 999800)
            return true;
        gu32_Random30DayCode = (gu32_RandomCode + 30) % 1000000;          //读取解锁密码
        gu32_Random60DayCode = (gu32_RandomCode + 60) % 1000000;           //读取30天密码
        gu32_RandomUnlockCode = (gu32_RandomCode + 100) % 1000000;          //读取60天密码
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
函数名称: void UpdataGrandShutCode(void)
功    能: 更新锁机密码
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2011-5-20
修    改:                      时    间: 
*********************************************************************/
void UpdataGrandShutCode(void)
{
    if (gu32_BuyerID == 99)
        gu32_RandomCode = (gu32_RandomID * 3313 + 107999) % 998989;//获得随机密码
    else
        gu32_RandomCode = (gu32_RandomID * IDSFA[gu32_BuyerID] + IDSFB[gu32_BuyerID]) % 1000000;//获得随机密码

    if ((gu32_ShutDownSwitch != 0) && (gu32_LeaveDays == 0))
    {
        if (gu32_BuyerID == 99)
        {
            gu32_Random30DayCode = (gu32_RandomID * 3221 + 107071) % 998989;//读取一级随机密码
            gu32_Random60DayCode = (gu32_RandomID * 3137 + 106367) % 998989;//读取二级随机密码
            gu32_RandomUnlockCode = (gu32_RandomID * 3041 + 104827) % 998989;//读取三级随机密码
        }
        else
        {
            gu32_Random30DayCode = (gu32_RandomCode + 30) % 1000000;//读取一级随机密码
            gu32_Random60DayCode = (gu32_RandomCode + 60) % 1000000;//读取二级随机密码
            gu32_RandomUnlockCode = (gu32_RandomCode + 100) % 1000000;//读取三级随机密码
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
函数名称: void Key_ShutdownState(void)
功    能: 定时锁机的相关处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-3
修    改:                      时    间: 
*********************************************************************/
void Key_ShutdownState(void)
{
    static bool sb_SuperCodeFlg = false;        //输入的是超级密码标志
    u8 luc_DataLen = 0;      //输入数据位数
    sTime SysDataTime;
    
    if (gu32_KeyCode == K_RIGHT)     //→键显示切换到下一项
    {
        gb_FirstNumKeyFlg = true;
        if (gu8_Item != SHUTDOWN_CHECKCODE && gu8_Item != SHUTDOWN_UNLOCK)     //密码输入状态不能按→键
            gu8_Item++;
        if (gu8_Item == SHUTDOWN_DAYNUM)        //→键不能进入锁机剩余天数设置
            gu8_Item++;
        if (gu8_Item > SHUTDOWN_INPUTCODE + sb_SuperCodeFlg)
            gu8_Item = SHUTDOWN_SWITCH;
        ulParameter.ul = GetShutItemValue(gu8_Item);
    }
    
    //构造每一项的显示数值
    switch (gu8_Item)
    {
        case SHUTDOWN_CHECKCODE:        //密码输入
            gb_FirstNumKeyFlg = false;
            luc_DataLen = 7;
            break;
        case SHUTDOWN_SWITCH:           //锁机开关
            ulParameter.ul = Key_IncInput(ulParameter.ul, 0, 1);      //两项切换，用↑键修改
            break;
        case SHUTDOWN_DAYNUM:           //剩余天数设置
            luc_DataLen = 5;
            gb_SetFlg = false;
            break;
        case SHUTDOWN_INPUTCODE:        //密码修改
            gb_FirstNumKeyFlg = false;
            if (gu32_KeyCode == K_SET)           //进入密码设置状态
                gb_SetFlg = true;
            if (gb_SetFlg)
            {
                if (gu32_KeyCode == K_ESC)       //退出密码设置状态
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
        case SHUTDOWN_BUYID:            //用户ID
            luc_DataLen = 2;
            gb_SetFlg = false;
        default:
            break;
    }
    
    //数据输入
    ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
    
    //每一项下的按键处理程序
    switch(gu32_KeyCode)
    {
        case K_ESC:             //退出键处理
            gb_FlashFlg = false;
            if (gu8_Item == SHUTDOWN_DAYNUM)
                gu8_Item = SHUTDOWN_SWITCH;
            else
                gu32_SystemState = STOPSTATE;
            break;
        case K_ENTER:           //确认键处理
            gu8_DataInLength = 0;
            switch(gu8_Item)
            {
                case SHUTDOWN_CHECKCODE:     //密码输入
                    gu8_ShutDownInTime++;
                    sb_SuperCodeFlg = false;
                    if (gu32_BuyerID == 0)
                    {
                        gu32_ShutDownCode = 0xFFEFFEFE;     //如果密码定时关机功能关闭,则用户密码为不可输入值.
                        gu32_RandomCode = 0xF2EFFEFE;       //应急密码为不可输入值.
                    }
    
                    if ((ulParameter.ul == gu32_RandomUnlockCode)||(ulParameter.ul == gu32_Random30DayCode)||(ulParameter.ul == gu32_Random60DayCode))
                    {
                        if (ulParameter.ul == gu32_RandomUnlockCode)
                            Update_ShutDown_data(0);
                        else if(ulParameter.ul == gu32_Random30DayCode)
                            Update_ShutDown_data(1);
                        else
                            Update_ShutDown_data(2);
    
                        gu8_ShutDownInTime = 0;         //清除密码计数器
                        ulParameter.ul = 0;             //清下一项参数值
                        gb_SetFlg=false;//非设定密码状态
                        
                        do
                        {
                            gu32_RandomID = GetRandom();
                        }while(GradeShutCodeEQ());
                        gu32_GetedRandom = 0x55;
                        FRAM_WriteDW(FMAddr_GetedRandom, gu32_GetedRandom);
                        FRAM_WriteDW(FMAddr_RandomID, gu32_RandomID);
                        UpdataGrandShutCode();      //更新密码
                        
                        gu8_Item = SHUTDOWN_UNLOCK;     //解锁界面
                        gu32_TimeDelay = gu32_Sys10ms;
                        BuzzerStart(100);
                        return;
                    }
                    //超级密码或用户密码
                    else if ((ulParameter.ul == gu32_ShutDownCode) || (ulParameter.ul == SUPERSHUTCODE))
                    {
                        if(ulParameter.ul== SUPERSHUTCODE)
                            sb_SuperCodeFlg = true;
                        gu8_ShutDownInTime = 0;         //清除密码计数器
                        ulParameter.ul = 0;             //清下一项参数值
                        gb_SetFlg = false;                  //非设定密码状态
                    }
                    //应急密码
                    else if (ulParameter.ul == gu32_RandomCode)
                    {
                        gu8_ShutDownInTime=0;       //清除密码计数器
                        do
                        {
                            gu32_RandomID = GetRandom();
                        }while(GradeShutCodeEQ());
                        gu32_GetedRandom=0x55;
                        FRAM_WriteDW(FMAddr_GetedRandom, gu32_GetedRandom);
                        FRAM_WriteDW(FMAddr_RandomID, gu32_RandomID);
                        UpdataGrandShutCode();      //更新密码
                    }
                    else if (gu8_ShutDownInTime >= 3)
                    {
                        ErrorDeal(4, 0);        //显示error4
                        Disp_Error();
                        VFD_CopyDispArryToDispRam();         //将显示数组存入显示缓存
                        VFD_WriteDispRamArry();                    //写显示缓存 
                        while(1);
                    }
                    else        //密码输入错误
                    {
                        ErrorDeal(0, 100);
                        ulParameter.ul = 0xFFFFFFFA;
                        return;         // 错误
                    }
                    break;
                case SHUTDOWN_SWITCH:           //锁机开关
                    FRAM_WriteDW(GetShutDownPort(gu8_Item), ulParameter.ul);
                    if (gu32_ShutDownSwitch == 0)       //定时锁机开关关闭后要将剩余天数写为65535
                    {
                        gu32_LeaveDays = 65535;
                        FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
                    }
                    break;
                case SHUTDOWN_DAYNUM:
                    if (ulParameter.ul > 65535)     //锁机天数最大65535
                    {
                        ErrorDeal(0, 100);
                        return;         // 错误
                    }
                    else
                    { 
                        FRAM_WriteDW(GetShutDownPort(gu8_Item), ulParameter.ul);
                        RTC_ReadDateTime(&SysDataTime);      //读取当前日期
                        gu32_CmpYear = (SysDataTime.year >> 4) * 10 + (SysDataTime.year & 0x0F);
                        gu32_CmpMonth = (SysDataTime.month >> 4) * 10 + (SysDataTime.month & 0x0F);
                        gu32_CmpDate = (SysDataTime.date >> 4) * 10 + (SysDataTime.date & 0x0F);
                        FRAM_WriteDW(FMAddr_CmpYear, gu32_CmpYear);
                        FRAM_WriteDW(FMAddr_CmpMonth, gu32_CmpMonth);
                        FRAM_WriteDW(FMAddr_CmpDate, gu32_CmpDate);           //保存比较日期
                    }
                    break;
                case SHUTDOWN_INPUTCODE:
                    if (gb_SetFlg == true)
                    {
                        gu8_ShutDownInTime++;
                        if (gu8_ShutDownInTime >= 2)
                        {
                            if (ulParameter.ul == gu32_DataTemp)         //两次输入的密码一致
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
                            gu32_DataTemp = ulParameter.ul;      //暂存第一次密码设置值
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
            //参数越界处理，使用超级密码进入可以设置用户ID
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
函数名称: void Disp_ShutdownState(void)
功    能: 定时锁机显示缓存处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-3
修    改:                      时    间: 
*********************************************************************/
void Disp_ShutdownState(void)
{
    gb_FlashFlg = false;
    
    switch (gu8_Item)
    {
        case SHUTDOWN_CHECKCODE:        //密码输入
            Disp_InputCode();
            gb_FlashFlg = true;
            break;
        case SHUTDOWN_SWITCH:           //锁机开关
            Disp_OnOff(ulParameter.ul);           //显示开关
            VFD_AuxDisp_Str("ATC");
            break;
        case SHUTDOWN_DAYNUM:           //剩余天数设置
            gb_FlashFlg = true;
            Disp_Main_Data(ulParameter.ul, 0, 5, false, false);       //显示值
            VFD_AuxDisp_Str("DAY");
            break;
        case SHUTDOWN_INPUTCODE:        //密码修改
            if (gb_SetFlg == true)
                gb_FlashFlg = true;
            Disp_InputCode();           //密码输入显示处理
            break;
        case SHUTDOWN_BUYID:            //用户ID
            gb_FlashFlg = true;
            Disp_Main_Data(ulParameter.ul, 0, 2, false, false);       //显示值
            VFD_AuxDisp_Str("ID ");
            break;
        case SHUTDOWN_UNLOCK:           //解锁后的显示界面
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
    Flash_MainDisp(0x01);                //闪烁处理
}

/********************************************************************
函 数 名:Auto_ShutDown()
功    能:自动关机程序
说    明:判断自动关机日期是否到,到则自动关机
入口参数:
返 回 值:
设    计:丛海旭       日    期:2011-5-23
修    改:             日    期:
***********************************************************************/
void Auto_ShutDown(void)
{
    sTime ls_Time;
    //如果定时关机开关为0,或者密码定时关机客户码为0则返回，不做定时锁机判断
    if (gu32_ShutDownSwitch == 0 || gu32_BuyerID==0)
        return;             //返回
    RTC_ReadDateTime(&ls_Time);      //读取当前日期
    if (ls_Time.hour==0 || gu32_LeaveDays == 0)     //如果时钟为0
    {
        if(gu32_LeaveDays == 0)     //如果剩余天数已经为0
        {
            FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
            VFD_ClrDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);       //清显示缓存
            IO_CloseOut();
            VFD_MainDisp_Str("    TE");
            VFD_CopyDispArryToDispRam();         //将显示数组存入显示缓存
            VFD_WriteDispRamArry();                    //写显示缓存 
            BuzzerOff();
            while(1);//锁机
        }

        if (gb_JudgeShutDownFlg == false)       //如果判断完成标志为0
        {
            gb_JudgeShutDownFlg = true;//置位判断完成标志位
            gu32_LeaveDays--;
            if (gu32_LeaveDays == 0)//如果剩余天数减1为0
            {
                FRAM_WriteDW(FMAddr_LeaveDays, gu32_LeaveDays);
                VFD_ClrDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);       //清显示缓存
                IO_CloseOut();
                VFD_MainDisp_Str("    TE");
                VFD_CopyDispArryToDispRam();         //将显示数组存入显示缓存
                VFD_WriteDispRamArry();                    //写显示缓存 
                BuzzerOff();
                while(1);//锁机
            }
        }
    }
    else
      gb_JudgeShutDownFlg = false; //判断完成标志为0
}
