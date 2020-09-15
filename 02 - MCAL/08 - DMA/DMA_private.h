/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v02                                */
 /* date        : 14/9/2020                          */
/*****************************************************/
#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H

/******** Rigester defintions *********/
typedef struct {
	volatile u32 CCR ;
	volatile u32 CNDTR ;
	volatile u32 CPAR ;
	volatile u32 CMAR ;
	volatile u32 RES ; 
}DMA_channel_t;

typedef struct {
	volatile u32 ISR ;
	volatile u32 IFCR ;
	DMA_channel_t  CH[7];
}DMA_t;

#define   DMA   ((volatile DMA_t *) 0x40020000 )

/************ Rigester BITS ***********/

/***** ISR/IFCR  *****/
#define     DMA_GIF1        0
#define     DMA_TCIF1       1
#define     DMA_HTIF1       2 
#define     DMA_TEIF1       3
#define     DMA_GIF2        4
#define     DMA_TCIF2       5
#define     DMA_HTIF2       6
#define     DMA_TEIF2       7

#define     DMA_GIF3        8
#define     DMA_TCIF3       9
#define     DMA_HTIF3       10
#define     DMA_TEIF3       11

#define     DMA_GIF4       12
#define     DMA_TCIF4       13
#define     DMA_HTIF4       14
#define     DMA_TEIF4       15

#define     DMA_GIF5       16
#define     DMA_TCIF5       17
#define     DMA_HTIF5       18
#define     DMA_TEIF5       19

#define     DMA_GIF6        20
#define     DMA_TCIF6       21
#define     DMA_HTIF6       22
#define     DMA_TEIF6       23

#define     DMA_GIF7        24
#define     DMA_TCIF7       25
#define     DMA_HTIF7       26
#define     DMA_TEIF7       27


/***** CCR  *****/
#define     DMA_EN          0
#define     DMA_TCIE        1
#define     DMA_HTIE        2
#define     DMA_TEIE        3
#define     DMA_DIR         4
#define     DMA_CIRC        5
#define     DMA_PINC        6
#define     DMA_MINC        7
#define     DMA_PSIZE0      8
#define     DMA_PSIZE1      9
#define     DMA_MSIZE0      10
#define     DMA_MSIZE1      11
#define     DMA_PL0         12
#define     DMA_PL1         13
#define     DMA_MEM2MEM     14

#endif
