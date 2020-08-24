/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 24/8/2020                          */
/*****************************************************/
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

/* Struct for the EXTI regsiter mapping */
typedef struct {
	volatile u32 IMR   ;    /* Interrupt mask register            */
	volatile u32 EMR   ;    /* Event mask register                */
	volatile u32 RTSR  ;    /* Rising trigger selection register  */
	volatile u32 FTSR  ;    /* Falling trigger selection register */
	volatile u32 SWIER ;    /* Software interrupt event register  */
	volatile u32 PR    ;    /* Pending register                   */
}EXTI_t;

#define EXTI  ((volatile EXTI_t *) 0x40010400)



#endif