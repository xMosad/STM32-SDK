/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v02                                */
 /* date        : 14/9/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* Module includes */
#include "DMA_interface.h"
#include "DMA_private.h"
#include "DMA_config.h"

/******** Global variables ********/
void (*callBackFunc[7])(void);

void DMA_voidConfigChannel (DMA_Channels_t copy_ch , DMA_configCh_t *copy_config)
{
	/* Disable channel  and reset register */
	DMA->CH[copy_ch].CCR  = 0 ;
	
	/* Set channel priority */
	DMA->CH[copy_ch].CCR |=   ( copy_config -> p_level << DMA_PL0 );
	
	/* Set timer mode */
	switch (copy_config -> tr_mode){
		case MEM2MEM :
			/* Enable MEM2MEM and make the peripheral rigster source */
			SET_BIT  (DMA->CH[copy_ch].CCR , DMA_MEM2MEM);
			CLEAR_BIT(DMA->CH[copy_ch].CCR , DMA_DIR);
			break;
		case PER2MEM :
			/* Peripheral rigster as source */
			CLEAR_BIT(DMA->CH[copy_ch].CCR , DMA_DIR);
			break;
		case MEM2PER :
			/* Memory rigster as source */
			SET_BIT  (DMA->CH[copy_ch].CCR , DMA_DIR);
			break;
		case PER2PER :
			/* Peripheral rigster as source */
			CLEAR_BIT(DMA->CH[copy_ch].CCR , DMA_DIR);
			break;
		default : /* Should not be here */ break;
	}
	
	/* Set memroy elemnt size */
	DMA->CH[copy_ch].CCR |=   ( copy_config -> mem_size << DMA_MSIZE0 );
	
	/* Set peripheral elemnt size */
	DMA->CH[copy_ch].CCR |=   ( copy_config -> per_size << DMA_PSIZE0 );
	
	/* Memory address increment */
	DMA->CH[copy_ch].CCR |=   ( copy_config -> mem_increment << DMA_MINC );
	
	/* Peripheral address increment */
	DMA->CH[copy_ch].CCR |=   ( copy_config -> per_increment << DMA_PINC );
	
	/* Circular mode  */
	DMA->CH[copy_ch].CCR |=   ( copy_config -> circular_mode << DMA_CIRC );
	
	/* Interrupst mangement */
	DMA->CH[copy_ch].CCR |=   ( copy_config -> TF_interrupt  << DMA_TCIE );
	DMA->CH[copy_ch].CCR |=   ( copy_config -> HTF_interrupt << DMA_HTIE );
	DMA->CH[copy_ch].CCR |=   ( copy_config -> ETF_interrupt << DMA_TEIE );
}

void DMA_voidTransfer (DMA_Channels_t copy_ch  , DMA_TransData_t *copy_trans)
{
	/* Disable channel */
	CLEAR_BIT(DMA->CH[copy_ch].CCR , DMA_EN);
	
	/* Set source and distination */
	if (copy_trans ->tr_mode == MEM2PER ){
		/* Set MEM as source address */
		DMA->CH[copy_ch].CMAR = copy_trans -> u32SourceAdress ;
		/* Set PER as distination address */
		DMA->CH[copy_ch].CPAR = copy_trans -> u32DistAddress ;
	}
	else {
		/* Set MEM as source address */
		DMA->CH[copy_ch].CPAR = copy_trans -> u32SourceAdress ;
		/* Set PER as distination address */
		DMA->CH[copy_ch].CMAR = copy_trans -> u32DistAddress ;
	}
	
	/* Configure block size */
	DMA->CH[copy_ch].CNDTR = copy_trans -> u16BlockSize ;
	
	/* Enable channel */
	SET_BIT(DMA->CH[copy_ch].CCR , DMA_EN);
}

void DMA_voidSetHandler (DMA_Channels_t copy_ch , void(*func)(void))
{
	callBackFunc[copy_ch] = func ;
}

u8 DMA_u8GetStatus(DMA_Channels_t copy_ch)
{
	u8 local_u8TC = DMA_TCIF1 + (copy_ch  * 4 );
	u8 local_u8TE = DMA_TEIF1 + (copy_ch  * 4 );
	u8 local_u8State  ;
	if (GIT_BIT (DMA-> IFCR , local_u8TC)){
		local_u8State = DMA_TC ;
	}
	else if (GIT_BIT (DMA-> IFCR , local_u8TE)){
		local_u8State = DMA_TE ;
	}
	else {
		local_u8State = DMA_NT ;
	}
	return local_u8State ;
}

/****************** ISR handlers ************************/

void DMA1_Channel1_IRQHandler (void)
{
	callBackFunc[0]();
	/* Clear flag */
	DMA -> IFCR = ( 1 << DMA_GIF1);
}

void DMA1_Channel2_IRQHandler (void)
{
	callBackFunc[1]();
	/* Clear flag */
	DMA -> IFCR = ( 1 << DMA_GIF2);
}

void DMA1_Channel3_IRQHandler (void)
{
	callBackFunc[2]();
	/* Clear flag */
	DMA -> IFCR = ( 1 << DMA_GIF3);
}

void DMA1_Channel4_IRQHandler (void)
{
	callBackFunc[3]();
	/* Clear flag */
	DMA -> IFCR = ( 1 << DMA_GIF4);
}

void DMA1_Channel5_IRQHandler (void)
{
	callBackFunc[4]();
	/* Clear flag */
	DMA -> IFCR = ( 1 << DMA_GIF5);
}

void DMA1_Channel6_IRQHandler (void)
{
	callBackFunc[5]();
	/* Clear flag */
	DMA -> IFCR = ( 1 << DMA_GIF6);
}

void DMA1_Channel7_IRQHandler (void)
{
	callBackFunc[6]();
	/* Clear flag */
	DMA -> IFCR = ( 1 << DMA_GIF7);
}



 


