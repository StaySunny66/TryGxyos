//
// Created by 17901 on 2023/1/8.
//

#include "Gxyos.h"
#include "GxyosTime.h"



void INITPendSv(void);
void PENDSV(void);




extern GXYOS_U8 OS_OK;
extern OS_TASK_INDEX_TABLE * OSTaskTablePoi;
extern OS_TASK_MANAGE_TABLE OS_Task_Manage_Table;

GXYOS_U32   now_stack_p;
GXYOS_U32  ** next_stack_p;


void basic_task(){
	while(1){
	
		//GXYOS_PRINTLN("free Task");
		
		
	}
}


GXYOS_ERR GxyosInit(){
	  OS_OK = 0;
	
	  OS_Interrupt_Configuration(GXYOS_DISABLE);
	
  	OS_Task_Manage_Table.UP_OS_POX= OS_MAX_TASK+1;
	
	  INITPendSv();
	
	  Systick_init(1);

    OS_Task_init();

    OSTaskTablePoi[30].Priority = 30;
  	

    OS_New_Task(basic_task,100,"Basic Task",30);
	
	  OS_Interrupt_Configuration(GXYOS_ENABLE);
	
	  

    return GXYOS_OK;
}


void GXYOSStart(){

     OS_OK = 1;
	

};


void GxyosTick(){
	  
	  

    OS_Time_Handle();
	
	  // 获得即将进行的任务 节点
    OS_TASK_NODE * TASK  = OS_next_run();
	   
	
	  
	
	  //GXYOS_PRINTLN("%s \r\n",TASK->Task_Name );
	
	
	   next_stack_p = &(TASK->StackPoi);
	  if(OS_OK){
		
					PENDSV();
		}
	  
	
	  
	
	  
	
	   
	
	  
   /// TASK->Task();

}







