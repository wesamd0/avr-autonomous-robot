/*
 * Nom:Timer.cpp
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#include "Timer.h"

const uint16_t prescaler = 1024;

bool Timer::timerExpired = false;

Timer::Timer() {

}

void Timer::intialize() {
    cli();

    OCR1A = 15624; // Valeur pour obtenir une interruption après 1 seconde
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // Mode CTC, prescaler 1024
    TIMSK1 = (1 << OCIE1A);                            // Activer l'interruption de comparaison

    sei();
}

void Timer::startTimer(uint16_t duration) {
    Timer::timerExpired = 0;
    TCNT1 = 0; // Réinitialiser le compteur de la minuterie
    OCR1A = duration;//(F_CPU / prescaler) * duration; 
}

bool Timer::isTimerExpired() {
    if (Timer::timerExpired == 1) {
        return true;
    } else {
        return false;
    }
}