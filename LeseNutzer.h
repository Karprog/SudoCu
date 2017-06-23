#ifndef LESENUTZER_H_
#define LESENUTZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

static int callback (void *data, int argc, char **argv, char **colName);
char leseNutzerdatenVonDb(char* nutzername, char* passwort);

char nutzerId;
#endif /* LESENUTZER_H_ */
