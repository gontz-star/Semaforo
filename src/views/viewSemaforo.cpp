#include "views/views.h"
#include "buttons/buttonsSemaforo.h"
void viewSemaforo(Adafruit_TFTLCD* tft, Adafruit_GFX_Button* buttonsSemaforo){
    DEBUG_PRINTLN("dibujando semaforo");
    tft->fillScreen(BLACK);
    tft->setTextSize(3);
    tft->setTextColor(WHITE,BLACK);
    /*
    tft->fillCircle(50,50,10,RED);
    tft->fillCircle(100,30,10,BLUE);
    tft->fillCircle(10,100,10,YELLOW);
    buttonsSemaforo[BUTTON_SCREEN_BACK].initButtonUL(tft,0,0,220,40,RED,BLACK,WHITE,"BACK",3); 
    buttonsSemaforo[BUTTON_SCREEN_XD].initButtonUL(tft,20,50,220,40,RED,BLACK,WHITE,"XD",3); 
    buttonsSemaforo[BUTTON_SCREEN_BACK].drawButton();
    buttonsSemaforo[BUTTON_SCREEN_XD].drawButton();
    */
}