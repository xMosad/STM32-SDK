/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 21/9/2020                          */
/*****************************************************/
#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H


/* Colours */
#define     TFT_BLACK        0x0000
#define     TFT_WHITE        0xffff
#define     TFT_RED          0xf800
#define     TFT_BLUE         0x39df
#define     TFT_YELLOW       0xffc0
#define     TFT_ORANGE       0xfd20
#define     TFT_PURPLE       0xf1df
#define     TFT_GREEN        0x1427


void TFT_voidInit (void);

void TFT_voidDisplayImage(const u16* copy_u16Image);

void TFT_voidDrawRectangle (u16 copy_u16X ,u16 copy_u16Y , u16 copy_u16Width , u16 copy_u16Hight , u16 copy_u16Color );

void TFT_voidFillDisplay (u16 copy_u16Colour);

void TFT_voidPrintChar(s8 copy_s8Char , u16 copy_u16X , u16 copy_u16Y, u8 copy_u8Size , u16 copy_u16Color, u16 copy_u16BackColor);

void TFT_voidPrintText(s8 *copy_s8Text , u16 copy_u16X , u16 copy_u16Y, u8 copy_u8Size , u16 copy_u16Color, u16 copy_u16BackColor);

#endif
