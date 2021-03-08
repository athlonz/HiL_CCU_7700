/*  
* target: 软示波器UDP上传数据显示程序   
* Copyright 2018,4,16 IEE, Inc. 
* description: 使用UDP协议，用网线上传数据给电脑  
* function: 
* debug: 
* modification history:

*/
/********************************************************************************/
#include "subMod_DataDisplayUDP.h"
#include "math.h"
 /********************************************************************************/
/*通讯数据定义*/
#define LENGTH_SEND_BUF 480

struct  HIGH_RATE_DISPLAY_SAVE HighRateDisplaySaveBuf;     /*data struct high rate display*/
INT16   SendHighRateDisplaySaveBufUDP[LENGTH_SEND_BUF];   /*send buffer*/

struct  MODU_VOLTAGE_DISPLAY ModuVoltageDisplayBuf;        /*voltage display*/
struct  TEMPR_FAULT_DISPLAY TemprFaultDisplay;

struct  HIGH_RATE_DISPLAY_SAVE HighRateDisplaySaveBufMsg; 
struct  MODU_VOLTAGE_DISPLAY ModuVoltageDisplayBufMsg;        /*voltage display*/
struct  TEMPR_FAULT_DISPLAY TemprFaultDisplayMsg;

/*网络通讯socket定义*/
int sFd;				              /* Socket file descriptor */
struct sockaddr_in serverSockAddr;    /* Address of server */
int sockAddrSize = sizeof (struct sockaddr_in);

int sFd1;
struct sockaddr_in serverSockAddr1;

int sFd2;
struct sockaddr_in serverSockAddr2;

/*系统消息机制定义*/
MSG_Q_ID msgHighRate, msgVoltage, msgFault;
int rxTaskID_HighRate, rxTaskID_Voltage, rxTaskID_Fault;

#define MAX_MESSAGES 100

int NetWorkInit(void);
void task_Msg_init(void);

