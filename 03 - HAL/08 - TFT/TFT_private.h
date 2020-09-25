/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 21/9/2020                          */
/*****************************************************/
#ifndef TFT_PRIVATE_H
#define TFT_PRIVATE_H



static void voidWriteData (u8 copy_u8Data);
static void voidWriteCommand (u8 copy_u8Command);
static void voidDrawPixel (u16 copy_u16X , u16 copy_u16Y , u16 copy_u16Colour);
static void voidSetAddress (u16 copy_u16StartX ,u16 copy_u16EndX , u16 copy_u16StartY , u16 copy_u16EndY);
static void voidSetColour(u16 copy_u16Colour);


#endif
