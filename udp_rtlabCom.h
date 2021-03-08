#include "vxWorks.h"

#include "semLib.h"

#include <socket.h>
#include <in.h>
#include "main_variable.h"


unsigned short mcuStsStopPosNum=0;
#define con_A 1
#define con_B 2
int com_port;

#define PORTA 10000
#define PORTB 1100

char * ast7700_UDP_A="172.16.11.1234587";
char * RTLAB_UDP_A="172.16.11.123458";;

int sdRamAdrs;

int sockDccA,sockDccB,sockMcuACon,sockMcuBCon,sockMcuA,sockMcuA1,sockMcuB,sockMcuB1;
int sockMcuACon1,sockMcuBCon1;
int sockDccAConFlag,sockDccBConFlag,sockMcuAConFlag,sockMcuBConFlag;
SEM_ID semMcuaWrite,semDccWrite,semMcuaRead,semMcubRead,semMcuaWd,semMcubWd,semMcuaRestart,semMcubRestart;
SEM_ID logSem,Sem5136,stop5136_sem,yuhe5136_sem,yuhe5136_sem_frog;


int tMcuaAccept,tMcubAccept;
int tMcuaAccept1,tMcubAccept1;

#define yuhe_OK 0xa0
#define yuhe_DOWN 0
unsigned int yuhe5136_status;
#define m_num 26
#define p_num 35
#define SEC 7
#define dccSts_size sizeof(struct dccStatus)
#define mcuSts_size sizeof(struct mcuStatus)
#define stsChange_size sizeof(struct statusChange)
#define mcuAck_size sizeof(struct mcuAck)
#define log_size sizeof(struct log)
#define logout_size sizeof(struct logout)
#define lineData_size sizeof(struct lineData)
#define maxSpeedLine_size sizeof(struct maxSpeedLine)
#define stopPosRunReq_size sizeof(struct stopPosRunReq)
#define stopPosRunStep_size sizeof(struct stopPosRunStep)
#define lineDataDel_size sizeof(struct lineDataDel)
#define trainChange_size sizeof(struct trainChange)

#define MSG_SIZE sizeof(struct test)
#define MAX_CONNECTION 3
#define SA_LEN sizeof(struct sockaddr_in)

WDOG_ID	mcuaWgId,mcubWgId;

#define SWAP(x) ( (x<<8)|(x>>8) )


short IBR[24]={0x0,0x0,0x0,0x0,0x40,0x0,0,0,0xc048,0x4007,0xc020,0x4007,0xfffe,0xffff,0xaaaa,0xaaaa,0x5555,0x5555,0x55aa,0x55aa,0xaa55,0xaa55,0x7f99,0x7ff0};

unsigned short calculate;
int dingziduan_mode;
int dingziduan;
int tmpnode=0;
int k=0;
int tmpnodeOld=1;
int dingziduan_cmd;
int tmpnode_cmd=0;
int tmpnodeOld_cmd=1;
int MasBaseAdrs=0x8000;
int MasMemAdrs=0x100000;
char* localMasBaseAddr;
char* localMasMemAddr;
char* localBaseAddrRfmFor5136;

#ifdef MCU1_1
int sdRamAdrs=0x8c000000;
#endif

#ifdef MCU1_2
int sdRamAdrs=0x8c100000;
#endif

#ifdef MCU2_1
int sdRamAdrs=0x8c200000;
#endif

#ifdef MCU2_2
int sdRamAdrs=0x8c300000;
#endif


int   sdRamAdrsFor5136=0x8c000200;
int sdRamAdrs2536=0x7f0;
char* localBaseAddr5565;
char* localBaseAddr2536;
int tRun,tAccept,tAccept1,tstsChange;
int sockAddrSize;
unsigned short dccSts_seq=0;
unsigned short mcuSts_seq=0;
unsigned short stsChange_seq=0;
unsigned short logout_seq=0;
unsigned short log_seq=0;
unsigned short trainChange_seq=0;


