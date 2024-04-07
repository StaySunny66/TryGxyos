//
// Created by 17901 on 2023/2/4.
//

#include "GxyosTime.h"
#include "Gxyos.h"

GXYOS_U32 System_Time;
GXYOS_U32 System_Time_Loop_Count;
GXYOS_U16 TaskDelayTable[OS_MAX_TASK];

extern OS_TASK_MANAGE_TABLE OS_Task_Manage_Table;
void PENDSV(void);





void Task_delay(GXYOS_U16 ms){
	
	   
    OS_Interrupt_Configuration(GXYOS_DISABLE);

    TaskDelayTable[OS_Task_Manage_Table.UP_OS_POX] += ms;
	
	  OS_Interrupt_Configuration(GXYOS_ENABLE);
	  PENDSV();


}


void OS_Time_init(){
    System_Time = 0;
    System_Time_Loop_Count = 0;

    for (GXYOS_U16 i = 0; i < OS_MAX_TASK; ++i) {
        TaskDelayTable[i] = 0;
    }

}


GXYOS_U32 OS_Get_System_S(){

    return System_Time/1000 + 2592000 * System_Time_Loop_Count;

}


/// call  by  IRQ
/// 被硬件定时器中断调用  每次调用 系统时间加 1ms

void OS_Time_Handle(){
    // 系统时间
    if(System_Time == 2592000000 - 1){
        System_Time = 0;
        System_Time_Loop_Count ++;
    } else{
        System_Time ++;
    }


    // OS 级别延时削减
    for (GXYOS_U16 i = 0; i < OS_MAX_TASK; ++i) {
        if(TaskDelayTable[i] != 0) TaskDelayTable[i] --;
    }

#if OS_TIME_DEBUG
    if(System_Time%1000 == 0){

        GXYOS_LOG("System running Time %d",OS_Get_System_S());

        #if OS_TASK_DELAY_TABLE_DEBUE
            GXYOS_PRINTLN("===== OS TASK Delay Table =====")
            for (GXYOS_U16 i = 0; i < OS_TASK_NUM_GET()-1; ++i) {
                GXYOS_PRINTLN("Task %d , Delay MS : %d",i,TaskDelayTable[i]);
            }
        #endif

    }


#endif




}



