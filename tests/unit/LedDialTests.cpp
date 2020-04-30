#include "gtest/gtest.h"
//#include <LedDial/LedDial.h>
#include "LedDial/LedDial.c"

class LedDialFixture : public ::testing::Test {
protected:

    virtual void SetUp() {
        LedDial_Create(&virtualBSRR, 8);
        virtualBSRR = 0x0;
    }

    virtual void TearDown() {
    }

    uint32_t virtualBSRR;
};

TEST_F(LedDialFixture, LedsOffAfterCreate) {
    LedDial_Create(&virtualBSRR, 8);
    ASSERT_EQ(virtualBSRR, 0xFF000000);
}

TEST_F(LedDialFixture, TurnOnAllLeds) {
    LedDial_TurnAllOn();
    ASSERT_EQ(virtualBSRR, 0x0000FF00);
}

TEST_F(LedDialFixture, TurnOffAllLeds) {
    LedDial_TurnAllOff();
    ASSERT_EQ(virtualBSRR, 0xFF000000);
}

TEST_F(LedDialFixture, TurnOffAllLedsDifferentOffset) {
    LedDial_Create(&virtualBSRR, 4);
    LedDial_TurnAllOff();
    ASSERT_EQ(virtualBSRR, 0x0FF00000);
}

TEST_F(LedDialFixture, TurnOnLedOne) {
    LedDial_TurnOn(0);
    ASSERT_EQ(virtualBSRR, 0x100);
}

TEST_F(LedDialFixture, TurnOffLedOne) {
    LedDial_TurnOff(0);
    ASSERT_EQ(virtualBSRR, 0x1000000);
}

TEST_F(LedDialFixture, TurnOnMultipleLeds) {
    LedDial_TurnOn(3);
    LedDial_TurnOn(7);
    ASSERT_EQ(virtualBSRR, 0x8800);
}

TEST_F(LedDialFixture, TurnOffMultipleLeds) {
    LedDial_TurnOff(3);
    LedDial_TurnOff(7);
    ASSERT_EQ(virtualBSRR, 0x88000000);
}

// TODO: test out of bounds condition
/*
TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm)
{
    LedDriver_TurnOn(-1);
    LedDriver_TurnOn(0);
    LedDriver_TurnOn(17);
    LedDriver_TurnOn(3141);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
    LedDriver_TurnAllOn();

    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(3141);
    TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}
 */