unsigned char * p;
unsigned char dccSts_reCount=0;
unsigned char ch1_sts=0,ch2_sts=0;
unsigned char dccSts_respon=0,transSts_ready=1;
unsigned short dccCmd_Seq=0;
unsigned short crc,crcResult;
unsigned char conFd1_flag=0;

unsigned short SequenceNum=0;

	struct itimerspec itmsp;
/*	struct sigevent tmevent;*/
	timer_t tm;
/*	struct sigaction tmact;*/
	struct timespec tp;

struct itimerspec itmsp1;
/*	struct sigevent tmevent;*/
	timer_t tm1;
/*	struct sigaction tmact;*/
	struct timespec tp1;

struct itimerspec itmsp2;
/*	struct sigevent tmevent;*/
	timer_t tm2;
/*	struct sigaction tmact;*/
	struct timespec tp2;


unsigned short crctab[256]=
{
  0x0000,0x1021,0x2042,0x3063,0x4084,0x50A5,0x60C6,0x70E7,0x8108,0x9129,0xA14A,0xB16B,0xC18C,0xD1AD,
  0xE1CE,0xF1EF,0x1231,0x0210,0x3273,0x2252,0x52B5,0x4294,0x72F7,0x62D6,0x9339,0x8318,0xB37B,0xA35A,
  0xD3BD,0xC39C,0xF3FF,0xE3DE,0x2462,0x3443,0x0420,0x1401,0x64E6,0x74C7,0x44A4,0x5485,0xA56A,0xB54B,
  0x8528,0x9509,0xE5EE,0xF5CF,0xC5AC,0xD58D,0x3653,0x2672,0x1611,0x0630,0x76D7,0x66F6,0x5695,0x46B4,
  0xB75B,0xA77A,0x9719,0x8738,0xF7DF,0xE7FE,0xD79D,0xC7BC,0x48C4,0x58E5,0x6886,0x78A7,0x0840,0x1861,
  0x2802,0x3823,0xC9CC,0xD9ED,0xE98E,0xF9AF,0x8948,0x9969,0xA90A,0xB92B,0x5AF5,0x4AD4,0x7AB7,0x6A96,
  0x1A71,0x0A50,0x3A33,0x2A12,0xDBFD,0xCBDC,0xFBBF,0xEB9E,0x9B79,0x8B58,0xBB3B,0xAB1A,0x6CA6,0x7C87,
  0x4CE4,0x5CC5,0x2C22,0x3C03,0x0C60,0x1C41,0xEDAE,0xFD8F,0xCDEC,0xDDCD,0xAD2A,0xBD0B,0x8D68,0x9D49,
  0x7E97,0x6EB6,0x5ED5,0x4EF4,0x3E13,0x2E32,0x1E51,0x0E70,0xFF9F,0xEFBE,0xDFDD,0xCFFC,0xBF1B,0xAF3A,
  0x9F59,0x8F78,0x9188,0x81A9,0xB1CA,0xA1EB,0xD10C,0xC12D,0xF14E,0xE16F,0x1080,0x00A1,0x30C2,0x20E3,
  0x5004,0x4025,0x7046,0x6067,0X83B9,0X9398,0XA3FB,0XB3DA,0XC33D,0XD31C,0XE37F,0XF35E,0X02B1,0X1290,
  0X22F3,0X32D2,0X4235,0X5214,0X6277,0X7256,0XB5EA,0XA5CB,0X95A8,0X8589,0XF56E,0XE54F,0XD52C,0XC50D,
  0X34E2,0X24C3,0X14A0,0X0481,0X7466,0X6447,0X5424,0X4405,0XA7DB,0XB7FA,0X8799,0X97B8,0XE75F,0XF77E,
  0XC71D,0XD73C,0X26D3,0X36F2,0X0691,0X16B0,0X6657,0X7676,0X4615,0X5634,0XD94C,0XC96D,0XF90E,0XE92F,
  0X99C8,0X89E9,0XB98A,0XA9AB,0X5844,0X4865,0X7806,0X6827,0X18C0,0X08E1,0X3882,0X28A3,0XCB7D,0XDB5C,
  0XEB3F,0XFB1E,0X8BF9,0X9BD8,0XABBB,0XBB9A,0X4A75,0X5A54,0X6A37,0X7A16,0X0AF1,0X1AD0,0X2AB3,0X3A92,
  0XFD2E,0XED0F,0XDD6C,0XCD4D,0XBDAA,0XAD8B,0X9DE8,0X8DC9,0X7C26,0X6C07,0X5C64,0X4C45,0X3CA2,0X2C83,
  0X1CE0,0X0CC1,0XEF1F,0XFF3E,0XCF5D,0XDF7C,0XAF9B,0XBFBA,0X8FD9,0X9FF8,0X6E17,0X7E36,0X4E55,0X5E74,
  0X2E93,0X3EB2,0X0ED1,0X1EF0,
 };

