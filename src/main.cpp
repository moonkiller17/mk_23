#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

int main () {

    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);

    // Настройка таймера
    rcc_periph_clock_enable(RCC_TIM6);
    timer_set_prescaler(TIM6, 36000 - 1);
    timer_set_period(TIM6, 1000 - 1);

    timer_enable_counter(TIM6);

    // Настройка порта ввода-вывода
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9);

    while (true) {
        if (timer_get_counter(TIM6) < 500) {
            gpio_set(GPIOE, GPIO9);
        }
        else {
            gpio_clear(GPIOE, GPIO9);
        }
    }
}