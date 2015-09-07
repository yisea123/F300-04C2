/*************************************************
Project:                GM8804C-2_ARM
File name:              RTC.c
Description:            ʵʱʱ��оƬ��غ���
Author:                 �Ժ���
Version:                1.0
Date:                   2013-12-4
Others:                 IC:SD2103
History:
*************************************************/
#include "include.h"


sTime g_sSysDateTime;
dTime g_dSysDateTime;




//COMMAND:����ʱҪ��MSB-->LSB
//Data   :����ʱҪ��LSB-->MSB
//�����ͺ���ȫ����DataҪ�� L-->M,����COMMANDȫ��Ҫ����
#define RTC_COMMD_WSTA1    0x06
#define RTC_COMMD_WSTA2    0x46
#define RTC_COMMD_WADJ     0x36
#define RTC_COMMD_WTIME    0X66
#define RTC_COMMD_WDATE    0X26

#define RTC_COMMD_RSTA1    0x86
#define RTC_COMMD_RSTA2    0xC6
#define RTC_COMMD_RADJ     0xB6
#define RTC_COMMD_RTIME    0XE6
#define RTC_COMMD_RDATE    0XA6

#define RTC_DAT_CLR     GPIO_BitWrite(GPIO1,4,0)
#define RTC_DAT_SET     GPIO_BitWrite(GPIO1,4,1)
#define RTC_DAT_READ    GPIO_BitRead(GPIO1,4)

#define RTC_CLK_CLR     GPIO_BitWrite(GPIO1,3,0)
#define RTC_CLK_SET     GPIO_BitWrite(GPIO1,3,1)

#define RTC_CS_CLR      GPIO_BitWrite(GPIO1,2,0)
#define RTC_CS_SET      GPIO_BitWrite(GPIO1,2,1)


u8 dayofMonth[2][13]
   ={{0,31,28,31,30,31,30,31,31,30,31,30,31},
     {0,31,29,31,30,31,30,31,31,30,31,30,31}};
        
        
bool LeapYear(u16 year);
/*********************************************************************
��������: void RTC_Send_Byte(u8 indata)
��    ��: ��SD2103д���ݣ��ײ�����
˵    ��: 
��ڲ���: indata=����
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-4
��    ��:                      ʱ    ��: 
*********************************************************************/
void RTC_Send_Byte(u8 indata)
{
    u8 i;
    GPIO_Config(GPIO1, (1<<4), GPIO_OUT_PP);
    for (i = 0; i < 8; i++)
    {
        RTC_CLK_SET;
        __nop();
        (indata & 0x01) ? RTC_DAT_SET : RTC_DAT_CLR;
        RTC_CLK_CLR;
        __nop();
        indata >>= 1;       //����,��λ��ǰ
    }
}

/*********************************************************************
��������: u8 RTC_Receive_Byte(void)
��    ��: ��SD2103�����ݣ��ײ�����
˵    ��: 
��ڲ���: 
�� �� ֵ: ��������ֵ
��    ��: �Ժ���               ʱ    ��: 2013-12-4
��    ��:                      ʱ    ��: 
*********************************************************************/
u8 RTC_Receive_Byte(void)
{
	u8 i;
	u8 outdata = 0;
	GPIO_Config(GPIO1, (1<<4), GPIO_IN_TRI_TTL);
	for (i = 0; i < 8; i++)
	{
		outdata >>= 1;
		RTC_CLK_SET;
		__nop();
		RTC_CLK_CLR;
		if (RTC_DAT_READ)
		{
			outdata |= 0x80;
		}
	}
	return(outdata);
}

/*********************************************************************
��������: void RTC_Write_nByte(u8 commmand,u8 *dat, u8 n)
��    ��: ��SD2103���Ͷ��ֽ�����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-4
��    ��:                      ʱ    ��: 
*********************************************************************/
void RTC_Write_nByte(u8 commmand,u8 *dat, u8 n)
{
    u8 i;
    RTC_CLK_SET;
    RTC_CS_SET;
    __nop();
    RTC_Send_Byte(commmand);
    for (i = 0; i < n; i++)
    {
        RTC_Send_Byte(*dat);
        dat++;
    }
    RTC_CLK_SET;
    RTC_CS_CLR;
}

