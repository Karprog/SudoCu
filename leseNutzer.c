#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "LeseNutzer.h"

#define _CRT_SECURE_NO_DEPRECATE 1
#define DATABASE_FILE "benutzerverwaltung.sqlite3"



static int callback (void *data, int argc, char **argv, char **colName)
{
    printf("\n%s\n", argv[0]);
    nutzerId = atoi(argv[0]);
    return 0;
}


/*Schreibt die Nutzerdaten in die Datenbank. Wenn dies
gelingt, wird dem User angegeben, dass der Registrierungsvorgang
erfolgreich war. Wenn nicht, wird eine Fehlermeldung ausgegeben.*/
char leseNutzerdatenVonDb(char* nutzername, char* passwort )
{
    /*Variablendeklaration*/
    sqlite3 *db_handle;
    int rc;
    int control;
    char* sql;
    char* errormsg;

    /*Öffnen der Datenbankverbindung*/
    rc = sqlite3_open(DATABASE_FILE, &db_handle);

    if (rc == 0) {
        /*Query zum Schreiben der Nutzerdaten in die Datenbank*/
        sql = sqlite3_mprintf("SELECT id FROM nutzerdaten WHERE benutzername ="\
                              " '%s' AND passwort = '%s';",
                              nutzername, passwort);
    }
    /*Ausführen der Query auf der Datenbank*/
    control = sqlite3_exec(db_handle, sql, callback, NULL, &errormsg);
    /*Fehlermeldung bei fehlgeschlagener Ausführung,
    Freigabe der Verbindungsressourcen*/
    if (rc != SQLITE_OK || control != 0) {
        printf("SQL-Fehler: %s\n", errormsg);
		sqlite3_free(errormsg);
		return -1;
    }

    sqlite3_close(db_handle);
    return 0;
}
