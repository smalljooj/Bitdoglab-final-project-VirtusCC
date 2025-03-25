#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

// Estrutura para armazenar o estado de cada buzzer
typedef struct {
  uint pin;
  uint frequency;
  uint level;
  uint pause_ms; 
} Buzzer;


// Função para inicializar o buzzer com uma frequência específica
void buzzer_init(Buzzer *buzzer, uint pin, uint freq);

// Função para alterar a frequência do buzzer em tempo real
void buzzer_set_frequency(Buzzer *buzzer, uint frequency);

// Função para tocar um beep por um determinado tempo (essa função utiliza interrupção)
void buzzer_beep(Buzzer *buzzer, uint duration_ms, uint pause_ms);

// Função para tocar um beep por um determinado tempo (essa função não utiliza interrupção)
void buzzer_beep_no_interruption(Buzzer *buzzer, uint duration_ms, uint pause_ms);

// Função para ligar o buzzer manualmente (atenção, o buzzer será ligado com o valor armazenado no level.)
void buzzer_on(Buzzer *buzzer);
// Desliga o buzzer (atenção, essa função atualiza o valor do level do buzzer para 0)
void buzzer_off(Buzzer *buzzer);

// Ajusta o volume do buzzer alterando o duty cycle
void buzzer_set_volume(Buzzer *buzzer, uint volume);

//retorna a frequência do buzzer
uint buzzer_get_frequency(Buzzer *buzzer);

// toca uma sequência de tons definidos pelo usuário (essa função utiliza interrupção).
void buzzer_melody(Buzzer *buzzer, const uint *notes, const uint *durations, uint size);

// toca uma sequência de tons definidos pelo usuário (essa função não utiliza interrupção).
void buzzer_melody_no_interruption(Buzzer *buzzer, const uint *notes, const uint *durations, uint size);

//retorna o volume em pwm
uint buzzer_get_level(Buzzer *buzzer);

#endif // BUZZER_H