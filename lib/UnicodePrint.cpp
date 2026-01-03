/*
 * Nom:UnicodePRint.cpp
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 17 avril 2024
*/

#include <memoire_24.h>
#include <CommunicationUART.h>
#include <avr/io.h>
#include <util/delay.h>
#include <LED.h>
#include "UnicodePrint.h"

bool lines(uint16_t RelDistance, uint16_t RelLength, uint16_t currentcol, uint16_t COLDEBUTLIGNE, uint16_t currentligne, uint16_t LIGNEDEBUTLIGNE)
{
    return ((currentcol == (COLDEBUTLIGNE + (RelDistance * 3))) && (currentligne < (LIGNEDEBUTLIGNE + RelLength)));
}
bool linesBottom(uint16_t RelDistance, uint16_t RelLength, uint16_t currentcol, uint16_t COLDEBUTLIGNE, uint16_t currentligne, uint16_t LIGNEDEBUTLIGNE)
{
    return ((currentcol == (COLDEBUTLIGNE + (52 * 3) - (RelDistance * 3))) && (currentligne > (LIGNEDEBUTLIGNE + 16 - RelLength)) && (currentligne < LIGNEDEBUTLIGNE + 17));
}
bool Robot(uint16_t Rotation, uint16_t distancefromtop, uint16_t currentcol, uint16_t COLDEBUTROBOT, uint16_t currentligne, uint16_t LIGNEDEBUTROBOT)
{
    return ((currentcol == (COLDEBUTROBOT + 3 * 11)) && (currentligne == (4 + distancefromtop)));
}

