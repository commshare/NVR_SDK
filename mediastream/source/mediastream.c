#include "mssend.h"
#include "msrecv.h"

extern TMediaSndList	g_tMediaSndList;	//���Ͷ����б�ȫ�ֱ���
extern TMediaSndList	g_tMediaSndListTmp;
extern SEMHANDLE		g_hMediaSndSem;		//���Ͷ����б�ķ���ά�����ź���

extern TMediaRcvList	g_tMediaRcvList;	//���ն����б�ȫ�ֱ���
extern TMediaRcvList	g_tMediaRcvListTmp;
extern SEMHANDLE		g_hMediaRcvSem;		//���ն����б�ķ���ά�����ź���

void mediastreamver()
{
	printf(" mediastream version: %s   ", VER_MEDIASTREAM);
	printf(" compile time: %s,%s \n", __TIME__, __DATE__);
}

void mediastreamhelp()
{
	printf("\n /************************************/\n");
	printf("mediastreamver()  ���� �汾��ѯ\n");
	printf("printsock()  ���� �շ��׽��ӻ���״̬��Ϣ\n");
	printf("pbinfo(BOOL bShowRcv, BOOL bShowSnd) �����շ��������״̬��Ϣ��ͳ����Ϣ\n");
	printf("pdinfo(int nShowDebugInfo) �����Ƿ���ʾ���ص�һЩ����״̬��Ϣ\n");
	printf("\rsopen(BOOL bRcvCallback, BOOL bSelfSnd)  �����շ����ƿ���\n");
	printf("stest(int nSndObjIndex, int nFrameLen, int nSndNum, int nSpan)����ʹ�����ж������Բ��\n");
	printf("setconfuedadjust(int nbConfuedAdjust)���������������Ŀ���\n");
	printf("setrepeatsend(int nRepeatSnd)���� �ش����ƿ���\n");
	printf("setdiscardspan(int nDiscardSpan) ����ģ�ⶪ��С���Ĳ���������� \n");
	printf("\n /************************************/\n");
}

//��������ģ��
ifly_mediasnd_t* CreateMediaSnd(u32 dwMaxFrameSize, u32 dwNetBand, u8 byFrameRate, u8 byMediaType, u32 dwSSRC)
{
	ifly_mediasnd_t *pMediaSnd;
	BOOL bFind;
	s32  nPos;
	
	pMediaSnd = (ifly_mediasnd_t *)malloc(sizeof(ifly_mediasnd_t));
	SemBCreate(&pMediaSnd->m_hSndSynSem);
	pMediaSnd->m_pcNetSnd = CreateNetSnd(dwMaxFrameSize, dwNetBand, byFrameRate, byMediaType, dwSSRC);
	
	if(pMediaSnd->m_pcNetSnd == NULL)
	{
		SemDelete(pMediaSnd->m_hSndSynSem);
		pMediaSnd->m_hSndSynSem = NULL;
		free(pMediaSnd);
		return NULL;
	}
	
	SemTake(g_hMediaSndSem);
	
	//���뷢�Ͷ��������м�¼����ָ��
	bFind = FALSE;
	if(g_tMediaSndList.m_nMediaSndCount < MAX_SND_NUM)
	{
		for(nPos=0; nPos<g_tMediaSndList.m_nMediaSndCount; nPos++)
		{
			if(g_tMediaSndList.m_tMediaSndUnit[nPos] == pMediaSnd)
			{
				bFind = TRUE;
				break;
			}
		}
		if(FALSE == bFind)
		{
			g_tMediaSndList.m_nMediaSndCount++;
			g_tMediaSndList.m_tMediaSndUnit[g_tMediaSndList.m_nMediaSndCount-1] = pMediaSnd;
		}
	}
	//g_tMediaSndList
	
	SemGive(g_hMediaSndSem);
	
	return pMediaSnd;
}

