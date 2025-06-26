# Documentação Técnica - Controle de Servomotor com Joystick

## Visão Geral

Este projeto implementa um sistema de controle de ângulo de servomotor utilizando o microcontrolador Raspberry Pi Pico W (RP2040). O sistema utiliza o conversor A/D (ADC) para ler a posição de um joystick analógico e o módulo PWM para controlar o ângulo do servomotor.

## Arquitetura do Sistema

### Componentes Principais

1. **Microcontrolador RP2040**
   - Processador dual-core ARM Cortex-M0+
   - 264KB de RAM SRAM
   - 2MB de Flash
   - 30 pinos GPIO

2. **Conversor A/D (ADC)**
   - Resolução: 12 bits (0-4095)
   - 4 canais ADC (GP26, GP27, GP28, GP29)
   - Taxa de amostragem: até 500kSPS
   - Referência: 3.3V

3. **Módulo PWM**
   - 8 slices PWM independentes
   - 16 canais PWM
   - Frequência configurável
   - Resolução de 16 bits

### Esquema de Conexões

```
Raspberry Pi Pico W
├── GP0  → Servomotor (Sinal PWM)
├── GP26 → Joystick (Eixo X - ADC0)
├── GP27 → Joystick (Eixo Y - ADC1) [Reservado]
├── GP22 → Botão (Centralização)
├── 3V3  → Alimentação dos componentes
└── GND  → Terra comum
```

## Implementação do Código

### Estrutura do Programa

1. **Inicialização**
   - Configuração do sistema
   - Inicialização do PWM
   - Configuração do ADC
   - Setup do botão

2. **Loop Principal**
   - Leitura do joystick
   - Processamento dos dados
   - Controle do servomotor
   - Interface com usuário

### Funções Principais

#### `set_servo_angle(uint gpio, float angle)`
- **Propósito**: Configura o ângulo do servomotor
- **Parâmetros**:
  - `gpio`: Pino GPIO conectado ao servo
  - `angle`: Ângulo desejado (0-180°)
- **Funcionamento**:
  1. Limita o ângulo entre 0 e 180°
  2. Calcula a largura do pulso (1000-2000μs)
  3. Converte para duty cycle do PWM
  4. Aplica o sinal

#### `read_joystick(uint adc_input)`
- **Propósito**: Lê o valor do joystick com zona morta
- **Parâmetros**:
  - `adc_input`: Canal ADC a ser lido
- **Retorno**: Valor processado (0-4095)
- **Funcionalidades**:
  - Aplica zona morta para evitar drift
  - Centraliza valores próximos ao centro

#### `map_adc_to_angle(uint16_t adc_value)`
- **Propósito**: Mapeia valor ADC para ângulo
- **Parâmetros**:
  - `adc_value`: Valor lido do ADC
- **Retorno**: Ângulo mapeado (0-180°)

## Especificações Técnicas

### Servomotor
- **Tipo**: Micro servo padrão
- **Faixa de movimento**: 0-180°
- **Frequência de controle**: 50Hz
- **Largura de pulso**: 1000-2000μs
- **Tensão de alimentação**: 4.8-6V

### Joystick Analógico
- **Tipo**: Potenciômetro duplo
- **Resolução**: 10kΩ
- **Faixa de movimento**: 0-4095 (12 bits)
- **Zona morta**: ±100 unidades

### PWM
- **Frequência**: 50Hz
- **Período**: 20ms
- **Resolução**: 16 bits
- **Duty cycle**: 5-10% (1000-2000μs)

## Parâmetros de Configuração

```c
// Servomotor
#define SERVO_MIN_PULSE_US 1000   // Pulso mínimo (0°)
#define SERVO_MAX_PULSE_US 2000   // Pulso máximo (180°)
#define SERVO_PERIOD_US 20000     // Período (20ms)
#define SERVO_MIN_ANGLE 0.0f      // Ângulo mínimo
#define SERVO_MAX_ANGLE 180.0f    // Ângulo máximo

// ADC
#define ADC_RESOLUTION 4095       // Resolução (12 bits)
#define ADC_DEADZONE 100          // Zona morta
```

## Fluxo de Dados

```
Joystick → ADC → Processamento → PWM → Servomotor
   ↓         ↓         ↓         ↓        ↓
 0-4095   12 bits   Zona morta  50Hz    0-180°
```

## Considerações de Design

### Zona Morta
- Implementada para evitar drift do joystick
- Centraliza valores próximos ao centro (±100 unidades)
- Melhora a estabilidade do controle

### Taxa de Atualização
- Configurada para 20Hz (50ms)
- Balanceia responsividade e estabilidade
- Evita sobrecarga do sistema

### Debounce do Botão
- Implementado para evitar múltiplas ativações
- Delay de 200ms após ativação
- Melhora a experiência do usuário

## Testes e Validação

### Testes Realizados
1. **Calibração do ADC**
   - Verificação da linearidade
   - Teste de zona morta
   - Validação da resolução

2. **Controle do Servomotor**
   - Teste de faixa completa (0-180°)
   - Verificação da precisão
   - Teste de estabilidade

3. **Interface do Usuário**
   - Teste do botão de centralização
   - Validação da saída serial
   - Teste de responsividade

### Resultados Esperados
- **Precisão do ângulo**: ±1°
- **Tempo de resposta**: <100ms
- **Estabilidade**: Sem oscilações
- **Linearidade**: >95%

## Possíveis Melhorias

1. **Controle PID**
   - Implementar controle proporcional-integral-derivativo
   - Melhorar a precisão e estabilidade

2. **Interface Gráfica**
   - Adicionar display LCD/OLED
   - Mostrar ângulo atual e valores do ADC

3. **Controle Remoto**
   - Implementar comunicação WiFi
   - Controle via aplicativo móvel

4. **Múltiplos Servos**
   - Expandir para controle de múltiplos servomotores
   - Implementar controle coordenado

## Conclusão

O sistema implementado atende aos requisitos especificados, utilizando eficientemente os recursos do RP2040. O uso do ADC para leitura do joystick e PWM para controle do servomotor proporciona um controle preciso e responsivo, adequado para aplicações educacionais e de prototipagem. 