//
// Created by 17901 on 2023/1/9.
//

#include "os_porting.h"

/*
 *  Import You Device's STD Lib
 *  导入你设备的标准库
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"


/*
 * 导入你设备测硬件库
 */

#include "stm32f4xx.h"
#include "common.h"


/// os tick 
void SysTick_Handler(void)
{
	
	GxyosTick();
 
}



void Systick_init(GXYOS_U16 ms){
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	 GXYOS_U32 Reload_value = 168000 * ms;

   SysTick->LOAD = Reload_value & SysTick_LOAD_RELOAD_Msk;
	 SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk|SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_TICKINT_Msk;
	
	NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;      //串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =4;		   //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			   //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	  //根据指定的参数初始化VIC寄存器、
	
	


}



//// 适配硬件的中断配置
GXYOS_ERR OS_Interrupt_Configuration(GXYOS_INT_STATE State){
    if(State == GXYOS_ENABLE){
			
			
         INTX_ENABLE();
			
			  
       // GXYOS_LOG("Interrupt Enable !");

    }else{
      //  GXYOS_LOG("Interrupt Disable !");
			   INTX_DISABLE();

    }

    return GXYOS_OK;

}



GXYOS_VOID_POI OS_MEM_CALLOC(GXYOS_U32 size,GXYOS_U32 num){
    return calloc(num,size);
}

GXYOS_ERR OS_MEM_FREE(GXYOS_VOID_POI address){
    free(address);
    return GXYOS_OK;
}

GXYOS_ERR OS_Str_Cpy(GXYOS_CHAR *dest, const char *src){
    if(strcpy(dest,src)==GXYOS_NULL) return GXYOS_MEM_CPY_ERR;
}

GXYOS_U32 OS_STR_LEN(const char *src){
    return strlen(src);
}


void LOGD(const char* format, ...)
{
    printf("Debug => ");
    va_list vp;
    va_start(vp, format);
    vprintf (format, vp);
    va_end  (vp);
    printf  ("\n");
}







