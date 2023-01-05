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
#include "./display.h"
#include "./images/oled_splash_image.h"
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

//------------------------------------------------------------------------------------------------//
//---                                        Partagees                                         ---//
//------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------
// FONCTION    : KEYBOARD_Init
//
// DESCRIPTION : Initialisation de la carte : GPIO, Clocks, Interruptions...
//--------------------------------------------------------------------------------------------------
void DISPLAY_Init(void)
{
    OLED_Init();
}

void DISPLAY_FillScreen(void)
{
    DuinoShop_SSD1306 * oled = OLED_Get();
    oled->clearDisplay();
}

void DISPLAY_Booting(void)
{
    DuinoShop_SSD1306 * oled = OLED_Get();
    oled->drawBitmap(4,18,SplashLogoGraphicOled,120,27,WHITE);
    oled->display();
}

void DISPLAY_Progress(float value)
{

}

void DISPLAY_TextCenter(String text , int y){
    int16_t x1, y1;
    uint16_t width,height;
    DuinoShop_SSD1306 * oled = OLED_Get();
    oled->getTextBounds(text, 0, 0, &x1, &y1, &width, &height);
    oled->setCursor((SCREEN_WIDTH - width) / 2, y);
    oled->print(text);
}


void DISPLAY_PLIPMenu(void)
{
    DuinoShop_SSD1306 * oled = OLED_Get();
    oled->clearDisplay();
    oled->setTextSize(2);

    DISPLAY_TextCenter("Plip", 16);
    DISPLAY_TextCenter("Reader", 34);

    oled->display();
}

void DISPLAY_MCUMenu(void)
{
    DuinoShop_SSD1306 * oled = OLED_Get();
    oled->clearDisplay();

    oled->setTextSize(2);
    DISPLAY_TextCenter("MCU", 16);
    DISPLAY_TextCenter("Reader", 34);
    oled->display(); 
}

void DISPLAY_MCUWaiting(void)
{
    DuinoShop_SSD1306 * oled = OLED_Get();
    oled->clearDisplay();

    oled->setTextSize(2);

    DISPLAY_TextCenter("Waiting", 16);
    DISPLAY_TextCenter("MCU", 34);

    oled->display(); 
}

void DISPLAY_PLIPWaiting(void)
{
    DuinoShop_SSD1306 * oled = OLED_Get();
    oled->clearDisplay();

    oled->setTextSize(2);

    DISPLAY_TextCenter("Waiting", 16);
    DISPLAY_TextCenter("Plip", 34);

    oled->display(); 
}

void DISPLAY_PLIPCode(uint16_t code){
    DuinoShop_SSD1306 * oled = OLED_Get();
    oled->clearDisplay();

    oled->setTextSize(2);

    DISPLAY_TextCenter("Code", 16);
    DISPLAY_TextCenter(String(code), 34);
    oled->display(); 
}

void DISPLAY_MCUError(void)
{
    DuinoShop_SSD1306 * oled = OLED_Get();
    oled->clearDisplay();

    oled->setTextSize(2);
    DISPLAY_TextCenter("MCU", 0);
    DISPLAY_TextCenter("*********", 16);
    DISPLAY_TextCenter("* ERROR *", 32);
    DISPLAY_TextCenter("*********", 48);
    oled->display(); 
}