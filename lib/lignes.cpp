/*
 * Nom:Lignes.cpp
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 29 mars 2024
*/

#include "lignes.h"
//Tableau de données
//0 - nombre de lignes lues
//1 - nombre de coins passées
//2- 16 couples distance-longueur des lignes (longueur = 1 par default)
//17 - nombre de ligne d'un côté
//18- slot, 2 par default
volatile uint8_t dataLignes[19] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0};
//volatile uint8_t dataLignes[19] = {5,0,0x0b,0x03,0x0f,0x02,0x0d,0x01,0,0x0c,0x03,0x016,0x03,23,0,0,0,2,3};
volatile uint32_t longueurStart = 0;
volatile bool done = false;

Line::Line()
{
  DDRA &= ~((1 << PA2) | (1 << PA3) | (1 << PA4) | (1 << PA5) | (1 << PA6));
}

// Lit l'état du capteur de ligne spécifié.
// param: # de la broche du capteur à lire.
// return vrai si la ligne est détectée sur la broche du parametre

bool Line::readLineSensors(const uint8_t sensorPin)
{

  return (PINA & (1 << sensorPin));
}

Positions Line::getAlignment()
{

  bool extremLeft = readLineSensors(PA2);  // Capteur le plus à gauche
  bool left = readLineSensors(PA3);        // Capteur gauche
  bool center = readLineSensors(PA4);      // Capteur central
  bool right = readLineSensors(PA5);       // Capteur droit
  bool extremRight = readLineSensors(PA6); // Capteur le plus à droite

  // Si seulement le capteur central détecte la ligne, on est au centre

  if (!extremLeft && !left && center && !right && !extremRight)
    return Positions::CENTER;

  // Si les capteur de DROITE détectent la ligne, la ligne est un peu à droite du robot
  //(faire tourner la roue gauche plus vite pour revenir au centre)

  if ((!extremLeft && !left && center && right && !extremRight) || (!extremLeft && !left && !center && right && extremRight) ||
      (!extremLeft && !left && !center && !right && extremRight) || (!extremLeft && !left && !center && right && !extremRight))
    return Positions::RIGHT;

  // Si les capteur de EXTREME DROITE détectent la ligne, la ligne change de direction
  //(faire tourner le robot 90 degree pour se recentrer)

  if ((!extremLeft && !left && center && right && extremRight) || (!extremLeft && left && center && right && extremRight) ||
      (extremLeft && left && center && right && extremRight) || (!extremLeft && left && center && !right && extremRight) ||
      (!extremLeft && !left && center && !right && extremRight))

    return Positions::TURN_RIGHT;

  if ((!extremLeft && left && center && !right && !extremRight) || (extremLeft && left && !center && !right && !extremRight) ||
      (extremLeft && !left && !center && !right && !extremRight) || (!extremLeft && left && !center && !right && !extremRight))
    return Positions::LEFT;

  if ((extremLeft && left && !center && !right && !extremRight && (dataLignes[1]>=4)) ||
      (extremLeft && left && center && !right && !extremRight && (dataLignes[1]>= 4)))
    return Positions::TURN_LEFT;

  // ne capte rien une fois a la fin de la bande
  if (isEndTrip && !extremLeft && !left && !center && !right && !extremRight)
    return Positions::END_TRIP;

  if (!extremLeft && !left && !center && !right && !extremRight){
    _delay_ms(50);
      if(!extremLeft && !left && !center && !right && !extremRight){
        return Positions::END_LINE;
      }
  }
}

