#include "buzzer.h"

int stop_buzzer = 0; // Variável global para controlar a interrupção do buzzer

// Função para inicializar o PWM no pino do buzzer
void buzzer_init(uint pin)
{

    // Configuração do GPIO para o buzzer como saída
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);

    // Inicializar o PWM no pino do buzzer
    pwm_init_buzzer(pin);
}

// Função para inicializar o PWM no pino do buzzer
void pwm_init_buzzer(uint pin)
{
    // Configura o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Obtém o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configura o PWM com valores padrão
    pwm_config config = pwm_get_default_config();
    pwm_init(slice_num, &config, true);

    // Inicia o PWM com nível baixo (sem som)
    pwm_set_gpio_level(pin, 0);
}

// Função para definir a frequência do buzzer
void setFrequency(uint pin, uint frequency)
{
    // Evita divisão por zero
    if (frequency == 0)
        return;

    // Obtém o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configura o PWM com a nova frequência
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (frequency * 4096)); // Divisor de clock
    pwm_init(slice_num, &config, true);

    // Define o duty cycle para 50% (ativo)
    pwm_set_gpio_level(pin, 2048); // 2048 = 50% de 4096 (12 bits)
}

// Função para ligar o buzzer continuamente
void beepOn(uint pin, uint frequency)
{
    // Obtém o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configura o PWM com a frequência desejada
    pwm_set_clkdiv(slice_num, clock_get_hz(clk_sys) / (frequency * 4096));
    pwm_set_wrap(slice_num, 4095);

    // Define o duty cycle para 50% (ativo)
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), 2048);

    // Habilita o PWM
    pwm_set_enabled(slice_num, true);
}

// Função para desligar o buzzer
void beepOff(uint pin)
{
    // Desativa o sinal PWM (duty cycle 0)
    pwm_set_gpio_level(pin, 0);
}

// Função para parar o buzzer
void stop()
{
    // Define a variável global para interromper qualquer som
    stop_buzzer = 1;
}

// Função para tocar um tom específico com uma frequência e duração definidas
void playTone(uint pin, uint frequency, uint duration_ms)
{
    // Obtém o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configura o PWM com a frequência desejada
    pwm_set_clkdiv(slice_num, clock_get_hz(clk_sys) / (frequency * 4096));
    pwm_set_wrap(slice_num, 4095);

    // Define o duty cycle para 50% (ativo)
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), 2048);

    // Habilita o PWM
    pwm_set_enabled(slice_num, true);

    // Mantém a nota pelo tempo especificado
    sleep_ms((uint)(duration_ms));

    // Desliga o buzzer
    pwm_set_gpio_level(pin, 0);
}

// Função para tocar uma melodia com dois buzzers
void play_two_buzzer(uint pin_A, uint pin_B, uint melody_A[], uint melody_B[], uint durations[], uint length)
{
    for (int i = 0; i < length; i++)
    {
        // Verifica se o buzzer deve ser interrompido
        if (stop_buzzer)
        {
            pwm_set_gpio_level(pin_A, 0); // Desativa o sinal PWM no buzzer A
            pwm_set_gpio_level(pin_B, 0); // Desativa o sinal PWM no buzzer B
            return;                       // Sai da função
        }

        // Toca a nota atual no buzzer A (se houver)
        if (melody_A[i] > 0)
        {
            playTone(pin_A, melody_A[i], durations[i]);
        }

        // Toca a nota atual no buzzer B (se houver)
        if (melody_B[i] > 0)
        {
            playTone(pin_B, melody_B[i], durations[i]);
        }

        // Pausa entre as notas (opcional, para evitar sobreposição)
        sleep_ms(50); // Ajuste conforme necessário
    }

    // Desliga os buzzers ao final
    pwm_set_gpio_level(pin_A, 0);
    pwm_set_gpio_level(pin_B, 0);
}

