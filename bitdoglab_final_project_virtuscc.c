#include <stdio.h>
#include "pico/stdlib.h"
#include "pico_button_lib.h"
#include "pico_buzzer_lib.h" 
#include "pico_led_matrix_lib.h"
#include "joystick_lib.h"
#include "direcoes.h"

#define SLEEP_TEST 500

#define BUTTON 5
#define LED 12

void testa_led_por_index();

int main()
{
    stdio_init_all();

    init(INPUT_PIN);

    init_joystick();

    
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
        joystick_captura();
        normalizar_joystick();
        clear();
        matrix_write(); // Escreve os dados nos LEDs.
        sleep_ms(1);
        
        switch (get_direcao()) {
            // Direções principais
            case CIMA1: display_sprite(cima1); break;
            case CIMA2: display_sprite(cima2); break;
            case BAIXO1: display_sprite(bai1); break;
            case BAIXO2: display_sprite(bai2); break;
            case DIREITA1: display_sprite(dir1); break;
            case DIREITA2: display_sprite(dir2); break;
            case ESQUERDA1: display_sprite(esq1); break;
            case ESQUERDA2: display_sprite(esq2); break;
        
            // Diagonais
            case DIAG_CIMA_DIREITA1: display_sprite(dircim1); break;
            case DIAG_CIMA_DIREITA2: display_sprite(dircim2); break;
            case DIAG_CIMA_ESQUERDA1: display_sprite(esqcim1); break;
            case DIAG_CIMA_ESQUERDA2: display_sprite(esqcim2); break;
            case DIAG_BAIXO_DIREITA1: display_sprite(dirbax1); break;
            case DIAG_BAIXO_DIREITA2: display_sprite(dirbax2); break;
            case DIAG_BAIXO_ESQUERDA1: display_sprite(esqbax1); break;
            case DIAG_BAIXO_ESQUERDA2: display_sprite(esqbax2); break;
        
            case NEUTRO: display_sprite(neutro); break;
        }
        
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