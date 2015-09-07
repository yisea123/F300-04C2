#ifndef _SUM_H
#define _SUM_H

#include "71x_type.h"

extern u32 gu32_DebugSumNum;
extern u32 gu32_DebugSumNumTemp;   //��ӡ��ʹ��
extern u64 gu64_SumWt;                //�ۼ����� ���15λ
extern u32 gu32_SumNum;               //�ۼƴ���
extern u32 gu32_SumWt_Rec[21];             //�䷽0-9�ۼ�����
extern u32 gu32_SumNum_Rec[21];            //�䷽0-9�ۼƴ���

//�ۼ�����С����͵�λת��������ݱ���
extern u32 gu32_SumWt;
extern u32 gu32_SumWtUnit;             //�ۼƵ�λ
extern u32 gu32_SumWtPoint;            //�ۼ�С����
//extern u32 gu32_SumWt_Rec[21];
//extern u32 gu32_SumWtUnit_Rec[21];             //�ۼƵ�λ
//extern u32 gu32_SumWtPoint_Rec[21];            //�ۼ�С����


extern u8 gu8_SumCheckInTime;      //�ۼƲ�ѯ��������������


extern void DiscSumDeal(void);
extern void ClrSum(void);
extern void Disp_SumState(void);
extern void Key_SumState(void);
extern bool GetSumWt_u32(u64 fu64_SumWt,    //��Ҫת���ĵ�ǰ8�ֽ���������
                         u32 fu32_Unit,     //��ǰ������Ӧ�ĵ�λ
                         u32 fu32_Point,    //��ǰ������Ӧ��С����
                         u32* fu32p_SumWt,  //�õ���4�ֽ�Ŀ������
                         u32* fu32p_Unit,   //Ŀ�������ĵ�λ
                         u32* fu32p_Point   //Ŀ��������С����
                        );
extern void ClrSum_Rec(u8 fu8_Rec);

#endif