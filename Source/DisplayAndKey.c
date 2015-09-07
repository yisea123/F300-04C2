/*
Description:            ��ʾ�Ͱ�����غ�������
Author:                 �Ժ���
Date:                   2013-12-9
*/


#include "include.h"

//GM8804C-2_ARM��׼��汾��

/*  
v1.00 �Ժ��� 2014-5-30
1.  ��һ����׼�汾

v1.01 �Ժ��� 2014-7-9
2.  ���ӿ�ݱ궨��㹦�ܡ�
3.  ModbusͨѶ��������У׼�ĵ�ַ��
4.  Modbus��Ȧ��ַ0079�޸�Ϊ���п�1�Զ���ӡ���ء�
5.  ��ʾˢ�¼������Ϊ30ms��
6.  Cont������ʽ���ͼ������Ϊ������10ms��
7.  ������ʾOFLʱ�����ܱ궨�������⡣
8.  ����Modbus��ӡ�����䷽�ۼƺ��ٴ�ӡ���ۼƻ��ӡ�������ݵ����⡣
9.  ֹͣ״̬�²鿴�ۼ�����ʱ��Ϊ����ʾ��������ֻ࣬��SUMָʾ����������Ŀǰ���ڲ鿴�ۼ�״̬������ʱ�鿴�ۼ�ʱ�������⴦��������ָʾ��Ҳ������
10. �޶�ģʽ�д���ֻҪû�п�ʼ���ϣ��Ϳ����ɴ���
11. �����޶�ģʽ�������޸�Ŀ��ֵ����һ�Ӳ�ˢ�µ����⡣
12. ����RS485����Modbus ASCII��ʽͨѶʱż�������жϵ����⡣
13. ����Modbus RTU����ͨѶ�����У������Ǳ�ͨѶ��ʽѡ�ż������ֵ��������⡣
14. ���ٱ궨�궨�����������ֱ���˳��������������޸Ľ��档
15. VFD��ʾʵʱ��ʼ����

v1.02   �Ժ���  2014-10-30
1.	�궨�������float���ͣ���߱궨ʱ��׼ȷ�ȡ�
2.	�����ۼƲ�ѯ����򿪣�����ʱ��6����ѯ�ۼ�ʱ���������������������⡣
3.	�鿴�ۼ�ʱ��PRINT����ӡ�����û�д�������Ϊ��ӡ����Ӧ�ñ���ERR10��������ERR09��
4.	�Ż���ӡ����������
5.	����˫�޶��ӻ���ģʽ��
6.	����PROFIBUS-DPͨѶ��֧�֣��ṩ����GSD�ļ�ѡ������һ�����ݾɵ�Ƭ���汾DPͨѶ��
7.	����read-o���ʽͨѶ�����ݷǳ��ϵ�4λ�ۼƴ�����ͨѶ��ʽ��
8.	���ӿ��������롰�궨�������ܡ�



*/
#define VERSION     "103"
#define MODEL       "8804C2"


u32 gu32_KeyCode;           //����ֵ
u32 gu32_FlashDelay;        //��˸��ʱ
u8 gu8_DataInLength;       //�������볤��
bool gb_SetFlg;          //SET������־
bool gb_FirstNumKeyFlg;   //��һ�ΰ��������־
u8 gu8_DispErrorNumber;         //�����
//u8 gu8_DispErrorNumberBackup;   //����ű���
bool gb_DispErrorFlg;
bool gb_HandClrErrorFlg;
u32 gu32_DispErrorTime;
u32 gu32_ErrTimeDelay;
bool gb_FlashFlg;       //��˸��־λ



