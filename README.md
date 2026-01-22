# 🌡️ Sistema de Monitoramento de Solo (PIC16F877A)

Este projeto consiste em um sistema embarcado desenvolvido para medir e monitorar a temperatura e a umidade do solo. O sistema utiliza um microcontrolador PIC16F877A, uma interface de menu via LCD e um teclado para configuração de parâmetros.

## 🚀 Funcionalidades

- **Menu Interativo:** Interface intuitiva via LCD 16x2.
- **Configuração Personalizada:** Permite definir o intervalo entre as medições (em minutos) e o número total de amostras através de um teclado.
- **Armazenamento:** Cada medição é salva em uma posição de memória (EEPROM) para consulta posterior.
- **Alarme e Segurança:** Emite um sinal sonoro (Buzzer) ao finalizar o ciclo de medições e desliga automaticamente o processo.

## 🛠️ Hardware Utilizado

- **Microcontrolador:** Microchip PIC16F877A
- **Display:** LCD 16x2 (via interface 4-bits ou I2C)
- **Entrada:** Teclado Matricial 4x4
- **Sensores:** Sensor de Temperatura e Umidade (Simulado)
- **Saída de Áudio:** Buzzer Ativo
- **Software de Simulação:** Proteus 8.x
- **Compilador:** MPLAB XC8

## 📂 Estrutura do Repositório

- `/src`: Contém todo o código-fonte em C.
- `/simulation`: Arquivos do projeto Proteus (.pdsprj).
- `/assets`: Imagens do circuito e fluxogramas.

## 🔧 Como Replicar o Projeto

1. **Compilação:**
   - Abra os arquivos da pasta `/src` no **MPLAB X IDE**.
   - Certifique-se de que o compilador **XC8** está instalado.
   - Compile para gerar o arquivo `.hex`.

2. **Simulação:**
   - Abra o arquivo na pasta `/simulation` usando o **Proteus**.
   - Clique duas vezes no PIC16F877A e carregue o arquivo `.hex` gerado.
   - Inicie a simulação.

## 📝 Operação do Sistema

1. Ao ligar, o **Menu Inicial** aparecerá no LCD.
2. Use o teclado para navegar pelas opções:
   - **Iniciar:** Começa a coleta de dados com as configurações atuais.
   - **Ajustar Intervalo:** Define o tempo entre coletas.
   - **Nº de Medições:** Define quantas vezes o sensor será lido antes de parar.
3. O sistema soará o alarme ao término de todas as medições programadas.

---
Desenvolvido por João Victor Leitão, Anthony Saraiva, Moisés Costa e Rafael Silva
