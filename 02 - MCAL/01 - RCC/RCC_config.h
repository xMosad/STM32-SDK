/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 8/8/2020                           */
/*****************************************************/
#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_


/* Options : 
			RCC_HSI 		  
			RCC_HSE_CRYSTAL   
			RCC_HSE_RC       
			RCC_PLL 			 
*/
#define SYS_CLOCK         RCC_HSE_CRYSTAL

/* 
 Clock security system : (ENABLE - DISABLE)
 */
#define CSS_ON            DISABLE

/*
  Options : -16 : 15 
*/ 
#define HSI_STEP_CORRECTION   0 


/*
  Options :
			RCC_PLL_HSI_BY2   
			RCC_PLL_HSE       
			RCC_PLL_HSE_BY2
*/ 
#define RCC_PLL_SOURCE    HSI_CLOCK
/*
  Options : 2 : 16 
*/ 
#define RCC_PLL_MUL       2 

/*
  Options : 
			NO_CLOCK      
			HSI_CLOCK     
			HSE_CLOCK     
			PLL_CLOCK     
			SYSTEM_CLOCK
*/ 
#define RCC_MCO_PIN       NO_CLOCK

/*
  Options :  		  
			RCC_PRESCALLER_2   
			RCC_PRESCALLER_4 
			RCC_PRESCALLER_6
			RCC_PRESCALLER_8
*/ 
#define RCC_ADC_PRESCALLER    RCC_PRESCALLER_2

/*
  Options : 
			RCC_PRESCALLER_0 		  
			RCC_PRESCALLER_2   
			RCC_PRESCALLER_4 
			RCC_PRESCALLER_8 
			RCC_PRESCALLER_16
*/ 
#define RCC_APB2_PRESCALLER   RCC_PRESCALLER_0

/*
  Options : 
			RCC_PRESCALLER_0 		  
			RCC_PRESCALLER_2   
			RCC_PRESCALLER_4 
			RCC_PRESCALLER_8 
			RCC_PRESCALLER_16
*/
/* Note : this bus clock must not exceed 36 MHZ*/
#define RCC_APB1_PRESCALLER   RCC_PRESCALLER_0

/*
  Options : 
			RCC_PRESCALLER_0 		  
			RCC_PRESCALLER_2
			RCC_PRESCALLER_4			
			RCC_PRESCALLER_8 
			RCC_PRESCALLER_16
			RCC_PRESCALLER_64
			RCC_PRESCALLER_128
			RCC_PRESCALLER_256
			RCC_PRESCALLER_512			
*/
#define RCC_AHP_PRESCALLER    RCC_PRESCALLER_0




#endif
