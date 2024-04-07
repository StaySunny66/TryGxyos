//
// Created by 17901 on 2023/1/8.
//

#ifndef GXYOS_GXYTASK_H
#define GXYOS_GXYTASK_H

#include "Gxyos.h"

/************************
 * OS' Process Control Block
 *
 *
 ***********************/

#define PS_FREE 0

/*
 * System task Node
 * 系统任务节点
 */
typedef struct OS_TASK_NODE
{
    /* task fun call pointer*/
    void (*Task)();

    /* task stack pointer*/
    GXYOS_STACK * StackPoi;
    /* task name */
    GXYOS_CHAR Task_Name[OS_MAX_TASK_NAME_SIZE];

    /* task priority  */
    GXYOS_U8 Priority;
    /* task status    */
    GXYOS_TASK_STATE TASK_STATE;

    /* Node List     */
    struct OS_TASK_NODE * NextNode;


}OS_TASK_NODE;



/*
 * System Task Index Table
 * 系统任务索引表
 */

typedef struct OS_TASK_INDEX_TABLE
{
    GXYOS_U8 Priority;
    OS_TASK_NODE* Task_Node;
    GXYOS_TASK_STATE OS_STATE;

}OS_TASK_INDEX_TABLE;


typedef struct OS_TASK_MANAGE_TABLE
{
    GXYOS_U8 UP_PRI;
    OS_TASK_NODE* UP_Task_Node;
    GXYOS_U16 UP_OS_POX;

}OS_TASK_MANAGE_TABLE;





GXYOS_ERR OS_Task_init();
GXYOS_ERR OS_CHICK();
GXYOS_ERR OS_New_Task(
        void (*Task)(),
        GXYOS_U16 Stack_size,
        GXYOS_CHAR *Task_name,
        GXYOS_U8 Task_Pri
);
GXYOS_VOID_POI OS_next_run();
void GET_RUNNING_MESSAGE();
GXYOS_U32 OS_TASK_NUM_GET();

#endif 