//ɾ������ģ��
u16 DestroyMediaSnd(ifly_mediasnd_t* pMediaSnd)
{
	s32 i,j;
	
	if(pMediaSnd)
	{
		SemTake(g_hMediaSndSem);
		
		//�ӷ��Ͷ���������ɾ������ָ��
		memset(&g_tMediaSndListTmp, 0, sizeof(g_tMediaSndListTmp));
		for(i=0; i<g_tMediaSndList.m_nMediaSndCount; i++)
		{
			if(g_tMediaSndList.m_tMediaSndUnit[i] == pMediaSnd) continue;
			g_tMediaSndListTmp.m_tMediaSndUnit[g_tMediaSndListTmp.m_nMediaSndCount] \
				= g_tMediaSndList.m_tMediaSndUnit[i];
			g_tMediaSndListTmp.m_nMediaSndCount++;
		}
		g_tMediaSndList.m_nMediaSndCount = g_tMediaSndListTmp.m_nMediaSndCount;
		for(j=0; j<g_tMediaSndListTmp.m_nMediaSndCount; j++)
		{
			g_tMediaSndList.m_tMediaSndUnit[j] = 
				g_tMediaSndListTmp.m_tMediaSndUnit[j];
		}
		
		//g_tMediaSndList
		
		SemGive(g_hMediaSndSem);
		
		SemTake(pMediaSnd->m_hSndSynSem);
		DestroyNetSnd(pMediaSnd->m_pcNetSnd);
		pMediaSnd->m_pcNetSnd = NULL;
		SemGive(pMediaSnd->m_hSndSynSem);
		
		SemDelete(pMediaSnd->m_hSndSynSem);
		pMediaSnd->m_hSndSynSem = NULL;
		
		free(pMediaSnd);
	}
	
	return MEDIASTREAM_NO_ERROR;
}

//�������緢�Ͳ���(���еײ��׽��ֵĴ������󶨶˿�,�Լ�����Ŀ���ַ���趨�ȶ���)
u16 SetMediaSndNetParam(ifly_mediasnd_t* pMediaSnd,TNetSndParam tNetSndParam)
{
	u16 wRet = ERROR_SND_MEMORY;
	
	SemTake(pMediaSnd->m_hSndSynSem);
	if(pMediaSnd->m_pcNetSnd != NULL)
		wRet = SetNetSndNetParam(pMediaSnd->m_pcNetSnd,tNetSndParam);
	SemGive(pMediaSnd->m_hSndSynSem);
	
	return wRet;
}

//�Ƴ����緢�ͱ��ص�ַ����(���еײ��׽��ֵ�ɾ�����ͷŶ˿ڵȶ���)
u16 RemoveMediaSndLocalNetParam(ifly_mediasnd_t* pMediaSnd)
{
	u16 wRet = ERROR_SND_MEMORY;
	
	SemTake(pMediaSnd->m_hSndSynSem);
	if(pMediaSnd->m_pcNetSnd != NULL)
		wRet = RemoveNetSndLocalNetParam(pMediaSnd->m_pcNetSnd);
	SemGive(pMediaSnd->m_hSndSynSem);
	
	return wRet;
}

//����֡ID
u16 ResetMediaSndFrameId(ifly_mediasnd_t* pMediaSnd)
{
	u16 wRet = ERROR_SND_MEMORY;
	
	SemTake(pMediaSnd->m_hSndSynSem);
	if(pMediaSnd->m_pcNetSnd != NULL)
		wRet = ResetNetSndFrameId(pMediaSnd->m_pcNetSnd);
	SemGive(pMediaSnd->m_hSndSynSem);
	
	return wRet;
}
//����ͬ��ԴSSRC
u16 ResetMediaSndSSRC(ifly_mediasnd_t* pMediaSnd,u32 dwSSRC)
{
	u16 wRet = ERROR_SND_MEMORY;
	
	SemTake(pMediaSnd->m_hSndSynSem);
	if(pMediaSnd->m_pcNetSnd != NULL)
		wRet = ResetNetSndSSRC(pMediaSnd->m_pcNetSnd,dwSSRC);
	SemGive(pMediaSnd->m_hSndSynSem);
	
	return wRet;
}

