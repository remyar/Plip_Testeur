//=============================================================================
//
// PROJET       : POSTE FIXE 2013
// HEADER       : Event.h
//
//=============================================================================
#ifndef EVENT_H
#define EVENT_H

//-----------------------------------------------------------------------------
// Fichiers Inclus
//-----------------------------------------------------------------------------
#include <Arduino.h>

//-----------------------------------------------------------------------------
// Definition de type
//-----------------------------------------------------------------------------
#define EVENTS_FIFO_SIZE 1

#define EVENT_HAS(E, K) (((E)->type & (K)) == (K))

typedef struct //--- s_KEYB_EVENT
{
    uint8_t code;
    bool isLong;
} s_KEYB_EVENT;

typedef struct //--- s_LED_EVENT
{
    uint8_t state;
    uint32_t delay;
} s_LED_EVENT;

typedef struct //--- s_DISPLAY_EVENT
{
    uint8_t index;
    uint8_t value;
} s_DISPLAY_EVENT;

typedef struct //--- s_COMPC_EVENT
{
    uint8_t length;
    String str;
} s_COMPC_EVENT;

typedef struct //--- s_EVENT
{
    uint32_t type;
    //s_COMPC_EVENT compc;
    s_KEYB_EVENT key;
    s_LED_EVENT led;
    s_DISPLAY_EVENT display;
} s_EVENT;

class FIFOEvent
{
private:
    int head;
    int tail;
    int numElements;
    s_EVENT buffer[EVENTS_FIFO_SIZE];

public:
    FIFOEvent();
    ~FIFOEvent();
    void push(s_EVENT data);
    s_EVENT pop();
    s_EVENT peek();
    int size();
};

#define NO_EVENT 0x0000
#define KEYB_EVENT (uint32_t)(1 << 1)
#define LED_EVENT (uint32_t)(1 << 2)
#define DISPLAY_EVENT (uint32_t)(1 << 3)
#define COMPC_EVENT (uint32_t)(1 << 4)

//-----------------------------------------------------------------------------
// Fonctions publiques
//-----------------------------------------------------------------------------
void EVENT_None(uint8_t TaskId);
void EVENT_Clear(uint8_t TaskId, uint32_t type);
void EVENT_Push(uint8_t TaskId, uint32_t type, void *pValue);

#endif //--- EVENT_H