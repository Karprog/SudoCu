#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

#define _CRT_SECURE_NO_DEPRECATE 1
#define DATABASE_FILE "benutzerverwaltung.sqlite3"
float berechnePunkteProMinute(int punkte, int zeit);


/*******************************************************************
Schreibt die Nutzerdaten in die Datenbank. Wenn dies
gelingt, wird dem User angegeben, dass der Registrierungsvorgang
erfolgreich war. Wenn nicht, wird eine Fehlermeldung ausgegeben.
********************************************************************/
int schreibeErgebnisInDb(int nutzerId, char *schwierigkeitsgrad,
                         int punktzahl, int zeit)
{
    /*Variablendeklaration*/
    sqlite3 *db_handle;
    int rc;
    int control;
    float fPunkteProZeit = berechnePunkteProMinute(punktzahl, zeit);
    char* sql;
    char* errormsg;

    /*Öffnen der Datenbankverbindung*/
    rc = sqlite3_open(DATABASE_FILE, &db_handle);

    /*Query zum Schreiben der Nutzerdaten in die Datenbank*/
    sql = sqlite3_mprintf("INSERT INTO bestenliste (benutzerId, "\
                          "schwierigkeitsgrad, punktzahl, zeit, punkteProZeit) "\
                          "VALUES ('%d', '%s', '%d', '%d', '%f')",
                        nutzerId, schwierigkeitsgrad, punktzahl, zeit, fPunkteProZeit);

    /*Ausführen der Query auf der Datenbank*/
    control = sqlite3_exec(db_handle, sql, NULL, NULL, &errormsg);

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

float berechnePunkteProMinute(int iPunktzahl, int iZeit)
{
    float fMinute, fSekunde;
    float fFaktor, fPunkteProMinute;

    fMinute = iZeit/60;
    fSekunde = iZeit%60;
    fFaktor = fMinute + (fSekunde/60);
    fPunkteProMinute = (float) (iPunktzahl)/fFaktor;

    return fPunkteProMinute;
}