//���÷��Ͷ˶���mpeg4����H.264���õ��ش�����Ŀ���,�رպ󣬽������Ѿ����͵����ݰ����л���
u16 ResetMediaSndRSFlag(ifly_mediasnd_t* pMediaSnd, u16 wBufTimeSpan, BOOL32 bRepeatSnd)
{
	u16 wRet = ERROR_SND_MEMORY;
	
	SemTake(pMediaSnd->m_hSndSynSem);
	if(pMediaSnd->m_pcNetSnd != NULL)
		wRet = ResetNetSndRSFlag(pMediaSnd->m_pcNetSnd,wBufTimeSpan,bRepeatSnd);
	SemGive(pMediaSnd->m_hSndSynSem);
	
	return wRet;
}

//���÷���ѡ��
u16 SetMediaSndInfo(ifly_mediasnd_t* pMediaSnd,u32 dwNetBand, u8 byFrameRate)
{
	u16 wRet = ERROR_SND_MEMORY;
	
	SemTake(pMediaSnd->m_hSndSynSem);
	if(pMediaSnd->m_pcNetSnd != NULL)
		wRet = SetNetSndInfo(pMediaSnd->m_pcNetSnd,dwNetBand,byFrameRate);
	SemGive(pMediaSnd->m_hSndSynSem);
	
	return wRet;
}

//�������ݰ�
u16 SendMediaFrame(ifly_mediasnd_t* pMediaSnd,PFRAMEHDR pFrmHdr,int avgInterTime)
{
	u16 wRet = ERROR_SND_MEMORY;
	
	SemTake(pMediaSnd->m_hSndSynSem);
	if(pMediaSnd->m_pcNetSnd != NULL)
		wRet = SendFrame(pMediaSnd->m_pcNetSnd,pFrmHdr,avgInterTime);
	SemGive(pMediaSnd->m_hSndSynSem);
	
	return wRet;
}

//�õ�״̬
u16 GetMediaSndStatus(ifly_mediasnd_t* pMediaSnd,TSndStatus *pSndStatus)
{
	u16 wRet = ERROR_SND_MEMORY;
	
	SemTake(pMediaSnd->m_hSndSynSem);
	if(pMediaSnd->m_pcNetSnd != NULL)
		wRet = GetNetSndStatus(pMediaSnd->m_pcNetSnd,pSndStatus);
	SemGive(pMediaSnd->m_hSndSynSem);
	
	return wRet;
}

//�õ�ͳ��
u16 GetMediaSndStatistics(ifly_mediasnd_t* pMediaSnd,TSndStatistics *pSndStatistics)
{
	u16 wRet = ERROR_SND_MEMORY;
	
	SemTake(pMediaSnd->m_hSndSynSem);
	if(pMediaSnd->m_pcNetSnd != NULL)
		wRet = GetNetSndStatistics(pMediaSnd->m_pcNetSnd,pSndStatistics);
	SemGive(pMediaSnd->m_hSndSynSem);
	
	return wRet;
}

//�õ����Ͷ˸߼����ò���(�ش���)
u16 GetMediaSndAdvancedInfo(ifly_mediasnd_t* pMediaSnd,TAdvancedSndInfo *pAdvancedSndInfo)
{
	u16 wRet = ERROR_SND_MEMORY;
	
	SemTake(pMediaSnd->m_hSndSynSem);
	if(pMediaSnd->m_pcNetSnd != NULL)
		wRet = GetNetSndAdvancedInfo(pMediaSnd->m_pcNetSnd,pAdvancedSndInfo);
	SemGive(pMediaSnd->m_hSndSynSem);
	
	return wRet;
}

