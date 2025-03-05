// Miguel Umbelino da Mota Roma - a2021138955

#include "ficheiros.h"

//GUARDAR AS PARAGENS NUM FICHEIRO BINARIO
void guardaParagens(pparagem p, int total){
    FILE *f;

    f = fopen("paragens.dat", "wb");
    if(f == NULL){
        printf("ERRO ao guardar o ficheiro das PARAGENS\n");
        return;
    }

    fwrite(&total, sizeof(int), 1, f);  //Passamos o número de paragens registadas (total)
    fwrite(p, sizeof(paragem), total, f);   //Guarda a informação da struct de cada paragem armazenada no array dinamico "sistema"
    fclose(f);
}

//RECUPERAR AS PARAGENS DE UM FICHEIRO BINARIO
pparagem recuperaParagens(int *total){
    FILE *f;
    pparagem aux = NULL;

    *total = 0;
    f = fopen("paragens.dat", "rb");
    if(f == NULL){
        printf("ERRO na leitura do ficheiro\n");
        return NULL;
    }
    fread(total, sizeof(int), 1, f);    //Primeiro vai ler o inteiro guardado no ficheiro binario

    aux = malloc(sizeof(paragem) * (*total));   //Aloca espaço para o número de paragens lido acima
    if(aux == NULL){
        fclose(f);
        *total = 0;
        return NULL;
    }
    fread(aux, sizeof(paragem), *total, f);

    fclose(f);
    return aux;
}

//GUARDAR AS LINHAS NUM FICHEIRO BINARIO
void guardaLinhas(plinha p){
    FILE *f;
    f = fopen("linhas.dat", "wb");
    if (f == NULL) {
        printf("ERRO na leitura do ficheiro das LINHAS\n");
        return;
    }

    while(p != NULL){
        fwrite(p, sizeof(linha), 1, f); //Primeiro escreve a linha

        while(p->lista != NULL){
            fwrite(p->lista, sizeof (paragem), 1, f); //Em segundo escreve cada paragem que compoe essa linha
            p->lista = p->lista->prox;
        }

        p = p->prox;
    }
    fclose(f);
}

//RECUPERAR AS LINHAS DE UM FICHEIRO BINARIO
plinha recuperaLinhas() {
    plinha p = NULL;

    FILE *f;
    f = fopen("linhas.dat", "rb");
    if (f == NULL) {
        printf("ERRO na leitura do ficheiro das LINHAS\n");
        return NULL;
    }

    //Ler a informação relativa à linha
    linha lin;
    while (fread(&lin, sizeof(linha), 1, f) == 1) {
        plinha novo = malloc(sizeof(linha));
        if (novo == NULL) {
            fclose(f);
            return p;
        }

        *novo = lin;
        novo->prox = NULL;
        novo->lista = NULL;

        //Ler a informação relativa às paragens da linha
        int nPara = novo->nParag;
        while (nPara > 0) {
            pparagem novaParagem = malloc(sizeof(paragem));
            if (novaParagem == NULL) {
                free(p);
                fclose(f);
                return NULL;
            }

            fread(novaParagem, sizeof(paragem), 1, f);
            novaParagem->prox = NULL;
            novaParagem->ant = NULL;

            //Insere a paragem na lista de paragens da linha
            if (novo->lista == NULL) {
                novo->lista = novaParagem;
            } else {
                pparagem paragem = novo->lista;
                while (paragem->prox != NULL) {
                    paragem = paragem->prox;
                }
                paragem->prox = novaParagem;
                novaParagem->ant = paragem;
            }

            nPara--;
        }

        //Insere a linha na lista ligada
        if (p == NULL) {
            p = novo;
        } else {
            plinha aux = p;
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = novo;
        }
    }

    fclose(f);
    return p;
}

int verificaLinhaExiste(plinha p, char* nomeLinha) {
    plinha lin = p;
    while (lin != NULL) {
        if (strcmp(lin->nome, nomeLinha) == 0) {
            return 1;
        }
        lin = lin->prox;
    }
    return 0;
}

int verificaParagemExiste(plinha p, pparagem pp, int n, char* nomeParagem, char* codigo) {
    pparagem aux = pp;
    plinha temp = p;

    //Percorre o array dinâmico das paragens (verificar se a paragem existe)
    for(int i = 0; i < n; i++){
        if (strcmp(aux[i].nome, nomeParagem) == 0 || strcmp(aux[i].codigo, codigo) == 0)
            return 1;
    }

    //Percorre a lista das paragens na linha (verificar repetição)
    while (temp != NULL) {
        pparagem verf = temp->lista;
        while (verf != NULL) {
            if (strcmp(verf->nome, nomeParagem) == 0) {
                return 1;
            }
            verf = verf->prox;
        }
        temp = temp->prox;
    }

    return 0;
}