void taskHighRateSend(void);
void taskVoltageSend(void);
void taskFaultSend(void);
extern short adData1[16];
extern short datemp;
extern int intCounter2,intCounter1,counter;
/********************************************************************************/
/*Name		:SubMod_Data_DisplayUDP_Init
*Description:UDP数据显示函数初始化
*Input		:无		
*Output		:无
*Return		:无
*History	:2016,by cdd
*/
int SubMod_Data_DisplayUDP_Init(void)
{
	task_Msg_init();

	return NetWorkInit();
}
/********************************************************************************/
/*Name		:NetWorkInit
*Description:UDP 协议初始化
*Input		:无		
*Output		:无
*Return		:无
*History	:2016,by xufei
*/
int NetWorkInit(void)
{
	/* Create socket */
	if ((sFd = socket (AF_INET, SOCK_DGRAM, 0)) == ERROR)
	{
		return (ERROR);
	}

	/* Bind not required - port number will be dynamic */
	/* Build server socket address */
	bzero ((char *)&serverSockAddr, sockAddrSize);

	serverSockAddr.sin_family      = AF_INET;
	serverSockAddr.sin_port        = htons (RECEIVE_PC_PORT);
	serverSockAddr.sin_addr.s_addr = inet_addr (RECEIVE_PC_IP);
	
	return (OK);
}
/********************************************************************************/
/*Name		:task_Msg_init
*Description:消息初始化
*Input		:无		
*Output		:无
*Return		:无
*History	:2016,by xufei
*/
void task_Msg_init(void)
{
	rxTaskID_HighRate = taskSpawn("taskHighRateSend",150,VX_SPE_TASK|VX_FP_TASK,20000,(FUNCPTR)taskHighRateSend,0,0,0,0,0,0,0,0,0,0);
/*	rxTaskID_Voltage  = taskSpawn("taskVoltageSend", 150,0,20000,(FUNCPTR)taskVoltageSend ,0,0,0,0,0,0,0,0,0,0);
	rxTaskID_Fault    = taskSpawn("taskHighRateSend",150,0,20000,(FUNCPTR)taskFaultSend   ,0,0,0,0,0,0,0,0,0,0);*/

	msgHighRate = msgQCreate(MAX_MESSAGES ,sizeof(struct HIGH_RATE_DISPLAY_SAVE) ,MSG_Q_FIFO );
/*	msgVoltage  = msgQCreate(MAX_MESSAGES ,sizeof(struct MODU_VOLTAGE_DISPLAY)   ,MSG_Q_FIFO );
	msgFault    = msgQCreate(MAX_MESSAGES ,sizeof(struct TEMPR_FAULT_DISPLAY)    ,MSG_Q_FIFO );*/
}
/********************************************************************************/
/*Name		:SubMod_HightRate_Data_DisplayUDP_Send
*Description:高速数据发送执行函数
*Input		:无		
*Output		:无
*Return		:无
*History	:2016,by xufei
*/
int SubMod_HightRate_Data_DisplayUDP_Send(void)
{
	static int BufCountA = 0, BufCountB = 0;

	/* Send data to HighRate Buffer */
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen1[0]);
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen1[1]);
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen1[2]);
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen1[3]);
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen2[0]); 
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen2[1]);
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen2[2]);
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen2[3]); 
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen3[0]);
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen3[1]);
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen3[2]);
	SendHighRateDisplaySaveBufUDP[BufCountA++] = (HighRateDisplaySaveBuf.Screen3[3]);

	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen4[0]);
	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen4[1]);
	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen4[2]);
	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen4[3]);
	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen5[0]);
	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen5[1]);
	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen5[2]);
	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen5[3]);
	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen6[0]);
	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen6[1]);
	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen6[2]);
	SendHighRateDisplaySaveBufUDP[240+BufCountB++] = (HighRateDisplaySaveBuf.Screen6[3]);


	if (BufCountA == 240)
	{	
		BufCountA = 0;
		BufCountB = 0;
		if (sendto (sFd, (caddr_t)SendHighRateDisplaySaveBufUDP, 960, 0, (struct sockaddr  *) &serverSockAddr,sockAddrSize) == ERROR)
		{
			close (sFd);
			return (ERROR);
		}
	}
	return (OK);
}
/********************************************************************************/
/*Name		:taskHighRateSend
*Description:高速数据发送任务
*Input		:msgHighRate，&HighRateDisplaySaveBuf，sizeof(struct HIGH_RATE_DISPLAY_SAVE，WAIT_FOREVER
*Output		:无
*Return		:无
*History	:2016,by xufei
*/

void taskHighRateSend(void)
{
	FOREVER
	{
		if(msgQReceive(msgHighRate , &HighRateDisplaySaveBuf.Screen1[0], sizeof(struct HIGH_RATE_DISPLAY_SAVE) , WAIT_FOREVER) == ERROR)
		{
			printf("msgQReceive in task taskHighRateSend failed. \n");
		}
		else
		{
			SubMod_HightRate_Data_DisplayUDP_Send();
		}
	}
}
/********************************************************************************/
/*Name		:sendMsgHighRate
*Description:为高速数据发送用消息传递数据
*Input		:msgHighRate，&HighRateDisplaySaveBuf，sizeof(struct HIGH_RATE_DISPLAY_SAVE，WAIT_FOREVER
*Output		:无
*Return		:无
*History	:2016,by xufei
*/
void sendMsgHighRate(void)
{
	if(msgHighRate!=0 && msgHighRate!=ERROR)
	{
		if(msgQSend(msgHighRate , &HighRateDisplaySaveBufMsg.Screen1[0] , sizeof(struct HIGH_RATE_DISPLAY_SAVE), WAIT_FOREVER , MSG_PRI_NORMAL) == ERROR)
			logMsg("msgQ send in task 2 failed \n",0,0,0,0,0,0) ;
	}
}
/********************************************************************************/
/*Name		:SubMod_Data_DisplayUDP_Close
*Description:关闭UDP协议
*Input		:msgHighRate，&HighRateDisplaySaveBuf，sizeof(struct HIGH_RATE_DISPLAY_SAVE，WAIT_FOREVER
*Output		:无
*Return		:无
*History	:2016,by xufei
*/

void SubMod_Data_DisplayUDP_Close(void)
{
	int status; 
	status = taskDelete(rxTaskID_HighRate);
	msgQDelete(msgHighRate);
	close(sFd); 
}
/********************************************************************************/
/*Name		:SwapWord
*Description：16位数据内高低字节垫高
*Input		:Data
*Output		:无
*Return		:无
*History	:2016,by xufei
*/

