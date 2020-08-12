/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 8/8/2020                           */
/*****************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

void RCC_voidInitSysClock (void){
	
	// choose system clock from (HSI - HSE crystal - HSE RC- PLL)
	#if SYS_CLOCK == RCC_HSI 
		SET_BIT  (RCC_CR   , RCC_HSI_ON);       //HSI on
		while( !(RCC_CR & (1<<RCC_HSI_RDY) ) ); // wait till ready
		CLEAR_BIT(RCC_CFGR , RCC_SW0);          //Choosing HSI 
		CLEAR_BIT(RCC_CFGR , RCC_SW1);
		
	#elif SYS_CLOCK == RCC_HSE_CRYSTAL
		SET_BIT  (RCC_CR   , RCC_HSE_ON);       //HSE on
		while( !(RCC_CR & (1<<RCC_HSE_RDY) ) );
		CLEAR_BIT(RCC_CR   , RCC_HSE_BYP);	    //disable bypass
		CLEAR_BIT(RCC_CFGR , RCC_SW1 );         //Choosing HSE
		SET_BIT  (RCC_CFGR , RCC_SW0 );
	
	#elif SYS_CLOCK == RCC_HSE_RC
		SET_BIT  (RCC_CR   , RCC_HSE_ON);        //HSE on
		while( !(RCC_CR & (1<<RCC_HSE_RDY) ) );  // wait till ready
		SET_BIT  (RCC_CR   , RCC_HSE_BYP);	     //enable bypass
		CLEAR_BIT(RCC_CFGR , RCC_SW1    );       //Choosing HSE
		SET_BIT  (RCC_CFGR , RCC_SW0    );
		
    #elif SYS_CLOCK == PLL_CLOCK
		
		RCC_CFGR &= ~(15 << RCC_PLL_MUL0);                 //clear the four bits
		RCC_CFGR |= ( (RCC_PLL_MUL - 2 ) << RCC_PLL_MUL0); //load the new multiplication value
		
		#if   RCC_PLL_SOURCE == RCC_PLL_HSI_BY2
			SET_BIT  (RCC_CR   , RCC_HSI_ON ); //HSI on
			CLEAR_BIT(RCC_CFGR , RCC_PLL_SRC);
			
		#elif RCC_PLL_SOURCE == RCC_PLL_HSE
			SET_BIT  (RCC_CR   , RCC_HSE_ON ); //HSE on
			SET_BIT  (RCC_CFGR , RCC_PLL_SRC); // choose HSI as PLL source
			
		#elif RCC_PLL_SOURCE == RCC_PLL_HSE_BY2
			SET_BIT  (RCC_CR   , RCC_HSE_ON   ); //HSE on
			SET_BIT  (RCC_CFGR , RCC_PLL_XTPRE); // Enable prescaller by 2
			SET_BIT  (RCC_CFGR , RCC_PLL_SRC  ); // choose HSI as PLL source
			
		#else
			#error("Configuration error")
		#endif
	
		while( !(RCC_CR & (1<<RCC_PLL_RDY) ) );  // wait till ready
		SET_BIT  (RCC_CR   , RCC_PLL_ON);        //PLL on
		CLEAR_BIT(RCC_CFGR , RCC_SW0   );        // Choosing PLL
		SET_BIT  (RCC_CFGR , RCC_SW1   );
	#else
		#error("Configuration error")
	#endif
	

	
	//set the correction factor
	#if HSI_STEP_CORRECTION != 0 
		RCC_CR &= ~(31 << RCC_HSI_TRIM0);      //clear the five bits
		RCC_CR |= ( (HSI_STEP_CORRECTION + 16 ) << RCC_HSI_TRIM0);
	#endif



	
	//choosing output on MCO
	#if   RCC_MCO_PIN == NO_CLOCK 
		CLEAR_BIT(RCC_CFGR , RCC_MCO_2);
		
	#elif RCC_MCO_PIN == HSI_CLOCK
		SET_BIT  (RCC_CR   , RCC_HSI_ON);  //HSI on
		SET_BIT  (RCC_CFGR , RCC_MCO_0 );
		CLEAR_BIT(RCC_CFGR , RCC_MCO_1 );
		SET_BIT  (RCC_CFGR , RCC_MCO_2 );
		
    #elif RCC_MCO_PIN == HSE_CLOCK
		SET_BIT  (RCC_CR   , RCC_HSE_ON);  //HSE on
		CLEAR_BIT(RCC_CFGR , RCC_MCO_0 );
		SET_BIT  (RCC_CFGR , RCC_MCO_1 );
		SET_BIT  (RCC_CFGR , RCC_MCO_2 );
		
	#elif RCC_MCO_PIN == PLL_CLOCK
		SET_BIT  (RCC_CFGR , RCC_MCO_0);
		SET_BIT  (RCC_CFGR , RCC_MCO_1);
		SET_BIT  (RCC_CFGR , RCC_MCO_2);
		
	#elif RCC_MCO_PIN == SYSTEM_CLOCK
		CLEAR_BIT(RCC_CFGR , RCC_MCO_0);
		CLEAR_BIT(RCC_CFGR , RCC_MCO_1);
		SET_BIT  (RCC_CFGR , RCC_MCO_2);
	#endif
	
	
	
	// To enable or disable Clock security system 
	#if CSS_ON == ENABLE 
		SET_BIT  (RCC_CR , RCC_CSS_ON);
	#elif CSS_ON == DISABLE
		CLEAR_BIT(RCC_CR , RCC_CSS_ON);
	#endif
	
	/* Choosing a prescaller for the ADC */
	#if   RCC_ADC_PRESCALLER == RCC_PRESCALLER_2 
		CLEAR_BIT(RCC_CFGR , RCC_ADCPRE0);
		CLEAR_BIT(RCC_CFGR , RCC_ADCPRE2);
	#elif RCC_ADC_PRESCALLER == RCC_PRESCALLER_4
		SET_BIT  (RCC_CFGR , RCC_ADCPRE0);
		CLEAR_BIT(RCC_CFGR , RCC_ADCPRE2);
	#elif RCC_ADC_PRESCALLER == RCC_PRESCALLER_6
		CLEAR_BIT(RCC_CFGR , RCC_ADCPRE0);
		SET_BIT  (RCC_CFGR , RCC_ADCPRE2);
	#elif RCC_ADC_PRESCALLER == RCC_PRESCALLER_8
		SET_BIT  (RCC_CFGR , RCC_ADCPRE0);
		SET_BIT  (RCC_CFGR , RCC_ADCPRE2);
	#else
		#error("Configuration error")
	#endif
	
	/* Choosing a prescaller for the APB2 */
	#if   RCC_APB2_PRESCALLER == RCC_PRESCALLER_0 
		CLEAR_BIT(RCC_CFGR , RCC_PPRE2_2);
	#elif RCC_APB2_PRESCALLER == RCC_PRESCALLER_2
		CLEAR_BIT(RCC_CFGR , RCC_PPRE2_0);
		CLEAR_BIT(RCC_CFGR , RCC_PPRE2_1);
		SET_BIT  (RCC_CFGR , RCC_PPRE2_2);
	#elif RCC_APB2_PRESCALLER == RCC_PRESCALLER_4
		SET_BIT  (RCC_CFGR , RCC_PPRE2_0);
		CLEAR_BIT(RCC_CFGR , RCC_PPRE2_1);
		SET_BIT  (RCC_CFGR , RCC_PPRE2_2);
	#elif RCC_APB2_PRESCALLER == RCC_PRESCALLER_8
		CLEAR_BIT(RCC_CFGR , RCC_PPRE2_0);
		SET_BIT  (RCC_CFGR , RCC_PPRE2_1);
		SET_BIT  (RCC_CFGR , RCC_PPRE2_2);
	#elif RCC_APB2_PRESCALLER == RCC_PRESCALLER_16
		SET_BIT  (RCC_CFGR , RCC_PPRE2_0);
		SET_BIT  (RCC_CFGR , RCC_PPRE2_1);
		SET_BIT  (RCC_CFGR , RCC_PPRE2_2);
	#else
		#error("Configuration error")
	#endif
	
	/* Choosing a prescaller for the APB1 */
	#if   RCC_APB1_PRESCALLER == RCC_PRESCALLER_0 
		CLEAR_BIT(RCC_CFGR , RCC_PPRE1_2);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_2
		CLEAR_BIT(RCC_CFGR , RCC_PPRE1_0);
		CLEAR_BIT(RCC_CFGR , RCC_PPRE1_1);
		SET_BIT  (RCC_CFGR , RCC_PPRE1_2);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_4
		SET_BIT  (RCC_CFGR , RCC_PPRE1_0);
		CLEAR_BIT(RCC_CFGR , RCC_PPRE1_1);
		SET_BIT  (RCC_CFGR , RCC_PPRE1_2);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_8
		CLEAR_BIT(RCC_CFGR , RCC_PPRE1_0);
		SET_BIT  (RCC_CFGR , RCC_PPRE1_1);
		SET_BIT  (RCC_CFGR , RCC_PPRE1_2);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_16
		SET_BIT  (RCC_CFGR , RCC_PPRE1_0);
		SET_BIT  (RCC_CFGR , RCC_PPRE1_1);
		SET_BIT  (RCC_CFGR , RCC_PPRE1_2);
	#else
		#error("Configuration error")
	#endif
	
	/* Choosing a prescaller for the AHP */
	#if   RCC_APB1_PRESCALLER == RCC_PRESCALLER_0 
		CLEAR_BIT(RCC_CFGR , RCC_HPRE3);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_2
		CLEAR_BIT(RCC_CFGR , RCC_HPRE0);
		CLEAR_BIT(RCC_CFGR , RCC_HPRE1);
		CLEAR_BIT(RCC_CFGR , RCC_HPRE2);
		SET_BIT  (RCC_CFGR , RCC_HPRE3);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_4
		SET_BIT  (RCC_CFGR , RCC_HPRE0);
		CLEAR_BIT(RCC_CFGR , RCC_HPRE1);
		CLEAR_BIT(RCC_CFGR , RCC_HPRE2);
		SET_BIT  (RCC_CFGR , RCC_HPRE3);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_8
		CLEAR_BIT(RCC_CFGR , RCC_HPRE0);
		SET_BIT  (RCC_CFGR , RCC_HPRE15);
		CLEAR_BIT(RCC_CFGR , RCC_HPRE2);
		SET_BIT  (RCC_CFGR , RCC_HPRE3);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_16
		SET_BIT  (RCC_CFGR , RCC_HPRE0);
		SET_BIT  (RCC_CFGR , RCC_HPRE1);
		CLEAR_BIT(RCC_CFGR , RCC_HPRE2);
		SET_BIT  (RCC_CFGR , RCC_HPRE3);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_64
		CLEAR_BIT(RCC_CFGR , RCC_HPRE0);
		CLEAR_BIT(RCC_CFGR , RCC_HPRE1);
		SET_BIT  (RCC_CFGR , RCC_HPRE2);
		SET_BIT  (RCC_CFGR , RCC_HPRE3);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_128
		SET_BIT  (RCC_CFGR , RCC_HPRE0);
		CLEAR_BIT(RCC_CFGR , RCC_HPRE1);
		SET_BIT  (RCC_CFGR , RCC_HPRE2);
		SET_BIT  (RCC_CFGR , RCC_HPRE3);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_256
		CLEAR_BIT(RCC_CFGR , RCC_HPRE0);
		SET_BIT  (RCC_CFGR , RCC_HPRE1);
		SET_BIT  (RCC_CFGR , RCC_HPRE2);
		SET_BIT  (RCC_CFGR , RCC_HPRE3);
	#elif RCC_APB1_PRESCALLER == RCC_PRESCALLER_512
		SET_BIT  (RCC_CFGR , RCC_HPRE0);
		SET_BIT  (RCC_CFGR , RCC_HPRE1);
		SET_BIT  (RCC_CFGR , RCC_HPRE2);
		SET_BIT  (RCC_CFGR , RCC_HPRE3);
	#else
		#error("Configuration error")
	#endif
	
}


void RCC_voidEnableClock (u8 copy_u8BudId , u8 copy_u8PerId){
    if (copy_u8PerId <= 31){
      switch (copy_u8BudId) {
        case RCC_AHP  : SET_BIT (RCC_AHBENR  , copy_u8PerId ); break;
        case RCC_APB1 : SET_BIT (RCC_APB1ENR , copy_u8PerId ); break;
        case RCC_APB2 : SET_BIT (RCC_APB2ENR , copy_u8PerId ); break;
        default       : break;
      }
    }
    else {

    }
}

void RCC_voidDisableClock (u8 copy_u8BudId , u8 copy_u8PerId){
    if (copy_u8PerId <= 31){
      switch (copy_u8BudId) {
        case RCC_AHP  : CLEAR_BIT (RCC_AHBENR  , copy_u8PerId ); break;
        case RCC_APB1 : CLEAR_BIT (RCC_APB1ENR , copy_u8PerId ); break;
        case RCC_APB2 : CLEAR_BIT (RCC_APB2ENR , copy_u8PerId ); break;
        default       : break;
      }
    }
    else {

    }
}


