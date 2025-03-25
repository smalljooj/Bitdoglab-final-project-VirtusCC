#include "joystick_lib.h"
//#include "malha_led.h"

// Variáveis globais para armazenar os valores do joystick
int8_t botao;          // Estado do botão (true = solto, false = pressionado)
uint16_t valor_x;    // Valor do eixo X (0-4095 para ADC de 12 bits)
uint16_t valor_y;    // Valor do eixo Y (0-4095 para ADC de 12 bits)
int16_t eixo_x_norm = 0;
int16_t eixo_y_norm = 0;
int testing = 1;

// Configura o joystick (ADC para eixos e GPIO para o botão)
void init_joystick() {
    adc_init(); // Inicializa o ADC
    adc_gpio_init(vRx); // Configura o pino 26 para o eixo X
    adc_gpio_init(vRy); // Configura o pino 27 para o eixo Y

    gpio_init(SW); // Inicializa o pino 22 para o botão
    gpio_set_dir(SW, GPIO_IN); // Configura o pino como entrada
    gpio_pull_up(SW); // Habilita o resistor pull-up (botão em nível alto quando solto)
    // Configura a interrupção para detectar a borda de subida (botão solto)
    //gpio_set_irq_enabled_with_callback(SW, GPIO_IRQ_EDGE_RISE, true, &botaoJS_interrupcao);
}

// Captura os valores atuais do joystick
void joystick_captura() {
    inplicit_read_joystick(&valor_x, &valor_y, &botao);
}

// Lê os valores dos eixos X e Y, e o estado do botão
void inplicit_read_joystick(uint16_t *eixo_x, uint16_t *eixo_y, uint8_t *botao_j) {
    adc_select_input(ADC_CHANNEL_0); // Seleciona o canal do eixo X
    sleep_us(2); // Aguarda 2us para estabilização do ADC
    *eixo_x = adc_read(); // Lê o valor do eixo X

    adc_select_input(ADC_CHANNEL_1); // Seleciona o canal do eixo Y
    sleep_us(2); // Aguarda 2us para estabilização do ADC
    *eixo_y = adc_read(); // Lê o valor do eixo Y

    *botao_j = gpio_get(SW); // Lê o estado do botão
}


// Variáveis globais para armazenar os valores normalizados
int16_t valor_x_norm = 0; // Valor normalizado do eixo X (-100 a 100)
int16_t valor_y_norm = 0; // Valor normalizado do eixo Y (-100 a 100)

// Função para normalizar os valores do joystick
void normalizar_joystick() {
    // Valores de referência do ADC
    const uint16_t adc_min = 18;    // Valor mínimo do ADC
    const uint16_t adc_max = 4083;  // Valor máximo do ADC
    const uint16_t adc_medio = 2017; // Valor médio (centro) do ADC

    // Normaliza o eixo X
    if (valor_x > adc_medio) {
        valor_x_norm = (int16_t)((valor_x - adc_medio) * 100 / (adc_max - adc_medio));
    } else if (valor_x < adc_medio) {
        valor_x_norm = (int16_t)((valor_x - adc_medio) * 100 / (adc_medio - adc_min));
    } else {
        valor_x_norm = 0; // Valor central
    }

    // Normaliza o eixo Y
    if (valor_y > adc_medio) {
        valor_y_norm = (int16_t)((valor_y - adc_medio) * 100 / (adc_max - adc_medio));
    } else if (valor_y < adc_medio) {
        valor_y_norm = (int16_t)((valor_y - adc_medio) * 100 / (adc_medio - adc_min));
    } else {
        valor_y_norm = 0; // Valor central
    }
}
 
// Retorna o valor atual do eixo X
uint16_t get_joystick_x_puro() { return valor_x; }

// Retorna o valor atual do eixo Y
uint16_t get_joystick_y_puro() { return valor_y; }

// Retorna o estado atual do botão
bool get_botao() { return botao; }


// Retorna o valor normalizado do eixo X
int16_t get_joystick_x_norm() {
    return valor_x_norm;
}

// Retorna o valor normalizado do eixo Y
int16_t get_joystick_y_norm() {
    return valor_y_norm;
}