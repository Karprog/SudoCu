#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BestenlisteSchreiben.h"
#include "sqlite3.h"

#define _CRT_SECURE_NO_DEPRECATE 1
#define DATABASE_FILE "benutzerverwaltung.sqlite3"



/*******************************************************************
int schreibeErgebnisInDb(int iNutzerId, char *cSchwierigkeitsgrad,
                         int iPunktzahl, int iZeit)
Übergabeparameter: int iNutzerId, char *cSchwierigkeitsgrad,
                    int iPunktzahl, int iZeit
Rückgabewerte: 0 oder -1 (-1 bei SQL-Fehler)
Schreibt die Nutzerdaten in die Datenbank. Wenn dies
gelingt, wird dem User angegeben, dass der Registrierungsvorgang
erfolgreich war. Wenn nicht, wird eine Fehlermeldung ausgegeben.
********************************************************************/
int schreibeErgebnisInDb(int iNutzerId, char *cSchwierigkeitsgrad,
                         int iPunktzahl, int iZeit)
{
    /*Variablendeklaration*/
    sqlite3 *db_handle;
    int iRc;
    int iControl;
    float fPunkteProZeit = berechnePunkteProMinute(iPunktzahl, iZeit);
    char* cSql;
    char* cErrormsg;

    /*Öffnen der Datenbankverbindung*/
    iRc = sqlite3_open(DATABASE_FILE, &db_handle);

    /*Query zum Schreiben der Nutzerdaten in die Datenbank*/
    cSql = sqlite3_mprintf("INSERT INTO bestenliste (benutzerId, "\
                          "schwierigkeitsgrad, punktzahl, zeit, punkteProZeit)"\
                          " VALUES ('%d', '%s', '%d', '%d', '%f')",
                        iNutzerId, cSchwierigkeitsgrad, iPunktzahl, iZeit,
                        fPunkteProZeit);

    /*Ausführen der Query auf der Datenbank*/
    iControl = sqlite3_exec(db_handle, cSql, NULL, NULL, &cErrormsg);

    /*Fehlermeldung bei fehlgeschlagener Ausführung,
    Freigabe der Verbindungsressourcen*/
    if (iRc != SQLITE_OK || iControl != 0) {
        printf("SQL-Fehler: %s\n", cErrormsg);
		sqlite3_free(cErrormsg);
		return -1;
    }

    /*Schließen der Datenbankverbindung*/
    sqlite3_close(db_handle);
    return 0;
}

/********************************************************
float berechnePunkteProMinute(int iPunktzahl, int iZeit)
Übergabewerte: int iPunktzahl, int iZeit
Rückgabewert: float fPunkteProMinute
Berechnet die Punkte, die durchschnittlich pro Minute
erreicht wurden aus der absoluten Punktzahl und der Zeit.
********************************************************/
float berechnePunkteProMinute(int iPunktzahl, int iZeit)
{
    /*Deklaration lokaler Variablen*/
    float fMinute, fSekunde;
    float fFaktor, fPunkteProMinute;

    /*Berechnung der für die Berechnung der durchschnittlichen Punktzahl
      benötigten Zwischenwerte.*/
    fMinute = iZeit/60;
    fSekunde = iZeit%60;
    fFaktor = fMinute + (fSekunde/60);
    /*Berechnung der durchschnittlichen Punktzahl*/
    fPunkteProMinute = (float) (iPunktzahl)/fFaktor;

    return fPunkteProMinute;
}
