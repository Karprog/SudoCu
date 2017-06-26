#ifndef LOGIK_H_
#define LOGIK_H_

void AnfangsfelderGenerieren();                                                         //Generierung
void KandidatenGenerieren();                                                            //Spielfunktion
int KandidatEintragenEntfernen(int iPositionY, int iPositionX, int iZahl);              //Spielfunktion
int KomplettPruefen(int *iPointer);                                                     //Hilfsfunktion
int KomplettRichtigPruefen();                                                           //Hilfsfunktion
int LoesungEintragen(int iPositionY, int iPositionX);                                  //Spielfunktion
void LoesungFinden(int iPositionY, int iPositionX);                                     //Generierung
void LoesungGenerieren(int iPositionY, int iPositionX);                                 //Generierung
void Logik(int iSchwierigkeitsgrad);                                                     //Spielfunktion
void PositionSetzen(int *iPositionY, int *iPositionX);                                  //Hilfsfunktion
void SudokuAusgeben();                                                                  //Ein-/Ausgabe
void SudokuErstellen(int iSchwierigkeitsgrad);                                          //Generierung
void SudokuInitialisieren();                                                            //Generierung
int SudokuSpielen();                                                                   //Ein-/Ausgabe
int ZahlAnPositionPruefen(int *iSudoku, int iPositionY, int iPositionX, int iZahl);     //Hilfsfunktion
void ZahlEintragen();                                                                    //Spielfunktion
int ZufallszahlGenerieren(int iVon, int iBis);                                          //Generierung

#endif // LOGIK_H_