typedef struct test
    { 
	unsigned	char	a[48];/*84*/
//	unsigned	char	a[4098];/*84*/
    }test;

#pragma pack(1)

struct data{
	unsigned short seqNumber;
	unsigned char reCount;
	unsigned char packLength;
	unsigned char target;
	unsigned char source;
	unsigned char sourceFlag;
	unsigned char packFlag;
};

struct start{
	unsigned char meshead;
	struct data startHead;
	unsigned char trainFlag;
	unsigned char startPoint;
	unsigned short res;
	unsigned int startPos;
	unsigned short res1;
	unsigned short crc;
	unsigned char mesend;
};

struct run{
	unsigned char meshead;
	struct data runHead;
	unsigned char trainFlag;
	unsigned char dirFlag;
	unsigned short res;
	unsigned int startPoint;
	unsigned int stopPoint;
	unsigned int maxSpeed;
	unsigned int maxAccelerate;
	unsigned short res1;
	unsigned short crc;
	unsigned char mesend;
};

struct log{
	unsigned char meshead;
	struct data logHead;
	unsigned char trainFlag;
	unsigned char trainType; /* 列车类型*/
	unsigned char numberDCS;  /*  DCS 编号 */
	unsigned char direction;  /*   列车方向12 bytes，0表示列车方向未知，1表示列车前进，2表示列车后退*/
	unsigned int position;
	unsigned int length;
	unsigned short maxSpeed;
	unsigned short crc;
	unsigned char mesend;
};

struct logout{
	unsigned char meshead;
	struct data logoutHead;
	unsigned char trainFlag;      /*列车标识号*/
	unsigned char reserve;
	unsigned short crc;
	unsigned char mesend;
};

struct trainChange{/*列车切换报文*/
	unsigned char meshead;
	struct data trainChangeHead;
	unsigned char realTrainFlag;
	unsigned char virtualTrainFlag;
	unsigned short crc;
	unsigned char mesend;
};

struct maxSpeedLine{
	unsigned char meshead;
	struct data maxSpeedLineHead;
	unsigned short stopPosFlag;
	unsigned char trainFlag;
        unsigned char numberDNS;   /*12bytes  DCS 编号*/
        unsigned short reserve;
	unsigned char lastSpeedTrue;
	unsigned char dataSum;
	unsigned char speedData[8*p_num];/*p_num points*/
	unsigned char reserve2[8];
	unsigned short crc;
	unsigned char mesend;
};

struct lineData{
	unsigned char meshead;
	struct data lineDataHead;
	unsigned short stopPosFlag;  /*KI停车点运行标识号，本报文传递DP,FPM*/
	unsigned char trainFlag;
	unsigned char numberDNS;   /*12bytes  DCS 编号*/
	unsigned short stopPosNum;  /*     到达的停车点号码   */
	unsigned char stopPosType; /*   停车点类型(前三位有效)  1表示车站，2表示停车点，4表示服务区  */
	unsigned char positionNum; /*报文中包含的位置数据数量，小于26 */
	unsigned char line_Data[4*m_num];/* dingziduan，总共104个字节*/
        unsigned char reserve[4];
	unsigned int positionDP;
	unsigned int positionFPM;
	unsigned int lastDCSposition;
	unsigned int nextDCSposition;
	unsigned short crc;
	unsigned char mesend;
};