/*********************************************************************
��������: void Disp_FlgLight(void)
��    ��: ��־����ʾ
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-7
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_FlgLight(void)
{
    VFD_FlgDisp_ZERO(gb_ZeroPosition);
    VFD_FlgDisp_STAB(gb_StabFlg);
    if (gb_EndFlg)  //ֹͣ������Ч��runָʾ����˸
        VFD_FlgDisp_RUN(Flash_Flg(gb_RunFlg));
    else
        VFD_FlgDisp_RUN(gb_RunFlg);
    VFD_FlgDisp_SUM(gb_SumFlg);
    VFD_FlgDisp_OVER(gb_OverFlg || gb_OUOverFlg);
    VFD_FlgDisp_UNDER(gb_UnderFlg || gb_OUUnderFlg);
    //�ж�ģʽ&&����&&������ж�Ϲ��ŵ�λ�ź�&&ж�Ϲ��ŵ�λ�ź���Ч  ��ô�������ʱ�����ָʾ����˸
    //�޶�ģʽ&&����&&�����˼д���λ�ź�&&�д���λ�ź���Ч  ��ô�������ʱ�����ָʾ����˸
    if (((gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gb_RunFlg && gb_EnDiscCloseOKFlg && (!gb_DiscCloseOKFlg))
     || ((gs_Setup.TareMode == BINNO || gs_Setup.TareMode == NO2_A || gs_Setup.TareMode == NO2_B) && gb_RunFlg  && gb_EnPackOKFlg && (!gb_PackOKFlg)))
    {
        VFD_FlgDisp_SP1(Flash_Flg(Feed_SP(SP1_STATE)));
        VFD_FlgDisp_SP2(Flash_Flg(Feed_SP(SP2_STATE)));
        VFD_FlgDisp_SP3(Flash_Flg(Feed_SP(SP3_STATE)));
    }
    else
    {
        VFD_FlgDisp_SP1(Feed_SP(SP1_STATE));
        VFD_FlgDisp_SP2(Feed_SP(SP2_STATE));
        VFD_FlgDisp_SP3(Feed_SP(SP3_STATE));
    }
    //�ж�ģʽ&&����&&�����˼д���λ�ź�&&�д���λ�ź���Ч  ��ô���ж��ʱ��ж��ָʾ����˸
    if ((gs_Setup.TareMode == BINYES || gs_Setup.TareMode == BIN2_A || gs_Setup.TareMode == BIN2_B) && gb_RunFlg  && gb_EnPackOKFlg && (!gb_PackOKFlg))
        VFD_FlgDisp_DISC(Flash_Flg(gb_DiscFlg));
    else
        VFD_FlgDisp_DISC(gb_DiscFlg);
    VFD_FlgDisp_NZ(gb_NzFlg);
    VFD_FlgDisp_FILL(gb_FillFlg);
    if (gu8_ExtType == PBUS_UART)   //������PROFIBUS��չ��
    {
        VFD_FlgDisp_HILIM(Pbus_InitFail());       //PROFIBUS��ʼ��ʧ��
        VFD_FlgDisp_HI(Pbus_NotLinked());          //PROFIBUS����δ����
    }
    VFD_FlgDisp_GO(gb_GoFlg);
    VFD_FlgDisp_LO(gb_LowDefineFlg && (!gb_LowFlg));    //����λ�ж��嵫��������Ч
    VFD_FlgDisp_LOLIM(gb_FlapBagOutFlg || gb_FlapAllHighFlg);   //�Ĵ�ָʾ
    VFD_FlgDisp_HOLD(gb_CompFlg);   //��ֵָʾ
}

/*********************************************************************
��������: u8 monthfromname(u8 name[])
��    ��: ���·����ƻ���·�ֵ.������� 0,����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-7
��    ��:                      ʱ    ��: 
*********************************************************************/
u8 monthfromname(u8 name[])
{
    const u8 monthname[13][3]=
    {
     {0,0,0},
     {'J','a','n'},{'F','e','b'},{'M','a','r'},{'A','p','r'},
     {'M','a','y'},{'J','u','n'},{'J','u','l'},{'A','u','g'},
     {'S','e','p'},{'O','c','t'},{'N','o','v'},{'D','e','c'}
    };//�·�����
    u8 i,j;
    for(i=1;i<=12;i++)
    {
        for(j=0;j<3;j++)
        {
            if(name[j]!=monthname[i][j])
                break;
            if(j==2)
                return(i);
        }
    }
    return(0);
}

/*********************************************************************
��������: void Disp_VersionType(u8 fu8_Type)
��    ��: ��ʾ�汾�Ż�����޸�ʱ������ID��
˵    ��: 
��ڲ���: 0�汾�� 1�����޸�ʱ�� 2���ID��
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 
��    ��:                      ʱ    ��: 
*********************************************************************/
/*��ʾ��ǰ����ʱ������ 
unsigned char code DataStr[]=__DATE__; 
unsigned char code TimeStr[]=__TIME__; 
��ʽ 
DataStr[]=[][][]�ո�[][]�ո�[][][][]; 
          �µ�Ӣ��  ��   �� 
��2004/10/06��ʾΪ43 63 74 20 30 36 20 32 30 30 34 ��oct 06 2004 
1= Jan 2= Feb 3= Mar 4=Apr 5=May 6 =Jun 7=Jul 8=Aug 9=Sep 10=Oct 11=Nov 12=Dec  

TimeStr[]=[][]:[][]:[][]; ʱ:��:�� 
��10:31:26��ʾΪ31 30 3a 33 31 3a 32 36*/
void Disp_VersionType(u8 fu8_Type)
{
    u8 lu8_Date[] = __DATE__;
    u8 lu8_Time[] = __TIME__;
    u8 lu8_Month;
    
    VFD_ClrDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);       //����ʾ����
    switch(fu8_Type)
    {
        case 0:     //�ͺŰ汾��
            if (gu32_ModelSetSwitch)    //�ͺ��Զ��幦�ܴ�
            {
                gu8_MainDispArray[0] = Value_To_SEG[gu32_ModelArry[1]];
                gu8_MainDispArray[1] = Value_To_SEG[gu32_ModelArry[2]];
                gu8_MainDispArray[2] = Value_To_SEG[gu32_ModelArry[3]];
                gu8_MainDispArray[3] = Value_To_SEG[gu32_ModelArry[4]];
                gu8_MainDispArray[4] = Value_To_SEG[gu32_ModelArry[5]];
                gu8_MainDispArray[5] = Value_To_SEG[gu32_ModelArry[6]];
                VFD_AuxDisp_Str(VERSION);   //�汾��
                gu8_AuxDispArray[0] |= 0x80;    //ARM�汾04C2�汾�Ŵ�С���㣬��������Ƭ���汾
            }
            else
            {
                VFD_MainDisp_Str(MODEL);    //�ͺ�
                VFD_AuxDisp_Str(VERSION);   //�汾��
                gu8_AuxDispArray[0] |= 0x80;    //ARM�汾04C2�汾�Ŵ�С���㣬��������Ƭ���汾
            }
            break;
        case 1:     //��������
            lu8_Month = monthfromname(lu8_Date);
            
            gu8_MainDispArray[0] = Value_To_SEG[lu8_Date[9] & 0x0F];
            gu8_MainDispArray[1] = Value_To_SEG[lu8_Date[10] & 0x0F] | 0x80;
            gu8_MainDispArray[2] = Value_To_SEG[lu8_Month/10];
            gu8_MainDispArray[3] = Value_To_SEG[lu8_Month%10] | 0x80;
            gu8_MainDispArray[4] = Value_To_SEG[lu8_Date[4] & 0x0F];
            gu8_MainDispArray[5] = Value_To_SEG[lu8_Date[5] & 0x0F];
            VFD_AuxDisp_Str("DA ");
            break;
        case 2:     //����ʱ��
            gu8_MainDispArray[0] = Value_To_SEG[lu8_Time[0] & 0x0F];       
            gu8_MainDispArray[1] = Value_To_SEG[lu8_Time[1] & 0x0F] | 0x80;
            gu8_MainDispArray[2] = Value_To_SEG[lu8_Time[3] & 0x0F];       
            gu8_MainDispArray[3] = Value_To_SEG[lu8_Time[4] & 0x0F] | 0x80;       
            gu8_MainDispArray[4] = Value_To_SEG[lu8_Time[6] & 0x0F];       
            gu8_MainDispArray[5] = Value_To_SEG[lu8_Time[7] & 0x0F];       
            VFD_AuxDisp_Str("CL ");
            break;
        case 3:
            if (gu32_GetedRandom != 0x55 || gu32_RandomID == 0 || gu32_RandomID >= 1000000)
            {
                do
                {
                    gu32_RandomID = GetRandom();
                }while(GradeShutCodeEQ());
                
                gu32_GetedRandom = 0x55;
                FRAM_WriteDW(FMAddr_GetedRandom, gu32_GetedRandom);
                FRAM_WriteDW(FMAddr_RandomID, gu32_RandomID);
                UpdataGrandShutCode();      //��������
            }
            VFD_MainDisp_u32(gu32_RandomID);
            VFD_AuxDisp_Str("ID ");
            break;
        case 4:     //�ͻ�����
            Disp_Main_Data(gu32_BuyerID, 0, 2, false, false);       //��ʾ
            VFD_AuxDisp_Str("BUY");
            break;
        default:
            break;
    }
    VFD_CopyDispArryToDispRam();
    VFD_WriteDispRamArry();
}

