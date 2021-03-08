#include "udp_rtlabCom.h"

double testPoint;
UINT64 testPoint_tmp,testPoint_tmp1,testPoint_tmp2;
int RS_switchINcmd,RS_switch_DT_BTcmd,RS_switchOUTcmd;
int x,y;
test * preplyBuf;
struct sockaddr_in server,client,middle; /* 接受地址 for taskMcuA */
test	replyBuf; /*  remove to the begin */
float timer_realPeriod=0,work_time=0;

STATUS udp_ast7700TortlabCom()
{  
   
   int sockClient;   /* 定义一个套接字变流 */

//test	replyBuf; /*  remove to the begin lhc */

    unsigned int * pData;
	struct dccStatus * pdccSts;
	struct lineData * plineData;
	struct lineData1 * plineData1;
	struct lineData2 * plineData2;
	struct lineData3 * plineData3;
	struct lineData4 * plineData4;
	struct maxSpeedLine * pmaxSpeedLine;
	struct stopPosRunReq * pstopPosRunReq;
	struct stopPosRunStep * pstopPosRunStep;
	struct start * pstart;
	struct stop * pstop;
	struct run * prun;
	struct lineDataDel *plineDataDel;	
        int nRecv,nSend;
	int cmd;
	int i=0;
        int k,countlinedata,countmaxspeed;
	char status;
	unsigned char * p;
	unsigned short rfmOff;
        int sin_size;
	char * msg;
        char * msgack;
        countlinedata=0;countmaxspeed=0;
#if 0        
        int dataSend;
        static float thetaTmp=0;
        float ISR_Timer = 1.0/10.0;
#endif      

init();/* structure init before program start, this process need
to be modified as the communication rule */

	sockMcuA=socket(AF_INET,SOCK_DGRAM,0);
sockClient=socket(AF_INET,SOCK_DGRAM,0);
	if(sockMcuA==ERROR)
		{
		perror("socket not opened");
		return (ERROR);
		}
logMsg("create sockMcuA OK **\n ",0,0,0,0,0,0);
	
/* 初始化sockaddr_in结构并装载在接受地址里*/
bzero ((char *) &server,sizeof(struct sockaddr_in));
server.sin_family=AF_INET;
server.sin_len=sizeof(struct sockaddr_in);
server.sin_port=htons(PORTA);
server.sin_addr.s_addr = htonl(INADDR_ANY);


	bzero((char *) &middle,SA_LEN);
	middle.sin_family=AF_INET;
	middle.sin_len=SA_LEN;
	middle.sin_port=htons(PORTA);
	middle.sin_addr.s_addr=inet_addr(RTLAB_UDP_A);


	bzero((char *) &client,SA_LEN);
	client.sin_family=AF_INET;
	client.sin_len=SA_LEN;
	client.sin_port=htons(PORTB);
	client.sin_addr.s_addr=inet_addr(RTLAB_UDP_A);  /*  inet_addr(RTLAB_UDP_A);  */

if (bind(sockMcuA,(struct sockaddr *)&server,sizeof(struct sockaddr_in))==ERROR)
          {
		perror("bind error");
		return (ERROR);
		}     
logMsg(" bind sockMcuA OK**********\n ",0,0,0,0,0,0);


/* if(nSend=sendto(sockMcuA,"Welcome",strlen("welcome"),0,(struct sockaddr *)&client,sin_size)==ERROR)
{
  perror("sendto failed");
  return(ERROR);
 }
else
{
printf(" %d bytes of message sent\n",nSend);
logMsg(" already send message to client\n ",0,0,0,0,0,0);

} */


/* receive the message from client loop*/

while(TRUE)
{

sin_size =sizeof(struct sockaddr_in);
sysTimestampDisable();		     
sysTimestampEnable();
time1 = sysTimestamp();
nRecv=recvfrom(sockMcuA,(char *)&replyBuf,MSG_SIZE,0,(struct sockaddr *)&middle,&sin_size);
time3 = sysTimestamp();

work_time = (time3 - time1) / (cpufreq * 1.0 / 1000000);
timetest=work_time;
 
//if(work_time>22000)
//	logMsg("PRW UDP recieve delay %d us\n",timetest,0,0,0,0,0);

if(nRecv<0)
{
         	perror("recvform error");
		return (ERROR);
}
else
{
	x=x+1;
	RTLAB_dataout_p=(struct RTLAB_SEND_DATA *)&replyBuf;
	
	//here below, RTLAB_dataout_p->data[0]--[2], reply rtlab switch status
	// so SWAP64 to make it normal,which is used by ast7700srio.c reply code for sending 
	// data to ast7600
	
	for(i=0;i<4;i++)
	{
	testPoint_tmp1=*(UINT64 *)&(RTLAB_dataout_p->data[0+i]);
	testPoint_tmp1=SWAP64(testPoint_tmp1);
	RTLAB_dataout_p->data[0+i]=*(double *)&testPoint_tmp1;	
	
	
//			printf("RTLAB_dataout_p->data[%d]= %lf \n  ",i,RTLAB_dataout_p->data[0+i]);
	}

	RS_switchINcmd  = RTLAB_dataout_p->data[0];
    RS_switch_DT_BTcmd =RTLAB_dataout_p->data[1];
    RS_switchOUTcmd = RTLAB_dataout_p->data[2];

/*
	if(x==1000)
	{
		logMsg("(1000)RTLAB_dataout_p->data[0]=%d\n",RTLAB_dataout_p->data[0],0,0,0,0,0);
		logMsg("(1000)RTLAB_dataout_p->data[1]=%d\n",RTLAB_dataout_p->data[1],0,0,0,0,0);
		logMsg("(1000)RTLAB_dataout_p->data[2]=%d\n",RTLAB_dataout_p->data[2],0,0,0,0,0);
	}
	
	if(x==2000)
	{	printf("(2000)RTLAB_dataout_p->data[0]= %lf \n  ",RTLAB_dataout_p->data[0]);
		printf("(2000)RTLAB_dataout_p->data[1]= %lf \n ",RTLAB_dataout_p->data[1]);
		printf("(2000)RTLAB_dataout_p->data[2]= %lf\n  ",RTLAB_dataout_p->data[2]);
	}
	if(x==3000)
	{
		logMsg("(3000)RS_switchINcmd=%d\n",RS_switchINcmd,0,0,0,0,0);
		logMsg("(3000)RS_switch_DT_BTcmd=%d\n",RS_switch_DT_BTcmd,0,0,0,0,0);
		logMsg("(3000)RS_switchOUTcmd=%d\n",RS_switchOUTcmd,0,0,0,0,0);
	}
	 if(x==4000)
	 {
		
		printf("(4000)RS_switchINcmd= %lf \n  ",RS_switchINcmd);
		printf("(4000)RS_switch_DT_BTcmd= %lf \n ",RS_switch_DT_BTcmd);
		printf("(4000)RS_switchOUTcmd= %lf\n  ",RS_switchOUTcmd);
	 }
	 if(x==5000)
	 {
		printf("(5000)RS_switchINcmd= %d \n  ",RS_switchINcmd);
		printf("(5000)RS_switch_DT_BTcmd= %d \n ",RS_switch_DT_BTcmd);
		printf("(5000)RS_switchOUTcmd= %d\n  ",RS_switchOUTcmd);
	
		x=0;
	}*/

/*	if (x==1000)
	{		
			printf("\n");
			for(i=0;i<nRecv;i++)
			{
			if (i%8==0)
				printf("\n");
			printf("%x   ",replyBuf.a[i]);
			}
//			testPoint=(double)(RTLAB_dataout_p->data[0]);
//			testPoint=*((double *)&(replyBuf.a[2]));
#ifdef doubleDATA			
			for(i=0;i<nRecv/8;i++)
			{
			testPoint_tmp1=*(UINT64 *)&(RTLAB_dataout_p->data[0+i]);
			testPoint_tmp1=SWAP64(testPoint_tmp1);
			RTLAB_dataout_p->data[0+i]=*(double *)&testPoint_tmp1;	
			
			printf("RTLAB_dataout_p->data[%d]= %lf \n  ",i,RTLAB_dataout_p->data[0+i]);
			}

//			printf("RTLAB_dataout_p->data[0]= %lf \n  ",RTLAB_dataout_p->data[0]);
//			printf("RTLAB_dataout_p->data[1]= %lf \n ",RTLAB_dataout_p->data[1]);
//			printf("RTLAB_dataout_p->data[2]= %lf\n  ",RTLAB_dataout_p->data[2]);
//			printf("RTLAB_dataout_p->data[3]= %lf  \n ",RTLAB_dataout_p->data[3]);
//			printf("RTLAB_dataout_p->data[4]= %lf  \n ",RTLAB_dataout_p->data[4]);
#endif			
			
#ifdef intDATA			
			printf("RTLAB_dataout_p->data[0]= %x   ",SWAP16(RTLAB_dataout_p->data[0]));
			printf("RTLAB_dataout_p->data[1]= %x   ",SWAP16(RTLAB_dataout_p->data[1]));
			printf("RTLAB_dataout_p->data[2]= %x   ",SWAP16(RTLAB_dataout_p->data[2]));
#endif			
	}*/	
	
#if 0
			printf("\n");
printf("McuA get a message from %s\n",inet_ntoa(middle.sin_addr));
T_test();
printf("McuA: nRecv= %d\n",nRecv);/*打印收到字节数*/


/*8个字节一行，打印报文前n个字节*/
		com_port=con_A;
if (x==1000)
{	
		for(i=0;i<nRecv;i++)
		{
		if (i%8==0)
			printf("\n");
		printf("%x   ",replyBuf.a[i]);
		}
}		
#endif
		
	} /*end if*/
#if 0
thetaTmp+= 50.0*6.28 * ISR_Timer;

//        while(theta>6.283185) theta=theta-6.283185;
dataSend=100*sin(thetaTmp);
#endif
//RTLAB_datain.dev_id=0x100;
//RTLAB_datain.msg_id=x;

#ifdef intDATA
RTLAB_datain.dev_id=SWAP(1);   
RTLAB_datain.msg_id=SWAP16(x);
RTLAB_datain.msg_len=SWAP(20);// 20 for int data length  40 for double data length
//	RTLAB_datain.dev_id=replyBuf.a[1]<<8|(replyBuf.a[0]);
//	RTLAB_datain.msg_id=(replyBuf.a[5]<<24) | (replyBuf.a[4]<<16) | (replyBuf.a[3]<<8)|(replyBuf.a[2]);
//	RTLAB_datain.msg_len=0x2800;
	RTLAB_datain.data[0]=SWAP16(1);
	RTLAB_datain.data[1]=SWAP16(2);
	RTLAB_datain.data[2]=SWAP16(x);
#endif

#ifdef doubleDATA
RTLAB_datain.dev_id=SWAP(1);   
RTLAB_datain.msg_id=SWAP16(x);
RTLAB_datain.msg_len=SWAP(48); //  48 for 6 double data
//	RTLAB_datain.dev_id=replyBuf.a[1]<<8|(replyBuf.a[0]);
//	RTLAB_datain.msg_id=(replyBuf.a[5]<<24) | (replyBuf.a[4]<<16) | (replyBuf.a[3]<<8)|(replyBuf.a[2]);
//	RTLAB_datain.msg_len=0x2800;
//	RTLAB_datain.data[0]=SWAP16(1);
//	RTLAB_datain.data[1]=SWAP16(2);
//	RTLAB_datain.data[2]=SWAP16(x);
#endif
//	RTLAB_datain.dev_id=1;
//	RTLAB_datain.msg_id=x;
//	RTLAB_datain.msg_len=nRecv;
//	RTLAB_datain.data[0]=x;
#if 0
	if(nSend=sendto(sockMcuA,(char *)&RTLAB_datain,nRecv,0,(struct sockaddr *)&client,SA_LEN)==ERROR)
//replyBuf
//if(nSend=sendto(sockMcuA,(char *)&mcuSts,nRecv,0,(struct sockaddr *)&client,SA_LEN)==ERROR)
			   	       perror("mcuA:RTLAB_datain send fail\n");
//	printf("sendto ok *********");

	
	preplyBuf=(struct test*)&RTLAB_datain;
	if (x==1000)
	{	
			for(i=0;i<nRecv;i++)
			{
			if (i%8==0)
				printf("\n");
			printf("%x   ",preplyBuf->a[i]);
			}
	}
	
#endif
	

} /*end while*/
close(sockMcuA);

}
/**************************************************/ 
void taskMcuWrite()/*MCU  发送周期状态报文任务*/
{	
	for(;;)
	{
	if(semTake(semMcuaWrite,WAIT_FOREVER)==-1)	/*获取mcuA写的信号量，触发tx_mcuSts任务，MCU发送周期状态报文*/
		perror("error wait for semMcuaWrite\n");
	tx_mcuSts();
	}
}

