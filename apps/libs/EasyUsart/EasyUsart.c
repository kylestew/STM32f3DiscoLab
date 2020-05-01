#include "EasyUsart.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/gpio.h>

static uint32_t _usart;

void Usart_Setup(uint32_t usart) {
    _usart = usart;

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

void Usart_Print(int16_t value) {
    int8_t i;
    int8_t nr_digits = 0;
    char buffer[25];

    if (value < 0) {
        usart_send_blocking(_usart, '-');
        value = value * -1;
    }

    if (value == 0) {
        usart_send_blocking(_usart, '0');
    }

    while (value > 0) {
        buffer[nr_digits++] = "0123456789"[value % 10];
        value /= 10;
    }

    for (i = nr_digits-1; i >= 0; i--) {
        usart_send_blocking(_usart, buffer[i]);
    }

    usart_send_blocking(_usart, '\r');
    usart_send_blocking(_usart, '\n');
}

