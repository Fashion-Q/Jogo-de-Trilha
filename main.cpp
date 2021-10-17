#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio2.h>
#include <windows.h>
#include <fstream>

using namespace std;
const int cores[3]={/*CorJogador1*/10,/*CorJogador2*/9,/*CorInativo*/8};

void inicio(int vetorSetaXY[2][2],const int cores[3], char nome1[255], char nome2[255], char nome3[255],int& jBorda1, int& jBorda2);
void setaVere1(int seta,int setaXY[2][2],int& x, int& y);
void setaVere2(int seta,int setaXY[2][2],int& x, int& y);
void limparTexto(int x, int y, int xVezes, int yVezes);
void borda(int x, int y, int xVezes, int yVezes, int MilGrau);
void borda(int x, int y, int xVezes, int yVezes);
void jogador1(int const cores[3], bool vez, int& pecas1, char nome1[255]);
void jogador2(int const cores[3],bool vez,int& pecas2, char nome2[25]);
bool jogarPosicao(int x,int y, bool& vez, int const Cores[3], int M[8][3],bool liberado, int xAnterior, int yAnterior);
bool moinho(int M[8][3], int horizontal[1][8],int vertical[8][1], int jogador, int vetorSetaXY[2][2], int& p1, int& p2,char nome1[255],char nome2[255]);
void removerPecas(int d,int j, int horizontal[1][8],int vertical[8][1], int jogador, int vetorSetaXY[2][2],int M[8][3], int& p1, int& p2,char nome1[255], char nome2[255]);
void limparPecas(int x, int y,int M[8][3], int horizontal[1][8],int vertical[8][1]);
void trinca(bool t, int d, char nome1[255], char nome2[255]);
bool marcarEscolha(int x,int y,bool vez, int cor, int M[8][3]);
bool trancar(int M[8][3], bool vez);
bool moinhoHorizontalVertical(int x, int y, int horizontal[1][8],int vertical[8][1]);
bool verificarPrisaoDeMoinho(int horizontal[1][8],int vertical[8][1],int M[8][3], int j);
void designerDoJogo();
void creditos();

int main(){

    int controleSeta,vetorSetaXY[2][2] = {0},x=0,y=0,xAnterior=-1,yAnterior=-1,cor=0,contagemRegressiva=10;
    int pecas1=0,pecas2=0,jogadas=0,matriz[8][3]={0},moinhoHorizontal[1][8]={0},moinhoVertical[8][1]={0},jBorda1,jBorda2;
    bool vez = true, joguei = true, fezMoinho = false,liberado = true,tranca=true;
    char nome1[255], nome2[255], nome3[255];
    inicio(vetorSetaXY,cores,nome1,nome2,nome3,jBorda1,jBorda2);
    borda(135,3,26,5);//borda do jogador 1
    borda(135,9,26,5);//borda do jogador 2
    jogador1(cores,true,pecas1,nome1);
    jogador2(cores,false,pecas2,nome2);
    textcolor(cores[0]);

    do{ //principal
        gotoxy(vetorSetaXY[0][0],vetorSetaXY[1][0]);printf("-->");
        controleSeta = getch();

        if (controleSeta == 0xE0){
            controleSeta = getch();
            setaVere1(controleSeta,vetorSetaXY,x,y);
            //gotoxy(136,38);printf("x1 [%d] ",x);
            //gotoxy(136,39);printf("y2 [%d] ",y);
        }
        else if (controleSeta == 13){
            joguei = jogarPosicao(x,y,vez,cores,matriz,liberado,xAnterior,yAnterior);
            if (vez == false && joguei == true){
                moinho(matriz,moinhoHorizontal,moinhoVertical,1,vetorSetaXY,pecas1,pecas2,nome1,nome2);
                jogadas++;
                pecas1++;
                jogador1(cores,false,pecas1,nome1);
                jogador2(cores,true,pecas2,nome2);
                textcolor(cores[1]);
                //gotoxy(136,40);printf("Jogadas [%d] ",jogadas);
            }
            else if (vez == true && joguei == true){
                moinho(matriz,moinhoHorizontal,moinhoVertical,2,vetorSetaXY,pecas1,pecas2,nome1,nome2);
                jogadas++;
                pecas2++;
                jogador1(cores,true,pecas1,nome1);
                jogador2(cores,false,pecas2,nome2);
                textcolor(cores[0]);
                //gotoxy(136,40);printf("Jogadas [%d] ",jogadas);
            }
            joguei = true;
            int xx=36,yy=22;
            /*for (int y=0;y<3;y++){
                for (int x=0;x<8;x++){
                    gotoxy(xx+=2,yy);printf("%d",matriz[x][y]);
                }
                yy++;
                xx = 36;
    }*/
        }
    }while(jogadas < 18); //principal
    PlaySound(TEXT("primeiraInst.wav"),NULL,SND_LOOP | SND_ASYNC);
    borda(49,20,29,1,10);
    setlocale(LC_ALL,"Portuguese");
    gotoxy(50,21);printf("Movimento de peça começará!");
    setlocale(LC_ALL,"C");
    //############################################################################################################################################
    getch();
    limparTexto(49,19,30,4);
    liberado = false;
    bool liberadoAzul=false,liberadoVerde=false;
    //tranca = trancar(matriz,vez);
    do{ //principal

        gotoxy(vetorSetaXY[0][0],vetorSetaXY[1][0]);printf("-->");
        controleSeta = getch();

        if (controleSeta == 0xE0){
            controleSeta = getch();
            setaVere1(controleSeta,vetorSetaXY,x,y);
            //gotoxy(136,38);printf("x3 [%d] ",x);
            //gotoxy(136,39);printf("y4 [%d] ",y);
        }
        else if (controleSeta == 13){
            if (vez)
                cor = 6;
            else
                cor = 11;
            if (tranca = trancar(matriz,vez)){
                joguei = marcarEscolha(x,y,vez,cor,matriz);
                //gotoxy(136,36);printf("vez [%d] ",vez);
            if (joguei){
                xAnterior = x;
                yAnterior = y;
                do{
                    gotoxy(vetorSetaXY[0][0],vetorSetaXY[1][0]);printf("-->");
                    controleSeta = getch();

                        if (controleSeta == 0xE0){
                            controleSeta = getch();
                            setaVere1(controleSeta,vetorSetaXY,x,y);
                            //gotoxy(136,38);printf("x3 [%d] ",x);
                            //gotoxy(136,39);printf("y4 [%d] ",y);
                        }
                        else if (controleSeta == 13){
                            if (vez == true && pecas1 == 3){
                                liberado = true;
                            }
                            if (vez == false && pecas2 == 3){
                                liberado = true;
                            }
                            joguei = jogarPosicao(x,y,vez,cores,matriz,liberado,xAnterior,yAnterior);
                            if (joguei){
                                limparPecas(xAnterior,yAnterior,matriz,moinhoHorizontal,moinhoVertical);
                                if (pecas1 == 3 && pecas2 == 3 && contagemRegressiva == 10){
                                    textcolor(RED);
                                    borda(137,38,24,1,10);
                                    gotoxy(138,39);printf("Contagem Regressiva:%d",contagemRegressiva--);
                                    if (vez)
                                        textcolor(10);
                                    else
                                        textcolor(9);
                                }
                                else if (contagemRegressiva <= 9){
                                    textcolor(RED);
                                    gotoxy(158,39);printf("%d ",contagemRegressiva--);
                                    if (vez)
                                        textcolor(10);
                                    else
                                        textcolor(9);
                                }
                            }
                            else{
                                if (vez)
                                    cor = 10;
                                else
                                    cor = 9;
                                    marcarEscolha(xAnterior,yAnterior,vez,cor,matriz);
                            }
                        }
                }while(controleSeta != 13);
            }
        }
        else
            joguei = false;
            //joguei = jogarPosicao(x,y,vez,cores,matriz);
            if (vez == false && joguei == true){
                moinho(matriz,moinhoHorizontal,moinhoVertical,1,vetorSetaXY,pecas1,pecas2,nome1,nome2);
                jogador1(cores,false,pecas1,nome1);
                jogador2(cores,true,pecas2,nome2);
                textcolor(cores[1]);
            }
            else if (vez == true && joguei == true){
                moinho(matriz,moinhoHorizontal,moinhoVertical,2,vetorSetaXY,pecas1,pecas2,nome1,nome2);
                jogador1(cores,true,pecas1,nome1);
                jogador2(cores,false,pecas2,nome2);
                textcolor(cores[0]);
            }
            joguei = true;
            liberado = false;
            //nao ta utilizando fezMoinho = false;
            int xx=37,yy=22;
            /*for (int y=0;y<3;y++){
                for (int x=0;x<8;x++){
                    gotoxy(xx+=2,yy);printf("%d",matriz[x][y]);
                }
                yy++;
                xx = 37;
            }*/
                }
    }while(pecas1 > 2 && pecas2 > 2 && tranca == true && contagemRegressiva >= 0); //segunda instancia
    if (contagemRegressiva == -1){
        textcolor(RED);
        borda(54,22,19,1,10);
        gotoxy(55,23);printf("        EMPATE!");
        PlaySound(TEXT("vencedor.wav"),NULL, SND_ASYNC);
    }
    else if (pecas1 <3 ){
        textcolor(cores[1]);
        borda(54,22,jBorda2,1,10);
        gotoxy(55,23);printf("%s ganhou!", nome2);
        PlaySound(TEXT("vencedor.wav"),NULL, SND_ASYNC);
    }
    else if (pecas2 < 3){
        textcolor(cores[0]);
        borda(54,22,jBorda1,1,10);
        gotoxy(55,23);printf("%s ganhou!", nome1);
        PlaySound(TEXT("vencedor.wav"),NULL, SND_ASYNC);
    }
    else{
        if (vez){
            textcolor(cores[1]);
            borda(54,22,jBorda2,1,10);
            gotoxy(55,23);printf("%s ganhou!", nome2);
            PlaySound(TEXT("vencedor.wav"),NULL, SND_ASYNC);
        }
        else{
            textcolor(cores[0]);
            borda(54,22,jBorda1,1,10);
            gotoxy(55,23);printf("%s ganhou!", nome1);
            PlaySound(TEXT("vencedor.wav"),NULL, SND_ASYNC);
        }
    }
    Sleep(4000);
    //gotoxy(1,43);
    getch();
    clrscr();
    creditos();
    gotoxy(1,30);
    return 0;
}

