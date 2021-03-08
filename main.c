/*  
* target:ast7700  	 
* filename: main.c 
* Copyright 2018-2021 IEE-CAS, Inc.
* description: ������,Interrupt occurs every 7200Hz, SVM applied 
* function: running on the half simulation system
* debug:
* modification history��
* 2019,2,27 add upd communication with rtlab, which is realized in udp_ast7700TortlabCom
* 2021,3,8 add upd communication with keliang
*/
/*******************************************/
 
#include "vxWorks.h"
#include "taskLib.h"
#include "stdio.h"
#include "logLib.h"
#include "intLib.h"
#include "iv.h"  
#include "sysLib.h"
#include "vme.h"
#include "semLib.h"
#include "math.h"  
#include "ioLib.h"
#include "wdLib.h"

 
#include "ast7700Srio.h" 
#include "subMod_DataDisplayUDP.h"
#include "main_variable.h"
#include "udp_rtlabCom.h"
#define UDP_RTLAB
/**************define global variables**********************************************************/
#define DAVmeBaseAdrs 0Xaaaa80
char * DALocalBaseAdrs; 
int    auxClkIntSemID;
int	   auxClkIntTaskId;
int	   intCounter2=0;
int	   intCounter1=0;
int    counter=0;
int    writecounter=0;
struct TX_7600_STRUCT tx_7600_data;
struct RX_7600_STRUCT *rx_7600_data_pointer;
struct RX_7600_STRUCT rx_7600_data;
struct RTLAB_SEND_DATA *RTLAB_dataout_p;
STATUS udp_ast7700TortlabCom();

short  aaaa=0;
int  status11=0;
UINT32 time1=0,time2=0,time3=0,cpufreq=0;
UINT32 timetest;

/**********************���ļ����Ӻ�������**************************************************/
void   auxClkPoll(void);
void   auxClkIntTask(void);
/************************************************************************/
int main(void)		
{	
	int 	status;
    int 	rate=4000;
    int tSem,t7700UDP,tMcuWrite,tTimer,tMcuaWatchDg;
    char * ip;
	memset(&rx_7600_data,0,sizeof(struct RX_7600_STRUCT));
	memset(&tx_7600_data,0,sizeof(struct TX_7600_STRUCT));

#ifdef UDP_RTLAB	
/*  add udp commu with rtlab code down here */
	ip=(char *)malloc(32);
	getifaddrs("motetsec0",&ip);
//	gethostbyname(ip,32);
//	gethostname(ip,32);
	logMsg("\n ast7700_UDP_A =%s \n",ip,0,0,0,0,0);
	/*add ip 192.168.10.89 */
    ipAttach(1,"motetsec");   /* second net */
    	taskDelay(1);
    	ifconfig("motetsec1 192.168.10.10 netmask 255.255.255.0 down");
    	taskDelay(1);
    	ifconfig("motetsec1 up");
    	taskDelay(1);

    	ast7700_UDP_A="192.168.10.10";
    	logMsg("\n ast7700_UDP_A =%s \n",ast7700_UDP_A,0,0,0,0,0);

    	RTLAB_UDP_A="192.168.10.101";
    	logMsg("\n RTLAB_UDP_A =%s \n",RTLAB_UDP_A,0,0,0,0,0);	
    	
    	/* �����������ע�����ȼ� */
    	/*�����ź���������  */
    tSem=taskSpawn("taskSem",109,0,2000,(FUNCPTR)taskSem,0,0,0,0,0,0,0,0,0,0); 
    	/*ast7700  A���ڵ�����*/
    t7700UDP=taskSpawn("udp_ast7700TortlabCom",110,VX_FP_TASK,2000,(FUNCPTR)udp_ast7700TortlabCom,0,0,0,0,0,0,0,0,0,0);	

    /*ast7700  ��������״̬��������*/	
    tMcuWrite=taskSpawn("taskMcuWrite",110,VX_FP_TASK,2000,(FUNCPTR)taskMcuWrite,0,0,0,0,0,0,0,0,0,0);
#endif
	
/*  add udp commu with rtlab code up here*/	
	
//	sysClkRateSet(5000);/*1ms/tick*/
//	astLocalbusFpgaInit();		
	ast7700SrioInit();				/*CPU ast7700�ϵ�Powerpc��ʼSRIO���ܳ�ʼ��*/
	// 7700 srio ��init���´򿪣���ΪvxWorks��appinitû�з��䷢������
	sysAuxClkRateSet (rate);	
	printf("rate=%d\n",sysAuxClkRateGet());
	sysAuxClkConnect ((FUNCPTR)auxClkPoll,0);
	sysAuxClkEnable();
	auxClkIntSemID= semBCreate(SEM_Q_PRIORITY,SEM_EMPTY);/*�����ж��ź���*/
	auxClkIntTaskId=taskSpawn("auxClkIntTask",130,VX_SPE_TASK|VX_FP_TASK,20000,(FUNCPTR)auxClkIntTask,0,0,0,0,0,0,0,0,0,0);	
 	 
 	 
  	status = SubMod_Data_DisplayUDP_Init();
 	cpufreq = sysTimestampFreq();
 	    sysTimestampDisable();		     
 	    sysTimestampEnable();	
   
 	 
    
}

