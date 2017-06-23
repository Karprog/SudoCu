#include <stdio.h>
#include <stdlib.h>
#include "zeit.h"
#include "begruessungsbildschirm.h"

int main(){
    while (iZeitBerechnen() <= 1);
    iZeitStartWert=-1;
    begruessung();
    while (iZeitBerechnen() < 5);
    iZeitStartWert=-1;
    system("cls");
}