/*********************************************************************
��������: void Disp_Version(void)
��    ��: ��ʾ�ͺźͰ汾��
˵    ��: �����鿴�������ںͳ���
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-11
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_Version(void)
{
    u32 lu32_TimeBuf;
    u8  lu8_DispType = 0;
    
    Disp_VersionType(lu8_DispType);
    lu32_TimeBuf = gu32_Sys10ms;
    //��ʾ�汾��ʱ��4�ż��л�����ʱ������ID����ʾ
    while(gu32_Sys10ms - lu32_TimeBuf < 200)
    {
        OPBuzzer();
        gu32_KeyCode = Key_Deal();      //������
        if (gu32_KeyCode == K_SET)
        {
            gu32_SystemState = MODELSETSTATE;
            ModelSet();      //�ͺ�����
            gb_FlashFlg = false;
            Disp_VersionType(lu8_DispType);
            lu32_TimeBuf = gu32_Sys10ms;
        }
        else if (gu32_KeyCode == K_5)
        {
            if ((++lu8_DispType) >= 5)
                lu8_DispType = 0;
            Disp_VersionType(lu8_DispType);
            lu32_TimeBuf = gu32_Sys10ms;
        }
        else if (gu32_KeyCode != K_NONE)         //�������������ص��汾����ʾ
        {
            if (lu8_DispType != 0)
            {
               lu8_DispType = 0;
               Disp_VersionType(lu8_DispType);
               lu32_TimeBuf = gu32_Sys10ms;
            }
        }
        //δ����ADת����AD��ʼ�����ɹ��Ĵ���
        if (lu8_DispType != 0)
            lu32_TimeBuf = gu32_Sys10ms;
    }
    
    if (gs_Setup.PowerOnZeroSwitch != 0)     //�ϵ��Զ����㿪�ش򿪣����ϵ������־λ
        gb_PowerOnZeroFlg = true;
}

/*********************************************************************
��������: u32 Key_Deal(void)
��    ��: ���ذ���ֵ
˵    ��: ��������ȥ���ȴ���
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-11
��    ��:                      ʱ    ��: 
*********************************************************************/
u32 Key_Deal(void)
{
    static u32 KeyPushedTime;
    static u32 u32PreKey=K_NONE;
    static u32 u32AnsedKey=K_NONE;
    static u32 su32_LongKey = K_NONE;
    u32 lu32_Key = 0;
    u32 uicKey;
    
    uicKey = VFD_ReadKey();
    
    if ((gb_KeyLockFlg == false && gb_MbKeyLockFlg == false) || uicKey == K_ZERO || uicKey == K_ESC || uicKey == K_NONE)
    {
        if(uicKey!=u32PreKey){//����ɨ�赽���ϴ�ɨ�赽��ͬ,ȥ������Ӧ
            u32PreKey=uicKey;
            lu32_Key=K_NONE;
            KeyPushedTime=gu32_Sys10ms;
            return K_NONE;
        }
        else
        {                  //��������ɨ�赽��ͬ,��ȷ��һ�ΰ���
            u32PreKey=uicKey;
            if(uicKey!= u32AnsedKey)
            {//���ΰ��µĲ���ԭ�����µ�,������Ӧ
                lu32_Key=uicKey;
                u32AnsedKey=lu32_Key;
                KeyPushedTime=gu32_Sys10ms;
                su32_LongKey = lu32_Key;
    
                //��������
                if(uicKey!=K_NONE)
                {
                    BuzzerStart(5);
                    //�������¸�����˸ʱ�������ʵ����˸ʱ��������Ϩ�������Ҫ������
                    gu32_FlashDelay = gu32_Sys10ms;
                }
            }
            else
            {//���ΰ��µĺ��ϴ���Ӧ����ͬ
                if (gu32_Sys10ms - KeyPushedTime > 500 && uicKey != K_NONE)
                {//500*10 = 5s ����5s����
                    lu32_Key=(uicKey|K_5S);
//                    u32AnsedKey=lu32_Key;
                    //5s�����һ��
                    if(uicKey!=K_NONE && su32_LongKey != lu32_Key)
                    {
                        BuzzerStart(1);
                        //�����ּ����¸�����˸ʱ�������ʵ����˸ʱ��������Ϩ�������Ҫ������
                        gu32_FlashDelay = gu32_Sys10ms;
                    }
                    su32_LongKey = lu32_Key;
                }
                else if(gu32_Sys10ms-KeyPushedTime>200 && uicKey != K_NONE)
                {//200*10=2s ����2������
                    lu32_Key=(uicKey|K_2S);
//                    u32AnsedKey=lu32_Key;
                    //2s�����һ��
                    if(uicKey!=K_NONE && su32_LongKey != lu32_Key)
                    {
                        BuzzerStart(1);
                        //�����ּ����¸�����˸ʱ�������ʵ����˸ʱ��������Ϩ�������Ҫ������
                        gu32_FlashDelay = gu32_Sys10ms;
                    }
                    su32_LongKey = lu32_Key;
                }
                else
                {//�������������δ�� ����Ӧ
                    lu32_Key=K_NONE;
                }
            }//end:���ΰ��µĺ��ϴ���Ӧ����ͬ
        }
    }
    return lu32_Key;
}

