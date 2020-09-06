/*****************************************************/
 /* Author      : mosad                              */
 /* Version     : v01                                */
 /* date        : 5/9/2020                           */
 /**************************************************************/
/** Pre conditions : 
	1 - No other module use STK driver 
	2 - STK drivers files must be included in the project
	3 - Number of tasks must be configured  ( OS_NUMBER_OF_TASKS )
	4 - Clock must be selected right in STK driver to ensure right time
	5 - OS_voidStart must be called before while 
	6 - OS_voidDispatcher must be called in the while 
	7 - Global interrupt must be active  
**/
/****************************************************************/

#ifndef OS_INTERFACE_H
#define OS_INTERFACE_H

/** Errors **/
#define      SUCCESSED             1
#define      ERROR                 0

/* Hold the task states */
typedef enum {
	OS_TASK_READY    ,
	OS_TASK_SUSPENDE ,
}OS_TaskStates_t;

/***********************   Scheduler APIS   *********************/

/* 
  * OS_voidStart - > Initialize the OS and start the scheduling 
*/
void OS_voidStart(void);

/* 
  * OS_voidStop - > Stop the scheduling by stoping the timer ISR
*/
void OS_voidStop(void);

/* 
  * OS_voidResume - > Resume the scheduling by re enabling the ISR
*/
void OS_voidResume(void);

/* 
  * OS_voidDispatcher - > Called in the while Loop and responsible of calling the
						  the right task
*/
void OS_voidDispatcher (void);



/*********************** Task APIS ****************************/

/* 
  * OS_u8CreateTask - > create a new task note that maximum number of tasks is limited by 
						the config parameter (OS_NUMBER_OF_TASKS)
  * I / P : task id (u8)  /  initial delay for the first invoke of the function (u16)
			Period of the task (u16) , void function aka the task
  * O / P : an error state if successfully completed will be(SUCCESSED) else will be (ERROR)
*/
u8 OS_u8CreateTask(u8 copy_u8ID , u16 copy_u16delay , u16 copy_u16priode , void (* copy_voidFunc) (void));

/* 
  * OS_u8DeleteTask - > Delete a task permanently from the scheduler
  * I / P : task id (u8)
  * o / p : an error state if successfully completed will be(SUCCESSED) else will be (ERROR)
*/
u8 OS_u8DeleteTask (u8 copy_u8ID);

/* 
  * OS_voidSetTaskState - > Set task state to ready or suspended
  * I / P : task id (u8)  / state (OS_TaskStates_t)
  * o / p : an error state if successfully completed will be(SUCCESSED) else will be (ERROR)
*/
u8 OS_voidSetTaskState(u8 copy_u8ID , OS_TaskStates_t copy_state);





#endif
