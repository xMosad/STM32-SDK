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
#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"

#if   LED_OPERATION == ACTIVE_HIGH
	#define LED_SET_ON  1
	#define LED_SET_OFF 0
#elif LED_OPERATION == ACTIVE_LOW
	#define LED_SET_ON  0
	#define LED_SET_OFF 1
#endif

void LED_voidInit(LED_id_t copyID){
	/*  RCC enable clock for port  */
	RCC_voidEnableClock(RCC_APB2 , (copyID.LED_portId + IOPA_PERIPHERAL) );
	/* Setting pin as output */
	GPIO_voidSetPinMode(copyID.LED_portId , copyID.LED_pinNumber , LED_OUTPUT_MODE);
	/* Initialize the LED off */
	GPIO_voidsetPinValue(copyID.LED_portId , copyID.LED_pinNumber , LED_SET_OFF );
	
}

void LED_voidSetState (LED_id_t copyID , LED_states_t copyState){
	switch (copyState){
		case ON  :
			GPIO_voidsetPinValue(copyID.LED_portId , copyID.LED_pinNumber , LED_SET_ON  );
			break ;
		case OFF : 
			GPIO_voidsetPinValue(copyID.LED_portId , copyID.LED_pinNumber , LED_SET_OFF );
			break ;
		default  :  /* Should not be here */ break ;
	}
}

void LED_voidToggle (LED_id_t copyID){
	
	GPIO_voidTogglePinValue(copyID.LED_portId , copyID.LED_pinNumber);
	
}