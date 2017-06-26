#include "Punkte.h"

int iPunktzahl = 0;
int iAbgezogenePunkte = 0;
int iGesamtPunkte = 0;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Berechnet die Punkte nach der jeweiligen Eingabe                *
 * Parameter: none                                                           *
 * R�ckgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void punkteBerechnen(int iEingabeCode){
    // Punkte vergeben, wenn die Zahl an der Stelle korrekt ist
    if(iEingabeCode == 1){
        iPunktzahl += 10;
    }
    // Punkte abziehen, wenn die Zahl an der Stelle falsch ist
    else if(iEingabeCode == 2){
        iAbgezogenePunkte += 5;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Verrechnet die Punktzahl mit den abgezogenen Punkten            *
 * Parameter: none                                                           *
 * R�ckgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void gesamtPunkteBerechnen(){
    iGesamtPunkte = iPunktzahl - iAbgezogenePunkte;
}