void taskSem()	/*�������������ź���*/
{
	if((semMcuaWrite=semCCreate(SEM_Q_FIFO,0))==0)
		perror("mcu: create semaphore failed\n");
	if((semMcuaWd=semCCreate(SEM_Q_FIFO,0))==0)
		perror("mcuA:create watchdog semaphore failed\n");

	FOREVER{
		taskDelay(5);
	}	
}
/*********************7700�ϱ���FPGA��ʱ���жϵ��ú���*******************************************************************/
/*Name		:AuxClkPoll
*Description:����ʱ�Ӷ�ʱ���жϵ��ú���,�ͷ��ź���������һֱ�ȴ���clkinttask����
*Input		:��
*Output		:��
*Return		:OK or ERROR
*History	:2018-07-16
*History	rate=4000 , 4k frequency
*/
void auxClkPoll(void)
{
	counter++;
	intCounter2++;
	semGive(auxClkIntSemID);
#ifdef UDP_RTLAB	
	if(intCounter2==10)
	{
	semGive(semMcuaWrite); // 4k period frequency, 7700 udp send data to rtlab 
	intCounter2=0;
	}
#endif	
	 
}
/********************��ʱ���жϴ�������********************************************************************/
/*Name		:auxClkIntTask
*Description:����ʱ�Ӷ�ʱ���жϴ�������,�ȴ��ź���
*Input		:��
*Output		:��
*Return		:OK or ERROR
*History	:2018-07-16,modified by wxx
*/
void auxClkIntTask(void)/*�����ݳ���*/
{  
  int i,j;
  unsigned int  tickCnt=0;	/*���ڼ�����*/
  int status;
 
  FOREVER		/*ѭ��ִ��*/
  {
	  status11= semTake(auxClkIntSemID,WAIT_FOREVER);/*�ȴ��ж��ź���*/
	  if(status11==ERROR)
		logMsg("aux clock timer interrupt failed\n",0,0,0,0,0,0);
	  else
	  {	  
		  
	//	  logMsg("auxclk timer work! \n",0,0,0,0,0,0);
		  intCounter1++;	   
	//	  if(intCounter2==7200)
	//	  {
	//		  logMsg("auxclk timer work! \n",0,0,0,0,0,0);
	//	  }
 		  wait_7600_SrioInitOk();
		  if(ast7600SrioInitOk==1)
		  {
			  read_7600_SrioData();
			  write_7600_SrioData(); 
		  } 
 		  taskSendHighRateData();
 
	  }
  }/*end forever*/
}
/*��ʱ���жϴ����������*/
 
/********************ֹͣ��ɾ��������********************************************************************/
/*Name		:stop
*Description:ֹͣ����ʱ�Ӷ�ʱ���жϴ�������,ֹͣUDP�����������񣬽�ֹ����ʱ���жϹ���
*Input		:��
*Output		:��
*Return		:OK or ERROR
*History	:2018-07-16,modified by wxx
*/
void stop(void)
{
	int status;
 	SubMod_Data_DisplayUDP_Close();
	sysAuxClkDisable();
	taskDelete(auxClkIntTaskId);
	
}
