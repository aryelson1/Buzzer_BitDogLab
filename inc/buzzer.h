#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define BUTTON_PIN 5
#define BUTTON_PIN2 6
#define BUZZER_PIN 21

// Declaração das funções
void pwm_init_buzzer(uint pin);
void setFrequency(uint pin, uint frequency);
void beepOn(uint pin, uint frequency);
void beepOff(uint pin);
void playTone(uint pin, uint frequency, uint duration_ms);
void playMelody(uint pin, uint melody[], uint durations[], uint length);
void countdown_beep(uint pin, uint count, uint interval);
void stop();

void play_flamengo_anthem(uint pin);

#endif // BUZZER_H