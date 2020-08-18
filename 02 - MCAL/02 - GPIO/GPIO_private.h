/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v02                                */
 /* date        : 12/8/2020                           */
/*****************************************************/
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/*
base address 
0x4001 1000  GPIO Port C
0x4001 0C00  GPIO Port B
0x4001 0800  GPIO Port A
*/
/*
GPIOx_CRL   0X00 
GPIOx_CRH   0X04
GPIOx_IDR   0X08
GPIOx_ODR   0X0C
GPIOx_BSRR  0X10
GPIOx_BRR   0X14
GPIOx_LCKR  0X18
*/

/*     PORTA Registers defintions      */
#define GPIOA_CRL       *((volatile u32 *) 0x40010800 )
#define GPIOA_CRH       *((volatile u32 *) 0x40010804 )
#define GPIOA_IDR       *((volatile u32 *) 0x40010808 )
#define GPIOA_ODR       *((volatile u32 *) 0x4001080C )
#define GPIOA_BSRR      *((volatile u32 *) 0x40010810 )
#define GPIOA_BRR       *((volatile u32 *) 0x40010814 )
#define GPIOA_LCKR      *((volatile u32 *) 0x40010818 )

/*     PORTB Registers defintions      */
#define GPIOB_CRL       *((volatile u32 *) 0x40010C00 )
#define GPIOB_CRH       *((volatile u32 *) 0x40010C04 )
#define GPIOB_IDR       *((volatile u32 *) 0x40010C08 )
#define GPIOB_ODR       *((volatile u32 *) 0x40010C0C )
#define GPIOB_BSRR      *((volatile u32 *) 0x40010C10 )
#define GPIOB_BRR       *((volatile u32 *) 0x40010C14 )
#define GPIOB_LCKR      *((volatile u32 *) 0x40010C18 )

/*     PORTC Registers defintions      */
#define GPIOC_CRL       *((volatile u32 *) 0x40011000 )
#define GPIOC_CRH       *((volatile u32 *) 0x40011004 )
#define GPIOC_IDR       *((volatile u32 *) 0x40011008 )
#define GPIOC_ODR       *((volatile u32 *) 0x4001100C )
#define GPIOC_BSRR      *((volatile u32 *) 0x40011010 )
#define GPIOC_BRR       *((volatile u32 *) 0x40011014 )
#define GPIOC_LCKR      *((volatile u32 *) 0x40011018 )

#define CLEAR_VALUE 15

#endif