/*********************************************************************
��������: void RTC_Read_nByte(u8 commmand, u8 *dat, u8 n)
��    ��: ��SD2103
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-4
��    ��:                      ʱ    ��: 
*********************************************************************/
void RTC_Read_nByte(u8 commmand, u8 *dat, u8 n)
{
	u8 i;
	RTC_CLK_SET;
	RTC_CS_SET;
	__nop();
	RTC_Send_Byte(commmand);
	for (i = 0; i < n; i++)
	{
		*dat = RTC_Receive_Byte();
		dat++;
	}
	RTC_CLK_SET;
	RTC_CS_CLR;
}

/*********************************************************************
��������: void RTC_Init(void)
��    ��: ʱ��оƬ��ʼ��
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-4
��    ��:                      ʱ    ��: 
*********************************************************************/
void RTC_Init(void)
{
    u8 state1 = 0x02; //24Сʱ��
    u8 state2 = 0;    //���������ж�
    u8 adjust = 0;    //��ʹ��ʱ�ӵ���
    
    GPIO_Config(GPIO1, (1<<2), GPIO_OUT_PP);     //ʱ�� �������
    GPIO_Config(GPIO1, (1<<3), GPIO_OUT_PP);     //Ƭѡ �������

    RTC_Write_nByte(RTC_COMMD_WSTA1, &state1, 1);
    RTC_Write_nByte(RTC_COMMD_WSTA2, &state2, 1);
    RTC_Write_nByte(RTC_COMMD_WADJ, &adjust, 1);
}

//��RTC����һ������ʱ�����ݵ�һ���ṹ��
void RTC_ReadDateTime(sTime* sReadDate)
{
    RTC_Read_nByte(RTC_COMMD_RDATE, &(sReadDate->year), 7);
    (sReadDate->hour) &= 0x3f;//����AM/PM��־λ
}

//��RTC����һ��ʱ�����ݵ�һ���ṹ��
void RTC_ReadTime(sTime* sReadTime)
{
    RTC_Read_nByte(RTC_COMMD_RTIME, &(sReadTime->hour), 3);
    (sReadTime->hour) &= 0x3f;//����AM/PM��־λ
}

//����һ��RTCʱ��ṹ��Ϊһ����Hex��ʾ�ṹ��
void UTRC_sTimetoDisp(sTime* psTime, dTime* pdTime)
{
    (pdTime->hexdate)=((psTime->year)<<16)
                     +((psTime->month)<<8)
                     + (psTime->date);

    (pdTime->hextime)=(((psTime->hour)&0x3f)<<16)
                     +((psTime->min)       << 8)
                     +(psTime->sec          );
}

//����һ��RTCʱ��ṹ��Ϊһ��ASCII��������
void RTC_sDatetoASC(sTime* psTime,u8* a8Arry)
{
    a8Arry[0]=((psTime->year>>4)|0x30);
    a8Arry[1]=((psTime->year&0x0f)|0x30);
    a8Arry[2]=((psTime->month>>4)|0x30);
    a8Arry[3]=((psTime->month&0x0f)|0x30);
    a8Arry[4]=((psTime->date>>4)|0x30);
    a8Arry[5]=((psTime->date&0x0f)|0x30);
}

//����һ��RTCʱ��ṹ��Ϊһ��ASCII����ʱ��
void RTC_sTimetoASC(sTime* psTime,u8* a8Arry)
{
    a8Arry[0]=((psTime->hour>>4)|0x30);
    a8Arry[1]=((psTime->hour&0x0f)|0x30);
    a8Arry[2]=((psTime->min>>4)|0x30);
    a8Arry[3]=((psTime->min&0x0f)|0x30);
    a8Arry[4]=((psTime->sec>>4)|0x30);
    a8Arry[5]=((psTime->sec&0x0f)|0x30);
}

