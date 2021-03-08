/*  
* target:ast7600    
* Copyright 2018,4,16 IEE, Inc. 
* description:  the goal is to use SRIO channel to communicate with other slave board 
* function: 
* debug: 
* modification history
*/
/**************************************************************************************/
 

#include "vxWorks.h"

#include "ast7700Srio.h"

#include "h/rio_setup.h"
#include "h/rio_msg.h"
#include "h/rio_dbell.h"
#include "h/rio_dma.h"
#include "h/astSrio.h"

#include "main_variable.h"

/*************************************************************************************/


int ast7700SrioID;
INT32 ast7700SrioDmaInit( void );
/*************************************************************************************/
int  ast7600SrioStatus=0;
int  ast7600SrioId=0;
int  ast7600SrioInitOk=0;
struct RX_7600_STRUCT rx_7600_data2;
/*************************************************************************************/
/*Name		:ast7700SRIO_Init
*Description:初始化7700-2040DMA
*Input		:无
*Output		:无
*Return		:OK or ERROR
*History	:2018-07-16,modified by wxx
* 首先VME初始化各板卡的srio配置
* 得到ID
* 设置发送地址
* 设置接收地址
*设置发送大小接受大小 
* 设置广播ID
*其次初始化7700 SRIO，配置组播
*然后启动个从板发送srio
*/
INT32 ast7700SrioInit(void)
{
	INT32 istate = 0;
	
	int status=0;
	int dmaInitStaus=0;		
		
	astLocalbusFpgaInit();		
	status=ast7700SrioDmaInit();
 
	if(status==OK)
	{
		dmaInitStaus=1;
		astLocalbusFpgaWrite(0x1000,&dmaInitStaus,1);
	}
	else
	{
		dmaInitStaus=0;
		astLocalbusFpgaWrite(0x1000,&dmaInitStaus,1);
	}		 
 
	astSrioRouteShow();
	
	
	
 
	return OK ;
}
/*******************************************************************************************/
/*Name		:ast7700PpcSrioDmaInit
*Description:初始化DMA收发测试
*Input		:无
*Output		:无
*Return		:OK or ERROR
*History	:2018-01-10,modified by syjiang
*/
INT32 ast7700SrioDmaInit( void )
{
	INT32 istate = 0;
	INT32 taskId = 0;
	AST_SRIO_INBOUND srioInbound;
	AST_SRIO_OUTBOUND srioOutbound,srioOutbound2;	
	
	/* SRIO初始化 */
	astSrioSetup( );
	
	/* doorbell初始化，doorbell用于通知对方已发送数据 */
	istate = astSrioDoorbellInit();
	if(ERROR == istate)
	{
		printf("Srio doorbell initialize fail!\n");
		return ERROR;
	}
			
	/* message初始化 */
	istate = astSrioDmaInit();
	if(ERROR == istate)
	{
		printf("Srio dma initialize fail!\n");
		return ERROR;
	}
		
	/* inbound */
	memset(&srioInbound, 0, sizeof(AST_SRIO_INBOUND));
	srioInbound.inboundNo 	= 1;	/* 1~ 4 */
	srioInbound.inboundBase = AST_PPC_SRIO_DMA_INBOUND_BASE;
	srioInbound.inboundTar 	= AST_PPC_SRIO_DMA_INBOUND_TAR;
	srioInbound.size 		= AST_PPC_SRIO_DMA_INBOUND_SIZE;
	astSrioDmaInboundMap(0,srioInbound);

	/* outbound映射，如果目的id及地址固定，建议可系统初始化时配置一次，节省操作时间
		 * 以下例子为outbound分为16个subsegment，将outbound空间等分为16份
		 * 如不需要分段，则segment及subsegment参数置为0即可
	 */
	memset(&srioOutbound, 0, sizeof(AST_SRIO_OUTBOUND));
	srioOutbound.outboundNo 	= 2;				/* 1 ~ 8 */
	srioOutbound.targetID 		= 0;/*destId;*/			/* 起始目的rapidio id */
	
	srioOutbound.outboundBase 	= AST_PPC_SRIO_DMA_OUTBOUND_BASE;		/* 本地地址 */
	srioOutbound.outboundTar 	= AST_PPC_SRIO_DMA_OUTBOUND_TAR;		/* 目的rapidio地址 */
	srioOutbound.segment		= 2;	/*每个outbound分为2个segment*/
	srioOutbound.subsegment		= 2;	/*每个segment分为8个subsegment*/
	srioOutbound.wrtyp			= 4;
	srioOutbound.size 			= AST_PPC_SRIO_DMA_OUTBOUND_SIZE;
	astSrioDmaOutboundMap( 0,srioOutbound );	
	

	return OK;
}
/*******************************************************************************************/
/*
* Name		:ast7700SrioSingleSendData
*Description:以DMA或者IO方式单独发送srio数据,视数据大小采用IO或者DMA
*Input		:destId	目的设备rapidio id
*			:nbytes	发送数据长度,必须是4的倍数
*			：pbuffer，发送缓存
*Output		:无
*Return		:OK or ERROR
*History	:2018-01-10,modified by syjiang
*/
INT32 ast7700SrioSingleSendData( UINT16 destId, INT32 nbytes, UINT8 * pbuffer )/*单独发送各板卡*/
{

	INT32 istate = 0;
	INT32 i = 0;
	if(destId>srioMutiSendID) 
		return ERROR;
	/* 判断长度 */
	if( nbytes >= AST_PPC_SRIO_DMA_OUTBOUND_SIZE )
	{
	//	printf("Error, the data length [%d] is too big.\n", nbytes);
		return ERROR;
	}	
	if(nbytes<512)
	{	
		/* 通过IO发送数据 */
		for( i = 0; i < ( nbytes / 4 ); i++ )
		{
			*(volatile UINT32*)(AST_PPC_SRIO_DMA_OUTBOUND_BASE + destId * ( AST_PPC_SRIO_DMA_OUTBOUND_SIZE / 16) + i*4) = *(UINT32*)(pbuffer + i*4);
		}
	}
	else
	{	
		/* 通过DMA发送数据 */
		istate = astSrioDmaSend(0, (INT32)pbuffer, \
				AST_PPC_SRIO_DMA_OUTBOUND_BASE + destId * ( AST_PPC_SRIO_DMA_OUTBOUND_SIZE / 16 ), \
				nbytes);
		 
		if(ERROR == istate)
		{
		//	printf("Srio data send fail.\n");
			return ERROR;
		}	
	}	
	return OK;
}
/*******************************************************************************************/
/*
* Name		:read_7600_SrioData
*Description:从SRIO接收内存对应7600CPU的地址读出7600发送过来的数据
*Input		:结构体指针*
*Output		:结构体rx_7600_data
*Return		:无
*History	:2018-07-18,modified by wxx
*/
void read_7600_SrioData(void)
{
	int i=0;
	int size=0;
	size=sizeof(struct RX_7600_STRUCT);
	memcpy((void *)&rx_7600_data ,(const void *)rx_7600_data_pointer ,size);
}
/*******************************************************************************************/
/*
* Name		:write_7600_SrioData
*Description:向SRIO发送内存对应7600CPU的地址写数据
*Input		:结构体指针tx_7600_data
*Output		:无
*Return		:无
*History	:2018-07-18,modified by wxx
*/
void write_7600_SrioData(void)
{
	int i=0;
	int size=0;
	int status=0;
	size=sizeof(struct RX_7600_STRUCT);
  
	tx_7600_data.boardID=0x7700;
	tx_7600_data.liveCnt++;
	tx_7600_data.short_variable[8]=ast7600SrioId;
	tx_7600_data.int_variable[0]=0x12345678;
	tx_7600_data.float_variable[0]=1234.5678;
	
//	writecounter++; // add lhc for test 

#ifdef intDATA   //lhc remove for test double structure  20190322
	/*add status reply code here*/
	if(SWAP16(RTLAB_dataout_p->data[0]) ==1)
	{
		tx_7600_data.short_variable[0]=0x1;
	}
	else 
	{
		tx_7600_data.short_variable[0]=0;
	}

	if(SWAP16(RTLAB_dataout_p->data[1])==1)
	{
		tx_7600_data.short_variable[1]=0x1;
	}
	else 
	{
		tx_7600_data.short_variable[1]=0;
	}
	if(SWAP16(RTLAB_dataout_p->data[2])==1)
	{
		tx_7600_data.short_variable[2]=0x1;
	}
	else 
	{
		tx_7600_data.short_variable[2]=0;
	}
#endif	
	
#ifdef doubleDATA   //double structure  20190327
	/*add status reply code here*/
	
	if(RS_switchINcmd ==1)
	{
		tx_7600_data.short_variable[0]=0x1;
	}
	else 
	{
		tx_7600_data.short_variable[0]=0;
//		logMsg("(2)RS_switchINcmd =%d\n",RS_switchINcmd,0,0,0,0,0);
	}
	
	if(RS_switch_DT_BTcmd==1)
	{
		tx_7600_data.short_variable[1]=0x1;
	}
	else 
	{
		tx_7600_data.short_variable[1]=0;
	}
	if(RS_switchOUTcmd==1)
	{
		tx_7600_data.short_variable[2]=0x1;
	}
	else 
	{
		tx_7600_data.short_variable[2]=0;
	}
	
/*	if(RS_switchINcmd !=1)
			{
				logMsg("(2)RS_switchINcmd =%d\n",RS_switchINcmd,0,0,0,0,0);
			}
	if(writecounter==6000)
	{
		writecounter=0;
		printf("(lf)RS_switchINcmd= %lf \n  ",RS_switchINcmd);
		printf("(lf)RS_switch_DT_BTcmd= %lf \n ",RS_switch_DT_BTcmd);
		printf("(lf)RS_switchOUTcmd= %lf\n  ",RS_switchOUTcmd);
		
		printf("(d)RS_switchINcmd= %d \n  ",RS_switchINcmd);
		printf("(d)RS_switch_DT_BTcmd= %d \n ",RS_switch_DT_BTcmd);
		printf("(d)RS_switchOUTcmd= %d\n  ",RS_switchOUTcmd);
	}*/
/*	if(RTLAB_dataout_p->data[0] ==1)
	{
		tx_7600_data.short_variable[0]=0x1;
	}
	else 
	{
		tx_7600_data.short_variable[0]=0;
		logMsg("(2)RTLAB_dataout_p->data[0]=%d\n",RTLAB_dataout_p->data[0],0,0,0,0,0);
	}*/

/*	if(RTLAB_dataout_p->data[1]==1)
	{
		tx_7600_data.short_variable[1]=0x1;
	}
	else 
	{
		tx_7600_data.short_variable[1]=0;
	}
	if(RTLAB_dataout_p->data[2]==1)
	{
		tx_7600_data.short_variable[2]=0x1;
	}
	else 
	{
		tx_7600_data.short_variable[2]=0;
	}*/
#endif		
	
	status=ast7700SrioSingleSendData(ast7600SrioId,sizeof(struct TX_7600_STRUCT),(UINT8 *)&tx_7600_data);
	if(ERROR == status)
	{
		logMsg("Srio dma send fail!\n",0,0,0,0,0,0);			
	}

}
 
