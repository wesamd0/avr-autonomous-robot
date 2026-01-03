/*
 * Nom:Button.cpp
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#include "Button.h"

bool Button::buttonPressed = false;

Button::Button() {

}

void Button::intialize() {
    cli();
    DDRD &= ~((1 << DDD2) | (1 << DDD3));
    Button::buttonPressed = false;
    EIMSK |= ((1 << INT0) | (1 << INT1));
    EICRA |= (1 << ISC00);
    EICRA |= (1 << ISC01);
    //EICRA |= (0 << ISC10); //ajouter pour PD3
    EICRA |= (1 << ISC11); // ajouter pour PD3
    sei();
}

bool Button::isButtonPressed() {
    
    if (Button::buttonPressed == 1) {
        return true;
    }
    else {
        return false;
    }
}

