#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include <LedDial/LedDial.h>

void delay(long time) {
    volatile long count = time;
    while (count--) {
        __asm__("nop");
    }
}

static void gpio_setup(void) {
    // Enable port by enabling it's clock
    // pg 148: enable GPIO clock for port E - RCC_AHBENR: IOPE EN = 1
    rcc_periph_clock_enable(RCC_GPIOE);

    // Set control registers for port E pin 8
    // pg 237: general purpose output (open drain) - GPIOE MODER: MODER8 = 01
    // pg 237: set pin to push-pull - GPIOE_OTYPER: OT8 = 0
    // pg 238: set pin to high speed - GPIOE_OSSPEEDER: OSPEEDR8 = 11
    // pg 238: set pin to pull up / pull down - GPIOE_PUPDR: PUPDR8 = 00
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO8);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO10);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO11);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO14);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO15);
}

int main(void) {
    gpio_setup();

    uint32_t* porte_bsrr = (GPIOE + 0x18);
    LedDial_Create(porte_bsrr, 8);

    while (1) {
        // toggle LED on/off
//        gpio_toggle(GPIOE, GPIO8);

        LedDial_TurnAllOn();
        delay(100000);

        LedDial_TurnAllOff();
        delay(100000);
    }

    return 0;
}