bool trancar(int M[8][3], bool vez){
    int j; // j = jogador que está jogando atualmente
    if (vez)    //verificar se ele não está trancado
        j = 1;
    else
        j = 2;

    if (M[0][0] == j){ // A0
        if (M[1][0] == 0)
            return true;
        else if (M[3][0] == 0)
            return true;
    }

    if (M[1][0] == j){ // A1
        if (M[0][0] == 0)
            return true;
        else if (M[2][0] == 0)
            return true;
        else if (M[1][1] == 0)
            return true;
    }

    if (M[2][0] == j){ // A2
        if (M[1][0] == 0)
            return true;
        else if (M[4][0] == 0)
            return true;
    }

    if (M[3][0] == j){ // A3
        if (M[0][0] == 0)
            return true;
        else if (M[5][0] == 0)
            return true;
        if (M[3][1] == 0)
            return true;
    }

    if (M[4][0] == j){ // A4
        if (M[2][0] == 0)
            return true;
        else if (M[7][0] == 0)
            return true;
        else if (M[4][1] == 0)
            return true;
    }

    if (M[5][0] == j){ // A5
        if (M[3][0] == 0)
            return true;
        else if (M[6][0] == 0)
            return true;
    }

    if (M[6][0] == j){ // A6
        if (M[5][0] == 0)
            return true;
        else if (M[7][0] == 0)
            return true;
        else if (M[6][1] == 0)
            return true;
    }

    if (M[7][0] == j){ // A7
        if (M[6][0] == 0)
            return true;
        else if (M[4][0] == 0)
            return true;
    }

    if (M[0][1] == j){ // B0
        if (M[1][1] == 0)
            return true;
        else if (M[3][1] == 0)
             return true;
    }

    if (M[1][1] == j){ // B1
        if (M[1][0] == 0)
            return true;
        else if (M[1][2] == 0)
            return true;
        else if (M[0][1] == 0)
            return true;
        else if (M[2][1] == 0)
            return true;
    }

    if (M[2][1] == j){ // B2
        if (M[1][1] == 0)
            return true;
        else if (M[4][1] == 0)
            return true;
    }

    if (M[3][1] == j){ // B3
        if (M[3][0] == 0)
            return true;
        else if (M[3][2] == 0)
            return true;
        else if (M[0][1] == 0)
            return true;
        else if (M[5][1] == 0)
            return true;
    }

    if (M[4][1]==j){ // B4
        if (M[4][0] == 0)
            return true;
        else if (M[4][2] == 0)
            return true;
        else if (M[7][1] == 0)
            return true;
        else if (M[2][1] == 0)
            return true;
    }

    if (M[5][1]==j){ // B5
        if (M[3][1] == 0)
            return true;
        else if (M[6][1] == 0)
            return true;
    }

    if (M[6][1]==j){ // B6
        if (M[5][1] == 0)
            return true;
        else if (M[7][1] == 0)
            return true;
        else if (M[6][2] == 0)
            return true;
        else if (M[6][0] == 0)
            return true;
    }

    if (M[7][1] == j){ // B7
        if (M[4][1] == 0)
            return true;
        else if (M[6][1] == 0)
            return true;
    }

    if (M[0][2]==j){ // C0
        if (M[1][2] == 0)
            return true;
        else if (M[3][2] == 0)
            return true;
    }

    if (M[1][2]==j){ // C1
        if (M[0][2] == 0)
            return true;
        else if (M[2][2] == 0)
            return true;
        else if (M[1][1] == 0)
            return true;
    }

    if (M[2][2]==j){// C2
        if (M[4][2] == 0)
            return true;
        else if (M[1][2] == 0)
            return true;
    }

    if (M[3][2]==j){ // C3
        if (M[0][2] == 0)
            return true;
        else if (M[5][2] == 0)
            return true;
        else if (M[3][1] == 0)
            return true;
    }

    if (M[4][2]==j){ // C4
        if (M[2][2] == 0)
            return true;
        else if (M[7][2] == 0)
            return true;
        else if (M[4][1] == 0)
            return true;
    }

    if (M[5][2]==j){ // C5
        if (M[6][2] == 0)
            return true;
        else if (M[3][2] == 0)
            return true;
    }

    if (M[6][2]==j){ // C6
        if (M[5][2] == 0)
            return true;
        else if (M[7][2] == 0)
            return true;
        else if (M[6][1] == 0)
            return true;
    }

    if (M[7][2] == j){ // C7
        if (M[4][2] == 0)
            return true;
        else if (M[6][2] == 0)
            return true;
    }
    return false; // se ele chegar até aqui, significa que o jogador está preso
                  // e não tem para onde jogar, finaliza o jogo e ele perde.

}

void removerPecas(int d,int j, int horizontal[1][8],int vertical[8][1], int jogador, int vetorSetaXY[2][2],int M[8][3], int& p1, int& p2, char nome1[255], char nome2[255]){

    if (j == 1){
        trinca(true,d,nome1, nome2);
        j = 2;
    }
    else{
        trinca(false,d,nome1, nome2);
        j = 1;
    }
        /*gotoxy(37,33);printf("MOINHO VERDE H [%d]",d);
        PlaySound(TEXT("trinca.wav"),NULL, SND_ASYNC);
        bordaEspecial(137,31,24,2,5);
        setlocale(LC_ALL,"Portuguese");
        gotoxy(138,32);printf("Jogador 1 remove peça");
        gotoxy(138,33);printf("do jogador 2!");
        setlocale(LC_ALL,"C");*/
        //getch();
        Sleep(1500);
        int controleSeta,pecaRemovida=false,x=0,y=0;
        vetorSetaXY[0][1] = 136;
        vetorSetaXY[1][1] = 15; //iniciando a setaVere2
        gotoxy(vetorSetaXY[0][0],vetorSetaXY[1][0]);printf("   ");
        do{
            gotoxy(vetorSetaXY[0][1],vetorSetaXY[1][1]);printf("-->");
            controleSeta = getch();

            if (controleSeta == 0xE0){
                controleSeta = getch();
                setaVere2(controleSeta,vetorSetaXY,x,y);
            }
            else if (controleSeta == 13){
                if (M[x][y] == j && (moinhoHorizontalVertical(x,y,horizontal,vertical)
                                     || verificarPrisaoDeMoinho(horizontal,vertical,M,j))){
                    if (j == 2)
                        p2--;
                    else
                        p1--;
                    limparPecas(x,y,M,horizontal,vertical);
                    pecaRemovida = !pecaRemovida;
                }
                else{
                    PlaySound(TEXT("erro.wav"),NULL, SND_ASYNC);
                    textcolor(RED);
                    borda(56,22,19,1,5);
                    setlocale(LC_ALL,"Portuguese");
                    gotoxy(57, 23);printf("Escolha inválida!");
                    setlocale(LC_ALL,"C");
                    Sleep(2000);
                    limparTexto(56,22,25,3);
                    if (jogador == 1)
                        textcolor(10);
                    else
                        textcolor(9);
                    //pecaRemovida = !pecaRemovida;
                }
                    gotoxy(vetorSetaXY[0][1],vetorSetaXY[1][1]);printf("   ");
                    //gotoxy(148,40);printf("vetor [%d] ",vetorSetaXY[2][0]);
            }
        }while(!pecaRemovida);
        //Há um bug no jogo em si em que quando só tem moinho no mapa, os jogadores ficam
        //presos, esse controleSeta != 27 é para caso isso aconteça e não trave o jogo
        //pois não sabemos como funciona essa regra direita
        limparTexto(137,31,25,4);

}