/*********************************************************************
��������: void Disp_Echo0(u32 lul_Point, u8 *fucp_DataArry, u8 i)
��    ��: ������ʾ����
˵    ��: 
��ڲ���: lul_Point = С��λ��
          *fucp_DataArry = ��ʾ�����׵�ַ
          i ��ʾ����ĸ���
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-12
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_Echo0(u32 lul_Point, u8 *fucp_DataArry, u8 j)
{
    u8 i;
    
    for (i = 0; i < j - 1 - lul_Point; i++)
    {
        if (fucp_DataArry[i] == SEG_0)
            fucp_DataArry[i] = SEG_BLK;
        else
            break;
    }
}

/*********************************************************************
��������: void Disp_Main_Data(u32 ful_MainDispVal, u32 lul_Point, u8 fuc_DispNumber, bool fb_Echo0, bool fb_Ofl)
��    ��: ����ʾ����
˵    ��: 
��ڲ���: 
          ful_MainDispVal = ��ʾ������ֵ
          lul_Point = С����λ��
          fuc_DispNumber = ��ʾ���ݵ�λ��,���뵱fb_Echo0 = falseʱ�ñ�����������
          fuc_Echo0 = 1���� 0������
          fb_Ofl = 1 OFL
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-12
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_Main_Data(u32 ful_MainDispVal, u32 lul_Point, u8 fuc_DispNumber, bool fb_Echo0, bool fb_Ofl)
{
    u8 i;

    if (fb_Ofl == true)                //��ʾ���
    {
        if (gb_AdOflFlg)    //ad�����ʾLOFL
            VFD_MainDisp_Str("  LOFL");
        else
            VFD_MainDisp_Str("   OFL");
    }
    else
    {
        
        ful_MainDispVal %= 1000000;    //����������6λ���ݵ�ת��
        BIN4toNBCD(ful_MainDispVal, gu8_MainDispArray, 6);
        for (i = 0; i < 6; i++)         //����ֵת������ʾ����
            gu8_MainDispArray[i] = Value_To_SEG[gu8_MainDispArray[i]];
            
        if (lul_Point != 0)             //С������ʾ
            gu8_MainDispArray[5-lul_Point] |= 0x80;
    }
    
    if (fb_Echo0 == true && gb_FlashFlg == false)   //��˸ʱ������
        Disp_Echo0(lul_Point, gu8_MainDispArray, 6);
    else              //������ʱ����ʾλ��������
    {
        for (i = 0; i < 6 - fuc_DispNumber; i++)
            gu8_MainDispArray[i] = SEG_BLK;
    }
    VFD_CopyDispArryToDispRam();
}

/*********************************************************************
��������: void Disp_Aux_Rec(u32 fu32_Num)
��    ��: ����ʾ�䷽��
˵    ��: 
��ڲ���: fu32_Num����ʾ���䷽��
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-25
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_Aux_Rec(u32 fu32_Num)
{
    gu8_AuxDispArray[0] = SEG_R;
    gu8_AuxDispArray[1] = Value_To_SEG[fu32_Num%100/10];
    gu8_AuxDispArray[2] = Value_To_SEG[fu32_Num%10];
}

/*********************************************************************
��������: u32 Key_T9Input(u32 ful_Value)
��    ��: T9���뷨�������ֺ���ĸ֧��
˵    ��: 
��ڲ���: ful_Value = ����ֵ
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-1-2
��    ��:                      ʱ    ��: 
*********************************************************************/
u32 Key_T9Input(u32 ful_Value)
{
  /*T9���뷨ÿ��������Ӧ�����ֺ���ĸ
    1 - 1
    2 - 2 a b c
    3 - 3 d e f
    4 - 4 g h i
    5 - 5 j k l
    6 - 6 m n o
    7 - 7 p q r s
    8 - 8 t u v
    9 - 9 w x y z
    0 - 0 blank  
    ����ֵ0~36�ֱ��Ӧ0~9 a~z��blank
    */
    const u32 cu32_T9_1[] = {1};
    const u32 cu32_T9_2[] = {2, 10, 11, 12};
    const u32 cu32_T9_3[] = {3, 13, 14, 15};
    const u32 cu32_T9_4[] = {4, 16, 17, 18};
    const u32 cu32_T9_5[] = {5, 19, 20, 21};
    const u32 cu32_T9_6[] = {6, 22, 23, 24};
    const u32 cu32_T9_7[] = {7, 25, 26, 27, 28};
    const u32 cu32_T9_8[] = {8, 29, 30, 31};
    const u32 cu32_T9_9[] = {9, 32, 33, 34, 35};
    const u32 cu32_T9_0[] = {0, 36};
    
    static u8 su8_PressCnt = 0;
    static u16 su16_KeyCodeOld;
    
    if (gu32_KeyCode != K_NONE)
    {
        if (su16_KeyCodeOld != gu32_KeyCode)
        {
            su16_KeyCodeOld = gu32_KeyCode;
            su8_PressCnt = 0;
        }
    }
    
    switch (gu32_KeyCode)
    {
        case K_1:
            su8_PressCnt = 0;
            ful_Value = cu32_T9_1[su8_PressCnt];
            break;
        case K_2:
            ful_Value = cu32_T9_2[su8_PressCnt++];
            if (su8_PressCnt > 3)
                su8_PressCnt = 0;
            break;
        case K_3:
            ful_Value = cu32_T9_3[su8_PressCnt++];
            if (su8_PressCnt > 3)
                su8_PressCnt = 0;
            break;
        case K_4:
            ful_Value = cu32_T9_4[su8_PressCnt++];
            if (su8_PressCnt > 3)
                su8_PressCnt = 0;
            break;
        case K_5:
            ful_Value = cu32_T9_5[su8_PressCnt++];
            if (su8_PressCnt > 3)
                su8_PressCnt = 0;
            break;
        case K_6:
            ful_Value = cu32_T9_6[su8_PressCnt++];
            if (su8_PressCnt > 3)
                su8_PressCnt = 0;
            break;
        case K_7:
            ful_Value = cu32_T9_7[su8_PressCnt++];
            if (su8_PressCnt > 4)
                su8_PressCnt = 0;
            break;
        case K_8:
            ful_Value = cu32_T9_8[su8_PressCnt++];
            if (su8_PressCnt > 3)
                su8_PressCnt = 0;
            break;
        case K_9:
            ful_Value = cu32_T9_9[su8_PressCnt++];
            if (su8_PressCnt > 4)
                su8_PressCnt = 0;
            break;
        case K_0:
            ful_Value = cu32_T9_0[su8_PressCnt++];
            if (su8_PressCnt > 1)
                su8_PressCnt = 0;
            break;
        case K_NONE:
            break;
        default:
            break;
    }
    return ful_Value;
}

