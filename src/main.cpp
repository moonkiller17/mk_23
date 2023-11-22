#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>


constexpr uint16_t PERIOD_MS{1000};


void timer_setup() {

    // Настройка таймера
    rcc_periph_clock_enable(RCC_TIM6);
    timer_set_prescaler(TIM6, rcc_get_timer_clk_freq(TIM6) / PERIOD_MS - 1);
    timer_set_period(TIM6, 1000 - 1);

    timer_enable_irq(TIM6, TIM_DIER_UIE);
    nvic_enable_irq(NVIC_TIM6_DAC_IRQ);

    timer_enable_counter(TIM6);
}


void gpio_setup() {

    // Настройка порта ввода-вывода
    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9 | GPIO11);
}


void blink_LED() {
    if (timer_get_counter(TIM6) < PERIOD_MS / 2) {
        gpio_set(GPIOE, GPIO9);
    }
    else {
        gpio_clear(GPIOE, GPIO9);
    }
}


int main () {

    // Настройка тактов
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);

    timer_setup();

    gpio_setup();

    while (true) {

        blink_LED();
    }
}

void tim6_dac_isr() {

    gpio_toggle(GPIOE, GPIO11);
}