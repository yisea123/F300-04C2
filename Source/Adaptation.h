#ifndef __Adaptation_H_
#define __Adaptation_H_

#include "71x_type.h"

/*******************************************************************************
��ע��: ����Ӧ����
*******************************************************************************/
typedef struct
{
    s32  *const ps32Weight;     // ��ǰ���� ����ë���ذ�װ���� ָ��ͬ�ĵ�ַ�� ���ڼ���ǰ��λָ��
    s32  *const ps32SP2;        // ָ����Ͷ��ǰ��������ʱ�ã�
    s32  *const ps32SP3;        // ָ�������ǰ��������ʱ�ã�
    u32  *const pu32SP3RealTime;        //ָ��ʵ�ʲ�õ�СͶʱ��
    u32  *const pu32SP2RealTime;        //ָ��ʵ�ʲ�õ���Ͷʱ��
    u32  *const pu32SP3ForbidTime;      //ָ��СͶ����ʱ��
    s32  *const ps32SP3RealWt;          //ʵ��СͶֹͣ����
    s32  *const ps32SP2RealWt;          //ʵ����Ͷֹͣ����
    s32  *const ps32SP3KThisTime;       //ָ�򱾴�СͶ���̵��������Kֵ
    s32  *const ps32SP2KThisTime;       //������Ͷ��ֹ�㸽�����������Kֵ
    
    
    u32 u32AdatpEn;            // ����Ӧ����
    
    // ��/��Ͷ������
    bool bFirstIn;              // ֹͣ����1�����buf�����㣬�������buf
    s32 s32RushWtLow;           //�������͵�
    s32 s32RushWtMiddle;        //�������е�
    s32 s32RushWtHigh;          //�������ߵ�
    s32 s32RushWtLowProb;       //ͳ�ƹ������͵�
    s32 s32RushWtMiddleProb;    //ͳ�ƹ������е�
    s32 s32RushWtHighProb;      //ͳ�ƹ������ߵ�
    s32 s32SP2Bkp;             // ��Ͷ����ֵ�����ݣ�
    u32 u32SP2En;             // ��/��Ͷ��������
    u32 u32SP2Range;          // ��/��Ͷ������Χ���� %
    u32 u32SP2ThresholdMax;      // ��/��Ͷ������ֵ�ж� СͶ�ʱ�� ms
    u32 u32SP2ThresholdMin;      // ��/��Ͷ������ֵ�ж� СͶ���ʱ�� ����ʱ��+��ʱ��ms
    u32 u32SP2ThresholdVal;     //СͶ�����̵�����ʱ��
    u32 u32SP2Scope;           // ��Ͷ��������
    u32 u32SP2Count;          // ��/��Ͷ��ǰ��¼����      ��ֵֻ���ϵ��������������ʱ����
    u32 u32SP2SubCount;       // ��/��Ͷ��ǰ��¼����      ��ֵֻ���ϵ��������������ʱ����
    s32 s32SP3KProb;            //ͳ�ƴ����õ���СͶ�������Kֵ
    u32 u32SP3KCnt;             //ͳ�ƴ���СͶ�������Kֵ�õļ�������
    s32 s32SP2KProb;            //ͳ�ƴ����õ�����Ͷ��ֹ�㸽���������Kֵ
    u32 u32SP2WT;               //��Ͷ�ӵ�����
    float fSP2Flux;             //��Ͷ���� ��λ��AD����
    u32 u32SP2ResultWt;         //��Ͷ����ɼ���ʱ������
    
    // ���������
    s32 s32ConfirmWt;          // ��ֵ�����������Ƿ��ϣ����¼����ǰ�����������޲��ϣ���ֵΪ0
    s32 s32TargetVal;          // Ŀ��ֵ
    s32 s32SP3Bkp;             // �������ֵ�����ݣ�
    u32 u32SP3En;              // �����������
    u32 u32SP3Range;           // ���������Χ����ֵ %
    u32 u32SP3Scope;           // �����������
    u32 u32SP3Count;           // ��ǰ��¼����     ��ֵֻ���ϵ��������������ʱ����
    
    //������
    
    
    //����������
    s32 s32SP2AdaptVal; //��Ͷ����ֵ
    s32 s32SP2AdaptSig; //��Ͷ��ǰ���������� +=1  -=-1
    
    u32 u32SP3Prob;     //ͳ�����ֵ
    s32 s32SP3AdaptVal; //������ֵ
    
    
}struct_adapt_t;

extern struct_adapt_t  gs_Adapt;


/*******************************************************************************
            ����ӿ�
*******************************************************************************/
extern void Adapt_InitDataFirstRun(struct_adapt_t *pfs_Adapt);
extern void Adapt_InitData(struct_adapt_t *pfs_Adapt);
extern void SampleRushWt(struct_adapt_t *pfs_Adapt);
extern u32 Adapt_Process(struct_adapt_t *pfs_Adapt);
extern void Adapt_InitSP3KTemp(struct_adapt_t *pfs_Adapt);
extern s32 SP3LinearKProbabilityStatistics(struct_adapt_t *pfs_Adapt, s32 fs32_KThisTime);

#endif

/***************************************The End Of This File***************************************/