/*************************************************
Project:                GM8804C-2_ARM
File name:              VFD.c
Description:            VFD��ʾ�������
Author:                 �Ժ���
Version:                1.0
Date:                   2013-12-5
Others:                 IC:16312
History:
*************************************************/
#include "include.h"
//����������������16312оƬ��˵
//��16312���
#define VFD_DOUT_READ   GPIO_BitRead(GPIO1,9)            //����
//д16312����˿�
#define VFD_DIN_CLR     GPIO_BitWrite(GPIO1,10,0)
#define VFD_DIN_SET     GPIO_BitWrite(GPIO1,10,1)
//д16312ʱ�Ӷ˿�
#define VFD_CLK_CLR     GPIO_BitWrite(GPIO1,13,0)        //ʱ��
#define VFD_CLK_SET     GPIO_BitWrite(GPIO1,13,1)
//д16312Ƭѡ�˿�
#define VFD_CS_CLR      GPIO_BitWrite(GPIO1,14,0)        //Ƭѡ
#define VFD_CS_SET      GPIO_BitWrite(GPIO1,14,1)

/* 
��ʾ��ʽ����ָ��
MSB                    LSB
0  0  -  -  -  b2  b1  b0
b2/b1/b0 ѡ����ʾ��ʽ
0  0  0     4λ��16��
0  0  1     5λ��16��
0  1  0     6λ��16��
0  1  1     7λ��15��
1  0  0     8λ��14��
1  0  1     9λ��13��
1  1  0     10λ��12��
1  1  1     11λ��11��

�����趨ָ��
MSB                    LSB
0  1  -  -  b3  b2  b1  b0
b1/b0 �趨���ݶ�д��ʽ
0  0    д��������ʾ�洢��
0  1    д������LED��
1  0    ��������
1  1    ��SW����
b2 �趨��ַ������ʽ����ʾ��������
0   ����д����������ַ
1   �̶���ַ
b3 �趨����ģʽ
0   ��������
1   ����ģʽ

��ַ�趨ָ��
MSB                     LSB
1  1  -  b4  b3  b2  b1  b0
b4/b3/b2/b1/b0      ��ַ��00H~15H��

��ʾ����ָ��
MSB                     LSB
1  0  -  -  b3  b2  b1  b0
b2/b1/b0 ����ȼ��趨
0  0  0     �趨�������Ϊ1/16
0  0  1     �趨�������Ϊ2/16
0  1  0     �趨�������Ϊ4/16
0  1  1     �趨�������Ϊ10/16
1  0  0     �趨�������Ϊ11/16
1  0  1     �趨�������Ϊ12/16
1  1  0     �趨�������Ϊ13/16
1  1  1     �趨�������Ϊ14/16
b3 ͨ/����ʾ
0   ��ʾ�ϣ���ɨ�������
1   ��ʾͨ

LED�˿�
MSB                     LSB
-  -  -  -  b3  b2  b1  b0
b3 LED4 TARE
b2 LED3 GROSS
b1 LED2 PACK
b0 LED1 NET
Ϊ0ʱLED��


������ʾ����
����1���趨��ʾ��ʽ
����2���趨����
����3���趨��ַ
����1~n��������ʾ���ݣ����22�ֽڣ�
����4��������ʾ

����ָ����ַ
����1���趨����
����2���趨��ַ
���ݣ���ʾ����

*/


#define TEC16312_DISPMODE       B0000_0111          //��ʾ��ʽ 11λ11��
#define TEC16312_DATA_DISP      B0100_0000          //�����趨���� д��ʾ
#define TEC16312_DATA_LED       B0100_0101          //�����趨���� дLED
#define TEC16312_DATA_RKEY      B0100_0110          //�����趨���� ������
#define TEC16312_ADDRESS        B1100_0000          //��ַ�趨ָ���00H��ʼ
#define TEC16312_BRIGHT         B1000_1111          //��ʾ����ָ�� ����ȼ���ߣ���ʾͨ



 const u8 Value_To_SEG[]
      ={
        //0~9
        SEG_0,SEG_1,SEG_2,SEG_3,SEG_4,SEG_5,SEG_6,SEG_7,SEG_8,SEG_9,
        //A~G
        SEG_A,SEG_B,SEG_C,SEG_D,SEG_E,SEG_F,SEG_G,
        //H~N
        SEG_H,SEG_I,SEG_J,SEG_K,SEG_L,SEG_M,SEG_N,
        //O~T
        SEG_O,SEG_P,SEG_Q,SEG_R,SEG_S,SEG_T,
        //U~Z
        SEG_U,SEG_V,SEG_W,SEG_X,SEG_Y,SEG_Z,
        //�հ�
        SEG_BLK
       };
