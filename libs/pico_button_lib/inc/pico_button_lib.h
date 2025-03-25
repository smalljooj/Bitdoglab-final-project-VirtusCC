#ifndef BUTTON_H
#define BUTTON_H

#define DEBOUNCE_TIME_MS 50  // Tempo de debounce para eventos de interrupção
#define BOTAO_A  5
#define BOTAO_B  6

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Define um tipo de callback para facilitar o uso
//typedef void (*button_callback_t)(uint gpio, uint32_t events);

// Define o tipo de pull (pull-up ou pull-down)
typedef enum {
    PULLUP,   // Botão ligado ao GND (Padrão)
    PULLDOWN  // Botão ligado ao 3.3V
} button_mode_t;

// Inicializa um botão com pull-up ou pull-down
void button_init(uint gpio, button_mode_t mode);

// Lê o estado do botão (1 = pressionado, 0 = solto)
bool button_read(uint gpio);

//Alterna um LED ou variável cada vez que o botão for pressionado
bool button_toggle_on_press(uint gpio, bool *state);

//Quando um botão é pressionado, ele pode gerar múltiplos sinais indesejados (efeito bouncing). Essa função faz essa filtragem com um debounce via software
bool button_debounce(uint gpio);

//espera interação do usuário antes de continuar o código.
void button_wait_press(uint gpio);

//detecta se um botão ficou pressionado por um tempo mínimo
bool button_pressed_for(uint gpio, uint32_t duration_ms);

void botao_interrupcao(uint gpio, uint32_t events);

//permite que qualquer função seja chamada quando o botão for pressionado.
//void button_register_callback(uint gpio, uint32_t events, void (*callback)(uint, uint32_t));

#endif // BUTTON_H