#ifndef _MS_SEND_H_
#define _MS_SEND_H_

#include "msrtp.h"

typedef struct ifly_netsnd_t
{
	ifly_rtp_t			*m_pcRtp;
	
	ms_rtcp_t			*m_pcRtcp;//csp add 2008-11-20
	
//	TH261HeaderList		*m_ptH261HeaderList;
//	TH263HeaderList		*m_ptH263HeaderList;
	
//	TRtpPack			m_tOldRtp;
//	TRtpPack			m_tOldRtp;//csp add 2008-11-20
	
	u32					m_dwFrameId;
	u32					m_dwTimeStamp;
	u8					m_byFrameRate;
	
	u8					m_byMediaType; 
	u32					m_dwMaxFrameSize;
	
	u8					m_byExBuf[MAX_PACK_EX_LEN]; 
	
	s32					m_nMaxSendNum;//���ݴ�����������ʹ���;
	
	TSndStatus			m_tSndStatus;
	TSndStatistics		m_tSndStatistics;
	
//	FRAMEHDR			m_tSelfFrmHdr;
//	u8					*m_pSelfFrameBuf;	
	
	BOOL32				m_bRepeatSend;//�Ƿ��ط�
	u16					m_wBufTimeSpan;
	
	
	
	//csp add 2008-11-28
	u32					m_dwNewKeyFrameId;
	u32					m_dwLoseFrameId;
}ifly_netsnd_t;

#ifdef __cplusplus
extern "C" {
#endif

//��������ģ��
ifly_netsnd_t* CreateNetSnd(u32 dwMaxFrameSize, u32 dwNetBand, u8 byFrameRate, u8 byMediaType, u32 dwSSRC);

//ɾ������ģ��
u16 DestroyNetSnd(ifly_netsnd_t* pSnd);

//�������緢�Ͳ���(���еײ��׽��ֵĴ������󶨶˿�,�Լ�����Ŀ���ַ���趨�ȶ���)
u16 SetNetSndNetParam(ifly_netsnd_t* pSnd,TNetSndParam tNetSndParam);

//�Ƴ����緢�ͱ��ص�ַ����(���еײ��׽��ֵ�ɾ�����ͷŶ˿ڵȶ���)
u16 RemoveNetSndLocalNetParam(ifly_netsnd_t* pSnd);

//����֡ID
u16 ResetNetSndFrameId(ifly_netsnd_t* pSnd);
//����ͬ��ԴSSRC
u16 ResetNetSndSSRC(ifly_netsnd_t* pSnd,u32 dwSSRC);

//���÷��Ͷ˶���mpeg4����H.264���õ��ش�����Ŀ���,�رպ󣬽������Ѿ����͵����ݰ����л���
u16 ResetNetSndRSFlag(ifly_netsnd_t* pSnd, u16 wBufTimeSpan, BOOL32 bRepeatSnd);

//���÷���ѡ��
u16 SetNetSndInfo(ifly_netsnd_t* pSnd, u32 dwNetBand, u8 byFrameRate);
//�������ݰ�
u16 SendFrame(ifly_netsnd_t* pSnd,PFRAMEHDR pFrmHdr,int avgInterTime);//06-11

//�õ�״̬
u16 GetNetSndStatus(ifly_netsnd_t* pSnd,TSndStatus *pSndStatus);
//�õ�ͳ��
u16 GetNetSndStatistics(ifly_netsnd_t* pSnd,TSndStatistics *pSndStatistics);
//�õ����Ͷ˸߼����ò���(�ش���)
u16 GetNetSndAdvancedInfo(ifly_netsnd_t* pSnd,TAdvancedSndInfo *pAdvancedSndInfo);

u16 DealNetSndRtcpTimer(ifly_netsnd_t* pSnd);

//csp add 2008-11-28
u16 DealNetSndFrameLoseEvent(TRtcpSDESLose *ptLose, u32 dwContext);

#ifdef __cplusplus
}
#endif

#endif