/*********************************************************************
��������: u32 Key_NumInput(u32 ful_Value, u8 fuc_Len)
��    ��: �������봦������
˵    ��: �˴����ü��̵����ּ��������ݵ����룬fuc_Len == 0ʱ�˺�������ԭ����ֵ
��ڲ���: ful_Value = ���������ֵ�� fuc_Len = ����λ��
�� �� ֵ: ��������������ֵ
��    ��: �Ժ���               ʱ    ��: 2011-1-4
��    ��:                      ʱ    ��: 
*********************************************************************/
u32 Key_NumInput(u32 ful_Value, u8 fuc_Len)
{
#define FirstNumKeyDeal(); if(gb_FirstNumKeyFlg == true) {gb_FirstNumKeyFlg=false;lul_Result=0;gu8_DataInLength=0;}

    bool lb_Flg = false;
    u8 i;
    u32 lul_Result = 1;
    
    if (fuc_Len == 0)
        return ful_Value;
    for (i=0; i < fuc_Len - 1; i++)
        lul_Result *= 10;
    lul_Result = ful_Value % lul_Result;
    lul_Result *= 10;
    
    switch (gu32_KeyCode)
    {
        case K_1:
            FirstNumKeyDeal();
            lul_Result+=1;
            break;
        case K_2:
            FirstNumKeyDeal();
            lul_Result+=2;
            break;
        case K_3:
            FirstNumKeyDeal();
            lul_Result+=3;
            break;
        case K_4:
            FirstNumKeyDeal();
            lul_Result+=4;
            break;
        case K_5:
            FirstNumKeyDeal();
            lul_Result+=5;
            break;
        case K_6:
            FirstNumKeyDeal();
            lul_Result+=6;
            break;
        case K_7:
            FirstNumKeyDeal();
            lul_Result+=7;
            break;
        case K_8:
            FirstNumKeyDeal();
            lul_Result+=8;
            break;
        case K_9:
            FirstNumKeyDeal();
            lul_Result+=9;
            break;
        case K_0:
            FirstNumKeyDeal();
            lul_Result+=0;
            break;
        case K_ZERO:
            lul_Result=0;
            lb_Flg = true;
            gu8_DataInLength = 0;
            break;
        default:
            lul_Result = ful_Value;
            lb_Flg = true;
            break;
    }
    if (lb_Flg == 0)            //������������ּ���������������λ��
    {
        if (++gu8_DataInLength >= 8)    //�������볤���ж�ʹ�ã���ͨ����6λ������7λ���������8�㹻
            gu8_DataInLength = 8;
    }
    
    return lul_Result;
}

/*********************************************************************
��������: u32 Key_IncInput(u32 ful_Value, u8 fuc_Min, u8 fuc_Max)
��    ��: �������������봦��
˵    ��: 
��ڲ���: ful_Value = ����ֵ fuc_Min = ��Сֵ fuc_Max = ���ֵ
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-2-17
��    ��:                      ʱ    ��: 
*********************************************************************/
u32 Key_IncInput(u32 ful_Value, u8 fuc_Min, u8 fuc_Max)
{
    if(gu32_KeyCode == K_INC)
    {
        ful_Value++;
        if (ful_Value > fuc_Max)
            ful_Value = fuc_Min;
    }
    return ful_Value;
}