/****************************************************************************************/
/*
* Name		:wait_7600_SrioInitOk
*Description:等待7600初始化SRIO
*Input		:FPGA数据交换区地址0x2000,0x20004
*Output		:ast7700SrioStatus,ast7700SrioId
*Return		:OK or ERROR
*History	:2018-07-18,modified by wxx
*/
INT32 wait_7600_SrioInitOk(void)
{
/*wait for ast7600 finishing SRIO finish initiation*/	
	
	astLocalbusFpgaRead(0x2000,&ast7600SrioStatus,4);	
	 
	if(ast7600SrioStatus==1)		/*读取7600 SRIO ID*/	
		astLocalbusFpgaRead(0x2004,&ast7600SrioId,4);
	if(ast7600SrioStatus==1 && ast7600SrioId>0 && ast7600SrioId<256)
	{ 
		ast7600SrioInitOk=1;
		rx_7600_data_pointer=AST_PPC_SRIO_DMA_INBOUND_TAR;	//  20190401 	
//		rx_7600_data_pointer=AST_PPC_SRIO_DMA_INBOUND_TAR+ast7600SrioId*1024*1024/16;
//		return OK;
	}
//	else
//		return ERROR;

}
/*****************************************************************************
*Name		:astTestSrioDmaSegmentSend
*Description:outbound窗口分段，以dma方式发送srio数据
*Input		:destId	目的设备rapidio id，0~15
*			:nbytes	发送数据长度
*Output		:无
*Return		:OK or ERROR
*History	:2018-01-10,modified by syjiang
*/
INT32 astTestSrioDmaSegmentSend( UINT16 destId, INT32 nbytes )
{
	INT32 istate = 0;
	INT32 i = 0;
	UINT8 pbuffer[4096 + 1] = {0};
	UINT32 prand = 0;
	AST_SRIO_OUTBOUND srioOutbound;
	
	/* 判断长度 */
	if( nbytes >= AST_PPC_SRIO_DMA_OUTBOUND_SIZE )
	{
		printf("Error, the data length [%d] is too big.\n", nbytes);
		return ERROR;
	}
	
	/* 组织数据 */
	prand = rand();
	for(i = 0; i< nbytes; i++)
	{
		*(UINT8*)(pbuffer + i) = prand + i;
	}
	
	/* 发送数据 */
	istate = astSrioDmaSend(0, \
					(INT32)pbuffer, \
					AST_PPC_SRIO_DMA_OUTBOUND_BASE+destId*1024*1024, \
					nbytes);
	if(ERROR == istate)
	{
		printf("Srio data send fail.\n");
		return ERROR;
	}
	/* 发送doorbell通知 */
		istate = astSrioDbSend(destId, 0x1122);
		if(ERROR == istate)
		{
			printf("Srio doorbell send fail.\n");
			return ERROR;
		}
	/* 打印发送的前几个数据 */
	printf("We send data[%08x][%08x][%08x][%08x][%08x][%08x].\n", 
				*(UINT32*)(pbuffer+0), *(UINT32*)(pbuffer+4),*(UINT32*)(pbuffer+8),\
				*(UINT32*)(pbuffer+12),*(UINT32*)(pbuffer+16),*(UINT32*)(pbuffer+20));
	
	return OK;
}