// Função para tocar uma sequência de beeps (contagem regressiva)
void countdown_beep(uint pin, uint count, uint interval)
{
    for (int i = 0; i < count; i++)
    {
        // Verifica se o buzzer deve ser interrompido
        if (stop_buzzer)
        {
            pwm_set_gpio_level(pin, 0); // Desativa o sinal PWM
            return;                     // Sai da função
        }

        // Toca um beep de 1kHz por 100ms
        playTone(pin, 1000, 100);

        // Intervalo entre os beeps
        sleep_ms(interval);
    }
}

// Função para tocar uma melodia em um único buzzer
void playMelody(uint pin, uint melody[], uint durations[], uint length)
{
    for (int i = 0; i < length; i++)
    {
        // Verifica se o buzzer deve ser interrompido
        if (stop_buzzer)
        {
            pwm_set_gpio_level(pin, 0); // Desativa o sinal PWM
            return;                     // Sai da função
        }

        // Toca a nota atual
        playTone(pin, melody[i], durations[i]);

        // Pausa entre as notas (opcional, para evitar sobreposição)
        sleep_ms(50); // Ajuste conforme necessário
    }
}

// Função para tocar o hino do Flamengo
void play_flamengo_anthem(uint pin)
{
    // Frequências das notas (em Hz)
    uint melody[] = {
        330, 330, 392, 392, 440, 440, 392, // E4 E4 G4 G4 A4 A4 G4
        349, 349, 330, 330, 294, 294, 330, // F4 F4 E4 E4 D4 D4 E4
        330, 330, 392, 392, 440, 440, 392, // E4 E4 G4 G4 A4 A4 G4
        349, 349, 330, 330, 294, 294, 330, // F4 F4 E4 E4 D4 D4 E4
        392, 392, 440, 440, 494, 494, 440, // G4 G4 A4 A4 B4 B4 A4
        392, 392, 349, 349, 330, 330, 294, // G4 G4 F4 F4 E4 E4 D4
        330, 330, 392, 392, 440, 440, 392, // E4 E4 G4 G4 A4 A4 G4
        349, 349, 330, 330, 294, 294, 330  // F4 F4 E4 E4 D4 D4 E4
    };

    // Duração de cada nota (em ms)
    uint duration[] = {
        500, 500, 500, 500, 500, 500, 1000, // Notas da primeira linha
        500, 500, 500, 500, 500, 500, 1000, // Notas da segunda linha
        500, 500, 500, 500, 500, 500, 1000, // Notas da terceira linha
        500, 500, 500, 500, 500, 500, 1000, // Notas da quarta linha
        500, 500, 500, 500, 500, 500, 1000, // Notas da quinta linha
        500, 500, 500, 500, 500, 500, 1000, // Notas da sexta linha
        500, 500, 500, 500, 500, 500, 1000, // Notas da sétima linha
        500, 500, 500, 500, 500, 500, 1000  // Notas da oitava linha
    };

    // Toca a melodia
    playMelody(pin, melody, duration, sizeof(melody) / sizeof(melody[0]));
}

