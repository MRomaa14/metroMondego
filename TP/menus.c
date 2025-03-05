// Miguel Umbelino da Mota Roma - a2021138955

#include "menus.h"

int menuInicial(){
    int opt;

    system("cls");
    lerFich("metro.txt");

    printf("\t\t\t\t    --------------------------------------------\n");
    printf("\t\t\t\t    |             Miguel Roma - TP             |\n");
    printf("\t\t\t\t    --------------------------------------------\n");
    printf("\t\t\t\t    |       [  1 - Iniciar percurso    ]       |\n");
    printf("\t\t\t\t    |       [  2 - Gestao das linhas   ]       |\n");
    printf("\t\t\t\t    |       [  3 - Gestao das paragens ]       |\n");
    printf("\t\t\t\t    |       [  4 - Ler ficheiro texto  ]       |\n");
    printf("\t\t\t\t    |       [  5 - Guardar e sair      ]       |\n");
    printf("\t\t\t\t    --------------------------------------------\n");

    putchar('\n');

    printf("-> Digite uma opcao: ");
    scanf("%d", &opt);
    fflush(stdin);

    return opt;
}

int menuPercurso(){
    int opt;

    system("cls");
    lerFich("percurso.txt");

    printf("\t\t\t\t    ---------------------------------------------\n");
    printf("\t\t\t\t    |             Miguel Roma - TP              |\n");
    printf("\t\t\t\t    ---------------------------------------------\n");
    printf("\t\t\t\t    |        [   1 - Linha unica       ]        |\n");
    printf("\t\t\t\t    |        [   2 - Mudanca de linha  ]        |\n");
    printf("\t\t\t\t    |        [   3 - Voltar            ]        |\n");
    printf("\t\t\t\t    ---------------------------------------------\n");

    putchar('\n');

    printf("-> Digite uma opcao:");
    scanf("%d", &opt);
    fflush(stdin);

    return opt;
}

int menuLinhas(){
    int opt;

    system("cls");
    lerFich("linha.txt");

    printf("\t\t\t\t    --------------------------------------------\n");
    printf("\t\t\t\t    |             Miguel Roma - TP             |\n");
    printf("\t\t\t\t    --------------------------------------------\n");
    printf("\t\t\t\t    |       [   1 - Adicionar linha    ]       |\n");
    printf("\t\t\t\t    |       [   2 - Adicionar paragem  ]       |\n");
    printf("\t\t\t\t    |       [   3 - Eliminar paragem   ]       |\n");
    printf("\t\t\t\t    |       [   4 - Visualizar linhas  ]       |\n");
    printf("\t\t\t\t    |       [   5 - Linhas com paragem ]       |\n");
    printf("\t\t\t\t    |       [   6 - Voltar             ]       |\n");
    printf("\t\t\t\t    --------------------------------------------\n");

    putchar('\n');

    printf("-> Digite uma opcao:");
    scanf("%d", &opt);
    fflush(stdin);

    return opt;
}

int menuParagens(){
    int opt;

    system("cls");
    lerFich("paragem.txt");

    printf("\t\t\t\t    --------------------------------------------\n");
    printf("\t\t\t\t    |              Miguel Roma - TP             |\n");
    printf("\t\t\t\t    --------------------------------------------\n");
    printf("\t\t\t\t    |       [   1 - Registar paragem    ]       |\n");
    printf("\t\t\t\t    |       [   2 - Eliminar paragem    ]       |\n");
    printf("\t\t\t\t    |       [   3 - Visualizar paragens ]       |\n");
    printf("\t\t\t\t    |       [   4 - Voltar              ]       |\n");
    printf("\t\t\t\t    --------------------------------------------\n");

    putchar('\n');

    printf("-> Digite uma opcao: ");
    scanf("%d", &opt);
    fflush(stdin);

    return opt;
}