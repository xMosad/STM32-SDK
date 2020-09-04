/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 4/9/2020                          */
/*****************************************************/

/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* MCAL includes */
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "EXTI_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"

/* module includes */
#include "REMOTE_interface.h"
#include "REMOTE_config.h"
#include "REMOTE_private.h"

/****** Global variabled  *******/
volatile u8 global_u8Flag               = 0 ;
volatile u8 global_u8FinishFlag         = 0 ;
volatile u32 global_u32Frame            = 0 ;
volatile u8 global_u8Index              = 0 ;

u32 global_u32Data             = 0 ;
u32 global_u32DataInverted     = 0 ;
u32 global_u32Address          = 0 ;
u32 global_u32AddressInverted  = 0 ;


void REMOTE_voidInit(void)
{	
	/* Making the pin INPUT */
	GPIO_voidSetPinMode(REMOTE_EXTI_PORT , REMOTE_EXTI_LINE , GPIO_INPUT_FLOATING);
	
	/* Intialize EXTI */
	NVIC_voidEnableIRQ(REMOTE_NVIC_NUMBER);
	EXTI_voidInitLineInterrupt(REMOTE_EXTI_LINE , EXTI_FALLING_EDGE);
	EXTI_voidEnableLineInterrupt(REMOTE_EXTI_LINE);
	
	/* Configure the AFIO */
	AFIO_voidSelectPortForLine(REMOTE_EXTI_LINE ,REMOTE_EXTI_PORT);

	/* Systick initialize */
	STK_voidInit();
}


REMOTE_buttons_t REMOTE_getButton (void)
{
	REMOTE_buttons_t local_button = REMOTE_NO_DATA ;
	if (global_u8FinishFlag){
		u8 local_u8Check = REMOTE_u8CheckFrame();
		// determine which button was pressed 
		if (local_u8Check){
			switch (global_u32Data){
				case POWER       :  local_button = REMOTE_POWER;         break;
				case MODE        :  local_button = REMOTE_MODE;          break;
				case MUTE        :  local_button = REMOTE_MUTE;          break;
				case PLAY_RESUME :  local_button = REMOTE_P_RESUME ;     break;
				case RIGHT       :  local_button = REMOTE_RIGHT;         break;
				case LEFT        :  local_button = REMOTE_LEFT;          break;
				case EQ          :  local_button = REMOTE_EQ ;           break;
				case VOLUME_DOWN :  local_button = REMOTE_VOL_DOWN;      break;
				case VOLUME_UP   :  local_button = REMOTE_VOL_UP;        break;
				case ZERO        :  local_button = REMOTE_ZERO ;         break;
				case RPT         :  local_button = REMOTE_RPT;           break;
				case U_USD       :  local_button = REMOTE_U_SD;          break;
				case ONE         :  local_button = REMOTE_ONE ;          break;
				case TWO         :  local_button = REMOTE_TWO  ;         break;
				case THREE       :  local_button = REMOTE_THREE;         break;
				case FOUR        :  local_button = REMOTE_FOUR ;         break;
				case FIVE        :  local_button = REMOTE_FIVE ;         break;
				case SIX         :  local_button = REMOTE_SIX  ;         break;
				case SEVEN       :  local_button = REMOTE_SEVEN;         break;
				case EIGHT       :  local_button = REMOTE_EIGHT;         break;
				case NINE        :  local_button = REMOTE_NINE ;         break;
				default          :  
					/* If it is here data is not correct*/  
					local_button = REMOTE_ERROR ;			             break;                                   
			} 
		}
		global_u8FinishFlag = 0 ;
	}
	return local_button ; 
} 


void REMOTE_HANDLER(void) {
	/* Clear flag */
	EXTI_voidClearPendingFlag(REMOTE_EXTI_LINE);
	/* Get time elapsed*/
	u32 time = STK_u32GetElapsedTime(TIME_US);
	/* Start timer to count till the next isr */
	STK_voidStart();
	/* Wait for the start bit before recording frame*/
	if ((global_u8Flag == 0) && (time > 10000) && (time < 15000)){
		global_u8Flag = 1 ;
		global_u8Index = 0 ;
	}
	/* Start bit came and will start recording the frame */
	else if (global_u8Flag == 1){
		/* If bit == 1 */
		if ((time > 2000 ) && (time < 2400 )){
			SET_BIT(global_u32Frame , global_u8Index );
			global_u8Index++;
		}
		/* If bit == 0 */
		else if ( (time > 1000 ) &&  (time < 1200 ) ){
			CLEAR_BIT(global_u32Frame , global_u8Index );
			global_u8Index++;
		}
		/* the Wait before the next frame */
		else if ( (time > 20000 )){
			global_u8Flag = 0 ;
			global_u8FinishFlag = 1 ; 
		}
		else {

		}
	}
}


/***** Private functions ******/
static u8 REMOTE_u8CheckFrame(void)
{
	u8 local_u8Error = FRAME_ERROR ;
	/* Get data inverted from the frame*/
	global_u32DataInverted = (global_u32Frame & 0xff000000);
	global_u32DataInverted = (global_u32DataInverted >> DATA_INVERTED_BIT);
	
	/* Get data from the frame */
	global_u32Data         = (global_u32Frame & 0x00ff0000);
	global_u32Data         = (global_u32Data >> DATA_BIT);
	
	/* Get Address inverted from the frame */
	global_u32AddressInverted = (global_u32Frame & 0x0000ff00);
	global_u32AddressInverted = (global_u32AddressInverted >> ADDRESS_INVERTED_BIT);
	
	/* Get Address from the frame */
	global_u32Address = (global_u32Address & 0x000000ff);
	
	/* Check the data for errors */
	if ( (global_u32Data & global_u32DataInverted) | (global_u32Address & global_u32AddressInverted) ){
		local_u8Error = FRAME_ERROR ;
	}
	else {
		local_u8Error = FRAME_CORRECT ;
	}
	
	return local_u8Error ;

}

                                       
