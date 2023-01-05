#include "./Low-Level/board.h"
#include "./led/led.h"
#include "./screen/screen.h"
#include "./keyboard/keyboard.h"
#include "./plip/plip.h"
#include "./mcu/mcu.h"
#include "./compc/COM_PC.h"

void setup()
{

    BOARD_Init();

    SCHEDULER_AddTask("68HC11", MCU_TaskInit, MCU_TaskUpdate, MCU_TaskRun, 100, MCU_TASK_ID);
    SCHEDULER_AddTask("PLIP", PLIP_TaskInit, NULL, PLIP_TaskRun, 10, PLIP_TASK_ID);
    SCHEDULER_AddTask("KEYBOARD", KEYBOARD_TaskInit, NULL, KEYBOARD_TaskRun, 100, KEYBOARD_TASK_ID);
    SCHEDULER_AddTask("SCREEN", SCREEN_TaskInit, SCREEN_TaskUpdate, SCREEN_TaskRun, 10, SCREEN_TASK_ID);
    SCHEDULER_AddTask("LED", LED_TaskInit, LED_TaskUpdate, LED_TaskRun, 50, LED_TASK_ID);
    SCHEDULER_AddTask("COMPC", COMPC_TaskInit, COMPC_TaskUpdate, COMPC_TaskRun, 10, COMPC_TASK_ID);

    SCHEDULER_Init();
}

void loop()
{
    SCHEDULER_Run();
}