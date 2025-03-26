#ifndef LED_MATRIX
#define LED_MATRIX

/**
 * Esse módulo é responsavel por viabilizar o uso da matriz de leds.
 * 
 * Uma observação importante é que há duas formas de ascender leds individualmente baseados no index da lista de leds ou baseado nos eixos x e y da matriz 
 * Cada um desses casos tem uma orientação diferente.
 * Caso opte por ascender por índice, deve seguir a seguinte orientação:
 *  24  23  22  21  20
 *  15  16  17  18  19
 *  14  13  12  11  10
 *   5   6   7   8   9
 *   4   3   2   1   0
 * 
 * Mas para usar como matriz, é śo utilizar a orientação dos índices impressos na placa. 
 * 
 * Sobre a utilização, todas as operações que você fizer usando as funções (exceto o clear) funcionam com base em um buffer: a lista de pixels. 
 * Então sempre que quiseres ver o resultado na matriz de leds, execute "matrix_write"
 * 
*/

#include <stdio.h>

#define INPUT_PIN 7   // pino de entrada
#define LED_COUNT 25  // total de pinos
#define SIDE_SIZE 5   // tamanho da linha e da coluna da matriz
#define DELAY_MS 1    // tempo pra atualizar a matriz

// guarda o estado de cada led
typedef struct pixel_t {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Pixel;


// Cor tema (R, G, B)
extern uint8_t tema_cor[3];

/*
extern PIO np_pio;
extern uint sm;
extern Pixel matrix[];
*/

// permite ascender um dos leds baseado nos eixos x e y
void set_color_by_xy(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue);

// permite ascender um dos leds baseado no seu índice
void set_color_by_index(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

// permite ascender uma coluna inteira
void set_color_by_column(uint8_t column, uint8_t red, uint8_t green, uint8_t blue);

// permite ascender uma linha inteira
void set_color_by_line(uint8_t column, uint8_t red, uint8_t green, uint8_t blue);

// limpa a matriz
void clear();

// inicializa o componente
void init(uint8_t pin);

// envia os dados referentes a cada pixel para o componente
void matrix_write();


// Função para exibir sprites na matriz de LEDs
// Parâmetros:
// - sprite: Matriz 5x5x3 contendo os valores de cor (R, G, B) para cada LED
void display_sprite(const int sprite[5][5][3]);


void set_led_state(uint8_t index, uint8_t intensidade);

void set_cor(uint8_t r, uint8_t g, uint8_t b);

#endif