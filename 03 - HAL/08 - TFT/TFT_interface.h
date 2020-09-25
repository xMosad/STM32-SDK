/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 21/9/2020                          */
/*****************************************************/
#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H


void TFT_voidInit (void);

void TFT_voidDisplayImage(const u16* copy_u16Image);

void TFT_voidDrawRectangle (u16 copy_u16X ,u16 copy_u16Y , u16 copy_u16Width , u16 copy_u16Hight , u16 copy_u16Color );

void TFT_voidFillDisplay (u16 copy_u16Colour);

#endif
