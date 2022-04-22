#include <Adafruit_I2CDevice.h>
#include <Arduino.h>

#include "DEBUG_things.h"
#include "SPI.h"
#include "buttons/buttons.h"
#include "common_defs.h"
#include "controllers/controllers.h"
#include "src/Adafruit_GFX.h"
#include "src/Adafruit_TFTLCD.h"
#include "src/TouchScreen.h"
#include "touchscreen_config.h"
#include "views/views.h"

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

TouchScreen ts = TouchScreen(XP, YP, XM, YM, RX);

Screens CurrentScreen;

void tsMenu();
void funcionalidad();

void setup() {
  DEBUG_BEGIN(9600);

  uint16_t lcd_id = tft.readID();
  uint8_t lcd_rotation = 0;

  switch (lcd_id) {
    case 0x9325: {
      lcd_rotation = 1;
      break;
    }
    case 0x9341: {
      lcd_rotation = 3;
      break;
    }
    case 0xC0C0: {  // 0x9341
      DEBUG_PRINT(F("UNRECOGNIZED DRIVER (0x"));
      DEBUG_PRINTHEX(lcd_id);
      DEBUG_PRINTLN(F(") USING 0x9341 DRIVER"));
      lcd_id = 0x9341;
      lcd_rotation = 3;
      break;
    }
    default: {
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
  viewHome(&tft, buttonsHome);

  // put your setup code here, to run once:
}

void loop() {
  funcionalidad();

  tsMenu();

  // put your main code here, to run repeatedly:
}

extern LuzSemaforo semaforoEstado;
extern uint32_t contadorSemaforo;

const uint16_t tiempoRojo = 15000;
const uint16_t tiempoAmarillo = 10000;
const uint16_t tiempoVerde = 15000;

void funcionalidad() {
  static uint32_t ultima_vez_ejecutado;   // tiempo; 5000ms desde arranque
  const uint16_t espera_ejecucion = 100;  // tiempo de descanso

  uint16_t tiempo_desde_ultima_ejecucion = millis() - ultima_vez_ejecutado;

  if (tiempo_desde_ultima_ejecucion >= espera_ejecucion) {
    // codigp
    switch (CurrentScreen) {
      case Screens::Semaforo: {
        

        switch (semaforoEstado) {
          case LuzSemaforo::Rojo: {
            // rjoo
            // prender pantalla rojo.
           
            if (millis() - contadorSemaforo >= tiempoRojo) {
              semaforoEstado = LuzSemaforo::Amarillo;
              contadorSemaforo = millis();
              DEBUG_PRINTLN("amairlol");
              DEBUG_PRINT("contadorSemaforo: ");
              DEBUG_PRINTLN(contadorSemaforo);
              DEBUG_PRINTLN(millis() - contadorSemaforo);
            }
            break;
          }
          case LuzSemaforo::Amarillo: {
            // amarinllol
            if (millis() - contadorSemaforo >= tiempoRojo) {
              semaforoEstado = LuzSemaforo::Verde;
              contadorSemaforo = millis();
              DEBUG_PRINTLN("verdre");
              DEBUG_PRINT("contadorSemaforo: ");
              DEBUG_PRINTLN(contadorSemaforo);
              DEBUG_PRINTLN(millis() - contadorSemaforo);
            }
            break;
          }
          case LuzSemaforo::Verde: {
            // verdib
            if (millis() - contadorSemaforo >= tiempoRojo) {
              semaforoEstado = LuzSemaforo::Rojo;
              contadorSemaforo = millis();
              DEBUG_PRINTLN("rojfooo");
              DEBUG_PRINT("contadorSemaforo: ");
              DEBUG_PRINTLN(contadorSemaforo);
              DEBUG_PRINTLN(millis() - contadorSemaforo);
            }
            break;
          }
        }

        // contadorSemaforo = millis();

        break;
      }

      case Screens::Home: {
        break;
      }
    }
    ultima_vez_ejecutado = millis();
  }
}

void tsMenu() {
  TSPoint p = ts.getPoint();

  if (p.z > MINPRESSURE) {
    // el modulo tactil tiene 60 puntos no dibujables en la pantalla
    TSPoint pointTmp = p;

    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    p.y = map(pointTmp.x, TS_MINX, TS_MAXX, tft.height(), 0);
    p.x = map(pointTmp.y, TS_MINY, TS_MAXY - 60, 0, tft.width());

    switch (CurrentScreen) {
      case Screens::Home: {
        controllerHome(&tft, buttonsHome, buttonsSemaforo, p);
        break;
      }
      case Screens::Semaforo: {
        controllerSemaforo(&tft, buttonsSemaforo, buttonsHome, p);
        break;
      }

      default: {
        break;
      }
    }
  }
}