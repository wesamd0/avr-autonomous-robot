#include <lignes.h>
#include <avr/interrupt.h>
#include <UnicodePrint.h>
#include <robot2.h>
#include <lignes.cpp>
#include <infrarouge.h>
enum class Mode
{
    lignes,
    IR,
    RS232
};
volatile Mode state = Mode::lignes;
volatile bool buttonPressed = false;
volatile bool drawn = false;
volatile bool irdone = false;
const uint8_t SOUND_EMISSION_DELAY = 10;
const uint8_t SOUND_EMISSION_WAIT_DELAY = 50;
ISR(INT0_vect)
{
    _delay_ms(DEBOUNCE_DELAY);
    if (PIND & (MASK_D2))
    {
        state = Mode::IR;
    }
    EIFR |= (1 << INTF0);
}

ISR(INT1_vect)
{
    _delay_ms(DEBOUNCE_DELAY);
    if (!(PIND & (MASK_D3)))
    {
        state = Mode::RS232;
    }
    EIFR |= (1 << INTF1);
}

int main()
{
    Line test;
    Robot2 robot;
    robot.InitialiserRobot();
    robot.bouton.intialize();
    Infrarouge IR;

    while (true)
    {
        switch (state)
        {
        case Mode::lignes:
        {
            if(!done){
              test.followLine();
            }
            else{
                //fais rien
            }
            break;
            }
             
        
        case Mode::IR:
        {
            robot.del.setOff();
            
            if (!irdone)
            {
                robot.sono.startPiazo(81);
            _delay_ms(SOUND_EMISSION_DELAY);
            robot.sono.stopPiezo();
            _delay_ms(SOUND_EMISSION_WAIT_DELAY);
            robot.sono.startPiazo(81);
            _delay_ms(SOUND_EMISSION_DELAY);
            robot.sono.stopPiezo();
            _delay_ms(SOUND_EMISSION_WAIT_DELAY);
            robot.sono.startPiazo(81);
            _delay_ms(SOUND_EMISSION_DELAY);
            robot.sono.stopPiezo();
                
                
                uint8_t nbLignes = dataLignes[0];
                uint8_t upperLignes = dataLignes[18];
                uint8_t distanceLongeurs[12];
                DDRD |= 1 << DDD6;
                int compteur = 1;
                int j = 0;
                for (int i = 0; i < 14; i++)
                {

                    if (((upperLignes * 2) + 1) == compteur)
                    {
                        j--;
                    }
                    else if ((dataLignes[0] * 2) + 2 == compteur)
                    {
                        j--;
                    }
                    else
                    {
                        distanceLongeurs[j] = dataLignes[i + 2];
                    }
                    compteur++;
                    j++;
                }

                distanceLongeurs[1] *= 2;
                distanceLongeurs[3] *= 2;
                distanceLongeurs[5] *= 2;
                distanceLongeurs[7] *= 2;
                distanceLongeurs[9] *= 2;
                distanceLongeurs[11] *= 2;
                switch (upperLignes)
                    {
                    case 0:
                    {
                        distanceLongeurs[0] = distanceLongeurs[0];
                        distanceLongeurs[2] = distanceLongeurs[0] + distanceLongeurs[2];
                        distanceLongeurs[4] = distanceLongeurs[2] + distanceLongeurs[4];
                        distanceLongeurs[6] = distanceLongeurs[4] + distanceLongeurs[6];
                        if (distanceLongeurs[8] != 0)
                        {
                            distanceLongeurs[8] = distanceLongeurs[6] + distanceLongeurs[8];
                        }

                        if (distanceLongeurs[10] != 0)
                        {
                            distanceLongeurs[10] = distanceLongeurs[8] + distanceLongeurs[10];
                        }
                        break;
                    }
                    case 1:
                    {
                        distanceLongeurs[0] = distanceLongeurs[0];
                        distanceLongeurs[2] = distanceLongeurs[2];
                        distanceLongeurs[4] = distanceLongeurs[2] + distanceLongeurs[4];
                        distanceLongeurs[6] = distanceLongeurs[4] + distanceLongeurs[6];
                        if (distanceLongeurs[8] != 0)
                        {
                            distanceLongeurs[8] = distanceLongeurs[6] + distanceLongeurs[8];
                        }
                        if (distanceLongeurs[10] != 0)
                        {
                            distanceLongeurs[10] = distanceLongeurs[8] + distanceLongeurs[10];
                        }

                        break;
                    }
                    case 2:
                    {
                        distanceLongeurs[0] = distanceLongeurs[0];
                        distanceLongeurs[2] = distanceLongeurs[0] + distanceLongeurs[2];
                        distanceLongeurs[4] = distanceLongeurs[4];
                        distanceLongeurs[6] = distanceLongeurs[4] + distanceLongeurs[6];
                        if (distanceLongeurs[8] != 0)
                        {
                            distanceLongeurs[8] = distanceLongeurs[6] + distanceLongeurs[8];
                        }

                        if (distanceLongeurs[10] != 0)
                        {
                            distanceLongeurs[10] = distanceLongeurs[8] + distanceLongeurs[10];
                        }
            
                        break;
                    }
                    case 3:
                    {
                        distanceLongeurs[0] = distanceLongeurs[0];
                        distanceLongeurs[2] = distanceLongeurs[0] + distanceLongeurs[2];
                        distanceLongeurs[4] = distanceLongeurs[2] + distanceLongeurs[4];
                        distanceLongeurs[6] = distanceLongeurs[6];
                        if (distanceLongeurs[8] != 0)
                        {
                            distanceLongeurs[8] = distanceLongeurs[6] + distanceLongeurs[8];
                        }

                        if (distanceLongeurs[10] != 0)
                        {
                            distanceLongeurs[10] = distanceLongeurs[8] + distanceLongeurs[10];
                        }
                        break;
                    }
                    case 4:
                    {
                        distanceLongeurs[0] = distanceLongeurs[0];
                        distanceLongeurs[2] = distanceLongeurs[0] + distanceLongeurs[2];
                        distanceLongeurs[4] = distanceLongeurs[2] + distanceLongeurs[4];
                        distanceLongeurs[6] = distanceLongeurs[4] + distanceLongeurs[6];
                        distanceLongeurs[8] = distanceLongeurs[8];
                        if (distanceLongeurs[10] != 0)
                        {
                            distanceLongeurs[10] = distanceLongeurs[8] + distanceLongeurs[10];
                        }
                        break;
                    }
                }
                IR.envoyerChar(nbLignes);
                _delay_ms(25);
                IR.envoyerChar(upperLignes);
                _delay_ms(25);
                for (int i = 0; i < 12; i++)
                {
                    IR.envoyerChar(distanceLongeurs[i]);
                    robot.uart.transmitUART(distanceLongeurs[i]);
                    _delay_ms(25);
                }
                irdone = true;
            }
        }
        break;
        case Mode::RS232:
        {
            robot.del.setGreen();
            {
                if (!drawn)
                {
                    

                    uint8_t nbLignes = dataLignes[0];
                    uint8_t upperLignes = dataLignes[18];
                    uint8_t distanceLongeurs[12];
                    
                    int compteur = 1;
                    int j = 0;
                 
                    for (int i = 0; i < 14; i++)
                    {

                        if (((upperLignes * 2) + 1) == compteur)
                        {
                            j--;
                        }
                        else if ((dataLignes[0] * 2) + 2 == compteur)
                        {

                            j--;
                        }
                        else
                        {
                            distanceLongeurs[j] = dataLignes[i + 2];
                            
                        }
                        compteur++;
                        j++;
                    }
              
                    distanceLongeurs[1] *= 2;
                    distanceLongeurs[3] *= 2;
                    distanceLongeurs[5] *= 2;
                    distanceLongeurs[7] *= 2;
                    distanceLongeurs[9] *= 2;
                    distanceLongeurs[11] *= 2;
                
                    switch (upperLignes)
                    {
                    case 0:
                    {
                        distanceLongeurs[0] = distanceLongeurs[0];
                        distanceLongeurs[2] = distanceLongeurs[0] + distanceLongeurs[2];
                        distanceLongeurs[4] = distanceLongeurs[2] + distanceLongeurs[4];
                        distanceLongeurs[6] = distanceLongeurs[4] + distanceLongeurs[6];
                        if (distanceLongeurs[8] != 0)
                        {
                            distanceLongeurs[8] = distanceLongeurs[6] + distanceLongeurs[8];
                        }

                        if (distanceLongeurs[10] != 0)
                        {
                            distanceLongeurs[10] = distanceLongeurs[8] + distanceLongeurs[10];
                        }
                        break;
                    }
                    case 1:
                    {
                        distanceLongeurs[0] = distanceLongeurs[0];
                        distanceLongeurs[2] = distanceLongeurs[2];
                        distanceLongeurs[4] = distanceLongeurs[2] + distanceLongeurs[4];
                        distanceLongeurs[6] = distanceLongeurs[4] + distanceLongeurs[6];
                        if (distanceLongeurs[8] != 0)
                        {
                            distanceLongeurs[8] = distanceLongeurs[6] + distanceLongeurs[8];
                        }
                        if (distanceLongeurs[10] != 0)
                        {
                            distanceLongeurs[10] = distanceLongeurs[8] + distanceLongeurs[10];
                        }

                        break;
                    }
                    case 2:
                    {
                        distanceLongeurs[0] = distanceLongeurs[0];
                        distanceLongeurs[2] = distanceLongeurs[0] + distanceLongeurs[2];
                        distanceLongeurs[4] = distanceLongeurs[4];
                        distanceLongeurs[6] = distanceLongeurs[4] + distanceLongeurs[6];
                        if (distanceLongeurs[8] != 0)
                        {
                            distanceLongeurs[8] = distanceLongeurs[6] + distanceLongeurs[8];
                        }

                        if (distanceLongeurs[10] != 0)
                        {
                            distanceLongeurs[10] = distanceLongeurs[8] + distanceLongeurs[10];
                        }
            
                        break;
                    }
                    case 3:
                    {
                        distanceLongeurs[0] = distanceLongeurs[0];
                        distanceLongeurs[2] = distanceLongeurs[0] + distanceLongeurs[2];
                        distanceLongeurs[4] = distanceLongeurs[2] + distanceLongeurs[4];
                        distanceLongeurs[6] = distanceLongeurs[6];
                        if (distanceLongeurs[8] != 0)
                        {
                            distanceLongeurs[8] = distanceLongeurs[6] + distanceLongeurs[8];
                        }

                        if (distanceLongeurs[10] != 0)
                        {
                            distanceLongeurs[10] = distanceLongeurs[8] + distanceLongeurs[10];
                        }
                        break;
                    }
                    case 4:
                    {
                        distanceLongeurs[0] = distanceLongeurs[0];
                        distanceLongeurs[2] = distanceLongeurs[0] + distanceLongeurs[2];
                        distanceLongeurs[4] = distanceLongeurs[2] + distanceLongeurs[4];
                        distanceLongeurs[6] = distanceLongeurs[4] + distanceLongeurs[6];
                        distanceLongeurs[8] = distanceLongeurs[8];
                        if (distanceLongeurs[10] != 0)
                        {
                            distanceLongeurs[10] = distanceLongeurs[8] + distanceLongeurs[10];
                        }
                        break;
                    }
                    }
                      Dessin dessin;
                      dessin.printAll(nbLignes, upperLignes, distanceLongeurs[0], distanceLongeurs[1], distanceLongeurs[2], distanceLongeurs[3], distanceLongeurs[4],
                                      distanceLongeurs[5], distanceLongeurs[6], distanceLongeurs[7], distanceLongeurs[8], distanceLongeurs[9], distanceLongeurs[10], distanceLongeurs[11], 0, -20); // Max 16 pour distance Max

                    drawn = true;
                    break;
                }
            }
        }
        }
    }
}