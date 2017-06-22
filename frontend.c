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
        char auswahl;

        do
        {
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
            scanf("%c", &auswahl);
        //Die While Schleife lässt den nutzer solange eingaben machen bis ein
        //gültiger Wert eingegeben wurde.
        }while (auswahl != 'a' && auswahl != 'b' && auswahl != 'c' && auswahl != 'x');

        //Hier wird entschieden welche Aktion der User ausführen möchte.
        switch(auswahl)
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
                //zeigt die Bestenlistean
                Bestenliste(0);
                break;
            case 'x':
                //beendet das Programm
                exit(0);
                break;
            default:
                break;
        }
        //Rückgabe der User Auswahl
        return auswahl;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Login()                                                         *
 * Parameter: none                                                           *
 * Rückgabewert: char auswahl                                                *
 * Beschreibung: Diese Funktion stellt das Login menue dar und fängt         *
 *               nutzereigaben ab, um sich in der Menue Struktur zu bewegen  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char Login()
{
    //Variablen Deklaration
    char auswahl;

    do
    {
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
        scanf("%c", &auswahl);
    //Die While Schleife lässt den nutzer solange eingaben machen bis ein
    //gültiger Wert eingegeben wurde.
    }while(auswahl != 'a' && auswahl != 'b' && auswahl != 'x');

    //Hier wird entschieden welche Aktion der User ausführen möchte.
    switch(auswahl)
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
            //Zurueck zum Hauptmenue
            Hauptmenue();
            break;
        default:
            break;
    }

    //Rückgabe der User Auswahl
    return auswahl;
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
    char username[40];
    char passwort[40];
    int i = 0;
    int erfolgreich=0;

    do
    {
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
        scanf("%s", &username);

        printf(" Passwort: ");
        scanf("%s", &passwort);

        //Aufruf der Datenbankfunktion und speichern des Rückgabe wertes
        erfolgreich = mainNutzerInDb(username, passwort);

    //der Nutzer kann sich solange veruschen anzumelden bis es geklappt hat
    }while(erfolgreich == '0');

    //speichern des Nutzernamens in die Global Variable NUTZERNAME
    strcpy(NUTZERNAME, username);

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
    char username[40];
    char passwort[40];
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
    scanf("%s", &username);


    printf(" Passwort: ");
    scanf("%s", &passwort);

    //ruft die Datenbankfunktion auf um in die db zu schreiben
    mainNutzerVonDb(username, passwort);

    // SPielstart
    Schwierigkeit();
    return 0;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Bestenliste()                                                   *
 * Parameter: int iHelfer                                                           *
 * Rückgabewert: char auswahl                                                *
 * Beschreibung: Diese Funktion stellt die Bestenliste dar                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
char Bestenliste( int iHelfer)
{
    //Variablen Deklaration
    char auswahl;

    do
    {
        //Ausgabe des Menues
        system("cls");
        printf("\n");
        printf(" SudoCu Version 4.4Alpha\n\n\n");
        printf("\n\n                                                                                                                    Steuerung:  \n");
        printf("\n");
        printf(" Das Ziel ist es, die leeren                                                                                          0 = Kugelschreiber\n");
        printf(" Zellen im Spielfeld mit den                                       Bestenliste                                        1 = Bleistift\n");
        printf(" Ziffern 1 bis 9 wie folgt                                                                                            2 = Loesung Position\n");
        printf(" auszufuellen.                                Leicht                 Mittel                   Schwer                  3 = Kanidaten anzeigen\n");
        printf("                                              ¯¯¯¯¯¯                 ¯¯¯¯¯¯                   ¯¯¯¯¯¯                  \n");
        printf(" -In jeder Spalte kommt jede                                                                                          B = Bestenliste\n");
        printf("  Zahl nur einmal vor                                                                                                 X = Zurueck/Spiel abbrechen\n");
        printf("                                                                                                                      Q = Schliessen\n");
        printf(" -In jeder Zeile kommt jede                                                                                           \n");
        printf("  Zahl nur einmal vor\n");
        printf("\n");
        printf(" -In jedem 3 x 3 Quadranten\n");
        printf("  kommt jede Zahl nur einmal\n");
        printf("  vor.");
        printf(" \n\n\n");

        //Bentzer eingabe für rückführung
        scanf("%c", &auswahl);
    //fängt dei eingaben ab bis ein x eingegeben wird
    }while(auswahl != 'x');

    //Das hauptmenue wird wieder ausgeführt
    if(iHelfer == 0)
    {
        Hauptmenue();
    }
    else if(iHelfer == 1)
    {
        return auswahl;
    }


    return auswahl;
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
    char auswahl;

    do
    {
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
        scanf("%c", &auswahl);

    //Die While Schleife lässt den nutzer solange eingaben machen bis ein
    //gültiger Wert eingegeben wurde.
    }while(auswahl != '1' && auswahl != '2' && auswahl != '3'&& auswahl != 'x');

    //Hier wird entschieden welche Aktion der User ausführen möchte.
    switch(auswahl)
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
            Hauptmenue();
            break;
        default:
            break;
    }
    return auswahl;
}
