/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 24/8/2020                          */
/*****************************************************/
#ifndef AFIO_PRIVATE_H
#define AFIO_PRIVATE_H

/* Struct for the AFIO regsiter mapping */
typedef struct {
	volatile u32 EVCR      ;    /* Event control register                       */
	volatile u32 MAPR      ;    /* remap and debug I/O configuration register   */
	volatile u32 EXTICR[4] ;    /* External interrupt configuration registers   */
	volatile u32 MAPR2     ;    /* remap and debug I/O configuration register2  */
}AFIO_t;


#define AFIO  ((volatile AFIO_t *) 0x40010000)



#endif