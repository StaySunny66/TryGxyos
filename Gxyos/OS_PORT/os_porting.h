//
// Created by 17901 on 2023/1/9.
//
#ifndef GXYOS_OS_PORTING_H
#define GXYOS_OS_PORTING_H

#include "../OS_LIB/Gxyos.h"
#include "stdio.h"


#define GXYOS_LOG(fmt, ...) {printf("[%s:%d] "fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);}
#define GXYOS_PRINTLN(fmt, ...) {printf(" "fmt"\r\n", ##__VA_ARGS__);}

void OSContext(void);
GXYOS_VOID_POI OS_MEM_CALLOC(GXYOS_U32 size,GXYOS_U32 num);
GXYOS_ERR OS_MEM_FREE(GXYOS_VOID_POI address);
GXYOS_ERR OS_Str_Cpy(GXYOS_CHAR *dest, const char *src);
GXYOS_U32 OS_STR_LEN(const char *src);
GXYOS_ERR OS_Interrupt_Configuration(GXYOS_INT_STATE State);
void Systick_init(GXYOS_U16 ms);









#endif 


