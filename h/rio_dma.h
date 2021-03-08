#ifndef _INCriodmah
#define _INCriodmah

#ifdef _cplusplus
extern "C" {
#endif
	
#define RIO_DMAINIT_OK			0
#define RIO_DMAINIT_FAIL		1

typedef struct rio_dma {
	UINT32	mr;		/* 0x21100 - DMA 0 Mode Register */
	UINT32	sr;		/* 0x21104 - DMA 0 Status Register */
	char	res2[4];
	UINT32	clndar;	/* 0x2110c - DMA 0 Current Link Descriptor Address Register */
	UINT32	satr;	/* 0x21110 - DMA 0 Source Attributes Register */
	UINT32	sar;		/* 0x21114 - DMA 0 Source Address Register */
	UINT32	datr;	/* 0x21118 - DMA 0 Destination Attributes Register */
	UINT32	dar;		/* 0x2111c - DMA 0 Destination Address Register */
	UINT32	bcr;		/* 0x21120 - DMA 0 Byte Count Register */
	char	res3[4];
	UINT32	nlndar;	/* 0x21128 - DMA 0 Next Link Descriptor Address Register */
	char	res4[8];
	UINT32	clabdar;	/* 0x21134 - DMA 0 Current List - Alternate Base Descriptor Address Register */
	char	res5[4];
	UINT32	nlsdar;	/* 0x2113c - DMA 0 Next List Descriptor Address Register */
	UINT32	ssr;		/* 0x21140 - DMA 0 Source Stride Register */
	UINT32	dsr;		/* 0x21144 - DMA 0 Destination Stride Register */
} rio_dma_t;

/**/


/* function declare */
void rioDmaIsrhandel(UINT32 channel);
int rioDmaInitChn(UINT32 channel,int flag);
int rioDmaDirectSend(UINT32 channel, UINT32 source, UINT32 destination, UINT32 size_bytes);
int sic_srio_Dma_InitChn(UINT32 channel, VOIDFUNCPTR isrRoutine);

#ifdef _cplusplus
}
#endif

#endif
