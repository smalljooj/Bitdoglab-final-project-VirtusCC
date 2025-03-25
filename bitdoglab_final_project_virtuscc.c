#include <stdio.h>
#include "pico/stdlib.h"
#include "pico_button_lib.h"
#include "pico_buzzer_lib.h" 
#include "pico_led_matrix_lib.h"

#define SLEEP_TEST 500

#define BUTTON 5
#define LED 12

void testa_led_por_index();

int main()
{
    stdio_init_all();

    init(INPUT_PIN);

    button_init(BUTTON, PULLUP);
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(LED, 0);

    Buzzer buzzer;
    buzzer_init(&buzzer, 21, 1000);

    printf("Emitindo beep...\n");
    buzzer_beep(&buzzer, 500, 500);

    testa_led_por_index();

    while (true) {
        if (button_pressed_for(BUTTON, 2000)) {
            gpio_put(LED, 1);
            sleep_ms(500);
            gpio_put(LED, 0);
        }
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

void testa_led_por_index() {
    // acende tudo vermelho
    for (uint8_t i = 0; i < LED_COUNT; i++){
        set_color_by_index(i, 255, 0, 0);
    }
    matrix_write();
    sleep_ms(SLEEP_TEST);
    clear();

    // acende tudo verde
    for (uint8_t i = 0; i < LED_COUNT; i++){
        set_color_by_index(i, 0, 255, 0);
    }
    matrix_write();
    sleep_ms(SLEEP_TEST);
    clear();

    // acende tudo azul
    for (uint8_t i = 0; i < LED_COUNT; i++){
        set_color_by_index(i, 0, 0, 255);
    }
    matrix_write();
    sleep_ms(SLEEP_TEST);
    clear();

    // acende tudo branco
    for (uint8_t i = 0; i < LED_COUNT; i++){
        set_color_by_index(i, 255, 255, 255);
    }
    matrix_write();
    sleep_ms(SLEEP_TEST);
    clear();
}