//rtcp��ʱrtcp���ϱ�, �ڲ�ʹ�ã��ⲿ�������
u16 DealMediaSndRtcpTimer(ifly_mediasnd_t* pMediaSnd)
{
	u16 wRet = ERROR_SND_MEMORY;
	
	SemTake(pMediaSnd->m_hSndSynSem);
	if(pMediaSnd->m_pcNetSnd != NULL)
		wRet = DealNetSndRtcpTimer(pMediaSnd->m_pcNetSnd);
	SemGive(pMediaSnd->m_hSndSynSem);
	
	return wRet;
}

//��������ģ��
ifly_mediarcv_t* CreateMediaRcv(u32 dwMaxFrameSize, PFRAMEPROC pFrameCallBackProc, u32 dwContext, u32 dwSSRC)
{
	ifly_mediarcv_t* pMediaRcv;
	BOOL bFind;
	s32  nPos;
	
	pMediaRcv = (ifly_mediarcv_t *)malloc(sizeof(ifly_mediarcv_t));
	SemBCreate(&pMediaRcv->m_hRcvSynSem);
	pMediaRcv->m_pcNetRcv = CreateNetRcv(dwMaxFrameSize,pFrameCallBackProc,dwContext,dwSSRC);
	if(pMediaRcv->m_pcNetRcv == NULL)
	{
		SemDelete(pMediaRcv->m_hRcvSynSem);
		pMediaRcv->m_hRcvSynSem = NULL;
		free(pMediaRcv);
		return NULL;
	}
	
	SemTake(g_hMediaRcvSem);
	
	//������ն��������м�¼����ָ��
	bFind = FALSE;
	if(g_tMediaRcvList.m_nMediaRcvCount < FD_SETSIZE)
	{
		for(nPos=0; nPos<g_tMediaRcvList.m_nMediaRcvCount; nPos++)
		{
			if(g_tMediaRcvList.m_tMediaRcvUnit[nPos] == pMediaRcv)
			{
				bFind = TRUE;
				break;
			}
		}
		if(FALSE == bFind)
		{
			g_tMediaRcvList.m_nMediaRcvCount++;
			g_tMediaRcvList.m_tMediaRcvUnit[g_tMediaRcvList.m_nMediaRcvCount-1] = pMediaRcv;
		}
	}
	//g_tMediaRcvList
	
	SemGive(g_hMediaRcvSem);
	
	return pMediaRcv;
}

ifly_mediarcv_t* CreateMediaRcvRtp(u32 dwMaxFrameSize, PRTPCALLBACK PRtpCallBackProc, u32 dwContext, u32 dwSSRC)
{
	ifly_mediarcv_t* pMediaRcv;
	BOOL bFind;
	s32  nPos;
	
	pMediaRcv = (ifly_mediarcv_t *)malloc(sizeof(ifly_mediarcv_t));
	SemBCreate(&pMediaRcv->m_hRcvSynSem);
	pMediaRcv->m_pcNetRcv = CreateNetRcvRtp(dwMaxFrameSize,PRtpCallBackProc,dwContext,dwSSRC);
	if(pMediaRcv->m_pcNetRcv == NULL)
	{
		SemDelete(pMediaRcv->m_hRcvSynSem);
		pMediaRcv->m_hRcvSynSem = NULL;
		free(pMediaRcv);
		return NULL;
	}
	
	SemTake(g_hMediaRcvSem);
	
	//������ն��������м�¼����ָ��
	bFind = FALSE;
	if(g_tMediaRcvList.m_nMediaRcvCount < FD_SETSIZE)
	{
		for(nPos=0; nPos<g_tMediaRcvList.m_nMediaRcvCount; nPos++)
		{
			if(g_tMediaRcvList.m_tMediaRcvUnit[nPos] == pMediaRcv)
			{
				bFind = TRUE;
				break;
			}
		}
		if(FALSE == bFind)
		{
			g_tMediaRcvList.m_nMediaRcvCount++;
			g_tMediaRcvList.m_tMediaRcvUnit[g_tMediaRcvList.m_nMediaRcvCount-1] = pMediaRcv;
		}
	}
	//g_tMediaRcvList
	
	SemGive(g_hMediaRcvSem);
	
	return pMediaRcv;
}

