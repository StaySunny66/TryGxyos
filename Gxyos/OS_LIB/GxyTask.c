//
// Created by 17901 on 2023/1/8.
// Gxyos 任务函数
//

#include "GxyTask.h"


// 全局变量定义区域 //


GXYOS_U8 OS_OK;

OS_TASK_INDEX_TABLE OSTaskTable[OS_MAX_TASK];
OS_TASK_INDEX_TABLE * OSTaskTablePoi;
OS_TASK_MANAGE_TABLE OS_Task_Manage_Table;

/// 外部

extern GXYOS_U16 TaskDelayTable[OS_MAX_TASK];

// 这是一个空的队列头
OS_TASK_NODE OS_NODE_NULL;

OS_TASK_NODE * OS_NODE_HEAD;

OS_TASK_NODE * OS_NODE_LAST;



void Task_End_Call(){
	
	printf("task end !");
	
	
}





void Task_Stack_Init(OS_TASK_NODE *Task_Node ,GXYOS_U16 Stack_Size){
	
	/// 初始化 任务的堆栈
	
	/// STM32 的堆栈是从 高地址 --》 低地址
	
	unsigned int * Task_stack = &((unsigned int *)Task_Node->StackPoi)[Stack_Size-1];
	
	
	/// 此时 两个任务的堆栈指针都存在 了  Task_X_stack_p  中
	
	*(--Task_stack) =  0x01000000uL;   // 程序状态寄存器  PSR
	*(--Task_stack) = (unsigned int)Task_Node->Task;   // 程序开始地址   PC
	*(--Task_stack) = (unsigned int)Task_End_Call;  
	*(--Task_stack) =  0x00001234uL;   // R12
	*(--Task_stack) =  0x7788521AuL;   // R3
	*(--Task_stack) =  0x7788521BuL;   // R2
	*(--Task_stack) =  0x7788521CuL;   // R1
	*(--Task_stack) =  0x00000001uL;   // R0
	
	*(--Task_stack) =  0x7788521AuL;   // R11
	*(--Task_stack) =  0x7788521BuL;   // R10
	*(--Task_stack) =  0x7788521CuL;   // R9
	*(--Task_stack) =  0x7788521DuL;   // R8
	*(--Task_stack) =  0x7788521EuL;   // R7
	*(--Task_stack) =  0x7788521FuL;   // R6
	*(--Task_stack) =  0x7788521FuL;   // R5
	*(--Task_stack) =  0x7788521FuL;   // R4
	
	
	Task_Node->StackPoi = Task_stack;
	
	

}



GXYOS_VOID_POI OS_Manage(){

#if OS_MANAGE_DEBUG
    GXYOS_PRINTLN("OS_TASK_MANAGE_STATE")
    GXYOS_PRINTLN("OS_TASK--->UP_OS_POX  : %d",OS_Task_Manage_Table.UP_OS_POX);
    GXYOS_PRINTLN("OS_TASK--->UP_Priority: %d",OS_Task_Manage_Table.UP_OS_POX);
    GXYOS_PRINTLN("OS_TASK--->UP_Node    : %d",OS_Task_Manage_Table.UP_OS_POX);
    GXYOS_PRINTLN("         ->Node_Name %s",OSTaskTable[OS_Task_Manage_Table.UP_OS_POX+1].Task_Node->Task_Name);

#endif

    Start :
	
    if(OS_Task_Manage_Table.UP_OS_POX + 1 < OS_MAX_TASK){

        if(OSTaskTable[OS_Task_Manage_Table.UP_OS_POX].Priority ==OSTaskTable[OS_Task_Manage_Table.UP_OS_POX+1].Priority ){
            // 相等开始执行同优先级的任务

            OS_Task_Manage_Table.UP_OS_POX = OS_Task_Manage_Table.UP_OS_POX+1;
            OS_Task_Manage_Table.UP_PRI = OSTaskTable[OS_Task_Manage_Table.UP_OS_POX+1].Priority;
            OS_Task_Manage_Table.UP_Task_Node =  OSTaskTable[OS_Task_Manage_Table.UP_OS_POX+1].Task_Node;

            if(TaskDelayTable[OS_Task_Manage_Table.UP_OS_POX + 1] != 0) goto Start;

            return OS_Task_Manage_Table.UP_Task_Node;
        }


    }

    for(GXYOS_U16 i = 0;i < OS_MAX_TASK ; ++i){

        if(OSTaskTable[i].OS_STATE == OS_TASK_STATE_READY && TaskDelayTable[i] == 0){
            OS_Task_Manage_Table.UP_OS_POX = i;
            OS_Task_Manage_Table.UP_PRI = OSTaskTable[i].Priority;
            OS_Task_Manage_Table.UP_Task_Node = OSTaskTable[i].Task_Node;
            return OS_Task_Manage_Table.UP_Task_Node;
        }


    }
		
		return 0;

}


/*
 * GET next NULL position
 * 得到 下一个 空的优先级表的 位置索引
 *
 */

GXYOS_U32 OS_TASK_TABLE_GET_NEW(){
    GXYOS_U32 POX = 0;
    while(OSTaskTable[POX].Task_Node != NULL){
        POX ++;
    }
    if(POX< OS_MAX_TASK) return POX;
    return OS_MAX_TASK;

}


/*
 *
 * 获取当前系统中存在的任务数量
 */

