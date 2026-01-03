/*
 * Nom:sono.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#ifndef SONO_H
#define SONO_H

#define F_CPU 8000000
#pragma once
#include<stdio.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <AdjustPWM.h>


class Sono {
public:
    Sono();
    void startPiazo(uint8_t note);
    void stopPiezo();
    

    
};

#endif // SONO_H