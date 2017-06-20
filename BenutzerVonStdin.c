#include <stdio.h>
#include <stdlib.h>

int leseNutzerdaten(void);
int schreibeNutzerdatenInDb(char nutzerdaten);

int mainBenutzerVonStdin()
{
    //char Nutzerdaten;

    leseNutzerdaten();
    return 0;
}

int leseNutzerdaten(void)
{
    char benutzername[128];
    char passwort[128];
    //char *nutzerdaten[2];

    printf("Bitte Benutzernamen eingeben: ");
    fflush(stdin);
    scanf("%s", benutzername);

    printf("\nBitte Passwort eingeben: ");
    fflush(stdin);
    scanf("%s", passwort);

    printf("\n Benutzername: %s\n", benutzername);
    printf("\n Passwort: %s\n", passwort);

    /*nutzerdaten[0] = benutzername;
    nutzerdaten[1] = passwort;*/
    return 0;
}


