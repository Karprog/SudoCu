#include <stdio.h>
#include <stdlib.h>
//#include <zeit.h>

char Login();
char Hauptmenue();
char Bestenliste();
char Schnellstart();
char Schwierigkeit();


int Anmelden();
int Registrieren();

int mainFrontend()
{
    Hauptmenue();
    return 0;
}

char Hauptmenue()
{
        char auswahl;

        do
        {
            system("cls");

            printf("\n");
            printf(" SudoCu Version 4.4Alpha                                                                                            Steuerung:  \n");
            printf("\n");
            printf(" Das Ziel ist es, die leeren                                                                                         R = Nachladen\n");
            printf(" Zellen im Spielfeld mit den                                         SudoCo!                                         T = Flashlight\n");
            printf(" Ziffern 1 bis 9 wie folgt                                                                                           Q = Questlog\n");
            printf(" auszufüllen.                                                                                                        P = Skillbaum\n");
            printf("                                                                    a. Login                                         G = Granate\n");
            printf(" -In jeder Spalte kommt jede                                                                                         C = Charakterinformationen\n");
            printf("  Zahl nur einmal vor                                            b. Schnellstart                                     B = Inventar\n");
            printf("                                                                                                                     M = Map\n");
            printf(" -In jeder Zeile kommt jede                                       c. Bestenliste                                     U = Dungeonfinder\n");
            printf("  Zahl nur einmal vor\n");
            printf("\n");
            printf(" -In jedem 3 x 3 Quadranten\n");
            printf("  kommt jede Zahl nur einmal\n");
            printf("  vor.");
            printf(" \n\n\n");

            scanf("%c", &auswahl);

        }while (auswahl != 'a' && auswahl != 'b' && auswahl != 'c' && auswahl != 'x');


        switch(auswahl)
        {
            case 'a':
                Login();
                break;
            case 'b':
               Schwierigkeit();
                break;
            case 'c':
                Bestenliste();
                break;
            case 'x':
                exit(0);
                break;
            default:
                break;
        }

        return auswahl;
}

char Login()
{

    char auswahl;
    do
    {
        system("cls");
        printf("\n");
        printf(" SudoCu Version 4.4Alpha                                                                                            Steuerung:  \n");
        printf("\n");
        printf(" Das Ziel ist es, die leeren                                                                                         R = Nachladen\n");
        printf(" Zellen im Spielfeld mit den                                          Login                                          T = Flashlight\n");
        printf(" Ziffern 1 bis 9 wie folgt                                                                                           Q = Questlog\n");
        printf(" auszufüllen.                                                                                                        P = Skillbaum\n");
        printf("                                                                    a. Anmelden                                      G = Granate\n");
        printf(" -In jeder Spalte kommt jede                                                                                         C = Charakterinformationen\n");
        printf("  Zahl nur einmal vor                                             b. Registrieren                                    B = Inventar\n");
        printf("                                                                                                                     M = Map\n");
        printf(" -In jeder Zeile kommt jede                                                                                          U = Dungeonfinder\n");
        printf("  Zahl nur einmal vor\n");
        printf("\n");
        printf(" -In jedem 3 x 3 Quadranten\n");
        printf("  kommt jede Zahl nur einmal\n");
        printf("  vor.");
        printf(" \n\n\n");


        scanf("%c", &auswahl);

    }while(auswahl != 'a' && auswahl != 'b' && auswahl != 'x');

    switch(auswahl)
    {
        case 'a':
            Anmelden();
            break;
        case 'b':
           Registrieren();
            break;
        case 'x':
            Hauptmenue();
            break;
        default:
            break;
    }

    return auswahl;
}

int Anmelden()
{

    char username[40];
    char passwort[40];
    int i = 0;


    system("cls");
    printf("\n");
    printf(" SudoCu Version 4.4Alpha                                                                                            Steuerung:  \n");
    printf("\n");
    printf(" Das Ziel ist es, die leeren                                                                                         R = Nachladen\n");
    printf(" Zellen im Spielfeld mit den                                         Anmeldung                                       T = Flashlight\n");
    printf(" Ziffern 1 bis 9 wie folgt                                                                                           Q = Questlog\n");
    printf(" auszufüllen.                                                                                                        P = Skillbaum\n");
    printf("                                                                 Geben Sie erst Name                                 G = Granate\n");
    printf(" -In jeder Spalte kommt jede                                                                                         C = Charakterinformationen\n");
    printf("  Zahl nur einmal vor                                           und dann Passwort ein                                B = Inventar\n");
    printf("                                                                                                                     M = Map\n");
    printf(" -In jeder Zeile kommt jede                                                                                          U = Dungeonfinder\n");
    printf("  Zahl nur einmal vor\n");
    printf("\n");
    printf(" -In jedem 3 x 3 Quadranten\n");
    printf("  kommt jede Zahl nur einmal\n");
    printf("  vor.");
    printf(" \n\n\n");

    printf(" Benutzername: ");
    scanf("%s", &username);

    printf(" Passwort: ");
    scanf("%s", &passwort);

    //Hier Stefanies Methode !

    //prüfe übereinstimmungs

    Schwierigkeit();
    return 0;
}

