#ifndef _SUM_H
#define _SUM_H

#include "71x_type.h"

extern u32 gu32_DebugSumNum;
extern u32 gu32_DebugSumNumTemp;   //打印中使用
extern u64 gu64_SumWt;                //累计重量 最大15位
extern u32 gu32_SumNum;               //累计次数
extern u32 gu32_SumWt_Rec[21];             //配方0-9累计重量
extern u32 gu32_SumNum_Rec[21];            //配方0-9累计次数

//累计重量小数点和单位转换后的数据变量
extern u32 gu32_SumWt;
extern u32 gu32_SumWtUnit;             //累计单位
extern u32 gu32_SumWtPoint;            //累计小数点
//extern u32 gu32_SumWt_Rec[21];
//extern u32 gu32_SumWtUnit_Rec[21];             //累计单位
//extern u32 gu32_SumWtPoint_Rec[21];            //累计小数点


extern u8 gu8_SumCheckInTime;      //累计查询密码输入错误次数


extern void DiscSumDeal(void);
extern void ClrSum(void);
extern void Disp_SumState(void);
extern void Key_SumState(void);
extern bool GetSumWt_u32(u64 fu64_SumWt,    //需要转换的当前8字节重量数据
                         u32 fu32_Unit,     //当前重量对应的单位
                         u32 fu32_Point,    //当前重量对应的小数点
                         u32* fu32p_SumWt,  //得到的4字节目标重量
                         u32* fu32p_Unit,   //目标重量的单位
                         u32* fu32p_Point   //目标重量的小数点
                        );
extern void ClrSum_Rec(u8 fu8_Rec);

#endif
