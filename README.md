# Controle de Intensidade LED RGB com Joystick Analógico

Este projeto implementa um sistema de controle de intensidade de LED RGB utilizando o microcontrolador Raspberry Pi Pico W (RP2040), empregando o conversor A/D (ADC) para leitura do joystick analógico e o módulo PWM para controle da intensidade do LED.

## Características do Projeto

- **Microcontrolador**: Raspberry Pi Pico W (RP2040)
- **Controle**: Joystick analógico (eixo horizontal)
- **Atuador**: LED RGB
- **Interface**: Botão para ligar/desligar o LED
- **Ferramenta**: PicoSDK

## Funcionalidades

1. **Leitura Analógica**: Utiliza o ADC de 12 bits para ler a posição do joystick
2. **Controle PWM**: Gera sinais PWM de 25kHz para controle suave da intensidade
3. **Mapeamento**: Converte valores do ADC (0-4095) para intensidade (0-100%)
4. **Zona Morta**: Implementa zona morta para evitar drift do joystick
5. **Ligar/Desligar**: Botão para controlar o estado do LED
6. **Debug**: Saída serial para monitoramento dos valores

## Conexões

| Componente | Pino Pico | Função |
|------------|-----------|--------|
| LED RGB | GP13 | PWM (controle de intensidade) |
| Joystick X | GP26 | ADC0 (eixo horizontal) |
| Joystick Y | GP27 | ADC1 (reservado) |
| Botão SEL | GP22 | Entrada digital (ligar/desligar) |

## Compilação e Upload

```bash
# Criar diretório de build
mkdir build
cd build

# Configurar CMake
cmake ..

# Compilar
make

# Upload para o Pico (via drag & drop do arquivo .uf2)
```

## Uso

1. Conecte o LED RGB ao pino GP13
2. Conecte o joystick ao pino GP26 (eixo X)
3. Conecte o botão ao pino GP22
4. Alimente o sistema
5. Use o joystick para controlar a intensidade do LED
6. Pressione o botão para ligar/desligar o LED

## Especificações Técnicas

- **Frequência PWM**: 25kHz (sem piscamento visível)
- **Resolução PWM**: 16 bits (0-65535)
- **Intensidade**: 0-100%
- **Resolução ADC**: 12 bits (0-4095)
- **Taxa de Atualização**: 20Hz
- **Zona Morta**: ±100 unidades ADC

## Autor

Caio Nunes - 2024
