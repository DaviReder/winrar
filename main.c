#include <stdio.h>
#include <stdlib.h>
//#include <locale.h>
#include <windows.h>
#include "include/codificar.h"

int main()
{
    //setlocale(LC_ALL, "");
    int opcao, colunas, tam;
    //unsigned char frase[] = "BANANA PANTANEIRA";
    unsigned char *frase;
    unsigned int tabela_frequencia[TAM];
    Lista lista;
    No *arvore;
    char *codigo, *decodigo, **dicionario;
    SetConsoleOutputCP(65001);

    tam = descobrir_tamanho();
    printf("Quantidade de letras no arquivo: %d\n", tam);
    frase = calloc(tam+2, sizeof(unsigned char));
    ler_texto(frase);
    printf("Texto:\n%s\n\n", frase);

    printf("Algoritmo de Huffman - Davi Cabral\n");
    do{
        printf("0 - Sair.\n");
        printf("1 - Codificar e gerar arquivo a partir do log.txt\n");
        printf("2 - Ler arquivo\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            inicializa_com_zero(tabela_frequencia);
            imprime_tabela(tabela_frequencia);
            preenche_tabela(frase, tabela_frequencia);
            imprime_tabela(tabela_frequencia);

            criar_lista(&lista);
            preencher_lista(tabela_frequencia, &lista);
            imprimir_lista(&lista);

            arvore = montar_arvore(&lista);
            printf("\nÁrvore de Huffman\n");
            imprimir_arvore(arvore, 0);

            colunas = altura_arvore(arvore) + 1;
            dicionario = aloca_dicionario(colunas);
            gerar_dicionario(dicionario, arvore, "", colunas);
            imprimir_dicionario(dicionario);

            codigo = codificar(dicionario, frase);
            printf("\nTexto codificado: %s", codigo);

            compactar(codigo);
            break;
        case 2:
            //decodigo = decodificar(codigo, arvore);
            //printf("\nTexto decodificado: %s\n", decodigo);
            //descompactar(arvore);
            break;
        default:
            if(opcao != 0)
                printf("\nDigite uma opção válida.");
        }
    }while(opcao != 0);
    return 0;
}
