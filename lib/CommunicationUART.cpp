/*
 * Nom:CommunicationUART.cpp
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#include "CommunicationUART.h"


UART::UART() {

}

void UART::intializeUART() {

    // 2400 bauds. Nous vous donnons la valeur des deux
    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;
    UBRR0L = 0xCF;

    // Permettre la réception et la transmission par le UART0

    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

    // Format des trames: 8 bits (UCSZ01 et UCSZ00 à 1), 1 stop bits (USBS0 = 0) et sans parité (UPM00 et UPM01 à 0)

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
    
}

void UART::transmitUART(uint8_t data) {

    // Copy pasted from p.174 of the ATmega documentation
    /* Wait for empty transmit buffer */

    while (!(UCSR0A & (1 << UDRE0))) // UDRE0 = 1 quand le buffer est vide et qu'on peut écrire dans UDR0
        ;

    UDR0 = data; // On écrit dans UDR0 pour transmettre l'octet
}

unsigned char UART::recieveUART() {
    
    while (!(UCSR0A & (1 <<RXC0) ) )
        ;

    return UDR0;
}

