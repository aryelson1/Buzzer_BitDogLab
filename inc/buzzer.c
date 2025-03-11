#include "buzzer.h"

// Variável global para controlar se o buzzer deve parar
volatile bool stop_buzzer = false;

// Função para inicializar o PWM no pino do buzzer
void pwm_init_buzzer(uint pin)
{
    // Configurar o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o PWM com um valor inicial (frequência será configurada no beep)
    pwm_config config = pwm_get_default_config();
    pwm_init(slice_num, &config, true);

    // Iniciar o PWM no nível baixo
    pwm_set_gpio_level(pin, 0);
}

// Função para definir a frequência do buzzer
void setFrequency(uint pin, uint frequency)
{

    // Evita divisão por zero
    if (frequency == 0) return;

    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o PWM com a nova frequência
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (frequency * 4096)); // Divisor de clock
    pwm_init(slice_num, &config, true);

    // Manter o duty cycle em 50% (ativo)
    pwm_set_gpio_level(pin, 2048); // 2048 = 50% de 4096 (12 bits)
}

// Função para ligar o buzzer continuamente
void beepOn(uint pin, uint frequency)
{
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o PWM com a frequência desejada
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (frequency * 4096)); // Divisor de clock
    pwm_init(slice_num, &config, true);

    // Configurar o duty cycle para 50% (ativo)
    pwm_set_gpio_level(pin, 2048); // 2048 = 50% de 4096 (12 bits)
}

// Função para desligar o buzzer
void beepOff(uint pin)
{
    // Desativar o sinal PWM (duty cycle 0)
    pwm_set_gpio_level(pin, 0);
}

// Função para parar o buzzer
void stop()
{
    stop_buzzer = true;
}

// Função para tocar um tom específico com uma frequência e duração definidas
void playTone(uint pin, uint frequency, uint duration_ms)
{
    // Configurar a frequência
    setFrequency(pin, frequency);

    // Ligar o buzzer
    pwm_set_gpio_level(pin, 2048); // 50% de duty cycle

    // Manter o tom pelo tempo especificado
    sleep_ms(duration_ms);

    // Desligar o buzzer
    pwm_set_gpio_level(pin, 0);
}

void countdown_beep(uint pin, uint count, uint interval)
{
    for (int i = 0; i < count; i++)
    {
        if (stop_buzzer)
        {
            stop_buzzer = false;        // Reseta a flag
            pwm_set_gpio_level(pin, 0); // Desativa o sinal PWM
            return;                     // Sai da função
        }
        playTone(pin, 1000, 100); // Beep de 1kHz por 100ms
        sleep_ms(interval);       // Intervalo entre os beeps
    }
}

// Função para tocar uma melodia
void playMelody(uint pin, uint melody[], uint durations[], uint length)
{
    for (int i = 0; i < length; i++)
    {
        if (stop_buzzer)
        {
            stop_buzzer = false;        // Reseta a flag
            pwm_set_gpio_level(pin, 0); // Desativa o sinal PWM
            return;                     // Sai da função
        }

        // Tocar a nota atual
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

    // Tocar a melodia
    playMelody(pin, melody, duration, sizeof(melody) / sizeof(melody[0]));
}