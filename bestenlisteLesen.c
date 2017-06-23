#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "BestenlisteLesen.h"

#define DATABASE_FILE "benutzerverwaltung.sqlite3"
#define _CRT_SECURE_NO_DEPRECATE 1


/*********************************************************************
static int callback(void* data, int argc, char** argv, char **colName)
Übergabeparameter: void* data, int argc, char** argv, char **colName
Rückgabeparameter: 0
Die Funktion wird für jeden von sqli3_exec() zurückgegebenen Datensatz
aufgerufen. Die Übergabeparameter enthalten die Daten, die durch die
Datenbankabfrage zurückgegeben werden. Diese werden durchlaufen und
durch das Abspeichern in einer Struktur den anderen Funktionen zur
Verfügung gestellt.
*********************************************************************/
static int callback(void* data, int argc, char** argv, char **colName)
{
    /*Deklaration lokaler Variablen*/
    int j, i;
    float fPunkteProMinute;

    /*Schleife über das Array der Rückgabewerte und speicher der Werte*/
    for (j = 0; j < argc/5; j++) {
        if(!strcmp(argv[(j*5)+4], "Leicht")){
            for(i=0; i<4; i++){
                bestenliste.cLeicht[j][i] = argv[(j*5)+i];
            }
        }
        if(!strcmp(argv[(j*5)+4], "Mittel")){
            for(i=0; i<4; i++){
                bestenliste.cMittel[j][i] = argv[(j*5)+i];
            }
        }
        if(!strcmp(argv[(j*5)+4], "Schwer")){
            for(i=0; i<4; i++){
                bestenliste.cSchwer[j][i] = argv[(j*5)+i];
            }
        }
    }
    return 0;
}

/**********************************************************************
int selectBestenlisteNachSchwierigkeitsgrad(char *cSchwierigkeitsgrad)
Übergabeparameter: char cSchwierigkeitsgrad
Rückgabeparameter: 0
Öffnet die Datenbankdatei und führt eine Abfrage aus, die die Datensätze
der fünf besten Spieler aus der Datenbank ausließt.
***********************************************************************/
int selectBestenlisteNachSchwierigkeitsgrad(char *cSchwierigkeitsgrad)
{
    /*Deklaration lokaler Variablen*/
    sqlite3* db_handle;
    int iRc;
    int iControl;
    char* cSql;
    char *cErrormsg;
    char *data;

    /*Öffnen der Datenbankdatei*/
    iRc = sqlite3_open(DATABASE_FILE, &db_handle);

    /*Erstellen der Datenbankabfrage*/
    cSql = sqlite3_mprintf("SELECT nd.benutzername, bl.punkteProZeit, "\
                           "bl.punktzahl, bl.zeit, bl.schwierigkeitsgrad " \
                          " FROM nutzerdaten nd JOIN bestenliste bl ON "\
                          " nd.id = bl.benutzerId WHERE schwierigkeitsgrad = " \
                          "'%s' ORDER BY bl.punktzahl DESC",
                          cSchwierigkeitsgrad);

    /*Ausführen der Datenbankabfrage*/
    iControl = sqlite3_exec(db_handle, cSql, callback,(void*)data , &cErrormsg);

    /*Abfrage, ob bei der Ausführung der Datenbankoperationen Fehler auf-
      getreten sind. Wenn dies der Fall ist, wird eine Fehlermeldung aus-
      gegeben und die von der Datenbankverbindung belegten Ressourcen frei-
      gegeben.*/
    if (iRc != SQLITE_OK || iControl != 0) {
        printf("SQL-Fehler: %s\n", cErrormsg);
        sqlite3_free(cErrormsg);
        return(-1);
    }

    /*Schließen der Datenbankverbindung*/
    sqlite3_close(db_handle);
    return 0;
}

/**********************************************************
int berechnePunkteProMinuteLesen(int iPunktzahl, int iZeit)
Übergabeparameter: int iPunktzahl, int iZeit
Rückgabeparameter: fPunkteProMinute
Berechnet die Punkte, die durchschnittlich pro Minute
erreicht wurden.
**********************************************************/
int berechnePunkteProMinuteLesen(int iPunktzahl, int iZeit)
{
    /*Deklaration lokaler Variablen*/
    float fMinute, fSekunde;
    float fFaktor, fPunkteProMinute;

    /*Für die Berechnung der durchschnittlichen Punktzahl
    benötigte Berechnungen*/
    fMinute = iZeit/60;
    fSekunde = iZeit%60;
    fFaktor = fMinute + (fSekunde/60);
    /*Berechnung der durchschnittlichen Punktzahl während
    der Spielzeit*/
    fPunkteProMinute = (float) (iPunktzahl)/fFaktor;

    return fPunkteProMinute;
}


