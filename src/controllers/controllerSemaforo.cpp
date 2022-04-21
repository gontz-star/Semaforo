#include "controllers.h"
#include "buttons/buttonsSemaforo.h"

extern Screens CurrentScreen;
void controllerSemaforo(Adafruit_TFTLCD *tft,Adafruit_GFX_Button*buttonsSemaforo, Adafruit_GFX_Button *buttonsHome ,const TSPoint p)
{
    uint8_t pressedButton = 0xff;

    for (size_t i_btn = 0; i_btn < BUTTON_COUNT_SEMAFORO; i_btn++)
    {
        if (buttonsSemaforo[i_btn].contains(p.x, p.y))
        {
            pressedButton = i_btn;
            break;
        }
    }

    switch (pressedButton)
    {
    case BUTTON_SCREEN_BACK:
    {
        CurrentScreen = Screens::Home;
        viewHome(tft,buttonsHome);
        break;
    }
    default:
        break;
    }
}