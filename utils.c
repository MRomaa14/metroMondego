// Miguel Umbelino da Mota Roma - a2021138955

#include "utils.h"

//GERAR CODIGO ALFANUMERICO DE 4 CARACTERES
void gerarCodigo(char* cod){
    char ch[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int n = sizeof(ch) - 1;
    srand(time(NULL));

    for(int i = 0; i < 4; i++){
        cod[i] = ch[rand() % n];
    }
    cod[4] = '\0';
}

//LER OS FICHEIROS DE TEXTO PERSONALIZADOS A SEREM USADOS COMO TITULOS
int lerFich(char *nomeF){
    FILE *f = fopen(nomeF,"r");
    if(f == NULL) {
        printf("ERRO: nao foi possivel abrir o ficheiro %s\n", nomeF);
        fclose(f);
        return 1;
    }

    char buffer[MAX];
    while(fgets(buffer, MAX, f) != NULL)
        printf("%s", buffer);

    fclose(f);
    return 0;
}



