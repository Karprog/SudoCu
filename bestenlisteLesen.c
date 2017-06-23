#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "BestenlisteLesen.h"

#define DATABASE_FILE "benutzerverwaltung.sqlite3"
#define _CRT_SECURE_NO_DEPRECATE 1



static int callback(void* data, int argc, char** argv, char **colName)
{
    int j, i;
    float fPunkteProMinute;

    //*
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
    //*/
    return 0;
}

int selectBestenlisteNachSchwierigkeitsgrad(char *schwirigkeitsgrad)
{
    sqlite3* db_handle;
    int rc;
    int control;
    char* sql;
    char *errormsg;
    char *data;

    rc = sqlite3_open(DATABASE_FILE, &db_handle);

    sql = sqlite3_mprintf("SELECT nd.benutzername, bl.punkteProZeit, bl.punktzahl, bl.zeit, bl.schwierigkeitsgrad " \
                          " FROM nutzerdaten nd JOIN bestenliste bl ON "\
                          " nd.id = bl.benutzerId WHERE schwierigkeitsgrad = '%s'" \
                          " ORDER BY bl.punktzahl DESC",
                          schwirigkeitsgrad);

    control = sqlite3_exec(db_handle, sql, callback, (void*)data , &errormsg);

    if (rc != SQLITE_OK || control != 0) {
        printf("SQL-Fehler: %s\n", errormsg);
        sqlite3_free(errormsg);
        return(-1);
    }

    sqlite3_close(db_handle);
    return 0;
}

int berechnePunkteProMinuteLesen(int iPunktzahl, int iZeit)
{
    float iMinute, iSekunde;
    float fFaktor, iPunkteProMinute;

    iMinute = iZeit/60;
    iSekunde = iZeit%60;
    fFaktor = iMinute + (iSekunde/60);
    iPunkteProMinute = (float) (iPunktzahl)/fFaktor;

    return iPunkteProMinute;
}


