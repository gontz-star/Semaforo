#include "buttons/buttonsSemaforo.h"
#include "views/views.h"
extern LuzSemaforo semaforoEstado;
void viewSemaforo(Adafruit_TFTLCD* tft, Adafruit_GFX_Button* buttonsSemaforo) {
  DEBUG_PRINTLN("dibujando semaforo");

  
    tft->setCursor(0,0);
    tft->setTextSize(3);
    tft->setTextColor(WHITE,BLACK);
  switch (semaforoEstado) {
    case LuzSemaforo::Rojo: {
      // rjoo
      // prender pantalla rojo.
      tft->fillScreen(RED);
      tft->print("ROJO");
      DEBUG_PRINT ("DIBUJANDO ROJO");
      break;
    }
    case LuzSemaforo::Amarillo: {
      // amarinllol
      tft->fillScreen(YELLOW);
      tft->print("AMARILLO");
       DEBUG_PRINT ("DIBUJANDO AMARILLO");
      break;
    }
    case LuzSemaforo::Verde: {
      // verdib
      tft->fillScreen(GREEN);
      tft->print("AMARILLO");
       DEBUG_PRINT ("DIBUJANDO VERDE");
      break;
    }
  }

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