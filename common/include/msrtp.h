#ifndef _MS_RTP_H_
#define _MS_RTP_H_

#include "mssocket.h"

#include "msrtcp2.h"

typedef void (*PRCVPROC)(TRtpPack *ptRtpPack, u32 dwContext);

typedef struct ifly_rtp_t
{
	ms_rtcp_t	*m_pRtcp;
	
	ifly_socket_t *m_pSocket;
	TLoopBuf    *m_pLoopBuf;
	
	TAddr       m_tLocalAddr;
	TRemoteAddr m_tRemoteAddr;
	
	u32			m_dwSSRC;
	u16         m_wSeqNum;
	
    //RTP FIXED HEADER;
	u32			m_dwRtpHeader[RTP_FIXEDHEADER_SIZE/sizeof(u32)];
	u8			*m_pPackBuf;  
	
	PRCVPROC    m_pCallBack;
	u32			m_dwContext;
	
	
	BOOL		m_bRepeatSend;  //�Ƿ��ط�
	SEMHANDLE   m_hSynSem;		//�����ط����λ���ķ��ʻ���
	u8			*m_pRSPackBuf;
	u8			*m_pRLoopBuf;   //�ط����λ���
	u16		    m_wRLBUnitNum;  //�ط����λ�����С���ռ�����//3.0
	u16			m_wRLBWritePos;
	BOOL		m_bIsRLBFull;   //�ط����λ����Ƿ�����
	BOOL		m_bIsRLBWrited; //�ط����λ����Ƿ���д�룬��������СSN�ļ�¼
	INT32		m_nRLBUnitSize; //�ط����λ����е�λ����
	u16			m_wRLBMinSN;    //�ط����λ�����С����С�����
	u16			m_wRLBMinPos;   //�ط����λ������С���С����Ӧ������λ��
	
	
	u32			m_dwTotalPackNum;  //���͵��ܵ�С����
}ifly_rtp_t;

#ifdef __cplusplus
extern "C" {
#endif

ifly_rtp_t* CreateRtp(u32 dwSSRC, BOOL32 bAllocLPBuf);//csp modify 2008-11-20

void InitRtp(ifly_rtp_t *pRtp);
u16  DestroyRtp(ifly_rtp_t *pRtp);
void FreeRtpBuf(ifly_rtp_t *pRtp);

u16  SetRtpRtcp(ifly_rtp_t *pRtp, ms_rtcp_t *pRtcp);

u16  SetRtpCallBack(ifly_rtp_t *pRtp, PRCVPROC pCallBackHandle, u32 dwContext);

u16  SetRtpLocalAddr(ifly_rtp_t *pRtp,u32 dwIp, u16 wPort, BOOL bRcv);
u16  RemoveRtpLocalAddr(ifly_rtp_t *pRtp);
u16  SetRtpRemoteAddr(ifly_rtp_t *pRtp,TRemoteAddr *pRemoteAddr);
u16  WriteRtpPack(ifly_rtp_t *pRtp,TRtpPack *pRtpPack, BOOL bSend);
u16  SendRtpPack(ifly_rtp_t *pRtp,INT32 nPackNum,INT32 *pnRealPackNum);//csp modify 2008-11-28
void ResetRtpSeq(ifly_rtp_t *pRtp);
void ResetRtpSSRC(ifly_rtp_t *pRtp,u32 dwSSRC);

u16  ResetRtpRSFlag(ifly_rtp_t *pRtp, u16 wRLBUnitNum, BOOL32 bRepeatSnd);//csp modify 2008-11-20

void RtpCallBackProc(u8 *pBuf, s32 nSize, u32 dwContext);
void DealRtpData(ifly_rtp_t *pRtp, u8 *pBuf, s32 nSize);

u16  DealRtpRSQBackQuest(ifly_rtp_t *pRtp, TRtcpSDESRSQ *ptRSQ);//csp modify 2008-11-28

u16  CheckPackAvailabe(const TRtpPack *ptRtpPack, s32 *pnHeadLen);
u16  DirectSendRtpPack(ifly_rtp_t *pRtp, u8 *pPackBuf, s32 nPackLen, u32 dwTimeStamp);
u16  SaveRtpPackIntoLPBuf(ifly_rtp_t *pRtp, u8 *pPackBuf, s32 nPackLen, BOOL32 bTrans);
u16  WriteRtpPackIntoRLB(ifly_rtp_t *pRtp, u8 *pPacketBuf, s32 nPacketSize);
u16  ReadRtppackRLBBySN(ifly_rtp_t *pRtp, u8 *pBuf, s32 *pnBufSize, u32 dwTimeStamp, u16 wSeqNum);
s32  FindRtppackRLBByTS(ifly_rtp_t *pRtp, u8 *pBuf, u8 *pbyPackNum, u32 dwTimeStamp);

#ifdef __cplusplus
}
#endif

#endif
