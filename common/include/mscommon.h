#ifndef _MS_COMMON_H_
#define _MS_COMMON_H_

#include "mediastream.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include "common.h"

typedef struct
{
	u32 m_dwIP;
	u16 m_wPort;
}TAddr;

typedef struct
{
	u8		m_byNum;                    //��ַ����
    TAddr   m_tAddr[MAX_NETSND_DEST_NUM];//Զ�˵�ַ����
}TRemoteAddr;

typedef struct
{
    u8     *m_pBuf;
    INT32  m_nBufLen;
    INT32  m_nUintBufLen;
    INT32  m_nReadPos;
    INT32  m_nWritePos;
    INT32  m_nSubLen;
}TLoopBuf;

#define		LOOPBUF_NO_ERROR					(u16)0
#define		ERROR_LOOP_BUF_BASE					(u16)15000
#define		ERROR_LOOP_BUF_PARAM				(ERROR_LOOP_BUF_BASE+1)//���û�״�����������
#define		ERROR_LOOP_BUF_NULL					(ERROR_LOOP_BUF_BASE+2)//��״�������Ч���ݿ�
#define		ERROR_LOOP_BUF_FULL					(ERROR_LOOP_BUF_BASE+3)//��״�������Ч������ 
#define		ERROR_LOOP_BUF_NOCREATE				(ERROR_LOOP_BUF_BASE+4)//��״�������û�д���
#define		ERROR_LOOP_BUF_SIZE					(ERROR_LOOP_BUF_BASE+5)//��״�����е����ݵ�Ԫ��Ч���ȳ���
#define		ERROR_LOOP_BUF_MEMORY				(ERROR_LOOP_BUF_BASE+6)//��״�����е��ڴ��������

#define		THREADAFFMASK						1

//���¶��� FD_SETSIZE
#undef	FD_SETSIZE
#define FD_SETSIZE								(s32)256//����socket��

#ifdef __cplusplus
extern "C" {
#endif

u32  SetBitField(u32 dwValue, u32 dwBitField, INT32 nStartBit, INT32 nBits);
u32  GetBitField(u32 dwValue, INT32 nStartBit, INT32 nBits);
void ConvertH2N(u8 *pBuf, INT32 nStartIndex, INT32 nSize);
void ConvertN2H(u8 *pBuf, INT32 nStartIndex, INT32 nSize);

TLoopBuf* CreateLoopBuf(INT32 nUnitBufLen, INT32 nUnitBufNum);
u16 ReadLoopBuf(TLoopBuf *lp,u8 *pBuf, INT32 *pnBufSize);
u16 WriteLoopBuf(TLoopBuf *lp,u8 *pBuf, INT32 nBufSize);
u16 DestroyLoopBuf(TLoopBuf *lp);

BOOL SemBCreate(SEMHANDLE *phSema);
BOOL SemCCreate(SEMHANDLE *phSema, u32 dwInitCount, u32 dwMaxCount);
BOOL SemDelete(SEMHANDLE hSema);
BOOL SemTake(SEMHANDLE hSema);
BOOL SemTakeByTime(SEMHANDLE hSema, u32 dwTimeout);
BOOL SemGive(SEMHANDLE hSema);

BOOL SockInit();
BOOL SockCleanup();
BOOL SockClose(SOCKHANDLE hSock);

#ifdef WIN32
THREADHANDLE IFly_CreateThread(void* pvTaskEntry, char* szName, u8 byPriority, u32 dwStacksize, u32 dwParam, u16 wFlag, u32 *pdwTaskID);
#else
THREADHANDLE IFly_CreateThread(LINUXFUNC pvTaskEntry, char* szName, u8 byPriority, u32 dwStacksize, u32 dwParam, u16 wFlag, u32 *pdwTaskID);
#endif
BOOL IFly_ThreadExit();
BOOL IFly_ThreadTerminate(THREADHANDLE hTask);

u32 TickGet();
u32 GetSystemTick();//csp add 2008-11-20

u32 GetExclusiveSSRC();

#ifdef __cplusplus
}
#endif

#endif

