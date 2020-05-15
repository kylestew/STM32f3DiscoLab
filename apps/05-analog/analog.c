#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/adc.h>

#include <LedDial/LedDial.h>
#include <EasyUsart/EasyUsart.h>

void delay(long time) {
    volatile long count = time;
    while (count--) {
        __asm__("nop");
    }
}

static void adc_setup(void) {
    //ADC
    rcc_periph_clock_enable(RCC_ADC12);
    rcc_periph_clock_enable(RCC_GPIOA);

    //ADC
//    gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0);
//    gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO1);
//    adc_power_off(ADC1);
//    adc_set_clk_prescale(ADC1, ADC_CCR_CKMODE_DIV2);
//    adc_set_single_conversion_mode(ADC1);
//    adc_disable_external_trigger_regular(ADC1);
//    adc_set_right_aligned(ADC1);
//    /* We want to read the temperature sensor, so we have to enable it. */
//    adc_enable_temperature_sensor();
//    adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_61DOT5CYC);
//    uint8_t channel_array[] = { 1 }; /* ADC1_IN1 (PA0) */
//    adc_set_regular_sequence(ADC1, 1, channel_array);
//    adc_set_resolution(ADC1, ADC_CFGR1_RES_12_BIT);
//    adc_power_on(ADC1);
//
//    /* Wait for ADC starting up. */
//    int i;
//    for (i = 0; i < 800000; i++)
//            __asm__("nop");
}

static void gpio_setup(void) {
    // LED Dial
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
            GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
}

int main(void) {
    rcc_clock_setup_hsi(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);

    adc_setup();
    gpio_setup();

    Usart_Setup(USART1);
    LedDial_Create((GPIOE + 0x18), 8);

    int low = 0;
    int high = 1;

    LedDial_TurnOn(low);
    LedDial_TurnOn(high);

    uint16_t temp = 123;
    while (1) {
//        adc_start_conversion_regular(ADC1);
//        while (!(adc_eoc(ADC1)));
//        temp = adc_read_regular(ADC1);
//        gpio_port_write(GPIOE, temp << 4);
//        Usart_Print(temp);


        // TODO: tie to temp
        LedDial_TurnOff(low);
        low++;
        if (low > 7) low = 0;

        high++;
        if (high > 7) high = 0;
        LedDial_TurnOn(high);

        delay(1000000);

    }

    return 0;
}
