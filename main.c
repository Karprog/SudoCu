/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Autoren: Stefanie Pfleiderer, Robin Kitzelmann, Burhan Karaca, Pascal     *
 *          Scheufens, Janik Busch                                           *
 * Datum:   23.06.2017                                                       *
 * Name:    SudoCu                                                           *
 * Version: 1.4                                                              *
 * Compiler:GNU                                                              *
 * Beschreibung:                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Zeit.h"
#include "Punkte.h"
#include "LeseNutzer.h"

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

typedef struct{
    int iHilfsfelder[9][9][9];
    int iSpiel[9][9];
    int iAnfangsfelder[9][9];
    int iLoesung[9][9];
    int iAnz;
} SUDOKU;
SUDOKU spiel;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: Logik()                                                         *
 * Parameter: none                                                           *
 * Rückgabewert: none                                                        *
 * Beschreibung: Aufruf der verschiedenen Funktionen, um das Sudoku spielen  *
 *               spielen zu können.                                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Logik(int iSchwierigkeitsgrad){
    int k, iAbbrechen, iZeit;
    srand(time(NULL));

    switch(iSchwierigkeitsgrad){
        case 1: k=1; break;
        case 2: k=40; break;
        case 3: k=50; break;
    }

    while(spiel.iAnz!=1){
        SudokuErstellen(k);
    }

    iAbbrechen = SudokuSpielen();

    if(iAbbrechen==0){
        gesamtPunkteBerechnen();
        iZeit = iZeitBerechnen();
        schreibeErgebnisInDb(iSchwierigkeitsgrad, iZeit);
        Bestenliste();
        spiel.iAnz=0;
        iZeitStartWert=-1;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: SudokuErstellen()                                               *
 * Parameter: int iSchwierigkeitsgrad                                        *
 * Rückgabewert: none                                                        *
 * Beschreibung: Erstellt ein Sudoku. Dazu gehören 4 Multidimensionale       *
 *               Arrays: int iHilfsfelder[9][9][9];                          *
 *                       int iSpiel[9][9];                                   *
 *                       int iAnfangsfelder[9][9];                           *
 *                       int iLoesung[9][9];                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SudokuErstellen(int iSchwierigkeitsgrad){
    int i, j;

    SudokuInitialisieren();

    LoesungGenerieren(0, 0);

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            spiel.iAnfangsfelder[i][j] = spiel.iLoesung[i][j];
        }
    }

    for(i=0; i<iSchwierigkeitsgrad; i++){
        AnfangsfelderGenerieren();
    }

    LoesungFinden(0, 0);

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            spiel.iSpiel[i][j] = spiel.iAnfangsfelder[i][j];
        }
    }

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: SudokuSpielen()                                                 *
 * Parameter: none                                                           *
 * Rückgabewert: int iAbbrechen                                              *
 * Beschreibung: Regelt die Ein- und Ausgabe während des Spielens.           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int SudokuSpielen(){
    int iPositionX, iPositionY, iZahl, iAbbrechen=0;
    char cModus;

    SudokuAusgeben();

    do{
        printf("Was moechten Sie tun?");
        scanf("%c", &cModus);

        if(cModus== '0' || cModus== '1' || cModus== '2'){
            printf("Bitte geben Sie PositionX ein:");
            scanf("%i", &iPositionX);

            printf("Bitte geben Sie PositionY ein:");
            scanf("%i", &iPositionY);
            if(cModus== '0' || cModus== '1'){
                printf("Bitte geben Sie die Zahl ein:");
                scanf("%i", &iZahl);
                if(cModus== '0'){
                    ZahlEintragen(iPositionY, iPositionX, iZahl);
                }else if(cModus== '1' ){
                    KandidatEintragenEntfernen(iPositionY, iPositionX, iZahl);
                }
            }
            else{
                LoesungEintragen(iPositionY, iPositionX);
            }
        }
        else if(cModus== '3'){
            KandidatenGenerieren();
        }
        else if(cModus== 'x'){
            iAbbrechen = 1;
        }
        else if(cModus== 'q'){
            exit(0);
        }
        else if(cModus== 'b'){
            Bestenliste();
        }

        SudokuAusgeben();
    }while(!KomplettRichtigPruefen() && iAbbrechen==0);

    return iAbbrechen;

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: SudokuInitialisieren()                                          *
 * Parameter: none                                                           *
 * Rückgabewert: none                                                        *
 * Beschreibung: Setzt alle Felder der Arrays auf 0                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SudokuInitialisieren(){
    int i, j, k;

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            spiel.iSpiel[i][j] = 0;
            spiel.iAnfangsfelder[i][j] = 0;
            spiel.iLoesung[i][j] = 0;
            for(k=0; k<9; k++){
                spiel.iHilfsfelder[i][j][k] = 0;
            }
        }
    }

    spiel.iAnz = 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: ZufallszahlGenerieren()                                         *
 * Parameter: int iVon, int iBis                                             *
 * Rückgabewert: int iZufallszahl                                            *
 * Beschreibung: Generiert eine Zufallszahl in einem definierten Bereich     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int ZufallszahlGenerieren(int iVon, int iBis){
    int iZufallszahl = rand()%(iBis+1-iVon)+iVon;
    return iZufallszahl;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: PositionSetzen()                                                *
 * Parameter: int iPositionY, int iPositionX                                 *
 * Rückgabewert: none                                                        *
 * Beschreibung: Setzt die Position, falls sie außerhalb des Spielfeldes     *
 *               liegt, entsprechend der Werte neu.                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 void PositionSetzen(int *iPositionY, int *iPositionX){
        *iPositionY = (*iPositionY + (*iPositionX-(*iPositionX)%9)/9)%9;
        *iPositionX = (*iPositionX)%9;
 }

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: LoesungGenerieren()                                             *
 * Parameter: int iPositionY, int iPositionX                                 *
 * Rückgabewert: none                                                        *
 * Beschreibung: Generiert einen Lösungsarray                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LoesungGenerieren(int iPositionY, int iPositionX){
    int i, iZahl=ZufallszahlGenerieren(1,9);

    PositionSetzen(&iPositionY, &iPositionX);

    if(spiel.iLoesung[iPositionY][iPositionX]!=0){
        LoesungGenerieren(iPositionY, iPositionX+1);
    }else{
        for(i=0; i<9; i++){
            if(ZahlAnPositionPruefen(&spiel.iLoesung, iPositionY, iPositionX, (iZahl+i)%9+1)){
                spiel.iLoesung[iPositionY][iPositionX] = (iZahl+i)%9+1;
                //SudokuAusgeben();
                if(KomplettPruefen(&spiel.iLoesung[0][0])==0){
                    LoesungGenerieren(iPositionY, iPositionX+1);
                }
                if(KomplettPruefen(&spiel.iLoesung[0][0])==0){
                    spiel.iLoesung[iPositionY][iPositionX] = 0;
                }
            }
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: AnfangsfelderGenerieren()                                       *
 * Parameter: none                                                           *
 * Rückgabewert: none                                                        *
 * Beschreibung: Generiert den Anfangsfelderarray. Dazu muss zuvor der       *
 *               Anfangsfelderarray gleich dem Lösungsarray gesetzt werden.  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void AnfangsfelderGenerieren(){
    int iPositionY = ZufallszahlGenerieren(0,8),
        iPositionX = ZufallszahlGenerieren(0,8);

    if(spiel.iAnfangsfelder[iPositionY][iPositionX]!=0){
        spiel.iAnfangsfelder[iPositionY][iPositionX] = 0;
    }else{
        AnfangsfelderGenerieren();
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: LoesungFinden()                                                 *
 * Parameter: int iPositionY, int iPositionX                                 *
 * Rückgabewert: none                                                        *
 * Beschreibung: Prüft den Anfangsfelderarray auf Eindeutigkeit der Lösung.  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LoesungFinden(int iPositionY, int iPositionX){
    int i, j;

    PositionSetzen(&iPositionY, &iPositionX);

    if(spiel.iAnfangsfelder[iPositionY][iPositionX]!=0 && spiel.iAnz<2){
        LoesungFinden(iPositionY, iPositionX+1);
    }else{
        for(i=0; i<9; i++){
            if(ZahlAnPositionPruefen(&spiel.iAnfangsfelder, iPositionY, iPositionX, i+1)){
                spiel.iAnfangsfelder[iPositionY][iPositionX] = i+1;
                //SudokuAusgeben();
                if(KomplettPruefen(&spiel.iAnfangsfelder[0][0])==0 && spiel.iAnz<2){
                    LoesungFinden(iPositionY, iPositionX+1);
                }else{
                    for(i=0; i<9; i++){
                        for(j=0; j<9; j++){
                            spiel.iLoesung[i][j] = spiel.iAnfangsfelder[i][j];
                        }
                    }
                    spiel.iAnz++;
                    //SudokuAusgeben();
                }
                spiel.iAnfangsfelder[iPositionY][iPositionX] = 0;
            }
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: ZahlAnPositionPruefen()                                         *
 * Parameter: int *iSudoku, int iPositionY, int iPositionX, int iZahl        *
 * Rückgabewert: int iPruef                                                  *
 * Beschreibung: Prüft, ob Zahl an bestimmter Position in bestimmten Array   *
 *               nach Spielregeln gültig ist.                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int ZahlAnPositionPruefen(int *iSudoku, int iPositionY, int iPositionX, int iZahl){
    int i, j, iBlockY, iBlockX, iPruef;

    if(*(iSudoku+(iPositionY*9)+iPositionX)==0){
        iPruef = 1;
        for(i=0; i<9; i++){
            if(*(iSudoku+(iPositionY*9)+i)==iZahl ||
               *(iSudoku+(i*9)+iPositionX)==iZahl ){
                iPruef = 0;
            }
        }
        if((double)(iPositionY+1)/3<=1){
            iBlockY = 0;
        }else if((double)(iPositionY+1)/3<=2){
            iBlockY = 1;
        }else if((double)(iPositionY+1)/3<=3){
            iBlockY = 2;
        }
        if((double)(iPositionX+1)/3<=1){
            iBlockX = 0;
        }else if((double)(iPositionX+1)/3<=2){
            iBlockX = 1;
        }else if((double)(iPositionX+1)/3<=3){
            iBlockX = 2;
        }
        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
                if(*(iSudoku+(i+(3*iBlockY))*9+(j+(3*iBlockX)))==iZahl){
                    iPruef = 0;
                }
            }
        }
    }else{
        iPruef = 0;
    }

    return iPruef;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: KomplettPruefen()                                               *
 * Parameter: int *iPointer                                                  *
 * Rückgabewert: int iPruef                                                  *
 * Beschreibung: Prüft, ob alle Felder in Array ungleich 0 sind              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int KomplettPruefen(int *iPointer){
    int i, j, iPruef=0;

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(*(iPointer+(9*i)+j)!=0){
                iPruef++;
            }
        }
    }

    if(iPruef == 81){
        return 1;
    }else{
        return 0;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: KomplettRichtigPruefen()                                        *
 * Parameter: none                                                           *
 * Rückgabewert: int iPruef                                                  *
 * Beschreibung: Prüft, ob alle Felder des Spielarrays gleich dem            *
 *               Lösungsarray sind.                                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int KomplettRichtigPruefen(){
    int i, j, iPruef=0;

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(spiel.iSpiel[i][j] == spiel.iLoesung[i][j]){
                iPruef++;
            }
        }
    }

    if(iPruef==81){
        return 1;
    }else{
        return 0;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: SudokuAusgaben()                                                *
 * Parameter: none                                                           *
 * Rückgabewert: none                                                        *
 * Beschreibung: Gibt das Sudoku aus.                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SudokuAusgeben(){
    int i, j, k, l, m, n, o;
    int iZeit;
    int iMinuten;
    int iSekunden;
    char cTopline[79];
    char cBottomline[79];
    char cStrongline[79];
    char cWeakline[79];
    char cEmptyline[79];

    iZeit = iZeitBerechnen();
    iMinuten = iZeit/60;
    iSekunden = iZeit%60;

    gesamtPunkteBerechnen();

    for(i=0; i<79; i++){
        if(i==0){
            cTopline[i] = '\xDA';
            cBottomline[i] = '\xC0';
            cStrongline[i] = '\xC3';
            cWeakline[i] = '\xC3';
            cEmptyline[i] = '\xB3';
        }else if(i==26 || i==52){
            cTopline[i] = '\xC2';
            cBottomline[i] = '\xC1';
            cStrongline[i] = '\xC5';
            cWeakline[i] = '\xC5';
            cEmptyline[i] = '\xB3';
        }else if(i==78){
            cTopline[i] = '\xBF';
            cBottomline[i] = '\xD9';
            cStrongline[i] = '\xB4';
            cWeakline[i] = '\xB4';
            cEmptyline[i] = '\xB3';
        }else if(i==9 || i==17 || i==35 || i==43 || i==61 || i==69){
            cTopline[i] = '\xC2';
            cBottomline[i] = '\xC1';
            cStrongline[i] = '\xC5';
            cWeakline[i] = '\xC5';
            cEmptyline[i] = ' ';
        }else if(i==1 || i==2 || i==24 || i==25 || i==27 || i==28 ||
                 i==50 || i==51 || i==53 || i==54 || i==76 || i==77){
            cTopline[i] = '\xC4';
            cBottomline[i] = '\xC4';
            cStrongline[i] = '\xC4';
            cWeakline[i] = ' ';
            cEmptyline[i] = ' ';
        }else{
            cTopline[i] = '\xC4';
            cBottomline[i] = '\xC4';
            cStrongline[i] = '\xC4';
            cWeakline[i] = '\xC4';
            cEmptyline[i] = ' ';
        }

    }

    system("cls");

    /*
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(spiel.iLoesung[i][j]==0){
                printf("   ");
            }else{
                printf(" %i ", spiel.iLoesung[i][j]);
            }
            if(j==2 || j==5){
                printf(" | ");
            }
        }
        if(i==2 || i==5){
            printf("\n----------+-----------+---------- ");
        }
        printf("\n");
    }
    //*/
    //*
   printf( "                                Y " \
            "%.79s     " \
            "\n" \
            " SudoCu Version 4.4Alpha          " \
            "%.79s     " \
            "Steuerung:\n", cTopline, cEmptyline);
    for(i=0; i<9; i++){
        for(l=0; l<3; l++){
            switch(i){
                case 0: switch(l){
                    case 0: printf("                                  "); break;
                    case 1: printf("                                1 "); break;
                    case 2: printf("                                  "); break;
                } break;
                case 1: switch(l){
                    case 0: printf(" Das Ziel ist es, die leeren      "); break;
                    case 1: printf(" Zellen im Spielfeld mit den    2 "); break;
                    case 2: printf(" Ziffern 1 bis 9 wie folgt        "); break;
                } break;
                case 2: switch(l){
                    case 0: printf("                                  "); break;
                    case 1: printf("                                3 "); break;
                    case 2: printf(" -In jeder Spalte kommt jede      "); break;
                } break;
                case 3: switch(l){
                    case 0: printf(" -In jeder Zeile kommt jede       "); break;
                    case 1: printf("  Zahl nur einmal vor           4 "); break;
                    case 2: printf("                                  "); break;
                } break;
                case 4: switch(l){
                    case 0: printf(" -In jedem 3 x 3 Quadranten       "); break;
                    case 1: printf("  kommt jede Zahl nur einmal    5 "); break;
                    case 2: printf("  vor.                            "); break;
                } break;
                case 5: switch(l){
                    // 25 links
                    case 0: printf("                                  "); break;
                    case 1: printf("                                6 "); break;
                    case 2: printf("                                  "); break;
                } break;
                case 6: switch(l){
                    //31 links
                    case 0: printf("                                  "); break;
                    case 1: printf("                                7 "); break;
                    case 2: printf("                                  "); break;
                } break;
                case 7: switch(l){
                    //35 links
                    case 0: printf("                                  "); break;
                    case 1: printf("                                8 "); break;
                    case 2: printf("                                  "); break;
                } break;
                case 8: switch(l){
                    //39 links
                    case 0: printf("                                  "); break;
                    case 1: printf("                                9 "); break;
                    case 2: printf("                                  "); break;
                } break;
            }
            printf("%c  ", '\xB3');
            for(j=0; j<9; j++){
                switch(l){
                    case 0: n=3; o=0; break;
                    case 1: n=6; o=3; break;
                    case 2: n=9; o=6; break;
                }
                if(spiel.iSpiel[i][j]==0){
                    for(k=o; k<n; k++){
                        if(spiel.iHilfsfelder[i][j][k]==0){
                            if(k==1 || k==4 || k==7){
                                printf("   ");
                            } else{
                                printf(" ");
                            }
                        }else{
                            if(k==1 || k==4 || k==7){
                                printf(" %i ", spiel.iHilfsfelder[i][j][k]);
                            } else{
                                printf("%i", spiel.iHilfsfelder[i][j][k]);
                            }
                        }
                        if((k==2 || k==5 || k==8) && (j==2 || j==5 || j==8)){
                            printf("  %c  ", '\xB3');
                        }else if((k==2 || k==5 && k==8)){
                            printf(" %c ", '\xB3');
                        }else if(k==2 || k==5 || k==8){
                            printf(" %c ", '\xB3');
                        }
                    }
                }else if(spiel.iSpiel[i][j]==spiel.iAnfangsfelder[i][j]){
                    for(k=o; k<n; k++){
                        if(k==4){
                            printf(" %i ", spiel.iAnfangsfelder[i][j]);
                        }else if(k==1 || k==7){
                            printf("%c", '\xB2');
                            printf("%c", '\xB2');
                            printf("%c", '\xB2');
                        }else{
                            printf("%c", '\xB2');
                        }
                        if((k==2 || k==5 || k==8) && (j==2 || j==5 || j==8)){
                            printf("  %c  ", '\xB3');
                        }else if((k==2 || k==5 && k==8)){
                            printf(" %c ", '\xB3');
                        }else if(k==2 || k==5 || k==8){
                            printf(" %c ", '\xB3');
                        }
                    }
                }else{
                    for(k=o; k<n; k++){
                        if(k==4){
                            printf(" %i ", spiel.iSpiel[i][j]);
                        }else if(k==1 || k==7){
                            printf("%c", '\xB1');
                            printf("%c", '\xB1');
                            printf("%c", '\xB1');
                        }else{
                            printf("%c", '\xB1');
                        }
                        if((k==2 || k==5 || k==8) && (j==2 || j==5 || j==8)){
                            printf("  %c  ", '\xB3');
                        }else if((k==2 || k==5 && k==8)){
                            printf(" %c ", '\xB3');
                        }else if(k==2 || k==5 || k==8){
                            printf(" %c ", '\xB3');
                        }
                    }
                }
            }
            switch(i){
                case 0: switch(l){
                    case 0: printf("                 "); break;
                    case 1: printf("      0 = Kugelschreiber"); break;
                    case 2: printf("      1 = Bleistift"); break;
                } break;
                case 1: switch(l){
                    case 0: printf("      3 = Kanidaten anzeigen"); break;
                    case 1: printf("                         "); break;
                    case 2: printf("      B = Bestenliste"); break;
                } break;
                case 2: switch(l){
                    //11 Rechts
                    case 0: printf("      Q = Schliessen"); break;
                    case 1: printf("                    "); break;
                    case 2: printf("                    "); break;
                } break;
                case 3: switch(l){
                    //17 Rechts
                    case 0: printf("      %i:%02i", iMinuten, iSekunden); break;
                    case 1: printf("                    "); break;
                    case 2: printf("                    "); break;
                } break;
                case 4: switch(l){
                    //21 Rechts
                    case 0: printf("                    "); break;
                    case 1: printf("                    "); break;
                    case 2: printf("                    "); break;
                } break;
                case 5: switch(l){
                    //25 Rechts
                    case 0: printf("                    "); break;
                    case 1: printf("                    "); break;
                    case 2: printf("                    "); break;
                } break;
                case 6: switch(l){
                    //31 Rechts
                    case 0: printf("                    "); break;
                    case 1: printf("                    "); break;
                    case 2: printf("                    "); break;
                } break;
                case 7: switch(l){
                    //35 Rechts
                    case 0: printf("                    "); break;
                    case 1: printf("                    "); break;
                    case 2: printf("                    "); break;
                } break;
                case 8: switch(l){
                    //39 Rechts
                    case 0: printf("                    "); break;
                    case 1: printf("                    "); break;
                    case 2: printf("                    "); break;
                } break;
            }
            if(l==2 && i==0){
                printf( "\n                                  " \
                        "%.79s     " \
                        "   2 = Loesung Position", cWeakline);
            }else if(l==2 && i==1){
                printf( "\n auszufuellen.                    " \
                        "%.79s     " \
                        "   X = Zurueck/Spiel abbrechen", cWeakline);
            }else if(l==2 &&i==2){
                printf( "\n  Zahl nur einmal vor             " \
                        "%.79s     " \
                        "\n" \
                        "                                  " \
                        "%.79s     " \
                        "\n" \
                        "                                  " \
                        "%.79s     " \
                        "", cEmptyline, cStrongline, cEmptyline);
            }else if(l==2 && i==3){
                printf( "\n                                  " \
                        "%.79s     " \
                        "", cWeakline);
            }else if(l==2 && i==4){
                // 24 links
                printf( "\n                                  " \
                        "%.79s     " \
                        "", cWeakline);
            }else if(l==2 && i==5){
                // 28 links
                printf( "\n                                  " \
                        "%.79s     " \
                        "\n" \
                        // 29 links
                        "                                  " \
                        "%.79s     " \
                        "\n" \
                        // 30 links
                        "                                  " \
                        "%.79s     " \
                        "", cEmptyline, cStrongline, cEmptyline);
            }else if(l==2 && i==6){
                // 34 links
                printf( "\n                                  " \
                        "%.79s     " \
                        "", cWeakline);
            }else if(l==2 && i==7){
                // 38 links
                printf( "\n                                  " \
                        "%.79s     " \
                        "", cWeakline);
            }else if(l==2 && i==8){
                // 42 links
                printf( "\n                                  " \
                        "%.79s     " \
                        "\n" \
                        // 43 links
                        "                                  " \
                        "%.79s     " \
                        "\n" \
                        "                                  " \
                        "     1       2       3    " \
                        "     4       5       6    " \
                        "     7       8       9    X", cEmptyline, cBottomline);
            }
            printf("\n");
        }
    }
    //*/
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: KandidatenGenerieren()                                          *
 * Parameter: none                                                           *
 * Rückgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void KandidatenGenerieren(){
    int i, j, k;

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            for(k=0; k<9; k++){
                if(ZahlAnPositionPruefen(&spiel.iSpiel, i, j, k+1)){
                    spiel.iHilfsfelder[i][j][k] = k+1;
                    iZeitStartWert = iZeitStartWert -5;
                }else{
                    spiel.iHilfsfelder[i][j][k] = 0;
                }
            }
        }
    }

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: ZahlEintragen()                                                 *
 * Parameter: int iPositionY, int iPositionX, int iZahl                      *
 * Rückgabewert: none                                                        *
 * Beschreibung: Trägt eine bestimmte Zahl an bestimmter Position ein.       *
 *               Löscht außerdem Kandidaten nach Spielregeln.                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ZahlEintragen(int iPositionY, int iPositionX, int iZahl){
    int i, j, iBlockY, iBlockX;

    if((double)(iPositionY)/3<=1){
        iBlockY = 0;
    }else if((double)(iPositionY)/3<=2){
        iBlockY = 1;
    }else if((double)(iPositionY)/3<=3){
        iBlockY = 2;
    }
    if((double)(iPositionX)/3<=1){
        iBlockX = 0;
    }else if((double)(iPositionX)/3<=2){
        iBlockX = 1;
    }else if((double)(iPositionX)/3<=3){
        iBlockX = 2;
    }

    if(spiel.iAnfangsfelder[iPositionY-1][iPositionX-1]==0){
        spiel.iSpiel[iPositionY-1][iPositionX-1] = iZahl;

        for(i=0; i<9; i++){
            spiel.iHilfsfelder[iPositionY-1][iPositionX-1][i] = 0;
        }

        for(i=0; i<9; i++){
            if(spiel.iHilfsfelder[i][iPositionX-1][iZahl-1]==iZahl){
                spiel.iHilfsfelder[i][iPositionX-1][iZahl-1] = 0;
            }
            if(spiel.iHilfsfelder[iPositionY-1][i][iZahl-1]==iZahl){
                spiel.iHilfsfelder[iPositionY-1][i][iZahl-1] = 0;
            }
        }
        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
                if(spiel.iHilfsfelder[i+(3*iBlockY)][j+(3*iBlockX)][iZahl-1]==iZahl){
                    spiel.iHilfsfelder[i+(3*iBlockY)][j+(3*iBlockX)][iZahl-1] = 0;
                }
            }
        }

        if(spiel.iLoesung[iPositionY-1][iPositionX-1]==iZahl){
            punkteBerechnen(1);
        }else{
            punkteBerechnen(2);
        }

    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: LoesungEintragen()                                              *
 * Parameter: int iPositionY, int iPositionX                                 *
 * Rückgabewert: int (0, 1)                                                  *
 * Beschreibung: Trägt die richtige Zahl an bestimmter Position ein.         *
 *               Löscht außerdem Kandidaten nach Spielregeln.                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int LoesungEintragen(int iPositionY, int iPositionX){
    int i, j, iBlockY, iBlockX;

    if((double)(iPositionY)/3<=1){
        iBlockY = 0;
    }else if((double)(iPositionY)/3<=2){
        iBlockY = 1;
    }else if((double)(iPositionY)/3<=3){
        iBlockY = 2;
    }
    if((double)(iPositionX)/3<=1){
        iBlockX = 0;
    }else if((double)(iPositionX)/3<=2){
        iBlockX = 1;
    }else if((double)(iPositionX)/3<=3){
        iBlockX = 2;
    }

    if(spiel.iAnfangsfelder[iPositionY-1][iPositionX-1]==0){
        spiel.iSpiel[iPositionY-1][iPositionX-1] = spiel.iLoesung[iPositionY-1][iPositionX-1];

        for(i=0; i<9; i++){
            spiel.iHilfsfelder[iPositionY-1][iPositionX-1][i] = 0;
        }

        for(i=0; i<9; i++){
            if(spiel.iHilfsfelder[i][iPositionX-1][spiel.iLoesung[iPositionY-1][iPositionX-1]-1]==spiel.iLoesung[iPositionY-1][iPositionX-1]){
                spiel.iHilfsfelder[i][iPositionX-1][spiel.iLoesung[iPositionY-1][iPositionX-1]-1] = 0;
            }
            if(spiel.iHilfsfelder[iPositionY-1][i][spiel.iLoesung[iPositionY-1][iPositionX-1]-1]==spiel.iLoesung[iPositionY-1][iPositionX-1]){
                spiel.iHilfsfelder[iPositionY-1][i][spiel.iLoesung[iPositionY-1][iPositionX-1]-1] = 0;
            }
        }
        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
                if(spiel.iHilfsfelder[i+(3*iBlockY)][j+(3*iBlockX)][spiel.iLoesung[iPositionY-1][iPositionX-1]-1]==spiel.iLoesung[iPositionY-1][iPositionX-1]){
                    spiel.iHilfsfelder[i+(3*iBlockY)][j+(3*iBlockX)][spiel.iLoesung[iPositionY-1][iPositionX-1]-1] = 0;
                }
            }
        }
        return 1;
    }else{
        return 0;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: KandidatEintragenEntfernen()                                    *
 * Parameter: int iPositionY, int iPositionX, int iZahl                      *
 * Rückgabewert: int (0 oder 1)                                              *
 * Beschreibung: Trägt bestimmten Kandidaten an bestimmter Position ein.     *
 *               Eingabe von 0 "löscht" den Kandidaten wieder.               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int KandidatEintragenEntfernen(int iPositionY, int iPositionX, int iZahl){
    if(spiel.iSpiel[iPositionY-1][iPositionX-1]==0){
        if(spiel.iHilfsfelder[iPositionY-1][iPositionX-1][iZahl-1]==0){
            spiel.iHilfsfelder[iPositionY-1][iPositionX-1][iZahl-1] = iZahl;
        }else if(spiel.iHilfsfelder[iPositionY-1][iPositionX-1][iZahl-1]==iZahl){
            spiel.iHilfsfelder[iPositionY-1][iPositionX-1][iZahl-1] = 0;
        }
        return 1;
    }else{
        return 0;
    }
}
