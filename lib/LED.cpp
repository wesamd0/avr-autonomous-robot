/*
 * Nom:LED.cpp
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/


#include "LED.h"

Led::Led(Register mode, Register port, uint8_t pinGreen, uint8_t pinRed) : port_(port),
                                                                           pinGreenPosition_(pinGreen),
                                                                           pinRedPosition_(pinRed)


{
    *mode |= (1 << pinGreenPosition_) | (1 << pinRedPosition_);
    
}

void Led::setGreen()
{
    *port_ &= ~(1 << pinRedPosition_);
    *port_ |= (1 << pinGreenPosition_);
}

void Led::setRed()
{
    *port_ &= ~(1 << pinGreenPosition_);
    *port_ |= (1 << pinRedPosition_);
}

void Led::setOff()
{
    *port_ &= ~(1 << pinRedPosition_);
    *port_ &= ~(1 << pinGreenPosition_);
}

void Led::setAmber()
{
    setRed();
    _delay_ms(DELAY_AMBER);
    setGreen();
    _delay_ms(DELAY_AMBER);
}
