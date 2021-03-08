/*  
* target:ast7700  	 
* filename: main.c 
* Copyright 2018-2021 IEE-CAS, Inc.
* description: 主程序,Interrupt occurs every 7200Hz, SVM applied 
* function: running on the half simulation system
* debug:
* modification history：
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

/**********************本文件下子函数声明**************************************************/
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
    	
    	/* 发起各项任务，注意优先级 */
    	/*创建信号量的任务  */
    tSem=taskSpawn("taskSem",109,0,2000,(FUNCPTR)taskSem,0,0,0,0,0,0,0,0,0,0); 
    	/*ast7700  A网口的任务*/
    t7700UDP=taskSpawn("udp_ast7700TortlabCom",110,VX_FP_TASK,2000,(FUNCPTR)udp_ast7700TortlabCom,0,0,0,0,0,0,0,0,0,0);	

    /*ast7700  发送周期状态报文任务*/	
    tMcuWrite=taskSpawn("taskMcuWrite",110,VX_FP_TASK,2000,(FUNCPTR)taskMcuWrite,0,0,0,0,0,0,0,0,0,0);
#endif
	
/*  add udp commu with rtlab code up here*/	
	
//	sysClkRateSet(5000);/*1ms/tick*/
//	astLocalbusFpgaInit();		
	ast7700SrioInit();				/*CPU ast7700上的Powerpc开始SRIO功能初始化*/
	// 7700 srio 的init重新打开，因为vxWorks的appinit没有分配发生区间
	sysAuxClkRateSet (rate);	
	printf("rate=%d\n",sysAuxClkRateGet());
	sysAuxClkConnect ((FUNCPTR)auxClkPoll,0);
	sysAuxClkEnable();
	auxClkIntSemID= semBCreate(SEM_Q_PRIORITY,SEM_EMPTY);/*创建中断信号量*/
	auxClkIntTaskId=taskSpawn("auxClkIntTask",130,VX_SPE_TASK|VX_FP_TASK,20000,(FUNCPTR)auxClkIntTask,0,0,0,0,0,0,0,0,0,0);	
 	 
 	 
  	status = SubMod_Data_DisplayUDP_Init();
 	cpufreq = sysTimestampFreq();
 	    sysTimestampDisable();		     
 	    sysTimestampEnable();	
   
 	 
    
}

void taskSem()	/*创建各个所需信号量*/
{
	if((semMcuaWrite=semCCreate(SEM_Q_FIFO,0))==0)
		perror("mcu: create semaphore failed\n");
	if((semMcuaWd=semCCreate(SEM_Q_FIFO,0))==0)
		perror("mcuA:create watchdog semaphore failed\n");

	FOREVER{
		taskDelay(5);
	}	
}
/*********************7700上本地FPGA定时器中断调用函数*******************************************************************/
/*Name		:AuxClkPoll
*Description:辅助时钟定时器中断调用函数,释放信号量，触发一直等待的clkinttask任务
*Input		:无
*Output		:无
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
/********************定时器中断处理任务********************************************************************/
/*Name		:auxClkIntTask
*Description:辅助时钟定时器中断处理任务,等待信号量
*Input		:无
*Output		:无
*Return		:OK or ERROR
*History	:2018-07-16,modified by wxx
*/
void auxClkIntTask(void)/*收数据程序*/
{  
  int i,j;
  unsigned int  tickCnt=0;	/*周期计数器*/
  int status;
 
  FOREVER		/*循环执行*/
  {
	  status11= semTake(auxClkIntSemID,WAIT_FOREVER);/*等待中断信号量*/
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
/*定时器中断处理任务结束*/
 
/********************停止和删除任务函数********************************************************************/
/*Name		:stop
*Description:停止辅助时钟定时器中断处理任务,停止UDP发送数据任务，禁止辅助时钟中断功能
*Input		:无
*Output		:无
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