//����תΪ����ASCII�빲ռ10���ֽ�  ��2014/03/05
void RTC_DateToASC_Full(u8* a8Arry)
{
    u8 lu8_Array[6];
    
    RTC_ReadDateTime(&g_sSysDateTime);  //��������ʱ��ṹ��
    RTC_sDatetoASC(&g_sSysDateTime, lu8_Array);    //����תΪASCII��
    a8Arry[9] = lu8_Array[5];
    a8Arry[8] = lu8_Array[4];
    a8Arry[7] = '/';
    a8Arry[6] = lu8_Array[3];
    a8Arry[5] = lu8_Array[2];
    a8Arry[4] = '/';
    a8Arry[3] = lu8_Array[1];
    a8Arry[2] = lu8_Array[0];
    a8Arry[1] = '0';
    a8Arry[0] = '2';
}

//ʱ��תΪ����ASCII�빲ռ5���ֽ�  ��15:36
void RTC_TimeToASC_Full(u8* a8Arry)
{
    u8 lu8_Array[6];
    
    RTC_ReadDateTime(&g_sSysDateTime);  //��������ʱ��ṹ��
    RTC_sTimetoASC(&g_sSysDateTime, lu8_Array);    //����תΪASCII��
    a8Arry[4] = lu8_Array[3];
    a8Arry[3] = lu8_Array[2];
    a8Arry[2] = ':';
    a8Arry[1] = lu8_Array[1];
    a8Arry[0] = lu8_Array[0];
}

//�����������ݹ���һ������RTC�Ĵ����ṹ��������
//����:�� �� ��
//���:Ŀ��ṹ���е������ձ���
//����:����������պϷ�,�򷵻�true,���򷵻�false
bool RTC_FrameDate(sTime sTargTime)
{
    u8 year, month, date;
    year = (sTargTime.year >> 4) * 10 + (sTargTime.year & 0x0F);
    month = (sTargTime.month >> 4) * 10 + (sTargTime.month & 0x0F);
    date = (sTargTime.date >> 4) * 10 + (sTargTime.date & 0x0F);

    if((year>99)||(month<1)||(month>12)){
        return false;
    }
    if((date<1)||(date>dayofMonth[LeapYear(year)][month])){
        return false;
    }

    return true;
}

bool RTC_FrameTime(sTime sTargTime)
{
    u8 hour, min, sec;
    hour = (sTargTime.hour >> 4) * 10 + (sTargTime.hour & 0x0F);
    min = (sTargTime.min >> 4) * 10 + (sTargTime.min & 0x0F);
    sec = (sTargTime.sec >> 4) * 10 + (sTargTime.sec & 0x0F);
    
    if(hour>23 || min>59 || sec>59){
        return false;
    }
    
    return true;
}


//д�ṹ�������ʱ������ 7Byte ��RTC
void RTC_WriteDateTime(sTime* sWriteDateTime)
{
    RTC_Write_nByte(RTC_COMMD_WDATE,&(sWriteDateTime->year),7);
}
/*
//����ʵ��,�����Ե���ֻд���ڼĴ���
//�����޸�ʱ,�ȶ�����ǰʱ��,Ȼ������ʱ��һ��д��
//ʵ��ʱ,����100ms�����ͣд������,ʱ���ͣ��
//û�и��õİ취���
*/
void RTC_WriteDate(sTime* sWriteDate)
{
    RTC_ReadTime(sWriteDate);
    RTC_Write_nByte(RTC_COMMD_WDATE,&(sWriteDate->year),7);
}


//�����ж�
bool LeapYear(u16 year)
{
    if(year%400==0) {
        return true;
    }else if((year%4==0) && (year%100!=0)){
        return true;                           //����
    }else{
        return false;                           //ƽ��
    }
}



