#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

#define _CRT_SECURE_NO_DEPRECATE 1
#define DATABASE_FILE "benutzerverwaltung.sqlite3"

int leseNutzerdaten(void);
int schreibeNutzerdatenInDb(char *nutzername, char *passwort);


int main()
{

    leseNutzerdaten();
    system("pause");
    return 0;
}

int leseNutzerdaten(void)
{
    char benutzername[128];
    char passwort[128];

    printf("Bitte Benutzernamen eingeben: ");
    fflush(stdin);
    scanf("%s", benutzername);

    printf("\nBitte Passwort eingeben: ");
    fflush(stdin);
    scanf("%s", passwort);

    schreibeNutzerdatenInDb(benutzername, passwort);
    return 0;
}

int schreibeNutzerdatenInDb(char *nutzername, char *passwort)
{
     /*Variablendeklaration*/
    sqlite3 *db_handle;
    int rc;
    int control;
    char* sql;
    char* errormsg;

    /*�ffnen der Datenbankverbindung*/
    rc = sqlite3_open(DATABASE_FILE, &db_handle);

    if (rc == 0) {
        /*Query zum Schreiben der Nutzerdaten in die Datenbank*/
        sql = sqlite3_mprintf("INSERT INTO nutzerdaten (nutzername, passwort) VALUES ('%s', '%s')",
                            nutzername, passwort);
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
    return 0;
}




