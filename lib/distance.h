/*
 * Nom:distance.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 30 mars 2024
*/

#ifndef DISTANCE_H
#define DISTANCE_H

#define F_CPU 8000000
#pragma once
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <robot1.h>

const uint16_t TURN_DELAY = 1500;
const uint16_t TURN_DELAY_180 = 100;
const uint16_t CENTER_ADJUST_DELAY = 600;
const uint16_t START_MOTOR_DELAY = 100;
const uint16_t WAIT_DELAY = 2000;
const uint16_t ADVANCE_DELAY = 1000;
const uint8_t ADVANCE_SPEED_PERCENTAGE = 50;
const uint8_t ADVANCE_SPEED_PERCENTAGE_RIGHT = 45;
const uint8_t ADVANCE_SPEED_PERCENTAGE_LEFT = 46;
const uint8_t ADVANCE_SPEED_PERCENTAGE_MAX = 100;
const uint8_t DESIRED_DISTANCE = 45; // 26 cm
const uint8_t DOT_TO_WALL_DISTANCE_MIN =  42; // 30 cm
const uint8_t DOT_TO_WALL_DISTANCE_MAX =  30; // 45 cm

class Centralize {
public:
    bool donedebut = 0;
    bool donefin = 0;
    
    void turnRightForward();
    void turnLeftForward();
    void turnRightBackward();
    void turnLeftBackward();
    void do180();
    void readDistance();
    void centralizeRobot();

    //ascii
    void getPositionData(char* tab);

private:
    Robot1 robot;
    uint8_t distance;

    //ascii
    uint8_t initialDistance;
    bool isInFrontOfWall = false;
    bool isAboveCenter = false;
};

#endif // DISTANCE_H