/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 4/9/2020                          */
/*****************************************************/
#ifndef REMOTE_PRIVATE_H
#define REMOTE_PRIVATE_H


/* Setting up ISR number for NVIC and handler of the isr */
#if   REMOTE_EXTI_LINE == 0 
	#define   REMOTE_HANDLER        EXTI0_IRQHandler
	#define   REMOTE_NVIC_NUMBER    EXTI0_IRQ
	
#elif REMOTE_EXTI_LINE == 1
	#define   REMOTE_HANDLER        EXTI1_IRQHandler
	#define   REMOTE_NVIC_NUMBER    EXTI1_IRQ

#elif REMOTE_EXTI_LINE == 2
	#define   REMOTE_HANDLER        EXTI2_IRQHandler
	#define   REMOTE_NVIC_NUMBER    EXTI2_IRQ
	
#elif REMOTE_EXTI_LINE == 3
	#define   REMOTE_HANDLER        EXTI3_IRQHandler
	#define   REMOTE_NVIC_NUMBER    EXTI3_IRQ

#elif REMOTE_EXTI_LINE == 4
	#define   REMOTE_HANDLER        EXTI4_IRQHandler
	#define   REMOTE_NVIC_NUMBER    EXTI4_IRQ
	
#elif (REMOTE_EXTI_LINE  > 4) && (REMOTE_EXTI_LINE  < 10)
	#define   REMOTE_HANDLER        EXTI9_5_IRQHandler
	#define   REMOTE_NVIC_NUMBER    EXTI9_5_IRQ
	
#elif (REMOTE_EXTI_LINE  > 9) && (REMOTE_EXTI_LINE  < 16)
	#define   REMOTE_HANDLER        EXTI15_10_IRQHandler
	#define   REMOTE_NVIC_NUMBER    EXTI15_10_IRQ

#else 
	#error (" Configuration error ")
#endif


/* Frame bits */
#define  ADDRESS_BIT           0 
#define  ADDRESS_INVERTED_BIT  8
#define   DATA_BIT              16
#define  DATA_INVERTED_BIT     24

/* Errors */
#define   FRAME_CORRECT   1
#define   FRAME_ERROR     0

/* Buttons data ID */
#define     POWER            69
#define     MODE             70
#define     MUTE             71
#define     PLAY_RESUME      68
#define     RIGHT            64
#define     LEFT             67
#define     EQ               7
#define     VOLUME_DOWN      21
#define     VOLUME_UP        9
#define     ZERO             22
#define     RPT              25
#define     U_USD            13
#define     ONE              12
#define     TWO              24
#define     THREE            94
#define     FOUR             8
#define     FIVE             28
#define     SIX              90
#define     SEVEN            60
#define     EIGHT            82
#define     NINE             74

/******* Private functions prototypes ******/
static u8 REMOTE_u8CheckFrame(void);



#endif