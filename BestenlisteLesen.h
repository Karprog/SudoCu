#ifndef BESTENLISTELESEN_H_
#define BENUTZERVERWALTUNG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

static int callback(void* data, int argc, char** argv, char **colName);
int selectBestenlisteNachSchwierigkeitsgrad(char *schwirigkeitsgrad);
int berechnePunkteProMinuteLesen(int iPunktzahl, int iZeit);

typedef struct{
    char* cLeicht[5][3];
    char* cMittel[5][3];
    char* cSchwer[5][3];
} BESTENLISTE;
BESTENLISTE bestenliste;

#endif /* BENUTZERVERWALTUNG_H_ */
