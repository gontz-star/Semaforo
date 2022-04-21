#include "controllers.h"
#include "buttons/buttonsHome.h"
extern Screens CurrentScreen;
void controllerHome(Adafruit_TFTLCD *tft, Adafruit_GFX_Button *buttonsHome, Adafruit_GFX_Button*buttonsSemaforo ,const TSPoint p)
{
    uint8_t pressedButton = 0xff;

    for (size_t i_btn = 0; i_btn < BUTTON_COUNT_HOME; i_btn++)
    {
        if (buttonsHome[i_btn].contains(p.x, p.y))
        {
            pressedButton = i_btn;
            break;
        }
    }
    switch (pressedButton)
    {
    case BUTTON_SCREEN_SEMAFORO:
    {
        CurrentScreen = Screens::Semaforo;
        viewSemaforo(tft,buttonsSemaforo);
        break;
    }

    default:
        break;
    }
}