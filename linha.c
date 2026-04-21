// Miguel Umbelino da Mota Roma - a2021138955

#include "linha.h"
#include "paragem.h"

//CONTA OS NÓS NA LISTA LIGADA PRINCIPAL (DAS LINHAS)
int contaNos(plinha p){
    int cont = 0;

    //Percorre a lista ligada das linhas
    while(p != NULL){
        cont++;
        p = p->prox;
    }
    return cont;
}

//VERIFICA SE A PARAGEM PASSADA COMO ARGUMENTO EXISTE NO SISTEMA
pparagem procuraParagem(pparagem pp, int n, char *nomeParagem){
    pparagem aux = pp;

    //Percorre o array dinâmico das paragens
    for (int i = 0; i < n; i++) {
        if (strcmp(aux[i].nome, nomeParagem) == 0) {
            return &aux[i];
        }
    }
    return NULL;
}

//REGISTA UMA NOVA LINHA NA LISTA LIGADA
plinha regLinha(plinha p, pparagem pp, int n){
    plinha novo, aux;
    pparagem pnova, verf;

    char nomeLinha[100], nomeParagem[100], ch;
    int existe, encontrado;
    int numParag = 0;

    fflush(stdin);
    system("cls");

    printf("\n\t\t\t\t\t  --------------------------------------------\n");
    printf("\n\t\t\t\t\t  |           ADICIONAR NOVA LINHA           |\n");
    printf("\n\t\t\t\t\t  --------------------------------------------\n");

    //Caso não existam paragens no sistema, não permite criar linha
    if(n == 0){
        printf("\n[AVISO] IMPOSSIVEL registar linha, nao existem paragens no sistema!\n");

        printf("\n-> ENTER para voltar ao menu anterior");
        do{
            fflush(stdin);
            ch = getchar();
        }while( ch != '\n');
        return p;
    }

    //Alocar espaço para a nova linha
    novo = malloc(sizeof(linha));
    if(novo == NULL){
        printf("ERRO na alocacao de memoria da LINHA\n");
        return p;
    }

    do{
        existe = 0;
        aux = p;

        printf("-> Nome da linha: ");
        scanf(" %99[^\n]", nomeLinha);

        //Verificar se já há alguma linha com o mesmo nome
        while(aux != NULL){
            if(strcmp(aux->nome, nomeLinha) == 0){
                printf("[AVISO] Linha '%s' ja esta REGISTADA!\n\n", nomeLinha);
                existe = 1;
                break;
            }
            aux = aux->prox;
        }

        //No caso da linha inserida já existir
        if(existe == 1) {
            printf("\n-> Inserir outra linha (S/N)?");
            do {
                fflush(stdin);
                ch = getchar();
            } while (ch != 'S' && ch != 's' && ch != 'N' && ch != 'n');

            if (ch == 'n' || ch == 'N')
                return p;
        }
    }while(existe == 1);

    // Informação da nova linha
    strcpy(novo->nome, nomeLinha);
    novo->nParag = 0;
    novo->lista = NULL;
    novo->prox = NULL;

    if(p == NULL){  //Se for a primeira linha a ser adicionada à lista ligada
        p = novo;
    }
    else {  //Outras linhas sem ser a primeira
        aux = p;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    do{
        encontrado = 0;

        printf("-> Nome da paragem: ");
        scanf(" %99[^\n]", nomeParagem);

        //Chamada à função para procurar a paragem
        pparagem temp = procuraParagem(pp, n, nomeParagem);
        if(temp == NULL){
            printf("[AVISO] NENHUMA paragem [%s] no SISTEMA\n", nomeParagem);
        }
        else {  // Se a paragem estiver registada
            encontrado = 0;
            verf = novo->lista;
            while (verf != NULL) {  // Vai verificar se já se encontra na linha
                if (strcmp(verf->nome, nomeParagem) == 0) {
                    printf("[AVISO] Paragem [%s] JA se encontra na LINHA!\n", nomeParagem);
                    encontrado = 1;
                    break;
                }
                verf = verf->prox;
            }

            //Se a paragem não estiver já na linha e se estiver no array dinâmico
            if (encontrado == 0) {
                pnova = malloc(sizeof(paragem));
                if (pnova == NULL) {
                    printf("ERRO ao alocar memoria para PARAGEM!\n");
                    return p;
                }

                //Informação da nova paragem a adicionar
                strcpy(pnova->nome, nomeParagem);
                strcpy(pnova->codigo, temp->codigo);
                pnova->numLinhas = 0;

                temp->numLinhas++;
                printf("Paragem adicionada com SUCESSO!\n");

                pnova->ant = NULL;
                pnova->prox = NULL;

                if (novo->lista == NULL) {  //Caso seja a primeira paragem a ser adicionada à lista duplamente ligada
                    novo->lista = pnova;
                }
                else {  // Se já houver paragens adicionadas à linha
                    verf = novo->lista;
                    while (verf->prox != NULL)
                        verf = verf->prox;
                    verf->prox = pnova;
                    pnova->ant = verf;
                }

                //Atualiza os contadores
                novo->nParag++;
                numParag++;
            }
        }

        // Repete o pedido até receber uma paragem valida
        if(numParag == 0){
            printf("A linha tem de ter pelo menos 1 paragem!\n");
            ch = 's';
            putchar('\n');
        }
        else{
            printf("\n-> Inserir outra paragem? (S/N)");
            do{
                fflush(stdin);
                ch = getchar();
            }while(ch != 'S' && ch != 's' && ch != 'N' && ch != 'n');
        }
    }while(ch == 'S' || ch == 's');

    return p;
}

void adicParagemLinha(plinha p, pparagem pp, int n) {
    plinha temp;
    pparagem novo, aux;

    char nomeLinha[100], nomeParagem[100], ch;

    do {
        system("cls");
        fflush(stdin);

        printf("\n\t\t\t\t\t  --------------------------------------------\n");
        printf("\n\t\t\t\t\t  |         ADICIONAR PARAGEM A LINHA        |\n");
        printf("\n\t\t\t\t\t  --------------------------------------------\n");

        temp = p;
        printf("-> Linha a atualizar: ");
        scanf(" %99[^\n]", nomeLinha);

        //Verifica se a linha passada existe na lista
        while (temp != NULL && (strcmp(temp->nome, nomeLinha) != 0)) {
            temp = temp->prox;
        }

        if (temp == NULL) {
            printf("[AVISO] LINHA '%s' NAO registada!\n", nomeLinha);

            printf("\n-> Inserir outra linha (S/N)?");
            do {
                fflush(stdin);
                ch = getchar();
            } while (ch != 'S' && ch != 's' && ch != 'N' && ch != 'n');

            if (ch == 'N' || ch == 'n')
                return;
        }
    } while (temp == NULL);

    do {
        printf("-> Paragem a adicionar: ");
        scanf(" %99[^\n]", nomeParagem);

        aux = procuraParagem(pp, n, nomeParagem);
        if (aux == NULL) {  //Paragem não está registada
            printf("[AVISO] NENHUMA paragem com o nome [%s] no SISTEMA\n", nomeParagem);

            printf("-> Inserir outra paragem (S/N)?");
            do {
                fflush(stdin);
                ch = getchar();
            } while (ch != 'S' && ch != 's' && ch != 'N' && ch != 'n');

            if (ch == 'N' || ch == 'n')
                return;
        }
        else {
            int encontrado = 0;

            aux = temp->lista;
            while (aux != NULL) {   //Percorre a lista das paragens na linha
                if (strcmp(nomeParagem, aux->nome) == 0) {
                    printf("Paragem JA definida na LINHA!\n");
                    encontrado = 1;
                    break;
                }
                aux = aux->prox;
            }

            if (encontrado == 0) {  //Caso ainda não exista na linha
                novo = malloc(sizeof(paragem));
                if (novo == NULL) {
                    printf("[AVISO] ERRO ao alocar memoria para PARAGEM!\n");
                    return;
                }

                // Informação da paragem a adicionar
                aux = procuraParagem(pp, n, nomeParagem);
                strcpy(novo->nome, nomeParagem);
                strcpy(novo->codigo, aux->codigo);
                aux->numLinhas++;

                // Incrementar o número de paragens da linha
                temp->nParag++;
                printf("Paragem adicionada com SUCESSO!\n");

                novo->prox = NULL;
                novo->ant = NULL;

                if (temp->lista == NULL) {  //Se a lista das paragens da linha estiver vazia (ou seja é a primeira paragem)
                    temp->lista = novo;
                }
                else {
                    aux = temp->lista;
                    while (aux->prox != NULL) {
                        aux = aux->prox;
                    }

                    // Ponteiro ant fica a apontar para a paragem anterior e prox para a próxima paragem
                    aux->prox = novo;
                    novo->ant = aux;
                }
            }
        }

        printf("\n-> Inserir outra paragem? (S/N)");
        do {
            ch = getchar();
            fflush(stdin);
        } while (ch != 'S' && ch != 's' && ch != 'N' && ch != 'n');
    } while (ch == 'S' || ch == 's');
}

plinha elimParagemLinha(plinha p, pparagem pp, int n) {
    plinha linha = NULL;
    pparagem apagar = NULL;

    char nomeLinha[100], nomeParagem[100];
    char ch;
    int sair = 0;

    do {
        system("cls");
        fflush(stdin);

        printf("\n\t\t\t\t\t  --------------------------------------------\n");
        printf("\n\t\t\t\t\t  |         ELIMINAR PARAGEM DA LINHA        |\n");
        printf("\n\t\t\t\t\t  --------------------------------------------\n");

        printf("-> Linha a alterar: ");
        scanf(" %99[^\n]", nomeLinha);

        //Procura a linha na lista
        linha = p;
        while (linha != NULL && strcmp(linha->nome, nomeLinha) != 0)
            linha = linha->prox;

        if (linha == NULL) {
            printf("[AVISO] LINHA '%s' NAO registada!\n", nomeLinha);

            printf("\n-> Inserir outra linha (S/N)?");
            do {
                fflush(stdin);
                ch = getchar();
            } while (ch != 'S' && ch != 's' && ch != 'N' && ch != 'n');

            if (ch == 'N' || ch == 'n')
                return p;
        }
    } while (linha == NULL);

    do {
        printf("-> Paragem a eliminar: ");
        fflush(stdin);
        scanf(" %99[^\n]", nomeParagem);

        //Procura a paragem na lista ligada da linha
        apagar = linha->lista;
        while (apagar != NULL && strcmp(apagar->nome, nomeParagem) != 0)
            apagar = apagar->prox;

        if (apagar == NULL) {
            printf("[AVISO] PARAGEM [%s] NAO registada na LINHA!\n", nomeParagem);
        }
        else if (apagar == linha->lista) {  // Remove a paragem do início da lista (primeira paragem)
            linha->lista = apagar->prox;
            if (linha->lista != NULL)
                linha->lista->ant = NULL;

            // Atualiza os contadores das linhas e das paragens
            pparagem aux = procuraParagem(pp, n, nomeParagem);
            aux->numLinhas--;
            printf("PARAGEM [%s] eliminada com SUCESSO!\n", nomeParagem);
            linha->nParag--;

            free(apagar);
        }
        else {  // Remove as restantes paragens
            apagar->ant->prox = apagar->prox;
            if (apagar->prox != NULL)
                apagar->prox->ant = apagar->ant;

            // Atualiza os contadores das linhas e das paragens
            pparagem aux = procuraParagem(pp, n, nomeParagem);
            aux->numLinhas--;
            printf("PARAGEM [%s] eliminada com SUCESSO!\n", nomeParagem);
            linha->nParag--;

            free(apagar);
        }

        if (linha->nParag == 0) {
            if (linha == p) {   //Caso seja a primeira linha da lista ligada a ser eliminada
                p = linha->prox;
                printf("LINHA [%s] eliminada por nao ter mais paragens.\n", nomeLinha);
                free(linha);

                sair = 1;
            }
            else {    //Se forem as outras linhas a serem eliminadas
                plinha anterior = p;
                while (anterior->prox != linha) // Procurar a linha anterior à que vai ser removida
                    anterior = anterior->prox;

                anterior->prox = linha->prox;   // Apontar para a linha a seguir a removida
                printf("LINHA [%s] eliminada por nao ter mais paragens.\n", nomeLinha);
                free(linha);
                linha = anterior->prox;

                sair = 1;
            }
        }

        if(sair == 1){
            printf("\n-> ENTER para voltar ao menu anterior");
            do{
                fflush(stdin);
                ch = getchar();
            }while( ch != '\n');
        }
        else{
            printf("\n-> Eliminar outra paragem (S/N)?");
            do {
                fflush(stdin);
                ch = getchar();
            } while (ch != 'S' && ch != 's' && ch != 'N' && ch != 'n');
        }
    } while (ch == 'S' || ch == 's');

    return p;
}

//LISTAR AS LINHAS DO METRO E AS SUAS PARAGENS
void listarLinhas(plinha p){
    pparagem aux;
    char ch;
    int n;

    fflush(stdin);
    system("cls");

    n = contaNos(p);
    if(p != NULL){
        if(n == 1){
            printf("\n\t\t\t\t\t  --------------------------------------------\n");
            printf("\n\t\t\t\t\t  |    EXISTE 1 LINHA REGISTADA NO SISTEMA    |\n");
            printf("\n\t\t\t\t\t  --------------------------------------------\n");
        }
        else{
            printf("\n\t\t\t\t\t  --------------------------------------------\n");
            printf("\n\t\t\t\t\t  |  EXISTEM %d LINHAS REGISTADAS NO SISTEMA  |\n", n);
            printf("\n\t\t\t\t\t  --------------------------------------------\n");
        }

        // Percorrer a lista das linhas
        while(p != NULL){
            int i = 1;

            printf("|------- LINHA '%s' -------|\n", p->nome);
            printf("\t  [%d] paragens\n\n", p->nParag);

            aux = p->lista;

            // Percorrer as paragens da linha
            while(aux != NULL){
                printf(" %d. Nome:%s Codigo:%s\n", i, aux->nome, aux->codigo);
                aux = aux->prox;
                i++;
            }
            putchar('\n');
            p = p->prox;
        }
    }
    else {
        printf("\n\t\t\t\t\t  --------------------------------------------\n");
        printf("\n\t\t\t\t\t  |  EXISTEM 0 LINHAS REGISTADAS NO SISTEMA  |\n");
        printf("\n\t\t\t\t\t  --------------------------------------------\n");
    }

    printf("\n-> ENTER para voltar ao menu anterior");
    do{
        fflush(stdin);
        ch = getchar();
    }while( ch != '\n');
}

//LISTAR AS LINHAS QUE PASSEM NA PARAGEM INTRODUZIDA PELO UTILIZADOR
void listarLinhasParagem(plinha p){
    pparagem aux;

    char nomeParagem[100], ch;
    int encontrada = 0;

    fflush(stdin);
    system("cls");

    printf("\n\t\t\t\t\t  --------------------------------------------\n");
    printf("\n\t\t\t\t\t  |    LISTA DA LINHA QUE PASSA NA PARAGEM   |\n");
    printf("\n\t\t\t\t\t  --------------------------------------------\n");

    printf("Listar linhas com a paragem: ");
    scanf(" %99[^\n]", nomeParagem);

    // Percorre as linhas da lista
    while(p != NULL){
        aux = p->lista;
        while(aux != NULL){
            if(strcmp(aux->nome, nomeParagem) == 0){    //Caso encontre a paragem nessa linha quebra o ciclo e segue para a próxima linha
                printf("\tLINHA '%s'\n", p->nome);
                encontrada = 1;
                break;
            }
            aux = aux->prox;
        }
        p = p->prox;
    }

    // Caso nenhuma paragem seja encontrda em todas as linhas
    if(encontrada == 0){
        printf("NENHUMA linha com a paragem [%s]\n", nomeParagem);
    }

    printf("\n-> ENTER para voltar ao menu anterior");
    do{
        fflush(stdin);
        ch = getchar();
    }while( ch != '\n');
}