bool moinho(int M[8][3], int horizontal[1][8],int vertical[8][1], int jogador, int vetorSetaXY[2][2], int& p1, int& p2,char nome1[255],char nome2[255]){

    int x,y,m,h=7;//o "h" serve pra controlar as casas da matriz
                  //vertical/horizontal quando não da pra usar o x/y

    for (y=0,m=0;y<3;y++){//verificação do moinho horizontal da matriz
        for (x=0;x<3;x++){//A0,A1,A2/B0,B1,B2/C0,C1,C2
            if (M[x][y] == jogador){
                m++;
            }
        }
        if (m == 3 && horizontal[0][y] == false){
            horizontal[0][y] = jogador;
            if (jogador == 1){
                removerPecas(y,1,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }
            else{
                removerPecas(y,2,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }
        }
        m=0;
    }

    for (x=3,m=0;x<5;x++){
        for (y=0;y<3;y++){//A3,B3,C3/A4,B4,C4
            if (M[x][y] == jogador){
                m++;
            }
        }
        if (m == 3 && horizontal[0][x] == false){
            horizontal[0][x] = jogador;
            if (jogador == 1){
                removerPecas(y,1,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }
            else{
                removerPecas(y,2,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }

        }
        m=0;
    }

    for (y=0,m=0;y<3;y++){//verificação do moinho horizontal da matriz
        for (x=5;x<8;x++){//A5,A6,A7/B5,B6,B7/C5,C6,C7
            if (M[x][y] == jogador){
                m++;
            }
        }
        if (m == 3 && horizontal[0][h] == false){
            horizontal[0][h] = jogador;
            if (jogador == 1){
                removerPecas(y,1,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }
            else{
                removerPecas(y,2,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }

        }
        h--;
        m=0;
    }

    for (y=0,m=0;y<3;y++){//verificação do moinho vertical da matriz
        for (x=0;x<=5;x+=2){//A0,A3,A5,B0,B3,B5,C0,C3,C5
            if (x == 2)
                x++;
            if (M[x][y] == jogador){
                m++;
            }
        }
        if (m == 3 && vertical[y][0] == false){
            vertical[y][0] = jogador;
            if (jogador == 1){
                removerPecas(y,1,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }
            else{
                removerPecas(y,2,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }

        }
        m=0;
    }

    for (x=1,m=0,h=3;x<7;x+=5,h++){//verificação do moinho vertical da matriz
        for (y=0;y<3;y++){//A1,B1,C1,A6,B6,C6
            if (M[x][y] == jogador){
                m++;
            }
        }
        if (m == 3 && vertical[h][0] == false){
            vertical[h][0] = jogador;
            if (jogador == 1){
                removerPecas(y,1,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }
            else{
                removerPecas(y,2,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }
        }
        m=0;
    }

    for (y=0,m=0,h=7;y<3;y++,h--){//verificação do moinho vertical da matriz
        for (x=2;x<=7;x+=2){//A2,A4,A7,B2,B4,B7,C2,C4,C7
            if (x == 6)
                x++;
            if (M[x][y] == jogador){
                m++;
            }
        }
        if (m == 3 && vertical[h][0] == false){
            vertical[h][0] = jogador;
            if (jogador == 1){
                removerPecas(y,1,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }
            else{
                removerPecas(y,2,horizontal,vertical,jogador,vetorSetaXY,M,p1,p2,nome1,nome2);
            }
        }
        m=0;
    }

    /*for (int i=0,a=65;i<8;i++){//print teste da matriz horizontal
        gotoxy(a+=2,28);printf("%d",horizontal[0][i]);
    }

    for (int i=0,a=20;i<8;i++){//print teste da matriz vertical
        gotoxy(83,a++);printf("%d",vertical[i][0]);
    }
    limparTexto(137,31,25,7);
    gotoxy(37,33);printf("                   ");*/

}

void jogador1(int const cores[3],bool vez, int& pecas1, char nome1[255]){
    if (vez){
    textcolor(cores[0]);
    gotoxy(136,4);printf("%s", nome1);
    setlocale(LC_ALL,"Portuguese");
    gotoxy(136,5);printf("Instância: Jogando  ");
    gotoxy(136,6);printf("Peças disponíveis: %d",pecas1);

    setlocale(LC_ALL,"C");
    }
    else{
    textcolor(cores[2]);
    gotoxy(136,4);printf("%s", nome1);
    setlocale(LC_ALL,"Portuguese");
    gotoxy(136,5);printf("Instância: Esperando");
    gotoxy(136,6);printf("Peças disponíveis: %d",pecas1);

    setlocale(LC_ALL,"C");
    }
}

void jogador2(int const cores[3],bool vez, int& pecas2, char nome2[255]){

    if (vez){
    textcolor(cores[1]);
    gotoxy(136,10);printf("%s", nome2);
    setlocale(LC_ALL,"Portuguese");
    gotoxy(136,11);printf("Instância: Jogando  ");
    gotoxy(136,12);printf("Peças disponíveis: %d",pecas2);

    setlocale(LC_ALL,"C");
    }
    else{
    textcolor(cores[2]);
    gotoxy(136,10);printf("%s", nome2);
    setlocale(LC_ALL,"Portuguese");
    gotoxy(136,11);printf("Instância: Esperando");
    gotoxy(136,12);printf("Peças disponíveis: %d",pecas2);

    setlocale(LC_ALL,"C");
    }
    textcolor(14);
}

void setaVere2(int seta, int setaXY[2][2], int& x, int& y){
    if (seta == 72){   // [seta para cima]
        if (setaXY[1][1] > 15){
            PlaySound(TEXT("hit1.wav"),NULL, SND_ASYNC);
            gotoxy(setaXY[0][1],setaXY[1][1]);printf("   ");
            setaXY[1][1]-=2;
            x--;
        }
    }
    else if (seta == 75){   // [seta para esquerda]
        if (setaXY[0][1]>136){
            PlaySound(TEXT("hit1.wav"),NULL, SND_ASYNC);
            gotoxy(setaXY[0][1],setaXY[1][1]);printf("   ");
            setaXY[0][1]-=9;
            y--;
        }
    }
    else if (seta == 77){   // [seta para direita]
        if (setaXY[0][1]<154){
            PlaySound(TEXT("hit1.wav"),NULL, SND_ASYNC);
            gotoxy(setaXY[0][1],setaXY[1][1]);printf("   ");
            setaXY[0][1]+=9;
            y++;
        }
    }
    else if (seta == 80){   // [seta para baixo]
        if (setaXY[1][1]<29){
            PlaySound(TEXT("hit1.wav"),NULL, SND_ASYNC);
            gotoxy(setaXY[0][1],setaXY[1][1]);printf("   ");
            setaXY[1][1]+=2;
            x++;
        }
    }
    /*else{

    }*/

}

void setaVere1(int seta, int setaXY[2][2], int& x, int& y){
    if (seta == 72){   // [seta para cima]
        if (setaXY[1][0] > 15){
            PlaySound(TEXT("hit1.wav"),NULL, SND_ASYNC);
            gotoxy(setaXY[0][0],setaXY[1][0]);printf("   ");
            setaXY[1][0]-=2;
            x--;
        }
    }
    else if (seta == 75){   // [seta para esquerda]
        if (setaXY[0][0]>136){
            PlaySound(TEXT("hit1.wav"),NULL, SND_ASYNC);
            gotoxy(setaXY[0][0],setaXY[1][0]);printf("   ");
            setaXY[0][0]-=9;
            y--;
        }
    }
    else if (seta == 77){   // [seta para direita]
        if (setaXY[0][0]<154){
            PlaySound(TEXT("hit1.wav"),NULL, SND_ASYNC);
            gotoxy(setaXY[0][0],setaXY[1][0]);printf("   ");
            setaXY[0][0]+=9;
            y++;
        }
    }
    else if (seta == 80){   // [seta para baixo]
        if (setaXY[1][0]<29){
            PlaySound(TEXT("hit1.wav"),NULL, SND_ASYNC);
            gotoxy(setaXY[0][0],setaXY[1][0]);printf("   ");
            setaXY[1][0]+=2;
            x++;
        }
    }
    /*else{

    }*/

}

void limparTexto(int x, int y, int xVezes, int yVezes){
    for (int j=0;j<yVezes;j++){
        gotoxy(x,y);
        for (int i=0;i<xVezes;i++)
            printf(" ");
        y++;
    }
}

void trinca(bool t, int d, char nome1[255], char nome2[255]){

    int tratamento;
    PlaySound(TEXT("trinca.wav"),NULL, SND_ASYNC);
    borda(137,31,24,2,5);
    if (t){
        //gotoxy(37,33);printf("MOINHO VERDE H [%d]",d);
        tratamento = strlen(nome1);
        if (tratamento > 10){
            gotoxy(138,32);
            for (int i=0;i<10;i++){
                printf("%c",nome1[i]);
            }setlocale(LC_ALL,"Portuguese");
            printf(" remove peça");
            setlocale(LC_ALL,"C");
        }
        else{
            gotoxy(138,32);
            int i=0;
            for(;i<tratamento;i++){
                printf("%c",nome1[i]);
            }
            tratamento-=i;
            for(;tratamento > 0;tratamento--){
                printf(" ");
            }setlocale(LC_ALL,"Portuguese");
            printf(" remove peça");
            setlocale(LC_ALL,"C");
        }
        gotoxy(138,33);printf("de ");
        tratamento = strlen(nome2);
        if (tratamento > 10){
            for(int i=0;i<10;i++){
                printf("%c",nome2[i]);
            }
            printf("!");
        }
        else{
            int i=0;
            for(;i<tratamento;i++){
                printf("%c",nome2[i]);
            }
            printf("!");
        }
    }
    else{
        //gotoxy(37,33);printf("MOINHO AZUL H [%d]",d);
        tratamento = strlen(nome2);
        if (tratamento > 10){
            gotoxy(138,32);
            for (int i=0;i<10;i++){
                printf("%c",nome2[i]);
            }setlocale(LC_ALL,"Portuguese");
            printf(" remove peça");
            setlocale(LC_ALL,"C");
        }
        else{
            gotoxy(138,32);
            int i=0;
            for(;i<tratamento;i++){
                printf("%c",nome2[i]);
            }
            tratamento-=i;
            for(;tratamento > 0;tratamento--){
                printf(" ");
            }setlocale(LC_ALL,"Portuguese");
            printf(" remove peça");
            setlocale(LC_ALL,"C");
        }
        gotoxy(138,33);printf("de ");
        tratamento = strlen(nome1);
        if (tratamento > 10){
            for(int i=0;i<10;i++){
                printf("%c",nome1[i]);
            }
            printf("!");
        }
        else{
            int i=0;
            for(;i<tratamento;i++){
                printf("%c",nome1[i]);
            }
            printf("!");
        }
    }

}

void borda (int x, int y, int xVezes, int yVezes, int MilGrau){

    if (xVezes % 2 != 0){
        xVezes++;
    }
        int bugVezes = x + (xVezes / 2);

        int esquerda = bugVezes,direita = bugVezes - 1;

        for (int i= bugVezes;i!= x;i--){
            gotoxy(esquerda--,y);
            printf("%c",205);

            gotoxy(direita++,y);
            printf("%c",205);

            Sleep(MilGrau);
        }

        gotoxy(x,y);
        printf("%c",201);
        gotoxy((x + xVezes - 1),y);
        printf("%c",187);
        y++;

        for (int i=y,j=0;j<yVezes;i++,j++){
            gotoxy(x,i);
            printf("%c",186);

            gotoxy(direita,i);
            printf("%c",186);
            Sleep(MilGrau);
        }

        gotoxy(x,(y + yVezes));
        printf("%c",200);
        gotoxy((x + xVezes - 1),(y + yVezes));
        printf("%c",188);

        esquerda = x + 1;
        direita = x + xVezes - 2;

        y--;
        for (int i= bugVezes;i!= x;i--){
            gotoxy(esquerda++,(y + yVezes + 1));
            if (esquerda != (bugVezes+1))
                printf("%c",205);

            gotoxy(direita--,(y + yVezes + 1));
            if (direita != (bugVezes-2))
                printf("%c",205);

            Sleep(MilGrau);
        }
}

void borda(int x, int y, int xVezes, int yVezes){ //(135,3,26,5)
    int i,j;
    gotoxy(x,y);
    printf("%c",201);

    for (i=0;i<xVezes;i++)
        printf("%c",205);
    printf("%c",187);

    xVezes+=x + 1;
    y++;
    gotoxy(x,y);
    j = 2;

    for (i=y ; j<yVezes ; i++,j++){
        gotoxy(x,i);
        printf("%c",186);
        gotoxy(xVezes,i);
        printf("%c",186);
    }

    gotoxy(x,i);
    printf("%c",200);
    gotoxy(xVezes,i);
    printf("%c",188);
    gotoxy(x+1,i);

    xVezes = xVezes - x - 1;

    for (i=0;i<xVezes;i++)
        printf("%c",205);
}

void inicio(int vetorSetaXY[2][2],int const cores[3], char nome1[255], char nome2[255], char nome3[255],int& jBorda1, int& jBorda2){

    gotoxy(12,15);printf("Expanda o CMD para no minimo a resolucao 1360 x 768 e pressione qualquer tecla para comecar");
    getch();
    gotoxy(12,15);printf("                                                                                           ");
    designerDoJogo();
    gotoxy(1,1);
    fstream arquivo;
    char opc='s';
    arquivo.open("jogadores.txt",ios::app);
    cout<<"Digite o nome do primeiro jogador: ";
        gets(nome1);
        arquivo<<nome1<<"\n";
        cout<<"Digite o nome do  segundo jogador: ";
        gets(nome2);
        arquivo<<nome2<<"\n";

        while((opc=='s')||(opc=='S')){
            cout<<"\nalgum participante extra? [s/n] s para adcionar mais nomes.";
            cin>>opc;
            if((opc=='s') || (opc=='S')){
                    system("CLS");
                cout<<"Digite o nome do participante extra"<<endl;
                cin>>nome3;
                arquivo<<nome3<<endl;
            }
            system("CLS");
        }
    int tratamento;
    tratamento = strlen(nome1);

    if (tratamento > 25){
        char a[25];
        for(int i=0;i<25;i++){
            a[i] = nome1[i];
        }
        strcpy(nome1,a);
        nome1[25] = '\0';
    }
    tratamento = strlen(nome2);
    if (tratamento > 25){
        char a[25];
        for(int i=0;i<25;i++){
            a[i] = nome2[i];
            printf("%d\n",i);
        }
        strcpy(nome2,a);
        nome2[25] = '\0';
    }

    jBorda1 = strlen(nome1) + 10;
    jBorda2 = strlen(nome2) + 10;
    clrscr();

    borda(3,3,120,40);//Primeira borda do jogo A
    borda(17,9,94,28);//Segunda borda do jogo B
    borda(33,16,62,14);//borda do jogo terceira C

    borda(1,2,3,4); // A0
    borda(62,2,3,4); // A1
    borda(122,2,3,4); // A2
    borda(1,21,3,4); // A3
    borda(122,21,3,4); // A4
    borda(1,40,3,4); // A5
    borda(62,40,3,4); // A6
    borda(122,40,3,4); // A7
    //textbackground(2);
    limparTexto(2,3,3,2); // A0
    limparTexto(63,3,3,2); // A1
    limparTexto(123,3,3,2); // A2
    limparTexto(2,22,3,2); // A3
    limparTexto(123,22,3,2); // A4
    limparTexto(2,41,3,2); // A5
    limparTexto(63,41,3,2); // A6
    limparTexto(123,41,3,2); // A7
    //textbackground(0);
    gotoxy(6,4);printf("A0");
    gotoxy(60,4);printf("A1");
    gotoxy(120,4);printf("A2");
    gotoxy(6,24);printf("A3");
    gotoxy(120,24);printf("A4");
    gotoxy(6,41);printf("A5");
    gotoxy(60,41);printf("A6");
    gotoxy(120,41);printf("A7");

    borda(15,8,3,4); // B0
    borda(62,8,3,4); //B1
    borda(110,8,3,4); //B2
    borda(15,21,3,4); //B3
    borda(110,21,3,4); //B4
    borda(15,34,3,4); //B5
    borda(62,34,3,4); //B6
    borda(110,34,3,4); //B7
    //textbackground(2);
    limparTexto(16,9,3,2); //B0
    limparTexto(63,9,3,2); //B1
    limparTexto(111,9,3,2); //B2
    limparTexto(16,22,3,2); //B3
    limparTexto(111,22,3,2); //B4
    limparTexto(16,35,3,2); //B5
    limparTexto(63,35,3,2); //B6
    limparTexto(111,35,3,2); //B7
    //textbackground(0);
    gotoxy(20,10);printf("B0");
    gotoxy(60,10);printf("B1");
    gotoxy(108,10);printf("B2");
    gotoxy(20,24);printf("B3");
    gotoxy(108,24);printf("B4");
    gotoxy(20,35);printf("B5");
    gotoxy(60,35);printf("B6");
    gotoxy(108,35);printf("B7");

    borda(31,15,3,4); // C0
    borda(62,15,3,4); // C1
    borda(94,15,3,4); // C2
    borda(31,21,3,4); // C3
    borda(94,21,3,4); // C4
    borda(31,27,3,4); // C5
    borda(62,27,3,4); // C6
    borda(94,27,3,4); // C7
    //textbackground(2);
    limparTexto(32,16,3,2); // C0
    limparTexto(63,16,3,2); // C1
    limparTexto(95,16,3,2); // C2
    limparTexto(32,22,3,2); // C3
    limparTexto(95,22,3,2); // C4
    limparTexto(32,28,3,2); // C5
    limparTexto(63,28,3,2); // C6
    limparTexto(95,28,3,2); // C7
    //textbackground(0);
    gotoxy(36,17);printf("C0");
    gotoxy(60,17);printf("C1");
    gotoxy(92,17);printf("C2");
    gotoxy(36,24);printf("C3");
    gotoxy(92,24);printf("C4");
    gotoxy(36,28);printf("C5");
    gotoxy(60,28);printf("C6");
    gotoxy(92,28);printf("C7");

    for (int x=6,n=0 ; n<38 ; n++,x++){
        gotoxy(x,23);printf("%c",205);
        if (n == 8){
            x+=5;
        }
        else if (n == 19){
            x = 98;
        }
        else if (n == 30){
            x+=5;
        }
    }

    for (int y=6,n=0 ; n<10 ; y++,n++){
        gotoxy(64,y);printf("%c",186);
        if (n == 1){
            y+=4;
        }
        else if (n == 4){
            y+=16;
        }
        else if (n == 7){
            y+=4;
        }
    }

    borda(135,14,26,28);//Borda do A,B,C

    for (int x=140,y=15,k=0 ; y<31 ; y+=2,k++){
        gotoxy(x,y);printf("A%d",k);
    }
    for (int x=149,y=15,k=0 ; y<31 ; y+=2,k++){
        gotoxy(x,y);printf("B%d",k);
    }
    for (int x=158,y=15,k=0 ; y<31 ; y+=2,k++){
        gotoxy(x,y);printf("C%d",k);
    }

    borda(133,2,32,39,0); //borda lateral direita
    vetorSetaXY[0][0] = 136;
    vetorSetaXY[1][0] = 15; //iniciando a setaVere1
    //vetorSetaXY[2][0] = 0;
}

bool jogarPosicao(int x,int y, bool& vez, int const Cores[3], int M[8][3],bool liberado, int xAnterior, int yAnterior){

    if((x == 0 && y == 0 && (xAnterior == 1 || xAnterior == 3 && yAnterior == 0) && vez  == true && M[x][y] == 0)
        || (liberado == true && x == 0 && y == 0 && vez  == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(2,3,3,2); // A0
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 0 && y == 0 && (xAnterior == 1 || xAnterior == 3 && yAnterior == 0) && vez  == false && M[x][y] == 0)
        || (liberado == true && x == 0 && y == 0 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(2,3,3,2); // A0
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if ((x == 1 && y == 0 && ((xAnterior == 0 || xAnterior == 2 && yAnterior == 0) || (xAnterior == 1 && yAnterior == 1))
        && vez  == true && M[x][y] == 0)
        || (liberado == true && x == 1 && y == 0 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(63,3,3,2); // A1
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 1 && y == 0 && ((xAnterior == 0 || xAnterior == 2 && yAnterior == 0) || (xAnterior == 1 && yAnterior == 1))
        && vez  == false && M[x][y] == 0)
        || (liberado == true && x == 1 && y == 0 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(63,3,3,2); // A1
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if ((x == 2 && y == 0 && (xAnterior == 1 || xAnterior == 4 && yAnterior == 0) && vez  == true && M[x][y] == 0)
        || liberado == true && x == 2 && y == 0 && vez == true && M[x][y] == 0){
        textbackground(Cores[0]);
        limparTexto(123,3,3,2); // A2
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 2 && y == 0 && (xAnterior == 1 || xAnterior == 4 && yAnterior == 0) && vez  == false && M[x][y] == 0)
        || (liberado == true && x == 2 && y == 0 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(123,3,3,2); // A2
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 3 && y == 0 && ((xAnterior == 0 || xAnterior == 5 && yAnterior == 0)||
        xAnterior == 3 && yAnterior == 1) && vez  == true && M[x][y] == 0)
        || (liberado == true && x == 3 && y == 0 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(2,22,3,2); // A3
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if((x == 3 && y == 0 && ((xAnterior == 0 || xAnterior == 5 && yAnterior == 0)||
        xAnterior == 3 && yAnterior == 1) && vez  == false && M[x][y] == 0)
        || (liberado == true && x == 3 && y == 0 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(2,22,3,2); // A3
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 4 && y == 0 && ((xAnterior == 2 || xAnterior == 7 && yAnterior == 0)||
        xAnterior == 4 && yAnterior == 1) && vez == true && M[x][y] == 0)
        || (liberado == true && x == 4 && y == 0 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(123,22,3,2); // A4
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if((x == 4 && y == 0 && ((xAnterior == 2 || xAnterior == 7 && yAnterior == 0)||
        xAnterior == 4 && yAnterior == 1) && vez == false && M[x][y] == 0)
        || (liberado == true && x == 4 && y == 0 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(123,22,3,2); // A4
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 5 && y == 0 && (xAnterior == 3 || xAnterior == 6 && yAnterior == 0)
        && vez == true && M[x][y] == 0)
        || (liberado == true && x == 5 && y == 0 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(2,41,3,2); // A5
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if((x == 5 && y == 0 && (xAnterior == 3 || xAnterior == 6 && yAnterior == 0)
        && vez == false && M[x][y] == 0)
        || (liberado == true && x == 5 && y == 0 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(2,41,3,2); // A5
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 6 && y == 0 && ((xAnterior == 5 || xAnterior == 7 && yAnterior == 0)||
        xAnterior == 6 && yAnterior == 1) && vez == true && M[x][y] == 0)
        || (liberado == true && x == 6 && y == 0 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(63,41,3,2); // A6
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if((x == 6 && y == 0 && ((xAnterior == 5 || xAnterior == 7 && yAnterior == 0)||
        xAnterior == 6 && yAnterior == 1) && vez == false && M[x][y] == 0)
        || (liberado == true && x == 6 && y == 0 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(63,41,3,2); // A6
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 7 && y == 0 && (xAnterior == 6 || xAnterior == 4 && yAnterior == 0)
        && vez == true && M[x][y] == 0)
        || (liberado == true && x == 7 && y == 0 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(123,41,3,2); // A7
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 7 && y == 0 && (xAnterior == 6 || xAnterior == 4 && yAnterior == 0)
        && vez == false && M[x][y] == 0)
        || (liberado == true && x == 7 && y == 0 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(123,41,3,2); // A7
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 0 && y == 1 && (xAnterior == 3 || xAnterior == 1 && yAnterior == 1)
        && vez == true && M[x][y] == 0)
        || (liberado == true && x == 0 && y == 1 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(16,9,3,2); //B0
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 0 && y == 1 && (xAnterior == 3 || xAnterior == 1 && yAnterior == 1)
        && vez == false && M[x][y] == 0)
        || (liberado == true && x == 0 && y == 1 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(16,9,3,2); //B0
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 1 && y == 1 && ((xAnterior == 0 || xAnterior == 2 && yAnterior == 1)||
        xAnterior == 1) && vez == true && M[x][y] == 0)
        || (liberado == true && x == 1 && y == 1 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(63,9,3,2); //B1
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 1 && y == 1 && ((xAnterior == 0 || xAnterior == 2 && yAnterior == 1)||
        xAnterior == 1) && vez == false && M[x][y] == 0)
        || (liberado == true && x == 1 && y == 1 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(63,9,3,2); //B1
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 2 && y == 1 && (xAnterior == 1 || xAnterior == 4 && yAnterior == 1) && vez == true && M[x][y] == 0)
        || (liberado == true && x == 2 && y == 1 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(111,9,3,2); //B2
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 2 && y == 1 && (xAnterior == 1 || xAnterior == 4 && yAnterior == 1) && vez == false && M[x][y] == 0)
        || (liberado == true && x == 2 && y == 1 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(111,9,3,2); //B2
        textbackground(0);
        vez = true;
        M[2][1] = 2;
    }
    else if((x == 3 && y == 1 && ((xAnterior == 0 || xAnterior == 5 && yAnterior == 1)||
        xAnterior == 3) && vez == true && M[x][y] == 0)
        || (liberado == true && x == 3 && y == 1 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(16,22,3,2); //B3
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 3 && y == 1 && ((xAnterior == 0 || xAnterior == 5 && yAnterior == 1)||
        xAnterior == 3) && vez == false && M[x][y] == 0)
        || (liberado == true && x == 3 && y == 1 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(16,22,3,2); //B3
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
     else if((x == 4 && y == 1 && ((xAnterior == 2 || xAnterior == 7 && yAnterior == 1)||
        xAnterior == 4) && vez == true && M[x][y] == 0)
        || (liberado == true && x == 4 && y == 1 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(111,22,3,2); //B4
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 4 && y == 1 && ((xAnterior == 2 || xAnterior == 7 && yAnterior == 1)||
        xAnterior == 4) && vez == false && M[x][y] == 0)
        || (liberado == true && x == 4 && y == 1 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(111,22,3,2); //B4
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 5 && y == 1 && (xAnterior == 3 || xAnterior == 6 && yAnterior == 1) &&
        vez == true && M[x][y] == 0)
        || (liberado == true && x == 5 && y == 1 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(16,35,3,2); //B5
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 5 && y == 1 && (xAnterior == 3 || xAnterior == 6 && yAnterior == 1) &&
        vez == false && M[x][y] == 0)
        || (liberado == true && x == 5 && y == 1 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(16,35,3,2); //B5
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 6 && y == 1 && ((xAnterior == 5 || xAnterior == 7 && yAnterior == 1)||
        xAnterior == 6)&& vez == true && M[x][y] == 0)
        || (liberado == true && x == 6 && y == 1 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(63,35,3,2); //B6
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 6 && y == 1 && ((xAnterior == 5 || xAnterior == 7 && yAnterior == 1)||
        xAnterior == 6)&& vez == false && M[x][y] == 0)
        || (liberado == true && x == 6 && y == 1 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(63,35,3,2); //B6
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 7 && y == 1 && (xAnterior == 6 || xAnterior == 4 && yAnterior == 1)
        && vez == true && M[x][y] == 0)
        || (liberado == true && x == 7 && y == 1 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(111,35,3,2); //B7
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 7 && y == 1 && (xAnterior == 6 || xAnterior == 4 && yAnterior == 1)
        && vez == false && M[x][y] == 0)
        || (liberado == true && x == 7 && y == 1 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(111,35,3,2); //B7
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 0 && y == 2 && (xAnterior == 1 || xAnterior == 3 && yAnterior == 2)
        && vez == true && M[x][y] == 0)
        || (liberado == true && x == 0 && y == 2 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(32,16,3,2); // C0
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 0 && y == 2 && (xAnterior == 1 || xAnterior == 3 && yAnterior == 2)
        && vez == false && M[x][y] == 0)
        || (liberado == true && x == 0 && y == 2 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(32,16,3,2); // C0
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 1 && y == 2 && ((xAnterior == 0 || xAnterior == 2 && yAnterior == 2)||
        xAnterior == 1 && yAnterior == 1) && vez == true && M[x][y] == 0)
        || (liberado == true && x == 1 && y == 2 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(63,16,3,2); // C1
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 1 && y == 2 && ((xAnterior == 0 || xAnterior == 2 && yAnterior == 2)||
        xAnterior == 1 && yAnterior == 1) && vez == false && M[x][y] == 0)
        || (liberado == true && x == 1 && y == 2 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(63,16,3,2); // C1
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 2 && y == 2 && (xAnterior == 1 || xAnterior == 4 && yAnterior == 2)
        && vez == true && M[x][y] == 0)
        || (liberado == true && x == 2 && y == 2 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(95,16,3,2); // C2
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 2 && y == 2 && (xAnterior == 1 || xAnterior == 4 && yAnterior == 2)
        && vez == false && M[x][y] == 0)
        || (liberado == true && x == 2 && y == 2 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(95,16,3,2); // C2
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if ((x == 3 && y == 2 && ((xAnterior == 0 || xAnterior == 5 && yAnterior == 2)||
        xAnterior == 3 && yAnterior == 1) && vez == true && M[x][y] == 0)
        || (liberado == true && x == 3 && y == 2 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(32,22,3,2); // C3
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 3 && y == 2 && ((xAnterior == 0 || xAnterior == 5 && yAnterior == 2)||
        xAnterior == 3 && yAnterior == 1) && vez == false && M[x][y] == 0)
        || (liberado == true && x == 3 && y == 2 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(32,22,3,2); // C3
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
     else if((x == 4 && y == 2 && ((xAnterior == 2 || xAnterior == 7 && yAnterior == 2)||
        xAnterior == 4 && yAnterior == 1) && vez == true && M[x][y] == 0)
        || (liberado == true && x == 4 && y == 2 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(95,22,3,2); // C4
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 4 && y == 2 && ((xAnterior == 2 || xAnterior == 7 && yAnterior == 2)||
        xAnterior == 4 && yAnterior == 1) && vez == false && M[x][y] == 0)
        || (liberado == true && x == 4 && y == 2 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(95,22,3,2); // C4
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 5 && y == 2 && (xAnterior == 3 || xAnterior == 6 && yAnterior == 2)
        && vez == true && M[x][y] == 0)
        || (liberado == true && x == 5 && y == 2 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(32,28,3,2); // C5
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 5 && y == 2 && (xAnterior == 3 || xAnterior == 6 && yAnterior == 2)
        && vez == false && M[x][y] == 0)
        || (liberado == true && x == 5 && y == 2 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(32,28,3,2); // C5
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 6 && y == 2 && ((xAnterior == 5 || xAnterior == 7 && yAnterior == 2)||
        xAnterior == 6 && yAnterior == 1) && vez == true && M[x][y] == 0)
        || (liberado == true && x == 6 && y == 2 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(63,28,3,2); // C6
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 6 && y == 2 && ((xAnterior == 5 || xAnterior == 7 && yAnterior == 2)||
        xAnterior == 6 && yAnterior == 1) && vez == false && M[x][y] == 0)
        || (liberado == true && x == 6 && y == 2 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(63,28,3,2); // C6
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else if((x == 7 && y == 2 && (xAnterior == 6 || xAnterior == 4 && yAnterior == 2)
        && vez == true && M[x][y] == 0)
        || (liberado == true && x == 7 && y == 2 && vez == true && M[x][y] == 0)){
        textbackground(Cores[0]);
        limparTexto(95,28,3,2); // C7
        textbackground(0);
        vez = false;
        M[x][y] = 1;
    }
    else if ((x == 7 && y == 2 && (xAnterior == 6 || xAnterior == 4 && yAnterior == 2)
        && vez == false && M[x][y] == 0)
        || (liberado == true && x == 7 && y == 2 && vez == false && M[x][y] == 0)){
        textbackground(Cores[1]);
        limparTexto(95,28,3,2); // C7
        textbackground(0);
        vez = true;
        M[x][y] = 2;
    }
    else{
        PlaySound(TEXT("erro.wav"),NULL, SND_ASYNC);
        textcolor(RED);
        borda(56,22,19,1,5);
        setlocale(LC_ALL,"Portuguese");
        gotoxy(57, 23);printf("Escolha inválida!");
        setlocale(LC_ALL,"C");
        Sleep(2000);
        limparTexto(56,22,25,3);
        if (vez == true){
            textcolor(Cores[0]);
        }
        else{
            textcolor(Cores[1]);
        }
        return false;
    }
    return true;
}

void limparPecas(int x, int y,int M[8][3], int horizontal[1][8],int vertical[8][1]){

    if(x == 0 && y  == 0){
        limparTexto(2,3,3,2); // A0
        M[x][y] = 0;
        horizontal[0][0] = 0;
        vertical[0][0] = 0;
    }
    else if (x == 1 && y == 0){
        limparTexto(63,3,3,2); // A1
        M[x][y] = 0;
        horizontal[0][0] = 0;
        vertical[3][0] = 0;
    }
    else if (x == 2 && y == 0){
        limparTexto(123,3,3,2); // A2
        M[x][y] = 0;
        horizontal[0][0] = 0;
        vertical[7][0] = 0;
    }
    else if (x == 3 && y == 0){
        limparTexto(2,22,3,2); // A3
        M[x][y] = 0;
        horizontal[0][3] = 0;
        vertical[0][0] = 0;
    }
    else if (x == 4 && y == 0){
        limparTexto(123,22,3,2); // A4
        M[x][y] = 0;
        horizontal[0][4] = 0;
        vertical[7][0] = 0;
    }
    else if (x == 5 && y == 0){
        limparTexto(2,41,3,2); // A5
        M[x][y] = 0;
        horizontal[0][7] = 0;
        vertical[0][0] = 0;
    }
    else if (x == 6 && y == 0){
        limparTexto(63,41,3,2); // A6
        M[x][y] = 0;
        horizontal[0][7] = 0;
        vertical[4][0] = 0;
    }
    else if (x == 7 && y == 0){
        limparTexto(123,41,3,2); // A7
        M[x][y] = 0;
        horizontal[0][7] = 0;
        vertical[7][0] = 0;
    }
    else if (x == 0 && y == 1){
        limparTexto(16,9,3,2); //B0
        M[x][y] = 0;
        horizontal[0][1] = 0;
        vertical[1][0] = 0;
    }
    else if (x == 1 && y == 1){
        limparTexto(63,9,3,2); //B1
        M[x][y] = 0;
        horizontal[0][1] = 0;
        vertical[3][0] = 0;
    }
    else if (x == 2 && y == 1){
        limparTexto(111,9,3,2); //B2
        M[x][y] = 0;
        horizontal[0][1] = 0;
        vertical[6][0] = 0;
    }
    else if (x == 3 && y == 1){
        limparTexto(16,22,3,2); //B3
        M[x][y] = 0;
        horizontal[0][3] = 0;
        vertical[1][0] = 0;
    }
    else if (x == 4 && y == 1){
        limparTexto(111,22,3,2); //B4
        M[x][y] = 0;
        horizontal[0][4] = 0;
        vertical[6][0] = 0;
    }
    else if (x == 5 && y == 1){
        limparTexto(16,35,3,2); //B5
        M[x][y] = 0;
        horizontal[0][6] = 0;
        vertical[1][0] = 0;
    }
    else if (x == 6 && y == 1){
        limparTexto(63,35,3,2); //B6
        M[x][y] = 0;
        horizontal[0][6] = 0;
        vertical[4][0] = 0;
    }
    else if (x == 7 && y == 1){
        limparTexto(111,35,3,2); //B7
        M[x][y] = 0;
        horizontal[0][6] = 0;
        vertical[6][0] = 0;
    }
    else if (x == 0 && y == 2){
        limparTexto(32,16,3,2); // C0
        M[x][y] = 0;
        horizontal[0][2] = 0;
        vertical[2][0] = 0;
    }
    else if (x == 1 && y == 2){
        limparTexto(63,16,3,2); // C1
        M[x][y] = 0;
        horizontal[0][2] = 0;
        vertical[3][0] = 0;
    }
    else if (x == 2 && y == 2){
        limparTexto(95,16,3,2); // C2
        M[x][y] = 0;
        horizontal[0][2] = 0;
        vertical[5][0] = 0;
    }
    else if (x == 3 && y == 2){
        limparTexto(32,22,3,2); // C3
        M[x][y] = 0;
        horizontal[0][3] = 0;
        vertical[2][0] = 0;
    }
    else if (x == 4 && y == 2){
        limparTexto(95,22,3,2); // C4
        M[x][y] = 0;
        horizontal[0][4] = 0;
        vertical[5][0] = 0;
    }
    else if (x == 5 && y == 2){
        limparTexto(32,28,3,2); // C5
        M[x][y] = 0;
        horizontal[0][5] = 0;
        vertical[2][0] = 0;
    }
    else if (x == 6 && y == 2){
        limparTexto(63,28,3,2); // C6
        M[x][y] = 0;
        horizontal[0][5] = 0;
        vertical[4][0] = 0;
    }
    else if (x == 7 && y == 2){
        limparTexto(95,28,3,2); // C7
        M[x][y] = 0;
        horizontal[0][5] = 0;
        vertical[5][0] = 0;
    }

}

bool marcarEscolha(int x, int y, bool vez, int cor, int M[8][3]){

    if (x == 0 && y == 0 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(2,3,3,2); // A0
        textbackground(0);
    }
    else if (x == 0 && y == 0 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(2,3,3,2); // A0
        textbackground(0);
    }
    else if (x == 1 && y == 0 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(63,3,3,2); // A1
        textbackground(0);
    }
    else if (x == 1 && y == 0 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(63,3,3,2); // A1
        textbackground(0);
    }
    else if (x == 2 && y == 0 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(123,3,3,2); // A2
        textbackground(0);
    }
    else if (x == 2 && y == 0 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(123,3,3,2); // A2
        textbackground(0);
    }
    else if (x == 3 && y == 0 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(2,22,3,2); // A3
        textbackground(0);
    }
    else if (x == 3 && y == 0 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(2,22,3,2); // A3
        textbackground(0);
    }
    else if (x == 4 && y == 0 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(123,22,3,2); // A4
        textbackground(0);
    }
    else if (x == 4 && y == 0 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(123,22,3,2); // A4
        textbackground(0);
    }
    else if (x == 5 && y == 0 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(2,41,3,2); // A5
        textbackground(0);
    }
    else if (x == 5 && y == 0 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(2,41,3,2); // A5
        textbackground(0);
    }
    else if (x == 6 && y == 0 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(63,41,3,2); // A6
        textbackground(0);
    }
    else if (x == 6 && y == 0 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(63,41,3,2); // A6
        textbackground(0);
    }
    else if (x == 7 && y == 0 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(123,41,3,2); // A7
        textbackground(0);
    }
    else if (x == 7 && y == 0 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(123,41,3,2); // A7
        textbackground(0);
    }
    else if (x == 0 && y == 1 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(16,9,3,2); //B0
        textbackground(0);
    }
    else if (x == 0 && y == 1 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(16,9,3,2); //B0
        textbackground(0);
    }
    else if (x == 1 && y == 1 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(63,9,3,2); //B1
        textbackground(0);
    }
    else if (x == 1 && y == 1 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(63,9,3,2); //B1
        textbackground(0);
    }
    else if (x == 2 && y == 1 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(111,9,3,2); //B2
        textbackground(0);
    }
    else if (x == 2 && y == 1 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(111,9,3,2); //B2
        textbackground(0);
    }
    else if (x == 3 && y == 1 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(16,22,3,2); //B3
        textbackground(0);
    }
    else if (x == 3 && y == 1 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(16,22,3,2); //B3
        textbackground(0);
    }
    else if (x == 4 && y == 1 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(111,22,3,2); //B4
        textbackground(0);
    }
    else if (x == 4 && y == 1 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(111,22,3,2); //B4
        textbackground(0);
    }
    else if (x == 5 && y == 1 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(16,35,3,2); //B5
        textbackground(0);
    }
    else if (x == 5 && y == 1 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(16,35,3,2); //B5
        textbackground(0);
    }
    else if (x == 6 && y == 1 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(63,35,3,2); //B6
        textbackground(0);
    }
    else if (x == 6 && y == 1 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(63,35,3,2); //B6
        textbackground(0);
    }
    else if (x == 7 && y == 1 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(111,35,3,2); //B7
        textbackground(0);
    }
    else if (x == 7 && y == 1 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(111,35,3,2); //B7
        textbackground(0);
    }
    else if (x == 0 && y == 2 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(32,16,3,2); // C0
        textbackground(0);
    }
    else if (x == 0 && y == 2 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(32,16,3,2); // C0
        textbackground(0);
    }
    else if (x == 1 && y == 2 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(63,16,3,2); // C1
        textbackground(0);
    }
    else if (x == 1 && y == 2 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(63,16,3,2); // C1
        textbackground(0);
    }
    else if (x == 2 && y == 2 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(95,16,3,2); // C2
        textbackground(0);
    }
    else if (x == 2 && y == 2 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(95,16,3,2); // C2
        textbackground(0);
    }
    else if (x == 3 && y == 2 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(32,22,3,2); // C3
        textbackground(0);
    }
    else if (x == 3 && y == 2 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(32,22,3,2); // C3
        textbackground(0);
    }
    else if (x == 4 && y == 2 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(95,22,3,2); // C4
        textbackground(0);
    }
    else if (x == 4 && y == 2 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(95,22,3,2); // C4
        textbackground(0);
    }
    else if (x == 5 && y == 2 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(32,28,3,2); // C5
        textbackground(0);
    }
    else if (x == 5 && y == 2 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(32,28,3,2); // C5
        textbackground(0);
    }
    else if (x == 6 && y == 2 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(63,28,3,2); // C6
        textbackground(0);
    }
    else if (x == 6 && y == 2 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(63,28,3,2); // C6
        textbackground(0);
    }
    else if (x == 7 && y == 2 && vez == true && M[x][y] == 1){
        textbackground(cor);
        limparTexto(95,28,3,2); // C7
        textbackground(0);
    }
    else if (x == 7 && y == 2 && vez == false && M[x][y] == 2){
        textbackground(cor);
        limparTexto(95,28,3,2); // C7
        textbackground(0);
    }
    else{
        PlaySound(TEXT("erro.wav"),NULL, SND_ASYNC);
        textcolor(RED);
        borda(56,22,19,1,5);
        setlocale(LC_ALL,"Portuguese");
        gotoxy(57, 23);printf("Escolha inválida!");
        setlocale(LC_ALL,"C");
        Sleep(2000);
        limparTexto(56,22,25,3);
        if (vez == true){
            textcolor(10);
        }
        else{
            textcolor(9);
        }
        return false;
    }
    return true;
}

bool moinhoHorizontalVertical(int x, int y, int horizontal[1][8],int vertical[8][1]){

    if ((x == 0 || x == 1 || x == 2) && y == 0 && horizontal[0][0] != 0){
        return false;
    }
    else if ((x == 0 || x == 1 || x == 2) && y == 1 && horizontal[0][1] != 0){
        return false;
    }
    else if ((x == 0 || x == 1 || x == 2) && y == 2 && horizontal[0][2] != 0){
        return false;
    }
    else if (x == 3 && (y == 0 || y == 1 || y == 2) && horizontal[0][3] != 0){
        return false;
    }
    else if (x == 4 && (y == 0 || y == 1 || y == 2) && horizontal[0][4] != 0){
        return false;
    }
    else if ((x == 5 || x == 6 || x == 7) && y == 0 && horizontal[0][5] != 0){
        return false;
    }
    else if ((x == 5 || x == 6 || x == 7) && y == 1 && horizontal[0][6] != 0){
        return false;
    }
    else if ((x == 5 || x == 6 || x == 7) && y == 2 && horizontal[0][7] != 0){
        return false;
    }
    else if ((x == 0 || x == 3 || x == 5) && y == 0 && vertical[0][0] != 0){
        return false;
    }
    else if ((x == 0 || x == 3 || x == 5) && y == 1 && vertical[1][0] != 0){
        return false;
    }
    else if ((x == 0 || x == 3 || x == 5) && y == 2 && vertical[2][0] != 0){
        return false;
    }
    else if (x == 1 && (y == 0 || y == 1 || y == 2) && vertical[3][0] != 0){
        return false;
    }
    else if (x == 6 && (y == 0 || y == 1 || y == 2) && vertical[4][0] != 0){
        return false;
    }
    else if ((x == 2 || x == 4 || x == 7) && y == 2 && vertical[5][0] != 0){
        return false;
    }
    else if ((x == 2 || x == 4 || x == 7) && y == 1 && vertical[6][0] != 0){
        return false;
    }
    else if ((x == 2 || x == 4 || x == 7) && y == 0 && vertical[7][0] != 0){
        return false;
    }
    else
        return true;
}

bool verificarPrisaoDeMoinho(int horizontal[1][8],int vertical[8][1],int M[8][3], int j){

    if (M[0][0] == j && horizontal[0][0] == 0 && vertical[0][0] == 0){//A0
        return false;
    }
    else if (M[1][0] == j && horizontal[0][0] == 0 && vertical[3][0] == 0){//A1
        return false;
    }
    else if (M[2][0] == j && horizontal[0][0] == 0 && vertical[7][0] == 0){//A2
        return false;
    }
    else if (M[3][0] == j && horizontal[0][3] == 0 && vertical[0][0] == 0){//A3
        return false;
    }
    else if (M[4][0] == j && horizontal[0][4] == 0 && vertical[7][0] == 0){//A4
        return false;
    }
    else if (M[5][0] == j && horizontal[0][7] == 0 && vertical[0][0] == 0){//A5
        return false;
    }
    else if (M[6][0] == j && horizontal[0][7] == 0 && vertical[4][0] == 0){//A6
        return false;
    }
    else if (M[7][0] == j && horizontal[0][7] == 0 && vertical[7][0] == 0){//A7
        return false;
    }
    else if (M[0][1] == j && horizontal[0][1] == 0 && vertical[1][0] == 0){//B0
        return false;
    }
    else if (M[1][1] == j && horizontal[0][1] == 0 && vertical[3][0] == 0){//B1
        return false;
    }
    else if (M[2][1] == j && horizontal[0][1] == 0 && vertical[6][0] == 0){//B2
        return false;
    }
    else if (M[3][1] == j && horizontal[0][3] == 0 && vertical[1][0] == 0){//B3
        return false;
    }
    else if (M[4][1] == j && horizontal[0][4] == 0 && vertical[6][0] == 0){//B4
        return false;
    }
    else if (M[5][1] == j && horizontal[0][6] == 0 && vertical[1][0] == 0){//B5
        return false;
    }
    else if (M[6][1] == j && horizontal[0][6] == 0 && vertical[4][0] == 0){//B6
        return false;
    }
    else if (M[7][1] == j && horizontal[0][6] == 0 && vertical[6][0] == 0){//B7
        return false;
    }
    else if (M[0][2] == j && horizontal[0][2] == 0 && vertical[2][0] == 0){//C0
        return false;
    }
    else if (M[1][2] == j && horizontal[0][2] == 0 && vertical[3][0] == 0){//C1
        return false;
    }
    else if (M[2][2] == j && horizontal[0][2] == 0 && vertical[5][0] == 0){//C2
        return false;
    }
    else if (M[3][2] == j && horizontal[0][3] == 0 && vertical[2][0] == 0){//C3
        return false;
    }
    else if (M[4][2] == j && horizontal[0][4] == 0 && vertical[5][0] == 0){//C4
        return false;
    }
    else if (M[5][2] == j && horizontal[0][5] == 0 && vertical[2][0] == 0){//C5
        return false;
    }
    else if (M[6][2] == j && horizontal[0][5] == 0 && vertical[4][0] == 0){//C6
        return false;
    }
    else if (M[7][2] == j && horizontal[0][5] == 0 && vertical[5][0] == 0){//C7
        return false;
    }
    else
        return true;
}

void designerDoJogo(){

    int resposta,y=14;
    PlaySound(TEXT("title.wav"),NULL, SND_LOOP |SND_ASYNC);
    //PlaySound(NULL,NULL,0);para interromper o som sem precisar botar outro
    setlocale(LC_ALL,"Portuguese");
    gotoxy(33,37);printf("0 = Regras\n");
    gotoxy(76,37);printf("1 = Jogar\n");
    gotoxy(117,37);printf("2 = Sair\n");

    textcolor(14);
    gotoxy(40,4);printf("    ___                            _         _____        _  _  _               ");
    gotoxy(40,5);printf("   |_  |                          | |       |_   _|      (_)| || |              ");
    gotoxy(40,6);printf("     | |  ___    __ _   ___     __| |  ___    | |   _ __  _ | || |__    __ _    ");
    gotoxy(40,7);printf("     | | / _ \\  / _` | / _ \\   / _` | / _ \\   | |  | '__|| || || '_ \\  / _` |   ");
    gotoxy(40,8);printf(" /\\_/  /| (_) || (_| || (_) | | (_| ||  __/   | |  | |   | || || | | || (_| |   ");
    gotoxy(40,9);printf(" \\____/  \\___/  \\__, | \\___/   \\__,_| \\___|   \\_/  |_|   |_||_||_| |_| \\__,_|   ");
    gotoxy(40,10);printf("                 __/ |                                                          ");
    gotoxy(40,11);printf("                |___/                                                           ");
    gotoxy(40,12);printf("                          +@#                      #@+                         ");
    gotoxy(40,13);printf("                        +@*-:@*                   @:.*@+                       ");
    gotoxy(40,14);printf("                       @#....-*@:              :@*..---#@                      ");
    gotoxy(40,15);printf("                        :@#-.---##            ##....-#@:                       ");
    gotoxy(40,16);printf("                           =@+---:@*        =@:...:@=                          ");
    gotoxy(40,17);printf("                             +@*..-*@+    :@+.--=@*                            ");
    gotoxy(40,18);printf("                                @#:--##  ##..-#@:                              ");
    gotoxy(40,19);printf("                                  =@+-=@@=-+@=                                 ");
    gotoxy(40,20);printf("                                    +@*.-*@+                                   ");
    gotoxy(40,21);printf("                                   *@=@##@*@=                                  ");
    gotoxy(40,22);printf("                                :##:-+@+-##--#@:                               ");
    gotoxy(40,23);printf("                              *@*.--#=-=#*+@+.-*@=                             ");
    gotoxy(40,24);printf("                           :##:...=@+-#*.#*.##:--:##:                          ");
    gotoxy(40,25);printf("                         :@*----+#*@-.#*-#*-+##*...-*#*                        ");
    gotoxy(40,26);printf("                       ##:...-:@*-+=..*#*#+-:#-*@:.---:==                      ");
    gotoxy(40,27);printf("                        ##-.-##---#*....-----#+..##--:##                       ");
    gotoxy(40,28);printf("                          #@@:...-@+----.....*#---:@@#-                        ");
    gotoxy(40,29);printf("                                 +@-----.....:@                                ");
    gotoxy(40,30);printf("                                 @*------.....#=                               ");
    gotoxy(40,31);printf("                              *@#-...:@*+=@---.:@#:                            ");
    gotoxy(40,32);printf("                            +@+---...#*.--#*--....+@:                          ");
    gotoxy(40,33);printf("                            #@@@@@=..#*.--#*--#@@@@@*                          ");
    gotoxy(40,34);printf("                            #*...+#--#*-..#*.-@+---#*                          ");
    gotoxy(40,35);printf("                            ##===#@==@#===@#==@#===@*                          ");

    gotoxy(80,39);printf("[ ]");
    gotoxy(81,39);scanf("%d",&resposta);
    int a;
    a = getchar();

    if(resposta==0){
    clrscr();
    gotoxy(45,5);printf("______                                 \n");
    gotoxy(45,6);printf("| ___ \\                                \n");
    gotoxy(45,7);printf("| |_/ /  ___   __ _  _ __   __ _  ___  \n");
    gotoxy(45,8);printf("|    /  / _ \\ / _` || '__| / _` |/ __| \n");
    gotoxy(45,9);printf("| |\\ \\ |  __/| (_| || |   | (_| |\\__\\ \n");
    gotoxy(45,10);printf("\\_| \\_| \\___| \\__, ||_|    \\__,_||___/ \n");
    gotoxy(45,11);printf("               __/ |                   \n");
    gotoxy(45,12);printf("              |___/                    \n");

    gotoxy(45,y++);printf("1 - O jogo é jogado por dois jogadores!");
    gotoxy(45,y++);printf("2 - São 18 peças, distribuindo 9 para cada jogador!");
    gotoxy(45,y++);printf("3 - O tabuleiro tem 24 casas interligadas horizontalmente e verticalmente!");
    gotoxy(45,y++);printf("4 - Objetivo: Deixar o adversário com 2 peças no tabuleiro ou sem movimento!");
    gotoxy(45,y++);printf("5 - A partida inicia com o tabuleiro vazio e os jogadores alternam colocando suas peças no tabuleiro!");
    gotoxy(45,y++);printf("6 - Quando todas as peças forem colocadas, os jogadores se alternam deslizando-as e tentando fazer uma linha");
    gotoxy(45,y++);printf("    de três peças consecutivas da mesma cor (o moinho). O deslizamento de peças pode ocorrer se");
    gotoxy(45,y++);printf("    houver um espaço vazio adjacente diretamente conectado por uma linha. Se a qualquer momento durante a");
    gotoxy(45,y++);printf("    etapa de colocação de peças ou após o deslizamento de uma peça um jogador conseguir formar o moinho");
    gotoxy(45,y++);printf("    então ele pode remover uma peça do adversário, desde que a peça a ser removida não faça parte");
    gotoxy(45,y++);printf("    de outro moinho (porém se não houverem peças adversárias a não ser em moinho, então é permitido");
    gotoxy(45,y++);printf("    remover uma peça de moinho");
    gotoxy(45,y++);printf("7 - Aperte qualquer tecla para jogar!");
    getch();
    clrscr();
    }
    else if(resposta == 1){
            clrscr();
    }
    else if(resposta == 2){
            exit(1);
}
    setlocale(LC_ALL,"C");
    return;
}

void creditos(){

    int MAX_COLUNAS=98;
    int MAX_LINHAS=24;

    textcolor(14);
    for(int linha=6;linha<=MAX_LINHAS;linha++){
        for(int coluna=45; coluna<=MAX_COLUNAS;coluna++)
        printf(" ");
    printf("\n");
    }
    gotoxy(45,5); printf("%c",201);
    for(int coluna=45;coluna<MAX_COLUNAS;coluna++){
    printf("%c",205);
    }
    gotoxy(MAX_COLUNAS, 5); printf("%c\n",187);
    for(int linha=6;linha<MAX_LINHAS;linha++){
        gotoxy(45,linha);printf("%c",186);
        gotoxy(MAX_COLUNAS,linha);printf("%c",186);
    }
    gotoxy(45, MAX_LINHAS); printf("%c",200);
    for(int coluna=45;coluna<MAX_COLUNAS;coluna++){
        printf("%c",205);
    }
    gotoxy(MAX_COLUNAS, MAX_LINHAS); printf("%c",188);

    gotoxy(50,8); printf("          _     _    _ _   _  ____   _____ ");
    gotoxy(50,9); printf("    /\\   | |   | |  | | \\ | |/ __ \\ / ____|");
    gotoxy(50,10); printf("   /  \\  | |   | |  | |  \\| | |  | | (___  ");
    gotoxy(50,11); printf("  / /\\ \\ | |   | |  | | . ` | |  | |\\___ \\ ");
    gotoxy(50,12); printf(" / ____ \\| |___| |__| | |\\  | |__| |____) |");
    gotoxy(50,13); printf("/_/    \\_\\______\\____/|_| \\_|\\____/|_____/ ");
    setlocale(LC_ALL, "portuguese");
    gotoxy(58,16); printf("André Luiz Almeida Lima");
    gotoxy(58,17); printf("Ian Tavares Silva");
    gotoxy(58,18); printf("Luís Gabriel Costa Lima Ribeiro");
    gotoxy(58,19); printf("Natalia Da Silva Costa");
    gotoxy(58,20); printf("Natan Vinícius Santos Pereira");
    gotoxy(58,21); printf("Thalyta Costa Dos Santos");
    gotoxy(58,22); printf("Verenilson Da Silva Souza");
    getch();

}
