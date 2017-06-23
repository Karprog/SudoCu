#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "LeseNutzer.h"

#define _CRT_SECURE_NO_DEPRECATE 1
#define DATABASE_FILE "benutzerverwaltung.sqlite3"

/***********************************************************************
static int callback(void *data, int argc, char **argv, char **colName)
�bergabeparameter: void *data, int argc, char **argv, char **colName
R�ckgabewert: 0
Wird f�r jeden Datensatz aufgerufen. Die �bergabeparameter enthalten die
Informationen �ber die Datenfelder.
***********************************************************************/
static int callback (void *data, int argc, char **argv, char **colName)
{
    printf("\n%s\n", argv[0]);
    nutzerId = *argv[0];
    return 0;
}

/*****************************************************************
char leseNutzerdatenVonDb(char* nutzername, char* passwort)
�bergabeparameter: char* nutzername, char* passwort
R�ckgabewert: 0 oder -1
Schreibt die Nutzerdaten in die Datenbank. Wenn dies
gelingt, wird dem User angegeben, dass der Registrierungsvorgang
erfolgreich war. Wenn nicht, wird eine Fehlermeldung ausgegeben.
*****************************************************************/
char leseNutzerdatenVonDb(char* cNutzername, char* cPasswort )
{
    /*Variablendeklaration*/
    sqlite3 *db_handle;
    int iRc;
    int iControl;
    char* cSql;
    char* cErrormsg;

    /*�ffnen der Datenbankverbindung*/
    iRc = sqlite3_open(DATABASE_FILE, &db_handle);

    if (iRc == 0) {
        /*Query zum Schreiben der Nutzerdaten in die Datenbank*/
        cSql = sqlite3_mprintf("SELECT id FROM nutzerdaten WHERE benutzername="\
                              " '%s' AND passwort = '%s';",
                            cNutzername, cPasswort);
    }
    /*Ausf�hren der Query auf der Datenbank*/
    iControl = sqlite3_exec(db_handle, cSql, callback, NULL, &cErrormsg);
    /*Fehlermeldung bei fehlgeschlagener Ausf�hrung,
    Freigabe der Verbindungsressourcen*/
    if (iRc != SQLITE_OK || iControl != 0) {
        printf("SQL-Fehler: %s\n", cErrormsg);
		sqlite3_free(cErrormsg);
		return -1;
    }

    /*Schlie�en der Datenbankverbindung*/
    sqlite3_close(db_handle);
    return 0;
}
