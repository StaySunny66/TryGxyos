#include "usart1.h"
#include "led.h"
#include "key.h"
#include "Gxyos.h"







void task1(){
	
	  
	
	   while(1){
			 
				 GXYOS_PRINTLN("T1");
			   Task_delay(1000);
	 
		 }
    
       //Task_delay(1000);
}
void task2(){
      //Task_delay(500);
    while(1){
	      GXYOS_PRINTLN("T2");
			  Task_delay(2000);
	  }
}

void task3(){
      //Task_delay(500);
    while(1){
	      GXYOS_PRINTLN("T3");
			  Task_delay(3000);
			  //Task_delay(500);
	}
}



int main() {
	
	  uart1_init(115200);
    GxyosInit();
	
	
   	OS_New_Task(task1,100, "Hello task",1);
		OS_New_Task(task2,100, "Hi task",1);
	  OS_New_Task(task3,100, "Hi task 3",1);
    
    
	
	  GXYOSStart();
	
	
    while(1){
    }
    return 0;
}