int Registrieren()
{

    char username[40];
    char passwort[40];
    int i = 0;

    system("cls");

    printf("\n");
    printf(" SudoCu Version 4.4Alpha                                                                                            Steuerung:  \n");
    printf("\n");
    printf(" Das Ziel ist es, die leeren                                                                                         R = Nachladen\n");
    printf(" Zellen im Spielfeld mit den                                        Registrierung                                    T = Flashlight\n");
    printf(" Ziffern 1 bis 9 wie folgt                                                                                           Q = Questlog\n");
    printf(" auszufüllen.                                                                                                        P = Skillbaum\n");
    printf("                                                                 Geben Sie erst Name                                 G = Granate\n");
    printf(" -In jeder Spalte kommt jede                                                                                         C = Charakterinformationen\n");
    printf("  Zahl nur einmal vor                                           und dann Passwort ein                                B = Inventar\n");
    printf("                                                                                                                     M = Map\n");
    printf(" -In jeder Zeile kommt jede                                                                                          U = Dungeonfinder\n");
    printf("  Zahl nur einmal vor\n");
    printf("\n");
    printf(" -In jedem 3 x 3 Quadranten\n");
    printf("  kommt jede Zahl nur einmal\n");
    printf("  vor.");
    printf(" \n\n\n");

    printf(" Benutzername: ");
    scanf("%s", &username);


    printf(" Passwort: ");
    scanf("%s", &passwort);

    //Hier Daten an Stefanies Methode !

    // SPielstart
    Schwierigkeit();
    return 0;Schwierigkeit();
}

char Bestenliste()
{

    char auswahl;

    do
    {
        system("cls");

        printf("\n");
        printf(" SudoCu Version 4.4Alpha                                                                                            Steuerung:  \n");
        printf("\n");
        printf(" Das Ziel ist es, die leeren                                                                                         R = Nachladen\n");
        printf(" Zellen im Spielfeld mit den                                       Bestenliste                                       T = Flashlight\n");
        printf(" Ziffern 1 bis 9 wie folgt                                                                                           Q = Questlog\n");
        printf(" auszufüllen.                                 Leicht                 Mittel                   Schwer                 P = Skillbaum\n");
        printf("                                              ¯¯¯¯¯¯                 ¯¯¯¯¯¯                   ¯¯¯¯¯¯                 G = Granate\n");
        printf(" -In jeder Spalte kommt jede                                                                                         C = Charakterinformationen\n");
        printf("  Zahl nur einmal vor                                                                                                B = Inventar\n");
        printf("                                                                                                                     M = Map\n");
        printf(" -In jeder Zeile kommt jede                                                                                          U = Dungeonfinder\n");
        printf("  Zahl nur einmal vor\n");
        printf("\n");
        printf(" -In jedem 3 x 3 Quadranten\n");
        printf("  kommt jede Zahl nur einmal\n");
        printf("  vor.");
        printf(" \n\n\n");


        scanf("%c", &auswahl);

    }while(auswahl != 'x');

    Hauptmenue();

    return auswahl;
}

char Schwierigkeit()
{

    char auswahl;
    do
    {
        system("cls");
        printf("\n");
        printf(" SudoCu Version 4.4Alpha                                                                                            Steuerung:  \n");
        printf("\n");
        printf(" Das Ziel ist es, die leeren                                                                                         R = Nachladen\n");
        printf(" Zellen im Spielfeld mit den                                     Schwierigkeitsgrad                                  T = Flashlight\n");
        printf(" Ziffern 1 bis 9 wie folgt                                                                                           Q = Questlog\n");
        printf(" auszufüllen.                                                                                                        P = Skillbaum\n");
        printf("                                                                     1. Leicht                                       G = Granate\n");
        printf(" -In jeder Spalte kommt jede                                                                                         C = Charakterinformationen\n");
        printf("  Zahl nur einmal vor                                                2. Mittel                                       B = Inventar\n");
        printf("                                                                                                                     M = Map\n");
        printf(" -In jeder Zeile kommt jede                                          3. Schwer                                       U = Dungeonfinder\n");
        printf("  Zahl nur einmal vor\n");
        printf("\n");
        printf(" -In jedem 3 x 3 Quadranten\n");
        printf("  kommt jede Zahl nur einmal\n");
        printf("  vor.");
        printf(" \n\n\n");


        scanf("%c", &auswahl);

    }while(auswahl != '1' && auswahl != '2' && auswahl != '3'&& auswahl != 'x');

    switch(auswahl)
    {
        case '1':

            break;
        case '2':

            break;
        case '3':

            break;
        case 'x':
            Hauptmenue();
            break;
        default:
            break;
    }

    return auswahl;
}
