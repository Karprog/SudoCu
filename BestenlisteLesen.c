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
    static int iL=0, iM=0, iS=0;

    //*
    if(!strcmp(argv[4], "1")){
        strcpy(leicht.platz[iL].cName, argv[0]);
        strcpy(leicht.platz[iL].cPs, argv[1]);
        strcpy(leicht.platz[iL].cP, argv[2]);
        strcpy(leicht.platz[iL].cZ, argv[3]);
        if(iL<5){iL++;}
        if(iL==5){iL=0;}
    }
    if(!strcmp(argv[4], "2")){
        strcpy(mittel.platz[iM].cName, argv[0]);
        strcpy(mittel.platz[iM].cPs, argv[1]);
        strcpy(mittel.platz[iM].cP, argv[2]);
        strcpy(mittel.platz[iM].cZ, argv[3]);
        if(iM<5){iM++;}
        if(iM==5){iM=0;}
    }
    if(!strcmp(argv[4], "3")){
        strcpy(schwer.platz[iS].cName, argv[0]);
        strcpy(schwer.platz[iS].cPs, argv[1]);
        strcpy(schwer.platz[iS].cP, argv[2]);
        strcpy(schwer.platz[iS].cZ, argv[3]);
        if(iS<5){iS++;}
        if(iS==5){iS=0;}
    }
    //*/
    return 0;
}

int selectBestenlisteNachSchwierigkeitsgrad(int schwierigkeitsgrad)
{
    sqlite3* db_handle;
    int rc;
    int control;
    char* sql;
    char *errormsg;
    char *data;

    rc = sqlite3_open(DATABASE_FILE, &db_handle);

    sql = sqlite3_mprintf(
      "SELECT nd.benutzername, bl.punkteProZeit, bl.punktzahl"\
      ", bl.zeit, bl.schwierigkeitsgrad" \
      " FROM nutzerdaten nd JOIN bestenliste bl ON "\
      " nd.id = bl.benutzerId WHERE schwierigkeitsgrad = '%i'" \
      " ORDER BY bl.punkteProZeit DESC LIMIT 5",
      schwierigkeitsgrad);

    control = sqlite3_exec(db_handle, sql, callback, (void*)data , &errormsg);

    if (rc != SQLITE_OK || control != 0) {
        printf("SQL-Fehler: %s\n", errormsg);
        sqlite3_free(errormsg);
        return(-1);
    }

    sqlite3_close(db_handle);
    return 0;
}


