#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

#define _CRT_SECURE_NO_DEPRECATE 1
#define DATABASE_FILE "benutzerverwaltung.sqlite3"

/*Schreibt die Nutzerdaten in die Datenbank. Wenn dies
gelingt, wird dem User angegeben, dass der Registrierungsvorgang
erfolgreich war. Wenn nicht, wird eine Fehlermeldung ausgegeben.*/
int main(void)
{
    /*Variablendeklaration*/
    sqlite3 *db_handle;
    int rc;
    int control;
    char* sql;
    char* errormsg;
    int nutzerId = 12;
    char schwierigkeitsgrad[20] = "Mittel";
    int punktzahl = 123;
    char zeit[10] = "12:45";

    /*�ffnen der Datenbankverbindung*/
    rc = sqlite3_open(DATABASE_FILE, &db_handle);

    if (rc == 0) {
        /*Query zum Schreiben der Nutzerdaten in die Datenbank*/
        sql = sqlite3_mprintf("INSERT INTO bestenliste (benutzerId, schwierigkeitsgrad, punktzahl, zeit) VALUES ('%s', '%s', '%s', '%s')",
                            nutzerId, schwierigkeitsgrad, punktzahl, zeit);
    }
    else {
        printf("Es konnte keine Verbindung zur Datenbank aufgebaut werden.");
    }

    /*Ausf�hren der Query auf der Datenbank*/
    control = sqlite3_exec(db_handle, sql, NULL, NULL, &errormsg);

    /*Fehlermeldung bei fehlgeschlagener Ausf�hrung,
    Freigabe der Verbindungsressourcen*/
    if (rc != SQLITE_OK || control != 0) {
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