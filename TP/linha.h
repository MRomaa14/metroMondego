// Miguel Umbelino da Mota Roma - a2021138955
#ifndef TP_P_LINHA_H
#define TP_P_LINHA_H

#include "utils.h"
#include "paragem.h"

typedef struct linha linha, *plinha;
struct linha{
    char nome[100];
    int nParag;

    pparagem lista; //Ponteiro para a lista duplamente ligada das paragens
    plinha prox;  //Ponteiro para a lista ligada das linhas
};

int contaNos(plinha p);

pparagem procuraParagem(pparagem pp, int n, char *nomeParagem);

plinha regLinha(plinha p, pparagem parag, int n);

void adicParagemLinha(plinha p, pparagem pp, int n);

plinha elimParagemLinha(plinha p, pparagem pp, int n);

void listarLinhas(plinha p);

void listarLinhasParagem(plinha p);

#endif //TP_P_LINHA_H
