// Miguel Umbelino da Mota Roma - a2021138955
#ifndef TP_P_FICHEIROS_H
#define TP_P_FICHEIROS_H

#include "utils.h"
#include "paragem.h"
#include "linha.h"

void guardaParagens(paragem *p, int total);

pparagem recuperaParagens(int *total);

void guardaLinhas(plinha p);

plinha recuperaLinhas();

int verificaLinhaExiste(plinha p, char* nomeLinha);

int verificaParagemExiste(plinha p, pparagem pp, int n, char* nomeParagem, char* codigo);

plinha lerFicheiroTxt(plinha p, pparagem* pp, int *total);

#endif //TP_P_FICHEIROS_H
