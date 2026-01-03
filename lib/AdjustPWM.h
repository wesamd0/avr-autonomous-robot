/*
 * Nom:AdjustPWM.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#ifndef ADJUSTPWM_H
#define ADJUSTPWM_H

#define F_CPU 8000000
#pragma once
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

class AdjustPWM {
public:
    AdjustPWM();
    void adjustPwmForward(uint8_t percentageD, uint8_t percentageG);
    void adjustPwmBackward(uint8_t percentageD, uint8_t percentageG);
    void stopPwm();
    void spinRight(uint8_t percentageD, uint8_t percentageG);
    void spinLeft(uint8_t percentageD, uint8_t percentageG);
    void adjustCTC2(uint16_t freq);
    void adjustCTC3(uint16_t freq);

    uint8_t speedPercentage;
    bool isForward;
};

#endif // ADJUSTPWM_H