/*********************************************************************
��������: void ErrorDeal(u8 fuc_Number, u32 ful_Time)
��    ��: ���󱨾�����ش���
˵    ��: 
��ڲ���: fuc_Number �����  Ϊ0ʱ�޴����
          ful_Time ��ʾ���������ʱ�䣨��λΪ10ms��  Ϊ0ʱһֱ��ʾ
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-12
��    ��:                      ʱ    ��: 
*********************************************************************/
void ErrorDeal(u8 fuc_Number, u32 ful_Time)
{
    gb_DispErrorFlg = true;            //��ʾ�����־λ

//    if (fuc_Number == 0)
//    {
        //���֮ǰ����Ų�Ϊ0����ô����ԭ�д���ţ���ֹ���´�����˳���ԭ���Ĵ���ű仯
        //���籨��error1������������ñ���error�����˳�error1�����error
//        if (gu8_DispErrorNumber != 0)
//        {
//            gu8_DispErrorNumberBackup = gu8_DispErrorNumber;
//            gu8_DispErrorNumber = fuc_Number;
//        }
//        else
            gu8_DispErrorNumber = fuc_Number;
//    }
//    else
//    {
//        if (gu8_DispErrorNumber != SEG_BLK)
//        {
//            gu8_DispErrorNumberBackup = gu8_DispErrorNumber;
//            gu8_DispErrorNumber = Value_To_SEG[fuc_Number];       //�õ�����ŵ���ʾֵ
//        }
//        else
//            gu8_DispErrorNumber = Value_To_SEG[fuc_Number];       //�õ�����ŵ���ʾֵ
//    }
    
    if (ful_Time == 0)
        gb_HandClrErrorFlg = true;     //�������ֶ������־λ
    else
    {
        gb_HandClrErrorFlg = false;
        gu32_DispErrorTime = ful_Time;           //�������ʾ����ʱ��
        gu32_ErrTimeDelay = gu32_Sys10ms;            //���浱ǰʱ��
        BuzzerStart(50);
    }
}

/*********************************************************************
��������: void Disp_Error(void)
��    ��: ��ʾ���󱨾���Ϣ����
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-12
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_Error(void)
{
    if (gb_HandClrErrorFlg == false)            //����Ҫ�ֶ������error��������ʾ��Ӧgu32_DispErrorTimeʱ��
    {
        if (gu32_Sys10ms - gu32_ErrTimeDelay >= gu32_DispErrorTime)
        {
            gb_DispErrorFlg = false;
            if (gb_AlarmFlg)
            {
                gb_AlarmFlg = false;
            }
            
//            //���֮ǰ����ű���������˵��֮ǰ�д�����ʾû����������»ָ�ԭ�еĴ������ʾ
//            if (gu8_DispErrorNumberBackup != 0)
//            {
//                gu8_DispErrorNumber = gu8_DispErrorNumberBackup;
//                gu8_DispErrorNumberBackup = 0;
//            }
//            else
                gu8_DispErrorNumber = 0;
        }
    }
    
    gu8_MainDispArray[0] = SEG_E;
    gu8_MainDispArray[1] = SEG_r;
    gu8_MainDispArray[2] = SEG_r;
    if (gu8_DispErrorNumber == 0)
    {
        gu8_MainDispArray[3] = SEG_o;
        gu8_MainDispArray[4] = SEG_r;
        gu8_MainDispArray[5] = SEG_BLK;
    }
    else
    {
        gu8_MainDispArray[3] = SEG_BLK;
        gu8_MainDispArray[4] = Value_To_SEG[gu8_DispErrorNumber%100/10];
        gu8_MainDispArray[5] = Value_To_SEG[gu8_DispErrorNumber%10];
    }
}

/*********************************************************************
��������: void Flash_MainDisp(u8 fuc_Postion)
��    ��: ����ʾ��˸
˵    ��: fuc_Postion^0~fuc_Postion^5�ֱ������ʾ�����λ�����λ6λ����1������˸
��ڲ���: fuc_Position = ��˸λ
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-12
��    ��:                      ʱ    ��: 
*********************************************************************/
void Flash_MainDisp(u8 fuc_Postion)
{
    u8 i;
    
    if (gb_FlashFlg == true)
    {
        if(gu32_Sys10ms - gu32_FlashDelay > 45)
        {
            for (i = 0; i <= 5; i++)
            {
                if (fuc_Postion&0x20 >> i)
                    gu8_MainDispArray[i] = SEG_BLK;
            }
            
            if(gu32_Sys10ms - gu32_FlashDelay > 90)
            {
                gu32_FlashDelay = gu32_Sys10ms;
            }
        }
    }
}

/*********************************************************************
��������: bool Flash_Flg(bool fb_State)
��    ��: ��־λ��˸
˵    ��: ����ָʾ����˸����
��ڲ���: fb_State ��Чʱ����������ֵ����˸
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-2-12
��    ��:                      ʱ    ��: 
*********************************************************************/
bool Flash_Flg(bool fb_State)
{
    bool lb_Result;
    static u32 su32_FlashDelay = 0;
    
    if (fb_State == true)
    {
        if(gu32_Sys10ms - su32_FlashDelay > 40)
        {
            lb_Result = false;
            if(gu32_Sys10ms - su32_FlashDelay > 80)
            {
                su32_FlashDelay = gu32_Sys10ms;
                lb_Result = true;
            }
        }
        else
            lb_Result = true;
    }
    else
        lb_Result = false;
        
    return lb_Result;
}

/*********************************************************************
��������: void Flash_AuxDisp(u8 fuc_Postion)
��    ��: ����ʾ��˸
˵    ��: fuc_Postion^0~fuc_Postion^5�ֱ������ʾ�����λ�����λ6λ����1������˸
��ڲ���: fuc_Position = ��˸λ
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-25
��    ��:                      ʱ    ��: 
*********************************************************************/
void Flash_AuxDisp(u8 fuc_Postion)
{
    u8 i;
    
    if (gb_FlashFlg == true)
    {
        if(gu32_Sys10ms - gu32_FlashDelay > 45)
        {
            for (i = 0; i <= 2; i++)
            {
                if (fuc_Postion&0x04 >> i)
                    gu8_AuxDispArray[i] = SEG_BLK;
            }
            
            if(gu32_Sys10ms - gu32_FlashDelay > 90)
            {
                gu32_FlashDelay = gu32_Sys10ms;
            }
        }
    }
}