u8 gu8_VFDDispRamArray[22];          //16312����ʾRAM���飬11�Σ�ÿ��2�ֽ�
u8 gu8_VFDLedRam;       //16312��LED��RAM����
u8 gu8_MainDispArray[6];     //����ʾ����
u8 gu8_AuxDispArray[3];      //����ʾ����
u8 gu8_UnitDispArray[2];     //��λ��ʾ����
u8 gu8_FlgDispArray[6];      //��־����ʾ����



//ASCII���Ӧ�Ķ������һЩ��ֵķ��Ų�����ʾ����Ҫ��ʾ��ĸ���ֺ�-�ȼ򵥷���
const u8 ASCII_To_SEG[]=
 {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    //0x00~0x0F
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    //0x10~0x1F
//                   #                                                     -
    0x00,0x00,0x00,SEG_3LINE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,SEG_1LINE,0x00,0x00,    //0x20~0x2F
//   0     1     2     3     4     5     6     7     8     9                     =     
    SEG_0,SEG_1,SEG_2,SEG_3,SEG_4,SEG_5,SEG_6,SEG_7,SEG_8,SEG_9,0x00,0x00,0x00,SEG_2LINE,0x00,0x00,    //0x30~0x3F
//        A     B     C     D     E     F     G     H     I     J     K     L     M     N     O
    0x00,SEG_A,SEG_B,SEG_C,SEG_D,SEG_E,SEG_F,SEG_G,SEG_H,SEG_I,SEG_J,SEG_K,SEG_L,SEG_M,SEG_N,SEG_O,    //0x40~0x4F
//   P     Q     R     S     T     U     V     W     X     Y     Z                         _
    SEG_P,SEG_Q,SEG_R,SEG_S,SEG_T,SEG_U,SEG_V,SEG_W,SEG_X,SEG_Y,SEG_Z,0x00,0x00,0x00,0x00,0x02,    //0x50~0x5F
//        a     b     c     d     e     f     g     h     i     j     k     l     m     n     o
    0x00,SEG_A,SEG_B,SEG_C,SEG_D,SEG_E,SEG_F,SEG_G,SEG_H,SEG_I,SEG_J,SEG_K,SEG_L,SEG_M,SEG_N,SEG_O,    //0x60~0x6F
//    p    q     r     s     t     u     v     w     x     y     z
    SEG_P,SEG_Q,SEG_R,SEG_S,SEG_T,SEG_U,SEG_V,SEG_W,SEG_X,SEG_Y,SEG_Z,0x00,0x00,0x00,0x00,0x00,    //0x70~0x7F
 };

/*********************************************************************
��������: void VFD_SendByte(u8 outdata)
��    ��: д��16312һ�ֽ�����
˵    ��: �ײ�����
��ڲ���: outdata = ���͵�����
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-5
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_SendByte(u8 outdata)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        VFD_CLK_CLR;
        __nop();__nop();__nop();
        (outdata & 0x01) ? VFD_DIN_SET : VFD_DIN_CLR;
        __nop();__nop();__nop();
        VFD_CLK_SET;
        __nop();__nop();__nop();
        outdata >>= 1;
    }
}

/*********************************************************************
��������: u8 VFD_ReceiveByte(void)
��    ��: ��16312����һ�ֽ�����
˵    ��: �ײ�����
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-5
��    ��:                      ʱ    ��: 
*********************************************************************/
u8 VFD_ReceiveByte(void)
{
    u8 i;
    u8 indata = 0;
    for (i = 0; i < 8; i++)
    {
        VFD_CLK_SET;
        __nop();__nop();__nop();
        indata >>= 1;
        __nop();__nop();__nop();

        VFD_CLK_CLR;
        __nop();__nop();__nop();
        __nop();__nop();__nop();

        if(VFD_DOUT_READ == true)
            indata |= 0x80;
        else
            __nop();__nop();__nop();
    }
    return indata;
}

