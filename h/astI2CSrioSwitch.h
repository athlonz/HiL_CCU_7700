#ifndef _AST_I2C_SRIO_SWITCH_H_
#define _AST_I2C_SRIO_SWITCH_H_

/* switch no */
#define AST_SRIO_SWITCH_1		0		/* switch 1 */
#define AST_SRIO_SWITCH_2		1		/* switch 2 */

/* the i2c bus address of switch device */
#define AST_SRIO_I2C_BUS_ADDR_1	0x7d	/* switch1 I2C bus address */
#define AST_SRIO_I2C_BUS_ADDR_2	0x7f	/* switch2 I2C bus address */


/* routine define */

extern STATUS astI2CSrioSwitchWrite(
		UINT32 AST_SRIO_SWITCH_x, 
		UINT32 regAddr, 
		UINT32 value
		);

extern STATUS astI2CSrioSwitchRead(
		UINT32 AST_SRIO_SWITCH_x, 
		UINT32 regAddr, 
		UINT32 *value
		);

#endif

