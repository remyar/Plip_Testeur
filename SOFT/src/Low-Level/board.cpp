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

#include "board.h"

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

//------------------------------------------------------------------------------------------------//
//---                                        Partagees                                         ---//
//------------------------------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 FONCTIONS PRIVEES ET PARTAGEES                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------//
//---                                         Privees                                          ---//
//------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------
// FONCTION    : _InitClocks
//
// DESCRIPTION : Initialisation des clocks du micro
//--------------------------------------------------------------------------------------------------
static void _InitClocks(void)
{
}

//--------------------------------------------------------------------------------------------------
// FONCTION    : _InitGpio
//
// DESCRIPTION : Initiliasation des GPIO
//--------------------------------------------------------------------------------------------------
static void _InitGpio(void)
{
    pinMode(GPIO_PIN_BUILTIN_LED, OUTPUT);
    digitalWrite(GPIO_PIN_BUILTIN_LED, HIGH);

    pinMode(GPIO_PIN_BUTTON, INPUT_PULLUP);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);

    pinMode(3, INPUT_PULLUP);
}

//------------------------------------------------------------------------------------------------//
//---                                        Partagees                                         ---//
//------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------
// FONCTION    : BOARD_Init
//
// DESCRIPTION : Initialisation de la carte : GPIO, Clocks, Interruptions...
//--------------------------------------------------------------------------------------------------
void BOARD_Init(void)
{
    //--- Initialisation des clocks
    _InitClocks();

    //--- Initialisation des GPIO
    _InitGpio();

    SERIAL_Init();

}
