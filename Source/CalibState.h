#ifndef _CALIBSTATE_H
#define _CALIBSTATE_H

#include "71x_type.h"


#define SEN1mVMAX 17000    //1mV/V mV(max)/10
#define SEN2mVMAX 27000    //2mV/V mV(max)/10
#define SEN3mVMAX 37000    //3mV/V mV(max)/10
#define ADMAX  524288   //AD(max)/10        19位AD最大524288码


struct CALIB
{
    u32 Unit;
    u32 Point;
    u32 Div;
    u32 Cap;
    u32 Sensor;
    u32 Zero;
    float ADK;
};
extern struct CALIB gs_Cal;
extern u8 gu8_CalibInTime;
extern u32 gu32_TimeDelay;             //一般的延时计数器
extern u32 gu32_CalCode;
extern u32 gu32_DataTemp;
extern u32 gu32_CalDispWt;     //增益校准输入显示重量缓存

extern void Key_CalibState(void);
extern void Disp_CalibState(void);
extern u32 AdToMv(u32 ful_AdCode);
extern u32 MvToAd(u32 ful_MvData);

#endif
