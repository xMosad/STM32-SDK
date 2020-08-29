/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 24/8/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* Module includes */
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"


void EXTI_voidInitLineInterrupt(u8 copy_u8Line , EXTI_triggerSelect_t copy_triggerType){
	/* Disable interrupt on line */
	CLEAR_BIT(EXTI->IMR , copy_u8Line ); 
	
	/* select the edge */
	switch(copy_triggerType){
		case EXTI_RISING_EDGE  : 
			SET_BIT  (EXTI->RTSR , copy_u8Line );
			CLEAR_BIT(EXTI->FTSR , copy_u8Line );
			break;
		
		case EXTI_FALLING_EDGE :
			SET_BIT  (EXTI->FTSR , copy_u8Line );
			CLEAR_BIT(EXTI->RTSR , copy_u8Line );
			break;
		
		case EXTI_ON_CHANGE    :
			SET_BIT(EXTI->RTSR , copy_u8Line );
			SET_BIT(EXTI->FTSR , copy_u8Line );
			break;
		
		default :
			/* should not be here */
			break;
	}
}

void EXTI_voidEnableLineInterrupt(u8 copy_u8Line){
	/* Enable interrupt on line */
	SET_BIT(EXTI->IMR , copy_u8Line );
}

void EXTI_voidDisableLineInterrupt(u8 copy_u8Line){
	/* Disable interrupt on line */
	CLEAR_BIT(EXTI->IMR , copy_u8Line ); 
}

void EXTI_voidSoftwareInterrupt(u8 copy_u8Line){
	SET_BIT(EXTI->SWIER , copy_u8Line );
}

void EXTI_voidClearPendingFlag(u8 copy_u8Line){
	SET_BIT(EXTI->PR , copy_u8Line ); 
}







