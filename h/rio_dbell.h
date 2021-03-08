#ifndef _INCriodbellh
#define _INCriodbellh

#ifdef _cplusplus
extern "C" {
#endif
	
#define DBMS_MSGFC0_OFF		0xcc00
#define DBMS_MSGFC1_OFF		0xdd00
#define DBMS_MSGFC0_ON		0xee00
#define DBMS_MSGFC1_ON		0xff00
#define DBMG_BOOTUP_OK		0xbb00
	
	

/*******************************************************
 RapidIO Inbound Doorbell Registers bits define 
*******************************************************/
#define DOORBELL_DMR_DI         						0x00000002
#define DOORBELL_DMR_SEN        						0x00100000
#define DOORBELL_DMR_512_SIZ   						0x00008000
#define DOORBELL_DMR_QFIE       						0x00000100
#define DOORBELL_DMR_DIQIE      						0x00000040
#define DOORBELL_DMR_EIE        						0x00000020
#define DOORBELL_DMR_DE         						0x00000001
#define DOORBELL_DSR_TE         							0x00000080
#define DOORBELL_DSR_QFI        						0x00000010
#define DOORBELL_DSR_DIQI       						0x00000001
#define DOORBELL_TID_OFFSET    	 					0x00000003
#define DOORBELL_SID_OFFSET    	 					0x00000005
#define DOORBELL_INFO_OFFSET    					0x00000006
#define DOORBELL_MESSAGE_SIZE   					0x08
#define DOORBELL_UNIT_BUSY 							1

#define IDMR_DIQ_Thresh_Shift							28
#define IDMR_SEN_Shift										20
#define IDMR_Cirq_Size_Shift								12
#define IDMR_QFIE_Shift										8
#define IDMR_DIQIE_Shift									6
#define IDMR_EIE_Shift             	 						5
#define IDMR_DE_Shift											0
#define IDSR_DB_Mask											0x04
#define IDSR_DIQ_Mask										0x00010000
#define IDMR_DI_Mask										0x00000002
#define IDMR_DE_Mask										0x00000001

#define ODSR_DUB_Mask										0x04
#define ODMR_DUS_Mask									0x01
#define ODDPR_TGTROUTE_Shift							16
#define ODDATR_EODIE_Shift								29
#define ODDATR_DTFLOWLVL_Shift						26
#define ODDATR_INFO_Shift 								0 
#define ODDATR_DTGTINT_Shift 							20
#define IB_Q_EMPTY 											0

#define DBELL_SID(x)            								(*(UINT8 *)(x + DOORBELL_SID_OFFSET))
#define DBELL_TID(x)           							        (*(UINT8 *)(x + DOORBELL_TID_OFFSET))
#define DBELL_INF(x)           									(*(UINT16 *)(x + DOORBELL_INFO_OFFSET))

#define DB_DIQ_THRESH 										0
#define DB_SEN 1
#define DB_CIRQ_SIZE 											256 
#define DB_QUEUE_SIZE 										256
#define DB_QFIE 													1  
#define DB_DIQIE 												1   
#define DB_EIE             										0   
#define DB_DE 													1   
#define EODIE 														1               
#define DTFLOWLVL 											0 
#define DB_RETRY 												3

/* function declare */	
int enable_ob_dbs(VOIDFUNCPTR );
int enable_ib_dbs(VOIDFUNCPTR );
int rioSendDbMsg(int , UINT16 , UINT16);	
	


#ifdef _cplusplus
}
#endif

#endif
