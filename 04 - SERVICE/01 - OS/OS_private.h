/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 5/9/2020                          */
/*****************************************************/
#ifndef OS_PRIVATE_H
#define OS_PRIVATE_H

/* Task data type to hold task information */
typedef struct 
{
	OS_TaskStates_t taskState ;
	u8 RunMe;
	u16 priode;
	u16 initialDelay ;
	void (* func) (void);
}OS_Task_t;

#define NULL  ((void *) 0)

/******* Private functions *******/
static void voidScheduler (void);
static void voidGoToSleep(void);




#endif
