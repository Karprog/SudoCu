#ifndef FRONTEND_H_
#define FRINTEND_H_

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

#endif // FRONTEND_H_
