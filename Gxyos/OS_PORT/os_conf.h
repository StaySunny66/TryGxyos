//
// Created by 17901 on 2023/1/9.
// @author : StaySunny
//

#ifndef GXYOS_OS_CONF_H
#define GXYOS_OS_CONF_H



#define OS_LOGO_EN 1

#define OS_MSG_LOG  1
#define OS_ERR_LOG  1


// 系统时间 调式开关
#define  OS_TIME_DEBUG 0

#define  OS_TASK_DELAY_TABLE_DEBUE 0

#define  OS_MANAGE_DEBUG 0




/*
 * porting the basic type of data
 *
 */
#define GXYOS_CHAR char
#define GXYOS_U8   unsigned char
#define GXYOS_U16  unsigned short
#define GXYOS_U32  unsigned int
#define GXYOS_VOID_POI void *
#define GXYOS_STACK GXYOS_U32
#define GXYOS_NULL 0


/*
 * OS TASK STATE
 * Only one Task Can be Running!
 */

#define GXYOS_TASK_STATE GXYOS_U8
#define OS_TASK_STATE_READY   1
#define OS_TASK_STATE_RUNNING 2
#define OS_TASK_STATE_BLOCKED 3
#define OS_TASK_STATE_SUSPEND 4



/*
 * config some other options
 *
 */

#define OS_MAX_TASK 32
#define OS_MAX_TASK_NAME_SIZE 20
#define OS_MAX_STACK_SIZE  400





#endif 