struct lineData1{
	unsigned char meshead;
	struct data lineDataHead;
	unsigned char stopPosFlag;
	unsigned char trainFlag;
	unsigned char stopPosNum;
	unsigned char stopPosType;
	unsigned char reserve[3];
	unsigned char lineDataLength;
	unsigned char line_Data[4];/*m dingziduan=1*/
	unsigned int tarStopPos;
	unsigned int maxSpeedRootPos;
	unsigned short reserve1;
	unsigned short crc;
	unsigned char mesend;
};

struct lineData2{
	unsigned char meshead;
	struct data lineDataHead;
	unsigned char stopPosFlag;
	unsigned char trainFlag;
	unsigned char stopPosNum;
	unsigned char stopPosType;
	unsigned char reserve[3];
	unsigned char lineDataLength;
	unsigned char line_Data[8];/*m dingziduan=2*/
	unsigned int tarStopPos;
	unsigned int maxSpeedRootPos;
	unsigned short reserve1;
	unsigned short crc;
	unsigned char mesend;
};

struct lineData3{
	unsigned char meshead;
	struct data lineDataHead;
	unsigned char stopPosFlag;
	unsigned char trainFlag;
	unsigned char stopPosNum;
	unsigned char stopPosType;
	unsigned char reserve[3];
	unsigned char lineDataLength;
	unsigned char line_Data[12];/*m dingziduan=3*/
	unsigned int tarStopPos;
	unsigned int maxSpeedRootPos;
	unsigned short reserve1;
	unsigned short crc;
	unsigned char mesend;
};

struct lineData4{
	unsigned char meshead;
	struct data lineDataHead;
	unsigned char stopPosFlag;
	unsigned char trainFlag;
	unsigned char stopPosNum;
	unsigned char stopPosType;
	unsigned char reserve[3];
	unsigned char lineDataLength;
	unsigned char line_Data[16];/*m dingziduan=4*/
	unsigned int tarStopPos;
	unsigned int maxSpeedRootPos;
	unsigned short reserve1;
	unsigned short crc;
	unsigned char mesend;
};

struct statorLineData{
	unsigned char meshead;
	unsigned char statorFlag;
	unsigned char res[3];
};	/*included above*/

struct lineDataDel{
	unsigned char meshead;
	struct data lineDataDelHead;
	unsigned short stopPosFlag;
	unsigned char trainFlag;                /*                11 bytes               */
	unsigned char delRange;                /*    0,2位表示，1表示删除指定邋KI的停车点运行数据，2表示沿线路数据方向从指定位置删除所有线路数据，4表示删除所有线路数据 */
	unsigned int pos;                     /*  位置数据，从该处沿线路数据方向删除所有线路数据*/
	unsigned short crc;
	unsigned char mesend;
};

struct stopPosRunReq{                  /* 通过本报文，DCC向MCU请求计算到以KI标识的停车点运行DP制动曲线的计算状态 */
	unsigned char meshead;
	struct data stopPosRunReqHead;
	unsigned short stopPosFlag;
	unsigned char trainFlag;
	unsigned char reserve;
	unsigned short crc;
	unsigned char mesend;
};

struct stopPosRunStep
{
	unsigned char meshead;
	struct data stopPosRunStepHead;
	unsigned short stopPosFlag;
	unsigned char trainFlag;
	unsigned char reserve;
	unsigned short crc;
	unsigned char mesend;
};