//���ý��յ�ַ����(���еײ��׽��ӵĴ������󶨶˿ڵȶ���)
u16 SetMediaRcvLocalParam(ifly_mediarcv_t* pMediaRcv,TLocalNetParam tLocalNetParam)
{
	u16 wRet = ERROR_NET_RCV_MEMORY;
	
    if(NULL != pMediaRcv && NULL != pMediaRcv->m_hRcvSynSem) 
	{
		SemTake(pMediaRcv->m_hRcvSynSem);
		if(pMediaRcv->m_pcNetRcv != NULL)
			wRet = SetNetRcvLocalParam(pMediaRcv->m_pcNetRcv,tLocalNetParam);
		SemGive(pMediaRcv->m_hRcvSynSem);
	}
	
    return wRet;
}

//�Ƴ����յ�ַ����(���еײ��׽��ӵ�ɾ�����ͷŶ˿ڵȶ���)
u16 RemoveMediaRcvLocalParam(ifly_mediarcv_t* pMediaRcv)
{
	u16 wRet = ERROR_NET_RCV_MEMORY;
	
    if(NULL != pMediaRcv && NULL != pMediaRcv->m_hRcvSynSem) 
	{
		SemTake(pMediaRcv->m_hRcvSynSem);
		if(pMediaRcv->m_pcNetRcv != NULL)
			wRet = RemoveNetRcvLocalParam(pMediaRcv->m_pcNetRcv);
		SemGive(pMediaRcv->m_hRcvSynSem);
	}
	
    return wRet;
}

//���ý��ն˶���mpeg4����H.264���õ��ش�����Ŀ���,�رպ󣬽��������ش�����
u16 ResetMediaRcvRSFlag(ifly_mediarcv_t* pMediaRcv,TRSParam tRSParam, BOOL bRepeatSnd)
{
	u16 wRet = ERROR_NET_RCV_MEMORY;
	
    if(NULL != pMediaRcv && NULL != pMediaRcv->m_hRcvSynSem) 
	{
		SemTake(pMediaRcv->m_hRcvSynSem);
		if(pMediaRcv->m_pcNetRcv != NULL)
			wRet = ResetNetRcvRSFlag(pMediaRcv->m_pcNetRcv,tRSParam,bRepeatSnd);
		SemGive(pMediaRcv->m_hRcvSynSem);
	}
	
    return wRet;
}

//��ʼ����
u16 StartMediaRcv(ifly_mediarcv_t* pMediaRcv)
{
	u16 wRet = ERROR_NET_RCV_MEMORY;
	
    if(NULL != pMediaRcv && NULL != pMediaRcv->m_hRcvSynSem) 
	{
		SemTake(pMediaRcv->m_hRcvSynSem);
		if(pMediaRcv->m_pcNetRcv != NULL)
			wRet = StartNetRcv(pMediaRcv->m_pcNetRcv);
		SemGive(pMediaRcv->m_hRcvSynSem);
	}
	
    return wRet;
}

//ֹͣ����
u16 StopMediaRcv(ifly_mediarcv_t* pMediaRcv)
{
	u16 wRet = ERROR_NET_RCV_MEMORY;
	
    if(NULL != pMediaRcv && NULL != pMediaRcv->m_hRcvSynSem) 
	{
		SemTake(pMediaRcv->m_hRcvSynSem);
		if(pMediaRcv->m_pcNetRcv != NULL)
			wRet = StopNetRcv(pMediaRcv->m_pcNetRcv);
		SemGive(pMediaRcv->m_hRcvSynSem);
	}
	
    return wRet;
}

