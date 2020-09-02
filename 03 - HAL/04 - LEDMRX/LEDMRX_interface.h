/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 31/8/2020                          */
/*****************************************************/
#ifndef LEDMRX_INTERFACE_H
#define LEDMRX_INTERFACE_H


/* 
  * LEDMRX_voidInit - > Initialize the pins as output 
*/
void LEDMRX_voidInit(void);

/* 
  * LEDMRX_voidDisplay - > Dispaly a figure on the display
  * I/P : a pointer to the address of the array of the figure 
*/
void LEDMRX_voidDisplay (u8 *copy_u8Data);

/* 
  * LEDMRX_voidDisplayShiftText - > Dispaly a text and shift it 
  * I/P : a pointer to the address of the array of the figure , shift time (u16) , text size (u8)
*/
void LEDMRX_voidDisplayShiftText (u8 *copy_u8Data , u16 copy_u8Time , u8 copy_u8TextSize);




#endif