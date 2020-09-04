/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 4/9/2020                          */
/*****************************************************/
#ifndef REMOTE_INTERFACE_H
#define REMOTE_INTERFACE_H

/*
	Notes should be taken when using driver 
	1 - open RCC for the port you used as EXTI for the reciever 
	2 - open RCC for AFIO 
	3 - Don't use systick in other applications 
	4 - call (REMOTE_voidInit) before while 
	5 - check the comming data from (REMOTE_getButton) function 
	6 - if data is less than (REMOTE_NO_DATA) then data is valid 

*/



/* The buttons IDs*/
typedef enum {
	REMOTE_ZERO     ,
    REMOTE_ONE      ,
	REMOTE_TWO      ,
	REMOTE_THREE    ,
	REMOTE_FOUR     ,
	REMOTE_FIVE     ,
	REMOTE_SIX      ,
	REMOTE_SEVEN    ,
	REMOTE_EIGHT    ,
	REMOTE_NINE     ,
	REMOTE_RPT      ,
	REMOTE_U_SD     ,
	REMOTE_EQ       ,
	REMOTE_VOL_DOWN ,
	REMOTE_VOL_UP   ,
	REMOTE_P_RESUME ,
	REMOTE_RIGHT    ,
	REMOTE_LEFT     ,
	REMOTE_POWER    ,
	REMOTE_MODE     ,
	REMOTE_MUTE     ,
	REMOTE_NO_DATA  ,
	REMOTE_ERROR    ,
}REMOTE_buttons_t;



/* 
  * REMOTE_voidInit - > Intialize the exti for remote  
*/
void REMOTE_voidInit(void);


/* 
  * REMOTE_getButton - > get the button pressed
  * O/P : (REMOTE_buttons_t) the pressed button if no data came return (REMOTE_NO_DATA)
		   if data was not right (REMOTE_ERROR)
*/
REMOTE_buttons_t REMOTE_getButton (void);




#endif