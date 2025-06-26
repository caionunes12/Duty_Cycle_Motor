#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

#define VRX_PIN 26
#define SERVO_PIN 13

// Inicializa PWM para 50 Hz

uint pwm_init_gpio(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(gpio);
    
    // Clock base: 125 MHz / 125 = 1 MHz → 1 count = 1 µs
    pwm_set_clkdiv(slice_num, 125.0f);
    pwm_set_wrap(slice_num, 19999);  // 20ms período → 50 Hz
    
    pwm_set_enabled(slice_num, true);
    return slice_num;
}

// Mapeia de uma faixa para outra
uint16_t map_adc_to_pulse(uint16_t adc_value) {
    return 500 + ((adc_value * (2400 - 500)) / 4095);
}

int main() {
    stdio_init_all();
    adc_init();
    adc_gpio_init(VRX_PIN);
    uint slice = pwm_init_gpio(SERVO_PIN);

    // Começa em 90° (1470 µs)
    pwm_set_gpio_level(SERVO_PIN, 1470);

    while (true) {
        adc_select_input(0);
        uint16_t adc_value = adc_read();
        
        uint16_t pulse = map_adc_to_pulse(adc_value);
        pwm_set_gpio_level(SERVO_PIN, pulse);
        
        printf("ADC: %u | Pulso: %u us\n", adc_value, pulse);
        sleep_ms(100);
    }

    return 0;

}
