#ifndef __VIEWS_H__
#define __VIEWS_H__

#include <stdint.h>

#include "DEBUG_things.h"
#include "common_defs.h"
#include "src/Adafruit_TFTLCD.h"

class Adafruit_TFTLCD;
class Adafruit_GFX_Button;

void viewHome(Adafruit_TFTLCD* tft, Adafruit_GFX_Button* buttonsHome); 
void viewSemaforo(Adafruit_TFTLCD* tft, Adafruit_GFX_Button* buttonsSemaforo);
void viewNigga(Adafruit_TFTLCD* tft, Adafruit_GFX_Button* buttonsNigga);
#endif 