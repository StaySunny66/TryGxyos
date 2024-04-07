NVIC_INT_CTRL   EQU     0xE000ED04                              ; Interrupt control state register.
NVIC_SYSPRI14   EQU     0xE000ED22                              ; System priority register (priority 14).
NVIC_PENDSV_PRI EQU           0xFF                              ; PendSV priority value (lowest).
NVIC_PENDSVSET  EQU     0x10000000                              ; Value to trigger PendSV exception.


       ;汇编开始格式
	   ;AREA  C联代码端
	   ;表示代码
	   ;只读属性
	   
	   
		AREA |.text|, CODE , READONLY

		EXPORT PENDSV
		EXPORT INITPendSv
		EXPORT PendSV_Handler
		
			
		EXTERN  now_stack_p
        EXTERN  next_stack_p
			
			
			
INITPendSv 

			;设置 PendSv 中断优先级啊
			LDR     R0, =NVIC_SYSPRI14
			LDR     R1, =NVIC_PENDSV_PRI;
			STRB    R1, [R0]
			BX LR
			

			


PendSV_Handler

		    CPSID   I  			; 关闭总中断
			
			MRS     R0, PSP                                             ; 将状态寄存器的内容传送至通用寄存器。  判断 PSP 是否是 0
			CBZ     R0, OS_CPU_PendSVHandler_nosave                     ; 判断 R0 (PSP) 是否 是 0 如果是0 第一次任务不用进行现场保存 直接跳转到 nosave
		   
			SUBS    R0, R0, #0x20                                       ; 保存当前任务的CPU现场
			STM     R0, {R4-R11}
			
			LDR     R1, =now_stack_p                                       ; 获得当前运行的任务保存的 堆栈地址 的 保存地址
			LDR     R1, [R1]
			STR     R0, [R1]                                            ; R0 is SP of process being switched out
		
																		; 到此处 所有的cpu 现场 已经保存完成
OS_CPU_PendSVHandler_nosave
			
			LDR     R0, =now_stack_p                                       ; 这个应该保存着 当前任务的 c 中的堆栈指针
			LDR     R1, =next_stack_p         ; 获取了 堆栈指针 的 存储 地址
			LDR     R1,[R1]
			STR     R1,[R0]       ; now_stack_p 应该存 堆栈指针的 的存储 地址   OK 
			LDR     R1,[R1]
			;LDR     R2, [R1]       ; 现在  R2 是 堆栈指针 了
			
		 
			                                           ; R0 is new process SP; SP = OSTCBHighRdy->OSTCBStkPtr;
			LDM     R1, {R4-R11}                                        ; Restore r4-11 from new process stack
			ADDS    R1, R1, #0x20
			
            ;R0 存的地址是 现在是堆栈地址	 存储空间		
			
			LDR     R0, [R0]
			STR     R1, [R0] 
			;  好了 现在R0 存储的 是真正的堆栈 地址了 
			
	        ;       
			MSR     PSP, R1                                             ; Load PSP with new process SP
			ORR     LR , LR, #0x04                                       ; Ensure exception return uses process stack
			CPSIE   I					
			BX      LR                                                  ; Exception return will restore remaining context

			
PENDSV 			
				;触发PendSv异常
				
			    LDR     R0, =NVIC_INT_CTRL
				LDR     R1, =NVIC_PENDSVSET
				STR     R1, [R0]
				BX      LR
				
				CPSIE   I
				
			
		END