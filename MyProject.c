/*
 * PIC16F877A - mikroC PRO for PIC
 * LCD 16x2 (4-bit) + Keypad 4x4 + ADC (AN0/AN1) + EEPROM + Buzzer (RC0)
 *
 * LCD:
 *   RS -> RB0
 *   EN -> RB1
 *   D4 -> RB4
 *   D5 -> RB5
 *   D6 -> RB6
 *   D7 -> RB7
 *
 * Keypad 4x4: PORTD (biblioteca Keypad4x4 do mikroC)
 *
 * Sensores:
 *   AN0 = LM35 (temperatura)
 *   AN1 = Umidade (pot/sensor analógico)
 *
 * Buzzer:
 *   RC0
 */

#define BUZZER        PORTC.F0
#define BUZZER_TRIS   TRISC.F0

// ---------- LCD PINOUT (microC LCD library) ----------
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB1_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;

// ---------- KEYPAD PORT SETUP ----------
char keypadPort at PORTD;

// ---------- VARIÁVEIS ----------
unsigned short intervalo_min = 1;     // 1..9 min (simples)
unsigned short num_medicoes  = 1;     // 1..9
unsigned short cont_medicoes = 0;
unsigned short eeprom_addr   = 0;

char txt[17];

// ---------- FUNÇÕES ÚTEIS ----------
unsigned short clamp_1_9(unsigned short v) {
  if(v < 1) return 1;
  if(v > 9) return 9;
  return v;
}

void beep_ms(unsigned int ms) {
  BUZZER = 1;
  VDelay_ms(ms);
  BUZZER = 0;
}

void alarme_final() {
  // 3 beeps curtos
  beep_ms(250); Delay_ms(150);
  beep_ms(250); Delay_ms(150);
  beep_ms(250);
}

void wait_1s_x(unsigned short s) {
  while(s--) Delay_ms(1000);
}

void delay_minutos(unsigned short min) {
  unsigned short i;
  min = clamp_1_9(min);
  for(i=0; i<min; i++){
    // 60s
    wait_1s_x(60);
  }
}

// ---------- TECLADO ----------
/*
  Keypad_Key_Click() retorna 1..16
  Mapa padrão mikroC 4x4:
    1  2  3  4
    5  6  7  8
    9 10 11 12
   13 14 15 16

  Vamos mapear para:
    1 2 3 A
    4 5 6 B
    7 8 9 C
    * 0 # D
*/
char ler_tecla_char() {
  char k;
  do {
    k = Keypad_Key_Click();
  } while(!k);

  switch(k) {
    case  1: return '1';
    case  2: return '2';
    case  3: return '3';
    case  4: return 'A';
    case  5: return '4';
    case  6: return '5';
    case  7: return '6';
    case  8: return 'B';
    case  9: return '7';
    case 10: return '8';
    case 11: return '9';
    case 12: return 'C';
    case 13: return '*';
    case 14: return '0';
    case 15: return '#';
    case 16: return 'D';
  }
  return 0;
}

// lê 1 dígito 1..9 (pra intervalo e nº medições)
unsigned short ler_num_1_9() {
  char c;
  do {
    c = ler_tecla_char();
  } while(c < '1' || c > '9');
  return (unsigned short)(c - '0');
}

// ---------- ADC ----------
unsigned int read_adc(unsigned short canal) {
  // ADC_Read retorna 0..1023
  return ADC_Read(canal);
}

/*
  Para exibir simples:
  - temp_adc: (0..1023) -> só mostra "bruto" ou uma aproximação
  Se quiser aproximar LM35:
    tensão = adc*5/1023
    tempC ˜ tensão / 0.01 = adc*500/1023
*/
unsigned int lm35_to_c(unsigned int adc) {
  // tempC ˜ adc * 500 / 1023
  return (adc * 500UL) / 1023UL;
}

// Umidade fictícia em % (0..100) a partir do ADC
unsigned int adc_to_percent(unsigned int adc) {
  return (adc * 100UL) / 1023UL;
}