/*MCU发送周期状态报文*/
void tx_mcuSts()
{
/*trans lifecycle packet*/
unsigned char * p;
int i,nSend;

int dataSend;
static float thetaTmp=0;
float ISR_Timer = 1.0/4000.0;





//	if(sockMcuAConFlag==1)
#if 0
	if(sockMcuAConFlag==1||sockMcuBConFlag==1)	/*根据mcuA或B口连接标志，mcu向A或B口连接套接字写周期状态报文*/
#endif
	{

	}

		y++;
	thetaTmp+= 50.0*6.28 * ISR_Timer;
	
	//        while(theta>6.283185) theta=theta-6.283185;
	dataSend=100*sin(thetaTmp);
	
	if (rx_7600_data_pointer->short_variable[6]==1)
	{
		logMsg(" rx_7600_data[0]: %x\n ",rx_7600_data_pointer->short_variable[0],0,0,0,0,0);
		logMsg(" rx_7600_data[1]: %x\n ",rx_7600_data_pointer->short_variable[1],0,0,0,0,0);
		logMsg(" rx_7600_data[2]: %x\n ",rx_7600_data_pointer->short_variable[2],0,0,0,0,0);
		logMsg(" rx_7600_data[3]: %x\n ",rx_7600_data_pointer->short_variable[3],0,0,0,0,0);
		logMsg(" rx_7600_data[4]: %x\n ",rx_7600_data_pointer->short_variable[4],0,0,0,0,0);
		logMsg(" rx_7600_data[5]: %x\n ",rx_7600_data_pointer->short_variable[5],0,0,0,0,0);
		logMsg(" rx_7600_data[6]: %x\n ",rx_7600_data_pointer->short_variable[6],0,0,0,0,0);
		logMsg(" rx_7600_data[7]: %x\n ",rx_7600_data_pointer->short_variable[7],0,0,0,0,0);
		logMsg(" rx_7600_data[8]: %x\n ",rx_7600_data_pointer->short_variable[8],0,0,0,0,0);
		logMsg(" rx_7600_data[9]: %x\n ",rx_7600_data_pointer->short_variable[9],0,0,0,0,0);
		logMsg(" rx_7600_data[10]: %x\n ",rx_7600_data_pointer->short_variable[10],0,0,0,0,0);
		logMsg(" rx_7600_data[11]: %x\n ",rx_7600_data_pointer->short_variable[11],0,0,0,0,0);
		
	}

#ifdef intDATA	
	/*add switch code here*/
	if(rx_7600_data_pointer->short_variable[1]==0x1122)
	{
		/*lhc for switch test*/
		RTLAB_datain.data[0]=SWAP16(1);
	}
	else if(rx_7600_data_pointer->short_variable[1]==0x3344)
	{
		RTLAB_datain.data[0]=SWAP16(0);
	}
	
	if(rx_7600_data_pointer->short_variable[2]==0x1122)
	{
		/*lhc for switch test*/
		RTLAB_datain.data[1]=SWAP16(1);
	}
	else if(rx_7600_data_pointer->short_variable[2]==0x3344)
	{
		RTLAB_datain.data[1]=SWAP16(0);
	}
	
	if(rx_7600_data_pointer->short_variable[3]==0x1122)
	{
		/*lhc for switch test*/
		RTLAB_datain.data[2]=SWAP16(1);
	}
	else if(rx_7600_data_pointer->short_variable[3]==0x3344)
	{
		RTLAB_datain.data[2]=SWAP16(0);
	}
	
#endif
	
#ifdef doubleDATA	
	/*add switch code here*/
	if(rx_7600_data_pointer->short_variable[1]==0x1122)
	{
		/*lhc for switch test*/
		testPoint=1;
		testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);
//		testPoint_tmp2=SWAP64(1);
		RTLAB_datain.data[0]=*(double *)&testPoint_tmp2;
	}
	else if(rx_7600_data_pointer->short_variable[1]==0x3344)
	{
		testPoint=0;
		testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);
		//testPoint_tmp2=SWAP64(0);
		RTLAB_datain.data[0]=*(double *)&testPoint_tmp2;
	}
	
	if(rx_7600_data_pointer->short_variable[2]==0x1122)
	{
		/*lhc for switch test*/
		testPoint=1;
		testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);
		//testPoint_tmp2=SWAP64(1);
		RTLAB_datain.data[1]=*(double *)&testPoint_tmp2;
	}
	else if(rx_7600_data_pointer->short_variable[2]==0x3344)
	{
		testPoint=0;
		testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);
		//testPoint_tmp2=SWAP64(0);
		RTLAB_datain.data[1]=*(double *)&testPoint_tmp2;
	}
	
	if(rx_7600_data_pointer->short_variable[3]==0x1122)
	{
		/*lhc for switch test*/
		testPoint=1;
		testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);
		//testPoint_tmp2=SWAP64(1);
		RTLAB_datain.data[2]=*(double *)&testPoint_tmp2;
	}
	else if(rx_7600_data_pointer->short_variable[3]==0x3344)
	{
		testPoint=0;
		testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);
		//testPoint_tmp2=SWAP64(0);
		RTLAB_datain.data[2]=*(double *)&testPoint_tmp2;
		
		
	}
	
	if(rx_7600_data_pointer->short_variable[4]==0x1122)
	{
		/*lhc for switch test*/
		testPoint=1;
		testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);
		//testPoint_tmp2=SWAP64(1);
		RTLAB_datain.data[3]=*(double *)&testPoint_tmp2;
	}
	else if(rx_7600_data_pointer->short_variable[4]==0x3344)
	{
		testPoint=0;
		testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);
		//testPoint_tmp2=SWAP64(0);
		RTLAB_datain.data[3]=*(double *)&testPoint_tmp2;
			
	}	
	
	if(rx_7600_data_pointer->short_variable[5]!=0)
	{
		/*lhc for switch test*/
		testPoint=rx_7600_data_pointer->short_variable[5];
		testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);
		//testPoint_tmp2=SWAP64(1);
		RTLAB_datain.data[4]=*(double *)&testPoint_tmp2;
	}
	
