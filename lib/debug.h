/*
 * Nom:debug.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#ifndef DEBUG_H
#define DEBUG_H
#define F_CPU 8000000
#pragma once
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "CommunicationUART.h"



class Debug : public UART
{
public:

    Debug();
    template<typename Enum> void obtenirEtatEnum(Enum var);
    void obtenirBool(bool var);

    
};


//Transmet l'index de l'état selon son index dans l'énumeration
template<typename Enum>
void Debug::obtenirEtatEnum(Enum var) {
int data = static_cast<int>(var);
char texte = data + 48;
char message[7] = "Etat: ";

intializeUART();
for(int i = 0; i < 7; i++){
    transmitUART ( message[i] );
};
transmitUART(texte);
// transmitUART("\n"); // MARCHE PAS ATM error: cannot convert 'const char [2]' to 'uint8_t' {aka 'unsigned char'}
}



#endif // DEBUG_H