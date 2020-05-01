#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/adc.h>

#include <LedDial/LedDial.h>

void delay(long time) {
    volatile long count = time;
    while (count--) {
        __asm__("nop");
    }
}

static void gpio_setup(void) {
    // LED Dial
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
            GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
}

static void usart_setup(void) {
    /* Enable clocks for GPIO port C (for GPIO_USART1_TX) and USART1. */
    rcc_periph_clock_enable(RCC_USART1);
    rcc_periph_clock_enable(RCC_GPIOC);

    /* Setup GPIO pin GPIO_USART1_TX/GPIO4 on GPIO port C for transmit. */
    gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO4 | GPIO5);
    gpio_set_af(GPIOC, GPIO_AF7, GPIO4| GPIO5);

    /* Setup UART parameters. */
    usart_set_baudrate(USART1, 115200);
    usart_set_databits(USART1, 8);
    usart_set_stopbits(USART1, USART_STOPBITS_1);
    usart_set_mode(USART1, USART_MODE_TX_RX);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

    /* Finally enable the USART. */
    usart_enable(USART1);
}

static void usart_print_int(uint32_t usart, int16_t value) {
    int8_t i;
    int8_t nr_digits = 0;
    char buffer[25];

    if (value < 0) {
        usart_send_blocking(usart, '-');
        value = value * -1;
    }

    if (value == 0) {
        usart_send_blocking(usart, '0');
    }

    while (value > 0) {
        buffer[nr_digits++] = "0123456789"[value % 10];
        value /= 10;
    }

    for (i = nr_digits-1; i >= 0; i--) {
        usart_send_blocking(usart, buffer[i]);
    }

    usart_send_blocking(usart, '\r');
    usart_send_blocking(usart, '\n');
}

int main(void) {
    rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);

    gpio_setup();
//    adc_setup();
    usart_setup();

    LedDial_Create((GPIOE + 0x18), 8);

    int low = 0;
    int high = 1;

    LedDial_TurnOn(low);
    LedDial_TurnOn(high);

    uint16_t temp = 123;
    while (1) {
        LedDial_TurnOff(low);
        low++;
        if (low > 7) low = 0;

        high++;
        if (high > 7) high = 0;
        LedDial_TurnOn(high);

        delay(1000000);


        usart_print_int(USART1, temp);
    }

    return 0;
}
