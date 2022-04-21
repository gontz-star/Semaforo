#include <Arduino.h>
#include "DEBUG_things.h"
#include "SPI.h"
#include "common_defs.h"
#include "src/Adafruit_GFX.h"
#include "src/Adafruit_TFTLCD.h"
#include "src/TouchScreen.h"
#include "touchscreen_config.h"
#include "views/views.h"
#include <Adafruit_I2CDevice.h>
#include "controllers/controllers.h"
#include "buttons/buttons.h"
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

TouchScreen ts = TouchScreen(XP, YP, XM, YM, RX);


Screens CurrentScreen;

void tsMenu();

void setup()
{
  DEBUG_BEGIN(9600);

  uint16_t lcd_id = tft.readID();
  uint8_t lcd_rotation = 0;

  switch (lcd_id)
  {
  case 0x9325:
  {
    lcd_rotation = 1;
    break;
  }
  case 0x9341:
  {
    lcd_rotation = 3;
    break;
  }
  case 0xC0C0:
  { // 0x9341
    DEBUG_PRINT(F("UNRECOGNIZED DRIVER (0x"));
    DEBUG_PRINTHEX(lcd_id);
    DEBUG_PRINTLN(F(") USING 0x9341 DRIVER"));
    lcd_id = 0x9341;
    lcd_rotation = 3;
    break;
  }
  default:
  {
    DEBUG_PRINT(F("UNRECOGNIZED DRIVER (0x"));
    DEBUG_PRINTHEX(lcd_id);
    DEBUG_PRINTLN(F(") USING 0x9341 DRIVER"));
    lcd_id = 0x9341;
    lcd_rotation = 3;
    break;
  }
  }

  DEBUG_PRINT(F("LCD driver reported by screen: 0x"));
  DEBUG_PRINTLNHEX(lcd_id);
  DEBUG_PRINT(F("TFT size is "));
  DEBUG_PRINT(tft.width());
  DEBUG_PRINT(F("x"));
  DEBUG_PRINTLN(tft.height());

  tft.reset();
  tft.begin(lcd_id);
  tft.setRotation(lcd_rotation);

  tft.fillScreen(BLACK);

  CurrentScreen = Screens::Home;
  viewHome(&tft,buttonsHome);

  // put your setup code here, to run once:
}

void loop()
{
  tsMenu();
  
  // put your main code here, to run repeatedly:
}
void tsMenu(){
  TSPoint p = ts.getPoint();

  if (p.z > MINPRESSURE)
  {
    // el modulo tactil tiene 60 puntos no dibujables en la pantalla
    TSPoint pointTmp = p;

    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    p.y = map(pointTmp.x, TS_MINX, TS_MAXX, tft.height(), 0);
    p.x = map(pointTmp.y, TS_MINY, TS_MAXY - 60, 0, tft.width());

    switch (CurrentScreen)
    {
    case Screens::Home:
    {
      controllerHome(&tft,buttonsHome,buttonsSemaforo,p);
      break;
    }
    case Screens::Semaforo:{
      controllerSemaforo(&tft,buttonsSemaforo,buttonsHome,p);
      break;
    }

    default:
    {
      break;
    }
    }
  }
}