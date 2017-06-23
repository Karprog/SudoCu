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
�bergabeparameter: int iNutzerId, char *cSchwierigkeitsgrad,
                    int iPunktzahl, int iZeit
R�ckgabewerte: 0 oder -1 (-1 bei SQL-Fehler)
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

    /*�ffnen der Datenbankverbindung*/
    iRc = sqlite3_open(DATABASE_FILE, &db_handle);

    /*Query zum Schreiben der Nutzerdaten in die Datenbank*/
    cSql = sqlite3_mprintf("INSERT INTO bestenliste (benutzerId, "\
                          "schwierigkeitsgrad, punktzahl, zeit, punkteProZeit)"\
                          " VALUES ('%d', '%s', '%d', '%d', '%f')",
                        iNutzerId, cSchwierigkeitsgrad, iPunktzahl, iZeit,
                        fPunkteProZeit);

    /*Ausf�hren der Query auf der Datenbank*/
    iControl = sqlite3_exec(db_handle, cSql, NULL, NULL, &cErrormsg);

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

/********************************************************
float berechnePunkteProMinute(int iPunktzahl, int iZeit)
�bergabewerte: int iPunktzahl, int iZeit
R�ckgabewert: float fPunkteProMinute
Berechnet die Punkte, die durchschnittlich pro Minute
erreicht wurden aus der absoluten Punktzahl und der Zeit.
********************************************************/
float berechnePunkteProMinute(int iPunktzahl, int iZeit)
{
    /*Deklaration lokaler Variablen*/
    float fMinute, fSekunde;
    float fFaktor, fPunkteProMinute;

    /*Berechnung der f�r die Berechnung der durchschnittlichen Punktzahl
      ben�tigten Zwischenwerte.*/
    fMinute = iZeit/60;
    fSekunde = iZeit%60;
    fFaktor = fMinute + (fSekunde/60);
    /*Berechnung der durchschnittlichen Punktzahl*/
    fPunkteProMinute = (float) (iPunktzahl)/fFaktor;

    return fPunkteProMinute;
}
