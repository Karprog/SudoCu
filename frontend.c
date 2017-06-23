/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Autoren: Stefanie Pfleiderer, Robin Kitzelmann, Burhan Karaca, Pascal     *
 *          Scheufens, Janik Busch                                           *
 * Datum:   23.06.2017                                                       *
 * Name:    SudoCu                                                           *
 * Version: 1.4                                                              *
 * Compiler:GNU                                                              *
 * Beschreibung:                                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BestenlisteLesen.h"
#include "BestenlisteSchreiben.h"
#include "LeseNutzer.h"

//Funktions-Prototypen
char Login();
char Hauptmenue();
char Bestenliste();
char Schnellstart();
char Schwierigkeit();


int Anmelden();
int Registrieren();

//Globalevariable für den Nutzernnamen, welcher überall angezeigt wird.
char NUTZERNAME[40];

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: mainFrontend()                                                  *
 * Parameter: none                                                           *
 * Rückgabewert: none                                                        *
 * Beschreibung: Startpunkt des Frontends, von hier aus wird das Hauptmenue  *
 *               gestartet.                                                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int mainFrontend()
{
    //Aufruf des Hauptmenues
    Hauptmenue();
    return 0;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Hauptmenue()                                                    *
 * Parameter: none                                                           *
 * Rückgabewert: char auswahl                                                *
 * Beschreibung: Diese Funktion stellt das Grafische Hauptmenue dar und fängt*
 *               nutzereigaben ab, um sich in der Menue Struktur zu bewegen  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char Hauptmenue()
{
        //Variablen Deklaration
        char cAuswahl;
        int iBleib;

        do
        {
        iBleib=0;
            //Ausgabe des Menues
            system("cls");
            printf("\n");
            printf(" SudoCu Version 4.4Alpha\n\n\n");
            printf("\n\n                                                                                                                    Steuerung:  \n");
            printf("\n");
            printf(" Das Ziel ist es, die leeren                                                                                          0 = Kugelschreiber\n");
            printf(" Zellen im Spielfeld mit den                                         SudoCo!                                          1 = Bleistift\n");
            printf(" Ziffern 1 bis 9 wie folgt                                                                                            2 = Loesung Position\n");
            printf(" auszufuellen.                                                                                                        3 = Kanidaten anzeigen\n");
            printf("                                                                    a. Login                                         \n");
            printf(" -In jeder Spalte kommt jede                                                                                          B = Bestenliste\n");
            printf("  Zahl nur einmal vor                                            b. Schnellstart                                      X = Zurueck/Spiel abbrechen\n");
            printf("                                                                                                                      Q = Schliessen\n");
            printf(" -In jeder Zeile kommt jede                                       c. Bestenliste                                     \n");
            printf("  Zahl nur einmal vor\n");
            printf("\n");
            printf(" -In jedem 3 x 3 Quadranten\n");
            printf("  kommt jede Zahl nur einmal\n");
            printf("  vor.");
            printf(" \n\n\n");

            //Bentzer eingabe für weitere Menues
            scanf("%c", &cAuswahl);

        //Hier wird entschieden welche Aktion der User ausführen möchte.
        switch(cAuswahl)
        {
            //Ruft das Menue für Anmeldung und Registrierung auf
            case 'a':
                Login();
                break;
            case 'b':
                //Setzt den Nutzernamen für Gastspieler ohne Anmeldung
                strcpy(NUTZERNAME,"Gast");
                //öffnet das Schwierigkeitenmenue
                Schwierigkeit();
                break;
            case 'c':
                //zeigt die Bestenliste an
                Bestenliste(0);
                break;
            case 'x':
                //beendet das Programm
                exit(0);
                break;
            default:
                break;
        }

                //Die While Schleife lässt den nutzer solange eingaben machen bis ein
        //gültiger Wert eingegeben wurde.
        }while (iBleib==0);

        //Rückgabe der User Auswahl
        return cAuswahl;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Login()                                                         *
 * ParC:\VS\ansiC\SudoCu\BestenlisteSchreibenUnit.cameter: none                                                           *
 * Rückgabewert: char auswahl                                                *
 * Beschreibung: Diese Funktion stellt das Login menue dar und fängt         *
 *               nutzereigaben ab, um sich in der Menue Struktur zu bewegen  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char Login()
{
    //Variablen Deklaration
    char iAuswahl;
    int iBleib;

    do
    {
        iBleib=0;
        //Ausgabe des Menues
        system("cls");
        printf("\n");
        printf(" SudoCu Version 4.4Alpha\n\n\n");
        printf("\n\n                                                        "\
               "                                                            "\
               "Steuerung:  \n");
        printf("\n");
        printf(" Das Ziel ist es, die leeren                                                                                          0 = Kugelschreiber\n");
        printf(" Zellen im Spielfeld mit den                                          Login                                           1 = Bleistift\n");
        printf(" Ziffern 1 bis 9 wie folgt                                                                                            2 = Loesung Position\n");
        printf(" auszufuellen.                                                                                                        3 = Kanidaten anzeigen\n");
        printf("                                                                    a. Anmelden                                      \n");
        printf(" -In jeder Spalte kommt jede                                                                                          B = Bestenliste\n");
        printf("  Zahl nur einmal vor                                             b. Registrieren                                     X = Zurueck/Spiel abbrechen\n");
        printf("                                                                                                                      Q = Schliessen\n");
        printf(" -In jeder Zeile kommt jede                                                                                          \n");
        printf("  Zahl nur einmal vor\n");
        printf("\n");
        printf(" -In jedem 3 x 3 Quadranten\n");
        printf("  kommt jede Zahl nur einmal\n");
        printf("  vor.");
        printf(" \n\n\n");

        //Bentzer eingabe für weitere Menues
        scanf("%c", &iAuswahl);



        //Hier wird entschieden welche Aktion der User ausführen möchte.
        switch(iAuswahl)
        {
            case 'a':
                //Anmelden wenn ein Account vorhanden ist
                Anmelden();
                break;
            case 'b':
                //Registrieren falls kein Account vorhanden ist
               Registrieren();
                break;
            case 'x':
                //Registrieren falls kein Account vorhanden ist
               iBleib = 1;
                break;

            default:
                break;
        }
    //Die While Schleife lässt den nutzer solange eingaben machen bis ein
    //gültiger Wert eingegeben wurde.
    }while(iBleib == 0);
    //Rückgabe der User Auswahl
    return iAuswahl;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Anmelden()                                                      *
 * Parameter: none                                                           *
 * Rückgabewert: int 0                                                       *
 * Beschreibung: Diese Funktion stellt das Anmelde menue dar und ermöglicht  *
 *               das Anmelden.                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int Anmelden()
{
    //Variablen Deklaration
    char cUsername[40];
    char cPasswort[40];
    int i = 0;

    do
    {
        nutzerId=NULL;
        //Ausgabe des Menues
        system("cls");
        printf("\n");
        printf(" SudoCu Version 4.4Alpha\n\n\n");
        printf("\n\n                                                                                                                    Steuerung:  \n");
        printf("\n");
        printf(" Das Ziel ist es, die leeren                                                                                          0 = Kugelschreiber\n");
        printf(" Zellen im Spielfeld mit den                                         Anmeldung                                        1 = Bleistift\n");
        printf(" Ziffern 1 bis 9 wie folgt                                                                                            2 = Loesung Position\n");
        printf(" auszufuellen.                                                                                                        3 = Kanidaten anzeigen\n");
        printf("                                                                 Geben Sie erst Name                                  \n");
        printf(" -In jeder Spalte kommt jede                                                                                          B = Bestenliste\n");
        printf("  Zahl nur einmal vor                                           und dann Passwort ein                                 X = Zurueck/Spiel abbrechen\n");
        printf("                                                                                                                      Q = Schliessen\n");
        printf(" -In jeder Zeile kommt jede                                                                                           \n");
        printf("  Zahl nur einmal vor\n");
        printf("\n");
        printf(" -In jedem 3 x 3 Quadranten\n");
        printf("  kommt jede Zahl nur einmal\n");
        printf("  vor.");
        printf(" \n\n\n");

        //Bentzer eingabe für das Anmelden
        printf(" Benutzername: ");
        scanf("%s", &cUsername);

        printf(" Passwort: ");
        scanf("%s", &cPasswort);

        //Aufruf der Datenbankfunktion und speichern des Rückgabe wertes
        leseNutzerdatenVonDb(cUsername, cPasswort);

    //der Nutzer kann sich solange veruschen anzumelden bis es geklappt hat
    }while(!nutzerId);

    //speichern des Nutzernamens in die Global Variable NUTZERNAME
    strcpy(NUTZERNAME, cUsername);

    //Weiterleitung in die Auswahl der Schwierigkeitsstufe
    Schwierigkeit();

    return 0;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Registrieren()                                                  *
 * Parameter: none                                                           *
 * Rückgabewert: int 0                                                       *
 * Beschreibung: Diese Funktion stellt das Anmelde menue dar und ermöglicht  *
 *               das Registrieren.                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int Registrieren()
{
    //Variablen Deklaration
    char cUsername[40];
    char cPasswort[40];
    int i = 0;

    //Ausgabe des Menues
    system("cls");
    printf("\n");
    printf(" SudoCu Version 4.4Alpha\n\n\n");
    printf("\n\n                                                                                                                    Steuerung:  \n");
    printf("\n");
    printf(" Das Ziel ist es, die leeren                                                                                          0 = Kugelschreiber\n");
    printf(" Zellen im Spielfeld mit den                                        Registrierung                                     1 = Bleistift\n");
    printf(" Ziffern 1 bis 9 wie folgt                                                                                            2 = Loesung Position\n");
    printf(" auszufuellen.                                                                                                        3 = Kanidaten anzeigen\n");
    printf("                                                                 Geben Sie erst Name                                  \n");
    printf(" -In jeder Spalte kommt jede                                                                                          B = Bestenliste\n");
    printf("  Zahl nur einmal vor                                           und dann Passwort ein                                 X = Zurueck/Spiel abbrechen\n");
    printf("                                                                                                                      Q = Schliessen\n");
    printf(" -In jeder Zeile kommt jede                                                                                           \n");
    printf("  Zahl nur einmal vor\n");
    printf("\n");
    printf(" -In jedem 3 x 3 Quadranten\n");
    printf("  kommt jede Zahl nur einmal\n");
    printf("  vor.");
    printf(" \n\n\n");

    //Bentzer eingaben für das Registrieren
    printf(" Benutzername: ");
    scanf("%s", &cUsername);


    printf(" Passwort: ");
    scanf("%s", &cPasswort);

    //ruft die Datenbankfunktion auf um in die db zu schreiben
    //mainNutzerVonDb(cUsername, cPasswort);
    schreibeNutzerdatenInDb(cUsername, cPasswort);

    // SPielstart
    Schwierigkeit();
    return 0;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Bestenliste()                                                   *
 * Parameter: int iHelfer                                                    *
 * Rückgabewert: char auswahl                                                *
 * Beschreibung: Diese Funktion stellt die Bestenliste dar                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char Bestenliste()
{
    //Variablen Deklaration
    char cAuswahl;

    selectBestenlisteNachSchwierigkeitsgrad("Leicht");
    selectBestenlisteNachSchwierigkeitsgrad("Mittel");
    selectBestenlisteNachSchwierigkeitsgrad("Schwer");

    //Ausgabe des Menues
    system("cls");
    printf("\n");
    printf(" SudoCu Version 4.4Alpha\n\n\n");
    printf("                                                                   Bestenliste                                         \n");
    printf("\n\n\n");
    printf("                         Leicht                                       Mittel                                       Schwer                         \n");
    printf("  ________________________________________________________________________________________________________________________________________________\n\n");
    printf("                     %s|%s|%s|%s                                  %s|%s|%s|%s                                  %s|%s|%s|%s\n",
           bestenliste.cLeicht[0][0], bestenliste.cLeicht[0][1], bestenliste.cLeicht[0][2], bestenliste.cLeicht[0][3],
           bestenliste.cMittel[0][0], bestenliste.cMittel[0][1], bestenliste.cMittel[0][2], bestenliste.cMittel[0][3],
           bestenliste.cSchwer[0][0], bestenliste.cSchwer[0][1], bestenliste.cSchwer[0][2], bestenliste.cSchwer[0][3]);
   printf("                     %s|%s|%s|%s                                  %s|%s|%s|%s                                   %s|%s|%s|%s\n",
           bestenliste.cLeicht[1][0], bestenliste.cLeicht[1][1], bestenliste.cLeicht[1][2], bestenliste.cLeicht[1][3],
           bestenliste.cMittel[1][0], bestenliste.cMittel[1][1], bestenliste.cMittel[1][2], bestenliste.cMittel[1][3],
           bestenliste.cSchwer[1][0], bestenliste.cSchwer[1][1], bestenliste.cSchwer[1][2], bestenliste.cSchwer[1][3]);
   printf("                     %s|%s|%s|%s                                  %s|%s|%s|%s                                  %s|%s|%s|%s\n",
           bestenliste.cLeicht[2][0], bestenliste.cLeicht[2][1], bestenliste.cLeicht[2][2], bestenliste.cLeicht[2][3],
           bestenliste.cMittel[2][0], bestenliste.cMittel[2][1], bestenliste.cMittel[2][2], bestenliste.cMittel[2][3],
           bestenliste.cSchwer[2][0], bestenliste.cSchwer[2][1], bestenliste.cSchwer[2][2], bestenliste.cSchwer[2][3]);
   printf("                     %s|%s|%s|%s                                  %s|%s|%s|%s                                   %s|%s|%s|%s\n",
           bestenliste.cLeicht[3][0], bestenliste.cLeicht[3][1], bestenliste.cLeicht[3][2], bestenliste.cLeicht[3][3],
           bestenliste.cMittel[3][0], bestenliste.cMittel[3][1], bestenliste.cMittel[3][2], bestenliste.cMittel[3][3],
           bestenliste.cSchwer[3][0], bestenliste.cSchwer[3][1], bestenliste.cSchwer[3][2], bestenliste.cSchwer[3][3]);
   printf("                     %s|%s|%s|%s                                  %s|%s|%s|%s                                   %s|%s|%s|%s\n",
           bestenliste.cLeicht[4][0], bestenliste.cLeicht[4][1], bestenliste.cLeicht[4][2], bestenliste.cLeicht[4][3],
           bestenliste.cMittel[4][0], bestenliste.cMittel[4][1], bestenliste.cMittel[4][2], bestenliste.cMittel[4][3],
           bestenliste.cSchwer[4][0], bestenliste.cSchwer[4][1], bestenliste.cSchwer[4][2], bestenliste.cSchwer[4][3]);
    printf(" \n\n\n");

    //Bentzer eingabe für rückführung
    scanf("%c", &cAuswahl);

    system("pause");

    return cAuswahl;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Schwierigkeit()                                                 *
 * Parameter: none                                                           *
 * Rückgabewert: char auswahl                                                *
 * Beschreibung: Diese Funktion stellt die auswahl der Schwierigkeit dar     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char Schwierigkeit()
{
    //Variablen Deklaration
    char cAuswahl;
    int iBleib;

    do
    {
        iBleib = 0;
        //Ausgabe des Menues
        system("cls");
        printf("\n");
        printf(" SudoCu Version 4.4Alpha\n\n\n");
        printf(" Benutzername: %s", NUTZERNAME);
        printf("\n\n                                                                                                                    Steuerung:  \n");
        printf("\n");
        printf(" Das Ziel ist es, die leeren                                                                                          0 = Kugelschreiber\n");
        printf(" Zellen im Spielfeld mit den                                     Schwierigkeitsgrad                                   1 = Bleistift\n");
        printf(" Ziffern 1 bis 9 wie folgt                                                                                            2 = Loesung Position\n");
        printf(" auszufüllen.                                                                                                         3 = Kanidaten anzeigen\n");
        printf("                                                                     1. Leicht                                        \n");
        printf(" -In jeder Spalte kommt jede                                                                                          B = Bestenliste\n");
        printf("  Zahl nur einmal vor                                                2. Mittel                                        X = Zurueck/Spiel abbrechen\n");
        printf("                                                                                                                      Q = Schliessen\n");
        printf(" -In jeder Zeile kommt jede                                          3. Schwer                                        \n");
        printf("  Zahl nur einmal vor\n");
        printf("\n");
        printf(" -In jedem 3 x 3 Quadranten\n");
        printf("  kommt jede Zahl nur einmal\n");
        printf("  vor.");
        printf(" \n\n\n");

        //Bentzer eingabe für rückführung
        scanf("%c", &cAuswahl);


        //Hier wird entschieden welche Aktion der User ausführen möchte.
        switch(cAuswahl)
        {
            //übergeben der Schwiergikeitsstufe an die Spiellogik
            case '1':
                Logik(1);
                break;
            case '2':
                Logik(2);
                break;
            case '3':
                Logik(3);
                break;
            case 'x':
                //Zurueck zum Hauptmenue
                iBleib = 1;
                break;
            default:
                break;
        }
    //Die While Schleife lässt den nutzer solange eingaben machen bis ein
    //gültiger Wert eingegeben wurde.
    }while(iBleib == 0);

    return cAuswahl;
}
