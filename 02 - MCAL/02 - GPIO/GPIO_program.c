/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 12/8/2020                           */
/*****************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"

void GPIO_voidSetPinMode (GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyPinNumber , GPIO_modes_t copyMode  ) {
	switch (copyPortId){
		case PORTA : 
			if (copyPinNumber <= 7){
				GPIOA_CRL &= ~ (CLEAR_VALUE << copyPinNumber * 4 ) ; // clear the four bits first
				GPIOA_CRL |=   (copyMode    << copyPinNumber * 4 ) ; // update with mode value
			}
			else if (copyPinNumber <= 15){
				copyPinNumber = copyPinNumber - 8 ;
				GPIOA_CRH &= ~ (CLEAR_VALUE << copyPinNumber * 4 ) ; // clear the four bits first
				GPIOA_CRH |=   (copyMode    << copyPinNumber * 4 ) ; // update with mode value
			}
			else {
				
			}
			break;
		case PORTB : 
			if (copyPinNumber <= 7){
				GPIOB_CRL &= ~ (CLEAR_VALUE << copyPinNumber * 4 ) ; // clear the four bits first
				GPIOB_CRL |=   (copyMode    << copyPinNumber * 4 ) ; // update with mode value
			}
			else if (copyPinNumber <= 15){
				copyPinNumber = copyPinNumber - 8 ;
				GPIOB_CRH &= ~ (CLEAR_VALUE << copyPinNumber * 4 ) ; // clear the four bits first
				GPIOB_CRH |=   (copyMode    << copyPinNumber * 4 ) ; // update with mode value
			}
			else {
				
			}
			break;
		case PORTC : 
			if (copyPinNumber <= 7){
				GPIOC_CRL &= ~ (CLEAR_VALUE << copyPinNumber * 4 ) ; // clear the four bits first
				GPIOC_CRL |=   (copyMode    << copyPinNumber * 4 ) ; // update with mode value
			}
			else if (copyPinNumber <= 15){
				copyPinNumber = copyPinNumber - 8 ;
				GPIOC_CRH &= ~ (CLEAR_VALUE << copyPinNumber * 4 ) ; // clear the four bits first
				GPIOC_CRH |=   (copyMode    << copyPinNumber * 4 ) ; // update with mode value
			}
			else{
				
			}
			break;
		default    : /* Error code */  break ;
		
	}
}

void GPIO_voidsetPinValue (GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyPinNumber , u8 copy_u8Value){
	switch (copyPortId) {
		case PORTA :
			if      (copy_u8Value == HIGH){
				SET_BIT   (GPIOA_ODR , copyPinNumber) ;
			}
			else if (copy_u8Value == LOW ){
				CLEAR_BIT (GPIOA_ODR , copyPinNumber) ;
			}
			else {
				/* should not be here */
			}
			break ;
		case PORTB :
			if      (copy_u8Value == HIGH){
				SET_BIT   (GPIOB_ODR , copyPinNumber) ;
			}
			else if (copy_u8Value == LOW ){
				CLEAR_BIT (GPIOB_ODR , copyPinNumber) ;
			}
			else {
				/* should not be here */
			}
			break ;
		case PORTC : 
			if      (copy_u8Value == HIGH){
				SET_BIT   (GPIOC_ODR , copyPinNumber) ;
			}
			else if (copy_u8Value == LOW ){
				CLEAR_BIT (GPIOC_ODR , copyPinNumber) ;
			}
			else {
				/* should not be here */
			}
			break ;
		default    : /* should not be here */ break ;
	}
}

void GPIO_voidTogglePinValue (GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyPinNumber){
	switch (copyPortId) {
		case PORTA :
			TOGGLE_BIT (GPIOA_ODR , copyPinNumber) ;
			break ;
		case PORTB :
			TOGGLE_BIT (GPIOB_ODR , copyPinNumber) ;
			break ;
		case PORTC : 
			TOGGLE_BIT (GPIOC_ODR , copyPinNumber) ;
			break ;
		default    : /* should not be here */ break ;
	}
}

u8 GPIO_u8GetPinValue (GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyPinNumber){
	u8 bitValue = 0 ;
	switch (copyPortId) {
		case PORTA :
			bitValue = GIT_BIT (GPIOA_IDR , copyPinNumber );
			break ;
		case PORTB :
			bitValue = GIT_BIT (GPIOB_IDR , copyPinNumber );
			break ;
		case PORTC : 
			bitValue = GIT_BIT (GPIOC_IDR , copyPinNumber );
			break ;
		default    : /* should not be here */ break ;
	}
	return bitValue ;
}

void GPIO_voidSetPortMode (GPIO_portId_t copyPortId , GPIO_modes_t copyMode ){
	for (GPIO_pinsNumbers_t pins = PIN0 ; pins <= PIN15 ; pins++){
		GPIO_voidSetPinMode(copyPortId , pins , copyMode);
	}
}

void GPIO_voidSetPortValue (GPIO_portId_t copyPortId , u16 copy_u16Value){
	switch (copyPortId) {
		case PORTA :
			GPIOA_ODR = copy_u16Value ;
			break ;
		case PORTB :
			GPIOB_ODR = copy_u16Value ;
			break ;
		case PORTC : 
			GPIOC_ODR = copy_u16Value ;
			break ;
		default    : /* should not be here */ break ;
	}
}

void GPIO_voidWritePins(GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyStartPinNumber , GPIO_numberOfPins_t copyNumberOfPins , u8 copy_u8Value ){
	switch (copyPortId) {
		case PORTA :
			GPIOA_ODR &= ~ (copyNumberOfPins << copyStartPinNumber ) ;
			GPIOA_ODR |=   (copy_u8Value     << copyStartPinNumber ) ;
			break ;
		case PORTB :
			GPIOB_ODR &= ~ (copyNumberOfPins << copyStartPinNumber ) ;
			GPIOB_ODR |=   (copy_u8Value << copyStartPinNumber ) ;
			break ;
		case PORTC : 
			GPIOC_ODR &= ~ (copyNumberOfPins << copyStartPinNumber ) ;
			GPIOC_ODR |=   (copy_u8Value << copyStartPinNumber ) ;
			break ;
		default    : /* should not be here */ break ;
	}
}