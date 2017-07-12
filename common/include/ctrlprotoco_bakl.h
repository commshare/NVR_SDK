#ifndef _CTRLPROTOCOL_H_
#define _CTRLPROTOCOL_H_

#include "iflytype.h"
#include "camera.h"

#ifdef WIN32
#include "winsock2.h"
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>
#endif

#ifdef WIN32
#define SOCKHANDLE		SOCKET
#else
#define SOCKHANDLE		int
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WIN32
#define INFINITE						0xffffffff
#endif

#define CTRL_PROTOCOL_SERVERPORT		6610					//�������˿�
#define CTRL_PROTOCOL_MAXLINKNUM		256

#define CTRL_PROTOCOL_CONNECT_BLOCK		INFINITE				//���ӷ�ʽ:����
#define CTRL_PROTOCOL_CONNECT_DEFAULT	3000					//ȱʡ����ʱ��:3��

#define CTRL_VERSION					0x0100

#define CTRL_COMMAND					0
#define CTRL_NOTIFY						1
#define CTRL_ACK						2

//��������
#define CTRL_CMD_BASE					10000
#define CTRL_CMD_STARTVIDEOMONITOR		CTRL_CMD_BASE+0			//��ʼ��Ƶ���
#define CTRL_CMD_STOPVIDEOMONITOR		CTRL_CMD_BASE+1			//ֹͣ��Ƶ���
#define CTRL_CMD_STARTAUDIOMONITOR		CTRL_CMD_BASE+2			//��ʼ��Ƶ���
#define CTRL_CMD_STOPAUDIOMONITOR		CTRL_CMD_BASE+3			//ֹͣ��Ƶ���

#define CTRL_CMD_STARTFILEPLAY			CTRL_CMD_BASE+5			//��ʼԶ���ļ��ط�
#define CTRL_CMD_STOPFILEPLAY			CTRL_CMD_BASE+6			//ֹͣԶ���ļ��ط�
#define CTRL_CMD_STARTTIMEPLAY			CTRL_CMD_BASE+7			//��ʼԶ��ʱ��ط�
#define CTRL_CMD_STOPTIMEPLAY			CTRL_CMD_BASE+8			//ֹͣԶ��ʱ��ط�
#define CTRL_CMD_FASTPLAY				CTRL_CMD_BASE+9			//���
#define CTRL_CMD_SLOWPLAY				CTRL_CMD_BASE+10		//����
#define CTRL_CMD_SETPLAYRATE			CTRL_CMD_BASE+11		//���ò�������
#define CTRL_CMD_PAUSEPLAY				CTRL_CMD_BASE+12		//��ͣ
#define CTRL_CMD_RESUMEPLAY				CTRL_CMD_BASE+13		//�ָ�
#define CTRL_CMD_SINGLEPLAY				CTRL_CMD_BASE+14		//֡��
#define CTRL_CMD_FASTBACKPLAY			CTRL_CMD_BASE+15		//����
#define CTRL_CMD_PLAYPREV				CTRL_CMD_BASE+16		//��һ��
#define CTRL_CMD_PLAYNEXT				CTRL_CMD_BASE+17		//��һ��
#define CTRL_CMD_PLAYSEEK				CTRL_CMD_BASE+18		//seek
#define CTRL_CMD_PLAYMUTE				CTRL_CMD_BASE+19		//����
#define CTRL_CMD_PLAYPROGRESS			CTRL_CMD_BASE+20		//���Ž���
#define CTRL_CMD_STARTVOIP				CTRL_CMD_BASE+21		//��ʼ�����ӽ�		07-07-27
#define CTRL_CMD_STOPVOIP				CTRL_CMD_BASE+22		//ֹͣ�����ӽ�		07-07-27
#define CTRL_CMD_UPDATE					CTRL_CMD_BASE+23		//Զ���������		07-07-27
#define CTRL_CMD_REBOOT					CTRL_CMD_BASE+24		//Զ������			07-07-27
#define CTRL_CMD_OSD_CHANNEL    		CTRL_CMD_BASE+25		//Զ��ͨ��λ������	07-07-27
#define CTRL_CMD_OSD_TIME				CTRL_CMD_BASE+26		//Զ��ʱ��λ������	07-07-27
#define CTRL_CMD_MASK					CTRL_CMD_BASE+27		//Զ���ڸ���������	07-07-31
#define CTRL_CMD_PICTURE_ADJUST			CTRL_CMD_BASE+28		//���ʵ��ڣ��������� ɫ�� �Աȶȼ����Ͷ�07-07-31

