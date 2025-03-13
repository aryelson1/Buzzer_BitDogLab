#include "buzzer_test.h"
#include <stdio.h>

// Função para testar ativação e desativação do buzzer
void test_beep_on_off() {
    printf("Teste 1: Ativação e Desativação do Buzzer\n");
    beepOn(BUZZER_PIN, 440); // Ativa o buzzer com 440 Hz
    sleep_ms(1000);          // Mantém ativo por 1 segundo
    beepOff(BUZZER_PIN);     // Desativa o buzzer
    printf("Teste 1 Concluído\n\n");
}

// Função para testar reprodução de tons com duração
void test_play_tone() {
    printf("Teste 2: Reprodução de Tons com Duração\n");
    playTone(BUZZER_PIN, 262, 500);  // Dó por 500 ms
    playTone(BUZZER_PIN, 330, 1000); // Mi por 1000 ms
    playTone(BUZZER_PIN, 392, 2000); // Sol por 2000 ms
    printf("Teste 2 Concluído\n\n");
}

// Função para testar contagem regressiva com beeps
void test_countdown_beep() {
    printf("Teste 3: Contagem Regressiva com Beeps\n");
    countdown_beep(BUZZER_PIN, 5, 500); // 5 beeps com intervalo de 500 ms
    printf("Teste 3 Concluído\n\n");
}

// Função para testar reprodução de uma melodia
void test_play_melody() {
    printf("Teste 4: Reprodução de Melodia\n");
    uint melody[] = {262, 294, 330, 349, 392}; // Dó, Ré, Mi, Fá, Sol
    uint durations[] = {500, 500, 500, 500, 500}; // 500 ms cada nota
    playMelody(BUZZER_PIN, melody, durations, 5);
    printf("Teste 4 Concluído\n\n");
}

// Função para testar reprodução do hino do Flamengo
void test_play_flamengo_anthem() {
    printf("Teste 5: Reprodução do Hino do Flamengo\n");
    play_flamengo_anthem(BUZZER_PIN);
    printf("Teste 5 Concluído\n\n");
}

// Função para testar parada forçada do buzzer
void test_stop() {
    printf("Teste 6: Parada Forçada\n");
    playTone(BUZZER_PIN, 440, 5000); // Tocar por 5 segundos
    sleep_ms(1000);                  // Esperar 1 segundo
    stop();                          // Parar o buzzer
    printf("Teste 6 Concluído\n\n");
}

// Função para testar interação com os botões
void test_button_interaction() {
    printf("Teste 7: Interação com Botões\n");

    // Simula o pressionamento do botão 1
    printf("Simulando pressionamento do Botão 1...\n");
    countdown_beep(BUZZER_PIN, 10, 1000); // 10 beeps com intervalo de 1 segundo

    // Simula o pressionamento do botão 2
    printf("Simulando pressionamento do Botão 2...\n");
    stop(); // Para o buzzer
    printf("Buzzer parado pelo Botão 2\n");

    printf("Teste 7 Concluído\n\n");
}