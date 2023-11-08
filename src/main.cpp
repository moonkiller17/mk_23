#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

int main () {

    // Разморозка светодиодов
    rcc_periph_clock_enable(RCC_GPIOE);

    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9);

    while (true) {
        gpio_toggle(GPIOE, GPIO9);

        for (volatile uint32_t i = 0; i < 500'000; ++i);

    }
}