void Line::turnRight()
{
  
  bool isCorner = false;
  motor.adjustPwmForward(70,70);
  _delay_ms(10);
  motor.adjustPwmForward(speedPercentage+3, speedPercentage+2);
  _delay_ms(WAIT_DELAY - 200);
  motor.stopPwm();
  if(getAlignment()==Positions::END_LINE){
    isCorner = true;
  }
  
  // le robot avance un peu pour permettre d'etre plus centré sur la ligne une
  // fois le virage
  

  bool horsligne = false;
  while (!horsligne)
  {
    motor.adjustPwmBackward(80,0);
    _delay_ms(10);
    motor.adjustPwmBackward(speedPercentage+7, 0);
    _delay_ms(400);
    if (getAlignment() == Positions::END_LINE)
    {
      robot.del.setGreen();
      _delay_ms(400);
      motor.stopPwm();
      horsligne = true;
    }
  }

  // Tourne à droite avec la roue gauche à l'arrêts
  // Petit délai pour permettre un ajustement progressif
  _delay_ms(50);

  robot.del.setRed();
  motor.adjustPwmBackward(80, 0);
  _delay_ms(10);
  motor.adjustPwmBackward(speedPercentage+7, 0);

  while (!readLineSensors(PA4))
    ; // Continue jusqu'à ce que le capteur central détecte la ligne
  //**(faire PA5 a cause dun delai, comme ca il est beaucoup plus centree)

  motor.stopPwm();
  
  if(!isCorner){
    uint16_t counter = 0;

    while(!(getAlignment()==Positions::END_LINE)){
      motor.adjustPwmForward(speedPercentage, speedPercentage);
      counter++;
      robot.uart.transmitUART(counter/100);
      if(getAlignment() == Positions::RIGHT){
        robot.del.setOff(); 
        robot.del.setGreen();
        motor.adjustPwmForward(speedPercentage, 50);
        _delay_ms(10);
        counter++;
      }
      else if(getAlignment() == Positions::LEFT){
        robot.del.setOff(); 
        robot.del.setGreen();
        motor.adjustPwmForward(50,speedPercentage);
        _delay_ms(10);
        counter++;
      }
    }
    robot.uart.transmitUART(counter/100);
    motor.stopPwm();
    dataLignes[dataLignes[17]] = (counter/100);
    dataLignes[17]++;
  }
  else if(isCorner){
    dataLignes[1]++;
    motor.adjustPwmForward(speedPercentage, speedPercentage);
  }
}

void Line::turnLeft()
{
  // le robot avance un peu pour permettre d'etre plus centré sur la ligne une
  // fois le virage
  motor.adjustPwmForward(speedPercentage + 5, speedPercentage);
  _delay_ms(WAIT_DELAY - 100);

  bool horsligne = false;
  while (!horsligne)
  {
    motor.adjustPwmBackward(0, TURN_PERCENTAGE);
    if (getAlignment() == Positions::END_LINE)
    {
      robot.del.setGreen(); 
      _delay_ms(100);
      motor.stopPwm();
      horsligne = true;
    }
    _delay_ms(200);
    robot.del.setRed();
    motor.adjustPwmBackward(0, 80);
  _delay_ms(10);
    motor.adjustPwmBackward(0, TURN_PERCENTAGE);
  }
  while (!readLineSensors(PA2))
    ; // Continue jusqu'à ce que le capteur central détecte la ligne
  //**(faire PA5 a cause dun delai, comme ca il est beaucoup plus centree)

  motor.stopPwm();
  _delay_ms(WAIT_DELAY);
  while(!(getAlignment()==Positions::END_LINE)){
    motor.adjustPwmForward(speedPercentage, speedPercentage); // Avance tout droit une fois la ligne détectée
    if(getAlignment() == Positions::RIGHT){
      robot.del.setOff(); 
      robot.del.setGreen();
      motor.adjustPwmForward(speedPercentage, 55);
      _delay_ms(10);
    }
    else if(getAlignment() == Positions::LEFT){
        robot.del.setOff(); 
        robot.del.setGreen();
        motor.adjustPwmForward(55,speedPercentage);
        _delay_ms(10);
      }
    }
    
    motor.stopPwm();
}

void Line::goBackwards(){
  bool isMistake = false;
  _delay_ms(500);
   while((getAlignment()==Positions::END_LINE)){
   
    motor.adjustPwmBackward(80, 80);
    _delay_ms(10);
    motor.adjustPwmBackward(speedPercentage, speedPercentage);

    
  }
  
  if(!isMistake){
    
 
  motor.stopPwm();
  
  bool horsligne = false;
  while (!horsligne)
  {
    motor.spinLeft(speedPercentage+7,speedPercentage+7);
    if (getAlignment() == Positions::END_LINE)
    {
      robot.del.setGreen(); 
      _delay_ms(100);
      motor.stopPwm();
      horsligne = true;
    }
    _delay_ms(200);
    robot.del.setRed();
    motor.spinLeft(80, 80);
    _delay_ms(10);
    motor.spinLeft(speedPercentage+7,speedPercentage+7);
  }
  while (!readLineSensors(PA2));
  motor.stopPwm();
  _delay_ms(WAIT_DELAY);
  dataLignes[0]++;
  motor.adjustPwmForward(80,80);
  _delay_ms(10);
  motor.adjustPwmForward(speedPercentage, speedPercentage); // Avance tout droit une fois la ligne détectée
  }
  }


