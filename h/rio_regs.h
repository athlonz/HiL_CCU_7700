#ifndef _INCrioregsh
#define _INCrioregsh

#ifdef _cplusplus
extern "C" {
#endif
	
typedef unsigned int UINT32;

typedef struct ccsr_srio
{
	UINT32 didcar; /* 0xc0000 - Device Identity Capability Register */
	UINT32 dicar; /* 0xc0004 - Device Information Capability Register */
	UINT32 aidcar; /* 0xc0008 - Assembly Identity Capability Register */
	UINT32 aicar; /* 0xc000c - Assembly Information Capability Register */
	UINT32 pefcar; /* 0xc0010 - Processing Element Features Capability Register */
	UINT32 spicar_x; /* 0xc0014 - Switch Port Information Capability Register */
	UINT32 socar; /* 0xc0018 - Source Operations Capability Register */
	UINT32 docar; /* 0xc001c - Destination Operations Capability Register */
	char res1[32];
	UINT32 msr_x; /* 0xc0040 - Mailbox Command And Status Register */
	UINT32 pwdcsr_x; /* 0xc0044 - Port-Write and Doorbell Command And Status Register */
	char res2[4];
	UINT32 pellccsr; /* 0xc004c - Processing Element Logic Layer Control Command and Status Register */
	char res3[12];
	UINT32 lcsbacsr; /* 0xc005c - Local Configuration Space Base Address Command and Status Register */
	UINT32 bdidcsr; /* 0xc0060 - Base Device ID Command and Status Register */
	char res4[4];
	UINT32 hbdidlcsr; /* 0xc0068 - Host Base Device ID Lock Command and Status Register */
	UINT32 ctcsr; /* 0xc006c - Component Tag Command and Status Register */
	char res5[144];
	UINT32 pmbh0csr; /* 0xc0100 - 8/16 LP-LVDS Port Maintenance Block Header 0 Command and Status Register */
	char res6[28];
	UINT32 pltoccsr; /* 0xc0120 - Port Link Time-out Control Command and Status Register */
	UINT32 prtoccsr; /* 0xc0124 - Port Response Time-out Control Command and Status Register */
	char res7[20];
	UINT32 pgccsr; /* 0xc013c - Port General Command and Status Register */
	UINT32 p0lmreqcsr; /* 0xc0140 - Port Link Maintenance Request Command and Status Register */
	UINT32 p0lmrespcsr; /* 0xc0144 - Port Link Maintenance Response Command and Status Register */
	UINT32 p0lascsr; /* 0xc0148 - Port Local Ackid Status Command and Status Register */
	char res8[12];
	UINT32 p0escsr; /* 0xc0158 - Port Error and Status Command and Status Register */
	UINT32 p0ccsr; /* 0xc015c - Port Control Command and Status Register */
	char res9[1184];
	UINT32 erbh; /*0xc0600*/
	char res9b[4];
	UINT32 ltledcsr; /*0xc0608*/
	UINT32 ltleecsr; /*0xc060c*/
	char res9c[4];
	UINT32 ltlaccsr; /*0xc0614*/
	UINT32 ltldidccsr; /*0xc0618*/
	UINT32 ltlcccsr; /*0xc061c*/
	char res9d[32];
	UINT32 p0edcsr; /*0xc0640*/
	char res9e[63932];

	UINT32 cr; /* 0xd0000 - Port Control Command and Status Register */
	char res10[12];
	UINT32 pcr; /* 0xd0010 - Port Configuration Register */
	UINT32 peir; /* 0xd0014 - Port Error Injection Register */
	char res11a[264];
	UINT32 pptaacr; /* 0xd0120 - accept all */
	char res11b[2780];
	UINT32 rowtar0; /* 0xd0c00 - RapidIO Outbound Window Translation Address Register 0 */
	UINT32 rowetar0;
	char res12[8];
	UINT32 rowar0; /* 0xd0c10 - RapidIO Outbound Attributes Register 0 */
	char res13[12];
	UINT32 rowtar1; /* 0xd0c20 - RapidIO Outbound Window Translation Address Register 1 */
	UINT32 rowetar1;
	UINT32 rowbar1; /* 0xd0c28 - RapidIO Outbound Window Base Address Register 1 */
	char res15[4];
	UINT32 rowar1; /* 0xd0c30 - RapidIO Outbound Attributes Register 1 */
	UINT32 rows1r1; /* 0xd0c34 - RapidIO Outbound Window Segment 1 Register 1 */
	UINT32 rows2r1; /* 0xd0c38 - RapidIO Outbound Window Segment 2 Register 1 */
	UINT32 rows3r1; /* 0xd0c3c - RapidIO Outbound Window Segment 3 Register 1 */
	UINT32 rowtar2; /* 0xd0c40 - RapidIO Outbound Window Translation Address Register 2 */
	char res17[4];
	UINT32 rowbar2; /* 0xd0c48 - RapidIO Outbound Window Base Address Register 2 */
	char res18[4];
	UINT32 rowar2; /* 0xd0c50 - RapidIO Outbound Attributes Register 2 */
	UINT32 rows1r2; /* 0xd0c54 - RapidIO Outbound Window Segment 1 Register 2 */
	UINT32 rows2r2; /* 0xd0c58 - RapidIO Outbound Window Segment 2 Register 2 */
	UINT32 rows3r2; /* 0xd0c5c - RapidIO Outbound Window Segment 3 Register 2 */
	UINT32 rowtar3; /* 0xd0c60 - RapidIO Outbound Window Translation Address Register 3 */
	char res20[4];
	UINT32 rowbar3; /* 0xd0c68 - RapidIO Outbound Window Base Address Register 3 */
	char res21[4];
	UINT32 rowar3; /* 0xd0c70 - RapidIO Outbound Attributes Register 3 */
	UINT32 rows1r3; /* 0xd0c74 - RapidIO Outbound Window Segment 1 Register 3 */
	UINT32 rows2r3; /* 0xd0c78 - RapidIO Outbound Window Segment 2 Register 3 */
	UINT32 rows3r3; /* 0xd0c7c - RapidIO Outbound Window Segment 3 Register 3 */
	UINT32 rowtar4; /* 0xd0c80 - RapidIO Outbound Window Translation Address Register 4 */
	char res23[4];
	UINT32 rowbar4; /* 0xd0c88 - RapidIO Outbound Window Base Address Register 4 */
	char res24[4];
	UINT32 rowar4; /* 0xd0c90 - RapidIO Outbound Attributes Register 4 */
	UINT32 rows1r4; /* 0xd0c94 - RapidIO Outbound Window Segment 1 Register 4 */
	UINT32 rows2r4; /* 0xd0c98 - RapidIO Outbound Window Segment 2 Register 4 */
	UINT32 rows3r4; /* 0xd0c9c - RapidIO Outbound Window Segment 3 Register 4 */
	UINT32 rowtar5; /* 0xd0ca0 - RapidIO Outbound Window Translation Address Register 5 */
	char res26[4];
	UINT32 rowbar5; /* 0xd0ca8 - RapidIO Outbound Window Base Address Register 5 */
	char res27[4];
	UINT32 rowar5; /* 0xd0cb0 - RapidIO Outbound Attributes Register 5 */
	UINT32 rows1r5; /* 0xd0cb4 - RapidIO Outbound Window Segment 1 Register 5 */
	UINT32 rows2r5; /* 0xd0cb8 - RapidIO Outbound Window Segment 2 Register 5 */
	UINT32 rows3r5; /* 0xd0cbc - RapidIO Outbound Window Segment 3 Register 5 */
	UINT32 rowtar6; /* 0xd0cc0 - RapidIO Outbound Window Translation Address Register 6 */
	char res29[4];
	UINT32 rowbar6; /* 0xd0cc8 - RapidIO Outbound Window Base Address Register 6 */
	char res30[4];
	UINT32 rowar6; /* 0xd0cd0 - RapidIO Outbound Attributes Register 6 */
	UINT32 rows1r6; /* 0xd0cd4 - RapidIO Outbound Window Segment 1 Register 6 */
	UINT32 rows2r6; /* 0xd0cd8 - RapidIO Outbound Window Segment 2 Register 6 */
	UINT32 rows3r6; /* 0xd0cdc - RapidIO Outbound Window Segment 3 Register 6 */
	UINT32 rowtar7; /* 0xd0ce0 - RapidIO Outbound Window Translation Address Register 7 */
	char res32[4];
	UINT32 rowbar7; /* 0xd0ce8 - RapidIO Outbound Window Base Address Register 7 */
	char res33[4];
	UINT32 rowar7; /* 0xd0cf0 - RapidIO Outbound Attributes Register 7 */
	UINT32 rows1r7; /* 0xd0cf4 - RapidIO Outbound Window Segment 1 Register 7 */
	UINT32 rows2r7; /* 0xd0cf8 - RapidIO Outbound Window Segment 2 Register 7 */
	UINT32 rows3r7; /* 0xd0cfc - RapidIO Outbound Window Segment 3 Register 7 */
	UINT32 rowtar8; /* 0xd0d00 - RapidIO Outbound Window Translation Address Register 8 */
	UINT32 rowetar8;
	UINT32 rowbar8; /* 0xd0d08 - RapidIO Outbound Window Base Address Register 8 */
	char res36[4];
	UINT32 rowar8; /* 0xd0d10 - RapidIO Outbound Attributes Register 8 */
	UINT32 rows1r8; /* 0xd0d14 - RapidIO Outbound Window Segment 1 Register 8 */
	UINT32 rows2r8; /* 0xd0d18 - RapidIO Outbound Window Segment 2 Register 8 */
	UINT32 rows3r8; /* 0xd0d1c - RapidIO Outbound Window Segment 3 Register 8 */
	char res37[64];
	UINT32 riwtar4; /* 0xd0d60 - RapidIO Inbound Window Translation Address Register 4 */
	char res38[4];
	UINT32 riwbar4; /* 0xd0d68 - RapidIO Inbound Window Base Address Register 4 */
	char res39[4];
	UINT32 riwar4; /* 0xd0d70 - RapidIO Inbound Attributes Register 4 */
	char res40[12];
	UINT32 riwtar3; /* 0xd0d80 - RapidIO Inbound Window Translation Address Register 3 */
	char res41[4];
	UINT32 riwbar3; /* 0xd0d88 - RapidIO Inbound Window Base Address Register 3 */
	char res42[4];
	UINT32 riwar3; /* 0xd0d90 - RapidIO Inbound Attributes Register 3 */
	char res43[12];
	UINT32 riwtar2; /* 0xd0da0 - RapidIO Inbound Window Translation Address Register 2 */
	char res44[4];
	UINT32 riwbar2; /* 0xd0da8 - RapidIO Inbound Window Base Address Register 2 */
	char res45[4];
	UINT32 riwar2; /* 0xd0db0 - RapidIO Inbound Attributes Register 2 */
	char res46[12];
	UINT32 riwtar1; /* 0xd0dc0 - RapidIO Inbound Window Translation Address Register 1 */
	char res47[4];
	UINT32 riwbar1; /* 0xd0dc8 - RapidIO Inbound Window Base Address Register 1 */
	char res48[4];
	UINT32 riwar1; /* 0xd0dd0 - RapidIO Inbound Attributes Register 1 */
	char res49[12];
	UINT32 riwtar0; /* 0xd0de0 - RapidIO Inbound Window Translation Address Register 0 */
	char res50[12];
	UINT32 riwar0; /* 0xd0df0 - RapidIO Inbound Attributes Register 0 */
	char res51[12];
	
	UINT32 p2rowtar0; /* 0xd0e00 - RapidIO Outbound Window Translation Address Register 0 */
	UINT32 p2rowetar0; /* 0xd0e04 */
	char p2res12[8];
	UINT32 p2rowar0; /* 0xd0e10 - RapidIO Outbound Attributes Register 0 */
	char p2res13[12];
	UINT32 p2rowtar1; /* 0xd0e20 - RapidIO Outbound Window Translation Address Register 1 */
	UINT32 p2rowetar1; /* 0xd0e24 */
	UINT32 p2rowbar1; /* 0xd0e28 - RapidIO Outbound Window Base Address Register 1 */
	char p2res15[4];
	UINT32 p2rowar1; /* 0xd0e30 - RapidIO Outbound Attributes Register 1 */
	UINT32 p2rows1r1; /* 0xd0e34 - RapidIO Outbound Window Segment 1 Register 1 */
	UINT32 p2rows2r1; /* 0xd0e38 - RapidIO Outbound Window Segment 2 Register 1 */
	UINT32 p2rows3r1; /* 0xd0e3c - RapidIO Outbound Window Segment 3 Register 1 */
	UINT32 p2rowtar2; /* 0xd0e40 - RapidIO Outbound Window Translation Address Register 2 */
	UINT32 p2rowetar2; /* 0xd0e44 */
	UINT32 p2rowbar2; /* 0xd0e48 - RapidIO Outbound Window Base Address Register 2 */
	char p2res18[4];
	UINT32 p2rowar2; /* 0xd0e50 - RapidIO Outbound Attributes Register 2 */
	UINT32 p2rows1r2; /* 0xd0e54 - RapidIO Outbound Window Segment 1 Register 2 */
	UINT32 p2rows2r2; /* 0xd0e58 - RapidIO Outbound Window Segment 2 Register 2 */
	UINT32 p2rows3r2; /* 0xd0e5c - RapidIO Outbound Window Segment 3 Register 2 */
	UINT32 p2rowtar3; /* 0xd0e60 - RapidIO Outbound Window Translation Address Register 3 */
	UINT32 p2rowetar3; /* 0xd0e64 */
	UINT32 p2rowbar3; /* 0xd0e68 - RapidIO Outbound Window Base Address Register 3 */
	char p2res21[4];
	UINT32 p2rowar3; /* 0xd0e70 - RapidIO Outbound Attributes Register 3 */
	UINT32 p2rows1r3; /* 0xd0e74 - RapidIO Outbound Window Segment 1 Register 3 */
	UINT32 p2rows2r3; /* 0xd0e78 - RapidIO Outbound Window Segment 2 Register 3 */
	UINT32 p2rows3r3; /* 0xd0e7c - RapidIO Outbound Window Segment 3 Register 3 */
	UINT32 p2rowtar4; /* 0xd0e80 - RapidIO Outbound Window Translation Address Register 4 */
	UINT32 p2rowetar4; /* 0xd0e84 */
	UINT32 p2rowbar4; /* 0xd0c88 - RapidIO Outbound Window Base Address Register 4 */
	char p2res24[4];
	UINT32 p2rowar4; /* 0xd0e90 - RapidIO Outbound Attributes Register 4 */
	UINT32 p2rows1r4; /* 0xd0e94 - RapidIO Outbound Window Segment 1 Register 4 */
	UINT32 p2rows2r4; /* 0xd0e98 - RapidIO Outbound Window Segment 2 Register 4 */
	UINT32 p2rows3r4; /* 0xd0e9c - RapidIO Outbound Window Segment 3 Register 4 */
	UINT32 p2rowtar5; /* 0xd0ca0 - RapidIO Outbound Window Translation Address Register 5 */
	UINT32 p2rowetar5; /* 0xd0ca4 */
	UINT32 p2rowbar5; /* 0xd0ca8 - RapidIO Outbound Window Base Address Register 5 */
	char p2res27[4];
	UINT32 p2rowar5; /* 0xd0eb0 - RapidIO Outbound Attributes Register 5 */
	UINT32 p2rows1r5; /* 0xd0eb4 - RapidIO Outbound Window Segment 1 Register 5 */
	UINT32 p2rows2r5; /* 0xd0eb8 - RapidIO Outbound Window Segment 2 Register 5 */
	UINT32 p2rows3r5; /* 0xd0ebc - RapidIO Outbound Window Segment 3 Register 5 */
	UINT32 p2rowtar6; /* 0xd0ec0 - RapidIO Outbound Window Translation Address Register 6 */
	UINT32 p2rowetar6;  /* 0xd0ec4 */
	UINT32 p2rowbar6; /* 0xd0ec8 - RapidIO Outbound Window Base Address Register 6 */
	char p2res30[4];
	UINT32 p2rowar6; /* 0xd0ed0 - RapidIO Outbound Attributes Register 6 */
	UINT32 p2rows1r6; /* 0xd0ed4 - RapidIO Outbound Window Segment 1 Register 6 */
	UINT32 p2rows2r6; /* 0xd0ed8 - RapidIO Outbound Window Segment 2 Register 6 */
	UINT32 p2rows3r6; /* 0xd0edc - RapidIO Outbound Window Segment 3 Register 6 */
	UINT32 p2rowtar7; /* 0xd0ee0 - RapidIO Outbound Window Translation Address Register 7 */
	UINT32 p2rowetar7; /* 0xd0ee4 */
	UINT32 p2rowbar7; /* 0xd0ee8 - RapidIO Outbound Window Base Address Register 7 */
	char p2res33[4];
	UINT32 p2rowar7; /* 0xd0ef0 - RapidIO Outbound Attributes Register 7 */
	UINT32 p2rows1r7; /* 0xd0ef4 - RapidIO Outbound Window Segment 1 Register 7 */
	UINT32 p2rows2r7; /* 0xd0ef8 - RapidIO Outbound Window Segment 2 Register 7 */
	UINT32 p2rows3r7; /* 0xd0efc - RapidIO Outbound Window Segment 3 Register 7 */
	UINT32 p2rowtar8; /* 0xd0f00 - RapidIO Outbound Window Translation Address Register 8 */
	UINT32 p2rowetar8; /* 0xd0f04 */
	UINT32 p2rowbar8; /* 0xd0f08 - RapidIO Outbound Window Base Address Register 8 */
	char p2res36[4];
	UINT32 p2rowar8; /* 0xd0f10 - RapidIO Outbound Attributes Register 8 */
	UINT32 p2rows1r8; /* 0xd0d14 - RapidIO Outbound Window Segment 1 Register 8 */
	UINT32 p2rows2r8; /* 0xd0d18 - RapidIO Outbound Window Segment 2 Register 8 */
	UINT32 p2rows3r8; /* 0xd0d1c - RapidIO Outbound Window Segment 3 Register 8 */
	char p2res37[64];
	UINT32 p2riwtar4; /* 0xd0f60 - RapidIO Inbound Window Translation Address Register 4 */
	char p2res38[4];
	UINT32 p2riwbar4; /* 0xd0f68 - RapidIO Inbound Window Base Address Register 4 */
	char p2res39[4];
	UINT32 p2riwar4; /* 0xd0f70 - RapidIO Inbound Attributes Register 4 */
	char p2res40[12];
	UINT32 p2riwtar3; /* 0xd0f80 - RapidIO Inbound Window Translation Address Register 3 */
	char p2res41[4];
	UINT32 p2riwbar3; /* 0xd0f88 - RapidIO Inbound Window Base Address Register 3 */
	char p2res42[4];
	UINT32 p2riwar3; /* 0xd0f90 - RapidIO Inbound Attributes Register 3 */
	char p2res43[12];
	UINT32 p2riwtar2; /* 0xd0fa0 - RapidIO Inbound Window Translation Address Register 2 */
	char p2res44[4];
	UINT32 p2riwbar2; /* 0xd0fa8 - RapidIO Inbound Window Base Address Register 2 */
	char p2res45[4];
	UINT32 p2riwar2; /* 0xd0fb0 - RapidIO Inbound Attributes Register 2 */
	char p2res46[12];
	UINT32 p2riwtar1; /* 0xd0fc0 - RapidIO Inbound Window Translation Address Register 1 */
	char p2res47[4];
	UINT32 p2riwbar1; /* 0xd0dc8 - RapidIO Inbound Window Base Address Register 1 */
	char p2res48[4];
	UINT32 p2riwar1; /* 0xd0fd0 - RapidIO Inbound Attributes Register 1 */
	char p2res49[12];
	UINT32 p2riwtar0; /* 0xd0fe0 - RapidIO Inbound Window Translation Address Register 0 */
	char p2res50[12];
	UINT32 p2riwar0; /* 0xd0ff0 - RapidIO Inbound Attributes Register 0 */	
	char p2res51[12];
	
	char res54c[8192];
#if 0	
	UINT32 pnfedr; /* 0xd0e00 - Port Notification/Fatal Error Detect Register */
	UINT32 pnfedir; /* 0xd0e04 - Port Notification/Fatal Error Detect Register */
	UINT32 pnfeier; /* 0xd0e08 - Port Notification/Fatal Error Interrupt Enable Register */
	UINT32 pecr; /* 0xd0e0c - Port Error Control Register */
	UINT32 pepcsr0; /* 0xd0e10 - Port Error Packet/Control Symbol Register 0 */
	UINT32 pepr1; /* 0xd0e14 - Port Error Packet Register 1 */
	UINT32 pepr2; /* 0xd0e18 - Port Error Packet Register 2 */
	char res52[4];
	UINT32 predr; /* 0xd0e20 - Port Recoverable Error Detect Register */
	char res53[4];
	UINT32 pertr; /* 0xd0e28 - Port Error Recovery Threshold Register */
	UINT32 prtr; /* 0xd0e2c - Port Retry Threshold Register */
	/*Changes by lorraine, 22nd March */
	/*//char	res54[464];
	 */
	char res54a[216];
	UINT32 pdedr; /*d0f08 */
	UINT32 pdedir; /*d0f0c */
	char res54b[240];
	/*end of these changes by lorraine */
	char res54c[8192];
#endif	
	UINT32 om0mr; /* 0xd3000 - Outbound Mode Register */
	UINT32 om0sr; /* 0xd3004 - Outbound Status Register */
	UINT32 om0edqdpar; /* 0xd3008 - Extended Outbound Descriptor Queue Tail Pointer Address Register */
	UINT32 om0dqdpar; /* 0xd300c - Outbound Descriptor Queue Tail Pointer Address Register */
	UINT32 om0eosar; /* 0xd3010 - Extended Outbound Unit Source Address Register */
	UINT32 om0sar; /* 0xd3014 - Outbound Unit Source Address Register */
	UINT32 om0dpr; /* 0xd3018 - Outbound Destination Port Register */
	UINT32 om0datr; /* 0xd301c - Outbound Destination Attributes Register */
	UINT32 om0dcr; /* 0xd3020 - Outbound Doubleword Count Register */
	UINT32 om0edqepar; /* 0xd3024 - Extended Outbound Descriptor Queue Head Pointer Address Register */
	UINT32 om0dqepar; /* 0xd3028 - Outbound Descriptor Queue Head Pointer Address Register */
	UINT32 om0retcr; /* 0xd302c - Outbound Message 0 Retry Error Threshold */
	UINT32 om0mgr; /* 0xd3030 - Outbound message 0 Multicast Group Register*/
	UINT32 om0mlr; /* 0xd3034 - Outbound Message 0 Multicast List REgister */
	char res55[40];
	UINT32 im0mr; /* 0xd3060 - Outbound Mode Register */
	UINT32 im0sr; /* 0xd3064 - Inbound Status Register */
	UINT32 im0efqdpar; /* 0xd3068 - Extended Inbound Descriptor Queue Tail Pointer Address Register */
	UINT32 im0fqdpar; /* 0xd306c - Inbound Descriptor Queue Tail Pointer Address Register */
	UINT32 im0efqepar; /* 0xd3070 - Extended Inbound Frame Queue Head Pointer Address Register */
	UINT32 im0fqepar; /* 0xd3074 - Inbound Frame Queue Head Pointer Address Register */
	char res56[904];
	UINT32 od0mr; /* 0xd3400 */
	UINT32 od0sr; /* 0xd3404 */
	char res57[16];
	UINT32 od0dpr; /* 0xd3418 */
	UINT32 od0datr; /* 0xd341c */
	char res58[12];
	UINT32 od0retcr; /* 0xd342c */
	char res59[48];
	UINT32 id0mr; /* 0xd3460 */
	UINT32 id0sr; /* 0xd3464 */
	UINT32 eid0qdpar; /* 0xd3468 */
	UINT32 id0qdpar; /* 0xd346c */
	UINT32 eid0qepar; /* 0xd3470 */
	UINT32 id0qepar; /* 0xd3474 */
	UINT32 id0mirir; /* 0xd3478 */
	char res60[100];
	UINT32 ipw0mr; /* 0xd34e0 */
	UINT32 ipw0sr; /* 0xd34e4 */
	UINT32 eipw0qbar; /* 0xd34e8 */
	UINT32 ipw0qbar; /* 0xd34ec */
	char res61[51984];
} ccsr_srio_t;

/*//#define	NULL          ((void *) 0)

 #define TRUE           1
 #define FALSE          0*/

/* Error Codes */
#define SUCCESS                 0       /* successful return code */
/* Return when there is another host which has bigger power-on Device ID */
#define ERROR_BAD_TRANSACTION  -1
#define ERROR_SLAVE            -2       /* slave device */
#define ERR_LOCK               -3       /* device has been locked by another host */
#define ERR_INVALID_PARAMETER  -4       /* invalid input paramenters */

/* RIO transaction types */
#define RIO_MREAD       7       /* RIO maintenance read */
#define RIO_MWRITE      RIO_MREAD       /* RIO maintenance write */
#define RIO_NREAD       4       /* RIO Normal read */
#define RIO_NWRITE      RIO_NREAD       /* RIO Normal write */

/* RIO Transaction flow */
#define MEDIUM_LEVEL    1

#define RIO_ROWTAR1                                   0xD0C20
#define   ROW_DEV_ID_Mask                             0x3FC00000
#define   ROW_DEV_ID_Shift                            22
#define   ROW_TEA_Mask                                0x00300000
#define   ROW_TEA_Shift                               20
#define   ROW_HOPCNT_Mask                             0x000FF000       /* maintenance only */
#define   ROW_HOPCNT_Shift                            12
#define   ROW_OFS_Mask                                0x00000FFF       /* maintenance only */
#define   ROW_OFS_Shift                               0
#define   ROW_TA_Mask                                 0x000FFFFF
#define   ROW_TA_Shift                                0
/* For maintenance configuration read/write offset conversion */
#define   ROW_OFF2CO(x)  (((x)>>ROW_OFS_Shift)&ROW_OFS_Mask)   /* regOffset to configOffset */
#define   ROW_CO2OFF(x)  (((x)&ROW_OFS_Mask)<<ROW_OFS_Shift)   /* configOffset to regOffset */
/* For normal read/write address conversion */
#define   ROW_ADDR2TA(x) (((x)>>12)&ROW_TA_Mask)
#define   ROW_TA2ADDR(x) (((x)&ROW_TA_Mask)<<12)
#define RIO_ROWBAR1                                   0xD0C28
#define   ROW_BEA_Mask                                0x00F00000
#define   ROW_BEA_Shift                               20
#define   ROW_BA_Mask                                 0x000FFFFF
#define   ROW_BA_Shift                                0
#define   ROW_ADDR2BA(x) (((x)>>12)&ROW_BA_Mask)
#define   ROW_BA2ADDR(x) (((x)&ROW_BA_Mask)<<12)
#define RIO_ROWAR1                                    0xD0C30
#define   ROW_En_Mask                                 0x80000000
#define   ROW_En_Shift                                31
#define   ROW_Tflowlvl_Mask                           0x0C000000
#define   ROW_Tflowlvl_Shift                          26
#define   ROW_pci_order_Mask                          0x02000000
#define   ROW_pci_order_Shift                         25
#define   ROW_ReadTType_Mask                          0x000F0000
#define   ROW_ReadTType_Shift                         16
#define   ROW_WriteTType_Mask                         0x0000F000
#define   ROW_WriteTType_Shift                        12
#define   ROW_WindSize_Mask                           0x0000003F
#define   ROW_WindSize_Shift                          0
#define RIO_RIWTAR1                                   0xD0DC0
#define   RIW_TEA_Mask                                0x00F00000
#define   RIW_TEA_Shift                               20
#define   RIW_TA_Mask                                 0x000FFFFF
#define   RIW_TA_Shift                                0
#define RIO_RIWBAR1                                   0xD0DC8
#define   RIW_BEA_Mask                                0x00300000
#define   RIW_BEA_Shift                               20
#define   RIW_BA_Mask                                 0x000FFFFF
#define   RIW_BA_Shift                                0
#define RIO_RIWAR1                                    0xD0DD0
#define   RIW_En_Mask                                 0x80000000
#define   RIW_En_Shift                                31
#define   RIW_TgtInt_Mask                             0x00F00000
#define   RIW_TgtInt_Shift                            20
#define   RIW_ReadTType_Mask                          0x000F0000
#define   RIW_ReadTType_Shift                         16
#define   RIW_WriteTType_Mask                         0x0000F000
#define   RIW_WriteTType_Shift                        12
#define   RIW_WindSize_Mask                           0x0000003F
#define   RIW_WindSize_Shift                          0


#ifdef _cplusplus
}
#endif

#endif