#define CTRL_CMD_STARTRECDOWNLOAD		CTRL_CMD_BASE+30		//��ʼ����¼���ļ�
#define CTRL_CMD_STOPRECDOWNLOAD		CTRL_CMD_BASE+31		//ֹͣ����¼���ļ�
#define CTRL_CMD_MDAREA					CTRL_CMD_BASE+32		//�����ƶ��������
#define CTRL_CMD_CAMERA					CTRL_CMD_BASE+33		//��̨����

#define CTRL_CMD_NETCONFIG				CTRL_CMD_BASE+34		//Զ����������
#define CTRL_CMD_TIMESET_PARAMSH		CTRL_CMD_BASE+35		//�ڵ�����Զ�̲���
#define CTRL_CMD_TIMESET_PARAMVL		CTRL_CMD_BASE+36		//��Ƶ��ʧԶ�̲���
#define CTRL_CMD_TIMESET_PARAMMD		CTRL_CMD_BASE+37		//�ƶ����Զ�̲���
#define CTRL_CMD_EXCEPTION				CTRL_CMD_BASE+38		//Զ���쳣����
#define CTRL_CMD_MOTION_ALARM			CTRL_CMD_BASE+39		//Զ���ƶ���⴦��
#define CTRL_CMD_REC_SETTIME			CTRL_CMD_BASE+40		//¼����������
#define CTRL_CMD_ALARMSET				CTRL_CMD_BASE+41		//��������
#define CTRL_CMD_ALARMIN_SETTIME		CTRL_CMD_BASE+42		//�������벼��
#define CTRL_CMD_ALARMIN_MANAGE			CTRL_CMD_BASE+43		//�������봦��
#define CTRL_CMD_ALARMIN_PTZ			CTRL_CMD_BASE+44		//��������PTZ����
#define CTRL_CMD_ALARMOUT_SET			CTRL_CMD_BASE+45		//�����������
#define CTRL_CMD_IMAGSET_PARAM			CTRL_CMD_BASE+46		//Զ��ͼ�����ò�������
#define CTRL_CMD_RECORDSET_PARAM		CTRL_CMD_BASE+47		//Զ��¼�����ò�������
#define CTRL_CMD_LOGIN					CTRL_CMD_BASE+48		//Զ�̵�¼����
#define CTRL_CMD_USERQUERY				CTRL_CMD_BASE+49		//Զ���û���Ϣ����
#define CTRL_CMD_USEREDIT				CTRL_CMD_BASE+50		//Զ���û��༭ 
#define CTRL_CMD_YUNTAISET				CTRL_CMD_BASE+51		//Զ����̨��������
#define CTRL_CMD_SYSPARAM				CTRL_CMD_BASE+52		//Զ��ϵͳ������ѯ
#define CTRL_CMD_SYSINFO				CTRL_CMD_BASE+53		//Զ��ϵͳ��Ϣ��ѯ
#define CTRL_CMD_HDDINFO				CTRL_CMD_BASE+54		//Զ��Ӳ����Ϣ��ѯ
#define CTRL_CMD_CLRALARM				CTRL_CMD_BASE+55		//Զ���������
#define CTRL_CMD_ONLINE					CTRL_CMD_BASE+56		//Զ�������û���ѯ
#define CTRL_CMD_EDITPASS				CTRL_CMD_BASE+57		//Զ���޸ĵ�¼�û�����

#define CTRL_CMD_USER_ADD				CTRL_CMD_BASE+60		//Զ���û����
#define CTRL_CMD_USER_MODIFY			CTRL_CMD_BASE+61		//Զ���û��޸�
#define CTRL_CMD_USER_DEL				CTRL_CMD_BASE+62		//Զ���û�ɾ��
#define CTRL_CMD_LOG					CTRL_CMD_BASE+63		//Զ����־��ѯ
#define CTRL_CMD_HANDREC				CTRL_CMD_BASE+64		//Զ���ֶ�¼��

