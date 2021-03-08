#ifndef _AST7700SRIO_
#define _AST7700SRIO_

#ifdef __cplusplus
extern "C" {
#endif


#define AST_PPC_SRIO_DMA_INBOUND_BASE	(0xf0000000)
#define AST_PPC_SRIO_DMA_INBOUND_TAR	(0x78000000)
#define AST_PPC_SRIO_DMA_INBOUND_SIZE	(16*1024*1024)

#define AST_PPC_SRIO_DMA_OUTBOUND_BASE	(0xc8000000)
#define AST_PPC_SRIO_DMA_OUTBOUND_TAR	(0xf0000000)
#define AST_PPC_SRIO_DMA_OUTBOUND_SIZE	(16*1024*1024)


#define srioMutiSendID 20
extern int ast7700SrioID;

extern int  ast7600SrioStatus;
extern int  ast7600SrioId;
extern int  ast7600SrioInitOk;

extern INT32 ast7700SrioInit(void);
extern INT32 ast7700SrioDmaInit( void );
extern INT32 ast7700SrioSingleSendData( UINT16 destId, INT32 nbytes, UINT8 * pbuffer );/*单独发送各板卡*/
extern INT32 ast7700SrioMutilSendData( INT32 nbytes, UINT8 * pbuffer );/*组播发送各板卡，主要是4个PWM板*/
extern void read_7600_SrioData(void);
extern void write_7600_SrioData(void);
extern INT32 wait_7600_SrioInitOk(void);
#ifdef __cplusplus
}
#endif

#endif
