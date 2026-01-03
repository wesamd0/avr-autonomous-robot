/*
 * Nom:PositionsLigne.h
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 29 mars 2024
*/

#ifndef POSITION_LINE_H
#define POSITION_LINE_H


// définir les positions de la ligne par rapport au capteur sur le robot

enum class Positions
{
    TURN_LEFT,            // La ligne est la plus à gauche possible.
    LEFT,                 // La ligne est un peu à gauche.
    CENTER,               // La ligne est au centre.
    RIGHT,                // La ligne est un peu à droite.
    TURN_RIGHT,           // La ligne est la plus à droite possible.
    END_LINE,              // La ligne est arrive a la fin d'un ruban
    END_TRIP,              // Fin du parcours
    //DEBUG
};

#endif // POSITION_LINE_H