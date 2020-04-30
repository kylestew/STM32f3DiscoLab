#ifndef STM32F3_DISCO_LEDDIAL_H
#define STM32F3_DISCO_LEDDIAL_H
#include <stdint.h>

void LedDial_Create(uint32_t* bsrrAddress, int bsrrOffset);

void LedDial_TurnAllOn();
void LedDial_TurnAllOff();

void LedDial_TurnOn(int ledNumber);
void LedDial_TurnOff(int ledNumber);

#endif //STM32F3_DISCO_LEDDIAL_H
