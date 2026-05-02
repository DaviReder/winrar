#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // Para imprimir corretamente textos em portugues no terminal do windows.
#include "include/codificar.h"
#include "include/decodificar.h"

int main() {
    SetConsoleOutputCP(65001);
    int opcao;

    printf("'Winrar' - Compactador de arquivos com Huffman\n");
    do {
        printf("1 - Codificar e gerar arquivo binário.\n");
        printf("2 - Descompactar arquivo e gerar .txt.\n");
        printf("0 - Sair.\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            executar_compactacao();
            break;
        case 2:
            descompactar("data/compactado.dc", "data/descompactado.txt");
            break;
        default:
            if(opcao != 0)
                printf("\nDigite uma opção válida.");
            }
    }while(opcao != 0);
    return 0;
}
