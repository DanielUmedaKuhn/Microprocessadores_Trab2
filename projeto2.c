// Definir a frequência do oscilador
#define _XTAL_FREQ 8000000

volatile unsigned int delay_time = 1000;

// Configurações específicas para o PIC18F4550 no MikroC
void setup() {
    TRISB = 0x03; // Configura RB0 e RB1 como entradas (botões)
    TRISD = 0x00; // Configura a porta D como saída (display de 7 segmentos)
    PORTD = 0x00; // Limpa a porta D

    // Configurações de Interrupção
    GIE_bit = 1;      // Ativa interrupções globais
    PEIE_bit = 1;     // Ativa interrupções periféricas
    INT0IE_bit = 1;   // Ativa interrupção externa em RB0
    INT1IE_bit = 1;   // Ativa interrupção externa em RB1
    INTEDG0_bit = 1;  // Interrupção na borda de subida para RB0
    INTEDG1_bit = 1;  // Interrupção na borda de subida para RB1
}

// Função para exibir número no display de 7 segmentos
void mostrar_no_display(unsigned char num) {
    switch (num) {
        case 0: PORTD = 0b00111111; break; // 0
        case 1: PORTD = 0b00000110; break; // 1
        case 2: PORTD = 0b01011011; break; // 2
        case 3: PORTD = 0b01001111; break; // 3
        case 4: PORTD = 0b01100110; break; // 4
        case 5: PORTD = 0b01101101; break; // 5
        case 6: PORTD = 0b01111101; break; // 6
        case 7: PORTD = 0b00000111; break; // 7
        case 8: PORTD = 0b01111111; break; // 8
        case 9: PORTD = 0b01101111; break; // 9
        default: PORTD = 0b00000000; // Apaga o display
    }
}

// Interrupções para os botões
void interrupt() {
    if (INT0IF_bit) { // Botão em RB0 pressionado
        delay_time = 1000; // Configura delay de 1s
        INT0IF_bit = 0; // Limpa flag de interrupção
    }
    if (INT1IF_bit) { // Botão em RB1 pressionado
        delay_time = 250; // Configura delay de 0,25s
        INT1IF_bit = 0; // Limpa flag de interrupção
    }
}

void main() {
    unsigned char contador = 0; // Variável do contador para o display

    setup();

    while (1) {
        mostrar_no_display(contador); // Exibe o contador no display
        if(delay_time == 1000){
             Delay_ms(1000);         // Delay de 1s
        }
        else if(delay_time == 250){
             Delay_ms(250);           // Delay de 0,25s
        }
        contador = (contador + 1) % 10; // Incrementa o contador de 0 a 9
    }
}
