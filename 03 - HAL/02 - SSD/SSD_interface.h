/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 14/8/2020                          */
/*****************************************************/
#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H 

/* A struct to type to hold the ssd port and start pin  
 The struck is like an id to the ssd as you can make than one ssd
 at differnt pins and ports by passing the struct to the function   */
typedef struct {
	GPIO_portId_t       SSD_portId   ;
	GPIO_pinsNumbers_t  SSD_startPin ;
}SSD_selectID_t;



/* 
  * SSD_voidInit - > Initialize the SSD 
  * i/p : struct have the port and the start pin (SSD_selectID_t)
*/
void SSD_voidInit(SSD_selectID_t copy_id);

/* 
  * SSD_voidWriteNumber - > Write a number to the ssd 
  * i/p : struct have the port and the start pin (SSD_selectID_t) / Number 0:9 / 
*/
void SSD_voidWriteNumber (SSD_selectID_t copy_id , u8 copy_u8Number);

/* 
  * SSD_voidUpdateMultiplexing - > Write a number to the number of SSD multiplexing up to 4 (check SSD_config.h)
  * i/p : struct have the port and the start pin (SSD_selectID_t) / Number up to 4 digits  / 
*/
void SSD_voidUpdateMultiplexing (SSD_selectID_t copy_id , u16 copy_u16Number) ;
#endif