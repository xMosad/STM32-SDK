/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 10/9/2020                          */
/*****************************************************/

/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* module includes */
#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"

/*  Global variables  */
extern const TIMER_config_t configTable[TIMER_NUMBER];
void (* callBackFunc[TIMER_NUMBER])(void);

void TIMER_voidInit (void)
{
	for (TIMER_channels_t i = 0 ; i < MAX_TIMERS ; i++){
		/* Will only configure the time if enabled otherwise the rigseters 
		   will remain at the reset value */
		if (configTable[i].u8Enable){
			/* Disable timer */
			CLEAR_BIT ( *(TIM[i]+CR1)  , 0 );
			
			/* choose mode */
			switch (configTable[i].u8Mode) {
				case UP_COUNTER     :
					CLEAR_BIT ( *(TIM[i]+CR1)  , 4 );
					break ;
				case DOWN_COUNTER   :
					SET_BIT   ( *(TIM[i]+CR1)  , 4 );
					break ;
				default : 
					break;
			}
			
			/* Enable / disable interrupt for update  */
			/* Rest of interrups will be implemented later */
			if (configTable[i].u8InterruptEnable){
				SET_BIT   ( (*(TIM[i]+DIER))  , 0 );

			}
			else {
				CLEAR_BIT ( (*(TIM[i]+DIER))  , 0 );
			}
			
			/* Configure prescaller */
			(*(TIM[i]+PSC)) =  (configTable[i].u16Prescaler - 1 ) ;
			
			/* Configure interval  */
			u32 loacl_u32Hold =  (configTable[i].u32ClkSource / 1000000 ) * configTable[i].u32Interval ;
			loacl_u32Hold =  loacl_u32Hold / configTable[i].u16Prescaler;
			if (loacl_u32Hold < 65536 ){
				(*(TIM[i]+ARR)) = loacl_u32Hold ;
			}
			else {
				/* Error code */
			}

			/* Start timer */
			SET_BIT ( (*(TIM[i] +CR1)) , 0 );
		}
	}
} 

/****************** Timer basic functions **********************/

void TIMER_voidSetBusyWait (TIMER_channels_t copy_channel , u32 copy_u32TimeUS)
{
	/* Stop timer */
	CLEAR_BIT ( (*(TIM[copy_channel]+CR1))  , 0 ); 
	
	/* Clear flag */
	CLEAR_BIT ((*(TIM[copy_channel] +SR)) , 0);
	
	/* Configure interval */
	u32 loacl_u32Hold =  (configTable[copy_channel].u32ClkSource / 1000000 ) * copy_u32TimeUS ;
	loacl_u32Hold =  loacl_u32Hold / configTable[copy_channel].u16Prescaler;
	if (loacl_u32Hold < 65536 ){
		(*(TIM[copy_channel]+ARR)) = loacl_u32Hold ;
		(*(TIM[copy_channel]+CNT)) = 0 ;
	}
	else {
		/* Error code */
	}
	
	/* Start timer */
	SET_BIT ( (*(TIM[copy_channel] +CR1)) , 0 ); 
	
	/* Wait for flag */
	while (!(GIT_BIT ((*(TIM[copy_channel] +SR)) , 0)));
	
	/* Stop timer */
	CLEAR_BIT ( (*(TIM[copy_channel]+CR1))  , 0 ); 
} 


void TIMER_voidSetPeriodic (TIMER_channels_t copy_channel , u32 copy_u32TimeUS , void (*func)(void))
{

	/* Stop timer */
	CLEAR_BIT ( (*(TIM[copy_channel]+CR1))  , 0 ); 
	
	/* Configure interval */
	u32 loacl_u32Hold =  (configTable[copy_channel].u32ClkSource / 1000000 ) * copy_u32TimeUS  ;
	loacl_u32Hold =  loacl_u32Hold / configTable[copy_channel].u16Prescaler;
	if (loacl_u32Hold < 65536 ){
		(*(TIM[copy_channel]+ARR)) = loacl_u32Hold ;
	}
	else {
		/* Error code */
	}
	
	/* Set call back function */
	callBackFunc[copy_channel] = func ;
	
	/* Start timer */
	SET_BIT ( (*(TIM[copy_channel] +CR1)) , 0 ); 
	
	/* Enable interrupt */
	SET_BIT   ( (*(TIM[copy_channel]+DIER))  , 0 );
}


void TIMER_voidDisableOverFlowInterrupt(TIMER_channels_t copy_channel )
{
	/* Disable interrupt */
	CLEAR_BIT( (*(TIM[copy_channel]+DIER))  , 0 );
}



/************** ISR handlers ******************/

void TIM2_IRQHandler (void){
	/* Clear flag */
	CLEAR_BIT ((*(TIM[1] +SR)) , 0);
	callBackFunc[1]();
}
void TIM3_IRQHandler (void){
	/* Clear flag */
	CLEAR_BIT ((*(TIM[2] +SR)) , 0);
	callBackFunc[2]();
}
void TIM4_IRQHandler (void){
	/* Clear flag */
	CLEAR_BIT ((*(TIM[3] +SR)) , 0);
	callBackFunc[3]();
}
