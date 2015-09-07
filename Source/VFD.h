#ifndef _VFD_H
#define _VFD_H

#include "71x_type.h"


//显示段码，字母不区分大小写，大小写相同，显示规则见公司“显示字符对照表.bmp”
/*主显示码译码关系
DP|G|A|F|E|C|D|B
 7|6|5|4|3|2|1|0

VFD引脚与显示芯片16312对应的关系如下：
SG1 -P10
SG2 -P5
SG3 -P7
SG4 -P6
SG5 -P9
SG6 -P11
SG7 -P8
SG8 -P4
SG9 -P2
SG10-P3
SG11-P1
 */
#define     SEG_0   0x3F
#define     SEG_1   0x05
#define     SEG_2   0x6B
#define     SEG_3   0x67
#define     SEG_4   0x55
#define     SEG_5   0x76
#define     SEG_6   0x7E
#define     SEG_7   0x25
#define     SEG_8   0x7F
#define     SEG_9   0x77
#define     SEG_A   0x7D
#define     SEG_a   0x7D
#define     SEG_B   0x5E
#define     SEG_b   0x5E
#define     SEG_C   0x3A
#define     SEG_c   0x3A
#define     SEG_D   0x4F
#define     SEG_d   0x4F
#define     SEG_E   0x7A
#define     SEG_e   0x7A
#define     SEG_F   0x78
#define     SEG_f   0x78
#define     SEG_G   0x3E
#define     SEG_g   0x3E
#define     SEG_H   0x5D
#define     SEG_h   0x5D
#define     SEG_I   0x04
#define     SEG_i   0x04
#define     SEG_J   0x07
#define     SEG_j   0x07
#define     SEG_K   0x7C
#define     SEG_k   0x7C
#define     SEG_L   0x1A
#define     SEG_l   0x1A
#define     SEG_M   0x2C
#define     SEG_m   0x2C
#define     SEG_N   0x4C
#define     SEG_n   0x4C
#define     SEG_O   0x4E
#define     SEG_o   0x4E
#define     SEG_P   0x79
#define     SEG_p   0x79
#define     SEG_Q   0x75
#define     SEG_q   0x75
#define     SEG_R   0x48
#define     SEG_r   0x48
#define     SEG_S   0x76
#define     SEG_s   0x76
#define     SEG_T   0x5A
#define     SEG_t   0x5A
#define     SEG_U   0x1F
#define     SEG_u   0x1F
#define     SEG_V   0x0E
#define     SEG_v   0x0E
#define     SEG_W   0x53
#define     SEG_w   0x53
#define     SEG_X   0x54
#define     SEG_x   0x54
#define     SEG_Y   0x57
#define     SEG_y   0x57
#define     SEG_Z   0x6B
#define     SEG_z   0x6B
#define     SEG_BLK 0x00
#define     SEG_SIG 0x40            //-
#define     SEG_1LINE   0x40        //-
#define     SEG_2LINE   0x42        //=
#define     SEG_3LINE   0x62        //≡
#define     SEG_TOPLINE 0x20        //≡

//按键值
#define     K_0        0x00000800
#define     K_1        0x00000100
#define     K_2        0x00001000
#define     K_3        0x00000001
#define     K_4        0x00000010
#define     K_5        0x00000200
#define     K_6        0x00000400
#define     K_7        0x00004000
#define     K_8        0x00000004
#define     K_9        0x00000040
#define     K_ZERO     0x00000020
#define     K_INC      0x00002000
#define     K_RIGHT    0x00008000
#define     K_ESC      0x00000008
#define     K_ENTER    0x00000080
#define     K_SET      0x00000002
#define     K_NONE     0x00000000
//长按键值，分2秒钟和5秒钟长按
#define     K_2S       0x00020000
#define     K_5S       0x00050000
//2秒长按键值
#define     K_0_2S        (K_0|K_2S)
#define     K_1_2S        (K_1|K_2S)    
#define     K_2_2S        (K_2|K_2S)    
#define     K_3_2S        (K_3|K_2S)    
#define     K_4_2S        (K_4|K_2S)    
#define     K_5_2S        (K_5|K_2S)    
#define     K_6_2S        (K_6|K_2S)    
#define     K_7_2S        (K_7|K_2S)    
#define     K_8_2S        (K_8|K_2S)    
#define     K_9_2S        (K_9|K_2S)    
#define     K_ZERO_2S     (K_ZERO|K_2S) 
#define     K_INC_2S      (K_INC|K_2S)  
#define     K_RIGHT_2S    (K_RIGHT|K_2S)
#define     K_ESC_2S      (K_ESC|K_2S)  
#define     K_ENTER_2S    (K_ENTER|K_2S)
#define     K_SET_2S      (K_SET|K_2S)  
//5秒长按键值
#define     K_0_5S        (K_0|K_5S)
#define     K_1_5S        (K_1|K_5S)    
#define     K_2_5S        (K_2|K_5S)    
#define     K_3_5S        (K_3|K_5S)    
#define     K_4_5S        (K_4|K_5S)    
#define     K_5_5S        (K_5|K_5S)    
#define     K_6_5S        (K_6|K_5S)    
#define     K_7_5S        (K_7|K_5S)    
#define     K_8_5S        (K_8|K_5S)    
#define     K_9_5S        (K_9|K_5S)    
#define     K_ZERO_5S     (K_ZERO|K_5S) 
#define     K_INC_5S      (K_INC|K_5S)  
#define     K_RIGHT_5S    (K_RIGHT|K_5S)
#define     K_ESC_5S      (K_ESC|K_5S)  
#define     K_ENTER_5S    (K_ENTER|K_5S)
#define     K_SET_5S      (K_SET|K_5S)  


