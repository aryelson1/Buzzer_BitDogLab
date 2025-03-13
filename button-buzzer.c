#include <stdio.h>
#include "pico/stdlib.h"
#include "./inc/buzzer.h"
#include "./tests/buzzer_test.h"

void button2_callback(uint gpio, uint32_t events)
{
    if (gpio == BUTTON_PIN2)
    {
        stop(); // Ativa a flag para parar o buzzer
    }
}

int main()
{
    // Configuração do GPIO para o botão como entrada com pull-up
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Configuração do GPIO para o botão 2 como entrada com pull-up
    gpio_init(BUTTON_PIN2);
    gpio_set_dir(BUTTON_PIN2, GPIO_IN);
    gpio_pull_up(BUTTON_PIN2);

    // Configurar a interrupção no pino do botão
    gpio_set_irq_enabled_with_callback(BUTTON_PIN2, GPIO_IRQ_EDGE_FALL, true, &button2_callback);

    // Inicia o BUZZER 1
    buzzer_init(BUZZER_PIN);

    // Inicia o BUZZER 2
    buzzer_init(BUZZER_PIN2);

    // Testa o buzzer 1
    test_buzzer(BUZZER_PIN);

    // Testa o buzzer 2
    test_buzzer(BUZZER_PIN2);

    // Loop infinito
    while (true)
    {
        // Verifica o estado do botão
        if (gpio_get(BUTTON_PIN) == 0)
        {

            // Botão pressionado (nível lógico baixo)
            printf("Button pressed\n");
            stop_buzzer = 0;
            // Melodia para o buzzer A (notas em Hz)
            uint melody_A[] = {392, 392, 0, 311, 466, 392, 0, 466, 392, 587, 587, 0, 622, 466, 369, 0, 466, 392};

            // Melodia para o buzzer B (notas em Hz)
            uint melody_B[] = {0, 392, 392, 311, 0, 0, 311, 0, 0, 0, 587, 587, 0, 0, 0, 311, 0, 392};

            // Duração das notas (em ms)
            uint durations[] = {200, 200, 200, 150, 100, 200, 150, 100, 400, 200, 200, 200, 150, 100, 200, 150, 100, 400};

            // Tocar a melodia
            play_two_buzzer(BUZZER_PIN, BUZZER_PIN2, melody_A, melody_B, durations, sizeof(melody_A) / sizeof(melody_A[0]));

            // Toca a melodia Marcha Imperial
            marcha_imperial();

            // Exemplo de uso do play_flamengo_anthem
            play_flamengo_anthem(BUZZER_PIN); // Toca o hino do Flamengo
        }
    }

    return 0;
}