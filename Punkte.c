#include "Punkte.h"

int iPunktzahl = 0;
int iAbgezogenePunkte = 0;
int iGesamtPunkte = 0;

void punkteBerechnen(int iEingabeCode){
    if(iEingabeCode == 1){
        iPunktzahl += 10;
    }
    else if(iEingabeCode == 2){
        iAbgezogenePunkte += 5;
    }
}

void gesamtPunkteBerechnen(){
    iGesamtPunkte = iPunktzahl - iAbgezogenePunkte;
}
