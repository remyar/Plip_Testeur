//=============================================================================
//
// PROJET       : POSTE FIXE 2013
// HEADER       : Tick.h
//
//=============================================================================
#ifndef _TICK_H_
#define _TICK_H_

//-----------------------------------------------------------------------------
// Fichiers Inclus
//-----------------------------------------------------------------------------

#define TICK_PERIOD 1.
#define TICK_1_MS (1. / TICK_PERIOD)
#define TICK_10_MS (10. / TICK_PERIOD)
#define TICK_100_MS (100. / TICK_PERIOD)
#define TICK_1_SEC (1000. / TICK_PERIOD)

//-----------------------------------------------------------------------------
// Fonctions publiques
//-----------------------------------------------------------------------------
void TICK_Init(void);
uint32_t TICK_Count(void);
uint32_t TICK_nbCountSince(uint32_t lastCount);
uint32_t TICK_nbMsSince(uint32_t lastCount);
uint16_t TICK_nbSecSince(uint32_t lastCount);
uint16_t TICK_nbMinSince(uint32_t lastCount);
uint16_t TICK_nbHourSince(uint32_t lastCount);
void TICK_GetTimeSince(uint32_t lastCount, uint8_t *nbHour, uint8_t *nbMin, uint8_t *nbSec, uint16_t *nbMs);
void TICK_HandleIT(void);

#endif //--- _TICK_H_