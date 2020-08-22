/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 22/8/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* Module includes */
#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"


void NVIC_voidInit(void){
	/* Applying the key to enable write on the reg  */
	SCB_AIRCR = (VECTKEY << VECTKEY_BIT) ; 

	/* Clear the three bits fisrt before writing to them */
	SCB_AIRCR &= ~ (0b111            << GROUPING_BIT ); 

	/* Choose configurations */	
	#if   NVIC_GROUPING_PRIORITY_TYPE == NVIC_GROUPING_16
		SCB_AIRCR |=   (NVIC_GROUPING_16 << GROUPING_BIT );
		
	#elif NVIC_GROUPING_PRIORITY_TYPE == NVIC_GROUPING_8
		SCB_AIRCR |=   (NVIC_GROUPING_8 << GROUPING_BIT);
		
	#elif NVIC_GROUPING_PRIORITY_TYPE == NVIC_GROUPING_4
		SCB_AIRCR |=   (NVIC_GROUPING_4 << GROUPING_BIT);
		
	#elif NVIC_GROUPING_PRIORITY_TYPE == NVIC_GROUPING_2
		SCB_AIRCR |=   (NVIC_GROUPING_2 << GROUPING_BIT);
		
	#elif NVIC_GROUPING_PRIORITY_TYPE == NVIC_GROUPING_0
		SCB_AIRCR |=   (NVIC_GROUPING_0 << GROUPING_BIT);
	
	#else 
		#error (" Configuration error ")
	#endif
	
}

void NVIC_voidEnableIRQ(NVIC_IRQn_t copyIRQn){
	/* Devided by 32 to write to the right regsiter index         */
	/* Anding (copyIRQn) with 31 so value will always be under 32 */
	
	NVIC->ISER[ copyIRQn / 32 ] = (1 << (copyIRQn & 31 )) ;
}

void NVIC_voidDisableIRQ(NVIC_IRQn_t copyIRQn){
	NVIC->ICER[ copyIRQn / 32 ] = (1 << (copyIRQn & 31 )) ;
}

u8   NVIC_u8GetPendingIRQ (NVIC_IRQn_t copyIRQn){
	u8 bit = GIT_BIT(NVIC->ISPR[ copyIRQn / 32 ] , (copyIRQn & 31 ) ) ;
	return bit ;  
}

void NVIC_voidSetPendingIRQ (NVIC_IRQn_t copyIRQn){
	NVIC->ISPR[ copyIRQn / 32 ] = (1 << (copyIRQn & 31 )) ;
}

void NVIC_voidClearPendingIRQ (NVIC_IRQn_t copyIRQn){
	NVIC->ICPR[ copyIRQn / 32 ] = (1 << (copyIRQn & 31 )) ;
}

u8  NVIC_u8GetActive (NVIC_IRQn_t copyIRQn){
	u8 bit = GIT_BIT(NVIC->IABR[ copyIRQn / 32 ] , (copyIRQn & 31 ) ) ;
	return bit ;
}

void NVIC_voidSetPriority (NVIC_IRQn_t copyIRQn, u8 copy_u8Priority){
	/* Geting the register number */
	u8 reg_number = copyIRQn / 4 ;
	
	/* Geting the offset of specific interrupt */
	u8 offset = copy_u8Priority % 4 ;
	offset *= 8 ;
	offset += 4 ;
	
	/* Clear the four bit before writing to it  */
	NVIC->IPR[ reg_number ] &= ~ (0x0f            << offset);
	
	/* Writing into the four bit the periority */
	NVIC->IPR[ reg_number ] |=   (copy_u8Priority << offset);
	
}





