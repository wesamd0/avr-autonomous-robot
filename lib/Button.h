/*
 * Nom:Button.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#ifndef BUTTON_H
#define BUTTON_H

#define F_CPU 8000000
#pragma once
#include<stdio.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const uint8_t DEBOUNCE_DELAY = 30;
const uint8_t MASK_D2 = (1 << PIND2); 
const uint8_t MASK_D3 = (1 << PIND3); 
class Button {
public:
    Button();
    void intialize();
    bool isButtonPressed();

    static bool buttonPressed;
};

#endif // BUTTON_H