#define CTRL_CMD_LOGINOFF				CTRL_CMD_BASE+67		//ע���û���¼
#define CTRL_CMD_NETQUERY				CTRL_CMD_BASE+68		//��ѯ��������
#define CTRL_CMD_HANDINFO				CTRL_CMD_BASE+69
#define CTRL_CMD_EXCEPINFO				CTRL_CMD_BASE+70
#define CTRL_CMD_YUNTAIINFO				CTRL_CMD_BASE+71
#define CTRL_CMD_IMAGINFO				CTRL_CMD_BASE+72
#define CTRL_CMD_RECINFO				CTRL_CMD_BASE+73
#define CTRL_CMD_SYSPARA_INFO			CTRL_CMD_BASE+74
#define CTRL_CMD_SYSTIME_FIRST			CTRL_CMD_BASE+75
#define CTRL_CMD_SYSTIME_SEND			CTRL_CMD_BASE+76
#define CTRL_CMD_ALARMSET_FIRST			CTRL_CMD_BASE+77
#define CTRL_CMD_SHTIME_FIRST			CTRL_CMD_BASE+78
#define CTRL_CMD_VLTIME_FIRST			CTRL_CMD_BASE+79
#define CTRL_CMD_MDTIME_FIRST			CTRL_CMD_BASE+80
#define CTRL_CMD_MDSET_FIRST			CTRL_CMD_BASE+81
#define CTRL_CMD_RECSTART_FIRST			CTRL_CMD_BASE+82
#define CTRL_CMD_INSET_FIRST			CTRL_CMD_BASE+83
#define CTRL_CMD_INDISPOSE_FIRST		CTRL_CMD_BASE+84
#define CTRL_CMD_INPTZ_FIRST			CTRL_CMD_BASE+85
#define CTRL_CMD_OUTSET_FIRST			CTRL_CMD_BASE+86
#define CTRL_CMD_RECSEARCH				CTRL_CMD_BASE+87			//�طŲ�ѯ07-07-30
#define CTRL_CMD_USER_SEND				CTRL_CMD_BASE+88			//07-07-30
#define CTRL_CMD_LAYIN					CTRL_CMD_BASE+89			//Զ�̵���07-08-02
#define CTRL_CMD_LAYOUT					CTRL_CMD_BASE+90			//Զ�̵���07-08-02
#define CTRL_CMD_PRESET_SAVE			CTRL_CMD_BASE+91		//Ԥ�õ����
#define CTRL_CMD_PRESET_DEL				CTRL_CMD_BASE+92		//Ԥ�õ�ɾ��
#define CTRL_CMD_CRUISEPOS_ADD			CTRL_CMD_BASE+93		//Ѳ��·�������
#define CTRL_CMD_CRUISEPOS_DEL			CTRL_CMD_BASE+94		//Ѳ��·����ɾ��
#define CTRL_CMD_CRUISE_START			CTRL_CMD_BASE+95			//��ʼѲ��
#define CTRL_CMD_CRUISE_STOP			CTRL_CMD_BASE+96			//����Ѳ��
#define CTRL_CMD_TRACKPATTERN_START		CTRL_CMD_BASE+97	//��¼�켣
#define CTRL_CMD_TRACKPATTERN_STOP		CTRL_CMD_BASE+98	//������¼
#define CTRL_CMD_TRACK_START		CTRL_CMD_BASE+99				//��ʼ�켣
#define CTRL_CMD_TRACK_STOP		CTRL_CMD_BASE+100					//ֹͣ�켣
#define CTRL_CMD_RESOLUTION   CTRL_CMD_BASE+101					//ͼ��ֱ���
#define CTRL_CMD_MULTICAST		CTRL_CMD_BASE+102				 //�����鲥��ַ

//�¼�֪ͨ����
#define CTRL_NOTIFY_BASE				20000
#define	CTRL_NOTIFY_CONNLOST			CTRL_NOTIFY_BASE+0		//������Ϣ
#define	CTRL_NOTIFY_HEARTBEAT_REQ		CTRL_NOTIFY_BASE+1		//��������
#define	CTRL_NOTIFY_HEARTBEAT_RESP		CTRL_NOTIFY_BASE+2		//�����ظ�
#define CTRL_NOTIFY_PLAYEND				CTRL_NOTIFY_BASE+3		//�������
#define CTRL_NOTIFY_PLAYPROGRESS		CTRL_NOTIFY_BASE+4		//�������֪ͨ

