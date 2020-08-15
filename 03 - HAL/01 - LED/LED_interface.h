/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 15/8/2020                          */
/*****************************************************/
#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

/* A struct type to hold the LED port and pin  
 The struck is like an id to the LED as you can make than one LED
 at differnt pins and ports by passing the struct to the function   */
typedef struct {
	GPIO_portId_t      LED_portId ; 
	GPIO_pinsNumbers_t LED_pinNumber ;
}LED_id_t;

/*  LED states */
typedef enum {
	ON   , 
	OFF
}LED_states_t;

/* 
  * LED_voidInit - > initialize the led 
  * i/p : struct have the port and the pin (SSD_selectID_t) 
*/
void LED_voidInit(LED_id_t copyID);

/* 
  * LED_voidSetState - > Set led state on or off 
  * i/p : struct have the port and the start pin (SSD_selectID_t) / (LED_states_t)  ON , OFF
*/
void LED_voidSetState (LED_id_t copyID , LED_states_t copyState);

/* 
  * LED_voidToggle - > toggle led state
  * i/p : struct have the port and the start pin (SSD_selectID_t) / delay of toggle (u16) 
*/
void LED_voidToggle (LED_id_t copyID);


#endif