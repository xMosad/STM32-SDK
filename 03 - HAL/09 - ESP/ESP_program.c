/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 30/9/2020                          */
/*****************************************************/

/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include <string.h>

/* MCAL includes */
#include "UART_interface.h"

/* module includes */
#include "ESP_interface.h"
#include "ESP_config.h"
#include "ESP_private.h"

static void voidWaitForRes(u8 *copy_u8Rec , u8 time ){
	while (time--){
		UART_voidRecDataSynch (ESP_UART_CH , copy_u8Rec , 100);
		if (copy_u8Rec[0]){break;}
	}
}

void ESP_voidInit (void)
{
	u8 local_RecBuffer[100] = {0} ;
	do {
	/* Turn off echo */
	UART_voidSendDataSynch (ESP_UART_CH , "ATE0\r\n" );
	voidWaitForRes(local_RecBuffer , 1);
	}while((local_RecBuffer[2] != 'O') &&(local_RecBuffer[3] != 'K'));
	
	/* Set the mode */
	do {
		UART_voidSendDataSynch (ESP_UART_CH , "AT+CWMODE=1\r\n" );
		voidWaitForRes(local_RecBuffer , 1);
	}while((local_RecBuffer[2] != 'O') &&(local_RecBuffer[3] != 'K'));

}

void ESP_voidConnectToWifi(const u8 *copy_u8SSD , const u8 *copy_u8Pass)
{
	u8 local_buffer[100] = {0} ;
	sprintf (local_buffer , "AT+CWJAP_CUR=\"%s\",\"%s\"\r\n" ,copy_u8SSD , copy_u8Pass );
	UART_voidSendDataSynch (ESP_UART_CH , local_buffer );
}

void ESP_voidConnectToServer(const u8 *copy_u8IP ,const u8 copy_u8Port )
{
	u8 local_buffer[100] = {0} ;
	u8 local_RecBuffer[100] = {0} ;
	u8 flag1 , flag2 ;
	/* Try to connect to server till it is connceted */
	do{
		sprintf (local_buffer , "AT+CIPSTART=\"TCP\",\"%s\",%i\r\n" ,copy_u8IP , copy_u8Port );
		UART_voidSendDataSynch (ESP_UART_CH , local_buffer );
		voidWaitForRes(local_RecBuffer , 2);
		if ((local_RecBuffer[2] != 'b') &&(local_RecBuffer[3] != 'u')){
			voidWaitForRes(local_RecBuffer , 4);
		}
		flag1 = ((local_RecBuffer[0] != 'C') &&(local_RecBuffer[1] != 'O'));
		flag2 = ((local_RecBuffer[0] != 'A') &&(local_RecBuffer[1] != 'L'));
	}while( flag1 && flag2);

}


u8 ESP_voidRecData (const u8 *copy_u8URL )
{
	u8 local_u8Lenght =  0;
	u8 local_ReceiveBuffer[100] = {0};
	u8 local_buffer[100] = {0} ;
	u8 local_buffer2[20] = {0};

	local_u8Lenght = strlen(copy_u8URL);
	local_u8Lenght += 6 ;

	sprintf (local_buffer , "GET %s\r\n" ,copy_u8URL);
	sprintf (local_buffer2 , "AT+CIPSEND=%i\r\n" ,local_u8Lenght);
	
	/* Send length */
	u8 buf[100] = {0};
	UART_voidSendDataSynch (ESP_UART_CH , local_buffer2 );
	voidWaitForRes(buf , 1);
	/* Send request */
	UART_voidSendDataSynch (ESP_UART_CH , local_buffer );
	voidWaitForRes(buf , 1);
	/* Rec  one char from text file */
	UART_voidRecDataSynch (ESP_UART_CH , local_ReceiveBuffer , 22);
	return local_ReceiveBuffer[20];
}





