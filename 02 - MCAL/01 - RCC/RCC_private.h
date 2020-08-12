/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 8/8/2020                           */
/*****************************************************/
#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

// base address : 0x4002 1000
/* Register Definitions */
#define RCC_CR       *((volatile u32 *) 0x40021000)
#define RCC_CFGR     *((volatile u32 *) 0x40021004)
#define RCC_CIR      *((volatile u32 *) 0x40021008)
#define RCC_APB2RSTR *((volatile u32 *) 0x4002100C)
#define RCC_APB1RSTR *((volatile u32 *) 0x40021010)
#define RCC_AHBENR   *((volatile u32 *) 0x40021014)
#define RCC_APB2ENR  *((volatile u32 *) 0x40021018)
#define RCC_APB1ENR  *((volatile u32 *) 0x4002101C)
#define RCC_BDCR     *((volatile u32 *) 0x40021020)
#define RCC_CSR      *((volatile u32 *) 0x40021024)


/*            Configuratuin parameters                     */
#define ENABLE   1
#define DISABLE  0

/*  Clock system options  */
#define RCC_HSI 		  0
#define RCC_HSE_CRYSTAL   1
#define RCC_HSE_RC        2
#define RCC_PLL           3

/* PLL options */
#define RCC_PLL_HSI_BY2   0
#define RCC_PLL_HSE       1
#define RCC_PLL_HSE_BY2   2

/*  MCO pin options   */
#define NO_CLOCK      0
#define HSI_CLOCK     1
#define HSE_CLOCK     2
#define PLL_CLOCK     3
#define SYSTEM_CLOCK  4

/* Prescaller options for buses*/
#define RCC_PRESCALLER_0 	 0	  
#define RCC_PRESCALLER_2     2
#define RCC_PRESCALLER_4     3
#define RCC_PRESCALLER_6     4   
#define RCC_PRESCALLER_16    5
#define RCC_PRESCALLER_64    6
#define RCC_PRESCALLER_128   7
#define RCC_PRESCALLER_256   8
#define RCC_PRESCALLER_512   9


/* RCC_CR BITS  */
#define RCC_HSI_ON       0
#define RCC_HSI_RDY      1
#define RCC_HSI_TRIM0    3            
#define RCC_HSE_ON       16 
#define RCC_HSE_RDY      17
#define RCC_HSE_BYP      18
#define RCC_CSS_ON       19   
#define RCC_PLL_ON       24
#define RCC_PLL_RDY      25 

/* RCC_CFGR BITS */
#define RCC_SW0          0
#define RCC_SW1          1
#define RCC_HPRE0        4
#define RCC_HPRE1        5
#define RCC_HPRE2        6
#define RCC_HPRE3        7
#define RCC_PPRE1_0      8
#define RCC_PPRE1_1      9
#define RCC_PPRE1_2      10 
#define RCC_PPRE2_0      11 
#define RCC_PPRE2_1      12 
#define RCC_PPRE2_2      13
#define RCC_ADCPRE0      14 
#define RCC_ADCPRE2      15
#define RCC_PLL_SRC      16
#define RCC_PLL_XTPRE    17
#define RCC_PLL_MUL0     18
#define RCC_MCO_0        24
#define RCC_MCO_1        25
#define RCC_MCO_2        26          
         


#endif
