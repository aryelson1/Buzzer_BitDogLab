#include "buzzer_test.h"

// Função para testar o buzzer
void test_buzzer(uint pin) {
    uint frequencia_minima = 20;   // Frequência mínima audível (20 Hz)
    uint frequencia_maxima = 5000; // Frequência máxima suportada pelo buzzer (5 kHz)
    uint incremento = 10;          // Incremento de frequência a cada passo (10 Hz)
    uint duracao_nota = 100;       // Duração de cada nota em milissegundos (100 ms)

    // Inicializa o buzzer
    pwm_init_buzzer(pin);

    // Loop para aumentar a frequência gradualmente
    for (uint frequencia = frequencia_minima; frequencia <= frequencia_maxima; frequencia += incremento) {
        if (stop_buzzer) {
            beepOff(pin); // Desliga o buzzer se a variável stop_buzzer for verdadeira
            return;       // Sai da função
        }

        // Toca a nota com a frequência atual
        playTone(pin, frequencia, duracao_nota);

        // Pequeno atraso para ouvir a mudança no tom
        sleep_ms(50);
    }

    // Desliga o buzzer ao final do teste
    beepOff(pin);
}