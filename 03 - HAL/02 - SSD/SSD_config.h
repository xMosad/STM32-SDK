/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 14/8/2020                          */
/*****************************************************/
/*
	* The SSD module will be in the HAL layer and dependant on RCC and GPIO modules in the MCAL
	* the module has three basic functions one to intialize the SSD you can intialize more than one
	* SSD each one has an ID which is a struct ( SSD_selectID_t ) a function to write to one SSD
	* and a function to write to a set of multiplexing SSD 
	* these features can be controlled for the desired Application by the configuration paramteres in 
	* this file .
	* how to configure : 
	*  - > first you can choose what output mode you need in ( SSD_OUTPUT_MODE )
	*  - > choose the the SSD type from ( SSD_TYPE )
	*  - > if you are not using multiplexing write 0 or 1 to ( SSD_MULTIPLEXING_NUMBER )
	*  - > in case of multiplexing write number of SSD in ( SSD_MULTIPLEXING_NUMBER ) up to 4 
	*  - > you can choose the port of selection pins and which pins and also the delay time between switching the SSD
	*  - > if a pin is not used write ( NOT_USED )
	
*/

#ifndef SSD_CONFIG_H
#define SSD_CONFIG_H 

/*
	Options :
			GPIO_OUTPUT_10MHZ_PP
			GPIO_OUTPUT_2MHZ_PP
			GPIO_OUTPUT_50MHZ_PP
*/
#define  SSD_OUTPUT_MODE      GPIO_OUTPUT_10MHZ_PP


/*
	Options :
			COMMON_CATHOD
			COMMON_ANODE
*/
#define  SSD_TYPE             COMMON_CATHOD

/*
	Options :
			0 : 4 
*/
#define SSD_MULTIPLEXING_NUMBER       2 

/*    SSD select configuration pins   */
#if SSD_MULTIPLEXING_NUMBER > 1 
	#define     SSD_DELAY             10
	#define 	SSD_SELECT_PORT       PORTA 
	#define     SSD_RIGHT_SELECT      PIN9
	#define     SSD_MID1_SELECT       PIN10
	#define     SSD_MID2_SELECT       NOT_USED
	#define     SSD_LEFT_SELECT       NOT_USED
#endif



#endif