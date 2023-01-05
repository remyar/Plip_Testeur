//=============================================================================
//
// PROJET       : KIGAZ 2012
// HEADER       : Task.h
//
//=============================================================================
#ifndef _TASK_H_
#define _TASK_H_

//-----------------------------------------------------------------------------
// Fichiers Inclus
//-----------------------------------------------------------------------------
#include <Arduino.h>

#include "Event.h"

#define MAX_TASKS   8


//-----------------------------------------------------------------------------
// Definition de type
//-----------------------------------------------------------------------------
typedef bool (*PTR_TASK_INIT_FUNC)(void);
typedef bool (*PTR_TASK_UPDATE_FUNC)(void *);
typedef void (*PTR_TASK_RUN_FUNC)(void);

typedef struct
{
    uint8_t idx;
    uint8_t status;
    int16_t period;
    int16_t counter;
    FIFOEvent events;

    int32_t taskLength;
    int32_t minTaskLength;
    int32_t maxTaskLength;

    uint32_t totalTickUsed;

    PTR_TASK_INIT_FUNC init;
    PTR_TASK_UPDATE_FUNC update;
    PTR_TASK_RUN_FUNC run;

    String name;
} s_TASK;

enum
{
    NO_STATUS = 0,
    INIT_STATUS,
    WAITING_STATUS,
    READY_STATUS,
    RUNNING_STATUS,
    END_RUN_STATUS
};


extern s_TASK   tasks[MAX_TASKS];
//-----------------------------------------------------------------------------
// Fonctions publiques
//-----------------------------------------------------------------------------
bool TASK_Init(s_TASK *t);
bool TASK_Update(uint8_t idx);
bool TASK_SetActive(uint8_t idx, bool isActive);
bool TASK_SetPeriod(uint8_t idx, uint16_t time, bool toUpdateTimer);
bool TASK_IsRunning(uint8_t idx);
/*s_EVENT *TASK_Event(uint8_t idx);
void TASK_ImmediateEvent(uint8_t idx);*/

#endif //--- _TASK_H_