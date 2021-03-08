#ifndef _MAIN_VARIABLE_
#define _MAIN_VARIABLE_
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************/
#define doubleDATA
#undef intDATA

extern UINT64 testPoint_tmp,testPoint_tmp1,testPoint_tmp2;
extern int RS_switchINcmd,RS_switch_DT_BTcmd,RS_switchOUTcmd;
extern int writecounter;
extern UINT32 time1,time2,time3,cpufreq,timetest;;
extern float timer_realPeriod,work_time;


struct TX_7600_STRUCT
{
	short	boardID;
	short	liveCnt;
	short	short_variable[10];	 
	int		int_variable[10];	 
	float 	float_variable[10];	 	
};
struct RX_7600_STRUCT
{
	short	boardID;
	short	liveCnt;
	short	short_variable[10];	 
	int		int_variable[10];	 
	float 	float_variable[10];	 	
};

#pragma pack(1)
struct RTLAB_SEND_DATA
   {
    short dev_id;
    int   msg_id;
    short msg_len;
 //   int   data[64];  //test 2019 3 4
    double data[64];
   }; 

struct RTLAB_REC_DATA
   {
    short dev_id;
    int   msg_id;
    short msg_len;
 //   int   data[64];  //test 2019 3 4
    double data[64];
   }; 

#pragma pack()

#define SWAP16(x) ((((x) & 0x000000ff) << 24) |   \
        (((x) & 0x0000ff00) <<  8) |   \
        (((x) & 0x00ff0000) >>  8) |   \
        (((x) & 0xff000000) >> 24))

#define	UINT64 unsigned long long

#define SWAP64(x) (UINT64)((((UINT64)x & 0x00000000000000ff) << 56) |   \
				(((UINT64)x & 0x000000000000ff00) <<  40) |   \
				(((UINT64)x & 0x0000000000ff0000) <<  24) |   \
				(((UINT64)x & 0x00000000ff000000) << 	8)	|	\
				(((UINT64)x & 0x000000ff00000000) >>  8)  |	\
				(((UINT64)x & 0x0000ff0000000000) >> 24)  |	\
				(((UINT64)x & 0x00ff000000000000) >> 40)  |	\
				(((UINT64)x & 0xff00000000000000) >> 56) )
        

#define swab64(x)  ((UINT64)((((UINT64)(x)& (UINT64)0x00000000000000ffULL) << 56) | \
				 (((UINT64)(x)& (UINT64)0x000000000000ff00ULL) << 40) | \
				 (((UINT64)(x)& (UINT64)0x0000000000ff0000ULL) << 24) | \
				 (((UINT64)(x)& (UINT64)0x00000000ff000000ULL) << 8) | \
				 (((UINT64)(x)& (UINT64)0x000000ff00000000ULL) >> 8) | \
				 (((UINT64)(x)& (UINT64)0x0000ff0000000000ULL) >> 24) | \
				 (((UINT64)(x)& (UINT64)0x00ff000000000000ULL) >> 40) | \
				 (((UINT64)(x)& (UINT64)0xff00000000000000ULL) >> 56) ))

		
extern struct TX_7600_STRUCT tx_7600_data;
extern struct RX_7600_STRUCT *rx_7600_data_pointer;
extern struct RX_7600_STRUCT rx_7600_data;

extern struct RTLAB_SEND_DATA *RTLAB_dataout_p;/*add lhc for receive data from rtlab*/
/*************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif
