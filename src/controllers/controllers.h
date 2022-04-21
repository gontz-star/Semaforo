#ifndef __CONTROLLERS_H__
#define __CONTROLLERS_H__

#include "DEBUG_things.h"
#include "common_defs.h"
#include "src/Adafruit_TFTLCD.h"
#include "src/TouchScreen.h"
#include "views/views.h"
void controllerHome(Adafruit_TFTLCD *tft, Adafruit_GFX_Button *buttonsHome,Adafruit_GFX_Button*buttonsSemaforo, const TSPoint p);
void controllerSemaforo(Adafruit_TFTLCD *tft,Adafruit_GFX_Button*buttonsSemaforo, Adafruit_GFX_Button *buttonsHome ,const TSPoint p);
#endif