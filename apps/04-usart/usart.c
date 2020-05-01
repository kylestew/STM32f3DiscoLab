#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>

#include <EasyUsart/EasyUsart.h>

void delay(long time) {
    volatile long count = time;
    while (count--) {
        __asm__("nop");
    }
}

int main(void) {
    rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);

    Usart_Setup(USART1);

    uint16_t temp = 123;
    while (1) {
        Usart_Print(temp);

        delay(1000000);
    }

    return 0;
}