/*********************************************************************
��������: void VFD_WriteByte(u8 fu8_Data)
��    ��: VFDд��һ�ֽ����ݣ���ƬѡCS�߼�
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-9
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_WriteByte(u8 fu8_Data)
{
    VFD_CS_CLR;
    VFD_SendByte(fu8_Data);
    VFD_CS_SET;
}

/*********************************************************************
��������: void VFD_Init(void)
��    ��: VFD��ʾ�ĳ�ʼ��
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-6
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_Init(void)
{
    //���� ��׼TTL���룬GPIO_IN_TRI_CMOS����ģ������
    GPIO_Config(GPIO1,(1<<9),GPIO_IN_TRI_TTL);
    //��� �������
    GPIO_Config(GPIO1,(1<<10),GPIO_OUT_PP);
    //ʱ�� �������GPIO_OUT_PP
    GPIO_Config(GPIO1,(1<<13),GPIO_OUT_PP);
    //Ƭѡ �������
    GPIO_Config(GPIO1,(1<<14),GPIO_OUT_PP);

    VFD_WriteByte(TEC16312_DISPMODE);  //11λ11��
    VFD_WriteByte(TEC16312_BRIGHT);    //�������
}

/*********************************************************************
��������: void VFD_MainDisp_u32(u32 fu32_Data)
��    ��: ��Ҫ��ʾ����������תΪSEG�����������ʾ����
˵    ��: ���6λ
��ڲ���: fu32_Data=��ʾ����
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-9
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_MainDisp_u32(u32 fu32_Data)
{
    u8 i;
    fu32_Data %= 1000000;    //����������6λ���ݵ�ת��
    BIN4toNBCD(fu32_Data, gu8_MainDispArray, 6);
    for (i = 0; i < 6; i++)         //����ֵת������ʾ����
        gu8_MainDispArray[i] = Value_To_SEG[gu8_MainDispArray[i]];
}

/*********************************************************************
��������: void VFD_MainDisp_Str(char* fu8p_Arry)
��    ��: ��Ҫ��ʾ���ַ�������תΪSEG�����������ʾ����
˵    ��: ���6λ
��ڲ���: fu32_Data=��ʾ����
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-9
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_MainDisp_Str(char* fu8p_Arry)
{
    u8 i;
    
    for (i = 0; (i < 6) && ((*fu8p_Arry) != '\0'); i++, fu8p_Arry++)
        gu8_MainDispArray[i] = ASCII_To_SEG[*fu8p_Arry];
}

/*********************************************************************
��������: void VFD_MainDisp_ASCII(u8* fu8_Arry)
��    ��: ��Ҫ��ʾ��ASCII����������תΪSEG�����������ʾ����
˵    ��: ���6λ
��ڲ���: fu8_Arry=��ʾ��������
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-23
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_MainDisp_ASCII(u8* fu8_Arry)
{
    u8 i;
    for (i = 0; i <= 5; i++)
        fu8_Arry[i] = ASCII_To_SEG[fu8_Arry[i]];
}
/*********************************************************************
��������: void VFD_AuxDisp_u32(u32 fu32_Data)
��    ��: ��Ҫ��ʾ����������תΪSEG������븱��ʾ����
˵    ��: ���3λ
��ڲ���: fu32_Data=��ʾ����
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-11
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_AuxDisp_u32(u32 fu32_Data)
{
    u8 i;
    fu32_Data %= 1000;    //����������3λ���ݵ�ת��
    BIN4toNBCD(fu32_Data, gu8_AuxDispArray, 3);
    for (i = 0; i < 3; i++)         //����ֵת������ʾ����
        gu8_AuxDispArray[i] = Value_To_SEG[gu8_AuxDispArray[i]];
}

/*********************************************************************
��������: void VFD_AuxDisp_Str(char* fu8p_Arry)
��    ��: ��Ҫ��ʾ���ַ�������תΪSEG������븱��ʾ����
˵    ��: ���3λ
��ڲ���: fu32_Data=��ʾ����
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-11
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_AuxDisp_Str(char* fu8p_Arry)
{
    u8 i;
    
    for (i = 0; (i < 3) && ((*fu8p_Arry) != '\0'); i++, fu8p_Arry++)
        gu8_AuxDispArray[i] = ASCII_To_SEG[*fu8p_Arry];
}

/*********************************************************************
��������: void VFD_UnitDisp(u32 fu32_Data)
��    ��: ��λ��ʾ���ݴ��뵥λ����
˵    ��: 
��ڲ���: fu32_Data=��ʾ����
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-11
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_UnitDisp(u32 fu32_Data)
{
    switch (fu32_Data)
    {
        case UNIT_g:
            gu8_UnitDispArray[0] = 0x80;
            gu8_UnitDispArray[1] = 0x02;
            break;
        case UNIT_kg:
            gu8_UnitDispArray[0] = 0xC4;
            gu8_UnitDispArray[1] = 0x02;
            break;
        case UNIT_t:
            gu8_UnitDispArray[0] = 0x58;
            gu8_UnitDispArray[1] = 0x00;
            break;
        case UNIT_lb:
            gu8_UnitDispArray[0] = 0xC2;
            gu8_UnitDispArray[1] = 0x00;
            break;
        case UNIT_N:
            gu8_UnitDispArray[0] = 0x20;
            gu8_UnitDispArray[1] = 0x00;
            break;
        case UNIT_PCS:
            gu8_UnitDispArray[0] = 0x01;
            gu8_UnitDispArray[1] = 0x00;
            break;
        default:
            gu8_UnitDispArray[0] = 0x00;
            gu8_UnitDispArray[1] = 0x00;
            break;
    }
}

/*********************************************************************
��������: void VFD_LEDDisp(bool fb_Gross, bool fb_Net, bool fb_Tare, bool fb_Pack)
��    ��: LED����ʾ
˵    ��: 
��ڲ���: fb_Gross fb_Net fb_Tare fb_Pack ��Ӧ4��LED״̬
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-7
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_LEDDisp(bool fb_Gross, bool fb_Net, bool fb_Tare, bool fb_Pack)
{
    gu8_VFDLedRam = 0;
    
    if (fb_Tare)
        gu8_VFDLedRam |= 0x01;
    if (fb_Gross)
        gu8_VFDLedRam |= 0x02;
    if (fb_Pack)
        gu8_VFDLedRam |= 0x04;
    if (fb_Net)
        gu8_VFDLedRam |= 0x08;
    gu8_VFDLedRam = (~gu8_VFDLedRam);
}

/*********************************************************************
��������: void VFD_FlgDisp(u32 fu32_Data)
��    ��: ״̬λ��ʾ
˵    ��: 
��ڲ���: fu32_Data
fu32_Data��ÿһλ״̬����һ��ָʾ��
^17:ZERO    ^16:STAB    ^15:RUN     ^14:SUM     ^13:OVER    ^12:UNDER
^11:SP1     ^10:SP2     ^9:SP3      ^8:DISC     ^7:NZ       ^6:FILL
^5:HILIM    ^4:HI       ^3:GO       ^2:LO       ^1:LOLIM    ^0:HOLD
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-16
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_FlgDisp(u32 fu32_Data)
{
//----------------------------------------------//
    if (fu32_Data & 0x00020000)     //ZERO
        gu8_FlgDispArray[0] |= 0x02;
    if (fu32_Data & 0x00000800)     //SP1
        gu8_FlgDispArray[0] |= 0x01;
    if (fu32_Data & 0x00000020)     //HILIM
        gu8_FlgDispArray[0] |= 0x04;
//----------------------------------------------//
    if(fu32_Data & 0x00010000)      //STAB
        gu8_FlgDispArray[1] |= 0x02;
    if(fu32_Data & 0x00000400)      //SP2
        gu8_FlgDispArray[1] |= 0x01;
    if(fu32_Data & 0x00000010)      //HI
        gu8_FlgDispArray[1] |= 0x04;
//---------------------------------------------//
    if(fu32_Data & 0x00008000)      //RUN
        gu8_FlgDispArray[2] |= 0x02;
    if(fu32_Data & 0x00000200)      //SP3
        gu8_FlgDispArray[2] |= 0x01;
    if(fu32_Data & 0x00000008)      //GO
        gu8_FlgDispArray[2] |= 0x04;
//---------------------------------------------//
    if(fu32_Data & 0x00004000)      //SUM
        gu8_FlgDispArray[3] |= 0x02;
    if(fu32_Data & 0x00000100)      //DISC
        gu8_FlgDispArray[3] |= 0x01;
    if(fu32_Data & 0x00000004)      //LO
        gu8_FlgDispArray[3] |= 0x04;
//---------------------------------------------//
    if(fu32_Data & 0x00002000)      //OVER
        gu8_FlgDispArray[4] |= 0x02;
    if(fu32_Data & 0x00000080)      //NZ
        gu8_FlgDispArray[4] |= 0x01;
    if(fu32_Data & 0x00000002)      //LOLIM
        gu8_FlgDispArray[4] |= 0x04;
//---------------------------------------------//
    if(fu32_Data & 0x00001000)      //UNDER
        gu8_FlgDispArray[5] |= 0x02;
    if(fu32_Data & 0x00000040)      //FILL
        gu8_FlgDispArray[5] |= 0x01;
    if(fu32_Data & 0x00000001)      //HOLD
        gu8_FlgDispArray[5] |= 0x04;
//---------------------------------------------//
}

void VFD_FlgDisp_ZERO(bool fb_On)
{
    gu8_FlgDispArray[0] |= (fb_On ? 0x02 : 0);
}
void VFD_FlgDisp_SP1(bool fb_On)
{
    gu8_FlgDispArray[0] |= (fb_On ? 0x01 : 0);
}
void VFD_FlgDisp_HILIM(bool fb_On)
{
    gu8_FlgDispArray[0] |= (fb_On ? 0x04 : 0);
}
void VFD_FlgDisp_STAB(bool fb_On)
{
    gu8_FlgDispArray[1] |= (fb_On ? 0x02 : 0);
}
void VFD_FlgDisp_SP2(bool fb_On)
{
    gu8_FlgDispArray[1] |= (fb_On ? 0x01 : 0);
}
void VFD_FlgDisp_HI(bool fb_On)
{
    gu8_FlgDispArray[1] |= (fb_On ? 0x04 : 0);
}
void VFD_FlgDisp_RUN(bool fb_On)
{
    gu8_FlgDispArray[2] |= (fb_On ? 0x02 : 0);
}
void VFD_FlgDisp_SP3(bool fb_On)
{
    gu8_FlgDispArray[2] |= (fb_On ? 0x01 : 0);
}
void VFD_FlgDisp_GO(bool fb_On)
{
    gu8_FlgDispArray[2] |= (fb_On ? 0x04 : 0);
}
void VFD_FlgDisp_SUM(bool fb_On)
{
    gu8_FlgDispArray[3] |= (fb_On ? 0x02 : 0);
}
void VFD_FlgDisp_DISC(bool fb_On)
{
    gu8_FlgDispArray[3] |= (fb_On ? 0x01 : 0);
}
void VFD_FlgDisp_LO(bool fb_On)
{
    gu8_FlgDispArray[3] |= (fb_On ? 0x04 : 0);
}
void VFD_FlgDisp_OVER(bool fb_On)
{
    gu8_FlgDispArray[4] |= (fb_On ? 0x02 : 0);
}
void VFD_FlgDisp_NZ(bool fb_On)
{
    gu8_FlgDispArray[4] |= (fb_On ? 0x01 : 0);
}
void VFD_FlgDisp_LOLIM(bool fb_On)
{
    gu8_FlgDispArray[4] |= (fb_On ? 0x04 : 0);
}
void VFD_FlgDisp_UNDER(bool fb_On)
{
    gu8_FlgDispArray[5] |= (fb_On ? 0x02 : 0);
}
void VFD_FlgDisp_FILL(bool fb_On)
{
    gu8_FlgDispArray[5] |= (fb_On ? 0x01 : 0);
}
void VFD_FlgDisp_HOLD(bool fb_On)
{
    gu8_FlgDispArray[5] |= (fb_On ? 0x04 : 0);
}


/*********************************************************************
��������: void VFD_CopyMainDispArryToDispRam(void)
��    ��: ����ʾ�������VFD��ʾRAM����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-9
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_CopyMainDispArryToDispRam(void)
{
    u8 i,j;
    //������ʾ���渴�Ƶ���ʾ�������� ����ʾ��������ʾRAM�е���ʼ��ַΪ0x02
    for (i = 0,j = 2; i < 6; i++,j += 2)
        gu8_VFDDispRamArray[j] = gu8_MainDispArray[i];
}

/*********************************************************************
��������: void VFD_CopyAuxDispArryToDispRam(void)
��    ��: ����ʾ�������VFD��ʾRAM����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-9
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_CopyAuxDispArryToDispRam(void)
{
    u8 i,j;
    //������ʾ���渴�Ƶ���ʾ�������� ����ʾ��������ʾRAM�е���ʼ��ַΪ0x10
    for (i = 0,j = 0x10; i < 3; i++,j += 2)
        gu8_VFDDispRamArray[j] = gu8_AuxDispArray[i];
}

/*********************************************************************
��������: void VFD_CopyUnitDispArryToDispRam(void)
��    ��: ����ʾ�������VFD��ʾRAM����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-13
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_CopyUnitDispArryToDispRam(void)
{
    u8 i,j;
    //����λ��ʾ���渴�Ƶ���ʾ�������� ��λ��ʾ��������ʾRAM�е���ʼ��ַΪ0x0E
    for (i = 0,j = 0x0E; i < 2; i++,j ++)
        gu8_VFDDispRamArray[j] = gu8_UnitDispArray[i];
}

/*********************************************************************
��������: void VFD_CopyFlgDispArryToDispRam(void)
��    ��: ����ʾ�������VFD��ʾRAM����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-13
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_CopyFlgDispArryToDispRam(void)
{
    u8 i,j;
    //����־����ʾ���渴�Ƶ���ʾ�������� ��λ��ʾ��������ʾRAM�е���ʼ��ַΪ0x05
    for (i = 0,j = 0x01; i < 6; i++,j += 2)
        gu8_VFDDispRamArray[j] = gu8_FlgDispArray[i];
}

/*********************************************************************
��������: void VFD_CopyDispArryToDispRam(void)
��    ��: ����ʾ�������VFD��ʾRAM����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-13
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_CopyDispArryToDispRam(void)
{
    VFD_CopyMainDispArryToDispRam();    //����ʾ����
    VFD_CopyAuxDispArryToDispRam();     //����ʾ����
    VFD_CopyUnitDispArryToDispRam();    //��λ����
    VFD_CopyFlgDispArryToDispRam();     //��־�ƻ���
}

/*********************************************************************
��������: void VFD_WriteDispRamArry(void)
��    ��: ����ʾ��������д��VFD������LED�����ݵ�
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-9
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_WriteDispRamArry(void)
{
    u8 i;
    
    VFD_WriteByte(TEC16312_DISPMODE);   //11λ11��
    VFD_WriteByte(TEC16312_DATA_DISP);  //��������������:��������,��ַ��1��ʽ,д��ʾ���ݵ���ʾRAM
    VFD_CS_CLR;
    VFD_SendByte(TEC16312_ADDRESS);             //��ַ����������:�ӵ�ַ0��ʼ
    for (i = 0; i < sizeof(gu8_VFDDispRamArray) / sizeof(gu8_VFDDispRamArray[0]); i++)
    {
        VFD_SendByte(gu8_VFDDispRamArray[i]);        //��ʾ����
    }
    VFD_CS_SET;
    VFD_WriteByte(TEC16312_BRIGHT);    //�������
    
    VFD_CS_CLR;
    VFD_SendByte(TEC16312_DATA_LED);     //led��
    VFD_SendByte(gu8_VFDLedRam);        //led
    VFD_CS_SET;
}



/*********************************************************************
��������: void VFD_FillDispRam(u32 fu32_ModelSet, u32 fu32_Logo)
��    ��: ��ʾȫ��
˵    ��: 
��ڲ���: fu32_ModelSet=�ͺ��Զ��忪�أ�fu32_Logo=LOGO����
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-9
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_FillDispRam(u32 fu32_ModelSet, u32 fu32_Logo)
{
    u8 i;
    //��ʾ����ȫ��
    memset(gu8_VFDDispRamArray, 0xFF, sizeof(gu8_VFDDispRamArray));
    gu8_VFDLedRam = 0;          //LEDȫ��
    
    if (fu32_ModelSet != 0 && fu32_Logo == 0) //�ͺ��Զ���򿪲��ҵ�Դ�������
        gu8_VFDDispRamArray[0] = 0;            //�����Դ��
        
    for (i = 0; i < 6; i++)
    {
        gu8_MainDispArray[i] = 0xFF;        //�������ʾ����
        gu8_FlgDispArray[i] = 0xFF;         //����־λ����
        if (i < 3)
            gu8_AuxDispArray[i] = 0xFF;     //��丱��ʾ����
        if (i < 2)
            gu8_UnitDispArray[i] = 0xFF;    //��䵥λ��ʾ����
    }
}

/*********************************************************************
��������: void VFD_ClrDispRam(u32 fu32_ModelSet, u32 fu32_Logo)
��    ��: ��VFD��ʾ���棬��������ʾ������ʾ�Ļ�������
˵    ��: 
��ڲ���: fu32_ModelSet=�ͺ��Զ��忪�أ�fu32_Logo=LOGO����
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-9
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_ClrDispRam(u32 fu32_ModelSet, u32 fu32_Logo)
{
    u8 i;
    //��ʾ����ȫ��
    memset(gu8_VFDDispRamArray, 0, sizeof(gu8_VFDDispRamArray));
    gu8_VFDLedRam = 0xFF;          //LEDȫ��
    //�ͺ��Զ���رջ����ͺ��Զ���򿪲��ҵ�Դ����ʾ��
    if (fu32_ModelSet == 0 || (fu32_ModelSet != 0 && fu32_Logo != 0))
        gu8_VFDDispRamArray[0] = 0xFF;            //�����Դ��
    
    for (i = 0; i < 6; i++)
    {
        gu8_MainDispArray[i] = 0;        //������ʾ����
        gu8_FlgDispArray[i] = 0;         //���־λ����
        if (i < 3)
            gu8_AuxDispArray[i] = 0;     //�帱��ʾ����
        if (i < 2)
            gu8_UnitDispArray[i] = 0;    //�嵥λ��ʾ����
    }
}

/*********************************************************************
��������: u32 VFD_ReadKey(void)
��    ��: ����ֵ
˵    ��: 
��ڲ���: 
�� �� ֵ: ����ֵ
��    ��: �Ժ���               ʱ    ��: 2013-12-9
��    ��:                      ʱ    ��: 
*********************************************************************/
u32 VFD_ReadKey(void)
{
    UIDATA uiKey;
    
    VFD_CS_CLR;
    VFD_SendByte(TEC16312_DATA_RKEY);
    __nop();__nop();__nop();__nop();__nop();__nop();;
    uiKey.uc[1]=VFD_ReceiveByte();
    uiKey.uc[0]=VFD_ReceiveByte();
    VFD_CS_SET;
    return (u32)uiKey.ui;
}

