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

//Globalevariable f�r den Nutzernnamen, welcher �berall angezeigt wird.
char NUTZERNAME[40];

#endif // FRONTEND_H_
