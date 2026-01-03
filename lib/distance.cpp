/*
 * Nom:distance.cpp
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 30 mars 2024
*/

#include "distance.h"



void Centralize::turnRightForward() {
    robot.motor.adjustPwmForward(0 , ADVANCE_SPEED_PERCENTAGE);
    _delay_ms(1600);
    robot.motor.stopPwm();
}

void Centralize::turnRightBackward() {
    robot.motor.adjustPwmBackward(ADVANCE_SPEED_PERCENTAGE, 0);
    _delay_ms(2500);
    robot.motor.stopPwm();
}

void Centralize::turnLeftForward() {
    robot.motor.adjustPwmForward(ADVANCE_SPEED_PERCENTAGE, 0);
    _delay_ms(1800);
    robot.motor.stopPwm();
}

void Centralize::turnLeftBackward() {
    for (int i = 0; i < 9; ++i) {
        robot.motor.adjustPwmBackward(0, 100);
        _delay_ms(30);
        robot.motor.adjustPwmBackward(0, 45);
        _delay_ms(300);
        robot.motor.stopPwm();
        _delay_ms(1000);
    }
}
 
void Centralize::do180() {
    robot.motor.spinRight(ADVANCE_SPEED_PERCENTAGE_MAX, ADVANCE_SPEED_PERCENTAGE_MAX);
    _delay_ms(30);
    robot.motor.spinRight(ADVANCE_SPEED_PERCENTAGE, ADVANCE_SPEED_PERCENTAGE);
    _delay_ms(TURN_DELAY_180);
    robot.motor.stopPwm();
    _delay_ms(500);
}

void Centralize::getPositionData(char* tab) {
    if (isInFrontOfWall) {
        tab[0] = 'F';
    } else {
        tab[0] = 'B';
    }

    if (isAboveCenter) {
        tab[1] = 'A';
    } else {
        tab[1] = 'B';
    }

    if (!isInFrontOfWall) {
        if (initialDistance < 27) {
            tab[2] = '1';
        }
        if (initialDistance >= 27 && initialDistance < 32) {
            tab[2] = '2';
        }
        if (initialDistance >= 32) {
            tab[2] = '3';
        }

    } else {
        if (initialDistance >= 76) {
            tab[2] = '1';
        }
        if (initialDistance >= 61 && initialDistance < 76) {
            tab[2] = '2';
        }
        if (initialDistance < 61) {
            tab[2] = '3';
        }
    }
}


void Centralize::readDistance() {
    uint16_t distance16bits, distance16bits2, distance16bits3, distance16bits4, distance16bits5;

    distance16bits = robot.can1.lecture(0);
    distance16bits2 = robot.can1.lecture(0);
    distance16bits3 = robot.can1.lecture(0);
    distance16bits4 = robot.can1.lecture(0);
    distance16bits5 = robot.can1.lecture(0);

    uint16_t sum;
    
    sum = (distance16bits + distance16bits2 + distance16bits3 + distance16bits4 + distance16bits5) / 5;
    distance = sum >> 2;
}

void Centralize::centralizeRobot() {
    // Marque le début de la centralisation
    donedebut = 1;
    DDRA &= ~(1 << PA0);
    uint8_t numberOfSpins = 0;

    // Lecture de la distance initiale
    readDistance();
    initialDistance = distance;
    // Déterminer si le robot est face au mur ou au centre
    if (distance > DOT_TO_WALL_DISTANCE_MAX) {
        isInFrontOfWall = true;
    }
    _delay_ms(WAIT_DELAY);

    readDistance();
    if (isInFrontOfWall) {
        // Reculer vers la distance désirée si face au mur
        while (distance > DESIRED_DISTANCE) {
            readDistance();
            robot.motor.adjustPwmBackward(94, ADVANCE_SPEED_PERCENTAGE_MAX);
            _delay_ms(START_MOTOR_DELAY);
            robot.motor.stopPwm();
            _delay_ms(700);
        }
    } 
    else {
        // Avancer vers la distance désirée si face au centre
        while (distance < DESIRED_DISTANCE) {
            readDistance();
            robot.motor.adjustPwmForward(94, ADVANCE_SPEED_PERCENTAGE_MAX);
            _delay_ms(START_MOTOR_DELAY);
            robot.motor.stopPwm();
            _delay_ms(700);
        }
    }

    robot.motor.stopPwm();
    _delay_ms(WAIT_DELAY);
 
    // Effectuer des rotations 180° pour déterminer la position
    readDistance();
    while (distance > 15) {
        readDistance();
        do180();
        numberOfSpins++;
    } 

    // Déterminer si le robot est au-dessus ou en-dessous du centre
    if (isInFrontOfWall && numberOfSpins < 26) {
        isAboveCenter = true;
    }
    if (!isInFrontOfWall && numberOfSpins > 26) {
        isAboveCenter = true;
    }
    // Marque la fin de la centralisation
    donefin = 1;
}