//�õ�״̬
u16 GetMediaRcvStatus(ifly_mediarcv_t* pMediaRcv,TRcvStatus *pRcvStatus)
{
	u16 wRet = ERROR_NET_RCV_MEMORY;
	
    if(NULL != pMediaRcv && NULL != pMediaRcv->m_hRcvSynSem) 
	{
		SemTake(pMediaRcv->m_hRcvSynSem);
		if(pMediaRcv->m_pcNetRcv != NULL)
			wRet = GetNetRcvStatus(pMediaRcv->m_pcNetRcv,pRcvStatus);
		SemGive(pMediaRcv->m_hRcvSynSem);
	}
	
    return wRet;
}

//�õ�ͳ��
u16 GetMediaRcvStatistics(ifly_mediarcv_t* pMediaRcv,TRcvStatistics *pRcvStatistics)
{
	u16 wRet = ERROR_NET_RCV_MEMORY;
	
    if(NULL != pMediaRcv && NULL != pMediaRcv->m_hRcvSynSem) 
	{
		SemTake(pMediaRcv->m_hRcvSynSem);
		if(pMediaRcv->m_pcNetRcv != NULL)
			wRet = GetNetRcvStatistics(pMediaRcv->m_pcNetRcv,pRcvStatistics);
		SemGive(pMediaRcv->m_hRcvSynSem);
	}
	
    return wRet;
}

u16 DestroyMediaRcv(ifly_mediarcv_t* pMediaRcv)
{
	s32 i,j;
	
	if(pMediaRcv)
	{
		SemTake(g_hMediaRcvSem);
		
		//�ӽ��ն���������ɾ������ָ��
		memset(&g_tMediaRcvListTmp, 0, sizeof(g_tMediaRcvListTmp));
		for(i=0; i<g_tMediaRcvList.m_nMediaRcvCount; i++)
		{
			if(g_tMediaRcvList.m_tMediaRcvUnit[i] == pMediaRcv) continue;
			g_tMediaRcvListTmp.m_tMediaRcvUnit[g_tMediaRcvListTmp.m_nMediaRcvCount] \
				= g_tMediaRcvList.m_tMediaRcvUnit[i];
			g_tMediaRcvListTmp.m_nMediaRcvCount++;
		}
		g_tMediaRcvList.m_nMediaRcvCount = g_tMediaRcvListTmp.m_nMediaRcvCount;
		for(j=0; j<g_tMediaRcvListTmp.m_nMediaRcvCount; j++)
		{
			g_tMediaRcvList.m_tMediaRcvUnit[j] = 
				g_tMediaRcvListTmp.m_tMediaRcvUnit[j];
		}
		//g_tMediaRcvList
		
		SemGive(g_hMediaRcvSem);
		
		if(pMediaRcv->m_hRcvSynSem) SemTake(pMediaRcv->m_hRcvSynSem);
		if(pMediaRcv->m_pcNetRcv)   DestroyNetRcv(pMediaRcv->m_pcNetRcv);
		if(pMediaRcv->m_hRcvSynSem) SemGive(pMediaRcv->m_hRcvSynSem);
		
		if(pMediaRcv->m_hRcvSynSem) SemDelete(pMediaRcv->m_hRcvSynSem);
		pMediaRcv->m_hRcvSynSem = NULL;
		
		free(pMediaRcv);
	}
	return MEDIASTREAM_NO_ERROR;
}

u16 DealMediaRcvRtcpTimer(ifly_mediarcv_t* pMediaRcv)
{
	u16 wRet = ERROR_NET_RCV_MEMORY;
	
	if(NULL != pMediaRcv && NULL != pMediaRcv->m_hRcvSynSem)
	{
		SemTake(pMediaRcv->m_hRcvSynSem);
		if(pMediaRcv->m_pcNetRcv != NULL)
			wRet = DealNetRcvRtcpTimer(pMediaRcv->m_pcNetRcv);
		SemGive(pMediaRcv->m_hRcvSynSem);
	}
	
    return wRet;
}
