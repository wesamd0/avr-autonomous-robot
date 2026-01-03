#include <UnicodePrint.h>
#include <LED.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <distance.h>
#include <robot1.h>
#include <memoire_24.h>

#include <sono.h>

#include <CommunicationUART.h>
#include <infrarouge.h>

const uint8_t SOUND_EMISSION_DELAY = 50;
const uint8_t SOUND_EMISSION_WAIT_DELAY = 50;
volatile bool buttonPressed = false;

ISR (INT0_vect) {
    _delay_ms(DEBOUNCE_DELAY);

    if (PIND & MASK_D2) { 
        buttonPressed = true;
    } else {
        buttonPressed = false;
    }
    EIFR |= (1 << INTF0);
}

uint8_t arrayToChar(bool array[8])
{
    uint8_t data = 0;
    for (int i = 0; i < 8; i++)
    {
        data |= (array[i] ? 1 : 0) << i;
    }
    return data;
}
int main()
{

    Centralize centralize;
    Robot1 robot;
    char tab[3];
    char cha;
    uint8_t direction;
    uint8_t position;
    Infrarouge infra;
    robot.bouton.intialize();
    _delay_ms(2000);

    centralize.centralizeRobot(); 
    centralize.getPositionData(tab);

    if (tab[1] == 'A') {
        if (tab[0] == 'F') { // face au mur et et en dessus de centre
            if (tab[2] == '1') {
                position = 3;
                direction = 0;
            }
            if (tab[2] == '2') {
                position = 4;
                direction = 0;
            }
            if (tab[2] == '3') {
                position = 5;
                direction = 0;
            }
        } 
        else {              // face au centre et en dessus de centre
            if (tab[2] == '1') {
                position = 3;
                direction = 1;
            }
            if (tab[2] == '2') {
                position = 4;
                direction = 1;
            }
            if (tab[2] == '3') {
                position = 5;
                direction = 1;
            }
        }
    } 
    else {                  // face au mur et en bas de centre
        if (tab[0] == 'F') {
            if (tab[2] == '1') {
                position = 13;
                direction = 1;
            }
            if (tab[2] == '2') {
                position = 12;
                direction = 1;
            }
            if (tab[2] == '3') {
                position = 11;
                direction = 1;
            }
        } 
        else {              // face au centre et en bas de centre
            if (tab[2] == '1') {
                position = 1;
                direction = 0;
            }
            if (tab[2] == '2') {
                position = 1;
                direction = 0;
            }
            if (tab[2] == '3') {
                position = 1;
                direction = 0;
            }
        }
    }

    robot.del.setRed();
    while (!(PIND & (1<<PD2))) {
        
    }
   
    robot.sono.startPiazo(82);
    _delay_ms(SOUND_EMISSION_DELAY);
    robot.sono.stopPiezo();
    _delay_ms(SOUND_EMISSION_WAIT_DELAY);
    robot.sono.startPiazo(82);
    _delay_ms(SOUND_EMISSION_DELAY);
    robot.sono.stopPiezo();
    _delay_ms(SOUND_EMISSION_WAIT_DELAY);
    robot.sono.startPiazo(82);
    _delay_ms(SOUND_EMISSION_DELAY);
    robot.sono.stopPiezo();
    robot.del.setGreen();


    robot.del.setOff();
    UART uart;
    uart.intializeUART();

    infra.init(1);
    
    uint8_t arraytop[14];
    infra.recevoir(arraytop);

    robot.del.setGreen();
     while (!(PIND & (1<<PD2))) {
        
     }
     robot.del.setOff();
    
    Dessin dessin;
    dessin.printAll(arraytop[0],arraytop[1],arraytop[2],arraytop[3],arraytop[4],arraytop[5],arraytop[6],arraytop[7],arraytop[8],arraytop[9],arraytop[10],arraytop[11],arraytop[12],arraytop[13],direction,position);
    uint8_t phrase[28] = "Produit par: Optimus Prime";
    uart.transmitUART(0x0a);
    for(int i = 0; i <28; i++){
        uart.transmitUART(phrase[i]);
    }
}
