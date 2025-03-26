#include <stdio.h>
#include "pico/stdlib.h"
#include "pico_button_lib.h"
#include "pico_buzzer_lib.h" 
#include "pico_led_matrix_lib.h"
#include "joystick_lib.h"
#include "direcoes.h"

#define BOTAO_A  5
#define BOTAO_B  6

Nota notas = MUTE;
Buzzer buzzer;
uint16_t notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

void botao_a_interrupcao(uint gpio, uint32_t events);
void botao_b_interrupcao(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();
    init(INPUT_PIN);
    init_joystick();
    buzzer_init(&buzzer, 21, 1000);
    button_init(BOTAO_A, PULLUP);
    button_init(BOTAO_B, PULLUP);

    button_register_callback(BOTAO_A, BUTTON_A, GPIO_IRQ_EDGE_FALL, &botao_a_interrupcao); 
    button_register_callback(BOTAO_B, BUTTON_B, GPIO_IRQ_EDGE_FALL, &botao_b_interrupcao);    

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

        switch (notas){
            case DO: buzzer_set_frequency(&buzzer, notes[0]); break; // DO
            case RE: buzzer_set_frequency(&buzzer, notes[1]); break; // RE
            case MI: buzzer_set_frequency(&buzzer, notes[2]); break; // MI
            case FA: buzzer_set_frequency(&buzzer, notes[3]); break; // FA
            case SOL: buzzer_set_frequency(&buzzer, notes[4]); break; // SOL
            case LA: buzzer_set_frequency(&buzzer, notes[5]); break; // LA
            case SI: buzzer_set_frequency(&buzzer, notes[6]); break; // SI
            case DO2: buzzer_set_frequency(&buzzer, notes[7]); break; // DO2
            case MUTE: buzzer_set_volume(&buzzer, 0); break;   
        }
    }
}


void botao_a_interrupcao(uint gpio, uint32_t events) {
    printf("AMANHA!!!!!!!!!!!!!!!!!\n\n");
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
        case DIAG_CIMA_ESQUERDA2: notas = DO2; break; // DO2
        case NEUTRO: notas = MUTE; break;
    }
}