//Ӧ������
#define CTRL_SUCCESS					0						//�ɹ�
#define CTRL_FAILED_BASE				30000					//������ƫ����
#define CTRL_FAILED_USER				CTRL_FAILED_BASE+1		//�����ڵ��û���
#define CTRL_FAILED_PASSWORD			CTRL_FAILED_BASE+2		//�������
#define CTRL_FAILED_COMMAND				CTRL_FAILED_BASE+3		//δ�Ͽɵ�����
#define CTRL_FAILED_PARAM				CTRL_FAILED_BASE+4		//��Ч����
#define CTRL_FAILED_OUTOFMEMORY			CTRL_FAILED_BASE+5		//�ڴ治��
#define CTRL_FAILED_RESOURCE			CTRL_FAILED_BASE+6		//��Դ����
#define CTRL_FAILED_FILENOTEXIST		CTRL_FAILED_BASE+7		//�ļ�������
#define CTRL_FAILED_DATABASE			CTRL_FAILED_BASE+8		//���ݿ����
#define CTRL_FAILED_RELOGIN				CTRL_FAILED_BASE+9		//�ظ���¼
#define CTRL_FAILED_BAUDLIMIT			CTRL_FAILED_BASE+10		//ÿһ·ͨ�����֧��5·ʵʱ���			
#define CTRL_FAILED_CREATESOCKET		CTRL_FAILED_BASE+11		//�����׽���ʧ��
#define CTRL_FAILED_CONNECT				CTRL_FAILED_BASE+12		//��������ʧ��
#define CTRL_FAILED_BIND				CTRL_FAILED_BASE+13		//��ʧ��
#define CTRL_FAILED_LISTEN				CTRL_FAILED_BASE+14		//����ʧ��
#define CTRL_FAILED_NETSND				CTRL_FAILED_BASE+15		//���緢�ͳ���
#define CTRL_FAILED_NETRCV				CTRL_FAILED_BASE+16		//������ճ���
#define CTRL_FAILED_TIMEOUT				CTRL_FAILED_BASE+17		//�������ӳ�ʱ
#define CTRL_FAILED_CHNERROR			CTRL_FAILED_BASE+18		//����ͨ������
#define CTRL_FAILED_DEVICEBUSY			CTRL_FAILED_BASE+19		//�豸����æ
#define CTRL_FAILED_WRITEFLASH			CTRL_FAILED_BASE+20		//��дflash����
#define CTRL_FAILED_VERIFY				CTRL_FAILED_BASE+21		//У���
#define CTRL_FAILED_CONFLICT			CTRL_FAILED_BASE+22		//ϵͳ��Դ��ͻ
#define CTRL_FAILED_BUSY				CTRL_FAILED_BASE+23		//ϵͳ����æ
#define CTRL_FAILED_LINKLIMIT			CTRL_FAILED_BASE+24		//�Ѵﵽ��������
#define CTRL_FAILED_UNKNOWN				CTRL_FAILED_BASE+9999	//δ֪����

#define CTRL_CONNECTION_NULL			0x0
#define CTRL_CONNECTION_TCPCLIENT		0x1
#define CTRL_CONNECTION_TCPSERVER		0x2

#pragma pack( push, 1 )

typedef struct
{
	u8 data[6];
}CPGuid;

typedef struct
{
	u32         ip;
	u16			port;
	CPGuid		guid;
	SOCKHANDLE	sockfd;
	u8			conntype;
	u8          newmsgcome;
	u8          nolnkcount;
}ifly_cp_t,*CPHandle;

typedef struct
{
	u32 length;							//��Ϣ����
	u16 type;							//��Ϣ����
	u16 event;							//��Ϣ��
	u16 number;							//��ˮ��
	u16 version;						//�汾��
}ifly_cp_header_t;

typedef struct							//07-07-23 
{										//������ҳ���ύʱ����ӵ�¼����û���һ���ύ
	char usrname[12];
}ifly_usrname_header;

typedef struct
{
	u16 startID;						//07-07-28
	u16 max_return;
}ifly_remusr_send_t;

typedef struct							//Զ���ֶ�¼��ṹ
{
	u8 chan_rec[4];
	u8 allrec;
	u8 allstop;
}ifly_hand_rec_t;

//Զ����־��ѯ
typedef struct
{
	u8  query_mode;						//��ѯ��ʽ
	u8  main_type;						//������
	u8  slave_type;						//������
	u16 max_return;						//��󷵻���
	u16 startID;						//���شӵ�һ����¼��ʼ
	u32 start_time;						//��ʼʱ��
	u32 end_time;						//����ʱ��	
}ifly_research_log_t;

typedef struct
{
	u32  startTime;
	char main[64];						//������
	char slave[64];						//������
}ifly_log_back_t;

//Զ�̵�¼
typedef struct
{
	char username[12];
	char loginpass[12];
	u32	 ipAddr;
}ifly_loginpara_t;

typedef struct
{
	char username[12];
	char loginpass[12];
}ifly_logininfo_t;

