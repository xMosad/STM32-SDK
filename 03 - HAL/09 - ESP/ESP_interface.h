/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 30/9/2020                          */
/*****************************************************/
#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H

/*********************************************************
	Pre conditions : 
		1 - UART initialized 
*********************************************************/


/*
  * ESP_voidInit - > Initialize the WIFI module 
*/
void ESP_voidInit (void);

/*
  * ESP_voidConnectToWifi - > connect to wifi network
  * i/p : the SSD of wifi and password as text 
*/
void ESP_voidConnectToWifi(const u8 *copy_u8SSD , const u8 *copy_u8Pass);

/*
  * ESP_voidConnectToServer - > connect to server 
  * i/p : the IP of the server as text and port number  
*/
void ESP_voidConnectToServer(const u8 *copy_u8IP ,const u8 copy_u8Port );

/*
  * ESP_voidRecData - > Receive data from a given URL
  * i/p : the URL as text 
  * o/p : the received character 
*/
u8 ESP_voidRecData (const u8 *copy_u8URL );


#endif
