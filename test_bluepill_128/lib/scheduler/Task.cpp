//=============================================================================
//
// PROJET       : POSTE_FIXE 2013
// MODULE       : Task.c
// DESCRIPTION  : Gestion d'une tache
//
//=============================================================================

//=============================================================================
//--- DECLARATIONS
//=============================================================================

//-----------------------------------------------------------------------------
// Fichiers Inclus
//-----------------------------------------------------------------------------
#include "Task.h"

//-----------------------------------------------------------------------------
// Constantes
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Variables globales
//-----------------------------------------------------------------------------


//=============================================================================
//--- DEFINITIONS
//=============================================================================

//-----------------------------------------------------------------------------
// FONCTION    : TASK_Init
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
bool TASK_Init(s_TASK *t)
{
    t->status = INIT_STATUS;
    t->counter = t->period;
    t->totalTickUsed = 0;
    return t->init();
}

//-----------------------------------------------------------------------------
// FONCTION    : TASK_Update
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
bool TASK_Update(uint8_t idx)
{
    bool eventOK;
    s_TASK *t = &tasks[idx];
    s_EVENT sE = t->events.peek();
    //--- Verification si evenement attendu par la tache
    //--- et mise a jour de la tache au besoin
    eventOK = t->update(&sE);

    if (eventOK == true)
    {
        //--- Si la tache est prete, on la passe en Active
        t->status = READY_STATUS;
    }
    else
    {
        //--- Sinon on la passe en attente
        t->status = WAITING_STATUS;
    }

    return eventOK;
}

//-----------------------------------------------------------------------------
// FONCTION    : TASK_SetActive
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
bool TASK_SetActive(uint8_t idx, bool isActive)
{
    s_TASK *t = &tasks[idx];

    if (isActive == true)
        t->counter = 0;
    else
        t->counter = t->period;

    return true;
}

//-----------------------------------------------------------------------------
// FONCTION    : TASK_SetPeriod
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
bool TASK_SetPeriod(uint8_t idx, uint16_t time, bool toUpdateTimer)
{
    s_TASK *t = &tasks[idx];

    t->period = time;
    if (toUpdateTimer == true)
        t->counter = t->period;

    return true;
}

//-----------------------------------------------------------------------------
// FONCTION    : TASK_IsRunning
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
bool TASK_IsRunning(uint8_t idx)
{
    return (bool)(tasks[idx].status == RUNNING_STATUS);
}

/*
//-----------------------------------------------------------------------------
// FONCTION    : TASK_Event
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
s_EVENT *TASK_Event(uint8_t idx)
{
    return &(tasks[idx].event);
}

//-----------------------------------------------------------------------------
// FONCTION    : TASK_ImmediateEvent
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
void TASK_ImmediateEvent(uint8_t idx)
{
}

*/