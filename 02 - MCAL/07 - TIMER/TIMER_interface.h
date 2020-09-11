/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 10/9/2020                           */
/*****************************************************/
#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H


/**** Timer channels ****/
typedef enum {
	TIM1,
	TIM2,
	TIM3,
	TIM4,
	MAX_TIMERS
}TIMER_channels_t;

/***********************************************************/
 /* Function Name  : TIMER_voidInit 
  * Function Type  : Initialization 
  * Parameters     : void 
  * Return         : void
  * Discription    : 
  * Pre-conditions : RCC must be enabled for used timers
					if interrupt is enabled you must enable 
					the correspending interrupt from NVIC
  */				
/************************************************************/
void TIMER_voidInit (void);

/***********************************************************/
 /* Function Name  : TIMER_voidSetBusyWait 
  * Function Type  : Delay function  
  * Parameters     : Timer channel   /  Time in us 
  * Return         : void
  * Discription    : 
  * Pre-conditions : Timer's interrupt must be disabled 
  */				
/************************************************************/
void TIMER_voidSetBusyWait (TIMER_channels_t copy_channel , u32 copy_u32TimeUS);


/***********************************************************/
 /* Function Name  : TIMER_voidSetPeriodic 
  * Function Type  :   
  * Parameters     : Timer channel   /  Time in us  /  void function 
  * Return         : void
  * Discription    : 
  * Pre-conditions :  
  */				
/************************************************************/
void TIMER_voidSetPeriodic (TIMER_channels_t copy_channel , u32 copy_u32TimeUS , void (*func)(void));

/***********************************************************/
 /* Function Name  : TIMER_voidDisableOverFlowInterrupt 
  * Function Type  :   
  * Parameters     : Timer channel  
  * Return         : void
  * Discription    : 
  * Pre-conditions :  
  */				
/************************************************************/
void TIMER_voidDisableOverFlowInterrupt(TIMER_channels_t copy_channel );



#endif
