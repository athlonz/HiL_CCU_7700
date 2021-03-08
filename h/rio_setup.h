#ifndef _INCriosetuph
#define _INCriosetuph

#ifdef _cplusplus
extern "C" {
#endif
	
	
/*#define MAX_DEVICES_IN_SYSTEM   256*/

#define     LAW_ENCODED_SIZE_4KB          0x0000000B
#define     LAW_ENCODED_SIZE_8KB          0x0000000C
#define     LAW_ENCODED_SIZE_16KB         0x0000000D
#define     LAW_ENCODED_SIZE_32KB         0x0000000E
#define     LAW_ENCODED_SIZE_64KB         0x0000000F
#define     LAW_ENCODED_SIZE_128KB        0x00000010
#define     LAW_ENCODED_SIZE_256KB        0x00000011
#define     LAW_ENCODED_SIZE_512KB        0x00000012
#define     LAW_ENCODED_SIZE_1MB          0x00000013
#define     LAW_ENCODED_SIZE_2MB          0x00000014
#define     LAW_ENCODED_SIZE_4MB          0x00000015
#define     LAW_ENCODED_SIZE_8MB          0x00000016
#define     LAW_ENCODED_SIZE_16MB         0x00000017
#define     LAW_ENCODED_SIZE_32MB         0x00000018
#define     LAW_ENCODED_SIZE_64MB         0x00000019
#define     LAW_ENCODED_SIZE_128MB        0x0000001A
#define     LAW_ENCODED_SIZE_256MB        0x0000001B
#define     LAW_ENCODED_SIZE_512MB        0x0000001C
#define     LAW_ENCODED_SIZE_1GB          0x0000001D
#define     LAW_ENCODED_SIZE_2GB          0x0000001E 

/* struct define */	
typedef struct srio_ob
{
	UINT32 outboundNo;
	UINT32 outboundBase;
	UINT32 outboundAttr;
	UINT32 outboundTar;
	UINT32 targetID;
	UINT8 segment;
	UINT8 subsegment;
	UINT32 wrtyp;
	UINT32 size;
}srio_ob_t;

typedef struct srio_ib
{
	UINT32 inboundNo;
	UINT32 inboundBase;
	UINT32 inboundAttr;
	UINT32 inboundTar;
	UINT32 targetID;
	UINT32 size;
}srio_ib_t;


/* function declared */
int srio_ob_map(srio_ob_t srioOBound);
int srio_ob_map2(srio_ob_t srioOBound);
int srio_ib_map(srio_ib_t srioIBound);
int srio_ib_map2(srio_ib_t srioInBound);
int srioSetup(unsigned int ccsbar, unsigned int flag, unsigned int speed);
int srio_switch_route_set(UINT8 destid, UINT8 hopcount, UINT8 portnum, UINT16 id);
int srio_switch_port_status_get(UINT8 destid, UINT8 hopcount, UINT8 portnum, UINT32 *ptempVal);
int srio_devid_reset(int maxportnum, int destid, int hopcount, int *idtable);
int srio_port_set(UINT16 destid, UINT8 hopcount, UINT8 portnum, int *table);
int srioFindDevNumGet(void);


#ifdef _cplusplus
}
#endif

#endif