#endif
//	dataSend++;
#ifdef intDATA	
			RTLAB_datain.dev_id=SWAP(1);   //  
			RTLAB_datain.msg_id=SWAP16(x);
			RTLAB_datain.msg_len=SWAP(20); //  20 for 5 int data
			//	RTLAB_datain.dev_id=replyBuf.a[1]<<8|(replyBuf.a[0]);
			//	RTLAB_datain.msg_id=(replyBuf.a[5]<<24) | (replyBuf.a[4]<<16) | (replyBuf.a[3]<<8)|(replyBuf.a[2]);
			//	RTLAB_datain.msg_len=0x2800;
		//		RTLAB_datain.data[0]=SWAP16(1);
				RTLAB_datain.data[4]=SWAP16(2);
		//		RTLAB_datain.data[2]=SWAP16(x);
				RTLAB_datain.data[3]=SWAP16((int)(thetaTmp));
		//		RTLAB_datain.data[1]=SWAP16(dataSend);
#endif
				
#ifdef doubleDATA	
			RTLAB_datain.dev_id=SWAP(1);   //  
			RTLAB_datain.msg_id=SWAP16(x);
			RTLAB_datain.msg_len=SWAP(512); //  48 for 6 double data
			//	RTLAB_datain.dev_id=replyBuf.a[1]<<8|(replyBuf.a[0]);
			//	RTLAB_datain.msg_id=(replyBuf.a[5]<<24) | (replyBuf.a[4]<<16) | (replyBuf.a[3]<<8)|(replyBuf.a[2]);
			//	RTLAB_datain.msg_len=0x2800;
