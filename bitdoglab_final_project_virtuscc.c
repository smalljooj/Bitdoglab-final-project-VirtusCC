#include <stdio.h>
#include "pico/stdlib.h"
#include "pico_button_lib.h"
#include "pico_buzzer_lib.h" 
#include "pico_led_matrix_lib.h"
#include "joystick_lib.h"
#include "direcoes.h"

// Definição dos pinos dos botões
#define BOTAO_A  5
#define BOTAO_B  6

// Variáveis globais
Nota notas = MUTE;          // Nota musical atual (inicia mutada)
Buzzer buzzer;              // Objeto do buzzer
uint8_t demo = 0;           // Flag para ativar modo demonstração
uint16_t notes[] = {262, 294, 330, 349, 392, 440, 494, 523}; // Frequências das notas musicais (C4 a C5)

// Protótipos das funções
void botao_a_interrupcao(uint gpio, uint32_t events);  // Handler do botão A
void botao_b_interrupcao(uint gpio, uint32_t events);  // Handler do botão B
void demonstracao();                                   // Função da demo animada

int main() {
    // Inicialização de hardware
    stdio_init_all();       // Inicializa comunicação serial
    init(INPUT_PIN);        // Configura pinos de entrada
    init_joystick();        // Inicializa joystick
    buzzer_init(&buzzer, 21, 1000); // Configura buzzer no pino 21 com frequência base 1kHz
    button_init(BOTAO_A, PULLUP);    // Configura botão A com resistor pull-up
    button_init(BOTAO_B, PULLUP);    // Configura botão B com resistor pull-up

    // Registra interrupções dos botões
    button_register_callback(BOTAO_A, BUTTON_A, GPIO_IRQ_EDGE_FALL, &botao_a_interrupcao);
    button_register_callback(BOTAO_B, BUTTON_B, GPIO_IRQ_EDGE_FALL, &botao_b_interrupcao);    

    // Loop principal
    while (true) {
        // Controle do display LED
        joystick_captura();     // Lê posição do joystick
        normalizar_joystick();  // Processa valores brutos do joystick
        clear();                // Limpa o display
        matrix_write();         // Atualiza LEDs
        sleep_ms(1);            // Pequeno delay para estabilidade
        
        // Verifica modo demonstração
        if (demo == 1) {
            demonstracao();
        }

        // Exibe sprite correspondente à direção do joystick
        switch (get_direcao()) {
            // Direções cardinais
            case CIMA1: display_sprite(cima1); break;
            case CIMA2: display_sprite(cima2); break;
            case BAIXO1: display_sprite(bai1); break;
            case BAIXO2: display_sprite(bai2); break;
            case DIREITA1: display_sprite(dir1); break;
            case DIREITA2: display_sprite(dir2); break;
            case ESQUERDA1: display_sprite(esq1); break;
            case ESQUERDA2: display_sprite(esq2); break;
        
            // Direções diagonais
            case DIAG_CIMA_DIREITA1: display_sprite(dircim1); break;
            case DIAG_CIMA_DIREITA2: display_sprite(dircim2); break;
            case DIAG_CIMA_ESQUERDA1: display_sprite(esqcim1); break;
            case DIAG_CIMA_ESQUERDA2: display_sprite(esqcim2); break;
            case DIAG_BAIXO_DIREITA1: display_sprite(dirbax1); break;
            case DIAG_BAIXO_DIREITA2: display_sprite(dirbax2); break;
            case DIAG_BAIXO_ESQUERDA1: display_sprite(esqbax1); break;
            case DIAG_BAIXO_ESQUERDA2: display_sprite(esqbax2); break;
        
            case NEUTRO: display_sprite(neutro); break; // Posição neutra
        }

        // Controle do buzzer baseado na nota selecionada
        switch (notas) {
            case DO: buzzer_set_frequency(&buzzer, notes[0]); break;  // 262 Hz
            case RE: buzzer_set_frequency(&buzzer, notes[1]); break;  // 294 Hz
            case MI: buzzer_set_frequency(&buzzer, notes[2]); break;  // 330 Hz
            case FA: buzzer_set_frequency(&buzzer, notes[3]); break;  // 349 Hz
            case SOL: buzzer_set_frequency(&buzzer, notes[4]); break; // 392 Hz
            case LA: buzzer_set_frequency(&buzzer, notes[5]); break; // 440 Hz (A4)
            case SI: buzzer_set_frequency(&buzzer, notes[6]); break; // 494 Hz
            case DO2: buzzer_set_frequency(&buzzer, notes[7]); break; // 523 Hz
            case MUTE: buzzer_set_volume(&buzzer, 0); break;   // Silencia o buzzer
        }
    }
}

