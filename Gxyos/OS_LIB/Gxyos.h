//
// Created by 17901 on 2023/1/8.
//

#ifndef GXYOS_GXYOS_H
#define GXYOS_GXYOS_H



/*********************************************
 *  describe : OS's ERR code
 *  描述      ：操作系统的错误代码
 *
 *********************************************/
#define GXYOS_ERR unsigned char
#define GXYOS_OK 0
#define GXYOS_FATAL_ERR 1
#define GXYOS_TASK_ADD_ERR 2
#define GXYOS_TASK_PRI_ERR 3
#define GXYOS_TASK_NAME_ERR 6
#define GXYOS_TASK_STACK_OVER_ERR 7
#define GXYOS_TASK_NUM_OVER_ERR 8

#define GXYOS_MEM_NEW_ERR  4
#define GXYOS_MEM_CPY_ERR  5


#define GXYOS_INT_STATE GXYOS_U8
#define GXYOS_ENABLE 1
#define GXYOS_DISABLE 0





/*
 * Global OS valuable
 * 系统全局变量
 */

#include "../OS_PORT/os_conf.h"
#include "../OS_PORT/os_porting.h"
#include "GxyTask.h"
#include "GxyosTime.h"



/*********************************************
 *  describe : OS' basic Fun
 *
 *
 *********************************************/

GXYOS_ERR GxyosInit(void);
void GxyosTick();
void GXYOSStart();




#endif 
