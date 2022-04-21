#include "views/views.h"

void viewHome(Adafruit_TFTLCD* tft, Adafruit_GFX_Button* buttonsHome) {
  DEBUG_PRINTLN("drawing home screen");
  tft->fillScreen(BLACK);
  tft->setTextSize(3);
  tft->setTextColor(WHITE,BLACK);
  tft->setCursor(100,100);
  tft->print("dross");
  buttonsHome[0].initButtonUL(tft,0,0,220,40,RED,BLACK,WHITE,"SEMAFORO",3); 
  buttonsHome[0].drawButton();
}