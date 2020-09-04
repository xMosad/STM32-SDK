/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v02                                */
 /* date        : 25/8/2020                          */
/*****************************************************/
#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

/* Struct for the AFIO regsiter mapping */
typedef struct {
	volatile u32 CTRL      ;    /* SysTick control and status register */
	volatile u32 LOAD      ;    /* SysTick reload value register       */
	volatile u32 VAL       ;    /* SysTick reload value register       */
	volatile u32 CALIB     ;    /* SysTick calibration value register  */
}STK_t;

#define STK  ((volatile STK_t *) 0xE000E010)

/********** Bits **********/
#define  STK_CTRL_ENABLE     0
#define  STK_CTRL_TICKINT    1
#define  STK_CTRL_CLKSOURCE  2
#define  STK_CTRL_COUNTFLAG  16

/******** Clk options ********/
#define   AHP          0
#define   AHP_BY_8     1

/****** interrupt options *******/
#define    ENABLE     1
#define    DISABLE    0



#endif