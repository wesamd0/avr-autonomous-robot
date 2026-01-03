/*
 * Nom:Timer.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#ifndef TIMER_H
#define TIMER_H

#define F_CPU 8000000
#pragma once
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>


class Timer {
public:
    Timer();
    void intialize();
    void startTimer(uint16_t duration);
    bool isTimerExpired();

    static bool timerExpired;
};

#endif // TIMER_H