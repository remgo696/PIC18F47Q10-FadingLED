#include <xc.h>
#include "config.h"

void configure(void) {
    /* --------------------------------- *
     * Oscillator module: HFINTOSC 2 MHz *
     * --------------------------------- */
    OSCCON1 = 0x60;     // NOSC = HFINTOSC (110), NDIV = 1:1 (0000)
    OSCFRQ  = 0x01;     // FRQ = 2 MHz
    OSCEN   = 0x40;     // Habilitar HFINTOSC

    /* --------------------------------- *
     * I/O: RC0 como salida digital      *
     * --------------------------------- */
    ANSELCbits.ANSELC0 = 0;    // RC0 digital
    TRISCbits.TRISC0   = 0;    // RC0 como salida

    /* --------------------------------- *
     * PPS: CCP1 → RC0                   *
     * --------------------------------- */
    RC0PPS = 0x05;              // Dirigir salida CCP1 a RC0

    /* --------------------------------- *
     * CCP1 (PWM) + TMR2: periodo 400 µs *
     * --------------------------------- */
    CCPTMRSbits.C1TSEL = 1;    // CCP1 usa TMR2
    T2PR    = 199;              // Periodo PWM = 400 µs (2,5 kHz)
    CCP1CON = 0x9C;             // EN=1, FMT=1 (izquierda), MODE=1100 (PWM)
    CCPR1H  = 0x00;
    CCPR1L  = 0x00;             // Duty cycle inicial = 0 %
    T2CLKCON = 0x01;            // Fuente de reloj TMR2 = Fosc/4
    T2CON    = 0x80;            // TMR2 ON, prescaler 1:1

    /* --------------------------------- *
     * TMR0: interrupción a ≈ 120 Hz     *
     * --------------------------------- */
    T0CON0 = 0x80;              // TMR0 ON, 8-bit, postscaler 1:1
    T0CON1 = 0x45;              // Fosc/4, síncrono, prescaler 1:32
    TMR0H  = 129;               // Cuenta 0→129 (130 cuentas) → 120,19 Hz

    /* --------------------------------- *
     * Interrupciones                    *
     * --------------------------------- */
    PIR0bits.TMR0IF = 0;        // Limpiar bandera TMR0
    PIE0bits.TMR0IE = 1;        // Habilitar interrupción TMR0
    INTCONbits.GIE  = 1;        // Habilitar interrupciones globales
}