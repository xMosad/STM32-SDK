/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 5/9/2020                          */
/*****************************************************/
#ifndef OS_CONFIG_H
#define OS_CONFIG_H

/*
  Number of tasks 
   each task take 10 byte in RAM 
*/
#define   OS_NUMBER_OF_TASKS   3

/*
	Options 
		TIME_MS
		TIME_US
*/
#define   OS_TICK_UNIT         TIME_MS
   
/*
	The tick interval  
*/
#define   OS_TICK_PERIOD       1 



#endif