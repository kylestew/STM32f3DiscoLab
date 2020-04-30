#include "gtest/gtest.h"
//#include "LedDial.c"

class LedDialFixture : public ::testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    uint16_t virtualLeds;
};

TEST_F(LedDialFixture, FalsIsTrue) {
    ASSERT_EQ(false, true);
}