UINT16 SwapWord(UINT16 Data)
{
	return((Data>>8)|(Data<<8));
}

/********************************************************************************/
/*Name		:taskSendHighRateData
*Description：高速数据发送的数据采集函数
*Input		:6个屏幕，每个屏幕4个通道，共24个通道
*Output		:无
*Return		:无
*History	:2016,by xufei
*/

void taskSendHighRateData(void)
{


	static float theta = 0;
	static int dataSend=0;
	float ISR_Timer = 1.0/8000.0;

	/*theta += 10.0*6.28 * ISR_Timer;*/
	theta += 50.0*6.283185 * ISR_Timer;
        while(theta>6.283185) theta=theta-6.283185;
	dataSend = 100 * sin(theta);
//	dataSend++;
//	if(dataSend>10000)dataSend=0;

	HighRateDisplaySaveBufMsg.Screen1[0] =  dataSend;//PWMdata_REC1.VFGama*1000;//PWMdata_INV1.IntFlag*10;
	HighRateDisplaySaveBufMsg.Screen1[1] =  dataSend;//PWMdata_REC1.Reg_UpDown*10;//IntFlagTest*10;
	HighRateDisplaySaveBufMsg.Screen1[2] =  dataSend;//SyncFlagTest*10;
	HighRateDisplaySaveBufMsg.Screen1[3] =  dataSend;//interrupt_index*10	;
	
	HighRateDisplaySaveBufMsg.Screen2[0] = 	dataSend;//PWMdata_REC1. ACQ_ZRO*10; 
	HighRateDisplaySaveBufMsg.Screen2[1] = 	dataSend;//PWMdata_REC1. ACQ_CAU*10;
	HighRateDisplaySaveBufMsg.Screen2[2] =  dataSend;//PWMdata_REC1.ACQ_PRD*10; 
	HighRateDisplaySaveBufMsg.Screen2[3] = 	dataSend;// PWMdata_REC1.ACQ_CAD*10;	

	HighRateDisplaySaveBufMsg.Screen3[0] =  dataSend;//PWMdata_INV1.Kv*100;
	HighRateDisplaySaveBufMsg.Screen3[1] =  dataSend;//PWMdata_INV1.VFGama*10;
	HighRateDisplaySaveBufMsg.Screen3[2] =  dataSend;//PWMdata_INV1.vvvf1*10;
	HighRateDisplaySaveBufMsg.Screen3[3] = 	dataSend;// faultCode.inv1_DeadZoneErr*10;
	
	
	HighRateDisplaySaveBufMsg.Screen4[0] =  dataSend;//txRecSrioData1.CMPAU2*10;//rxMcuData.invGama1*10;
	HighRateDisplaySaveBufMsg.Screen4[1] =  dataSend;//txRecSrioData1.CMPAD2*10;//(rxMcuData.livecnt & 0x000f)*10;
	HighRateDisplaySaveBufMsg.Screen4[2] = 	dataSend;// rxMcuData.invGama2*10;
	HighRateDisplaySaveBufMsg.Screen4[3] = 	dataSend;// PWMdata_INV1.vvvf1IncreFlag*10;	

	HighRateDisplaySaveBufMsg.Screen5[0] =  dataSend;
	HighRateDisplaySaveBufMsg.Screen5[1] =  dataSend;//SVPWM-> SHEPWM change flag
	HighRateDisplaySaveBufMsg.Screen5[2] =  dataSend;
	HighRateDisplaySaveBufMsg.Screen5[3] = 	dataSend;
	
	HighRateDisplaySaveBufMsg.Screen6[0] =  dataSend;
	HighRateDisplaySaveBufMsg.Screen6[1] =  counter*10;// faultCode.inv1_MinPulseErr*10;
	HighRateDisplaySaveBufMsg.Screen6[2] =  intCounter2*10; //SHEPWM type flag
	HighRateDisplaySaveBufMsg.Screen6[3] = 	intCounter1*10;// invIu1*10;//CMPAD6Test*10;
	sendMsgHighRate();
}



