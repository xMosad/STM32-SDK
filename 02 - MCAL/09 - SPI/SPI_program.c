/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 14/9/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* Module includes */
#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"

/* Global variables */
void (*callBackFunc[SPI_MAX_CH])(u16);

/****** Public fucntions *******/

u8 SPI_u8ConfigureCh(SPI_Ch_t copy_channel , SPI_config_t *copy_config)
{
	u8 local_u8ErrorCode = 0 ;

	/* Intialize the register */
	(*(SPI[copy_channel] + CR1 ))  = 0;
	
	
	/* Configure polarity in in idle */
	switch (copy_config -> u8CPOL){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , CPOL);
			break ;
		case 0  :
			CLEAR_BIT((*(SPI[copy_channel] + CR1 )) , CPOL);
			break;
		default :
			local_u8ErrorCode = 1 ;
		break ;
	}

	/* Configure phase */
	switch (copy_config -> u8CPHA){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , CPHA);
			break ;
		case 0  :
			CLEAR_BIT((*(SPI[copy_channel] + CR1 )) , CPHA);
			break;
		default :
			local_u8ErrorCode = 1 ;
		break ;
	}

	/* Configure Frame format MSB or LSB first */
	switch (copy_config -> u8FrameFormat){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , LSBFIRST);
			break ;
		case 0  :
			CLEAR_BIT((*(SPI[copy_channel] + CR1 )) , LSBFIRST);
			break;
		default :
			local_u8ErrorCode = 1 ;
		break ;
	}

	/* Configure Frame size 8 or 16 bit */
	switch (copy_config -> u8FrameSize){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , DFF);
			break ;
		case 0  :
			CLEAR_BIT((*(SPI[copy_channel] + CR1 )) , DFF);
			break;
		default :
			local_u8ErrorCode = 1 ;
		break ;
	}

	/* Enable or disable S.W slave mangement */
	switch (copy_config -> u8SSM){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , SSM);
			SET_BIT  ((*(SPI[copy_channel] + CR1 ))  , SS1);
			break ;
		case 0  :
			CLEAR_BIT((*(SPI[copy_channel] + CR1 )) , SSM);
			break;
		default :
			local_u8ErrorCode = 1 ;
		break ;
	}

	/* Full duplex or Receive only  */
	switch (copy_config -> u8TransmissonMode){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , RXONLY);
			break ;
		case 0  :
			CLEAR_BIT((*(SPI[copy_channel] + CR1 )) , RXONLY);
			break;
		default :
			local_u8ErrorCode = 1 ;
		break ;
	}

	/* Prescaller */
	if (copy_config -> u8Prescaler  <  8 )
	{
		(*(SPI[copy_channel] + CR1 )) |= (copy_config -> u8Prescaler << BR0);
	}
	else
	{
		local_u8ErrorCode = 1 ;
	}

	/* Enable or Disable interrupt */
	switch (copy_config -> u8InterruptEnable){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR2 )) , RXNEIE);
			break ;
		case 0  :
			CLEAR_BIT((*(SPI[copy_channel] + CR2 )) , RXNEIE);
			break;
		default :
			local_u8ErrorCode = 1 ;
		break ;
	}

	/* Configure mode master or slave */
	switch (copy_config -> u8Mode){
		case 1  :
			SET_BIT  ((*(SPI[copy_channel] + CR1 )) , MSTR);
			break ;
		case 0  :
			CLEAR_BIT((*(SPI[copy_channel] + CR1 )) , MSTR);
			break;
		default :
			local_u8ErrorCode = 1 ;
		break ;
	}

	/* Enable SPI */
	SET_BIT  ((*(SPI[copy_channel] + CR1 )) , SPE);

	/* return error state */
	return local_u8ErrorCode ;
}


u16 SPI_voidSendRecSynch (SPI_Ch_t copy_channel , u16 copy_u16SendData)
{
	/* Send data */
	(*(SPI[copy_channel] + DR )) = copy_u16SendData ;
	
	/* Wait till finish transmision */
	while (GIT_BIT ( (*(SPI[copy_channel] + SR )) , BSY) == 1) ;
	
	/* Return data data */
	return ( (*(SPI[copy_channel] + DR )) ) ;
}

void SPI_voidSendRecAsynch (SPI_Ch_t copy_channel , u16 copy_u16SendData , void (*func)(u16))
{
	/* Assign call back function */
	callBackFunc[copy_channel] = func ;
	
	/* Send data */
	(*(SPI[copy_channel] + DR )) = copy_u16SendData ;
}

/***************** ISR handlers ******************/
void SPI1_IRQHandler (void){
	/* clear falg */
	CLEAR_BIT ((*(SPI[0] + SR )) , RXNE );
	/* Receive data */
	u16 local_u16RecData = (*(SPI[0] + DR )) ;
	/* call function*/
	callBackFunc[0](local_u16RecData);
}

void SPI2_IRQHandler (void){
	/* clear falg */
	CLEAR_BIT ((*(SPI[1] + SR )) ,RXNE );
	/* Receive data */
	u16 local_u16RecData = (*(SPI[0] + DR )) ;
	/* call function*/
	callBackFunc[1](local_u16RecData);
}


