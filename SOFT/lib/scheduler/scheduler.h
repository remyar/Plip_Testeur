//=============================================================================
//
// PROJET       :
// HEADER       : Scheduler.h
//
//=============================================================================
#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

//-----------------------------------------------------------------------------
// Fichiers Inclus
//-----------------------------------------------------------------------------
#include <Arduino.h>
#include "Task.h"
#include "Tick.h"

//-----------------------------------------------------------------------------
// Fonctions publiques
//-----------------------------------------------------------------------------
void SCHEDULER_Init(void);
void SCHEDULER_Update(void);
void SCHEDULER_Run(void);
void SCHEDULER_AddTask(String name , PTR_TASK_INIT_FUNC initFunc , PTR_TASK_UPDATE_FUNC updFunc , PTR_TASK_RUN_FUNC runFunc , uint16_t period , uint16_t TaskId);

#endif //--- _SCHEDULER_H_