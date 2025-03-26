#include <stdio.h>
#include "pico/stdlib.h"
#include "pico_button_lib.h"
#include "pico_buzzer_lib.h" 
#include "pico_led_matrix_lib.h"
#include "joystick_lib.h"
#include "direcoes.h"

#define SLEEP_TEST 500

#define BOTAO_A  5
#define BOTAO_B  6
#define LED 12

Nota notas = NEUTRO;
Buzzer buzzer;
uint16_t notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

void testa_led_por_index();

void botao_a_interrupcao(uint gpio, uint32_t events);

void botao_b_interrupcao(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    init(INPUT_PIN);

    init_joystick();
    
    button_init(BOTAO_A, PULLUP);
    button_init(BOTAO_B, PULLUP);
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(LED, 0);

    button_register_callback(BOTAO_A, BUTTON_A, GPIO_IRQ_EDGE_FALL, &botao_a_interrupcao); 
    button_register_callback(BOTAO_B, BUTTON_B, GPIO_IRQ_EDGE_FALL, &botao_b_interrupcao); 

    Buzzer buzzer;
    buzzer_init(&buzzer, 21, 1000);

    printf("Emitindo beep...\n");
    //buzzer_beep(&buzzer, 500, 500);

    //testa_led_por_index();

    

    // Frequências em Hz (valores arredondados)
    const uint16_t frequencies[] = {
        392, 392, 392,   // "We wish you"
        330, 523, 494,    // "a merry Christ-"
        440, 392,         // "-mas"
        392, 392, 392,    // "We wish you"
        330, 523, 494,    // "a merry Christ-"
        440, 392,         // "-mas"
        392, 392, 440,    // "We wish you"
        349, 330, 294,    // "a merry"
        523, 523, 494,    // "Christ-mas"
        440, 392          // "and a happy new year!"
    };

    // Durações em milissegundos (ms)
    const uint16_t durations[] = {
        400, 400, 400,    // "We wish you"
        800, 400, 400,    // "a merry Christ-"
        800, 800,         // "-mas"
        400, 400, 400,    // "We wish you"
        800, 400, 400,    // "a merry Christ-"
        800, 800,         // "-mas"
        400, 400, 400,    // "We wish you"
        800, 800, 800,    // "a merry"
        1200, 400, 400,   // "Christ-mas"
        800, 1000         // "and a happy new year!"
    };

    while (true) {
        /*
        for(int i = 0; i < 8; i++) {
            buzzer_set_frequency(&buzzer, notes[i]);
            sleep_ms(400);
        }*/

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
        switch (notas){
            case DO: 
                buzzer_set_frequency(&buzzer, notes[0]);
                sleep_ms(400);
                buzzer_set_frequency(&buzzer, 0);
                notas = MUTE;
                break;

            case RE:
                buzzer_set_frequency(&buzzer, notes[1]); // RE
                sleep_ms(400);
                buzzer_set_frequency(&buzzer, 0);
                notas = MUTE;
                break;

            case MI:
                buzzer_set_frequency(&buzzer, notes[2]); // MI
                sleep_ms(400);
                buzzer_set_frequency(&buzzer, 0);
                notas = MUTE;
                break;

            case FA:
                buzzer_set_frequency(&buzzer, notes[3]); // FA
                sleep_ms(400);
                buzzer_set_frequency(&buzzer, 0);
                notas = MUTE;
                break;

            case SOL:
                buzzer_set_frequency(&buzzer, notes[4]); // SOL
                sleep_ms(400);
                buzzer_set_frequency(&buzzer, 0);
                notas = MUTE;
                break;

            case LA:
                buzzer_set_frequency(&buzzer, notes[5]); // LA
                sleep_ms(400);
                buzzer_set_frequency(&buzzer, 0);
                notas = MUTE;
                break;

            case SI: 
                buzzer_set_frequency(&buzzer, notes[6]); // SI
                sleep_ms(400);
                buzzer_set_frequency(&buzzer, 0);
                notas = MUTE;
                break;

            case DO2:
                buzzer_set_frequency(&buzzer, notes[7]); // DO
                sleep_ms(400);
                buzzer_set_frequency(&buzzer, 0);
                notas = MUTE;
                break;

            case MUTE: buzzer_set_frequency(&buzzer, 0); break;   
        }
    }
}


void botao_a_interrupcao(uint gpio, uint32_t events) {
    
}

void botao_b_interrupcao(uint gpio, uint32_t events) {
    switch (get_direcao()) {
        case CIMA2: notas = DO; break; // DO
        case DIAG_CIMA_DIREITA2: notas = RE; break; // RE
        case DIREITA2: notas = MI; break; // MI
        case DIAG_BAIXO_DIREITA2: notas = FA; break; // FA
        case BAIXO2: notas = SOL; break; // SOL
        case DIAG_BAIXO_ESQUERDA2: notas = LA; break; // LA
        case ESQUERDA2: notas = SI; break; // SI
        case DIAG_CIMA_ESQUERDA2: notas = DO2; break; // DO
        case NEUTRO: notas = MUTE; break;   
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