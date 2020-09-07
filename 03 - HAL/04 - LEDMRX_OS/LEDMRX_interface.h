/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 7/9/2020                           */
/*****************************************************/
#ifndef LEDMRX_INTERFACE_H
#define LEDMRX_INTERFACE_H

/***********************************************************/
 /* Function Name  : LEDMRX_voidInit 
  * Function Type  : Initialization 
  * Parameters     : void 
  * Return         : void
  * Discription    : configure LED matrix display pins as output
  * Pre-conditions : RCC must be enabled for the GPIO ports used				
  */				
/************************************************************/
void LEDMRX_voidInit(void);

/***********************************************************/
 /* Function Name  : LEDMRX_voidDisplay 
  * Function Type  : Periodic Task
  * Parameters     : void 
  * Return         : void
  * Discription    : show a certain frame on the display , frame 
					 is passed as an array to setter function
  * Pre-conditions : OS must be initialized first 
  * Notes          : Period of the task will determine the frame 
					 rate per seconed 
  */				
/************************************************************/
void LEDMRX_voidDisplay (void);


/***********************************************************/
 /* Function Name  : LEDMRX_voidDisplayShiftText 
  * Function Type  : Periodic Task
  * Parameters     : void 
  * Return         : void
  * Discription    : Shift string on the display , frame is passed as 
					 an array to setter function
  * Pre-conditions : OS must be initialized first
					 LEDMRX_voidDisplay Task must be activated
  * Notes          : Period of the task will determine the delay  
					 between each shift 
  */				
/************************************************************/
void LEDMRX_voidDisplayShiftText (void);


/***********************************************************/
 /* Function Name  : LEDMRX_voidSetData 
  * Function Type  : Setter 
  * Parameters     : Pointer to u8 
  * Return         : void
  * Discription    : To pass frame for the task 				
  */				
/************************************************************/
void LEDMRX_voidSetData (u8 *copy_u8Data);


/***********************************************************/
 /* Function Name  : LEDMRX_voidSetStringLenght 
  * Function Type  : Setter 
  * Parameters     : (u8) Lenght of the string  
  * Return         : void
  * Discription    : To pass string lenght				
  */				
/************************************************************/
void LEDMRX_voidSetStringLenght(u8 copy_u8Data);




#endif
