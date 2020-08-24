/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 24/8/2020                          */
/*****************************************************/
#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H


/* 
  * AFIO_voidSelectPortForLine - > Assign the line for specific port 
  * i/p : (u8) line number 0:15  / (u8) Port id 0:6
*/
void AFIO_voidSelectPortForLine(u8 copy_u8Line , u8 copy_u8PortId);


#endif