#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

#define _CRT_SECURE_NO_DEPRECATE 1
#define DATABASE_FILE "benutzerverwaltung.sqlite3"

/*Schreibt die Nutzerdaten in die Datenbank. Wenn dies
gelingt, wird dem User angegeben, dass der Registrierungsvorgang
erfolgreich war. Wenn nicht, wird eine Fehlermeldung ausgegeben.*/
int mainTestmain(void)
{
    /*Variablendeklaration*/
    sqlite3 *db_handle;
    int rc;
    int control;
    char* sql;
    char* errormsg;
    char nutzername[30] = "spfleid";
    char passwort[20] = "abcdefg";

    /*Öffnen der Datenbankverbindung*/
    rc = sqlite3_open(DATABASE_FILE, &db_handle);

    /*Query zum Schreiben der Nutzerdaten in die Datenbank*/
    sql = sqlite3_mprintf("INSERT INTO nutzerdaten (nutzername, passwort) "\
                          "VALUES ('%s', '%s')",
                          nutzername, passwort);

    printf(sql);

    /*Ausführen der Query auf der Datenbank*/
    control = sqlite3_exec(db_handle, sql, NULL, NULL, &errormsg);
    printf("\n%d\n", control);

    /*Fehlermeldung bei fehlgeschlagener Ausführung,
    Freigabe der Verbindungsressourcen*/
    if (rc != SQLITE_OK) {
        printf("SQL-Fehler: %s\n", errormsg);
		sqlite3_free(errormsg);
		return -1;
    }
    else {
        printf(
               "\nSie wurden in das System aufgenommen und koennen "
               );
        printf(
               "sich nun mit Ihren Zugangsdaten anmelden\n"
               );
    }

    sqlite3_close(db_handle);
    system("pause");
    return 0;
}