//			testPoint=1.0;
//			testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);
//			RTLAB_datain.data[0]=*(double *)&testPoint_tmp2;
//			testPoint=2.0;
//			testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);
//			testPoint=223.8901;
//			testPoint_tmp2=SWAP64(*(UINT64 *)&testPoint);			
//			RTLAB_datain.data[2]=*(double *)&testPoint_tmp2;				
				//RTLAB_datain.data[0]=SWAP64(1);
				//RTLAB_datain.data[1]=SWAP64(0);
				//RTLAB_datain.data[2]=SWAP64(1);
//				testPoint_tmp2=SWAP64(*(UINT64 *)&thetaTmp);
//				RTLAB_datain.data[3]=*(double *)&testPoint_tmp2;
//				RTLAB_datain.data[4]=SWAP64(2);
//				testPoint_tmp2=SWAP64(*(UINT64 *)&x);
//				RTLAB_datain.data[5]=*(double *)&testPoint_tmp2;
//				RTLAB_datain.data[6]=SWAP64(0);
		//		RTLAB_datain.data[1]=SWAP16(dataSend);
#endif
				
				preplyBuf=(struct test*)&RTLAB_datain;
				if (y==3000)
				{	
						for(i=0;i<56;i++)  //28
						{
						if (i%8==0)
							printf("\n");
						printf("%x   ",preplyBuf->a[i]);
						}
				}				
			
			//	RTLAB_datain.dev_id=1;
			//	RTLAB_datain.msg_id=x;
			//	RTLAB_datain.msg_len=nRecv;
			//	RTLAB_datain.data[0]=x;

	if(nSend=sendto(sockMcuA,(char *)&RTLAB_datain,520,0,(struct sockaddr *)&client,SA_LEN)==ERROR)
			//replyBuf                             28  nRecv
			//if(nSend=sendto(sockMcuA,(char *)&mcuSts,nRecv,0,(struct sockaddr *)&client,SA_LEN)==ERROR)
					   perror("mcuA:RTLAB_datain fail\n");
