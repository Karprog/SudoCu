#include <stdio.h>
#include <stdlib.h>
#include "Zeit.h"

int main(){

    begrusung();

    while(iZeitBerechnen() < 3);

    system("cls");
    iZeitStartWert = -1;

    mainFrontend();
    return 0;
}
