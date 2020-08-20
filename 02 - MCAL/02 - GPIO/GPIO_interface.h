/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v02                                */
 /* date        : 12/8/2020                           */
/*****************************************************/
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/* GPIO port id data type  */
typedef enum {
	PORTA = 0 ,
	PORTB ,
	PORTC
}GPIO_portId_t;

/* GPIO pins number data type */
typedef enum {
	PIN0 = 0 ,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}GPIO_pinsNumbers_t;

/* GPIO mode data type */
typedef enum {
	/*   Input modes    */
	GPIO_INPUT_ANALOG              = 0B0000 ,
	GPIO_INPUT_FLOATING            = 0B0100 ,
	GPIO_INPUT_PULL_UP_DOWN        = 0B1000 ,            
	
	/*   Output modes   */
	GPIO_OUTPUT_10MHZ_PP           = 0B0001 ,
	GPIO_OUTPUT_10MHZ_OD           = 0B0101 ,
	GPIO_OUTPUT_10MHZ_AFPP         = 0B1001 ,
	GPIO_OUTPUT_10MHZ_AFOD         = 0B1101 ,
	
	GPIO_OUTPUT_2MHZ_PP            = 0B0010 ,
	GPIO_OUTPUT_2MHZ_OD            = 0B0110 ,
	GPIO_OUTPUT_2MHZ_AFPP          = 0B1010 ,
	GPIO_OUTPUT_2MHZ_AFOD          = 0B1110 ,
	
	GPIO_OUTPUT_50MHZ_PP           = 0B0011 ,
	GPIO_OUTPUT_50MHZ_OD           = 0B0111 ,
	GPIO_OUTPUT_50MHZ_AFPP         = 0B1011 ,
	GPIO_OUTPUT_50MHZ_AFOD         = 0B1111 
}GPIO_modes_t;

/* number of pins to write into */
typedef enum {
	PINS_2       =   0x03  ,
	PINS_3       =   0x07  ,
	PINS_4       =   0x0f  ,
	PINS_5       =   0x1f  ,
	PINS_6       =   0x3f  ,
	PINS_7       =   0x7f  ,
	PINS_8       =   0xff  ,
}GPIO_numberOfPins_t ;

/* pins value */
#define HIGH           1 
#define LOW            0

/* pull types */
#define GPIO_PULL_UP   1
#define GPIO_PULL_DOWN 0

/* 
  * GPIO_voidSetPinMode - > set the mode of the pin 
  * i/p : port id (PORTA - PORTB - PORTC) / pin number ( PIN0 -> PIN15) / mode
*/
void GPIO_voidSetPinMode (GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyPinNumber , GPIO_modes_t copyMode  );

/* 
  * GPIO_voidsetPinValue - > used to set a specific pin HIGH or LOW 
							 or enable PULL UP or DOWN 
  * i/p : port id (PORTA - PORTB - PORTC) / pin number ( PIN0 -> PIN15) / value ( HIGH - LOW) (GPIO_PULL_UP - GPIO_PULL_DOWN)
*/
void GPIO_voidsetPinValue (GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyPinNumber , u8 copy_u8Value);

/* 
  * GPIO_voidTogglePinValue - > Toggle the pin value  
  * i/p : port id (PORTA - PORTB - PORTC) / pin number ( PIN0 -> PIN15) 
*/
void GPIO_voidTogglePinValue (GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyPinNumber );

/* 
  * GPIO_u8GetPinValue - > set the pin value 1 or 0 
  * i/p : port id (PORTA - PORTB - PORTC) / pin number ( PIN0 -> PIN15) 
  * o/p : the pin value (u8)
*/
u8 GPIO_u8GetPinValue (GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyPinNumber);

/* 
  * GPIO_voidSetPortMode - > set the mode of the port 
  * i/p : port id (PORTA - PORTB - PORTC) / mode
*/
void GPIO_voidSetPortMode (GPIO_portId_t copyPortId , GPIO_modes_t copyMode );

/* 
  * GPIO_voidSetPortValue - > write a value to the whole port
  * i/p : port id (PORTA - PORTB - PORTC) / value (0x0000 - 0xffff)
*/
void GPIO_voidSetPortValue (GPIO_portId_t copyPortId , u16 copy_u16Value);

/* 
  * GPIO_voidWriteByte - > write a value to the 8 pins 
  * i/p : port id (PORTA - PORTB - PORTC) / pin number ( PIN0 -> PIN15)/ number of pins to be written /value (0x00 - 0xff)
*/
void GPIO_voidWritePins(GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyStartPinNumber , GPIO_numberOfPins_t copyNumberOfPins , u8 copy_u8Value ) ;

/* 
  * GPIO_voidLockPin - > Lock the pin configuration 
  * i/p : port id (PORTA - PORTB - PORTC) / pin number (PIN0 - PIN15)
*/
void GPIO_voidLockPin(GPIO_portId_t copyPortId , GPIO_pinsNumbers_t copyPinNumber);

#endif