struct statusChange{
	unsigned char meshead;
	struct data statusChangeHead;
	unsigned char status;      /*   00表示牵引系统提交当前状态，01表示初始状态，02表示基本状态，04表示带电等待状态，08列车运行，10表示准备测试，20表示带电牵引测试，40不带电牵引测试，80模拟运行*/             
	unsigned char res;
	unsigned short crc;
	unsigned char mesend;
};

struct dccStatus{
	unsigned char meshead;
	struct data dccStatusHead;
	unsigned char ch1status;
        unsigned char res1;  /*  10 bytes */
	unsigned char ch2status;
        unsigned char res2;   /*  12 bytes */
	unsigned char responGot;  /* 响应DCC状态报文的牵引报文状态，0表示已经收到牵引控制系统对上一次DCC状态报文的报文，1表示没有收到牵引控制系统的响应 */	
	unsigned char statusReadyInfo;	/*1表示无与就绪信息有关的请求，2表示删除牵引状态改变就绪信息*/
	unsigned short confirmLastCmdSeq; /*  上次应答的报文序列号(A类)*/
	unsigned char maxRepeat;  /*  DCC 可重复报文的最大数量  */
	unsigned char trainFlag;/*  当前列车标识号 18bytes */
	unsigned char trainStatus;     /*  0,1位表示悬浮/落下命令状态，2,3位表示相应状态，4-7位保留  */
    unsigned char operationregulation; /*  0--3位表示期望速度的默认类型，4---7期望牵引系统的运行方向     */
	unsigned short speed;	/* 期望速度和最大速度百分比     */
	unsigned short limitAcceleration;		
	unsigned short minSpeed;
	unsigned char diagnose;
	unsigned char res3;
	unsigned char res[128];
	unsigned short crc;
    unsigned char mesend;
};

struct mcuStatus{


        unsigned char meshead;  
	struct data mcuStatusHead;
	unsigned char ch1status;  /* 9 bytes */
        unsigned char res1;
	unsigned char ch2status;
        unsigned char res2;      /* 12 bytes */
	unsigned char respon;	
	unsigned char reDccCmdFlag;
	unsigned short reDccCmdSeq;
	unsigned char statusReadyInfo;
	unsigned char trainFlag;     /* 18 bytes 当前列车的列车标识号*/ 
	unsigned char cancelinfo;    /* 19 bytes 注销"当前"列车就绪信息*/ 
	unsigned char dcsnumber;     /* 20 bytes DCS编号*/ 
	int currentPos;           /* 21 -24bytes "当前"列车的当前位置，相对于列车中心*/ 
        short currentSpeed;
	short currentAcceleration;
	unsigned char TractioninusePercent;  
	unsigned char trainStatus;  /* 30 bytes 当前列车的状态*/ 
	unsigned char virtualTrainFlag;
	unsigned char logoutVirtualTrainReady;
	unsigned char virtualPercent;	
	unsigned char errorLevel;	
	unsigned char stopPosNum;
	unsigned char res3;      /* 36 bytes */
	unsigned short real_test_info[10];
	unsigned short virtual_test_info[10];
	unsigned char res4[96];
	unsigned short crc;
        unsigned char mesend;
};

struct mcuAck{
        unsigned char meshead;
	struct data mcuAckHead;
	unsigned char ch1status;
        unsigned char res1;
	unsigned char ch2status;
        unsigned char res2;        /* 12 bytes */
	unsigned char errorFlag;  
	unsigned char reDccCmdFlag;    /*need number of Dcc packed resend */	
	unsigned char statusChange;    /* 1表示没有处理状态，2表示请求正在处理，3表示请求已执行，3表示处理过程中发生错误*/
	unsigned char ackPacketFlag;   /*应答的报文的报文标识号*/
        unsigned short infoReq1;
        unsigned char infoReq2;
        unsigned char infoReq3;
	unsigned short crc;
        unsigned char mesend;
};

#pragma pack()

struct start start;
struct run run;

