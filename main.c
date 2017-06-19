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

typedef struct{
    int iHilfsfelder[9][9][9];
    int iFelder[9][9];
    int iLoesung[9][9];
    int iAnz;
} SUDOKU;
SUDOKU spiel;

int main(){
    int k;
    srand(time(NULL));

    while(spiel.iAnz!=1){
        test();
    }

    SudokuAusgeben();

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

    SudokuInitialisieren();

    LoesungErstellen(0, 0);

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            spiel.iFelder[i][j] = spiel.iLoesung[i][j];
        }
    }

    for(i=0; i<40; i++){
        SudokuErstellen();
    }

    LoesungFinden(0, 0);

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
            spiel.iFelder[i][j] = 0;
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
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int ZufallszahlGenerieren(int iVon, int iBis){
    int iZufallszahl = rand()%(iBis+1-iVon)+iVon;
    return iZufallszahl;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: PositionSetzen()                                                *
 * Parameter: int iPositionX, int iPositionY                                 *
 * Rückgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 void PositionSetzen(int *iPositionX, int *iPositionY){
        *iPositionX = (*iPositionX + (*iPositionY-(*iPositionY)%9)/9)%9;
        *iPositionY = (*iPositionY)%9;
 }

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: LoesungErstellen()                                              *
 * Parameter: int iPositionX, int iPositionY                                 *
 * Rückgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LoesungErstellen(int iPositionX, int iPositionY){
    int i, j, iZahl=ZufallszahlGenerieren(1,9);

    PositionSetzen(&iPositionX, &iPositionY);

    if(spiel.iLoesung[iPositionX][iPositionY]!=0){
        LoesungErstellen(iPositionX, iPositionY+1);
    }else{
        for(i=0; i<9; i++){
            if(ZahlAnPositionPruefen(&spiel.iLoesung, iPositionX, iPositionY, (iZahl+i)%9+1)){
                spiel.iLoesung[iPositionX][iPositionY] = (iZahl+i)%9+1;
                SudokuAusgeben();
                if(KomplettPruefen(&spiel.iLoesung[0][0])==0){
                    LoesungErstellen(iPositionX, iPositionY+1);
                }
                if(KomplettPruefen(&spiel.iLoesung[0][0])==0){
                    spiel.iLoesung[iPositionX][iPositionY] = 0;
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
    int iPositionX = ZufallszahlGenerieren(0,8),
        iPositionY = ZufallszahlGenerieren(0,8);

    if(spiel.iFelder[iPositionX][iPositionY]!=0){
        spiel.iFelder[iPositionX][iPositionY] = 0;
    }else{
        SudokuErstellen();
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: LoesungFinden()                                                 *
 * Parameter: int iPositionX, int iPositionY                                 *
 * Rückgabewert: none                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LoesungFinden(int iPositionX, int iPositionY){
    int i, j;

    PositionSetzen(&iPositionX, &iPositionY);

    if(spiel.iFelder[iPositionX][iPositionY]!=0 && spiel.iAnz<2){
        LoesungFinden(iPositionX, iPositionY+1);
    }else{
        for(i=0; i<9; i++){
            if(ZahlAnPositionPruefen(&spiel.iFelder, iPositionX, iPositionY, i+1)){
                spiel.iFelder[iPositionX][iPositionY] = i+1;
                SudokuAusgeben();
                if(KomplettPruefen(&spiel.iFelder[0][0])==0 && spiel.iAnz<2){
                    LoesungFinden(iPositionX, iPositionY+1);
                }else{
                    for(i=0; i<9; i++){
                        for(j=0; j<9; j++){
                            spiel.iLoesung[i][j] = spiel.iFelder[i][j];
                        }
                    }
                    spiel.iAnz++;
                    SudokuAusgeben();
                }
                spiel.iFelder[iPositionX][iPositionY] = 0;
            }
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Funktion: ZahlAnPositionPruefen()                                               *
 * Parameter: int *iSudoku, int iPositionX, int iPositionY, int iZahl        *
 * Rückgabewert: int iPruef                                                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int ZahlAnPositionPruefen(int *iSudoku, int iPositionX, int iPositionY, int iZahl){
    int i, j, iBlockX, iBlockY, iPruef;

    if(*(iSudoku+(iPositionX*9)+iPositionY)==0){
        iPruef = 1;
        for(i=0; i<9; i++){
            if(*(iSudoku+(iPositionX*9)+i)==iZahl ||
               *(iSudoku+(i*9)+iPositionY)==iZahl ){
                iPruef = 0;
            }
        }
        if((double)(iPositionX+1)/3<=1){
            iBlockX = 0;
        }else if((double)(iPositionX+1)/3<=2){
            iBlockX = 1;
        }else if((double)(iPositionX+1)/3<=3){
            iBlockX = 2;
        }
        if((double)(iPositionY+1)/3<=1){
            iBlockY = 0;
        }else if((double)(iPositionY+1)/3<=2){
            iBlockY = 1;
        }else if((double)(iPositionY+1)/3<=3){
            iBlockY = 2;
        }
        for(i=0; i<3; i++){
            for(j=0; j<3; j++){
                if(*(iSudoku+(i+(3*iBlockX))*9+(j+(3*iBlockY)))==iZahl){
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
    int i, j;

    system("cls");

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(spiel.iFelder[i][j]==0){
                printf("   ");
            }else{
                printf(" %i ", spiel.iFelder[i][j]);
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
                   "  ----------+-----------+----------");
        }

        printf("\n");
    }

    printf("\nAnzahl der Moeglichkeiten: %i\n", spiel.iAnz);
}
