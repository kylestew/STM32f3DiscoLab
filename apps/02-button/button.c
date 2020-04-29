#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void clock_setup(void) {
    // set STM32 to 64 MHz
    rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);
}

static void gpio_setup(void) {
    // Enable GPIOE clock
    rcc_periph_clock_enable(RCC_GPIOE);

    // Set GPIO8 (in GPIO port E) to 'output push-pull'
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO11);
}

static void button_setup(void) {
    // Enable GPIOA clock
    rcc_periph_clock_enable(RCC_GPIOA);

    // Set GPIO0 (in GPIO port A) to 'input open-drain'
    gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);
}

int main(void) {
    clock_setup();
    button_setup();
    gpio_setup();

    // Blink the LED (PE11) on the board
    while (1) {

        if (gpio_get(GPIOA, GPIO0)) {
            gpio_set(GPIOE, GPIO11);
        } else {
            gpio_clear(GPIOE, GPIO11);
        }

        __asm__("nop");
    }

    return 0;
}
