//================================================================================================//
//                                                                                                //
// PROJET       : DBM620                                                                          //
// MODULE       : Board                                                                           //
// DESCRIPTION  :                                                                                 //
// CREATION     : 18/12/2017                                                                      //
// HISTORIQUE   :                                                                                 //
//                                                                                                //
//================================================================================================//

#ifndef _LED_H_
#define _LED_H_

//================================================================================================//
//                                        FICHIERS INCLUS                                         //
//================================================================================================//

//================================================================================================//
//                                            DEFINES                                             //
//================================================================================================//

//================================================================================================//
//                                          ENUMERATIONS                                          //
//================================================================================================//
typedef enum {
    LED_ON = 0 ,
    LED_OFF,
    LED_TOOGLE
}e_LED_STATE;

//================================================================================================//
//                                      STRUCTURES ET UNIONS                                      //
//================================================================================================//

//================================================================================================//
//                                VARIABLES ET FONCTION PARTAGEES                                 //
//================================================================================================//

//------------------------------------------------------------------------------------------------//
//---                                        Variables                                         ---//
//------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
//---                                        Fonctions                                         ---//
//------------------------------------------------------------------------------------------------//
bool LED_TaskInit(void);
bool LED_TaskUpdate(void *p);
void LED_TaskRun(void);

#endif //--- _BOARD_
