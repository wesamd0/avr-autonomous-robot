/*
 * Nom:debug.cpp
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 11 mars 2024
*/


#include "debug.h"


Debug::Debug() {

}

//Transmet la valeur d'une variable booleene
void Debug::obtenirBool(bool var) {
    char vrai[7] = "Vrai\n";
    char faux[7] = "Faux\n";
    intializeUART();
    if(var){
        for(int i = 0; i < 7; i++){
            transmitUART(vrai[i]);
        }
    }
    else{
        for(int i = 0; i < 7; i++){
            transmitUART(faux[i]);
        }
    }
}