// ---------- EEPROM ----------
void salvar_eeprom_byte(unsigned short addr, unsigned short value0_255) {
  if(value0_255 > 255) value0_255 = 255;
  EEPROM_Write(addr, (unsigned char)value0_255);
  Delay_ms(10); // tempo de escrita
}

// ---------- UI ----------
void mostrar_menu() {
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Out(1,1,"1-Iniciar");
  Lcd_Out(2,1,"2-Int 3-Num");
}

void mostrar_intervalo() {
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Out(1,1,"Intervalo(min)");
  Lcd_Out(2,1,"Digite 1..9:");
}

void mostrar_num_med() {
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Out(1,1,"N Medicoes");
  Lcd_Out(2,1,"Digite 1..9:");
}

void mostrar_medicao(unsigned int temp_c, unsigned int hum_pct) {
  Lcd_Cmd(_LCD_CLEAR);

  // Linha 1: T:xxC
  Lcd_Out(1,1,"T:");
  WordToStr(temp_c, txt);      // "  25"
  Ltrim(txt);
  Lcd_Out(1,3,txt);
  Lcd_Out(1,3 + strlen(txt), "C");

  // Linha 2: H:xx%
  Lcd_Out(2,1,"H:");
  WordToStr(hum_pct, txt);
  Ltrim(txt);
  Lcd_Out(2,3,txt);
  Lcd_Out(2,3 + strlen(txt), "%");
}

// ---------- MAIN ----------
void main() {
  // I/O
  TRISA = 0xFF;   // AN0/AN1 entradas
  TRISB = 0x00;   // LCD
  TRISC = 0x00;   // buzzer etc
  TRISD = 0xF0;   // keypad: RD0..RD3 saídas, RD4..RD7 entradas (padrão)

  // Buzzer
  BUZZER_TRIS = 0;
  BUZZER = 0;

  // Inicializações libs
  ADC_Init();
  Keypad_Init();
  Lcd_Init();
  Lcd_Cmd(_LCD_CURSOR_OFF);
  Lcd_Cmd(_LCD_CLEAR);

  while(1) {
    char key;

    mostrar_menu();
    key = ler_tecla_char();

    // Configurar intervalo
    if(key == '2') {
      mostrar_intervalo();
      intervalo_min = ler_num_1_9();
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Out(1,1,"Intervalo = ");
      ByteToStr(intervalo_min, txt);
      Ltrim(txt);
      Lcd_Out(1,12,txt);
      Lcd_Out(2,1,"OK");
      Delay_ms(800);
    }

    // Configurar num medicoes
    if(key == '3') {
      mostrar_num_med();
      num_medicoes = ler_num_1_9();
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Out(1,1,"N Med = ");
      ByteToStr(num_medicoes, txt);
      Ltrim(txt);
      Lcd_Out(1,9,txt);
      Lcd_Out(2,1,"OK");
      Delay_ms(800);
    }

    // Iniciar
    if(key == '1') {
      cont_medicoes = 0;
      eeprom_addr = 0;

      while(cont_medicoes < num_medicoes) {
        unsigned int adc_temp = read_adc(0);  // AN0
        unsigned int adc_hum  = read_adc(1);  // AN1

        unsigned int temp_c   = lm35_to_c(adc_temp);
        unsigned int hum_pct  = adc_to_percent(adc_hum);

        // Salva 1 byte cada (0..255)
        salvar_eeprom_byte(eeprom_addr++, temp_c);
        salvar_eeprom_byte(eeprom_addr++, hum_pct);

        mostrar_medicao(temp_c, hum_pct);

        cont_medicoes++;

        if(cont_medicoes < num_medicoes) {
          Lcd_Out(2,11,"Aguarde");
          delay_minutos(intervalo_min);
        }
      }

      alarme_final();
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Out(1,1,"Finalizado");
      Lcd_Out(2,1,"(Simulacao)");
      while(1) { } // para aqui (no real daria SLEEP)
    }
  }
}