// Função para tocar a Marcha Imperial
void marcha_imperial()
{
    // Definição das notas e durações
    Nota notas[] = {
        {392, 0, 0.2},    // G
        {392, 392, 0.2},  // Harmonia G em ambos
        {392, 0, 0.2},    // G
        {311, 0, 0.15},   // Eb
        {466, 0, 0.1},    // Bb
        {392, 0, 0.2},    // G
        {311, 311, 0.15}, // Harmonia Eb em ambos
        {466, 0, 0.1},    // Bb
        {392, 0, 0.4},    // G
        {587, 0, 0.2},    // D
        {587, 587, 0.2},  // Harmonia D em ambos
        {587, 0, 0.2},    // D
        {622, 0, 0.15},   // Eb
        {466, 0, 0.1},    // Bb
        {369, 0, 0.2},    // G#
        {311, 311, 0.15}, // Harmonia Eb em ambos
        {466, 0, 0.1},    // Bb
        {392, 392, 0.4}   // Harmonia G em ambos
    };

    // Toca a sequência de notas
    for (int rep = 0; rep < 5; rep++)
    {
        for (int i = 0; i < sizeof(notas) / sizeof(notas[0]); i++)
        {
            // Verifica se o buzzer deve ser interrompido
            if (stop_buzzer)
            {
                pwm_set_gpio_level(BUZZER_PIN, 0); // Desativa o sinal PWM
                pwm_set_gpio_level(BUZZER_PIN2, 0); // Desativa o sinal PWM

                return;                     // Sai da função
            }

            if (notas[i].frequencia_B > 0)
            {
                // Toca harmonia
                tocar_harmonia(BUZZER_PIN, BUZZER_PIN2, notas[i].frequencia_A, notas[i].frequencia_B, notas[i].duracao);
            }
            else
            {
                // Toca nota única no buzzer A
                tocar_nota(BUZZER_PIN, notas[i].frequencia_A, notas[i].duracao);
            }
        }
    }
}

// Função para tocar uma nota em um buzzer
void tocar_nota(uint pin, uint frequencia, float duracao)
{
    if (frequencia > 0)
    { // Verifica se a frequência é válida
        // Configura o PWM para a frequência desejada
        gpio_set_function(pin, GPIO_FUNC_PWM);
        uint slice_num = pwm_gpio_to_slice_num(pin);
        pwm_set_clkdiv(slice_num, clock_get_hz(clk_sys) / (frequencia * 4096));
        pwm_set_wrap(slice_num, 4095);
        pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), 2048); // 50% duty cycle
        pwm_set_enabled(slice_num, true);

        // Mantém a nota pelo tempo especificado
        sleep_ms((uint)(duracao * 1000));

        // Desliga o buzzer
        pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), 0);
    }
    else
    {
        // Para frequências inválidas, apenas faz uma pausa
        sleep_ms((uint)(duracao * 1000));
    }
}

// Função para tocar harmonias (notas simultâneas em dois buzzers)
void tocar_harmonia(uint pin_A, uint pin_B, uint frequencia_A, uint frequencia_B, float duracao)
{
    // Configura o PWM para o buzzer A
    if (frequencia_A > 0)
    {
        gpio_set_function(pin_A, GPIO_FUNC_PWM);
        uint slice_num_A = pwm_gpio_to_slice_num(pin_A);
        pwm_set_clkdiv(slice_num_A, clock_get_hz(clk_sys) / (frequencia_A * 4096));
        pwm_set_wrap(slice_num_A, 4095);
        pwm_set_chan_level(slice_num_A, pwm_gpio_to_channel(pin_A), 2048); // 50% duty cycle
        pwm_set_enabled(slice_num_A, true);
    }

    // Configura o PWM para o buzzer B
    if (frequencia_B > 0)
    {
        gpio_set_function(pin_B, GPIO_FUNC_PWM);
        uint slice_num_B = pwm_gpio_to_slice_num(pin_B);
        pwm_set_clkdiv(slice_num_B, clock_get_hz(clk_sys) / (frequencia_B * 4096));
        pwm_set_wrap(slice_num_B, 4095);
        pwm_set_chan_level(slice_num_B, pwm_gpio_to_channel(pin_B), 2048); // 50% duty cycle
        pwm_set_enabled(slice_num_B, true);
    }

    // Mantém a harmonia pelo tempo especificado
    sleep_ms((uint)(duracao * 1000));

    // Desliga os buzzers
    if (frequencia_A > 0)
    {
        uint slice_num_A = pwm_gpio_to_slice_num(pin_A);
        pwm_set_chan_level(slice_num_A, pwm_gpio_to_channel(pin_A), 0);
    }
    if (frequencia_B > 0)
    {
        uint slice_num_B = pwm_gpio_to_slice_num(pin_B);
        pwm_set_chan_level(slice_num_B, pwm_gpio_to_channel(pin_B), 0);
    }
}