/*********************************************************************
��������: void VFD_MainSigDisp(bool fb_SigFlg)
��    ��: С������ʾ
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-13
��    ��:                      ʱ    ��: 
*********************************************************************/
void VFD_MainSigDisp(bool fb_SigFlg)
{
    u8 i;
    
    if (fb_SigFlg)
    {
        for (i = 0; i < 6; i++)
        {
            if (gu8_MainDispArray[i] != SEG_BLK && i != 0)
            {
                gu8_MainDispArray[i - 1] = SEG_SIG;
                break;
            }
        }
    }
}

/*********************************************************************
��������: u8 VFD_KeyCode_To_Value(u32 ful_KeyCode)
��    ��: ��������ת������ֵ
˵    ��: 
��ڲ���: ful_KeyCode = ��������
�� �� ֵ: ������Ӧ������
��    ��: �Ժ���               ʱ    ��: 2011-3-31
��    ��:                      ʱ    ��: 
*********************************************************************/
u8 VFD_KeyCode_To_Value(u32 ful_KeyCode)
{
    u8 luc_Value = 0;
    
    switch (ful_KeyCode)
    {
        case K_1:
            luc_Value = 1;break;
        case K_2:
            luc_Value = 2;break;
        case K_3:
            luc_Value = 3;break;
        case K_4:
            luc_Value = 4;break;
        case K_5:
            luc_Value = 5;break;
        case K_6:
            luc_Value = 6;break;
        case K_7:
            luc_Value = 7;break;
        case K_8:
            luc_Value = 8;break;
        case K_9:
            luc_Value = 9;break;
        case K_0:
        default:
            luc_Value = 0;break;
    }
    return luc_Value;
}


