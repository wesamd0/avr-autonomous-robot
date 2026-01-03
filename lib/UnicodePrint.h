/*
 * Nom:UnicodePRint.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 17 avril 2024
*/

#ifndef UNICODEPRINT_H
#define UNICODEPRINT_H

#pragma once
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <CommunicationUART.h>
#include <memoire_24.h>

const uint16_t tableauAddBegin = 0x0101;
const uint16_t tableauElements = 3719;

class Dessin
{

public:
    
    void printAll(uint8_t totallines, uint8_t upperlines, uint8_t relativeD1, uint8_t relativeL1, uint8_t relativeD2, uint8_t relativeL2, uint8_t relativeD3, uint8_t relativeL3, uint8_t relativeD4, uint8_t relativeL4, uint8_t relativeD5, uint8_t relativeL5, uint8_t relativeD6, uint8_t relativeL6, bool orientation, uint8_t distancefromtop); 
    uint16_t ligneduHaut;
    uint16_t ligneduBas;
    uint16_t colonneR1;
};

#endif // SONO_H