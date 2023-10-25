// Miguel Umbelino da Mota Roma - a2021138955

#include "percurso.h"

// PROCURA UM PERCURSO VÁLIDO UMA LINHA DE CADA VEZ
void percursoLinhaUnica(plinha p) {
    plinha paux = p;
    char nomePartida[100], nomeChegada[100], ch;
    int encontrado, perc = 0;

    fflush(stdin);
    system("cls");

    printf("\n\t\t\t\t\t  --------------------------------------------\n");
    printf("\n\t\t\t\t\t  |       LISTAR PERCURSO DE UMA LINHA       |\n");
    printf("\n\t\t\t\t\t  --------------------------------------------\n");

    printf("-> Paragem de partida: ");
    fflush(stdin);
    scanf(" %99[^\n]", nomePartida);

    printf("-> Paragem de chegada: ");
    fflush(stdin);
    scanf(" %99[^\n]", nomeChegada);

    //Percorre todas as linhas da lista ligada
    while(paux != NULL){
        encontrado = 0;
        pparagem partida = paux->lista;

        //Percorre todas as paragens da lista da linha à procura do percurso (ponteiro prox)
        while(partida != NULL){
            if(strcmp(nomePartida, partida->nome) == 0){  //Até encontrar a paragem de partida
                pparagem chegada = partida->prox;

                while(chegada != NULL){ //Verifica se essa mesma linha tem a paragem de chegada
                    if(strcmp(nomeChegada, chegada->nome) == 0){
                        encontrado = 1;
                        perc = 1;

                        printf("\nPercurso na linha '%s':\n", paux->nome);
                        printf("%s -> ", nomePartida);

                        // Imprime as paragens que estão entre a partida e a chegada
                        pparagem percurso = partida->prox;
                        while(percurso != chegada){
                            printf("%s -> ", percurso->nome);
                            percurso = percurso->prox;
                        }
                        printf("%s\n", nomeChegada);
                    }
                    if(encontrado == 1) //Não é necessário procurar mais nessa linha
                        break;

                    chegada = chegada->prox;
                }
            }
            if(encontrado == 1)
                break;

            partida = partida->prox;
        }

        // Caso não seja encontrada, procura o percurso no sentido inverso (ponteiro ant)
        if (encontrado == 0) {
            partida = paux->lista;

            // Percorre as linhas da lista ligada
            while (partida != NULL) {
                if (strcmp(nomePartida, partida->nome) == 0) {
                    pparagem chegada = partida->ant;

                    // Percorre a lista das paragens na linha
                    while (chegada != NULL) {
                        if (strcmp(nomeChegada, chegada->nome) == 0) {
                            encontrado = 1;
                            perc = 1;

                            printf("\nPercurso na linha '%s':\n", paux->nome);
                            printf("%s -> ", nomePartida);

                            // Apresenta o percurso no sentido inverso
                            pparagem percurso = partida->ant;
                            while (percurso != chegada) {
                                printf("%s -> ", percurso->nome);
                                percurso = percurso->ant;
                            }
                            printf("%s\n", nomeChegada);
                        }
                        if(encontrado == 1)
                            break;

                        chegada = chegada->ant;
                    }
                }
                if (encontrado == 1)
                    break;

                partida = partida->prox;
            }
        }
        paux = paux->prox;
    }

    // Se não for encontrado nenhum percurso
    if (perc == 0) {
        printf("[AVISO] NENHUM percurso encontrado entre '%s' e '%s'\n", nomePartida, nomeChegada);
    }

    printf("\n-> ENTER para voltar ao menu anterior");
    do {
        fflush(stdin);
        ch = getchar();
    } while (ch != '\n');
}

/*
void percursoLinhaTroca(plinha p) {
}
 */