struct trainChange trainChange;
struct dccStatus dccSts;
struct mcuStatus mcuSts;
struct statusChange stsChange;
struct mcuAck mcuAck;

struct logout logout;
struct lineData lineData;
struct maxSpeedLine maxSpeedLine;
struct stopPosRunReq stopPosRunReq;
struct stopPosRunStep stopPosRunStep;
struct lineDataDel lineDataDel;

struct RTLAB_REC_DATA  RTLAB_datain;/*add lhc for send data to rtlab*/
struct RTLAB_SEND_DATA  RTLAB_dataout;/*add lhc for receive data from rtlab*/


void run5136(void);
void sts5136(void);


STATUS taskMcuA();
STATUS taskDccA();
STATUS taskDccA1();
STATUS taskDccB();

STATUS taskMcuA_test();
STATUS taskMcuA1();
STATUS taskMcuB();

void taskSem();
void taskMcuaAccept();
void taskMcuaAccept1();
void taskMcuWrite();
void taskDccWrite();
void tx_dccSts();
void tx_mcuSts();
void taskTimer();
void taskMcubAccept();
void taskDccSem();
void taskDccTimer();
void timer_dccHandler(timer_t tm, int arg);
void timer_handler(timer_t tm, int arg);
void taskMcuaRead();
void taskMcubRead();
void taskMcuaWatchDg();
void taskMcubWatchDg();
void taskSetSockMcuAConFlag();
void taskSetSockMcuBConFlag();
int taskMcuaRestart();
int taskMcubRestart();

