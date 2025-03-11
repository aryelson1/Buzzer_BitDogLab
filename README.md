# Controle de Buzzer na BitDogLab

Este projeto implementa um controle de buzzer utilizando a BitDogLab, com suporte para tons personalizados, melodias e interrupção via botão.

## 📌 Funcionalidades
- Geração de sons utilizando PWM.
- Emissão de tons personalizados e melodias.
- Interrupção do som ao pressionar um botão.
- Reprodução do hino do Flamengo.

## 🛠️ Hardware Utilizado
- Raspberry Pi Pico
- Buzzer ativo/passivo
- Botões (para ativar e interromper o som)
- Jumpers e protoboard

## 📜 Estrutura do Código
```
├── inc/
│   ├── buzzer.h  # Cabeçalho das funções do buzzer
│   ├── buzzer.c  # Implementação das funções do buzzer
├── src/
│   ├── main.c    # Código principal
├── README.md     # Documentação do projeto
```

## 🚀 Como Compilar e Executar
1. Clone este repositório:
   ```sh
   git clone https://github.com/aryelson1/Buzzer_BitDogLab.git
   cd Buzzer_BitDogLab
   ```
2. Compile o código utilizando o SDK do Raspberry Pi Pico:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
3. Envie o arquivo `.uf2` gerado para o Raspberry Pi Pico.

## 🔧 Configuração dos Pinos
| Componente | Pino do Pico |
|------------|-------------|
| Buzzer     | GP21        |
| Botão 1    | GP5         |
| Botão 2    | GP6         |

## 📖 Documentação das Funções

### `pwm_init_buzzer(uint pin)`
Inicializa o PWM no pino do buzzer.

### `setFrequency(uint pin, uint frequency)`
Define a frequência do som gerado pelo buzzer.

### `beepOn(uint pin, uint frequency)`
Liga o buzzer em uma frequência específica sem pausas.

### `beepOff(uint pin)`
Desliga o buzzer.

### `playTone(uint pin, uint frequency, uint duration_ms)`
Toca um tom por um tempo determinado.

### `playMelody(uint pin, uint melody[], uint durations[], uint length)`
Toca uma sequência de notas musicais.

### `countdown_beep(uint pin, uint count, uint interval)`
Executa uma contagem regressiva com beeps.

### `stop()`
Para qualquer som ativo no buzzer.

### `play_flamengo_anthem(uint pin)`
Toca o hino do Flamengo.

## 📝 Licença
Este projeto é de código aberto e pode ser usado conforme necessário.