typedef struct
{
	char usrname[12];
	char remote_privilege[16];
}ifly_remusr_limit;
/*****************/
//07-07-11
typedef struct
{
	int link_online;
}ifly_link_online;
//Զ���û�������Ϣ�ṹ
typedef struct
{
	char name[12];
	char password[12];
	char local_privilege[16];
	char remote_privilege[16];
	char mac_address[18];
}ifly_userinfo_t;

//Զ���û��༭�����ṹ
typedef struct
{
	char name[12];						//�û���
	char passwd[12];					//����
	char confirm[12];					//У������
	char macaddr[18];					//�����ַ
	u32  index;							//�û�Ȩ��
	u32  rcamer;						//Զ����̨Ȩ��
	u32  rrec;							//Զ��¼��Ȩ��
	u32  rplay;							//Զ�̻ط�Ȩ��
	u32  rsetpara;						//Զ�����ò���
	u32  rlog;							//Զ����־Ȩ��
	u32  rtool;							//Զ�̹���Ȩ��
	u32  rpreview;						//Զ��Ԥ��Ȩ��
	u32  ralarm;						//Զ�̱���Ȩ��
	u32  rvoip;							//�����Խ�Ȩ��
	u32  lcamer;						//������̨Ȩ��
	u32  lrec;							//����¼��Ȩ��
	u32  lplay;							//���ػط�Ȩ��
	u32  lsetpara;						//�������ò���
	u32  llog;							//������־Ȩ��
	u32  ltool;							//���ع���Ȩ��
}ifly_useredit_t;

//Զ���û�ɾ�������ṹ
typedef struct
{
	u32  user_index;					//��ǰɾ���û���¼
	char name[12];						//��ǰ��ɾ���û���
}ifly_userdel_t;

//Զ���û������޸Ĳ���
typedef struct 
{
	char name[12];
	char oldpass[12];
	char newpass[12];
	char confirm[12];
}ifly_editpass_t;

//Զ�̷���Ӳ����Ϣ�ṹ
typedef	struct 
{
	s64  capability;//Byte
	s64  freesize;//Byte
}ifly_remhdd_t;

/********************/
//07-07-03
typedef struct
{
	u8 hdd_exist[2];
}ifly_hdd_desc_t;

//Զ��ϵͳ��Ϣ���� 
typedef struct
{
	char devicename[32];
	char devicemodel[32];
	char deviceser[32];
	char version[64];
}ifly_recsysinfo_t;

//Զ��ϵͳ�����ṹ added by kmli
typedef struct
{
	u16	 device_id;
	char device_name[32];
	u8	 flag_overlap;
	u32	 time;
	u8	 lock_time;
	u8	 switch_time;
	u8	 flag_statusdisp;
	u8	 video_format;
	u8	 vga_solution;
}ifly_syspara_send_t;

//Զ����̨����
typedef struct
{
	u8	 channel_no;
	u16  address;
	u8   baud_ratesel;
	u8   data_bitsel;
	u8   stop_bitsel;
	u8   crccheck;
	u8   flow_control;
	u8   protocol;
}ifly_yuntai_send_t;

//Զ�̼��
typedef struct
{
	u32 dwIp;		//����ip
	u16 wPort;		//�������ݵĶ˿�
	u8  byChn;		//ͨ���ţ���ַΪ0
}ifly_monitor_param_t;

//���ļ�Զ�̻ط�
typedef struct
{
	u32  dwIp;			//����ý�����ݵ�ip
	u16  wVideoPort;	//������Ƶ���ݵĶ˿�
	u16  wAudioPort;	//������Ƶ���ݵĶ˿�
	char filename[64];	//�طŵ��ļ�
	u32	 offset;		//�ļ�ƫ��
}ifly_remote_playback_t;

typedef struct
{
	u32  id;
}ifly_play_handle_t;

typedef struct
{
	u32  curpos;
	u32  totaltime;
}ifly_play_progress_t;

typedef struct
{
	u32  dwIp;			//�����ļ����ݵ�ip
	u16  wPort;			//�����ļ����ݵĶ˿�
	char filename[64];	//���ص��ļ�
	u32	 offset;		//�ļ�ƫ��
	u32  size;			//�ļ���С
}ifly_remote_download_t;

typedef struct
{
	u32  id;
}ifly_download_handle_t;

typedef struct
{
	char filename[64];	//�ļ���
	u32  size;			//�ļ�����
	u32  verify;		//У���
	u16  version;		//�ļ��汾��
	u16  reserved;
}ifly_remote_upload_t;
/*********************/
//07-08-02
/*typedef struct
{
	char filename[64];
	u32  size;
	u16  reserved;
}ifly_remote_layin_t;*/		//Զ�̵���
typedef struct
{
	u32 dwIp;
	u16 wPort;
}ifly_remote_layout_head;
typedef struct
{
	char filename[64];
	u32  size;
	u16  reserved;
}ifly_remote_layout_t;		//Զ�̵��뵼��
/*********************/
typedef struct
{
	u32 dwIp;
	u16 wPort;
}ifly_voip_t;

