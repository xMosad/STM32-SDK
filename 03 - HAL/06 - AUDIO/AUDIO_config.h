/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 8/9/2020                          */
/*****************************************************/
#ifndef AUDIO_CONFIG_H
#define AUDIO_CONFIG_H

/** Choose pins of the DAC **/
#define     AUDIO_DAC0    PORTA,PIN0
#define     AUDIO_DAC1    PORTA,PIN1
#define     AUDIO_DAC2    PORTA,PIN2
#define     AUDIO_DAC3    PORTA,PIN3
#define     AUDIO_DAC4    PORTA,PIN4
#define     AUDIO_DAC5    PORTA,PIN5
#define     AUDIO_DAC6    PORTA,PIN6
#define     AUDIO_DAC7    PORTA,PIN7

/* 
	OPTIONS : 
		GPIO_OUTPUT_10MHZ_PP
		GPIO_OUTPUT_50MHZ_PP
		GPIO_OUTPUT_2MHZ_PP
*/
#define   AUDIO_DAC_OUTPUT_MODE     GPIO_OUTPUT_10MHZ_PP





#endif
