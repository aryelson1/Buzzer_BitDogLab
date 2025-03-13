#ifndef BUZZER_H
#define BUZZER_H

// Inclusão das bibliotecas necessárias
#include "pico/stdlib.h"       // Biblioteca padrão do Raspberry Pi Pico
#include "hardware/pwm.h"     // Biblioteca para controle de PWM
#include "hardware/clocks.h"  // Biblioteca para controle de clocks

// Definição dos pinos dos botões e buzzers
#define BUTTON_PIN 5          // Pino do botão 1
#define BUTTON_PIN2 6         // Pino do botão 2
#define BUZZER_PIN 21         // Pino do buzzer 1
#define BUZZER_PIN2 8         // Pino do buzzer 2

// Variável global para controlar se o buzzer deve parar
extern int stop_buzzer;       // Declaração da variável global para controle de interrupção

// Definição da estrutura para representar uma nota musical
typedef struct {
    uint frequencia_A;        // Frequência da nota para o buzzer A (em Hz)
    uint frequencia_B;        // Frequência da nota para o buzzer B (em Hz)
    float duracao;            // Duração da nota (em segundos)
} Nota;

// Declaração das funções

// Inicializa o BUZZER
void buzzer_init(uint pin);

// Inicializa o PWM no pino do buzzer
void pwm_init_buzzer(uint pin);

// Define a frequência do buzzer
void setFrequency(uint pin, uint frequency);

// Liga o buzzer continuamente com uma frequência específica
void beepOn(uint pin, uint frequency);

// Desliga o buzzer
void beepOff(uint pin);

// Toca um tom específico com uma frequência e duração definidas
void playTone(uint pin, uint frequency, uint duration_ms);

// Toca uma melodia em um único buzzer
void playMelody(uint pin, uint melody[], uint durations[], uint length);

// Toca uma melodia com dois buzzers (notas simultâneas ou individuais)
void play_two_buzzer(uint pin_A, uint pin_B, uint melody_A[], uint melody_B[], uint durations[], uint length);

// Toca uma sequência de beeps (contagem regressiva)
void countdown_beep(uint pin, uint count, uint interval);

// Interrompe qualquer som tocado
void stop();

// Toca o hino do Flamengo
void play_flamengo_anthem(uint pin);

// Toca uma nota em um buzzer específico
void tocar_nota(uint pin, uint frequencia, float duracao);

// Toca uma harmonia (notas simultâneas em dois buzzers)
void tocar_harmonia(uint pin_A, uint pin_B, uint frequencia_A, uint frequencia_B, float duracao);

// Toca a Marcha Imperial
void marcha_imperial();

#endif // BUZZER_H