/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 15/8/2020                          */
/*****************************************************/
/* Library includes */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL includes */
#include "GPIO_interface.h"
#include "RCC_interface.h"

/* Specific module includes  */
#include "BUTTON_interface.h"
#include "BUTTON_private.h"
#include "BUTTON_config.h"

/* check to detrmine the voltage check on pins */
#if   (BUTTON_PULL_TYPE == INTERNAL_PULL_UP ) || (BUTTON_PULL_TYPE == EXTERNAL_PULL_UP )
	#define BUTTON_PRESSED_VOLTAGE   0
	#define BUTTON_RELEASED_VOLTAGE  1
		
#elif (BUTTON_PULL_TYPE == INTERNAL_PULL_DOWN) || (BUTTON_PULL_TYPE == EXTERNAL_PULL_DOWN)
	#define BUTTON_PRESSED_VOLTAGE   1
	#define BUTTON_RELEASED_VOLTAGE  0
	
#else 
		#error("Configuration error")
#endif


typedef struct {
	BUTTON_state_t state ;
	u8 samples[2];
}BUTTON_data_t;

BUTTON_data_t       button_info [BUTTON_NUMBER] ; 
GPIO_portId_t       buttons_port[BUTTON_NUMBER] ;
GPIO_pinsNumbers_t  buttons_pins[BUTTON_NUMBER] ;

 

u8 BUTTON_voidInit(GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyPinNumber){
	static u8 i ;
	/* Enable RCC for the port*/
	RCC_voidEnableClock(RCC_APB2 , (copyPortId + IOPA_PERIPHERAL) );
	 
	 /* Intialize the pins as input */
	#if   BUTTON_PULL_TYPE == INTERNAL_PULL_UP 
		GPIO_voidSetPinMode (copyPortId , copyPinNumber , GPIO_INPUT_PULL_UP_DOWN );
		GPIO_voidSetPullType(copyPortId , copyPinNumber , GPIO_PULL_UP);
		
	#elif BUTTON_PULL_TYPE == INTERNAL_PULL_DOWN
		GPIO_voidSetPinMode(copyPortId , copyPinNumber , GPIO_INPUT_PULL_UP_DOWN );
		GPIO_voidSetPullType(copyPortId , copyPinNumber , GPIO_PULL_DOWN);
		
	#elif (BUTTON_PULL_TYPE == EXTERNAL_PULL_UP) || (BUTTON_PULL_TYPE == EXTERNAL_PULL_DOWN)
		GPIO_voidSetPinMode(copyPortId , copyPinNumber , GPIO_INPUT_FLOATING );
	
	#else 
		#error("Configuration error")
	#endif
	  
	//initial state
	button_info [i].state  = RELEASED      ;
	buttons_port[i]        = copyPortId    ;
	buttons_pins[i]        = copyPinNumber ;
	i++ ;
	return (i - 1) ;
}

void BUTTON_voidScane(void){
	for ( u8 i = 0 ; i < BUTTON_NUMBER ; i++){
		button_info[i].samples[0] = button_info[i].samples[1] ;
		
		button_info[i].samples[1] = GPIO_u8GetPinValue(buttons_port[i] , buttons_pins[i]);
		
		switch(button_info[i].state){
			case RELEASED:
				if((button_info[i].samples[0] == BUTTON_PRESSED_VOLTAGE) &&
				   (button_info[i].samples[1] == BUTTON_PRESSED_VOLTAGE))
				{
					button_info[i].state = PRE_PRESSED;
				}
				break;
				
			case PRE_PRESSED:
				if(button_info[i].samples[1] == BUTTON_PRESSED_VOLTAGE)
				{
					button_info[i].state = PRESSED;
				}
				break;
				
			case PRESSED:
				if((button_info[i].samples[0] == BUTTON_RELEASED_VOLTAGE) &&
				   (button_info[i].samples[1] == BUTTON_RELEASED_VOLTAGE))
				{
					button_info[i].state = PRE_RELEASED;
				}
				break;
			case PRE_RELEASED:
				if(button_info[i].samples[1] == BUTTON_RELEASED_VOLTAGE)
				{
					button_info[i].state = RELEASED;
				}
				break;
			default:
				/* Should not be here */
			break;
		}
	}
}

BUTTON_state_t BUTTON_voidGetState(u8 copy_u8Number){
	
	return button_info[copy_u8Number].state ;
	
}