//单位
#define     UNIT_g      0
#define     UNIT_kg     1
#define     UNIT_t      2
#define     UNIT_lb     3
#define     UNIT_N      4
#define     UNIT_PCS    5
#define     UNIT_none   6




extern const u8 Value_To_SEG[];
extern u8 gu8_VFDDispRamArray[22];
extern u8 gu8_VFDLedRam;
extern u8 gu8_MainDispArray[6];     //主显示缓存数组
extern u8 gu8_AuxDispArray[3];      //副显示数组


//extern void Disp_All(u8 dispdata,u8 addr,u8 n);
extern void VFD_Init(void);
extern void VFD_WriteDispRamArry(void);
extern void VFD_MainDisp_u32(u32 fu32_Data);
extern void VFD_DispAll(u32 fu32_ModelSet, u32 fu32_Logo);
extern u32 VFD_ReadKey(void);
extern void VFD_FillDispRam(u32 fu32_ModelSet, u32 fu32_Logo);
extern void VFD_ClrDispRam(u32 fu32_ModelSet, u32 fu32_Logo);
extern void VFD_MainDisp_u32(u32 fu32_Data);
extern void VFD_MainDisp_Str(char* fu8p_Arry);
extern void VFD_MainDisp_ASCII(u8* fu8_Arry);
extern void VFD_AuxDisp_u32(u32 fu32_Data);
extern void VFD_AuxDisp_Str(char* fu8p_Arry);
extern void VFD_CopyAuxDispArryToDispRam(void);
extern void VFD_CopyMainDispArryToDispRam(void);
extern void VFD_CopyDispArryToDispRam(void);
extern void VFD_UnitDisp(u32 fu32_Data);
extern void VFD_FlgDisp(u32 fu32_Data);
extern void VFD_MainSigDisp(bool fb_SigFlg);
extern void VFD_FlgDisp_ZERO(bool fb_On);
extern void VFD_FlgDisp_STAB(bool fb_On);
extern void VFD_FlgDisp_RUN(bool fb_On);
extern void VFD_FlgDisp_SUM(bool fb_On);
extern void VFD_FlgDisp_OVER(bool fb_On);
extern void VFD_FlgDisp_UNDER(bool fb_On);
extern void VFD_FlgDisp_SP1(bool fb_On);
extern void VFD_FlgDisp_SP2(bool fb_On);
extern void VFD_FlgDisp_SP3(bool fb_On);
extern void VFD_FlgDisp_DISC(bool fb_On);
extern void VFD_FlgDisp_NZ(bool fb_On);
extern void VFD_FlgDisp_FILL(bool fb_On);
extern void VFD_FlgDisp_HILIM(bool fb_On);
extern void VFD_FlgDisp_HI(bool fb_On);
extern void VFD_FlgDisp_GO(bool fb_On);
extern void VFD_FlgDisp_LO(bool fb_On);
extern void VFD_FlgDisp_LOLIM(bool fb_On);
extern void VFD_FlgDisp_HOLD(bool fb_On);
extern u8 VFD_KeyCode_To_Value(u32 ful_KeyCode);
extern void VFD_LEDDisp(bool fb_Gross, bool fb_Net, bool fb_Tare, bool fb_Pack);
extern void VFD_CopyFlgDispArryToDispRam(void);

#endif
