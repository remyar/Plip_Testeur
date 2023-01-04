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
#include "./screen.h"
#include "./keyboard/keyboard.h"
#include "./plip/plip.h"

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
static e_SCREEN _e_screen = SCREEN_BOOTING;
static e_SCREEN _old_e_screen = SCREEN_BOOTING;
static unsigned long _ms = millis();
static float updateProgress = 0.00;
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

//-----------------------------------------------------------------------------
// FONCTION    :  SCREEN_Init
//
// DESCRIPTION :  Initialisation de l'ecran
//-----------------------------------------------------------------------------
void SCREEN_Init(void)
{
   DISPLAY_Init();
   _e_screen = SCREEN_BOOTING;
   _ms = millis();
}

//--------------------------------------------------------------------------------------------------
// FONCTION    : SCREEN_TaskInit
//
// DESCRIPTION : Initialisation de la tache
//--------------------------------------------------------------------------------------------------
bool SCREEN_TaskInit(void)
{
   SCREEN_Init();
   _e_screen = SCREEN_BOOTING;
   _old_e_screen = SCREEN_MAX;
   return true;
}

void SCREEN_Change(e_SCREEN _s)
{
   _e_screen = _s;
}

//-----------------------------------------------------------------------------
// FONCTION    : SCREEN_TaskUpdate
//
// DESCRIPTION : MAJ de la Tache : gestion evenements
//-----------------------------------------------------------------------------
bool SCREEN_TaskUpdate(void *p)
{
   s_EVENT *event = (s_EVENT *)p;

   if (event->type & KEYB_EVENT)
   {
      if (event->key.code == 1)
      {
         if (event->key.isLong == false)
         {
            switch (_e_screen)
            {
            case (SCREEN_PLIP):
            {
               _e_screen = SCREEN_MCU;
               break;
            }
            case (SCREEN_PLIP_WAITING):
            {
               _e_screen = SCREEN_PLIP_WAITING;
               break;
            }
            case (SCREEN_MCU):
            {
               _e_screen = SCREEN_PLIP;
               break;
            }
            }
         } else {
            switch (_e_screen)
            {
            case (SCREEN_PLIP):
            {
               _e_screen = SCREEN_PLIP_WAITING;
               break;
            }
            case (SCREEN_PLIP_WAITING):
            {
               _e_screen = SCREEN_PLIP;
               break;
            }
            case (SCREEN_MCU):
            {
               _e_screen = SCREEN_PLIP;
               break;
            }
            } 
         }
      }

      EVENT_Clear(SCREEN_TASK_ID, KEYB_EVENT);
   }

   return true;
}

void SCREEN_SetUpdateProgress(float value)
{
   updateProgress = value;
}

void SCREEN_TaskRun(void)
{

   bool forceRefresh = false;
   if ((_e_screen == SCREEN_BOOTING) && (millis() - _ms) >= 1000)
   {
      SCREEN_Change(SCREEN_PLIP);
   }

   if (_e_screen != _old_e_screen)
   {
      DISPLAY_FillScreen();
      forceRefresh = true;
      _old_e_screen = _e_screen;
   }

   if (forceRefresh == true)
   {
      switch (_e_screen)
      {
      case (SCREEN_BOOTING):
      {
         DISPLAY_Booting();
         break;
      }
      case (SCREEN_PLIP):
      {
         DISPLAY_PLIPMenu();
         break;
      }
      case (SCREEN_MCU):
      {
         DISPLAY_MCUMenu();
         break;
      }
      case ( SCREEN_PLIP_WAITING ):
      {
         PLIP_TaskInit();
         DISPLAY_PLIPWaiting();
         while ( PLIP_TaskRun() == false ){
            KEYBOARD_TaskRun();
            if ( EVENT_HasEvent() == true ){
               return;
            }
         }

         DISPLAY_PlipCode(PLIP_GetCode());
         break;
      }
      default:
      {
         break;
      }
      }
   }
}