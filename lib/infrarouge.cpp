/*
 * Nom:infrarouge.cpp
 * Auteurs: Kamil Benabdallah
            Wesam Dawod
            Mehmet Erten
            Alexandre Ribeiro
 * Date : 25 mars 2024
*/

#include "infrarouge.h"

//mode 0 = transmission, mode 1 = reception

void Infrarouge::init(bool mode) {
   if(mode){
    DDRD |= (1 << DDD6);
   }
   else {
    DDRC &= (0 << DDC4);
   }
   uart.intializeUART();
}

void Infrarouge::envoyerBit(bool bit){
    
    //1200us a 38kHz -> ~46 periodes de 25us
    if(bit){
        for(int i = 0; i < 46; i++){
                
            PORTD |= (1<<PD6); 
            _delay_us(12.7);
            PORTD &= (0<<PD6);
            _delay_us(12.7);   

        }
    }
    
    //600us a 38kHz -> ~23 periodes de 25us
    else{
        for(int i = 0; i < 23; i++){

            PORTD |= (1<<PD6); 
            _delay_us(12.7);
            PORTD &= (0<<PD6);
            _delay_us(12.7);   
        
        }
    }

}
    
void Infrarouge::eteindreIR(){
    PORTC &= (TRANSMITPORT << 0);
    _delay_us(BUFFERDELAYUS);
}

void Infrarouge::signalerDepart(){
    //2x 1200us
    envoyerBit(1);
    envoyerBit(1);
    eteindreIR();
}

//cree le crc16 avec le tableau qui contient jusqu'a 6 paires emplacement-longueur, si il y a moins
//que 6 paires, encodez 0 dans le tableau et la fonction l'ignore
uint8_t Infrarouge::creerCRC16(uint8_t data[12]){

    uint8_t crc = 0xFF;

    for(int i = 0; i < 12; i++){
        
        if(data[i] != 0){
        
            crc = _crc16_update(crc, data[i]);
        
        } 
    }
    
    return crc;
}

void Infrarouge::envoyerChar(uint8_t data) {
   
    bool bitDansChar;

    //transmet le char du MSB au LSB
    for (int i = 7; i >= 0; i--) {

        bitDansChar = (data >> i) & 1;

        if (bitDansChar) {

            envoyerBit(1);
            _delay_ms(25);
        }
        else {

            envoyerBit(0);
            _delay_ms(25);

        }
    }
}

//envoie un signal de depart, le crc calculé avec creerCRC16 le tableau
//char par char, puis 0x00
void Infrarouge::envoyerArray(uint8_t data[14]){
    
    uint8_t crc = creerCRC16(data);
    

    envoyerChar(crc);

    for(int i = 0; i < 12; i++){
        envoyerChar(data[i]);
    }

    envoyerChar(0x00);
}

/*On entre le crc, suivi de 8 a 12 chars dependant du nombre
de lignes si le robot rencontre 0x00, il considere la transmission
complete et fait la verification crc. True si ca passe.*/

bool Infrarouge::recevoir() {
    
    uint8_t crc  = 0xFF;
    uint8_t data = 0x00; 
    uint8_t bit  = 7;
    uint16_t adresse = 0x00;

    bool bitComplet = false;
    bool receptionEnCours = false;

    uint8_t crcCompare;
   
    //capter signal de depart
    if(!(PINC & INPUT)){

        receptionEnCours = true;
        _delay_us(STARTDELAYUS);
    }
    while(receptionEnCours){
        while(!bitComplet){

            uint16_t counter = 0;

            //on compte le temps ou la DEL IR est allumée
            while(!(PINC & INPUT)){
                counter++;
            }
            //assez longtemps pour 1, on bitshift 1
            if(counter > SIRCVALUE) {
                data |= (bit << 1);
            }
            //pas assez longtemps pour 1, on bitshift 0
            else{
                data &= (bit<<0);
            }
            bit--; 
            if(bit == -1){
                bitComplet = true;
            }
            counter = 0;
        }

            
        //on ecrit le char dans la memoire
       // mem.ecriture(adresse, data);
       // _delay_ms(5);
       adresse++;
       //UART uart;
       //uart.intializeUART();
       uart.transmitUART(data);
        
        //verifie si le dernier bit etait 0x00/si on a rencontré la fin
        //et on sort de la boucle.
        if(adresse == 0x0f){
            break;
        }
        //sinon, mettre a jour le crc
        else{
            crc = _crc16_update(crc, data);
        }
        data = 0x00;
    }
    
    //comparaison du CRC contenu a l'adresse 0x00
    mem.lecture(0x00, &crcCompare);
    if (crc == crcCompare){
        return true;
    }
    else{
        return false;
    }
    
}

