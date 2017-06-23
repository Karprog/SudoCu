#include <stdio.h>
#include <stdlib.h>
#include "Zeit.h"

int main(){
    system("mode 600");
    begrusung();

    while(iZeitBerechnen() < 3);

    system("cls");
    iZeitStartWert = -1;

    mainFrontend();
    return 0;
}
