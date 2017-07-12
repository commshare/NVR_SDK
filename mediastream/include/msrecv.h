#ifndef _MS_RECV_H_
#define _MS_RECV_H_

#include "msrtp.h"

typedef struct
{
	u8	m_byMediaType;
	u16 m_wSeq;
	u32 m_dwTimeStamp;
    u32 m_dwSSRC;
	u32 m_dwWritePos;
	//Number of least significant bits 
	//that should be ignored in the last data octet.
	u8  m_byEndBit;
}TLastInfo;

typedef struct
{
	u8		m_byPackNum;//����С����
	u8		m_byIndex;
	s32		m_nMode;
	s32		m_nRate;
	u32		m_dwFrameId;
	u16		m_wWidth;
	u16		m_wHeight;
}TMp4Header;

typedef struct
{
	u32		m_dwTimeStamp;
	u32		m_dwFrameId;
	u8		m_byMediaType;
	u8		m_byFrameRate;
	u8		m_bAudioMode;
	BOOL	m_bKeyFrame;
	u16		m_wWidth;
	u16		m_wHeiht;
	u16		m_wStartSeq;
	u32		m_dwPackLen;
	u32		m_dwPackNum;//����С����
	u8		m_lpBuf[MAX_FRAME_SIZE];
	u8		m_byMakerIndex;//���һ��Index;
	u8		m_byBit[0xff];
}TPackInfo;

typedef struct
{
	BOOL	bInvalid;
	u16		m_wSeq;
	u8	    m_byMode;
	u8	    m_byMediaType;
	u32		m_dwTimeStamp;
	u8		m_pBuf[MAX_PACK_SIZE+1];
	INT32	m_nLen;
}TAudioPack;

//��Ƶ��������Ϣ
typedef struct
{
	BOOL	m_bSave; //�Ƿ��Ѿ�����
	u16		m_wMinSeq;
	//u16 m_wWaitSeq; //��Ⱥ��sequence;
	TAudioPack m_tAudioPack[MAX_AUDIO_PACK_NUM];
}TAudioInfo;

typedef struct
{
	u32 m_dwTimeStamp;
}TCBPackInfo;

#define INSERT_NEW_MIN_POS   (u16)1   //�ȶ������λ��С
#define INSERT_NEW_MID_POS   (u16)2   //���ڶ����м�
#define INSERT_NEW_MAX_POS   (u16)3   //�ȶ������λ����

typedef struct ifly_netrcv_t
{
	ifly_rtp_t		*m_pcRtp;
	
	ms_rtcp_t		*m_pcRtcp;//2008-11-20 csp add
	
	u8				*m_pFrameBuf; 
	TLastInfo		m_tLastInfo;
	TPackInfo		*m_ptPackInfo[MAX_PACK_QUENE_NUM+1];
	TAudioInfo		*m_ptAudioInfo;
	
	TCBPackInfo		*m_ptCBPackInfo[MAX_PACK_QUENE_NUM*2+1];//��¼�Ѿ��ص����ϲ����������Ϣ����ֹ�ظ��ص����ϲ�
	
	TMp4Header		m_tMp4Header;
	FRAMEHDR		m_FrmHdr;
	
	u32				m_dwFrameId;
	u32				m_dwTimeStamp;
	
	BOOL			m_bConfuedAdjust;	//���� (mp3) �Ƿ����������
	
	BOOL			m_bRepeatSend;		//���� (mp4/H.264) �Ƿ��ط�
	TRSParam		m_tRSParam;
	
	TRtcpSDESRSQ	m_tSndRSQ;			//�ط������//2008-11-20 csp add
	
	u32				m_dwQueneNum;		//���������������е�ʵ��֡��
	u32				m_dwMaxQueneNum;	//���������������е����洢֡��
	
	u32				m_dwMinTimeStamp;	//���������������е� ���λ[] ��Ӧ��ʱ���
	u32				m_dwMaxTimeStamp;	//���������������е� ���λ[��ʵ��֡] ��Ӧ��ʱ���
	u32				m_dwLastTimeStamp;	//�ϴλص��������� ��Ӧ��ʱ���
	
	SEMHANDLE		m_hSem;
	
	u32				m_dwLastSSRC;
	
	u32				m_dwMaxFrameSize;//���֡��С
	PFRAMEPROC		m_pFrameCallBackHandler;//�ص�������ָ��
    PRTPCALLBACK	m_pRtpCallBackHandler;//RTP�ص�������
	u32				m_dwContext;//�û�����
	
	BOOL            m_bRcvStart;//�Ƿ�ʼ����
	
	TRcvStatus		m_tRcvStatus;
	TRcvStatistics  m_tRcvStatistics;
	
	TLocalNetParam	m_tLocalNetParam;//�����������
}ifly_netrcv_t;

