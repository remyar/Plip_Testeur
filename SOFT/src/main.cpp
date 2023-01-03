#include "./Low-Level/board.h"
#include "./led/led.h"
#include "./screen/screen.h"
#include "./keyboard/keyboard.h"

void setup()
{
    BOARD_Init();

    SCHEDULER_AddTask("KEYBOARD", KEYBOARD_TaskInit, NULL, KEYBOARD_TaskRun, 100, KEYBOARD_TASK_ID);
    SCHEDULER_AddTask("SCREEN", SCREEN_TaskInit, SCREEN_TaskUpdate, SCREEN_TaskRun, 10, SCREEN_TASK_ID);
    SCHEDULER_AddTask("LED", LED_TaskInit, LED_TaskUpdate, LED_TaskRun, 50, LED_TASK_ID);

    SCHEDULER_Init();
}

void loop()
{
    SCHEDULER_Run();
}