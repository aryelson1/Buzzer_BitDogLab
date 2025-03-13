# Projeto de Controle de Buzzer na BitDogLab

<p align="center">
  <img src="images/VirtusCC.png" alt="Virtus">
</p>

## Autores

- [Aryelson Gonçalves](https://github.com/aryelson1)  

- [Guilherme Santos](https://github.com/GuilhermexL)  

---

## Descrição do Projeto

Este projeto implementa um controle de buzzer utilizando a placa BitDogLab, com suporte para geração de tons personalizados, melodias e interrupção via botão. O código foi desenvolvido para a Raspberry Pi Pico, utilizando o SDK oficial, permitindo controlar um buzzer conectado à placa BitDogLab, oferecendo funcionalidades como:

- Geração de sons utilizando PWM.
- Emissão de tons personalizados e melodias.
- Interrupção do som ao pressionar um botão.
- Reprodução do hino do Flamengo.

---

## Arquitetura do Projeto

![Placa](images/Placa_profile.png)

1. Hardware Utilizado

- 1x Placa BitDogLab
- Buzzer (ativo ou passivo)
- 2 Botões (para ativar e interromper o som)

2. Conexões

- Buzzer: Pino GPIO21
- Botão 1: Pino GPIO5
- Botão 2: Pino GPIO6

---

## Funcionalidades

O projeto oferece as seguintes funcionalidades, implementadas através de funções específicas:

### `pwm_init_buzzer(uint pin)`

- [ ] **Descrição:** Inicializa o PWM no pino do buzzer.
- [ ] **Detalhes:**
  - Configura o pino especificado para saída PWM.
  - Define os parâmetros iniciais do PWM, como frequência e duty cycle.

### `setFrequency(uint pin, uint frequency)`

- [ ] **Descrição:** Define a frequência do som gerado pelo buzzer.
- [ ] **Detalhes:**
  - Ajusta a frequência do PWM no pino especificado.
  - Aceita valores de frequência dentro de um intervalo específico (ex: 20Hz a 20kHz).

### `beepOn(uint pin, uint frequency)`

- [ ] **Descrição:** Liga o buzzer em uma frequência específica sem pausas.
- [ ] **Detalhes:**
  - Ativa o PWM no pino especificado com a frequência definida.
  - Mantém o som ativo até que `beepOff` seja chamado.

### `beepOff(uint pin)`

- [ ] **Descrição:** Desliga o buzzer.
- [ ] **Detalhes:**
  - Interrompe o PWM no pino especificado, parando o som.

### `playTone(uint pin, uint frequency, uint duration_ms)`

- [ ] **Descrição:** Toca um tom por um tempo determinado.
- [ ] **Detalhes:**
  - Ativa o buzzer com a frequência especificada.
  - Mantém o som ativo pelo tempo definido em milissegundos.
  - Desliga o buzzer automaticamente após o término.

### `playMelody(uint pin, uint melody[], uint durations[], uint length)`

- [ ] **Descrição:** Toca uma sequência de notas musicais.
- [ ] **Detalhes:**
  - Recebe dois arrays: um com as frequências das notas e outro com as durações.
  - Reproduz cada nota na sequência, respeitando a duração especificada.

### `countdown_beep(uint pin, uint count, uint interval)`

- [ ] **Descrição:** Executa uma contagem regressiva com beeps.
- [ ] **Detalhes:**
  - Emite um beep a cada intervalo de tempo especificado.
  - Repete o processo pelo número de vezes definido em `count`.

### `stop()`

- [ ] **Descrição:** Para qualquer som ativo no buzzer.
- [ ] **Detalhes:**
  - Interrompe todas as operações de PWM relacionadas ao buzzer.
  - Garante que o buzzer seja desligado imediatamente.

### `play_flamengo_anthem(uint pin)`

- [ ] **Descrição:** Toca o hino do Flamengo.
- [ ] **Detalhes:**
  - Utiliza a função `playMelody` para reproduzir a melodia do hino.
  - Inclui as frequências e durações das notas do hino.

---

## Casos de Teste para o Buzzer

### 1. **Teste de Variação de Frequência**
   - **Objetivo**: Verificar se o buzzer é capaz de reproduzir tons em uma ampla faixa de frequências.
   - **Passos**:
     1. Inicializa o buzzer com `pwm_init_buzzer(pin)`.
     2. Aumenta a frequência gradualmente de 20 Hz até 5000 Hz, com incrementos de 10 Hz.
     3. Toca cada frequência por 100 ms, com um pequeno atraso de 50 ms entre as notas.
     4. Verifica se o buzzer para imediatamente caso a variável `stop_buzzer` seja verdadeira.
   - **Resultado Esperado**: O buzzer emite tons em frequências crescentes, começando em 20 Hz e terminando em 5000 Hz, ou para imediatamente se `stop_buzzer` for ativado.

---

## Casos de Teste

### Teste de Variação de Frequência
Este teste verifica se o buzzer é capaz de reproduzir tons em uma ampla faixa de frequências, desde 20 Hz até 5000 Hz. O teste aumenta a frequência gradualmente, com incrementos de 10 Hz, e toca cada frequência por 100 ms. Caso a variável `stop_buzzer` seja ativada, o buzzer para imediatamente.

#### Passos:
1. Inicializa o buzzer com `pwm_init_buzzer(pin)`.
2. Aumenta a frequência de 20 Hz até 5000 Hz, com incrementos de 10 Hz.
3. Toca cada frequência por 100 ms, com um atraso de 50 ms entre as notas.
4. Verifica se o buzzer para imediatamente caso `stop_buzzer` seja verdadeiro.

#### Resultado Esperado:
- O buzzer emite tons em frequências crescentes, começando em 20 Hz e terminando em 5000 Hz.
- O buzzer para imediatamente se `stop_buzzer` for ativado.

---

### Exemplo de Uso no Código

Aqui está um exemplo de como você pode chamar o teste no seu código principal:

```c
#ifndef BUZZER_TEST_H
#define BUZZER_TEST_H

#include "pico/stdlib.h"
#include "../inc/buzzer.h"

// Declaração da função de teste do buzzer
void test_buzzer(uint pin);

#endif // BUZZER_TEST_H
```

---

## Como Compilar e Executar

### Requisitos

- **Visual Studio Code** (ou outra IDE compatível)
- **Extensão Raspberry Pi Pico** (para desenvolvimento com Raspberry Pi Pico)
- **Raspberry Pi Pico SDK** (versão 1.5.1)

### Passos para Compilação

1. Clone o repositório do projeto.
2. Abra o projeto no Visual Studio Code.
3. Importe o projeto utilizando a extensão Raspberry Pi Pico.
4. Configure o SDK para a versão 1.5.1.

### Passos para Execução

1. Conecte a Raspberry Pi Pico ao computador via USB.
2. Carregue o arquivo `.uf2` gerado na Pico.
   - Alternativamente, instale o **Zadig** para executar diretamente do VSCode.
3. Interaja com os botões para emitir sons no buzzer.

---

## Conclusão

Este projeto demonstra como controlar um buzzer utilizando a Raspberry Pi Pico e a placa BitDogLab. Ele pode ser expandido para incluir novas funcionalidades, como a reprodução de outras músicas ou a integração com sensores para criar sistemas interativos.

---

## Referências
  
  - [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk)  

  - [Documentação oficial da Raspberry Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/)  

---
