//================================================================================================//
//                                                                                                //
// PROJET       : DongleWifi GoodRace                                                             //
// MODULE       : Board                                                                           //
// DESCRIPTION  :                                                                                 //
// CREATION     : 27/01/2020                                                                      //
// HISTORIQUE   :                                                                                 //
//                                                                                                //
//================================================================================================//

//================================================================================================//
//                                        FICHIERS INCLUS                                         //
//================================================================================================//

#include "./led.h"
#include "../Low-Level/board.h"

//================================================================================================//
//                                            DEFINES                                             //
//================================================================================================//

//================================================================================================//
//                                          ENUMERATIONS                                          //
//================================================================================================//

//================================================================================================//
//                                      STRUCTURES ET UNIONS                                      //
//================================================================================================//

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 VARIABLES PRIVEES ET PARTAGEES                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------//
//---                                         Privees                                          ---//
//------------------------------------------------------------------------------------------------//
static e_LED_STATE eLedState = LED_OFF;
static uint32_t toggleDelay = 0;
static bool ledState = false;
static unsigned long _ms = millis();

//------------------------------------------------------------------------------------------------//
//---                                        Partagees                                         ---//
//------------------------------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 FONCTIONS PRIVEES ET PARTAGEES                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------//
//---                                         Privees                                          ---//
//------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
//---                                        Partagees                                         ---//
//------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------
// FONCTION    : COMPC_TaskInit
//
// DESCRIPTION : Initialisation de la carte : GPIO, Clocks, Interruptions...
//--------------------------------------------------------------------------------------------------
bool LED_TaskInit(void)
{
    _ms = millis();
    return true;
}

bool LED_TaskUpdate(void *p)
{
    s_EVENT *event = (s_EVENT *)p;
    if (event->type & LED_EVENT)
    {
        eLedState = (e_LED_STATE)event->led.state;
        toggleDelay = event->led.delay;
        EVENT_Clear(LED_TASK_ID, LED_EVENT);
    }

    return true;
}

void LED_TaskRun(void)
{

    switch (eLedState)
    {
    case (LED_ON):
    {
        ledState = true;
        break;
    }
    case (LED_OFF):
    {
        ledState = false;
        break;
    }
    case (LED_TOOGLE):
    {
        if ((millis() - _ms) > toggleDelay)
        {
            ledState = (ledState == false) ? true : false;
            _ms = millis();
        }

        break;
    }
    }

    GPIO_BUILTIN_LED(ledState);
}
