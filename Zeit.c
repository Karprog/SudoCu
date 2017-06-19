#include "Zeit.h"

long int iZeitStartWert = -1;
int iLetzteZeit = 0;

int iZeitBerechnen(void){
    int iZeitJetzt = time(0);
    int iSekunden = 0;

    if(iZeitStartWert == -1){
        iZeitStartWert = iZeitJetzt;
        iLetzteZeit = iZeitJetzt;
    }

    iSekunden =  iZeitJetzt - iZeitStartWert;

    if((iLetzteZeit - iZeitJetzt) <= -1){
        iLetzteZeit = iZeitJetzt;

        return iSekunden;
    }

    return -1;
}
