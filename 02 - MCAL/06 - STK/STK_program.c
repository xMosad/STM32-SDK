/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 25/8/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* Module includes */
#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

/*****   Global variable   *****/
u32 global_u32Clk  = 0 ;
void (* functionCallBack)();  

void STK_voidInit(void)
{
	
	/*  choosing clk for the SysTick  */
	#if   STK_CLK_SOURCE  ==  AHP
		SET_BIT   (STK->CTRL , STK_CTRL_CLKSOURCE);
		global_u32Clk = STK_AHP_CLK ;
		
	#elif STK_CLK_SOURCE  ==  AHP_BY_8
		CLEAR_BIT (STK->CTRL , STK_CTRL_CLKSOURCE);
		global_u32Clk = STK_AHP_CLK / 8  ;
	
	#else 
		#error (" configuration error")
	#endif 
}

void STK_voidSetBusyWait( u32 Copy_u32Time , STK_time_t copy_unit )
{
	u32 local_u32Load = 0 ;
	STK->VAL = 0 ;
	/* Calculate and load the load value */
	switch (copy_unit){
		case TIME_MS : 
			local_u32Load = Copy_u32Time * (global_u32Clk / 1000) ;
			STK->LOAD     = local_u32Load ;
			break;
			
		case TIME_US :
			local_u32Load = Copy_u32Time * (global_u32Clk / 1000000) ;
			STK->LOAD     = local_u32Load ;
			break ; 
		default :    /* Should not be here */      break;
	}
	
	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);
	
	/* Wait for the flag */
	while ( !(GIT_BIT (STK->CTRL , STK_CTRL_COUNTFLAG)));
	
	/* Stop timer */
	CLEAR_BIT(STK->CTRL , STK_CTRL_ENABLE);
}

void STK_voidSetIntervalPeriodic( u32 Copy_u32Time , STK_time_t copy_unit, void (*Copy_func)(void)){
	u32 local_u32Load = 0 ;
	STK->VAL = 0 ;
	/* Calculate and load the load value */
	switch (copy_unit){
		case TIME_MS : 
			local_u32Load = Copy_u32Time * (global_u32Clk / 1000) ;
			STK->LOAD     = local_u32Load ;
			break;
			
		case TIME_US :
			local_u32Load = Copy_u32Time * (global_u32Clk / 1000000) ;
			STK->LOAD     = local_u32Load ;
			break ; 
		default :    /* Should not be here */      break;
	}
	
	/* To pass the function to ISR */
	functionCallBack = Copy_func ;
	
	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);
	
	/* Enable interrupt */
	SET_BIT(STK->CTRL , STK_CTRL_TICKINT);
}

void STK_voidStop(void)
{
	/* Stop timer */
	CLEAR_BIT(STK->CTRL , STK_CTRL_ENABLE);
	
	/* Disable interrupt */
	CLEAR_BIT(STK->CTRL , STK_CTRL_TICKINT);	
}

void STK_voidResume(void)
{
	/* Start timer */
	SET_BIT(STK->CTRL , STK_CTRL_ENABLE);
	
	/* Enable interrupt */
	SET_BIT(STK->CTRL , STK_CTRL_TICKINT);	
}


u32 STK_u32GetElapsedTime(STK_time_t copy_unit)
{
	u32 local_u32Value =  STK->LOAD - STK->VAL ;
	u32 local_u32ElapsedTime = 0 ;
	/* Calculate the elabsed time in ms or us */
	switch (copy_unit){
		case TIME_MS : 
			local_u32ElapsedTime = local_u32Value / (global_u32Clk / 1000) ;
			break;
			
		case TIME_US :
			local_u32ElapsedTime = local_u32Value / (global_u32Clk / 1000000) ;
			break ; 
		default :    /* Should not be here */      break;
	}
	return local_u32ElapsedTime ;
}


u32 STK_u32GetRemainingTime(STK_time_t copy_unit)
{
	u32 local_u32Value = STK->VAL ;
	u32 local_u32RemainingTime = 0 ;
	/* Calculate remaining time in ms or us */
	switch (copy_unit){
		case TIME_MS : 
			local_u32RemainingTime = local_u32Value / (global_u32Clk / 1000) ;
			break;
			
		case TIME_US :
			local_u32RemainingTime = local_u32Value / (global_u32Clk / 1000000) ;
			break ; 
		default :    /* Should not be here */      break;
	}
	return local_u32RemainingTime ;
}

void SysTick_Handler(void)
{
	functionCallBack();
}