GXYOS_U32 OS_TASK_NUM_GET(){
    return OS_TASK_TABLE_GET_NEW()+1;
}



/*
 *  将任务按优先级进行排序
 */

GXYOS_ERR OS_TASK_SORT(){
    GXYOS_U32 i;
    GXYOS_U32 j;
    OS_TASK_INDEX_TABLE TEM;
    GXYOS_U32 len = OS_TASK_NUM_GET();

    for (i = 0 ; i < len - 1  ; i++)
    {
        GXYOS_U32 min = i;
        for (j = i + 1; j < len - 1; j++)
        {
            if (OSTaskTable[j].Priority < OSTaskTable[min].Priority)
            {
                min = j;
            }
        }
        if(min != i)
        {
            TEM=OSTaskTable[min];
            OSTaskTable[min]=OSTaskTable[i];
            OSTaskTable[i]=TEM;
        }

    }
		
		return GXYOS_NULL;
}



/*
 * Related to memory operation,
 * Please configure the underlying implementation in os_porting.c
 * 内存操作相关 请自主配置 os_porting.c 中的底层实现
 */

GXYOS_STACK * OS_Stack_New_Mem(GXYOS_U32 SIZE){

    return (GXYOS_STACK *)OS_MEM_CALLOC(sizeof(GXYOS_STACK),SIZE);

}

OS_TASK_NODE * OS_Node_New_Mem(){

    return (OS_TASK_NODE *) OS_MEM_CALLOC(sizeof (OS_TASK_NODE),1);

}


/*
 *  The initialization of tasks and event tables；
 *  The beginning of the system life cycle
 *  任务、事件表的初始化，是系统生命周期的开始
 */

GXYOS_ERR OS_Task_init(){
        if(&OSTaskTable==GXYOS_NULL){
            OSTaskTablePoi = 0;
            return GXYOS_FATAL_ERR;
        }

        OSTaskTablePoi = OSTaskTable;

        OS_NODE_HEAD = &OS_NODE_NULL;
        OS_NODE_LAST = OS_NODE_HEAD;

    return GXYOS_OK;
}


/*
 *  Add a task to the operating system
 *  向操作系统添加一个任务
 *
 *  @parameters
 *  void (*Task)() : 任务函数的指针
 *  Stack_size ： 任务使用的堆栈大小
 *  Task_name : 任务的名称（无关紧要）
 *  Task_Pri :  任务的优先级
 */

GXYOS_ERR OS_New_Task(
        void (*Task)(),
        GXYOS_U16 Stack_size,
        GXYOS_CHAR *Task_name,
        GXYOS_U8 Task_Pri
        ){
    // 关闭 中断
    OS_Interrupt_Configuration(GXYOS_DISABLE);

    GXYOS_U32 POS;
    GXYOS_ERR ERR_CODE = GXYOS_OK;

    if(!(Task_Pri>=0&&Task_Pri<254)) return GXYOS_TASK_PRI_ERR;

    if(OS_STR_LEN(Task_name)>OS_MAX_TASK_NAME_SIZE) return GXYOS_TASK_NAME_ERR;

    if( Stack_size > OS_MAX_STACK_SIZE) return GXYOS_TASK_STACK_OVER_ERR;

    //分配节点空间
    OS_TASK_NODE * node;
    node = OS_Node_New_Mem();
    if(node == GXYOS_NULL) return ERR_CODE;

    //分配堆栈空间
    node->StackPoi = OS_Stack_New_Mem(Stack_size);
	 
    // 初始化内容
    node->Priority = Task_Pri;
    node->TASK_STATE = OS_TASK_STATE_READY;
    node->Task = Task;

    OS_Str_Cpy(node->Task_Name,Task_name);

    //在任务表中注册
    POS = OS_TASK_TABLE_GET_NEW();
    if(POS >= OS_MAX_TASK){
        // 超出系统最大任务值
        OS_MEM_FREE(node);
        return GXYOS_TASK_NUM_OVER_ERR;
    }
		
		
		///////////////////////////////////////////////
					
		// 任务堆栈初始化  ^_^
		
		///////////////////////////////////////////////
		
		Task_Stack_Init(node,Stack_size);
		
   /////////////////////////////////////////////////
		
		
		

    OSTaskTable[POS].Priority =Task_Pri;
    OSTaskTable[POS].Task_Node = node;
    OSTaskTable[POS].OS_STATE = OS_TASK_STATE_READY;

    // 加入任务链
    OS_NODE_LAST->NextNode = node;
    OS_NODE_LAST = node;

    OS_TASK_SORT();


    //重新 开启中断
    OS_Interrupt_Configuration(GXYOS_ENABLE);
		
		return GXYOS_OK;
}



// 获取下一个该运行的任务指针

GXYOS_VOID_POI OS_next_run(){

    return OS_Manage();
}


void GET_RUNNING_MESSAGE(){



    GXYOS_PRINTLN("");
    GXYOS_PRINTLN("------------->>    <<-----------");
    GXYOS_PRINTLN("Task running ...");
    GXYOS_PRINTLN("Task ---> Name :%s",OSTaskTable[OS_Task_Manage_Table.UP_OS_POX].Task_Node->Task_Name);
    GXYOS_PRINTLN("Task ---> PRI  :%d",OSTaskTable[OS_Task_Manage_Table.UP_OS_POX].Task_Node->Priority);
    GXYOS_PRINTLN("------------->>    <<-----------");
    GXYOS_PRINTLN("");

}







