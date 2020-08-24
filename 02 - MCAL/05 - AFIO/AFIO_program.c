/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 24/8/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* Module includes */
#include "AFIO_interface.h"
#include "AFIO_private.h"
#include "AFIO_config.h"


void AFIO_voidSelectPortForLine(u8 copy_u8Line , u8 copy_u8PortId){
	
	/* Get the register index */
	u8 local_u8RegIndex = copy_u8Line / 4 ;
	
	/* Get the offest */
	u8 local_u8Offset = copy_u8Line % 4 ;
	local_u8Offset   *= 4 ;
	
	/* Clear the four bits first */
	AFIO->EXTICR[local_u8RegIndex] &= ~(0xf           << local_u8Offset);
	
	/* Write into the four bits */
	AFIO->EXTICR[local_u8RegIndex] |=  (copy_u8PortId << local_u8Offset);
}






