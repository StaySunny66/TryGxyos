#include <stdio.h>
#include "OS_LIB/Gxyos.h"


////// WINDOWS LIB
#include "windows.h"





void main_loop();


void task1(){
    GXYOS_PRINTLN("TASK 1 HELLO ...")
    Task_delay(10);
}
void task2(){
    Task_delay(36);
    GXYOS_PRINTLN("TASK 2 HI ...")
}
int main() {
    GxyosInit();
    OS_New_Task(task1,20, "Hello task",1);
    OS_New_Task(task2,20, "Hi task",1);
    while(1){
        main_loop();
    }
    return 0;
}
void main_loop(){
    ///Ä£ÄâÓ²¼þTICK
    Sleep(1);
    GxyosTick();

}
