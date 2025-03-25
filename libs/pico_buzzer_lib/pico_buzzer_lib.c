#include "pico_buzzer_lib.h"
#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"

#define DEBUG_BUZZER 1
#define MAX_PWM 4096  // Valor máximo do PWM

// Timers e variáveis globais
static alarm_id_t beep_off_alarm_id;  
static alarm_id_t melody_alarm_id;  

static Buzzer *active_buzzer = NULL;
static const uint *active_notes = NULL;
static const uint *active_durations = NULL;
static uint melody_size = 0;
static uint melody_index = 0;

// ===========================
//    Inicialização do Buzzer
// ===========================
void buzzer_init(Buzzer *buzzer, uint pin, uint freq) {
    if (freq < 20 || freq > 20000) {
        printf("Erro: Frequência %d Hz fora do intervalo audível!\n", freq);
        return;
    }

    buzzer->pin = pin;
    buzzer->frequency = freq;
    buzzer->level = MAX_PWM / 2;  // Começa com 50% de volume

    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (freq * 4096));
    pwm_init(slice_num, &config, true);

    pwm_set_gpio_level(pin, 0);

    #if DEBUG_BUZZER
        printf("Buzzer inicializado no pino %d com frequência %d Hz\n", pin, freq);
    #endif
}

// ===========================
//    Controle de Frequência
// ===========================
void buzzer_set_frequency(Buzzer *buzzer, uint frequency) {
    uint slice_num = pwm_gpio_to_slice_num(buzzer->pin);
    pwm_set_clkdiv(slice_num, clock_get_hz(clk_sys) / (frequency * 4096));
    buzzer->frequency = frequency;
}

uint buzzer_get_frequency(Buzzer *buzzer) {
    return buzzer->frequency;
}

// ===========================
//    Controle de Volume
// ===========================
void buzzer_set_volume(Buzzer *buzzer, uint volume) {
    if (volume > 100) volume = 100;
    buzzer->level = (volume * MAX_PWM) / 100;
    pwm_set_gpio_level(buzzer->pin, buzzer->level);
}

uint buzzer_get_level(Buzzer *buzzer) {
    return buzzer->level;
}

// ===========================
//    Controle do Beep
// ===========================

// Callback para desligar o buzzer após duration_ms
static int64_t beep_off_callback(alarm_id_t id, void *user_data) {
    buzzer_off(active_buzzer);
    return 0; // Finaliza a interrupção corretamente
}

void buzzer_beep(Buzzer *buzzer, uint duration_ms, uint pause_ms) {
    active_buzzer = buzzer;
    buzzer_on(buzzer);
    
    // Configura o alarme para desligar o beep após o tempo desejado
    beep_off_alarm_id = add_alarm_in_ms(duration_ms, beep_off_callback, NULL, false);
}

//Buzzer_beep sem interrupções:
void buzzer_beep_no_interruption(Buzzer *buzzer, uint duration_ms, uint pause_ms) {
    buzzer_on(buzzer);
    sleep_ms(duration_ms);
    buzzer_off(buzzer);
    sleep_ms(pause_ms);
}

// Liga o buzzer continuamente com o volume atual
void buzzer_on(Buzzer *buzzer) {
    pwm_set_gpio_level(buzzer->pin, buzzer->level);
}

// Desliga o buzzer (atenção, essa função atualiza o valor do level do buzzer para 0)
void buzzer_off(Buzzer *buzzer) {
    pwm_set_gpio_level(buzzer->pin, 0);
    buzzer->level = 0;
}

// ===========================
//    Controle de Melodia
// ===========================

// Callback para tocar a próxima nota
static int64_t melody_timer_callback(alarm_id_t id, void *user_data) {
    if (melody_index < melody_size) {
        buzzer_set_frequency(active_buzzer, active_notes[melody_index]);
        buzzer_beep(active_buzzer, active_durations[melody_index], 100);

        melody_index++;
        
        // Agendar a próxima nota
        add_alarm_in_ms(active_durations[melody_index - 1] + 100, melody_timer_callback, NULL, false);

    }
    return 0;  // Finaliza a interrupção
}

void buzzer_melody(Buzzer *buzzer, const uint *notes, const uint *durations, uint size) {
    active_buzzer = buzzer;
    active_notes = notes;
    active_durations = durations;
    melody_size = size;
    melody_index = 0;

    // Inicia a melodia chamando o primeiro alarme
    melody_timer_callback(0, NULL);
}

//Melody sem interrupção para quando queremos que algo ocorra apenas apos a melodia terminar:
void buzzer_melody_no_interruption(Buzzer *buzzer, const uint *notes, const uint *durations, uint size) {
    for (uint i = 0; i < size; i++) {
        buzzer_set_frequency(buzzer, notes[i]);
        buzzer_beep_no_interruption(buzzer, durations[i], 100);
    }
}