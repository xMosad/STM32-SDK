/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 8/9/2020                          */
/*****************************************************/

/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* MCAL includes */
#include "GPIO_interface.h"

/* module includes */
#include "AUDIO_interface.h"
#include "AUDIO_config.h"
#include "AUDIO_private.h"



/****** Global variables  *******/
 u8 global_u8PinsMap[16] = {AUDIO_DAC0 , AUDIO_DAC1 , AUDIO_DAC2 , AUDIO_DAC3 ,                                             
							AUDIO_DAC4 , AUDIO_DAC5 ,  AUDIO_DAC6 , AUDIO_DAC7 };
u16 global_u16Index ;
u16 global_u16SongLen ;
u8 global_u8Arr ;
                                       
/********* Initialization ********/
void AUDIO_voidInit (void)
{
	for (u8 i = 0 ; i < 16 ; i += 2)
	{
		GPIO_voidSetPinMode(global_u8PinsMap[i] , global_u8PinsMap[i+1] , AUDIO_DAC_OUTPUT_MODE);
	}
}                           
   
/*********** Tasks ************/ 
void AUDIO_voidSetDAC (void){
	GPIO_voidWritePins(AUDIO_DAC0 , PINS_8 , global_u8Arr[global_u16Index]);
	global_u16Index++;
	if (global_u16Index == global_u16SongLen){
		global_u16Index = 0 ;
	}
}


/*  Setter function  */
void AUDIO_voidSetSong(u8 *copy_u8Arr , u16 copy_u16SongLen){
	global_u8Arr = copy_u8Arr ;
	global_u16SongLen = copy_u16SongLen ;
}
  
