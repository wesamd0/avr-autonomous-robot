/*
 * Nom:CommunicationUART.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#ifndef UART_H
#define UART_H

#define F_CPU 8000000
#pragma once
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>



class UART  {
public:
    UART();
    static void intializeUART();
    static void transmitUART(uint8_t data);
    static unsigned char recieveUART();
    
   
};

#endif // UART_H
