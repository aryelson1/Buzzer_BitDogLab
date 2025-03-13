#ifndef BUZZER_TEST_H
#define BUZZER_TEST_H

#include "pico/stdlib.h" // Inclui funções padrão do Raspberry
#include "buzzer.h"      // Inclui as funções do buzzer

// Declarações das funções de teste
void test_beep_on_off(void);
void test_play_tone(void);
void test_countdown_beep(void);
void test_play_melody(void);
void test_play_flamengo_anthem(void);
void test_stop(void);
void test_button_interaction(void);

#endif // BUZZER_TEST_H