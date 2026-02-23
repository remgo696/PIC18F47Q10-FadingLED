#include <xc.h>
#include "main.h"
#include "config.h"

#define DUTY_CYCLE_MAX   100
#define DUTY_CYCLE_MIN   0
#define CCPR1H_STEP      2      // 1 % duty cycle → sumar/restar 2 a CCPR1H (FMT=1)

unsigned char duty_cycle = 0;
__bit b_subiendo;               // 1 = encendiendo, 0 = apagando

void main(void) {
    b_subiendo = 1;
    configure();

    while (1) {
        // Toda la lógica del fading se ejecuta en la ISR de TMR0
    }
}

void __interrupt() TMR0_ISR(void) {
    if (PIR0bits.TMR0IF) {
        PIR0bits.TMR0IF = 0;

        if (b_subiendo) {
            if (duty_cycle < DUTY_CYCLE_MAX) {
                duty_cycle++;
                CCPR1H += CCPR1H_STEP;
            } else {
                b_subiendo = 0;
            }
        } else {
            if (duty_cycle > DUTY_CYCLE_MIN) {
                duty_cycle--;
                CCPR1H -= CCPR1H_STEP;
            } else {
                b_subiendo = 1;
            }
        }
    }
}
