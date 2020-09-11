/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 10/9/2020                          */
/*****************************************************/
#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H


/* Array of the base address of each timer  */
volatile u32 *TIM [TIMER_NUMBER] =
{ (u32*)(0x40012C00) ,
  (u32*)(0x40000000) ,
  (u32*)(0x40000400) ,
  (u32*)(0x40000800)
};

/* Offset of each rigester */
#define    CR1      0
#define    CR2      1
#define    SMCR     2
#define    DIER     3
#define    SR       4
#define    EGR      5
#define    CCMR1    6
#define    CCMR2    7
#define    CCER     8
#define    CNT      9
#define    PSC      10
#define    ARR      11
#define    RCR      12
#define    CCR1     13
#define    CCR2     14
#define    CCR3     15
#define    CCR4     16
#define    BDTR     17
#define    DCR      18
#define    DMAR     19



#endif
