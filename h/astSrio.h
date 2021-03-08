#ifndef _AST_SRIO_H_
#define _AST_SRIO_H_

/* serial RapidIO register address define */
#define AST_SRIO_REG_BASE	( CCSBAR + 0xC0000 )				/* Base address of SRIO registers */
#define AST_SRIO_BDIDCSR	( AST_SRIO_REG_BASE + 0x0060 )		/* Base device ID command and status register */
#define AST_SRIO_PGCCSR		( AST_SRIO_REG_BASE + 0x013C )		/* Port General control command and status register */

/* nnumber of dma channel */
#define AST_SRIO_DMA_CHANNEL_NUMBER	( 4 )

/* srio dma outbound number */
#define AST_SRIO_OUTBOUND_NUMBER	( 1 + 8 )
#define AST_SRIO_INBOUND_NUMBER		( 1 + 4 )

/* srio dma struct */
#define AST_SRIO_OUTBOUND 	srio_ob_t
#define AST_SRIO_INBOUND	srio_ib_t

/* routine define */
extern INT32 astSrioDbRecive(
		UINT16 *sourceID, 
		UINT16 *data, 
		_Vx_ticks_t timeout
		);

extern INT32 astSrioDbSend(
		UINT16 destID, 
		UINT16 data
		);

extern INT32 astSrioDoorbellInit( void );

extern INT32 astSrioMsgReceive(
		UINT8 *buffer,
		INT32 maxBytes, 
		_Vx_ticks_t timeout
		);

extern INT32 astSrioMsgSend(
		UINT32 destID,
		const UINT8 *buffer, 
		UINT32 bufferSize
		);

extern INT32 astSrioMsgInit( void );

extern STATUS astSrioDmaSend(
		UINT32 channel,
		UINT32 buffer,
		UINT32 dst_addr,
		INT32 nbytes
		);

extern INT32 astSrioDmaOutboundMap(
		INT32 srioPort,
		AST_SRIO_OUTBOUND outbound );

extern INT32 astSrioDmaInboundMap(
		INT32 srioPort,
		AST_SRIO_INBOUND inbound );

extern INT32 astSrioDmaInit( void );

extern void astSrioRouteShow( void );

extern UINT32 astSrioHostOrAgentGet( void );

extern UINT8 astSrioDeviceIDGet( void );

extern void astSrioDeviceIDShow( void );

extern INT32 astSrioMulticastAdd(
		UINT8 hopcount, 
		UINT16 mcast_mask, 
		UINT8 outPort, 
		UINT16 multicast_id);

extern INT32 astSrioMulticastRemove(
		UINT8 hopcount, 
		UINT16 mcast_mask, 
		UINT8 outPort, 
		UINT16 multicast_id);

extern STATUS astSrioSetup( void );


#endif
