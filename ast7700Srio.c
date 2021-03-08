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
*Description:��ʼ��7700-2040DMA
*Input		:��
*Output		:��
*Return		:OK or ERROR
*History	:2018-07-16,modified by wxx
* ����VME��ʼ�����忨��srio����
* �õ�ID
* ���÷��͵�ַ
* ���ý��յ�ַ
*���÷��ʹ�С���ܴ�С 
* ���ù㲥ID
*��γ�ʼ��7700 SRIO�������鲥
*Ȼ���������Ӱ巢��srio
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
*Description:��ʼ��DMA�շ�����
*Input		:��
*Output		:��
*Return		:OK or ERROR
*History	:2018-01-10,modified by syjiang
*/
INT32 ast7700SrioDmaInit( void )
{
	INT32 istate = 0;
	INT32 taskId = 0;
	AST_SRIO_INBOUND srioInbound;
	AST_SRIO_OUTBOUND srioOutbound,srioOutbound2;	
	
	/* SRIO��ʼ�� */
	astSrioSetup( );
	
	/* doorbell��ʼ����doorbell����֪ͨ�Է��ѷ������� */
	istate = astSrioDoorbellInit();
	if(ERROR == istate)
	{
		printf("Srio doorbell initialize fail!\n");
		return ERROR;
	}
			
	/* message��ʼ�� */
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

	/* outboundӳ�䣬���Ŀ��id����ַ�̶��������ϵͳ��ʼ��ʱ����һ�Σ���ʡ����ʱ��
		 * ��������Ϊoutbound��Ϊ16��subsegment����outbound�ռ�ȷ�Ϊ16��
		 * �粻��Ҫ�ֶΣ���segment��subsegment������Ϊ0����
	 */
	memset(&srioOutbound, 0, sizeof(AST_SRIO_OUTBOUND));
	srioOutbound.outboundNo 	= 2;				/* 1 ~ 8 */
	srioOutbound.targetID 		= 0;/*destId;*/			/* ��ʼĿ��rapidio id */
	
	srioOutbound.outboundBase 	= AST_PPC_SRIO_DMA_OUTBOUND_BASE;		/* ���ص�ַ */
	srioOutbound.outboundTar 	= AST_PPC_SRIO_DMA_OUTBOUND_TAR;		/* Ŀ��rapidio��ַ */
	srioOutbound.segment		= 2;	/*ÿ��outbound��Ϊ2��segment*/
	srioOutbound.subsegment		= 2;	/*ÿ��segment��Ϊ8��subsegment*/
	srioOutbound.wrtyp			= 4;
	srioOutbound.size 			= AST_PPC_SRIO_DMA_OUTBOUND_SIZE;
	astSrioDmaOutboundMap( 0,srioOutbound );	
	

	return OK;
}
/*******************************************************************************************/
/*
* Name		:ast7700SrioSingleSendData
*Description:��DMA����IO��ʽ��������srio����,�����ݴ�С����IO����DMA
*Input		:destId	Ŀ���豸rapidio id
*			:nbytes	�������ݳ���,������4�ı���
*			��pbuffer�����ͻ���
*Output		:��
*Return		:OK or ERROR
*History	:2018-01-10,modified by syjiang
*/
INT32 ast7700SrioSingleSendData( UINT16 destId, INT32 nbytes, UINT8 * pbuffer )/*�������͸��忨*/
{

	INT32 istate = 0;
	INT32 i = 0;
	if(destId>srioMutiSendID) 
		return ERROR;
	/* �жϳ��� */
	if( nbytes >= AST_PPC_SRIO_DMA_OUTBOUND_SIZE )
	{
	//	printf("Error, the data length [%d] is too big.\n", nbytes);
		return ERROR;
	}	
	if(nbytes<512)
	{	
		/* ͨ��IO�������� */
		for( i = 0; i < ( nbytes / 4 ); i++ )
		{
			*(volatile UINT32*)(AST_PPC_SRIO_DMA_OUTBOUND_BASE + destId * ( AST_PPC_SRIO_DMA_OUTBOUND_SIZE / 16) + i*4) = *(UINT32*)(pbuffer + i*4);
		}
	}
	else
	{	
		/* ͨ��DMA�������� */
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
*Description:��SRIO�����ڴ��Ӧ7600CPU�ĵ�ַ����7600���͹���������
*Input		:�ṹ��ָ��*
*Output		:�ṹ��rx_7600_data
*Return		:��
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
*Description:��SRIO�����ڴ��Ӧ7600CPU�ĵ�ַд����
*Input		:�ṹ��ָ��tx_7600_data
*Output		:��
*Return		:��
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
*Description:�ȴ�7600��ʼ��SRIO
*Input		:FPGA���ݽ�������ַ0x2000,0x20004
*Output		:ast7700SrioStatus,ast7700SrioId
*Return		:OK or ERROR
*History	:2018-07-18,modified by wxx
*/
INT32 wait_7600_SrioInitOk(void)
{
/*wait for ast7600 finishing SRIO finish initiation*/	
	
	astLocalbusFpgaRead(0x2000,&ast7600SrioStatus,4);	
	 
	if(ast7600SrioStatus==1)		/*��ȡ7600 SRIO ID*/	
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
*Description:outbound���ڷֶΣ���dma��ʽ����srio����
*Input		:destId	Ŀ���豸rapidio id��0~15
*			:nbytes	�������ݳ���
*Output		:��
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
	
	/* �жϳ��� */
	if( nbytes >= AST_PPC_SRIO_DMA_OUTBOUND_SIZE )
	{
		printf("Error, the data length [%d] is too big.\n", nbytes);
		return ERROR;
	}
	
	/* ��֯���� */
	prand = rand();
	for(i = 0; i< nbytes; i++)
	{
		*(UINT8*)(pbuffer + i) = prand + i;
	}
	
	/* �������� */
	istate = astSrioDmaSend(0, \
					(INT32)pbuffer, \
					AST_PPC_SRIO_DMA_OUTBOUND_BASE+destId*1024*1024, \
					nbytes);
	if(ERROR == istate)
	{
		printf("Srio data send fail.\n");
		return ERROR;
	}
	/* ����doorbell֪ͨ */
		istate = astSrioDbSend(destId, 0x1122);
		if(ERROR == istate)
		{
			printf("Srio doorbell send fail.\n");
			return ERROR;
		}
	/* ��ӡ���͵�ǰ�������� */
	printf("We send data[%08x][%08x][%08x][%08x][%08x][%08x].\n", 
				*(UINT32*)(pbuffer+0), *(UINT32*)(pbuffer+4),*(UINT32*)(pbuffer+8),\
				*(UINT32*)(pbuffer+12),*(UINT32*)(pbuffer+16),*(UINT32*)(pbuffer+20));
	
	return OK;
}
