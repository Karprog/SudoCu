#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Frontend.h"
#include "BestenlisteLesen.h"
#include "BestenlisteSchreiben.h"
#include "LeseNutzer.h"

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
    char cAuswahl;
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
        scanf("%c", &cAuswahl);

        //Hier wird entschieden welche Aktion der User ausführen möchte.
        switch(cAuswahl)
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
                //Zurück
                iBleib = 1;
                break;

            default:
                break;
        }
    //Die While Schleife lässt den nutzer solange eingaben machen bis ein
    //gültiger Wert eingegeben wurde.
    }while(iBleib == 0);
    //Rückgabe der User Auswahl
    return cAuswahl;
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
    int i = 0, iBleib;

    do
    {
        iBleib = 0;
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

        if(strcmp(cUsername,"x")==0 && strcmp(cPasswort,"x")==0){
            iBleib = 1;
        }

    //der Nutzer kann sich solange veruschen anzumelden bis es geklappt hat
    }while(!nutzerId && iBleib==0);

    if(nutzerId){
        //speichern des Nutzernamens in die Global Variable NUTZERNAME
        strcpy(NUTZERNAME, cUsername);

        //Weiterleitung in die Auswahl der Schwierigkeitsstufe
        Schwierigkeit();
    }

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
    int i = 0, iBleib;

    do{
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

        if(strcmp(cUsername,"x")==0 && strcmp(cPasswort,"x")==0){
            iBleib = 1;
        }

    }while(iBleib==0);

    if(!(strcmp(cUsername,"x")==0)){
        //ruft die Datenbankfunktion auf um in die db zu schreiben
        //mainNutzerVonDb(cUsername, cPasswort);
        schreibeNutzerdatenInDb(cUsername, cPasswort);

        strcpy(NUTZERNAME, cUsername);

        // SPielstart
        Schwierigkeit();
    }

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

    selectBestenlisteNachSchwierigkeitsgrad(1);
    selectBestenlisteNachSchwierigkeitsgrad(2);
    selectBestenlisteNachSchwierigkeitsgrad(3);

    //Ausgabe des Menues
    system("cls");
    printf("\n");
    printf(" SudoCu Version 4.4Alpha\n\n\n");
    printf("                                                                   Bestenliste                                         \n");
    printf("\n\n\n");
    printf("                         Leicht                                       Mittel                                       Schwer                         \n");
    printf("  ________________________________________________________________________________________________________________________________________________\n\n");
    printf("      %15s | %4s | %4s | %4s       %15s | %4s | %4s | %4s       %15s | %4s | %4s | %4s\n",
           leicht.platz[0].cName, leicht.platz[0].cPs, leicht.platz[0].cP, leicht.platz[0].cZ,
           mittel.platz[0].cName, mittel.platz[0].cPs, mittel.platz[0].cP, mittel.platz[0].cZ,
           schwer.platz[0].cName, schwer.platz[0].cPs, schwer.platz[0].cP, schwer.platz[0].cZ);
    printf("      %15s | %4s | %4s | %4s       %15s | %4s | %4s | %4s       %15s | %4s | %4s | %4s\n",
           leicht.platz[1].cName, leicht.platz[1].cPs, leicht.platz[1].cP, leicht.platz[1].cZ,
           mittel.platz[1].cName, mittel.platz[1].cPs, mittel.platz[1].cP, mittel.platz[1].cZ,
           schwer.platz[1].cName, schwer.platz[1].cPs, schwer.platz[1].cP, schwer.platz[1].cZ);
    printf("      %15s | %4s | %4s | %4s       %15s | %4s | %4s | %4s       %15s | %4s | %4s | %4s\n",
           leicht.platz[2].cName, leicht.platz[2].cPs, leicht.platz[2].cP, leicht.platz[2].cZ,
           mittel.platz[2].cName, mittel.platz[2].cPs, mittel.platz[2].cP, mittel.platz[2].cZ,
           schwer.platz[2].cName, schwer.platz[2].cPs, schwer.platz[2].cP, schwer.platz[2].cZ);
    printf("      %15s | %4s | %4s | %4s       %15s | %4s | %4s | %4s       %15s | %4s | %4s | %4s\n",
           leicht.platz[3].cName, leicht.platz[3].cPs, leicht.platz[3].cP, leicht.platz[3].cZ,
           mittel.platz[3].cName, mittel.platz[3].cPs, mittel.platz[3].cP, mittel.platz[3].cZ,
           schwer.platz[3].cName, schwer.platz[3].cPs, schwer.platz[3].cP, schwer.platz[3].cZ);
    printf("      %15s | %4s | %4s | %4s       %15s | %4s | %4s | %4s       %15s | %4s | %4s | %4s\n",
           leicht.platz[4].cName, leicht.platz[4].cPs, leicht.platz[4].cP, leicht.platz[4].cZ,
           mittel.platz[4].cName, mittel.platz[4].cPs, mittel.platz[4].cP, mittel.platz[4].cZ,
           schwer.platz[4].cName, schwer.platz[4].cPs, schwer.platz[4].cP, schwer.platz[4].cZ);
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
