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

#include "./plip.h"

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
static bool bits[3][24];
volatile bool trigger = false;
static uint16_t nbBits = 0;
static uint8_t frameNumber = 0;
static bool success = false;
static unsigned long _ms = millis();
int8_t E[10];
static uint32_t _us = micros();
//------------------------------------------------------------------------------------------------//
//---                                        Partagees                                         ---//
//------------------------------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 FONCTIONS PRIVEES ET PARTAGEES                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------//
//---                                         Privees                                          ---//
//------------------------------------------------------------------------------------------------//
void _ISR() // ISR function excutes when push button at pinD2 is pressed
{
    trigger = true;
    digitalWrite(PA9, HIGH);
    if ((micros() - _us) > 100000)
    {
        //-- start
        nbBits = 0;
        frameNumber = 0;
        _us = micros();
    }

    uint32_t _dd = (micros() - _us);

    if (_dd > 450 && _dd <= 520)
    {
        bits[frameNumber][nbBits] = false;
        nbBits++;
        if (nbBits >= 24)
        {
            nbBits = 0;
            frameNumber++;
            if (frameNumber > 3)
            {
                frameNumber = 0;
            }
        }
    }
    else if (_dd > 1800 && _dd <= 2200)
    {
        bits[frameNumber][nbBits] = true;
        nbBits++;
        if (nbBits >= 24)
        {
            nbBits = 0;
            frameNumber++;
            if (frameNumber > 3)
            {
                frameNumber = 0;
            }
        }
    }

    digitalWrite(PA9, LOW);
    _us = micros();
}

int8_t decode(uint8_t idx)
{
    int8_t val = -1;
    bool bit0 = bits[0][(idx * 2)];
    bool bit1 = bits[0][(idx * 2) + 1];

    if ((bit0 == true) && (bit1 == false))
    {
        val = 0;
    }
    else if ((bit0 == true) && (bit1 == true))
    {
        val = 1;
    }

    return val;
}

uint8_t decode_2(int8_t E0, int8_t E1)
{
    uint8_t val = 9;
    if (E0 == 0 && E1 == 0)
    {
        val = 4;
    }
    else if (E0 == -1 && E1 == 0)
    {
        val = 1;
    }
    else if (E0 == 1 && E1 == 0)
    {
        val = 7;
    }
    else if (E0 == 0 && E1 == -1)
    {
        val = 3;
    }
    else if (E0 == -1 && E1 == -1)
    {
        val = 0;
    }
    else if (E0 == 1 && E1 == -1)
    {
        val = 6;
    }
    else if (E0 == 0 && E1 == 1)
    {
        val = 5;
    }
    else if (E0 == -1 && E1 == 1)
    {
        val = 2;
    }
    else if (E0 == 1 && E1 == 1)
    {
        val = 8;
    }
    return val;
}

//------------------------------------------------------------------------------------------------//
//---                                        Partagees                                         ---//
//------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------
// FONCTION    : COMPC_TaskInit
//
// DESCRIPTION : Initialisation de la carte : GPIO, Clocks, Interruptions...
//--------------------------------------------------------------------------------------------------
bool PLIP_TaskInit(void)
{
    trigger = false;
    success = false;
    nbBits = 0;
    frameNumber = 0;
    _ms = millis();

    attachInterrupt(digitalPinToInterrupt(PA1), _ISR, RISING);

    return true;
}

void PLIP_TaskRun(void)
{
    if (frameNumber >= 3)
    {
        success = true;
        for (int i = 0; i < 24; i++)
        {
            if ((bits[0][i] != bits[1][i]) || (bits[0][i] != bits[2][i]) || (bits[1][i] != bits[2][i]))
            {
                success = false;
            }
        }
    
        if ( success == true ){
            uint16_t val = PLIP_GetCode();
            s_PLIP_EVENT sE;
            sE.code = val;
            EVENT_Push(SCREEN_TASK_ID, PLIP_EVENT,&sE);
        }
        frameNumber = 0;
        nbBits = 0;
    }
}

uint16_t PLIP_GetCode(void)
{
    uint16_t val = 0;
    if (success == true)
    {
        for (int i = 0; i < 10; i += 2)
        {
            val *= 10;
            val += decode_2(decode(i), decode(i+1));
        }
        success = false;
    }
    return val;
}