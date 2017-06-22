#ifndef BESTENLISTELESEN_H_
#define BENUTZERVERWALTUNG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

static int callback(void* data, int argc, char** argv, char **colName);
int selectBestenlisteNachSchwierigkeitsgrad(char *schwirigkeitsgrad);
int berechnePunkteProMinute(int iPunktzahl, int iZeit)

#endif /* BENUTZERVERWALTUNG_H_ */