# 🌡️ Sistema de Monitoramento de Solo (UFPA)

Este projeto foi desenvolvido como trabalho académico para a **UFPA (Universidade Federal do Pará)**. Consiste num sistema embarcado para medir e monitorar a temperatura e a humidade do solo utilizando o microcontrolador **PIC16F877A**.

## 🚀 Funcionalidades

- **Interface LCD:** Menu interativo para operação em campo.
- **Configuração via Teclado:** Ajuste de intervalos de medição (em minutos) e número de amostras sem alterar o código.
- **Persistência de Dados:** Armazenamento de cada leitura na memória **EEPROM** interna.
- **Notificação:** Alarme sonoro (Buzzer) ao concluir o ciclo de medições.

## 🛠️ Tecnologias e Ferramentas

- **Microcontrolador:** PIC16F877A.
- **Linguagem:** C.
- **Compilador:** CCS C Compiler (PCWHD).
- **Simulação:** Proteus 9
- **Hardware:** LCD 16x2, Teclado Matricial, Sensores e Buzzer.


## 🔧 Como Executar

1. **Compilação:**
   - Abra o arquivo .hex` utilizando o **CCS C Compiler**.
   - Compile (Build) para gerar o ficheiro `.hex`.

2. **Simulação:**
   - Abra o arquivo temp-humidade '.pdsprj' com o **Proteus**.
   - Carregue o ficheiro `.hex` gerado no componente PIC16F877A.
   - Inicie a simulação para interagir com o menu.
   - Certifique-se que esteja na versão correta do Proteus 9

## 📝 Operação

1. Ligue o sistema para ver o **Menu Inicial** no LCD.
2. Configure o intervalo e o número de medições desejados.
3. Inicie o processo; o sistema salvará os dados e soará o alarme ao terminar.

   ## 💡 Aplicações Práticas

Este sistema foi projetado com um foco versátil, podendo ser adaptado para diversas frentes reais, como:

1. **Agricultura de Precisão:** Monitoramento de canteiros experimentais ou hortas comunitárias em São Francisco do Pará, otimizando o uso de água através do controle exato da umidade.
2. **Estufas Automatizadas:** Base para sistemas de irrigação inteligente, onde a coleta de dados na EEPROM permite analisar o comportamento térmico do solo ao longo do dia.
3. **Educação Científica:** Ferramenta didática para o ensino de microcontroladores e lógica de programação em cursos técnicos e de graduação.
4. **Pesquisa Acadêmica (UFPA):** Coleta de dados ambientais para estudos sobre o impacto do clima local na temperatura do solo em diferentes coberturas vegetais.

---
**Desenvolvido como projeto didático - UFPA**
Desenvolvido por : João Victor Leitão, Anthony Saraiva, Moisés Costa, Rafael Silva
