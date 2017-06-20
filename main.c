#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test();
void SudokuInitialisieren();
int ZufallszahlGenerieren();
void LoesungErstellen();
void SudokuErstellen();
void LoesungFinden();
int ZahlAnPositionPruefen();
int KomplettPruefen();
void SudokuAusgeben();
int ZahlEintragen();
void HilfsfelderSetzen();

typedef struct{
    int iHilfsfelder[9][9][9];
    int iSpiel[9][9];
    int iAnfangsfelder[9][9];
    int iLoesung[9][9];
    int iAnz;
} SUDOKU;
SUDOKU spiel;

int mainLogik(){
    int k;
    srand(time(NULL));

    while(spiel.iAnz!=1){
        test();
    }

    system("pause");

    return k;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: test()                                                          *
 * Parameter: none                                                           *
 * Rückgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void test(){
    int i, j;
    int posx, posy, zahl;

    SudokuInitialisieren();

    LoesungErstellen(0, 0);

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            spiel.iAnfangsfelder[i][j] = spiel.iLoesung[i][j];
        }
    }

    for(i=0; i<30; i++){
        SudokuErstellen();
    }

    LoesungFinden(0, 0);

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            spiel.iSpiel[i][j] = spiel.iAnfangsfelder[i][j];
        }
    }

    HilfsfelderSetzen();

    SudokuAusgeben();

    do{
        printf("Bitte geben Sie PositionX ein:");
        scanf("%i", &posx);

        printf("Bitte geben Sie PositionY ein:");
        scanf("%i", &posy);

        printf("Bitte geben Sie die Zahl ein:");
        scanf("%i", &zahl);

        ZahlEintragen(posy, posx, zahl);

        HilfsfelderSetzen();

        SudokuAusgeben();
    }while(zahl<10);



}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: SudokuInitialisieren()                                          *
 * Parameter: none                                                           *
 * Rückgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SudokuInitialisieren(){
    int i, j, k;

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            spiel.iSpiel[i][j] = 0;
            spiel.iAnfangsfelder[i][j] = 0;
            spiel.iLoesung[i][j] = 0;
            for(k=0; k<9; k++){
                spiel.iHilfsfelder[i][j][k] = k+1;
            }
        }
    }

    spiel.iAnz = 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: ZufallszahlGenerieren()                                         *
 * Parameter: int iVon, int iBis                                             *
 * Rückgabewert: int iZufallszahl                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int ZufallszahlGenerieren(int iVon, int iBis){
    int iZufallszahl = rand()%(iBis+1-iVon)+iVon;
    return iZufallszahl;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: PositionSetzen()                                                *
 * Parameter: int iPositionY, int iPositionX                                 *
 * Rückgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 void PositionSetzen(int *iPositionY, int *iPositionX){
        *iPositionY = (*iPositionY + (*iPositionX-(*iPositionX)%9)/9)%9;
        *iPositionX = (*iPositionX)%9;
 }

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: LoesungErstellen()                                              *
 * Parameter: int iPositionY, int iPositionX                                 *
 * Rückgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LoesungErstellen(int iPositionY, int iPositionX){
    int i, j, iZahl=ZufallszahlGenerieren(1,9);

    PositionSetzen(&iPositionY, &iPositionX);

    if(spiel.iLoesung[iPositionY][iPositionX]!=0){
        LoesungErstellen(iPositionY, iPositionX+1);
    }else{
        for(i=0; i<9; i++){
            if(ZahlAnPositionPruefen(&spiel.iLoesung, iPositionY, iPositionX, (iZahl+i)%9+1)){
                spiel.iLoesung[iPositionY][iPositionX] = (iZahl+i)%9+1;
                //SudokuAusgeben();
                if(KomplettPruefen(&spiel.iLoesung[0][0])==0){
                    LoesungErstellen(iPositionY, iPositionX+1);
                }
                if(KomplettPruefen(&spiel.iLoesung[0][0])==0){
                    spiel.iLoesung[iPositionY][iPositionX] = 0;
                }
            }
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: SudokuErstellen()                                               *
 * Parameter: none                                                           *
 * Rückgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SudokuErstellen(){
    int iPositionY = ZufallszahlGenerieren(0,8),
        iPositionX = ZufallszahlGenerieren(0,8);

    if(spiel.iAnfangsfelder[iPositionY][iPositionX]!=0){
        spiel.iAnfangsfelder[iPositionY][iPositionX] = 0;
    }else{
        SudokuErstellen();
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: LoesungFinden()                                                 *
 * Parameter: int iPositionY, int iPositionX                                 *
 * Rückgabewert: none                                                        *
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
                    SudokuAusgeben();
                }
                spiel.iAnfangsfelder[iPositionY][iPositionX] = 0;
            }
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: ZahlAnPositionPruefen()                                               *
 * Parameter: int *iSudoku, int iPositionY, int iPositionX, int iZahl        *
 * Rückgabewert: int iPruef                                                  *
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
 * Funktion: SudokuAusgaben()                                                *
 * Parameter: none                                                           *
 * Rückgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SudokuAusgeben(){
    int i, j, k, l, m, n, o;
    char cTopline[79];
    char cBottomline[79];
    char cStrongline[79];
    char cWeakline[79];
    char cEmptyline[79];

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
            if(spiel.iSpiel[i][j]==0){
                printf("   ");
            }else{
                printf(" %i ", spiel.iSpiel[i][j]);
            }
            if(j==2 || j==5){
                printf(" | ");
            }
        }
        printf("   ");
        for(j=0; j<9; j++){
            if(spiel.iAnfangsfelder[i][j]==0){
                printf("   ");
            }else{
                printf(" %i ", spiel.iAnfangsfelder[i][j]);
            }
            if(j==2 || j==5){
                printf(" | ");
            }
        }
        printf("   ");
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
            printf("\n----------+-----------+---------- " \
                   "  ----------+-----------+---------- "  \
                   "  ----------+-----------+----------");
        }

        printf("\n");
    }
    */

    printf( "Zeile 1 links      " \
            "%.79s     " \
            "Zeile 1 rechts\n" \
            "Zeile 2 links      " \
            "%.79s     " \
            "Zeile 2 rechts\n", cTopline, cEmptyline);
    for(i=0; i<9; i++){
        for(l=0; l<3; l++){
            switch(i){
                case 0: switch(l){
                    case 0: printf("Zeile 3 links      "); break;
                    case 1: printf("Zeile 4 links      "); break;
                    case 2: printf("Zeile 5 links      "); break;
                } break;
                case 1: switch(l){
                    case 0: printf("Zeile 7 links      "); break;
                    case 1: printf("Zeile 8 links      "); break;
                    case 2: printf("Zeile 9 links      "); break;
                } break;
                case 2: switch(l){
                    case 0: printf("Zeile 11 links     "); break;
                    case 1: printf("Zeile 12 links     "); break;
                    case 2: printf("Zeile 13 links     "); break;
                } break;
                case 3: switch(l){
                    case 0: printf("Zeile 17 links     "); break;
                    case 1: printf("Zeile 18 links     "); break;
                    case 2: printf("Zeile 19 links     "); break;
                } break;
                case 4: switch(l){
                    case 0: printf("Zeile 21 links     "); break;
                    case 1: printf("Zeile 22 links     "); break;
                    case 2: printf("Zeile 23 links     "); break;
                } break;
                case 5: switch(l){
                    case 0: printf("Zeile 25 links     "); break;
                    case 1: printf("Zeile 26 links     "); break;
                    case 2: printf("Zeile 27 links     "); break;
                } break;
                case 6: switch(l){
                    case 0: printf("Zeile 31 links     "); break;
                    case 1: printf("Zeile 32 links     "); break;
                    case 2: printf("Zeile 33 links     "); break;
                } break;
                case 7: switch(l){
                    case 0: printf("Zeile 35 links     "); break;
                    case 1: printf("Zeile 36 links     "); break;
                    case 2: printf("Zeile 37 links     "); break;
                } break;
                case 8: switch(l){
                    case 0: printf("Zeile 39 links     "); break;
                    case 1: printf("Zeile 40 links     "); break;
                    case 2: printf("Zeile 41 links     "); break;
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
                    case 0: printf("   Zeile 3 rechts"); break;
                    case 1: printf("   Zeile 4 rechts"); break;
                    case 2: printf("   Zeile 5 rechts"); break;
                } break;
                case 1: switch(l){
                    case 0: printf("   Zeile 7 rechts"); break;
                    case 1: printf("   Zeile 8 rechts"); break;
                    case 2: printf("   Zeile 9 rechts"); break;
                } break;
                case 2: switch(l){
                    case 0: printf("   Zeile 11 rechts"); break;
                    case 1: printf("   Zeile 12 rechts"); break;
                    case 2: printf("   Zeile 13 rechts"); break;
                } break;
                case 3: switch(l){
                    case 0: printf("   Zeile 17 rechts"); break;
                    case 1: printf("   Zeile 18 rechts"); break;
                    case 2: printf("   Zeile 19 rechts"); break;
                } break;
                case 4: switch(l){
                    case 0: printf("   Zeile 21 rechts"); break;
                    case 1: printf("   Zeile 22 rechts"); break;
                    case 2: printf("   Zeile 23 rechts"); break;
                } break;
                case 5: switch(l){
                    case 0: printf("   Zeile 25 rechts"); break;
                    case 1: printf("   Zeile 26 rechts"); break;
                    case 2: printf("   Zeile 27 rechts"); break;
                } break;
                case 6: switch(l){
                    case 0: printf("   Zeile 31 rechts"); break;
                    case 1: printf("   Zeile 32 rechts"); break;
                    case 2: printf("   Zeile 33 rechts"); break;
                } break;
                case 7: switch(l){
                    case 0: printf("   Zeile 35 rechts"); break;
                    case 1: printf("   Zeile 36 rechts"); break;
                    case 2: printf("   Zeile 37 rechts"); break;
                } break;
                case 8: switch(l){
                    case 0: printf("   Zeile 39 rechts"); break;
                    case 1: printf("   Zeile 40 rechts"); break;
                    case 2: printf("   Zeile 41 rechts"); break;
                } break;
            }
            if(l==2 && i==0){
                printf( "\nZeile 6 links      " \
                        "%.79s     " \
                        "Zeile 6 rechts", cWeakline);
            }else if(l==2 && i==1){
                printf( "\nZeile 10 links     " \
                        "%.79s     " \
                        "Zeile 10 rechts", cWeakline);
            }else if(l==2 &&i==2){
                printf( "\nZeile 14 links     " \
                        "%.79s     " \
                        "Zeile 14 rechts\n" \
                        "Zeile 15 links     " \
                        "%.79s     " \
                        "Zeile 15 rechts\n" \
                        "Zeile 16 links     " \
                        "%.79s     " \
                        "Zeile 16 rechts", cEmptyline, cStrongline, cEmptyline);
            }else if(l==2 && i==3){
                printf( "\nZeile 20 links     " \
                        "%.79s     " \
                        "Zeile 20 rechts", cWeakline);
            }else if(l==2 && i==4){
                printf( "\nZeile 24 links     " \
                        "%.79s     " \
                        "Zeile 24 rechts", cWeakline);
            }else if(l==2 && i==5){
                printf( "\nZeile 28 links     " \
                        "%.79s     " \
                        "Zeile 28 rechts\n" \
                        "Zeile 29 links     " \
                        "%.79s     " \
                        "Zeile 29 rechts\n" \
                        "Zeile 30 links     " \
                        "%.79s     " \
                        "Zeile 30 rechts", cEmptyline, cStrongline, cEmptyline);
            }else if(l==2 && i==6){
                printf( "\nZeile 34 links     " \
                        "%.79s     " \
                        "Zeile 34 rechts", cWeakline);
            }else if(l==2 && i==7){
                printf( "\nZeile 38 links     " \
                        "%.79s     " \
                        "Zeile 38 rechts", cWeakline);
            }else if(l==2 && i==8){
                printf( "\nZeile 42 links     " \
                        "%.79s     " \
                        "Zeile 42 rechts\n" \
                        "Zeile 43 links     " \
                        "%.79s     " \
                        "Zeile 43 rechts\n", cEmptyline, cBottomline);
            }
            printf("\n");
        }
    }
    /*
    printf("\nB1 = %c", '\xB1');
    printf("\nB2 = %c", '\xB2');
    printf("\nB3 = %c", '\xB3');
    printf("\nB4 = %c", '\xB4');
    printf("\nBF = %c", '\xBF');
    printf("\nC0 = %c", '\xC0');
    printf("\nC1 = %c", '\xC1');
    printf("\nC2 = %c", '\xC2');
    printf("\nC3 = %c", '\xC3');
    printf("\nC4 = %c", '\xC4');
    printf("\nC5 = %c", '\xC5');
    printf("\nD9 = %c", '\xD9');
    printf("\nDA = %c", '\xDA');
    */
}

void HilfsfelderSetzen(){
    int i, j, k;

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            for(k=0; k<9; k++){
                if(ZahlAnPositionPruefen(&spiel.iSpiel, i, j, k+1)){
                    spiel.iHilfsfelder[i][j][k] = k+1;
                }else{
                    spiel.iHilfsfelder[i][j][k] = 0;
                }
            }
        }
    }

}

int ZahlEintragen(int iPositionY, int iPositionX, int iZahl){
    if(spiel.iAnfangsfelder[iPositionY-1][iPositionX-1]==0){
        spiel.iSpiel[iPositionY-1][iPositionX-1] = iZahl;
        if(spiel.iLoesung[iPositionY-1][iPositionX-1]== iZahl){
            return 1;
        }else{
            return 2;
        }
    }else{
        return 0;
    }
}
