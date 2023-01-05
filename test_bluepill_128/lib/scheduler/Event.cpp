//=============================================================================
//
// PROJET       : POSTE FIXE 2013
// MODULE       : Event.c
// DESCRIPTION  : Gestion d'un Evenement
//
//=============================================================================

//=============================================================================
//--- DECLARATIONS
//=============================================================================

//-----------------------------------------------------------------------------
// Fichiers Inclus
//-----------------------------------------------------------------------------
#include "Event.h"
#include "Task.h"


//=============================================================================
//--- DEFINITIONS
//=============================================================================

extern s_TASK tasks[MAX_TASKS];


FIFOEvent::FIFOEvent()
{
    head = 0;
    tail = 0;
    numElements = 0;
}

FIFOEvent::~FIFOEvent()
{
}

void FIFOEvent::push(s_EVENT data)
{
    if (numElements == EVENTS_FIFO_SIZE)
    {
        return;
    }
    else
    {
        // Increment size
        numElements++;

        // Only move the tail if there is more than one element
        if (numElements > 1)
        {
            // Increment tail location
            tail++;

            // Make sure tail is within the bounds of the array
            tail %= EVENTS_FIFO_SIZE;
        }

        // Store data into array
        buffer[tail] = data;
    }
}

s_EVENT FIFOEvent::peek()
{
    if (numElements == 0){
        //Serial.println(F("Buffer empty"));
        s_EVENT e;
        e.type = 0;
        return e;  
    } else {
        s_EVENT data = buffer[head];
        return data;
    }
}

s_EVENT FIFOEvent::pop()
{
    if (numElements == 0)
    {
        //Serial.println(F("Buffer empty"));
        s_EVENT e;
        e.type = 0;
        return e;
    }
    else
    {
        // Decrement size
        numElements--;

        s_EVENT data = buffer[head];

        if (numElements >= 1)
        {
            // Move head up one position
            head++;

            // Make sure head is within the bounds of the array
            head %= EVENTS_FIFO_SIZE;
        }

        return data;
    }
}

int FIFOEvent::size()
{
    return numElements;
}


//-----------------------------------------------------------------------------
// FONCTION    : EVENT_None
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
void EVENT_None(uint8_t TaskId)
{
    for (int i = 0; i < MAX_TASKS; i++)
    {
        if (tasks[i].idx == TaskId)
        {
            while (tasks[i].events.size())
            {
                tasks[i].events.pop();
            }
        }
    }

}

//-----------------------------------------------------------------------------
// FONCTION    : EVENT_Clear
//
// DESCRIPTION :
//-----------------------------------------------------------------------------
void EVENT_Clear(uint8_t TaskId, uint32_t type)
{
    for (int i = 0; i < MAX_TASKS; i++)
    {
        if (tasks[i].idx == TaskId)
        {
            if ( tasks[i].events.size()){
                tasks[i].events.pop();
            }
        }
    }
}

void EVENT_Push(uint8_t TaskId, uint32_t type, void *pValue)
{
    for (int i = 0; i < MAX_TASKS; i++)
    {
        if (tasks[i].idx == TaskId)
        {
            s_EVENT sE;
            sE.type = type;
            if (type == KEYB_EVENT)
            {
                s_KEYB_EVENT * v = (s_KEYB_EVENT *)pValue;
                sE.key.code = v->code;
                sE.key.isLong = v->isLong;
            }
            if (type == LED_EVENT){
                s_LED_EVENT * v = (s_LED_EVENT *)pValue;
                sE.led.state = v->state;
                sE.led.delay = v->delay;
            }
            if (type == DISPLAY_EVENT){
                s_DISPLAY_EVENT * v = (s_DISPLAY_EVENT *)pValue;
                sE.display.index = v->index;
                sE.display.value = v->value;
            }
            if (type == COMPC_EVENT){
                s_COMPC_EVENT * v = (s_COMPC_EVENT *)pValue;
                sE.compc.length = v->length;
                sE.compc.str = v->str;
            }
            if (type == PLIP_EVENT){
                s_PLIP_EVENT * v = (s_PLIP_EVENT *)pValue;
                sE.plip.code = v->code;
            }
            if (type == MCU_EVENT){
                s_MCU_EVENT * v = (s_MCU_EVENT *)pValue;
                sE.mcu.state = v->state;
            }

            tasks[i].events.push(sE);
        }
    }
}

bool EVENT_HasEvent(void){
    bool val = false;
    for (int i = 0; i < MAX_TASKS; i++){
        if ( tasks[i].events.size() > 0 ){
            val = true;
        }
    }
    return val;
}