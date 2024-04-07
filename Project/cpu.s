NVIC_INT_CTRL   EQU     0xE000ED04                              ; Interrupt control state register.
NVIC_SYSPRI14   EQU     0xE000ED22                              ; System priority register (priority 14).
NVIC_PENDSV_PRI EQU           0xFF                              ; PendSV priority value (lowest).
NVIC_PENDSVSET  EQU     0x10000000                              ; Value to trigger PendSV exception.


       ;��࿪ʼ��ʽ
	   ;AREA  C�������
	   ;��ʾ����
	   ;ֻ������
	   
	   
		AREA |.text|, CODE , READONLY

		EXPORT PENDSV
		EXPORT INITPendSv
		EXPORT PendSV_Handler
		
			
		EXTERN  now_stack_p
        EXTERN  next_stack_p
			
			
			
INITPendSv 

			;���� PendSv �ж����ȼ���
			LDR     R0, =NVIC_SYSPRI14
			LDR     R1, =NVIC_PENDSV_PRI;
			STRB    R1, [R0]
			BX LR
			

			


PendSV_Handler

		    CPSID   I  			; �ر����ж�
			
			MRS     R0, PSP                                             ; ��״̬�Ĵ��������ݴ�����ͨ�üĴ�����  �ж� PSP �Ƿ��� 0
			CBZ     R0, OS_CPU_PendSVHandler_nosave                     ; �ж� R0 (PSP) �Ƿ� �� 0 �����0 ��һ�������ý����ֳ����� ֱ����ת�� nosave
		   
			SUBS    R0, R0, #0x20                                       ; ���浱ǰ�����CPU�ֳ�
			STM     R0, {R4-R11}
			
			LDR     R1, =now_stack_p                                       ; ��õ�ǰ���е����񱣴�� ��ջ��ַ �� �����ַ
			LDR     R1, [R1]
			STR     R0, [R1]                                            ; R0 is SP of process being switched out
		
																		; ���˴� ���е�cpu �ֳ� �Ѿ��������
OS_CPU_PendSVHandler_nosave
			
			LDR     R0, =now_stack_p                                       ; ���Ӧ�ñ����� ��ǰ����� c �еĶ�ջָ��
			LDR     R1, =next_stack_p         ; ��ȡ�� ��ջָ�� �� �洢 ��ַ
			LDR     R1,[R1]
			STR     R1,[R0]       ; now_stack_p Ӧ�ô� ��ջָ��� �Ĵ洢 ��ַ   OK 
			LDR     R1,[R1]
			;LDR     R2, [R1]       ; ����  R2 �� ��ջָ�� ��
			
		 
			                                           ; R0 is new process SP; SP = OSTCBHighRdy->OSTCBStkPtr;
			LDM     R1, {R4-R11}                                        ; Restore r4-11 from new process stack
			ADDS    R1, R1, #0x20
			
            ;R0 ��ĵ�ַ�� �����Ƕ�ջ��ַ	 �洢�ռ�		
			
			LDR     R0, [R0]
			STR     R1, [R0] 
			;  ���� ����R0 �洢�� �������Ķ�ջ ��ַ�� 
			
	        ;       
			MSR     PSP, R1                                             ; Load PSP with new process SP
			ORR     LR , LR, #0x04                                       ; Ensure exception return uses process stack
			CPSIE   I					
			BX      LR                                                  ; Exception return will restore remaining context

			
PENDSV 			
				;����PendSv�쳣
				
			    LDR     R0, =NVIC_INT_CTRL
				LDR     R1, =NVIC_PENDSVSET
				STR     R1, [R0]
				BX      LR
				
				CPSIE   I
				
			
		END