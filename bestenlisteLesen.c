#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "BestenlisteLesen.h"

#define DATABASE_FILE "benutzerverwaltung.sqlite3"
#define _CRT_SECURE_NO_DEPRECATE 1


/*********************************************************************
static int callback(void* data, int argc, char** argv, char **colName)
�bergabeparameter: void* data, int argc, char** argv, char **colName
R�ckgabeparameter: 0
Die Funktion wird f�r jeden von sqli3_exec() zur�ckgegebenen Datensatz
aufgerufen. Die �bergabeparameter enthalten die Daten, die durch die
Datenbankabfrage zur�ckgegeben werden. Diese werden durchlaufen und
durch das Abspeichern in einer Struktur den anderen Funktionen zur
Verf�gung gestellt.
*********************************************************************/
static int callback(void* data, int argc, char** argv, char **colName)
{
    /*Deklaration lokaler Variablen*/
    int j, i;
    float fPunkteProMinute;

    /*Schleife �ber das Array der R�ckgabewerte und speicher der Werte*/
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
�bergabeparameter: char cSchwierigkeitsgrad
R�ckgabeparameter: 0
�ffnet die Datenbankdatei und f�hrt eine Abfrage aus, die die Datens�tze
der f�nf besten Spieler aus der Datenbank auslie�t.
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

    /*�ffnen der Datenbankdatei*/
    iRc = sqlite3_open(DATABASE_FILE, &db_handle);

    /*Erstellen der Datenbankabfrage*/
    cSql = sqlite3_mprintf("SELECT nd.benutzername, bl.punkteProZeit, "\
                           "bl.punktzahl, bl.zeit, bl.schwierigkeitsgrad " \
                          " FROM nutzerdaten nd JOIN bestenliste bl ON "\
                          " nd.id = bl.benutzerId WHERE schwierigkeitsgrad = " \
                          "'%s' ORDER BY bl.punktzahl DESC",
                          cSchwierigkeitsgrad);

    /*Ausf�hren der Datenbankabfrage*/
    iControl = sqlite3_exec(db_handle, cSql, callback,(void*)data , &cErrormsg);

    /*Abfrage, ob bei der Ausf�hrung der Datenbankoperationen Fehler auf-
      getreten sind. Wenn dies der Fall ist, wird eine Fehlermeldung aus-
      gegeben und die von der Datenbankverbindung belegten Ressourcen frei-
      gegeben.*/
    if (iRc != SQLITE_OK || iControl != 0) {
        printf("SQL-Fehler: %s\n", cErrormsg);
        sqlite3_free(cErrormsg);
        return(-1);
    }

    /*Schlie�en der Datenbankverbindung*/
    sqlite3_close(db_handle);
    return 0;
}

/**********************************************************
int berechnePunkteProMinuteLesen(int iPunktzahl, int iZeit)
�bergabeparameter: int iPunktzahl, int iZeit
R�ckgabeparameter: fPunkteProMinute
Berechnet die Punkte, die durchschnittlich pro Minute
erreicht wurden.
**********************************************************/
int berechnePunkteProMinuteLesen(int iPunktzahl, int iZeit)
{
    /*Deklaration lokaler Variablen*/
    float fMinute, fSekunde;
    float fFaktor, fPunkteProMinute;

    /*F�r die Berechnung der durchschnittlichen Punktzahl
    ben�tigte Berechnungen*/
    fMinute = iZeit/60;
    fSekunde = iZeit%60;
    fFaktor = fMinute + (fSekunde/60);
    /*Berechnung der durchschnittlichen Punktzahl w�hrend
    der Spielzeit*/
    fPunkteProMinute = (float) (iPunktzahl)/fFaktor;

    return fPunkteProMinute;
}


