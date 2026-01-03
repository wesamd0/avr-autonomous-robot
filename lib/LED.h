/*
 * Nom:LED.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#ifndef LED_H
#define LED_H

#define F_CPU 8000000
#pragma once
#include <util/delay.h>
#include <stdint.h>

typedef volatile uint8_t *Register;

class Led
{
public:
    Led(Register mode, Register port, uint8_t pinGreen, uint8_t pinRed);

    void setGreen();
    void setRed();
    void setAmber();
    void setOff();

private:
    Register port_;
    const uint8_t pinGreenPosition_;
    const uint8_t pinRedPosition_;

    static constexpr uint8_t DELAY_AMBER = 5;

};

#endif // LED_H
