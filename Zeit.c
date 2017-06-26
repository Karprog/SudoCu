#include "Zeit.h"

long int iZeitStartWert = -1;
int iLetzteZeit = 0;


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Berechnet die Zeit seit dem Spielstart in Sekunden              *
 * Parameter: none                                                           *
 * R�ckgabewert: int (Anzahl der Sekunden oder -1)                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int iZeitBerechnen(void){
    // Holt die jetzige Zeit
    int iZeitJetzt = time(0);
    int iSekunden = 0;

    // Bei dem ersten Aufruf den Zeitpunkt des Aufrufs setzen
    if(iZeitStartWert == -1){
        iZeitStartWert = iZeitJetzt;
        iLetzteZeit = iZeitJetzt;
    }

    iSekunden =  iZeitJetzt - iZeitStartWert;

    if((iLetzteZeit - iZeitJetzt) <= -1){
        iLetzteZeit = iZeitJetzt;
    }

    return iSekunden;
}
