#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

#define _CRT_SECURE_NO_DEPRECATE 1
#define DATABASE_FILE "benutzerverwaltung.sqlite3"

/***************************************************************
int schreibeNutzerdatenInDb(char *cNutzerdaten, char *cPasswort)
Übergabeparameter: char *cNutzerdaten, char *cPasswort
Rückgabeparameter: 0 oder -1 (-1 wenn ein SQL-Fehler auf-
                    getreten ist)
Schreibt den Nutzernamen und das Passwort, die der Nutzer über
die Kommandozeile einliest, in die Datenbank. Im Erfolgsfall
bekommt der Nutzer eine Nachricht, dass er erfolgreich in das
System aufgenommen wurde, sonst eine Fehlermeldung.
***************************************************************/

int schreibeNutzerdatenInDb(char *cNutzername, char *cPasswort)
{
     /*Variablendeklaration*/
    sqlite3 *db_handle;
    int iRc;
    int iControl;
    char* cSql;
    char* cErrormsg;

    /*Öffnen der Datenbankverbindung*/
    iRc = sqlite3_open(DATABASE_FILE, &db_handle);

    if (iRc == 0) {
        /*Query zum Schreiben der Nutzerdaten in die Datenbank*/
        cSql = sqlite3_mprintf("INSERT INTO nutzerdaten (benutzername, " \
                              "passwort) VALUES ('%s', '%s')",
                            cNutzername, cPasswort);
    }
    /*Ausgabe zu Problemen beim Verbindungsaufbau zur Datenbank*/
    else {
        printf("Es konnte keine Verbindung zur Datenbank aufgebaut werden.");
    }

    /*Ausführen der Query auf der Datenbank*/
    iControl = sqlite3_exec(db_handle, cSql, NULL, NULL, &cErrormsg);

    /*Fehlermeldung bei fehlgeschlagener Ausführung,
    Freigabe der Verbindungsressourcen*/
    if (iRc != SQLITE_OK || iControl != 0) {
        printf("SQL-Fehler: %s\n", cErrormsg);
		sqlite3_free(cErrormsg);
		return -1;
    }
    /*Ausgabe der erfolgreichen Aufnahme in das System*/
    else {
        printf(
               "\nSie wurden in das System aufgenommen und koennen "
               );
        printf(
               "sich nun mit Ihren Zugangsdaten anmelden\n"
               );
    }
    /*Schließen der Datenbankverbindung*/
    sqlite3_close(db_handle);
    return 0;
}




