//=============================================================================
//
// PROJET       : POSTE FIXE 2013
// MODULE       : Tick.c
// DESCRIPTION  : Gestion du Tick periodique
//
//=============================================================================

//=============================================================================
//--- DECLARATIONS
//=============================================================================

//-----------------------------------------------------------------------------
// Fichiers Inclus
//-----------------------------------------------------------------------------
#include "Scheduler.h"
#include "Tick.h"

//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------
#define DIFF_COUNT(R, C, L) (R) = ((C) >= (L)) ? (C) - (L) : (C) + 0xFFFFFFFF + 1 - (L)
#define _tick millis()
//-----------------------------------------------------------------------------
// Variables globales
//-----------------------------------------------------------------------------

//=============================================================================
//--- DEFINITIONS
//=============================================================================

//-----------------------------------------------------------------------------
// FONCTION    : TICK_Init
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
void TICK_Init(void)
{
}

//-----------------------------------------------------------------------------
// FONCTION    : TICK_Count
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
uint32_t TICK_Count(void)
{
    return _tick;
}

//-----------------------------------------------------------------------------
// FONCTION    : TICK_nbCountSince
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
uint32_t TICK_nbCountSince(uint32_t lastCount)
{
    uint64_t res;
    uint32_t newCount;

    newCount = _tick;
    DIFF_COUNT(res, newCount, lastCount);

    return (uint32_t)(res);
}

//-----------------------------------------------------------------------------
// FONCTION    : TICK_nbMsSince
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
uint32_t TICK_nbMsSince(uint32_t lastCount)
{
    return (uint32_t)((float)TICK_nbCountSince(lastCount) / TICK_1_MS);
}

//-----------------------------------------------------------------------------
// FONCTION    : TICK_nbSecSince
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
uint16_t TICK_nbSecSince(uint32_t lastCount)
{
    uint32_t res;
    uint32_t newCount;

    newCount = _tick;
    DIFF_COUNT(res, newCount, lastCount);

    return (uint16_t)(res / (uint32_t)TICK_1_SEC);
}

//-----------------------------------------------------------------------------
// FONCTION    : TICK_nbMinSince
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
uint16_t TICK_nbMinSince(uint32_t lastCount)
{
    uint32_t res;
    uint32_t newCount;

    newCount = _tick;
    DIFF_COUNT(res, newCount, lastCount);

    return (uint16_t)(res / (60 * (uint32_t)TICK_1_SEC));
}

//-----------------------------------------------------------------------------
// FONCTION    : TICK_nbHourSince
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
uint16_t TICK_nbHourSince(uint32_t lastCount)
{
    uint32_t res;
    uint32_t newCount;

    newCount = _tick;
    DIFF_COUNT(res, newCount, lastCount);

    return (uint8_t)(res / ((uint32_t)3600 * (uint32_t)TICK_1_SEC));
}

//-----------------------------------------------------------------------------
// FONCTION    : TICK_GetTimeSince
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
void TICK_GetTimeSince(uint32_t lastCount, uint8_t *nbHour, uint8_t *nbMin, uint8_t *nbSec, uint16_t *nbMs)
{
    uint32_t res;
    uint32_t newCount;

    newCount = _tick;
    DIFF_COUNT(res, newCount, lastCount);

    //--- Calcul des heures
    *nbHour = (uint8_t)(res / ((uint32_t)3600 * (uint32_t)TICK_1_SEC));
    res %= ((uint32_t)3600 * (uint32_t)TICK_1_SEC);

    //--- Calcul des minutes
    *nbMin = (uint8_t)(res / (60 * (uint32_t)TICK_1_SEC));
    res %= (60 * (uint32_t)TICK_1_SEC);

    //--- Calcul des secondes
    *nbSec = (uint8_t)(res / (uint32_t)TICK_1_SEC);
    res %= (uint32_t)TICK_1_SEC;

    //--- Calcul les mili-secondes
    *nbMs = (uint16_t)res;
}

//=============================================================================
//--- INTERRUPTIONS
//=============================================================================

//-----------------------------------------------------------------------------
// INTERRUPTION :  TICK_HandleIT
//
// DESCRIPTION :  Interruption du timer
//-----------------------------------------------------------------------------
void TICK_HandleIT(void)
{
    SCHEDULER_Update();
}