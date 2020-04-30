#include "LedDial.h"

static uint32_t* bsrrAddress;
static int bsrrOffset;

void LedDial_Create(uint32_t* address, int offset) {
    bsrrAddress = address;
    bsrrOffset = offset;
    LedDial_TurnAllOff();
}

void LedDial_TurnAllOn() {
    *bsrrAddress = 0xFF << bsrrOffset;
}

void LedDial_TurnAllOff() {
    *bsrrAddress = 0xFF << bsrrOffset + 16;
}

static uint32_t ledNumberToMaskBit(int ledNumber) {
    return 1 << ledNumber + bsrrOffset;
}

void LedDial_TurnOn(int ledNumber) {
    *bsrrAddress |= ledNumberToMaskBit(ledNumber);
}

void LedDial_TurnOff(int ledNumber) {
    // bit reset is upper word
    *bsrrAddress |= ledNumberToMaskBit(ledNumber + 16);
}