//	if(sockMcuAConFlag==1)
	{
//	if(nSend=sendto(sockMcuA,(char *)&mcuSts,mcuSts_size,0,(struct sockaddr *)&client,SA_LEN)==ERROR)
//			   	       perror("mcuA:mcuSts fail\n");
	}
//	printf("sendto ok *********");
#if 0
	if(sockMcuBConFlag==1)
	{
	if(nSend=sendto(sockMcuB,(char *)&mcuSts,mcuSts_size,0,(struct sockaddr *)&client,sin_size)==ERROR)
			   	       perror("mcuA:mcuSts fail\n");
	}
#endif

}


void testdouble()
{
	int i;
	
	replyBuf.a[0]=0x3f;
	replyBuf.a[1]=0xf0;
	replyBuf.a[2]=0;
	replyBuf.a[3]=0;
	replyBuf.a[4]=0;
	replyBuf.a[5]=0;
	replyBuf.a[6]=0;
	replyBuf.a[7]=0;
	
	replyBuf.a[8]=0x3f;
	replyBuf.a[9]=0xf0;
	replyBuf.a[10]=0;
	replyBuf.a[11]=0;
	replyBuf.a[12]=0;
	replyBuf.a[13]=0;
	replyBuf.a[14]=0;
	replyBuf.a[15]=0;
	
	replyBuf.a[16]=0;
	replyBuf.a[17]=0;
	replyBuf.a[18]=0;
	replyBuf.a[19]=0;
	replyBuf.a[20]=0;
	replyBuf.a[21]=0;
	replyBuf.a[22]=0xf0;
	replyBuf.a[23]=0x3f;

	
	replyBuf.a[24]=0x40;
	replyBuf.a[25]=0x79;
	replyBuf.a[26]=0;
	replyBuf.a[27]=0;
	replyBuf.a[28]=0;
	replyBuf.a[29]=0;
	replyBuf.a[30]=0;
	replyBuf.a[31]=0;

	
	replyBuf.a[32]=0x3f;
	replyBuf.a[33]=0xfb;
	replyBuf.a[34]=0xb6;
	replyBuf.a[35]=0x45;
	replyBuf.a[36]=0xa1;
	replyBuf.a[37]=0xca;
	replyBuf.a[38]=0xc0;
	replyBuf.a[39]=0x83;
	
			printf("\n");
			for(i=0;i<40;i++)
			{
			if (i%8==0)
				printf("\n");
			printf("%x   ",replyBuf.a[i]);
			}
			RTLAB_dataout_p=(struct RTLAB_SEND_DATA *)&replyBuf;
			testPoint=RTLAB_dataout_p->data[0];
			printf("testPoint= %lf \n  ",testPoint);
			
			memcpy(&testPoint,replyBuf.a[0],8);
			printf("testPoint= %lf \n  ",testPoint);
			
			printf("RTLAB_dataout_p->data[0]= %lf \n  ",RTLAB_dataout_p->data[0]);
			printf("RTLAB_dataout_p->data[1]= %lf \n ",RTLAB_dataout_p->data[1]);
			printf("RTLAB_dataout_p->data[2]= %lf\n  ",RTLAB_dataout_p->data[2]);
			printf("RTLAB_dataout_p->data[3]= %lf  \n ",RTLAB_dataout_p->data[3]);
			printf("RTLAB_dataout_p->data[4]= %lf  \n ",RTLAB_dataout_p->data[4]);

			
			testPoint=SWAP64(RTLAB_dataout_p->data[2]);
			printf("SWAP64(RTLAB_dataout_p->data[2]=%lf \n  ",testPoint);
			printf("SWAP64(RTLAB_dataout_p->data[0]=%lf \n  ",RTLAB_dataout_p->data[2]);
			
//			testPoint=1.0;
//			printf("%lf \n  ",testPoint);
	//		RTLAB_dataout_p->data[0]=1;
			RTLAB_dataout_p->data[1]=2;
			RTLAB_dataout_p->data[2]=3;
			RTLAB_dataout_p->data[3]=4.0;
			RTLAB_dataout_p->data[4]=1.732;
			
			printf("\n");

			printf("RTLAB_dataout_p->data[0]= %lf \n  ",RTLAB_dataout_p->data[0]);
			printf("RTLAB_dataout_p->data[1]= %lf \n ",RTLAB_dataout_p->data[1]);
			printf("RTLAB_dataout_p->data[2]= %lf\n  ",RTLAB_dataout_p->data[2]);
			printf("RTLAB_dataout_p->data[3]= %lf  \n ",RTLAB_dataout_p->data[3]);
			printf("RTLAB_dataout_p->data[4]= %lf  \n ",RTLAB_dataout_p->data[4]);

			
			for(i=0;i<40;i++)
			{
				replyBuf.a[i]=*((unsigned char *)&(RTLAB_dataout_p->data[0])+i);
			}
			
			for(i=0;i<40;i++)
						{
						if (i%8==0)
							printf("\n");
						printf("%x   ",replyBuf.a[i]);
						}
			
			printf("\n");
			printf("\n");
			printf("\n");
			
			testPoint=1.0;
			printf("testPoint= %lf\n   ",testPoint);
			testPoint_tmp=0x3ff0000000000000;
			printf("testPoint_tmp= %d\n   ",testPoint_tmp);			
	}