void Dessin::printAll(uint8_t totallines, uint8_t upperlines, uint8_t relativeD1, uint8_t relativeL1, uint8_t relativeD2, uint8_t relativeL2, uint8_t relativeD3, uint8_t relativeL3, uint8_t relativeD4, uint8_t relativeL4, uint8_t relativeD5, uint8_t relativeL5, uint8_t relativeD6, uint8_t relativeL6, bool orientation, uint8_t distancefromtop)
{

    // Tableau a partir de 0x0101; 
    
    // Premier dessin dans la memoire a 0x0060;
    // Autre à 0x0090; ---> A mettre dans le robot ligne

    // Total lines = le nombre de ligne totales,
    // upperlines = le nb de lignes en haut
    // RelativesDn à partir du bord en longuer, donc 2 - 3 - 4 sont collées, toujours partir du bord. 
    // Pour celle en bas a partir de en bas à droite du carré du Robot ligne, valeur entre 1 et 51; 
    // RelativesLn, valeur entre 1 et 8;
    // Orientation en 0 ou 1, 1 pointe vers le haut
    // Distance from top --> entre 0 et 15;


    Memoire24CXXX mem;
    UART uart;
    uint8_t data;
    uint16_t currentAdd = tableauAddBegin;

    uint16_t currentligne = 0;
    uint16_t currentcol = 0;

    uint16_t ld = 3;
    uint16_t ll = 3;
    uint8_t bigChar = 0;
    uint16_t COLDEBUTLIGNE = 2000000;
    uint16_t LIGNEDEBUTLIGNE = 2000000;

    uint16_t COLDEBUTROBOT = 2000000;
    uint16_t LIGNEDEBUTROBOT = 2000000;

    uint16_t currentLinesDrew = 0;
    uint16_t currentLineDistance = 3;
    uint16_t currentLineLength = 1;

    uint8_t currenttopdrew = 0;
    uint8_t currentbodydrew = 0;

    uint8_t partofRobotDrawn = 0;
    uint8_t RobotCharWritten[4] = {15, 5, 9, 9};
    uint8_t RobotCharWritten2[4] = {15, 9, 5, 9};
    uint8_t RobotLineWritten = 0;
    uint8_t RobotLineWrittenOn4 = 0;
   
    
   
    

    uint8_t CharRobotDntPrint;

    bool dntPrint = 0;
    bool flag;
    uart.intializeUART();
    mem.choisir_banc(0);
    uart.transmitUART(0x0a);
    bool firstcharLine = 1;
    mem.init();

    uint16_t adresserobot = 0x0060;
    uint16_t adresserobot2 = 0x0090;
    uint16_t AllLines[] = {relativeD1,
                           relativeL1,
                           relativeD2,
                           relativeL2,
                           relativeD3,
                           relativeL3,
                           relativeD4,
                           relativeL4,
                           relativeD5,
                           relativeL5,
                           relativeD6,
                           relativeL6};

    uint8_t firstlength = 1;
    uint8_t allBody;
    for (uint8_t i = 1; i < upperlines; i++)
    {
        allBody += AllLines[firstlength];
        firstlength = firstlength + 2;
    }
    for (uint16_t i = 0; i < tableauElements; i++)
    {

        mem.lecture(currentAdd, &data);
        _delay_ms(5);
        if (data == 0x0a)
        {
            currentcol = 0;
            currentligne++;

            if (flag == 1)
            {
                flag = 0;
                // uart.transmitUART(0x41);
            }
        }

        // if ((currentcol == COLDEBUTLIGNE + (45*3)) && (currentligne < (LIGNEDEBUTLIGNE + 5)))
        if ((lines(relativeD1, relativeL1, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (0 < upperlines)) ||
            (lines(relativeD2, relativeL2, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (1 < upperlines)) ||
            (lines(relativeD3, relativeL3, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (2 < upperlines)) ||
            (lines(relativeD4, relativeL4, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (3 < upperlines)) ||
            (lines(relativeD5, relativeL5, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (4 < upperlines)) ||
            (lines(relativeD6, relativeL6, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (5 < upperlines)))
        {

            if (currentligne >= LIGNEDEBUTLIGNE)
            {
                if (currentligne == LIGNEDEBUTLIGNE)
                {

                    uart.transmitUART(0xE2);
                    uart.transmitUART(0x95);
                    uart.transmitUART(0xA6);

                    dntPrint = 1;
                    // E2 95 91
                }
                else
                {

                    {
                        uart.transmitUART(0xE2);
                        uart.transmitUART(0x95);
                        uart.transmitUART(0x91);

                        dntPrint = 1;
                    } // E2 95 91
                }
            }
        }
        if ((linesBottom(relativeD1, relativeL1, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (1 > upperlines)) ||
            (linesBottom(relativeD2, relativeL2, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (2 > upperlines)) ||
            (linesBottom(relativeD3, relativeL3, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (3 > upperlines)) ||
            (linesBottom(relativeD4, relativeL4, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (4 > upperlines)) ||
            (linesBottom(relativeD5, relativeL5, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (5 > upperlines)) ||
            (linesBottom(relativeD6, relativeL6, currentcol, COLDEBUTLIGNE, currentligne, LIGNEDEBUTLIGNE) && (6 > upperlines)))
        {

            if (currentligne == (LIGNEDEBUTLIGNE + 16))
            {

                uart.transmitUART(0xE2);
                uart.transmitUART(0x95);
                uart.transmitUART(0xA9);

                dntPrint = 1;
                // E2 95 91
            }
            else
            {

                {
                    uart.transmitUART(0xE2);
                    uart.transmitUART(0x95);
                    uart.transmitUART(0x91);

                    dntPrint = 1;
                } // E2 95 91
            }
        }

        if (CharRobotDntPrint > 0)
        {
            dntPrint = 1;
            CharRobotDntPrint--;
        }

        
            

        if ((Robot(orientation, distancefromtop, currentcol, COLDEBUTROBOT, currentligne, LIGNEDEBUTROBOT)) && !(orientation))
        {
            uint16_t savedAdd = currentAdd;
            uint8_t savedData = data;

            if (RobotLineWrittenOn4 < 4)
            {
                for (uint8_t i = 0; i < RobotCharWritten[RobotLineWritten]; i++)
                {
                    mem.lecture(adresserobot, &data);
                    _delay_ms(5);

                    uart.transmitUART(data);
                    adresserobot++;
                    mem.lecture(currentAdd, &data);
                    _delay_ms(5);
                }
                CharRobotDntPrint = (4);
                RobotLineWritten++;
                distancefromtop++;
                dntPrint = 1;
                RobotLineWrittenOn4++;
            }
        }

        if ((Robot(orientation, distancefromtop, currentcol, COLDEBUTROBOT, currentligne, LIGNEDEBUTROBOT)) && (orientation))
        {
            uint16_t savedAdd = currentAdd;
            uint8_t savedData = data;

            if (RobotLineWrittenOn4 < 4)
            {
                for (uint8_t i = 0; i < RobotCharWritten2[RobotLineWritten]; i++)
                {
                    mem.lecture(adresserobot2, &data);
                    _delay_ms(5);

                    uart.transmitUART(data);
                    adresserobot2++;
                    mem.lecture(currentAdd, &data);
                    _delay_ms(5);
                }
                CharRobotDntPrint = (4);
                RobotLineWritten++;
                distancefromtop++;
                dntPrint = 1;
                RobotLineWrittenOn4++;
            }
        }

        if (data == 0xe2)
        {

            uint8_t currentData = data;
            uint16_t checkdata = currentAdd;

            mem.lecture(checkdata + 1, &data);
            _delay_ms(5);

            if (data == 0x95)
            {

                mem.lecture(checkdata + 2, &data);
                _delay_ms(5);
                if (data == 0x94)
                {

                    COLDEBUTLIGNE = currentcol;
                    LIGNEDEBUTLIGNE = currentligne;
                    data = currentData;
                }
                else
                {
                    data = currentData;
                }
            }
            else
            {
                data = currentData;
            }
        }

        if (data == 0xe2)
        {

            uint8_t currentData = data;
            uint16_t checkdata = currentAdd;

            mem.lecture(checkdata + 1, &data);
            _delay_ms(5);

            if (data == 0x94)
            {

                mem.lecture(checkdata + 2, &data);
                _delay_ms(5);
                if (data == 0x8F)
                {

                    COLDEBUTROBOT = currentcol;
                    LIGNEDEBUTROBOT = currentligne;
                    data = currentData;
                }
                else
                {
                    data = currentData;
                }
            }
            else
            {
                data = currentData;
            }
        }

        if (dntPrint == 0)
        {
            uart.transmitUART(data);
            if (data == 0x20 && bigChar == 0)
            {
                bigChar = 0;
            }
            else if (bigChar == 0)
            {
                bigChar = 3;
            }
            else
            {
                bigChar--;
            }
            if (bigChar == 0 && data == 0x20)
            {
                currentcol = currentcol + 3;
            }
            else
            {
                currentcol++;
            }

            currentAdd++;
        }
        else
        {
            if (data == 0x20)
            {
                currentAdd = currentAdd + 1;
            }
            else
            {
                currentAdd = currentAdd + 3;
                i = i + 2;
            }

            currentcol = currentcol + 3;
            bigChar = 0;
            dntPrint = 0;
        }
    }
}