//Զ�̻طŲ�ѯ������ṹ
typedef struct
{
	u8   channel_no;
	u8   type;
	u32  start_time;
	u32  end_time;
	u32  card_no;
	u8   mask;
	u16  startID;			//���صĵ�һ����¼,��1��ʼ
	u16  max_return;		//ÿ�η��ص�����¼��
}ifly_recsearch_param_t;

//Զ�̻طŷ��ص���Ϣ�ṹ
typedef struct
{
	u8   channel_no;
	u8   type;
	u32  start_time;
	u32  end_time;
	u8   image_format;//3:cif;4:4cif
	u8   stream_flag;//0:��Ƶ��;1:��Ƶ��
	u32	 size;
	u32  offset;
	char filename[64];
}ifly_recfileinfo_t;

typedef struct
{
	u16   sum;		//�ܼ�¼��
	u16   startID;	//��ʼ�ļ�¼����ַΪ1�����޷�������ʱ��startID��ֵΪ0
	u16   endID;	//�����ļ�¼����ַΪ1����endID��startID���ʱ����ʾ֮����һ����¼
}ifly_recfile_desc_t;

typedef struct
{
	char mac_address[18];
	u32  ip_address;
	u16  server_port;
	u32	 net_mask;
	u32	 net_gateway;
	u32	 dns;
	u32	 multicast_address;
	u32	 admin_host;
	u16	 host_port;
	u16	 http_port;
	u8	 flag_pppoe;
	char user_name[64];
	char passwd[64];
	char pwdcheck[64];
}ifly_network_t;

//Զ��ͼ����������ṹ
typedef struct 
{
	u8   channel_no;								//ͨ����
	char channelname[32];							//ͨ����
	//��λ����ص�
	u8   flag_name;									//����λ����ʾ
	//ʱ����ص�
	u8   flag_time;									//ʱ��λ����ʾ
	u8   flag_mask;									//�ڸ�
	u8   overlay;									//�ڵ�����
	u8   lost;										//��Ƶ��ʧ
	u8   motion;									//�ƶ����
	//����ʽ
	char record_channel[16];						//������¼��ͨ��
	u8   flag_buzz;									//��������
	u8   flag_send;									//�ϴ�����
	char alarm_out[16];								//�����������
}ifly_imagset_t;


//OSDλ������ 07-07-27
typedef struct 
{
	u8		channel_no;								//ͨ����
	u8		flag_name;								//����λ���Ƿ���ʾ
	u16	 	x;										//����λ�����Ͻ�x����
	u16  	y;										//����λ�����Ͻ�y����
}ifly_channelset_t;

typedef struct 
{
	u8		channel_no;								//ͨ����
	u8		flag_time;								//ʱ��λ���Ƿ���ʾ
	u16	 	x;										//ʱ��λ�����Ͻ�x����
	u16  	y;										//ʱ��λ�����Ͻ�y����
}ifly_timeset_t;

//�ڸ����� 07-08-01
typedef struct  
{
	u8		channel_no;								//ͨ����
	u8		flag_mask;								//�Ƿ���ʾ
	u8		mask_index;								//�ڸ���������		
	u32		x;										//�ڸ���������x����
	u32		y;										//�ڸ���������y����
	u32   	width;									//�ڸ�������
	u32   	height;									//�ڸ�����߶�
}ifly_maskset_t;
//ͼ�����û��ʵ���07-08-01
typedef	struct  
{
	u8		channel_no;								//ͨ����
	u8		flag;									//���ڱ�־ 0-3
	u8		val;									//����ֵ
}ifly_picset_t;

typedef struct										//�ڵ�����Ƶ��ʧ���ƶ���Ⲽ�������ṹ
{
	u8  channel_no;									//ͨ����
	u8  week;										//����
	u8  flag_alltime;								//�Ƿ�ȫ�첼��						
	u32 starttime[4];								//ʱ���1~4����ʼʱ��
	u32 endtime[4];									//ʱ���1~4����ֹʱ��
}ifly_valid_t;

