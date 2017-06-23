#ifndef BESTENLISTELESEN_H_
#define BENUTZERVERWALTUNG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

static int callback(void* data, int argc, char** argv, char **colName);
int selectBestenlisteNachSchwierigkeitsgrad(int schwierigkeitsgrad);

typedef struct{
    char cName[15];
    char cPs[3];
    char cP[3];
    char cZ[4];
} BESTENLISTENEINTRAG;

typedef struct{
    BESTENLISTENEINTRAG platz[5];
} BESTENLISTE;
BESTENLISTE leicht, mittel, schwer;

#endif /* BENUTZERVERWALTUNG_H_ */