//LER A NOVA LINHA E AS SUAS PARAGENS DE UM FICHEIRO DE TEXTO
plinha lerFicheiroTxt(plinha p, pparagem* pp, int* n) {
    FILE* f;

    char nomeFich[100], ch;
    char nomeLinha[100], nomeParagem[100], cod[5];

    int adicionadas = 0;

    fflush(stdin);
    system("cls");

    printf("\n\t\t\t\t\t  --------------------------------------------\n");
    printf("\n\t\t\t\t\t  |      ADICIONAR LINHA DE UM FICHEIRO      |\n");
    printf("\n\t\t\t\t\t  --------------------------------------------\n");

    printf("-> Ficheiro de texto: ");
    scanf(" %99[^\n]", nomeFich);

    // Abertura do ficheiro de texto
    f = fopen(nomeFich, "r");
    if (f == NULL) {
        printf("[AVISO] Erro ao abrir o ficheiro!\n");

        printf("\n-> ENTER para voltar ao menu anterior");
        do {
            fflush(stdin);
            ch = getchar();
        } while (ch != '\n');

        return p;
    }

    // Leitura da primeira linha do ficheiro (nome da linha) até o '\n'
    fscanf(f, " %99[^\n]", nomeLinha);
    if (verificaLinhaExiste(p, nomeLinha) == 1) {
        printf("[AVISO] Linha [%s] ja existe no sistema!\n", nomeLinha);
        printf("Informacao do ficheiro nao sera adicionada\n");
        fclose(f);

        printf("\n-> ENTER para voltar ao menu anterior");
        do {
            fflush(stdin);
            ch = getchar();
        } while (ch != '\n');

        return p;
    }

    // Alocar espaço para guardar a linha
    plinha nova = malloc(sizeof(linha));
    if (nova == NULL) {
        printf("[AVISO] Erro ao alocar memória para a nova linha!\n");
        fclose(f);
        return p;
    }

    // Informação da nova linha
    strcpy(nova->nome, nomeLinha);
    nova->nParag = 0;
    nova->lista = NULL;
    nova->prox = NULL;

    while (fscanf(f, " %99[^#] #%4s", nomeParagem, cod) == 2) { // Le a informação das paragens
        nomeParagem[strlen(nomeParagem) - 1] = '\0'; //Remove o espaço em branco que fica entre o nome da paragem e o '#'

        // Verifica se a paragem lida já estava registada
        if (verificaParagemExiste(p, *pp, *n, nomeParagem, cod) == 1) {
            printf("[AVISO] Paragem [%s] ja existe no sistema!\n", nomeParagem);
            printf("Informacao do ficheiro nao sera adicionada\n");

            fclose(f);
            free(nova); //Liberta a memória alocada para a nova linha

            printf("\n-> ENTER para voltar ao menu anterior");
            do {
                fflush(stdin);
                ch = getchar();
            } while (ch != '\n');

            return p;
        }

        // Alocar espaço para a nova paragem
        pparagem pnova = malloc(sizeof(paragem));
        if (pnova == NULL) {
            printf("[AVISO] Erro ao alocar memória para a nova paragem!\n");
            fclose(f);
            free(nova);

            return p;
        }

        // Informação da nova paragem a adicionar
        strcpy(pnova->nome, nomeParagem);
        strcpy(pnova->codigo, cod);
        pnova->numLinhas = 1;
        pnova->ant = NULL;
        pnova->prox = NULL;

        // Adicionar a nova paragem à lista da linha
        pparagem temp = nova->lista;
        if (temp == NULL) { //Se for a primeira paragem
            nova->lista = pnova;
        }
        else {    //Se ja houver alguma paragem na linha
            while (temp->prox != NULL) {    //Percorre a lista das paragens ate encontrar o ultimo nó
                temp = temp->prox;
            }
            temp->prox = pnova;
            pnova->ant = temp;
        }

        adicionadas++;
        nova->nParag++;
    }

    fclose(f);

    // Verifica se há paragens para serem adicionadas ao array dinamico (pparagem pp)
    if (adicionadas > 0) {
        if (nova->lista != NULL) {  // A lista das paragens da nova linha está preenchida com paragens
            pparagem temp = nova->lista;
            while (temp != NULL) {  //É percorrida a lista
                if (verificaParagemExiste(p, *pp, *n, temp->nome, temp->codigo) == 0) {
                    (*n)++;
                    *pp = realloc(*pp, sizeof(paragem) * (*n));
                    if (*pp == NULL) {
                        printf("[AVISO] Erro ao realocar memória para o array de paragens!\n");
                        return p;
                    }

                    (*pp)[(*n) - 1] = *temp; // Paragem adicionada ao final do array dinâmico
                }

                temp = temp->prox;
            }
        }

        // Adiciona a nova linha à lista
        if (p == NULL) {    //Se a lista estiver vazia
            printf("[AVISO] Nova linha e paragens adicionadas do ficheiro de texto!\n");
            printf("\n-> ENTER para voltar ao menu anterior");
            do{
                fflush(stdin);
                ch = getchar();
            }while( ch != '\n');

            return nova;
        } else {    //Se já houver alguma linha na lista
            plinha temp = p;
            while (temp->prox != NULL) {
                temp = temp->prox;
            }
            temp->prox = nova;
        }
    } else {
        free(nova); //Não são adicionadas as paragens e liberta a memória alocada para a nova linha
    }

    printf("[AVISO] Nova linha e paragens adicionadas do ficheiro de texto!\n");
    printf("\n-> ENTER para voltar ao menu anterior");
    do{
        fflush(stdin);
        ch = getchar();
    }while( ch != '\n');

    return p;
}