#ifdef __cplusplus
extern "C" {
#endif

ifly_netrcv_t* CreateNetRcv(u32 dwMaxFrameSize, PFRAMEPROC pFrameCallBackProc, u32 dwContext, u32 dwSSRC);
ifly_netrcv_t* CreateNetRcvRtp(u32 dwMaxFrameSize, PRTPCALLBACK pRtpCallBackProc, u32 dwContext, u32 dwSSRC);

u16  SetNetRcvLocalParam(ifly_netrcv_t *pRcv,TLocalNetParam tLocalNetParam);
u16  RemoveNetRcvLocalParam(ifly_netrcv_t *pRcv);

u16  ResetNetRcvRSFlag(ifly_netrcv_t *pRcv, TRSParam tRSParam, BOOL bRepeatSnd);

u16  StartNetRcv(ifly_netrcv_t *pRcv);
u16  StopNetRcv(ifly_netrcv_t *pRcv);

u16  GetNetRcvStatus(ifly_netrcv_t *pRcv,TRcvStatus *pRcvStatus);
u16  GetNetRcvStatistics(ifly_netrcv_t *pRcv,TRcvStatistics *pRcvStatistics);

u16  FreeNetRcvBuf(ifly_netrcv_t *pRcv);
u16  DestroyNetRcv(ifly_netrcv_t *pRcv);

void DealNetRcvData(ifly_netrcv_t *pRcv,TRtpPack *pRtpPack);
void RcvCallBack(TRtpPack *pRtpPack, u32 dwContext);

u16  DealNetRcvRtcpTimer(ifly_netrcv_t *pRcv);

void DealG711(ifly_netrcv_t *pRcv,TRtpPack *pRtpPack);
void DealG723(ifly_netrcv_t *pRcv,TRtpPack *pRtpPack);
void DealG722(ifly_netrcv_t *pRcv,TRtpPack *pRtpPack);
void DealG728(ifly_netrcv_t *pRcv,TRtpPack *pRtpPack);

void DealMpg4(ifly_netrcv_t *pRcv,TRtpPack *pRtpPack);
void DealH264(ifly_netrcv_t *pRcv,TRtpPack *pRtpPack);
void DealMp3(ifly_netrcv_t *pRcv,TRtpPack *pRtpPack);

void DealMpg4_RSCheck(ifly_netrcv_t *pRcv,TRtpPack *pRtpPack);

BOOL FindCBQuene(ifly_netrcv_t *pRcv,u32 dwTimeStamp);
void FillCBQuene(ifly_netrcv_t *pRcv,u32 dwTimeStamp);
s32  FindFullQuene(ifly_netrcv_t *pRcv);

void CallBackAndSerial(ifly_netrcv_t *pRcv,BOOL bDisCard);//bDisCardĬ��FALSE
void InsertQuene(ifly_netrcv_t *pRcv,TRtpPack *pRtpPack,u16 wPos);

void DealNetRcvRSQSndQuest(ifly_netrcv_t *pRcv,u32 dwTimeStamp);
void SendNetRcvRSQSndQuest(ifly_netrcv_t *pRcv,u32 dwIndex);

//csp add 2008-11-28
void DealNetRcvFrameLoseEvent(ifly_netrcv_t *pRcv,u32 m_dwFrameId);
void SendNetRcvFrameLoseEvent(ifly_netrcv_t *pRcv,u32 m_dwFrameId);

#ifdef __cplusplus
}
#endif

#endif