typedef struct										//Զ���ƶ���ⱨ����������ṹ
{
	u8 channel_no;									//ͨ����
	u8 recchan[4];									//������¼��ͨ��
	u8 flag_buzz;									//�Ƿ���������
	u8 flag_send;									//�Ƿ��ϴ�����
	u8 alarmout;									//�Ƿ񴥷��������
	u8 alarm_out[4];								//����ĳ·�ı������
}ifly_motion_t; 

typedef struct										//Զ���쳣����ҳ������ṹ
{
	u8 exceptiontype;								//�쳣����
	u8 flag_display;								//�Ƿ�������ʾ
	u8 flag_buzz;									//�Ƿ���������
	u8 flag_send;									//�Ƿ��ϴ�����
	u8 alarmout;									//�Ƿ񴥷��������
	u8 alarm_out[4];								//����ĳ·�ı������
}ifly_exceptioninfo_t;

typedef struct										//Զ��¼������ҳ������ṹ
{
	u8   channelno;									//ͨ����
	char channelname[32];							//ͨ����
	u8   code_type;									//��Ƶ����
	u8   video_resolution;							//�ֱ���
	u8   bit_type;									//λ������
	u32  bit_max;									//λ������
	u8   quality;									//ͼ������
	u8   frame_rate;								//��Ƶ֡��
	u16  pre_record;								//Ԥ¼ʱ��
	u16  post_record;								//¼����ʱ
	u8   flag_record;								//�Ƿ�����¼��
}ifly_recordinfo_t;

typedef struct										//Զ��¼������ҳ������ṹ
{
	u8  channelno;									//ͨ����
	u8  week;										//����
	u8  flag_alltime;								//�Ƿ�ȫ�첼��
	u8  alltype;									//ȫ�첼��ʱ��¼������
	u32 start_time[4];								//ʱ���1~4����ʼʱ��
	u32 end_time[4];								//ʱ���1~4����ֹʱ��
	u8  type[4];									//ʱ���1~4��¼������
}ifly_recordtime_t;

typedef struct										//Զ�̱�������ҳ��
{
	u8  inid;										//���������� 
	u8  typein;										//������������
	u8  flag_deal;									//�Ƿ񴥷��������봦��
	u8  copyin;
	u8  in_copy;									//�Ƿ�ѡ�񱨾����ĸ���
	u8  outid;										//ѡ�񱨾����
	u8  typeout;									//����������� 
	u8  out_copy;									//�����������
	u8  copyout;
	u16 delay;										//���������ʱ	
}ifly_alarmset_t;

typedef struct										//Զ��ptz����
{
	u8 inid;										//����������
	u8 channo;										//ͨ����
	u8 flag_preset;									//Ԥ�õ�
	u8 preset;
	u8 flag_cruise;									//Ѳ����
	u8 cruise;
	u8 flag_track;									//�켣
}ifly_alarmin_ptz;

typedef struct										//��������
{
	u8  id;											//ѡ�񱨾���
	u8  week;										//����	
	u8  flag_alltime;								//ȫ�첼��
	u32 starttime[4];								//ʱ���1~4����ʼʱ��
	u32 endtime[4];									//ʱ���1~4����ֹʱ��
}ifly_alarm_settime;

#define MD_ROW			12
#define MD_COL			16
#define MD_MIN_SENSE	0							//�����
#define MD_MAX_SENSE	5							//������

typedef struct
{
	u8   channel_no;
	u8   flag;  //�Ƿ����ƶ����
	u8   sense;	//������ MD_MIN_SENSE-MD_MAX_SENSE
	u8   block[MD_ROW*MD_COL];//��0ѡ�� 0��ѡ��
}ifly_md_param_t;

typedef struct
{
	u8   channel_no;
	u8	 byCmdId;	//����ͷ������������
	u8	 abyParam[MAX_PARAM_NUM];//����
	u8   byCtrlWay;	//����ͷ��������Ʒ�ʽ CAM_CTRLWAY_GENERAL:����;CAM_CTRLWAY_REVERSE:����
}ifly_camera_ctrl_t;

typedef struct  
{
	u16		width;
	u16   height;
}ifly_pic_resolution_t;		//�������͸��ͻ��˵�ͼ��ֱ���

typedef struct
{
	u8   channel_no;
}ifly_need_resolution_t;	//��ͨ����Ҫ��������ͼ��ֱ���

#pragma pack( pop )

typedef u16 (*pMESSAGE_CB)(CPHandle cph,u16 event,u8 *pbyMsgBuf,int msgLen,u8 *pbyAckBuf,int *pAckLen,void* pContext);
void SetMsgCallBack(pMESSAGE_CB pCB,void *pContext);

