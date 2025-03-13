#include <stdio.h>
#include "pico/stdlib.h"
#include "./inc/buzzer.h"


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

    // Configuração do GPIO para o buzzer como saída
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Inicializar o PWM no pino do buzzer
    pwm_init_buzzer(BUZZER_PIN);

    // Configurar a interrupção no pino do botão
    gpio_set_irq_enabled_with_callback(BUTTON_PIN2, GPIO_IRQ_EDGE_FALL, true, &button2_callback);

    // Exemplo de uso do beepOn e beepOff
    beepOn(BUZZER_PIN, 1000); // Liga o buzzer em 1kHz
    sleep_ms(1000);           // Mantém ligado por 1 segundo
    beepOff(BUZZER_PIN);      // Desliga o buzzer

    // Exemplo de uso do playTone
    playTone(BUZZER_PIN, 500, 500); // Toca um tom de 500Hz por 500ms

    // Exemplo de uso do play_flamengo_anthem
    play_flamengo_anthem(BUZZER_PIN); // Toca o hino do Flamengo

    // Loop infinito
    while (true)
    {
        // Verifica o estado do botão
        if (gpio_get(BUTTON_PIN) == 0){   
            
            // Botão pressionado (nível lógico baixo)
            printf("Button pressed\n");

            // Exemplo de uso do countdown_beep
            countdown_beep(BUZZER_PIN, 10, 1000);

            // Exemplo de uso do playMelody
            uint melody[] = {262, 294, 330, 349, 392, 440, 494, 523};    // Notas da escala musical
            uint durations[] = {500, 500, 500, 500, 500, 500, 500, 500}; // Duração de cada nota
            playMelody(BUZZER_PIN, melody, durations, 8);                // Toca a melodia
        }
    }

    // Executar os testes
    test_beep_on_off();
    test_play_tone();
    test_countdown_beep();
    test_play_melody();
    test_play_flamengo_anthem();
    test_stop();
    test_button_interaction();

    return 0;
}