void init()
{
	int i;
/*Client:  dccSts packet*/
            dccSts.meshead=0x02;
			dccSts.dccStatusHead.seqNumber=0;
			dccSts.dccStatusHead.reCount=0;
			dccSts.dccStatusHead.packLength=0x4f;/*  79    158 */
			dccSts.dccStatusHead.target=0x3;/*0x2*/
			dccSts.dccStatusHead.source=0x3;/*0x2*/
			dccSts.dccStatusHead.sourceFlag=0x1;/*0x2*/
			dccSts.dccStatusHead.packFlag=0x1;
			dccSts.ch1status=0x0;
			dccSts.ch2status=0x0;
			dccSts.responGot=0x0;
			dccSts.statusReadyInfo=0x0;
			dccSts.confirmLastCmdSeq=0x0;
			dccSts.maxRepeat=0x5;
			dccSts.trainFlag=0x1;	
			dccSts.trainStatus=0x0;
			dccSts.res1=0;
			dccSts.res2=0;
			dccSts.res3=0;
			dccSts.speed=0x0;
			dccSts.limitAcceleration=0x0;
			dccSts.minSpeed=0;
			dccSts.diagnose=0;
			for(i=0;i<128;i++)
		{
			dccSts.res[i]=0;
		}
			dccSts.crc=0x0;
            dccSts.mesend=0x03;

/*trans status change packet*/

stsChange.meshead=0x2;
	stsChange.statusChangeHead.seqNumber=0;
	stsChange.statusChangeHead.reCount=0;
	stsChange.statusChangeHead.packLength=0x7;/*  7   14*/
	stsChange.statusChangeHead.target=3;
	stsChange.statusChangeHead.source=3;
	stsChange.statusChangeHead.sourceFlag=5;
	stsChange.statusChangeHead.packFlag=0x9;
	stsChange.status=0;/*init status*/
	stsChange.res=0;
	stsChange.crc=0;
stsChange.mesend=0x3;

/*mcuSts packet*/
			
                        mcuSts.meshead=0x02;
                        mcuSts.mcuStatusHead.seqNumber=0;
			mcuSts.mcuStatusHead.reCount=0x0;
			mcuSts.mcuStatusHead.packLength=0xAE;
			mcuSts.mcuStatusHead.target=0x3;/*0x2*/
			mcuSts.mcuStatusHead.source=0x3;/*0x2*/
			mcuSts.mcuStatusHead.sourceFlag=0x1;/*0x2*/
			mcuSts.mcuStatusHead.packFlag=0x81;
			mcuSts.ch1status=0x0;
			mcuSts.ch2status=0x0;
			mcuSts.respon=0x0;
			mcuSts.reDccCmdFlag=0;
			mcuSts.reDccCmdSeq=0;
			mcuSts.statusReadyInfo=1;
			mcuSts.trainFlag=0x0;/*initialize 0*/
			mcuSts.cancelinfo=0x1;
			mcuSts.dcsnumber=0x3;
			mcuSts.currentPos=0x11223344;
			mcuSts.currentSpeed=0x55;
			mcuSts.currentAcceleration=0x0;
			mcuSts.TractioninusePercent=0x77;
                	mcuSts.trainStatus=0x0;
			mcuSts.virtualTrainFlag=0x1;
			mcuSts.logoutVirtualTrainReady=0;
			mcuSts.virtualPercent=0;	
			mcuSts.errorLevel=4;	
			mcuSts.stopPosNum=0x10;	
			
		for(i=0;i<20;i++)
		{
			mcuSts.real_test_info[i]=0;
			mcuSts.virtual_test_info[i]=0;
		}
               mcuSts.real_test_info[1]=0xc9;
		for(i=0;i<96;i++)
		{
			mcuSts.res4[i]=0;
		}
			mcuSts.res1=4;
			mcuSts.res2=5;
			mcuSts.res3=0xef;
			
			mcuSts.crc=0x0;
                        mcuSts.mesend=0x3;

/*mcu ack packet*/
        mcuAck.meshead=0x02;
	mcuAck.mcuAckHead.seqNumber=0;
	mcuAck.mcuAckHead.reCount=0;
	mcuAck.mcuAckHead.packLength=0xb; /* 11  22  */
	mcuAck.mcuAckHead.target=3;
	mcuAck.mcuAckHead.source=3;
	mcuAck.mcuAckHead.sourceFlag=1;
	mcuAck.mcuAckHead.packFlag=0x82;
	mcuAck.ch1status=0x0;
        	mcuAck.res1=0x0;
	mcuAck.ch2status=0x0;
          	mcuAck.res2=0x0;
	mcuAck.errorFlag=0;	
	mcuAck.reDccCmdFlag=0;
	mcuAck.statusChange=0;
	
	mcuAck.ackPacketFlag=0;
	mcuAck.infoReq1=0;
        mcuAck.infoReq2=0;
	mcuAck.infoReq3=0;
	mcuAck.crc=0;
        mcuAck.mesend=0x3;

/*trainChange packet*/
trainChange.meshead=0x2;
trainChange.mesend=0x3;
trainChange.trainChangeHead.seqNumber=0;
trainChange.trainChangeHead.reCount=0;
trainChange.trainChangeHead.packLength=7;
trainChange.trainChangeHead.target=1;
trainChange.trainChangeHead.source=1;
trainChange.trainChangeHead.sourceFlag=1;
trainChange.trainChangeHead.packFlag=0x4;

trainChange.realTrainFlag=1;
trainChange.virtualTrainFlag=0;
trainChange.crc=0;


/*logout packet*/
logout.meshead=0x2;
logout.mesend=0x3;
	logout.logoutHead.seqNumber=0;
	logout.logoutHead.reCount=0;
	logout.logoutHead.packLength=0x7;/*  7  14 */
	logout.logoutHead.target=3;
	logout.logoutHead.source=3;
	logout.logoutHead.sourceFlag=1;
	logout.logoutHead.packFlag=0x2;
	logout.trainFlag=1;
	logout.reserve=0;
	logout.crc=0;

/*line data packet*/
	lineData.lineDataHead.seqNumber=0;
	lineData.lineDataHead.reCount=0;
	lineData.lineDataHead.packLength=lineData_size;
	lineData.lineDataHead.target=3;
	lineData.lineDataHead.source=3;
	lineData.lineDataHead.sourceFlag=1;
	lineData.lineDataHead.packFlag=0x5;
	lineData.stopPosFlag=0x10;
	lineData.trainFlag=1;
	lineData.stopPosNum=1;
	lineData.stopPosType=1;
	lineData.line_Data[4*m_num]=0;
	lineData.reserve[4]=0; 
	lineData.positionDP=0;
	lineData.positionFPM=0;
        lineData.lastDCSposition=0;
        lineData.nextDCSposition=0;
	lineData.crc=0;

/*maxSeedLine packet*/
	maxSpeedLine.maxSpeedLineHead.seqNumber=0;
	maxSpeedLine.maxSpeedLineHead.reCount=0;
	maxSpeedLine.maxSpeedLineHead.packLength=maxSpeedLine_size;
	maxSpeedLine.maxSpeedLineHead.target=3;
	maxSpeedLine.maxSpeedLineHead.source=3;
	maxSpeedLine.maxSpeedLineHead.sourceFlag=3;
	maxSpeedLine.maxSpeedLineHead.packFlag=0x5;
	maxSpeedLine.stopPosFlag=0x10;
	maxSpeedLine.trainFlag=1;
        maxSpeedLine.reserve=0;
        maxSpeedLine.numberDNS=0;
	maxSpeedLine.lastSpeedTrue=0;
	maxSpeedLine.dataSum=p_num;
	maxSpeedLine.speedData[8*p_num]=0;/*p_num points*/
	maxSpeedLine.reserve2[8]=0;
	maxSpeedLine.crc=0;

/*stopPosRunReq packet*/
	stopPosRunReq.stopPosRunReqHead.seqNumber=0;
	stopPosRunReq.stopPosRunReqHead.reCount=0;
	stopPosRunReq.stopPosRunReqHead.packLength=0xc;
	stopPosRunReq.stopPosRunReqHead.target=3;
	stopPosRunReq.stopPosRunReqHead.source=3;
	stopPosRunReq.stopPosRunReqHead.sourceFlag=1;
	stopPosRunReq.stopPosRunReqHead.packFlag=0x7;
	stopPosRunReq.stopPosFlag=0x0;
	stopPosRunReq.trainFlag=1;
	stopPosRunReq.reserve=0;
	stopPosRunReq.crc=0;
/*stopPosRunStep packet*/
	stopPosRunStep.stopPosRunStepHead.seqNumber=0;
	stopPosRunStep.stopPosRunStepHead.reCount=0;
	stopPosRunStep.stopPosRunStepHead.packLength=0x10;
	stopPosRunStep.stopPosRunStepHead.target=3;
	stopPosRunStep.stopPosRunStepHead.source=3;
	stopPosRunStep.stopPosRunStepHead.sourceFlag=1;
	stopPosRunStep.stopPosRunStepHead.packFlag=0x8;
	stopPosRunStep.stopPosFlag=0x10;
	stopPosRunStep.trainFlag=1;
	stopPosRunStep.reserve=0;
	stopPosRunStep.crc=0;

/*lineDataDel packet*/
	lineDataDel.lineDataDelHead.seqNumber=0;
	lineDataDel.lineDataDelHead.reCount=0;
	lineDataDel.lineDataDelHead.packLength=0x14;
	lineDataDel.lineDataDelHead.target=3;
	lineDataDel.lineDataDelHead.source=3;
	lineDataDel.lineDataDelHead.sourceFlag=1;
	lineDataDel.lineDataDelHead.packFlag=0x6;
	lineDataDel.stopPosFlag=0x10;
	lineDataDel.trainFlag=1;
	lineDataDel.delRange=0x1;
	lineDataDel.pos=0;
	lineDataDel.crc=0;
	
#if 0	//romove lhc for double test 20190322
	RTLAB_datain.dev_id=1;
	RTLAB_datain.msg_id=2;
	RTLAB_datain.msg_len=0;
#endif  	
//	RTLAB_datain.data[0]=0;

}
