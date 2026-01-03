/*
 * Nom:infrarouge.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 25 mars 2024
*/

#ifndef INFRA_H
#define INFRA_H

#define F_CPU 8000000
#pragma once
#include <stdio.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <memoire_24.h>
#include <CommunicationUART.h>
#include <avr/crc16.h>

class Infrarouge: public Memoire24CXXX, public UART {
public:


    void init(bool mode);
    bool recevoir();
    void envoyerChar(uint8_t data);
    void envoyerBit(bool bit);
    void eteindreIR();
    void signalerDepart();
    uint8_t creerCRC16(uint8_t data[12]);
    void envoyerArray(uint8_t data[12]);
    

private:
    UART uart;
    Memoire24CXXX mem = Memoire24CXXX();
    static const uint8_t TRANSMITPORT = PC4;
    static const uint16_t ONEDELAYUS = 1200;
    static const uint16_t ZERODELAYUS = 600;
    static const uint16_t BUFFERDELAYUS = 600;
    static const uint16_t STARTDELAYUS = 2400;
    static const uint8_t INPUT = (1<<PC4);
    static const uint16_t SIRCVALUE = 100;
    static const uint8_t STOPBIT = 0x63;
    
};


#endif // INFRA_H