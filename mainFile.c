#include <stdio.h>
#include <stdlib.h>
#include "zeit.h"
#include "begrusungsbildschirm.h"

int main(){
    begrusung();
    while (iZeitBerechnen() < 5);
    system("cls");
}