u16  CPLibInit(u16 wPort);
u16  CPLibCleanup();

//���ӷ�����
CPHandle CPConnect(u32 dwServerIp, u16 wServerPort, u32 dwTimeOut, u16 *pwErrorCode);
//�崦����
u16  CleanCPHandle(CPHandle cph);
//�����¼�֪ͨ
u16  CPPost(CPHandle cph, u16 event, const void *content, int length);
//��������
u16  CPSend(CPHandle cph, u16 event, const void *content, int length, void* ackbuf, int ackbuflen, int *realacklen, u32 dwTimeOut);

//�õ�TCP���ӵı���ip��ַ��˿� 07-07-27 ??
BOOL GetCPHandleLocalAddr(CPHandle cph, struct sockaddr_in *pAddr);

//����NAT̽���	07-07-27 ??
BOOL SendSTUNPacket(u32 dwLocalIpAddr, u16 wLocalPort, u32 dwRemoteIpAddr, u16 wRemotePort, u8 *pbyBuf, u32 dwBufLen);

u16  GetTransactionNum();

u16  StartNetMonitor(ifly_monitor_param_t mp,u32 dwServerIp,u16 wServerPort,u32 dwTimeOut);
u16  StopNetMonitor(ifly_monitor_param_t mp,u32 dwServerIp,u16 wServerPort,u32 dwTimeOut);

u16  StartAudioNetMonitor(ifly_monitor_param_t mp,u32 dwServerIp,u16 wServerPort,u32 dwTimeOut);
u16  StopAudioNetMonitor(ifly_monitor_param_t mp,u32 dwServerIp,u16 wServerPort,u32 dwTimeOut);

u16  StartRemotePlay(ifly_remote_playback_t rp,u32 dwServerIp,u16 wServerPort,u32 dwTimeOut);
u16  StopRemotePlay(ifly_remote_playback_t rp,u32 dwServerIp,u16 wServerPort,u32 dwTimeOut);

/***************************************************************************************************************/
//���ͽ�������������������ؿ��ƴ�������ս��
//��������Ϊ��
//	1.client�˽�Ҫ���͵Ĳ������ض��ĸ�ʽ�����Ȼ����ñ�����
//	2.server�˽��յ�����󣬽�����Ӧ�Ĵ���
//	3.server���ݴ��������ض�Ӧ����Ϣ��client�����ر�socket ���ӣ�

//���������
//	dwHostIp��������IP��ַ
//	dwTimeOut�������ĳ�ʱʱ��
//	pBuf�����͵�����ͷ��������������Ϣ�������������У�pBuf = ifly_cp_header_t + ifly_monitor_param_t
//	dwBufLen��pBuf�ĳ���
//����ֵ��
//	0�����óɹ�
//	����������ʧ��
/***************************************************************************************************************/
u16  SendToHost(u32 dwHostIp, u32 dwTimeOut, void *pBuf, u32 dwBufLen);

/***************************************************************************************************************/
//���ͽ������������������Ҫ��������ö������Ϣ
//��������Ϊ��
//	1.client�˽�Ҫ���͵Ĳ������ض��ĸ�ʽ�����Ȼ����ñ�����
//	2.server�˽��յ�����󣬽�����Ӧ�Ĵ���
//	3.server���ݴ��������ض�Ӧ����Ϣ��client�����ر�socket ���ӣ�

//���������
//	dwHostIp��������IP��ַ
//	dwTimeOut�������ĳ�ʱʱ��
//	pinBuf�����͵�����ͷ��������������Ϣ�������������У�pinBuf = ifly_cp_header_t + ifly_monitor_param_t
//	dwinBufLen��pinBuf�ĳ���
//	dwoutBufLen��poutBuf��󳤶ȣ���ֹ�ڴ����
//���������
//	poutBuf�����������յ�����ͷ��������������Ϣ������Զ�̻طŲ�ѯ�У�poutBuf = ifly_cp_header_t + ��ѯ�Ľ��
//	dwoutBufLen��ʵ�ʽ��յ���buf�ĳ���
//����ֵ��
//	0�����óɹ�
//	����������ʧ��
//ע�⣺
//	����Ӧ���������dwoutBufLen�����Ʒ��ظ�client��������ݣ�������ܵ����������
/***************************************************************************************************************/
u16  SendToHost2(u32 dwHostIp, u32 dwTimeOut, void *pinBuf, u32 dwinBufLen, void *poutBuf, u32 *dwoutBufLen);

#ifdef __cplusplus
}
#endif

#endif
