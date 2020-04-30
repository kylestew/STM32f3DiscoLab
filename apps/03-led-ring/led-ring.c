#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

/*
* Blinks onboard LED @ PE8
*/

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
}

int main(void) {
    // PE8-15
    // LED ring is upper byte of port E
    // how to abstract this into a driver?

    gpio_setup();

    // Blink the LED (PE8) on the board
    while (1) {
        // toggle LED on/off
        gpio_toggle(GPIOE, GPIO8);
        delay(100000);
    }

    return 0;
}