// Interrupção do Botão A: Ativa modo demonstração
void botao_a_interrupcao(uint gpio, uint32_t events) {
    demo = 1;
}

// Interrupção do Botão B: Mapeia direções para notas musicais
void botao_b_interrupcao(uint gpio, uint32_t events) {
    switch (get_direcao()) {
        case CIMA2: notas = DO; break;              // Cima -> Dó
        case DIAG_CIMA_DIREITA2: notas = RE; break; // Diagonal superior direita -> Ré
        case DIREITA2: notas = MI; break;           // Direita -> Mi
        case DIAG_BAIXO_DIREITA2: notas = FA; break;// Diagonal inferior direita -> Fá
        case BAIXO2: notas = SOL; break;           // Baixo -> Sol
        case DIAG_BAIXO_ESQUERDA2: notas = LA; break;// Diagonal inferior esquerda -> Lá
        case ESQUERDA2: notas = SI; break;         // Esquerda -> Si
        case DIAG_CIMA_ESQUERDA2: notas = DO2; break;// Diagonal superior esquerda -> Dó alto
        case NEUTRO: notas = MUTE; break;          // Centro -> Mudo
    }
}

// Sequência de demonstração com animações e sons
void demonstracao() {
    // Animação circular com mudança de cores e notas musicais
    set_cor(255,0,0); // Cor
    display_sprite(cima1);
    matrix_write();
    sleep_ms(200);
    display_sprite(cima2);
    matrix_write();
    buzzer_set_frequency(&buzzer, notes[0]); // Nota
    sleep_ms(400);

    set_cor(0,255,0);
    display_sprite(dircim1);
    matrix_write();
    sleep_ms(200);
    display_sprite(dircim2);
    matrix_write();
    buzzer_set_frequency(&buzzer, notes[1]);
    sleep_ms(400);

    set_cor(0,0,255);
    display_sprite(dir1);
    matrix_write();
    sleep_ms(200);
    display_sprite(dir2);
    matrix_write();
    buzzer_set_frequency(&buzzer, notes[2]);
    sleep_ms(400);

    set_cor(255,0,255);
    display_sprite(dirbax1);
    matrix_write();
    sleep_ms(200);
    display_sprite(dirbax2);
    matrix_write();
    buzzer_set_frequency(&buzzer, notes[3]);
    sleep_ms(400);

    set_cor(255, 255,0);
    display_sprite(bai1);
    matrix_write();
    sleep_ms(200);
    display_sprite(bai2);
    matrix_write();
    buzzer_set_frequency(&buzzer, notes[4]);
    sleep_ms(400);

    set_cor(0, 255, 255);
    display_sprite(esqbax1);
    matrix_write();
    sleep_ms(200);
    display_sprite(esqbax2);
    matrix_write();
    buzzer_set_frequency(&buzzer, notes[5]);
    sleep_ms(400);


    set_cor(150, 150, 0);
    display_sprite(esq1);
    matrix_write();
    sleep_ms(200);
    display_sprite(esq2);
    matrix_write();
    buzzer_set_frequency(&buzzer, notes[6]);
    sleep_ms(400);

    set_cor(0, 150, 150);
    display_sprite(esqcim1);
    matrix_write();
    sleep_ms(200);
    display_sprite(esqcim2);
    matrix_write();
    buzzer_set_frequency(&buzzer, notes[7]);
    sleep_ms(400);

    set_cor(255, 255, 255);
    display_sprite(final1);
    matrix_write();
    sleep_ms(200);
    display_sprite(final2);
    matrix_write();
    buzzer_set_frequency(&buzzer, notes[0]);
    sleep_ms(400);

    set_cor(255, 255,0);
    demo = 0;
}