#ifndef _RTCP_H_
#define _RTCP_H_

#include "iflytype.h"

#include "mssend.h"
#include "msrecv.h"
#include "mssocket.h"

#ifdef __cplusplus 
extern "C"{
#endif /* __cplusplus */

#pragma pack(push,1)//��Ӧ???

typedef struct ifly_rtcp_t
{
	ifly_socket_t* m_hSocketSnd;
	ifly_socket_t* m_hSocketRcv;
	TAddr       m_tLocalAddr;
	TRemoteAddr m_tRemoteAddr;
	int			m_nLastSndPackNum;
	int			m_nLastRcvPackNum;
}ifly_rtcp_t;

/*RTCP ���ĸ������ͳ���*/
#define RTP_RTCP_SR   200
#define RTP_RTCP_RR   201

/* RR �����߱��������Ŀ�����ݽṹ, Ҳ�������߱�������ݽṹ, ������ȫ��ͬ. */
typedef struct RECEIVE_REPORT_PACKET_STRU
{
    /* ����˱������Դ */
    unsigned int udwSsrc;          
    
    /* ���յ��ϸ�SR/RR����, �������� */
    unsigned int bit8Fraction:8;   
    
    /* �Դӽ�������,���Ը�Դ�Ķ������� */
    unsigned int bit24LostNum:24;  
    
    /* �Ӹ�Դ�յ���RTP����������к�. ��16-bit�����к����ڵ���Ӧֵ(���ؾ����),
    ��16-bit���յ���RTP����������к�. */
    unsigned int udwLastSeq;       
    
    /* ���ݰ�������ʱ��ͳ�Ʊ�������ֵ */
    unsigned int udwJitter;        
    
    /* �Ӹ�Դ�յ�����һ��RTCP SR����NTPʱ�����м�32-bit */
    unsigned int udwLsr;           
    
    /* �Ӹ�Դ�յ��ϸ�RR�������ʹ˰�֮��ļ��, ��λʱ1/65536�� */
    unsigned int udwDlsr;          
} RR_LIST, SR_LIST;

/* �����߱����(SR) */
typedef struct SEND_REPORT_STRU 
{
    unsigned int udwSsrc;               
    unsigned int udwNtpMsw;             
    unsigned int udwNtpLsw;
    unsigned int udwRtpTimeStamp;              
    unsigned int udwSentRtpNum;              
    unsigned int udwSentRtpOctetCount;              
    //SR_LIST    SrList[1];
} SEND_REPORT;

/* �����߱����(RR) */
typedef struct RECEIVE_REPORT_STRU 
{
	unsigned int udwSsrc;      
    RR_LIST    RrList[1];   
} RECEIVE_REPORT;

/* 5�����Ͱ�����:SR,RR,SDSE,BYE,APP. */
typedef union RTCP_PACKET_TYPE_STRU 
{
    /* �����߱����(SR) */
    SEND_REPORT SR;
	
    /* �����߱����(RR) */        
    RECEIVE_REPORT RR;
	
    /* Դ�����������(SDES) */
    //SDES_REPORT SDES;
	
    /* ָʾ������˳������(BYE) */
    //BYE_REPORT BYE;
} RTCP_PACKET_TYPE;

/* RTCP���ư���ͷ�ṹ, �����κ�RTCP��, ������������¶����RTCP��ͷ */
typedef struct RTCP_COMMON_HEAD_STRU
{
	/*#ifdef _WIN95 */  /* ����ϵͳ��WIN95 */ 
    BYTE bit5Count:5;   /* ����/���ͱ��������� */
    BYTE bit1P    :1;   /* RTCP����β������ݱ�־λ */
    BYTE bit2V    :2;   /* RTCPЭ��汾�� */
	/*#else*/
//	BYTE bit2V    :2;   /* RTCPЭ��汾�� */
//	BYTE bit1P    :1;   /* RTCP����β������ݱ�־λ */
//	BYTE bit5Count:5;   /* ����/���ͱ��������� */
	/*#endif*/
	
    BYTE  ucPT;         /* RTCP������ */
    unsigned short uwLen;/* ���ĳ���, ����32-bit���� */
} RTCP_COMMON_HEAD;

/* RTCP�������ݽṹ*/
typedef struct RTCP_STRU
{
    /* RTCP��ͷ */
    RTCP_COMMON_HEAD CommonHead;                
	
	/* 5�����Ͱ�����:SR,RR,SDSE,BYE,APP. */
    RTCP_PACKET_TYPE RtcpType;
} RTCP_PACKET;

//VideoRtcpTask�̺߳�������
typedef struct RTCPPARAM 
{
	ifly_rtcp_t* pRTCP;
	ifly_netsnd_t* pSnd;
	ifly_netrcv_t* pRcv;
} RTCPParam;

#pragma pack(pop)//��Ӧ???

//�����Ƿ���ҪRTCP
//False�Ļ����Դ�������RCTP��socket�������������հ�
//����CloseRTCPRcvSnd֮ǰ����
void SetNeedRTCP(BOOL bNeed);


//����RTCP��socket
ifly_rtcp_t* CreateRTCPRcvSnd();

//����RTCP����Ӧ�������ú�RTP����֮��
//����RCTP���ͽ��յ�IP,�˿ڣ���
u16 SetRTCPNetParam(ifly_rtcp_t* pRTCP,TNetSndParam* tNetSndParam, TNetRcvParam* tNetRcvParam);

//����SR������һ��ʱ�䷢��
u16 SendRTCPSR(ifly_rtcp_t* pRTCP,ifly_netsnd_t* pSnd);

//����RR��
u16 SendRTCPRR(ifly_rtcp_t* pRTCP,ifly_netrcv_t *pRcv, BYTE bylostrate);

//�̺߳���������SR�Ľ����Լ�RR�ķ��ͽ���
void *VideoRtcpTask(void* param);

//�ر�RCTPsocket��pRTCP��ΪNULL
void CloseRTCPRcvSnd(ifly_rtcp_t* pRTCP);

//�ص��������壬����ΪTRUE�ϵ�������False�µ�
typedef void (*PSETVIDEORATEUP)(BOOL bUp);

//ע��ص�����
void SetCBsSetVideoRate(PSETVIDEORATEUP pSetVideoRateCB);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _RTCP_H_ */
