/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 5/9/2020                          */
/*****************************************************/
/* Library includes */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* MCAL includes */
#include "STK_interface.h"

/* module includes */
#include "OS_interface.h"
#include "OS_private.h"
#include "OS_config.h"

/************* Global variables ************/ 
OS_Task_t globalTasks[OS_NUMBER_OF_TASKS] ;

/************ Public functions **************/

/***********************   Scheduler APIS   *********************/
void OS_voidStart(void)
{
	/* To initialize the STK driver */
	STK_voidInit();
	/* To pass the scheduer function to the systick ISR */
	STK_voidSetIntervalPeriodic(OS_TICK_PERIOD, OS_TICK_UNIT , voidScheduler );
}

void OS_voidStop(void)
{
	STK_voidStop();
}

void OS_voidResume(void)
{
	STK_voidResume();
}

void OS_voidDispatcher (void)
{
	/* Check on all the tasks and execute any task with RunMe flag above zero*/
	for (u8 i = 0; i < OS_NUMBER_OF_TASKS ; i++)
	{
		if ( (globalTasks[i].func ) && (globalTasks[i].RunMe > 0) )
		{
			globalTasks[i].func();
			globalTasks[i].RunMe -= 1 ;
			
		}
		else
		{
			/* Should not be here */
		}
	}
	/* To save the power between ticks when there is no tasks ready yet*/
	voidGoToSleep();
}
/***************************************************************/

/*********************** Task APIS ****************************/
u8 OS_u8CreateTask(u8 copy_u8ID , u16 copy_u16delay , u16 copy_u16priode , void (* copy_voidFunc) (void))
{
	u8 local_u8ErrorState = SUCCESSED ;
	/* assign task parameters to the right array index */
	if (copy_u8ID < OS_NUMBER_OF_TASKS)
	{
		globalTasks[copy_u8ID].initialDelay = copy_u16delay ;
		globalTasks[copy_u8ID].priode 		= copy_u16priode ;
		globalTasks[copy_u8ID].func   		= copy_voidFunc ;
		globalTasks[copy_u8ID].taskState    = OS_TASK_READY ;
		globalTasks[copy_u8ID].RunMe        = 0 ;
	}
	else 
	{
		local_u8ErrorState = ERROR ;
	}
	/* To make the user check if the task created successfully */
	return local_u8ErrorState ;
}

u8 OS_u8DeleteTask (u8 copy_u8ID)
{
	u8 local_u8ErrorCode ;
	if (globalTasks[copy_u8ID].func)
	{
		globalTasks[copy_u8ID].initialDelay = 0 ;
		globalTasks[copy_u8ID].priode 		= 0 ;
		globalTasks[copy_u8ID].func   		= NULL ;
		globalTasks[copy_u8ID].RunMe        = 0 ;
		local_u8ErrorCode = SUCCESSED ;
	}
	else 
	{
		local_u8ErrorCode = ERROR ;
	}
	/* To make the user check if the task deleted successfully */
	return local_u8ErrorCode ;
}

u8 OS_voidSetTaskState(u8 copy_u8ID , OS_TaskStates_t copy_state)
{
	u8 local_u8ErrorCode ;
	if (globalTasks[copy_u8ID].func)
	{
		globalTasks[copy_u8ID].taskState = copy_state ;
		local_u8ErrorCode = SUCCESSED ;
	}
	else 
	{
		local_u8ErrorCode = ERROR ;
	}
	/* To make the user check if the user is changing the state of valid task */
	return local_u8ErrorCode ;
}


/********** Private functions ***************/
static void voidScheduler (void)
{
	/**  Co operative scheduling  **/
	for (u8 i = 0; i < OS_NUMBER_OF_TASKS ; i++)
	{
		if ( (globalTasks[i].func) && (globalTasks[i].taskState == OS_TASK_READY) )
		{
			
			/* Time of the task has come */
			if ( globalTasks[i].initialDelay == 0)
			{
				/* Dispatcher will check this flag in the while */
				globalTasks[i].RunMe++;
				
				/* Only if the task periodic will updated the initialDelay */
				if (globalTasks[i].priode){
					globalTasks[i].initialDelay = globalTasks[i].priode - OS_TICK_PERIOD ;
				}
			}
			else
			{
				globalTasks[i].initialDelay -= OS_TICK_PERIOD ;
			}
		}
		else
		{
			/* Should not be here */
		}
	}	

}

static void voidGoToSleep(void){
	__asm ("WFI");
}
