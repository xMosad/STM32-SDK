/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 16/9/2020                          */
/*****************************************************/
/*
	Pre conditions : 
		1 - Enable RCC for used GPIO pins 
		2 - Enable RCC for use SPI
		3 - Configure pins of SPI as output and input
		4 - Enable NVIC in case of using interrupts	
*/


#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

/******************* Public data types *******************/

/**** Timer channels ****/
typedef enum {
	SPI1,
	SPI2,
	MAX_TIMERS
}SPI_Ch_t;


/*** Configuration parameters ***/
typedef struct {
	/* 1 for master  /   0 for slave  */
	u8  u8Mode;
	
	/* 1 Idle is high  /   0 Idle is low  */
	u8  u8CPOL ;
	
	/* 1 Read first  /   0 Write first  */
	u8  u8CPHA ;
	
	/* 1 for LSB first  /   0 for MSB first  */
	u8  u8FrameFormat ;
	
	/* 1 for 16-bit  /   0 for 8-bit  */
	u8  u8FrameSize   ;
	
	/* 1  S.W mange slave  /   0  H.W mange slave */
	u8  u8SSM ;
	
	/* 1 for Rexieve only  /   0 for Full duplex  */
	u8  u8TransmissonMode ;
	
	/*  (F / 2   )   ->   0   */
	/*  (F / 4   )   ->   1   */
	/*  (F / 8   )   ->   2   */
	/*  (F / 16  )   ->   3   */
	/*  (F / 32  )   ->   4   */
	/*  (F / 64  )   ->   5   */
	/*  (F / 128 )   ->   6   */
	/*  (F / 256 )   ->   7   */
	u8  u8Prescaler;
	
	/* 1 for Enable  /   0 for Disable  */
	u8 u8InterruptEnable ;
}SPI_config_t;


/********************* Prototypes **********************/

/* 
  * SPI_u8ConfigureCh - > Configure specific SPI module refere to SPI_config_t data type
  * I/P : SPI_Ch_t   /   pointer to SPI_config_t 
  * O/P : u8 (Error state)
*/
u8 SPI_u8ConfigureCh(SPI_Ch_t copy_channel , SPI_config_t *copy_config);

/* 
  * SPI_voidSendRecSynch - > Send and receive data by specific SPI module (Synchronous function) 
  * I/P : SPI_Ch_t   /   u16   /  pointer to u16 
  * Pre condition : Activate SS pin of slave
*/
u16 SPI_voidSendRecSynch (SPI_Ch_t copy_channel , u16 copy_u16SendData);

/* 
  * SPI_voidSendRecAsynch - > Send and receive data by specific SPI module (Asynchronous function)
  * I/P : SPI_Ch_t   /   u16   /  pointer to function (u16)
  * Pre condition : Activate SS pin of slave
*/
void SPI_voidSendRecAsynch (SPI_Ch_t copy_channel , u16 copy_u16SendData , void (*func)(u16));

#endif
