/*
 * Nom:AdjustPWM.cpp
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#include "AdjustPWM.h"

const uint8_t MAX_8_BITS = 255;

AdjustPWM::AdjustPWM() {

}

void AdjustPWM::adjustPwmForward(uint8_t percentageD, uint8_t percentageG) {
    DDRB |= (1<<DDB3) | (1<<DDB4) | (1 << DDB2) | (1 << DDB5) ; // Configure les pins PB3 et PB4 en sortie (OC0A et OC0B respectivement)
    PORTB &= ~(1 << PB2);
    PORTB &= ~(1 << PB5);
    TCCR0A |= (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1); // PWM sur 8 bits et activer PWM sur OC0A et OC0B.
    TCCR0B |= (1 << CS01);                                  // prescaler = 8 pour timer0.

    OCR0A = (percentageD * MAX_8_BITS) / 100; // ajuster cycle PWM pour OC0A.
    OCR0B = (percentageG * MAX_8_BITS) / 100; // ajuster cycle PWM pour OC0B.
    speedPercentage = percentageD;
    isForward = true;
}

void AdjustPWM::stopPwm() {
    DDRB &= ~((1 << DDB3) | (1 <<DDB4) | (1 << DDB5) | (1 << DDB2)); // Configure les pins PB2, PB3, PB4 et PB5 en sortie (OC0A et OC0B respectivement)
    PORTB &= ~(1 << PB2);
    PORTB &= ~(1 << PB5);

    
    TCCR0A |= (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1); // PWM sur 8 bits et activer PWM sur OC0A et OC0B.
    TCCR0B |= (1 << CS01);                                  // prescaler = 8 pour timer0.

    OCR0A = 0;
    OCR0B = 0;
}

void AdjustPWM::spinRight(uint8_t percentageD, uint8_t percentageG) {
    DDRB |= ((1 << DDB2 ) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5)); // Configure les pins PB2, PB3, PB4 et PD5 en sortie (OC0A et OC0B respectivement)
    PORTB |= (1 << PB5);
    PORTB &= ~(1 << PB2);
    TCCR0A |= (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1); // PWM sur 8 bits et activer PWM sur OC0A et OC0B.
    TCCR0B |= (1 << CS01);                                  // prescaler = 8 pour timer0.
    
    OCR0A = (percentageD * MAX_8_BITS) / 100; // ajuster cycle PWM pour OC0A.
    OCR0B = (percentageG * MAX_8_BITS) / 100; // ajuster cycle PWM pour OC0B.
    speedPercentage = percentageD;
    isForward = false;
}

void AdjustPWM::spinLeft(uint8_t percentageD, uint8_t percentageG) {
    DDRB |= ((1 << DDB2 ) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5)); // Configure les pins PB2, PB3, PB4 et PD5 en sortie (OC0A et OC0B respectivement)
    PORTB |= (1 << PB2);
    PORTB &= ~(1 << PB5);
    TCCR0A |= (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1); // PWM sur 8 bits et activer PWM sur OC0A et OC0B.
    TCCR0B |= (1 << CS01);                                  // prescaler = 8 pour timer0.
    
    OCR0A = (percentageD * MAX_8_BITS) / 100; // ajuster cycle PWM pour OC0A.
    OCR0B = (percentageG * MAX_8_BITS) / 100; // ajuster cycle PWM pour OC0B.
    speedPercentage = percentageD;
    isForward = false;
}



void AdjustPWM::adjustPwmBackward(uint8_t percentageD, uint8_t percentageG) {
    DDRB |= ((1 << DDB2 ) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5)); // Configure les pins PB2, PB3, PB4 et PD5 en sortie (OC0A et OC0B respectivement)
    PORTB |= (1 << PB2);
    PORTB |= (1 << PB5);
    TCCR0A |= (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1); // PWM sur 8 bits et activer PWM sur OC0A et OC0B.
    TCCR0B |= (1 << CS01);                                  // prescaler = 8 pour timer0.
    
    OCR0A = (percentageD * MAX_8_BITS) / 100; // ajuster cycle PWM pour OC0A.
    OCR0B = (percentageG * MAX_8_BITS) / 100; // ajuster cycle PWM pour OC0B.
    speedPercentage = percentageD;
    isForward = false;
}

void AdjustPWM::adjustCTC2(uint16_t freq) {
    DDRD= ((1 << DDD5) | (1<< DDD4));  
    TCCR1A |= (1<< COM1A0);  
    
    TCCR1B |= (1 << CS11) | (1 << CS10);
    TCCR1B |= (1 << WGM12);
    uint16_t range =  2*64*freq/1000; //faut declarer des constants
    uint16_t cpu = 8000;
    OCR1A = (cpu/(range))-1;
}

void AdjustPWM::adjustCTC3(uint16_t freq) {
    DDRC &= (0 << DDC4);
    TCNT2 = 0;
    DDRD |= ((1 << DDD6) | (1<< DDD7));  
    TCCR2A = 0;
    TCCR2B = 0;
    TCCR2A |= (1 << COM2A0);
    TCCR2A |= (1 << COM2B0);

    // Set Timer/Counter2 to CTC Mode (WGM21 = 1, WGM20 = 0)
    TCCR2B |= (1 << WGM22);

    // Choose an appropriate prescaler:
    // Here, prescaler is set to 8 for this example (CS21 = 1)
    TCCR2B |= (1 << CS20);
    uint16_t range =  (2*freq/1000); //faut declarer des constants
    uint16_t cpu = 8000;
    OCR2A = 0;//(cpu/(range))-1;
}