/*********************************************************************
��������: void Disp_InputCode(void)
��    ��: ����������ʾ
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-12
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_InputCode(void)
{
    u8 i,j;
    u8 luc_CodeInputTime = 0;        //��������Ĵ������
    
    VFD_AuxDisp_Str("PAS");
    
    switch(gu32_SystemState)
    {
        case RESETSTATE:
            luc_CodeInputTime = gu8_ResetInTime;
            break;
        case SUMSTATE:
            luc_CodeInputTime = gu8_SumCheckInTime;
            break;
        case SETUPSTATE:
            luc_CodeInputTime = gu8_SetupInTime;
            break;
        case CALIBSTATE:
            luc_CodeInputTime = gu8_CalibInTime;
            break;
        case IOTESTSTATE:
            luc_CodeInputTime = gu8_IoTestInTime;
            break;
        case IODEFINESTATE:
            luc_CodeInputTime = gu8_IoDefInTime;
            break;
        case RECIPESTATE:
            luc_CodeInputTime = gu8_RecInTime;
            break;
        case SHUTDOWNSTATE:
            luc_CodeInputTime = gu8_ShutDownInTime;
            break;
        case MODELSETSTATE:
            luc_CodeInputTime = gu8_ModelSetInTime;
            break;
        case BORRSTATE:
            luc_CodeInputTime = gu8_BorRInTime;
            break;
        default:
            break;
    }
    
    if (luc_CodeInputTime == 0)             //��ʾ------
    {
        VFD_MainDisp_Str("------");
    }
    else if (luc_CodeInputTime == 1)        //��ʾ======
    {
        VFD_MainDisp_Str("======");
    }
    else                                    //��ʾ�ԡԡԡԡԡ�
    {
        VFD_MainDisp_Str("######");
    }
    
    for (i = gu8_DataInLength, j = 5; i > 0; i--, j--)
    {
        gu8_MainDispArray[j] = SEG_8;
        if (j == 0)     //gu8_DataInLength���Ϊ8���п��ܵ���j--С��0���������
            break;
    }
}

/*********************************************************************
��������: void Disp_OnOff(u32 ful_Data)
��    ��: ����״̬On OFF ��ʾ
˵    ��: 
��ڲ���: ful_Data == 0��ʾOFF��������ʾOn
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-20
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_OnOff(u32 ful_Data)
{
    if (ful_Data == 0)
        VFD_MainDisp_Str("   OFF");
    else
        VFD_MainDisp_Str("    ON");
}

/*********************************************************************
��������: void Disp_FlapOnOff(u32 ful_Data)
��    ��: �Ĵ�����״̬��ʾ
˵    ��: 
��ڲ���: ful_Data == 0��1��2��3 ��ʾ PoFF PF- P-d PFd
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-3-15
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_FlapOnOff(u32 ful_Data)
{
    if (ful_Data == 0)
        VFD_MainDisp_Str("  POFF");
    else if (ful_Data == 1)
        VFD_MainDisp_Str("   PF-");
    else if (ful_Data == 2)
        VFD_MainDisp_Str("   P-D");
    else
        VFD_MainDisp_Str("   PFD");
}

/*********************************************************************
��������: void Disp_TareMode(u32 ful_Data)
��    ��: ����ģʽѡ����ʾ
˵    ��: 
��ڲ���: ful_Data == 0��ʾbinyES��������ʾBinno
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-20
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_TareMode(u32 ful_Data)
{
    switch (ful_Data)
    {
        case BINYES:
            VFD_MainDisp_Str("BINYES");
            break;
        case BINNO:
            VFD_MainDisp_Str("BIN NO");
            break;
        case BIN2_A:
            VFD_MainDisp_Str("BIN2-A");
            break;
        case BIN2_B:
            VFD_MainDisp_Str("BIN2-B");
            break;
        case NO2_A:
            VFD_MainDisp_Str(" NO2-A");
            break;
        case NO2_B:
            VFD_MainDisp_Str(" NO2-B");
            break;
    }
}

/*********************************************************************
��������: void Disp_GorNMode(u32 ful_Data)
��    ��: �޶�ë������ʾ
˵    ��: 
��ڲ���: ful_Data == 0��ʾnEt��������ʾgroSS
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-20
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_GorNMode(u32 ful_Data)
{
    if (ful_Data == GROSS)
        VFD_MainDisp_Str(" GROSS");
    else
        VFD_MainDisp_Str("   NET");
}

/*********************************************************************
��������: void Disp_BaudRate(u32 ful_Data)
��    ��: ��������ʾ
˵    ��: 
��ڲ���: ful_Data = 0      2400
                     1      4800
                     2      9600
                     3      19200
                     4      38400
                     5      57600
                     6      115200
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-20
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_BaudRate(u32 ful_Data)
{
    switch(ful_Data)
    {
        case 0:
            VFD_MainDisp_Str("  2400");
            break;
        case 1:
            VFD_MainDisp_Str("  4800");
            break;
        case 2:
        default:
            VFD_MainDisp_Str("  9600");
            break;
        case 3:
            VFD_MainDisp_Str(" 19200");
            break;
        case 4:
            VFD_MainDisp_Str(" 38400");
            break;
        case 5:
            VFD_MainDisp_Str(" 57600");
            break;
        case 6:
            VFD_MainDisp_Str("115200");
            break;
        case 7:
            VFD_MainDisp_Str("128000");
            break;
        case 8:
            VFD_MainDisp_Str("192000");
            break;
        case 9:
            VFD_MainDisp_Str("230400");
            break;
        case 10:
            VFD_MainDisp_Str("256000");
            break;
    }
}

/*********************************************************************
��������: void Disp_GSDType(u32 ful_Data)
��    ��: GSD������ʾ
˵    ��: 
��ڲ���: ful_Data = 0      GSD-1
                     1      GSD-2
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-4-16
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_GSDType(u32 ful_Data)
{
    if (ful_Data == 0)
        VFD_MainDisp_Str(" GSD-1");
    else
        VFD_MainDisp_Str(" GSD-2");
}

/*********************************************************************
��������: void Disp_ComMode(u32 ful_Data)
��    ��: ͨѶЭ����ʾ
˵    ��: 
��ڲ���: ful_Data == 0��ʾprint
                      1��ʾcont
                      2��ʾread
                      3��ʾbus 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-20
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_ComMode(u32 ful_Data)
{
    switch(ful_Data)
    {
        case 0:
            VFD_MainDisp_Str(" PRINT");
            break;
        case 1:
        default:
            VFD_MainDisp_Str("  CONT");
            break;
        case 2:
            VFD_MainDisp_Str("  READ");
            break;
        case 3:
            VFD_MainDisp_Str("READ-O");
            break;
        case 4:
            VFD_MainDisp_Str(" BUS-R");
            break;
        case 5:
            VFD_MainDisp_Str(" BUS-A");
            break;
        case 6:
            VFD_MainDisp_Str("  PBUS");
            break;
    }
}

/*********************************************************************
��������: void Disp_FeedMode(u32 ful_Data)
��    ��: Ͷ�Ϸ�ʽ��ʾ
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��:2013-12-20
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_FeedMode(u32 ful_Data)
{
    if (ful_Data == 0)          //co
        VFD_MainDisp_Str("    CO");
    else                        //Sin
        VFD_MainDisp_Str("   SIN");
}

/*********************************************************************
��������: void Disp_ParityMode(u32 ful_Data)
��    ��: У�鷽ʽѡ��
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2013-12-20
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_ParityMode(u32 ful_Data)
{
    switch(ful_Data)
    {
        case 0:
            VFD_MainDisp_Str("  18N2");
            break;
        case 1:
        default:
            VFD_MainDisp_Str("  18E1");
            break;
        case 2:
            VFD_MainDisp_Str("  18O1");
            break;
        case 3:
            VFD_MainDisp_Str("  18N1");
            break;
        case 4:
            VFD_MainDisp_Str("  17N2");
            break;
        case 5:
            VFD_MainDisp_Str("  17E1");
            break;
        case 6:
            VFD_MainDisp_Str("  17O1");
            break;
    }
}

/*********************************************************************
��������: void Disp_HiLo(u32 ful_Data)
��    ��: MODBUS˫�ּĴ����ߵ��ִ洢˳��HiLo  LoHi
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-3
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_HiLo(u32 ful_Data)
{
    if (ful_Data == 0)          //HiLo
        VFD_MainDisp_Str("  HILO");
    else                        //LoHi
        VFD_MainDisp_Str("  LOHI");
}

/*********************************************************************
��������: void Disp_PrintType(u32 ful_Data)
��    ��: 
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2014-04-11
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_PrintType(u32 ful_Data)
{
    if (ful_Data == 0)
        VFD_MainDisp_Str("    16");
    else if (ful_Data == 1)
        VFD_MainDisp_Str("    32");
    else 
        VFD_MainDisp_Str("    80");
}

/*********************************************************************
��������: void Disp_No2PackOffTwoSwitch(u32 fu32_Data)
��    ��: ˫�޶��ӻ���ģʽͬʱ�ɴ����ص���ʾ
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2015-02-02
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_No2PackOffTwoSwitch(u32 fu32_Data)
{
    if (fu32_Data == 0)
        VFD_MainDisp_Str("   OFF");
    else if (fu32_Data == 1)
        VFD_MainDisp_Str("   ON1");
    else 
        VFD_MainDisp_Str("   ON2");
}

/*********************************************************************
��������: void Disp_PrintLanguage(u32 ful_Data)
��    ��: MODBUS˫�ּĴ����ߵ��ִ洢˳��HiLo  LoHi
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-3
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_PrintLanguage(u32 ful_Data)
{
    if (ful_Data == 0)          //Chn
        VFD_MainDisp_Str("   CHN");
    else                        //Eng
        VFD_MainDisp_Str("   ENG");
}

/*********************************************************************
��������: void Disp_AdSamplingRate(u32 ful_Data)
��    ��: AD�����ٶ�
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-3
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_AdSamplingRate(u32 ful_Data)
{
    switch(ful_Data)
    {
        case 0:
        default:
            VFD_MainDisp_Str("   120");
            break;
        case 1:
            VFD_MainDisp_Str("   240");
            break;
        case 2:
            VFD_MainDisp_Str("   480");
            break;
        case 3:
            VFD_MainDisp_Str("   960");
            break;
    }
}


/*********************************************************************
��������: void Disp_ExtType(u32 ful_Data)
��    ��: ��չ������
˵    ��: 
��ڲ���: 
�� �� ֵ: 
��    ��: �Ժ���               ʱ    ��: 2011-5-3
��    ��:                      ʱ    ��: 
*********************************************************************/
void Disp_ExtType(u32 ful_Data)
{
    switch(ful_Data)
    {
        case 0:
        default:
            VFD_MainDisp_Str(" UT-PT");
            break;
        case 1:
            VFD_MainDisp_Str(" UT-DA");
            break;
        case 2:
            VFD_MainDisp_Str(" UT-PB");
            break;
        case 3:
            VFD_MainDisp_Str(" DA-PB");
            break;
    }
}