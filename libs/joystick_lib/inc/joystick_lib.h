#ifndef JOYSTICK_LIB_H
#define JOYSTICK_LIB_H

#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include <stdio.h>

// Variáveis Joystick
#define vRx 26 // Eixo X - Pino GPIO conectado ao eixo X do joystick
#define vRy 27 // Eixo Y - Pino GPIO conectado ao eixo Y do joystick
#define ADC_CHANNEL_0 0 // Canal ADC para o Eixo X
#define ADC_CHANNEL_1 1 // Canal ADC para o Eixo Y
#define SW 22 // Botão Joystick - Pino GPIO conectado ao botão do joystick
#define BOTAO_A 5
#define BOTAO_B 6

extern int testing;

// Função para configurar o joystick
// Inicializa os pinos GPIO e ADC para leitura dos eixos X e Y, e o botão
void init_joystick();

// Função para leitura implícita dos dados do joystick
// Armazena os valores dos eixos X e Y, e o estado do botão nos ponteiros fornecidos
// Parâmetros:
// - eixo_x: Ponteiro para armazenar o valor do eixo X (0-4095 para ADC de 12 bits)
// - eixo_y: Ponteiro para armazenar o valor do eixo Y (0-4095 para ADC de 12 bits)
// - botao_j: Ponteiro para armazenar o estado do botão (true se pressionado, false caso contrário)
void inplicit_read_joystick(uint16_t *eixo_x, uint16_t *eixo_y, uint8_t *botao_j);

// Função para capturar os dados do joystick
// Chama a função inplicit_read_joystick para obter os valores atuais
void joystick_captura();

// Função para obter o valor do eixo X (vertical) do joystick
// Retorna o valor lido do eixo X (0-4095 para ADC de 12 bits)
uint16_t get_joystick_x_puro();

// Função para obter o valor do eixo Y (horizontal) do joystick
// Retorna o valor lido do eixo Y (0-4095 para ADC de 12 bits)
uint16_t get_joystick_y_puro();

// Função para obter o estado do botão do joystick
// Retorna true se o botão estiver pressionado, false caso contrário
bool get_botao();

// Função de callback para interrupção do botão
// Parâmetros:
// - gpio: Pino GPIO que gerou a interrupção
// - events: Eventos que acionaram a interrupção (borda de subida ou descida)
// OBS: Você vai precisar modificar esta função caso não esteja utilizando a Matriz de LED's
//void botao_interrupcao(uint gpio, uint32_t events);

// Função para normalizar os valores dos eixos X e Y do joystick
// Mapeia os valores do ADC (0-4095) para um intervalo de -100 a 100
// - Valor 0: Centro do joystick
// - Valor -100: Mínimo (esquerda ou para baixo)
// - Valor 100: Máximo (direita ou para cima)
void normalizar_joystick();

// Função para obter o valor normalizado do eixo X
// Retorna o valor normalizado do eixo X no intervalo de -100 a 100
int16_t get_joystick_x_norm();

// Função para obter o valor normalizado do eixo Y
// Retorna o valor normalizado do eixo Y no intervalo de -100 a 100
int16_t get_joystick_y_norm();

#endif