void Line::setDataLigne(uint8_t slot, uint8_t data){
  dataLignes[slot] = data;
}

uint8_t Line::getDataLigne(uint8_t slot){
  return dataLignes[slot];

}

void setDataLigne(uint8_t slot, uint8_t data){
  dataLignes[slot] = data;
}

uint8_t getDataLigne(uint8_t slot){
  return dataLignes[slot];

}

void Line::followLine()
{
 
  Positions position = getAlignment();

  switch (position)
  {

  case Positions::CENTER:
  {
    
    dataLignes[1] = dataLignes[1];
    uint16_t counter = 0;
    while((getAlignment() != Positions::TURN_RIGHT) && getAlignment() != Positions::TURN_LEFT){
    counter++;
    robot.del.setAmber();
    motor.adjustPwmForward(speedPercentage, speedPercentage);  
    if(getAlignment() == Positions::RIGHT){
      robot.del.setOff(); 
      robot.del.setGreen();
      motor.adjustPwmForward(speedPercentage, 50);
      _delay_ms(10);
      counter++;
    }
    else if(getAlignment() == Positions::LEFT){
        robot.del.setOff(); 
        robot.del.setGreen();
        motor.adjustPwmForward(50,speedPercentage);
        _delay_ms(10);
        counter++;
      }
    else if(getAlignment()==Positions::END_LINE){
      
      goBackwards();
      break;
    }
    
    robot.uart.transmitUART(dataLignes[1]);
    }
    if((dataLignes[1] == 0)){
      longueurStart = counter;
    }
    if(((dataLignes[1] == 1) || (dataLignes[1] == 3)) ){
      dataLignes[dataLignes[17]] = ((((counter)*11)/longueurStart))+6;
      dataLignes[17]++;
    }
    if((dataLignes[1] == 2)){
    dataLignes[18] = dataLignes[0];
    dataLignes[1] = dataLignes[1];

    }
    break;
  }
    
  case Positions::RIGHT:
  {
    
     robot.del.setOff(); 
     robot.del.setGreen();
    motor.adjustPwmForward(speedPercentage, 55);
    _delay_ms(10);
    position = Positions::CENTER;
    break;
  }

  case Positions::TURN_RIGHT:
  {
   
    robot.del.setOff();
    robot.del.setGreen();
   
    turnRight();
    robot.uart.transmitUART(dataLignes[1]);
    robot.uart.transmitUART(dataLignes[17]);
    break;
  }

  case Positions::LEFT:
  {
     
     robot.del.setOff(); 
     robot.del.setRed();
    motor.adjustPwmForward(55, speedPercentage);
    _delay_ms(10);
    position = Positions::CENTER;
    break;
  }


  case Positions::TURN_LEFT:
  {
    //fake turn left
    if(dataLignes[1] < 4){
      robot.del.setOff();
    robot.del.setGreen();
   
    turnRight();
    robot.uart.transmitUART(dataLignes[1]);
    robot.uart.transmitUART(dataLignes[17]);
    break;
      break;
    }
 
    robot.del.setOff();
    robot.del.setRed();
   
       turnLeft();
      isEndTrip = true;
   

    break;
  }

  case Positions::END_LINE:
  {
  
    
    if((getAlignment() == Positions::TURN_RIGHT)){
      robot.del.setOff();
    robot.del.setGreen();
    
    turnRight();
    robot.uart.transmitUART(dataLignes[1]);
    robot.uart.transmitUART(dataLignes[17]);
      break;
    }
    robot.del.setOff();
    robot.del.setGreen();

    goBackwards();
    
    
    break;
  }

  case ::Positions::END_TRIP:
  {
    
    robot.del.setRed();
    motor.stopPwm(); 
    _delay_ms(3000);
    _delay_ms(3000);
    _delay_ms(3000);
    done = true;
   
    }
  }
 }
