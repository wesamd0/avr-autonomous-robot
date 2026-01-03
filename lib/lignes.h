#ifndef LIGNES_H
#define LIGNES_H


/*
 * Nom:Lignes.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 29 mars 2024
*/

#define F_CPU 8000000
#pragma once
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <PositionsLigne.h>
#include <robot2.h>

class Line {
public:
    Line();
    bool readLineSensors(const uint8_t sensorPin);
    Positions getAlignment();
    void followLine();
    void turnRight();
    void turnLeft();
    void do180();
    void goBackwards();
    void setDataLigne(uint8_t slot, uint8_t data);
    uint8_t getDataLigne(uint8_t slot);
    
    //void recenter();
    
private:

    // Definir les constantes pour les broches des sorties du capteurs de ligne.
    static const uint8_t OUTPUT_S1 = PA2;
    static const uint8_t OUTPUT_S2 = PA3;
    static const uint8_t OUTPUT_S3 = PA4;
    static const uint8_t OUTPUT_S4 = PA5;
    static const uint8_t OUTPUT_S5 = PA6;

    static const uint16_t TURN_PERCENTAGE = 50;
    static const uint16_t speedPercentage = 35;
    static const uint16_t TURN_DELAY = 1800;
    static const uint16_t WAIT_DELAY = 1500;

    
    bool isEndTrip = false;
    //volatile bool shouldTurnRight = false;

    
    Robot2 robot;
    AdjustPWM motor;
    //uint8_t linesCrossed = 0;
    
};

#endif // LIGNES_H