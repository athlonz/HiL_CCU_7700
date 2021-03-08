#ifndef _INCriomsgh
#define _INCriomsgh

#ifdef _cplusplussrioMsgSetup
extern "C" {
#endif

#define RIO_MSG_REGS_OFFSET     	0x13000
#define OM_DESC_BASE0   			0x1e000000
#define OM_DESC_BASE1   			(OM_DESC_BASE0+0x10000)/*0x10000=(2048*32)*/
#define OM_BUF_BASE0 				0x12000000 
#define IM_BUF_BASE0  				(OM_BUF_BASE0 + 0x800000)
#define OM_BUF_BASE1  				(OM_BUF_BASE0 + 0x1000000)
#define IM_BUF_BASE1  				(OM_BUF_BASE0 + 0x1800000)
#define PW_BUF_BASE     			0x1f000000
#define RIO_MAX_MSGCHAIN_SIZE 		4096	
#define RIO_MSG_OBQ_SIZE 			2048
#define RIO_MSG_IBQ_SIZE 			2048
#define RIO_MSG_IBQ_HWLINE  		1024	/*(RIO_MAX_MSGCHAIN_SIZE>>1)*/
#define RIO_MSG_IBQ_LWLINE 			256		/*(RIO_MAX_MSGCHAIN_SIZE>>2)*/
#define RIOQMSG_RX_MBOX0 			0x00000001
#define RIOQMSG_RX_MBOX1 			0x00000002	
	

#define RIO_PORT_MNT_HEADER			0x0000
#define RIO_PORT_REQ_CTL_CSR		0x0020
#define RIO_PORT_RSP_CTL_CSR		0x0024	/* 0x0001/0x0002 */
#define RIO_PORT_LINKTO_CTL_CSR		0x0020	/* Serial */
#define RIO_PORT_RSPTO_CTL_CSR		0x0024	/* Serial */
#define RIO_PORT_GEN_CTL_CSR		0x003c
#define RIO_PORT_GEN_HOST			0x80000000
#define RIO_PORT_GEN_MASTER			0x40000000
#define RIO_PORT_GEN_DISCOVERED		0x20000000
#define RIO_PORT_N_MNT_REQ_CSR(x)	(0x0040 + x*0x20)	/* 0x0002 */
#define RIO_MNT_REQ_CMD_RD			0x03	/* Reset-device command */
#define RIO_MNT_REQ_CMD_IS			0x04	/* Input-status command */
#define RIO_PORT_N_MNT_RSP_CSR(x)	(0x0044 + x*0x20)	/* 0x0002 */
#define RIO_PORT_N_MNT_RSP_RVAL		0x80000000 /* Response Valid */
#define RIO_PORT_N_MNT_RSP_ASTAT	0x000007e0 /* ackID Status */
#define RIO_PORT_N_MNT_RSP_LSTAT	0x0000001f /* Link Status */
#define RIO_PORT_N_ACK_STS_CSR(x)	(0x0048 + x*0x20)	/* 0x0002 */
#define RIO_PORT_N_ACK_CLEAR		0x80000000
#define RIO_PORT_N_ACK_INBOUND		0x3f000000
#define RIO_PORT_N_ACK_OUTSTAND		0x00003f00
#define RIO_PORT_N_ACK_OUTBOUND		0x0000003f
#define RIO_PORT_N_ERR_STS_CSR(x)	(0x0058 + x*0x20)
#define RIO_PORT_N_ERR_STS_PW_OUT_ES	0x00010000 /* Output Error-stopped */
#define RIO_PORT_N_ERR_STS_PW_INP_ES	0x00000100 /* Input Error-stopped */
#define RIO_PORT_N_ERR_STS_PW_PEND	0x00000010 /* Port-Write Pending */
#define RIO_PORT_N_ERR_STS_PORT_ERR	0x00000004
#define RIO_PORT_N_ERR_STS_PORT_OK	0x00000002
#define RIO_PORT_N_ERR_STS_PORT_UNINIT	0x00000001
#define RIO_PORT_N_CTL_CSR(x)		(0x005c + x*0x20)
#define RIO_PORT_N_CTL_PWIDTH		0xc0000000
#define RIO_PORT_N_CTL_PWIDTH_1		0x00000000
#define RIO_PORT_N_CTL_PWIDTH_4		0x40000000
#define RIO_PORT_N_CTL_P_TYP_SER	0x00000001
#define RIO_PORT_N_CTL_LOCKOUT		0x00000002
#define RIO_PORT_N_CTL_EN_RX_SER	0x00200000
#define RIO_PORT_N_CTL_EN_TX_SER	0x00400000
#define RIO_PORT_N_CTL_EN_RX_PAR	0x08000000
#define RIO_PORT_N_CTL_EN_TX_PAR	0x40000000

#define RIO_IPWMR_SEN		0x00100000
#define RIO_IPWMR_QFIE		0x00000100
#define RIO_IPWMR_EIE		0x00000020
#define RIO_IPWMR_CQ		0x00000002
#define RIO_IPWMR_PWE		0x00000001

#define RIO_IPWSR_QF		0x00100000
#define RIO_IPWSR_TE		0x00000080
#define RIO_IPWSR_QFI		0x00000010
#define RIO_IPWSR_PWD		0x00000008
#define RIO_IPWSR_PWB		0x00000004

#define RIO_EPWISR		0x10010

#define LTLEECSR_ENABLE_ALL	0xFFC000FC

/* General EM Registers (Common for all Ports) */
#define RIO_EM_EFB_HEADER		0x000	/* Error Management Extensions Block Header */
#define RIO_EM_LTL_ERR_DETECT	0x008	/* Logical/Transport Layer Error Detect CSR */
#define RIO_EM_LTL_ERR_EN		0x00c	/* Logical/Transport Layer Error Enable CSR */
#define REM_LTL_ERR_ILLTRAN		0x08000000 /* Illegal Transaction decode */
#define REM_LTL_ERR_UNSOLR		0x00800000 /* Unsolicited Response */
#define REM_LTL_ERR_UNSUPTR		0x00400000 /* Unsupported Transaction */
#define REM_LTL_ERR_IMPSPEC		0x000000ff /* Implementation Specific */
#define RIO_EM_LTL_HIADDR_CAP	0x010	/* Logical/Transport Layer High Address Capture CSR */
#define RIO_EM_LTL_ADDR_CAP		0x014	/* Logical/Transport Layer Address Capture CSR */
#define RIO_EM_LTL_DEVID_CAP	0x018	/* Logical/Transport Layer Device ID Capture CSR */
#define RIO_EM_LTL_CTRL_CAP		0x01c	/* Logical/Transport Layer Control Capture CSR */
#define RIO_EM_PW_TGT_DEVID		0x028	/* Port-write Target deviceID CSR */
#define RIO_EM_PKT_TTL			0x02c	/* Packet Time-to-live CSR */

/* Per-Port EM Registers */
#define RIO_EM_PN_ERR_DETECT(x)	(0x040 + x*0x40) /* Port N Error Detect CSR */
#define REM_PED_IMPL_SPEC		0x80000000
#define REM_PED_LINK_TO			0x00000001
#define RIO_EM_PN_ERRRATE_EN(x) (0x044 + x*0x40) /* Port N Error Rate Enable CSR */
#define RIO_EM_PN_ATTRIB_CAP(x)	(0x048 + x*0x40) /* Port N Attributes Capture CSR */
#define RIO_EM_PN_PKT_CAP_0(x)	(0x04c + x*0x40) /* Port N Packet/Control Symbol Capture 0 CSR */
#define RIO_EM_PN_PKT_CAP_1(x)	(0x050 + x*0x40) /* Port N Packet Capture 1 CSR */
#define RIO_EM_PN_PKT_CAP_2(x)	(0x054 + x*0x40) /* Port N Packet Capture 2 CSR */
#define RIO_EM_PN_PKT_CAP_3(x)	(0x058 + x*0x40) /* Port N Packet Capture 3 CSR */
#define RIO_EM_PN_ERRRATE(x)	(0x068 + x*0x40) /* Port N Error Rate CSR */
#define RIO_EM_PN_ERRRATE_TR(x) (0x06c + x*0x40) /* Port N Error Rate Threshold CSR */
#define	IDT_ISLTL_ADDRESS_CAP	0x021014
#define IDT_PORT_ISERR_DET(n)	(0xf40008 + (n)*0x100)

#define IPWSR_CLEAR				0x98
#define OMSR_CLEAR				0x1cb3
#define IMSR_CLEAR				0x491
#define IDSR_CLEAR				0x91
#define ODSR_CLEAR				0x1c00
#define LTLEECSR_ENABLE_ALL		0xFFC000FC
#define RIO_LTLEECSR			0x060c
#define RIO_LTLEDCSR			0x0608
#define RIO_IM0SR				0x64
#define RIO_IM1SR				0x164
#define RIO_OM0SR				0x4
#define RIO_OM1SR				0x104


#define RIOMSG_OMR_SEN      (0x80000000 >>11)
#define RIOMSG_OMR_QOIE     (0x80000000 >>22)
#define RIOMSG_OMR_QFIE     (0x80000000 >>23)
#define RIOMSG_OMR_QEIE     (0x80000000 >>25)
#define RIOMSG_OMR_EIE      (0x80000000 >>26)
#define RIOMSG_OMR_MUTM     (0x80000000 >> 29)
#define RIOMSG_OMR_MUI      (0x80000000 >>30)
#define RIOMSG_OMR_MUS      (0x80000000 >> 31)

/*******************************************/
/* RapidIO outbound Message Registers bits define*/
/*******************************************/


#define OMR_SCTL_64               (7<<25)
#define OMR_SCTL_32               (6<<25)
#define OMR_SCTL_16               (5<<25)
#define OMR_SCTL_8               (4<<25)
#define OMR_SCTL_4               (3<<25)
#define OMR_SCTL_2               (2<<25)
#define OMR_SCTL_1               (1<<25)

#define OMR_CIRQ_SIZE_2048 		0xA
#define OMR_CIRQ_SIZE_1024 		0x9
#define OMR_CIRQ_SIZE_512   	0x8
#define OMR_CIRQ_SIZE_256   	0x7
#define OMR_CIRQ_SIZE_128   	0x6
#define OMR_CIRQ_SIZE_64   		0x5
#define OMR_CIRQ_SIZE_32   		0x4
#define OMR_CIRQ_SIZE_16   		0x3
#define OMR_CIRQ_SIZE_8   		0x2
#define OMR_CIRQ_SIZE_4   		0x1
#define OMR_CIRQ_SIZE_2   		0x0

#define OMR_CIRQ_SIZE_SHIFT (31-19)

#define RIOMSG_OSR_QF       (0x80000000 >>11)/* OSR (CCSBAR + 0xD3004 )*/
#define RIOMSG_OSR_TE       (0x80000000 >>24)
#define RIOMSG_OSR_QOI      (0x80000000 >>26)
#define RIOMSG_OSR_QFI      (0x80000000 >>27)
#define RIOMSG_OSR_MUB      (0x80000000 >>29)
#define RIOMSG_OSR_EOMI     (0x80000000 >>30)
#define RIOMSG_OSR_QEI      (0x80000000 >>31)

#define RIOMSG_OSAR_SNEN    (0x80000000 >> 29)/*OSAR (CCSBAR + 0xD3014 )*/

#define RIOMSG_ODATR_FLVL_0 		0
#define RIOMSG_ODATR_FLVL_1 		1
#define RIOMSG_ODATR_FLVL_2 		2
#define RIOMSG_ODATR_FLVL_SHIFT 	(31-5)
#define RIOMSG_ODATR_EOMIE  		(0x80000000 >> 2)/*ODATR (CCSBAR + 0xD301C )*/

/*******************************************/
/* RapidIO Inbound Message Registers bits define   */
/*******************************************/
#define RIO_MSG_ISR_TE      0x00000080
#define RIO_MSG_ISR_QF     (0x80000000 >>11)
#define RIO_MSG_ISR_QFI     0x00000010
#define RIO_MSG_ISR_MIQI    0x00000001
#define RIOMSG_ISR_MB       (0x80000000 >>29)
#define RIOMSG_ISR_MIQ      (0x80000000 >>15)


#define RIOMSG_IMR_SEN      (0x80000000 >>11)/* IMR (CCSBAR + 0xD3060 )*/
#define RIOMSG_IMR_QFIE     (0x80000000 >>23)
#define RIOMSG_IMR_MIQIE    (0x80000000 >>25)
#define RIOMSG_IMR_EIE      (0x80000000 >>26)
#define RIOMSG_IMR_MI       (0x80000000 >>30)
#define RIOMSG_IMR_ME       (0x80000000 >>31)
#define IMR_FRM_SIZE_4096   0xb
#define IMR_FRM_SIZE_SHIFT  (31-15)

#define IMR_CIRQ_SIZE_2048 	0xA
#define IMR_CIRQ_SIZE_1024 	0x9
#define IMR_CIRQ_SIZE_512   0x8
#define IMR_CIRQ_SIZE_256   0x7
#define IMR_CIRQ_SIZE_128   0x6
#define IMR_CIRQ_SIZE_64    0x5
#define IMR_CIRQ_SIZE_32    0x4
#define IMR_CIRQ_SIZE_16    0x3
#define IMR_CIRQ_SIZE_8     0x2
#define IMR_CIRQ_SIZE_4     0x1
#define IMR_CIRQ_SIZE_2     0x0

#define IMR_CIRQ_SIZE_SHIFT (31-19)

/*************************************/
/*************************************/
#define INT_VECTOR_IM0		(38+12)
#define INT_VECTOR_IM1		(40+12)
#define INT_VECTOR_OM0		(37+12)
#define INT_VECTOR_OM1		(39+12)
#define INT_VECTOR_ERR      (32+12)

#define RIO_MSG_DESC_SIZE       32
#define RIO_MSG_BUFFER_SIZE     4096
#define RIO_MIN_TX_RING_SIZE    2
#define RIO_MAX_TX_RING_SIZE    256
#define RIO_REGS_BASE       	(CCSR_BAR + 0xc0000)
#define RIO_PW_REGS_OFFSET		0x134e0


#define RIO_MUTM_DIRECT 1
#define RIO_MUTM_CHAIN  0


#define RIO_MSG_OK  			0
#define RIO_MSGSETUP_FAIL		0x01
#define RIO_MSG_IllEGAL_PARAM 	0x02
#define RIO_MSGTX_QF 			0x03
#define RIO_MSGTX_MUB 			0x04
#define RIO_MSGRX_FAIL 			0x04


typedef struct  rio_msg_map_t
{
    UINT32 omr;        	/*0xd_3000*/
    UINT32 osr;        	/*0xd_3004*/
    UINT32 pad1;       	/*0xd_3008*/
    UINT32 odqdpar;		/*0xd_300c*/
    UINT32 pad2;       	/*0xd_3010*/
    UINT32 osar;       	/*0xd_3014*/
    UINT32 odpr;       	/*0xd_3018*/
    UINT32 odatr;      	/*0xd_301c*/
    UINT32 odcr;       	/*0xd_3020*/
    UINT32 pad3;       	/*0xd_3024*/
    UINT32 odqepar;		/*0xd_3028*/
    UINT32 pad4[13];
    UINT32 imr;        	/*0xd_3060*/
    UINT32 isr;        	/*0xd_3064*/
    UINT32 pad5;       	/*0xd_3068*/
    UINT32 ifqdpar;		/*0xd_306c*/
    UINT32 pad6;       	/*0xd_3070*/
    UINT32 ifqepar;    	/*0xd_3074*/
    UINT32 pad7[226];
    UINT32 odmr;       	/*0xd_3400*/
    UINT32 odsr;       	/*0xd_3404*/
    UINT32 pad71[4];
    UINT32 oddpr;      	/*0xd_3418*/
    UINT32 oddatr;     	/*0xd_341c*/
    UINT32 pad72[3];
    UINT32 odretcr;    	/*0xd_342c*/
    UINT32 pad73[12];
    UINT32 dmr;        	/*0xd_3460*/
    UINT32 dsr;        	/*0xd_3464*/
    UINT32 pad8;
    UINT32 dqdpar;		/*0xd_346c*/
    UINT32 pad9;
    UINT32 dqepar;		/*0xd_3474*/
    UINT32 pad10[26];
    UINT32 pwmr;		/*0xd_34e0*/
    UINT32 pwsr;		/*0xd_34e4*/
    UINT32 pad11;
    UINT32 pwqbar;		/*0xd_34ec*/
}rio_msg_map;


/* function declare */
void msgFlowCntr(UINT32 message);
int riomsgsend(UINT32 dest_id, UINT32 s_mbox,  UINT32 d_mbox, UINT32 buffer, UINT32 len);
int srioMsgSetup(void);



#ifdef _cplusplus
}
#endif

#endif
