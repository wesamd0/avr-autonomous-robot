
#ifndef ROBOT1_H
#define ROBOT1_H

#define F_CPU 8000000
#pragma once
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Button.h>
#include <can.h>
#include <CommunicationUART.h>
#include <AdjustPWM.h>
#include <debug.h>
#include <LED.h>
#include <memoire_24.h>
#include <sono.h>
#include <Timer.h>

struct Robot1 {

    AdjustPWM motor;
    Button bouton;
    can can1;
    UART uart;
    Memoire24CXXX memoire;
    Sono sono;
    Timer timer;
    Debug debug;
    Led del = Led(&DDRA, &PORTA, PA3, PA2);

    void InitialiserRobot() {
        uart.intializeUART();
      //  timer.intialize();
    }

};

#endif // ROBOT_H