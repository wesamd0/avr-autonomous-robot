/*
 * Nom:sono.cpp
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/

#include<stdio.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "sono.h"
#include <AdjustPWM.h>


Sono::Sono() {
    

}


void Sono::startPiazo(uint8_t note) {
    AdjustPWM test;
    switch (note) {
        
        case 45: test.adjustCTC2(110); break;
        case 46: test.adjustCTC2(116.54); break;
        case 47: test.adjustCTC2(123.47); break;
        case 48: test.adjustCTC2(130.81); break;
        case 49: test.adjustCTC2(138.59); break;
        case 50: test.adjustCTC2(146.83); break;
        case 51: test.adjustCTC2(155.56); break;
        case 52: test.adjustCTC2(164.81); break;
        case 53: test.adjustCTC2(174.61); break;
        case 54: test.adjustCTC2(185.00); break;
        case 55: test.adjustCTC2(196.00); break;
        case 56: test.adjustCTC2(207.65); break;
        case 57: test.adjustCTC2(220); break;
        case 58: test.adjustCTC2(233.08); break;
        case 59: test.adjustCTC2(246.94); break;
        case 60: test.adjustCTC2(261.63); break;
        case 61: test.adjustCTC2(277.18); break;
        case 62: test.adjustCTC2(293.66); break;
        case 63: test.adjustCTC2(311.13); break;
        case 64: test.adjustCTC2(329.63); break;
        case 65: test.adjustCTC2(349.23); break;
        case 66: test.adjustCTC2(369.99); break;
        case 67: test.adjustCTC2(392.00); break;
        case 68: test.adjustCTC2(415.30); break;
        case 69: test.adjustCTC2(440); break;
        case 70: test.adjustCTC2(466.16); break;
        case 71: test.adjustCTC2(493.88); break;
        case 72: test.adjustCTC2(523.25); break;
        case 73: test.adjustCTC2(554.37); break;
        case 74: test.adjustCTC2(587.33); break;
        case 75: test.adjustCTC2(622.25); break;
        case 76: test.adjustCTC2(659.26); break;
        case 77: test.adjustCTC2(698.46); break;
        case 78: test.adjustCTC2(739.99); break;
        case 79: test.adjustCTC2(783.99); break;
        case 80: test.adjustCTC2(830.61); break;
        case 81: test.adjustCTC2(880); break;
        case 82: test.adjustCTC2(1500); break;

    }

    
}
void Sono::stopPiezo() {
     DDRD &= (0 << DDD5) & (0 << DDD4); 
}

    
   



