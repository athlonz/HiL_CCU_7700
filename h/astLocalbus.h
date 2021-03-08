#ifndef _AST_LOCAL_BUS_H_
#define _AST_LOCAL_BUS_H_

/* Enhanced local bus controller CS3 device address */
#define AST_LOCALBUS_FPGA_ADDR	0xf1000000

/* Enhanced local bus controller register address define */
#define AST_ELBC_REG_BASE_ADDR	( CCSBAR + 0x5000 )	/* Base address of localbus registers */


/* routine */

extern INT32 astLocalbusFpgaRead(
		INT32 offset, 
		INT32 *outbuffer, 
		INT32 length
		);


extern INT32 astLocalbusFpgaWrite(
		INT32 offset, 
		const INT32 *inbuffer, 
		INT32 length
		);

extern void astLocalbusFpgaInit(void);

#endif
