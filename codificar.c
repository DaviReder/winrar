#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/codificar.h"

// ====================================================
// =========== FUNCOES TABELA DE FREQUENCIA ===========
// ====================================================

void inicializa_com_zero(unsigned int vet[]){
    for(int i=0; i<TAM; i++){
        vet[i] = 0;
    }
}

void preenche_tabela(unsigned char texto[], unsigned int tabela[]){
    int i = 0;
    while(texto[i] != '\0'){
        tabela[texto[i]]++;
        i++;
    }
}

void imprime_tabela(unsigned int tabela[]){
    printf("\nTabela de Frequência\n");
    for(int i=0; i<TAM; i++){
        if(tabela[i] > 0){
            printf("[%d]: %d = '%c'\n", i, tabela[i], i);
        }
    }
}

// ======================================================
// =========== FUNCOES PARA LISTA 'ENCADEADA' ===========
// ======================================================

void criar_lista(Lista *lista){
    lista->inicio = NULL;
    lista->tam = 0;
}

void inserir_ordenado(Lista *lista, No *no){
    No *aux;
    if(lista->inicio == NULL){
        lista->inicio = no;
    }
    else if(no->frequencia < lista->inicio->frequencia){
        no->prox = lista->inicio;
        lista->inicio = no;
    }
    else{
        aux = lista->inicio;
        while(aux->prox && aux->prox->frequencia <= no->frequencia){
            aux = aux->prox;
        }
        no->prox = aux->prox;
        aux->prox = no;
    }
    lista->tam++;
}

void preencher_lista(unsigned int tab[], Lista *lista){
    No *novo;
    for(int i=0; i<TAM; i++){
        if(tab[i] > 0){
            novo = malloc(sizeof(No));
            if(novo){
                novo->caracter = i;
                novo->dir = NULL;
                novo->esq = NULL;
                novo->frequencia = tab[i];
                novo->prox = NULL;

                inserir_ordenado(lista, novo);
            }
            else{
                printf("\nErro ao alocar memoria: 'preencher_lista'.");
                break;
            }
        }
    }
}

void imprimir_lista(Lista *lista){
    No *aux = lista->inicio;
    printf("\nImprimindo Lista: Tamanho: %d\n", lista->tam);
    while(aux){
        printf("Caracter: %c, Frequência: %u\n", aux->caracter, aux->frequencia);
        aux = aux->prox;
    }
    printf("\n");
}

// ======================================================
// =========== FUNCOES PARA ARVORE DE HUFFMAN ===========
// ======================================================

No* remover_inicio(Lista *lista){
    No *aux = NULL;

    if(lista->inicio){
        aux = lista->inicio;
        lista->inicio = aux->prox;
        aux->prox = NULL;
        lista->tam--;
    }

    return aux;
}

No* montar_arvore(Lista *lista){
    No *primeiro, *segundo, *novo;
    while(lista->tam > 1){
        primeiro = remover_inicio(lista);
        segundo = remover_inicio(lista);
        novo = malloc(sizeof(No));

        if(novo){
            novo->caracter = '+';
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esq = primeiro;
            novo->dir = segundo;
            novo->prox = NULL;

            inserir_ordenado(lista, novo);
        }
        else{
            printf("\nErro ao alocar memória: 'montar_arvore'.");
            break;
        }

    }
    return lista->inicio;
}

void imprimir_arvore(No *raiz, int tam){
    if(raiz->esq == NULL && raiz->dir == NULL){
        printf("Folha: %c\tAltura: %d\n", raiz->caracter, tam);
    }
    else{
        imprimir_arvore(raiz->esq, tam+1);
        imprimir_arvore(raiz->dir, tam+1);
    }
}

// ======================================================
// =========== MONTAGEM DO DICIONARIO HUFFMAN ===========
// ======================================================

int altura_arvore(No *raiz){
    int esq, dir;
    if(raiz == NULL){
        return -1;
    }
    else{
        esq = altura_arvore(raiz->esq) +1;
        dir = altura_arvore(raiz->dir) +1;
        if(esq > dir) return esq;
        else return dir;
    }
}

char** aloca_dicionario(int colunas){
    char **dicionario;
    dicionario = malloc(sizeof(char*) * TAM);

    for(int i=0; i<TAM; i++){
        dicionario[i] = calloc(colunas, sizeof(char));
    }
    return dicionario;
}

void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas){
    char esquerda[colunas], direita[colunas];
    if(raiz->dir == NULL && raiz->esq == NULL){
        strcpy(dicionario[raiz->caracter], caminho);
    }
    else{
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gerar_dicionario(dicionario, raiz->esq, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}

void imprimir_dicionario(char **dicionario){
    printf("\nDicionario de Huffman\n");
    for(int i=0; i<TAM; i++){
        if(strlen(dicionario[i]) > 0)
            printf("%3d: %s\n", i, dicionario[i]);
    }
    printf("\n");
}

// ===================================
// =========== CODIFICAÇÃO ===========
// ===================================

int calc_tamanho_string(char **dicionario, unsigned char *texto){
    int i=0, tam=0;
    while(texto[i] != '\0'){
        tam = tam+strlen(dicionario[texto[i]]);
        i++;
    }
    return tam+1;
}

char* codificar(char **dicionario, unsigned char *texto){
    int i=0, tam = calc_tamanho_string(dicionario, texto);
    char *codigo = calloc(tam, sizeof(char));

    while(texto[i] != '\0'){
        strcat(codigo, dicionario[texto[i]]);
        i++;
    }
    return codigo;
}

// ===================================
// =========== DECODIFICAR ===========
// ===================================

char* decodificar(unsigned char texto[], No *raiz){
    No *aux = raiz;
    char temp[2];
    char *decodificado = calloc(strlen(texto), sizeof(char));

    for(int i=0; texto[i] != '\0'; i++){
        if(texto[i] == '0'){
            aux = aux->esq;
        }
        else{
            aux = aux->dir;
        }

        if(aux->esq == NULL && aux->dir == NULL){
            temp[0] = aux->caracter;
            temp[1] = '\0';
            strcat(decodificado, temp);
            aux = raiz;
        }
    }

    return decodificado;
}

// =========================================
// =========== MANIPULAR ARQUIVO ===========
// =========================================

void compactar(unsigned char codificado[]){
    FILE *arquivo = fopen("compactado.dc", "wb");
    int i=0, j=7;
    unsigned char mascara, byte=0;

    if(arquivo == NULL){
        fclose(arquivo);
        printf("\nErro ao abrir arquivo em 'compactar'.");
        return;
    }

    while(codificado[i] != '\0'){
        mascara=1;
        if(codificado[i] == '1'){
            mascara = mascara << j;
            byte = byte | mascara;
        }
        j--;

        if(j<0){
            fwrite(&byte, sizeof(unsigned char), 1, arquivo);
            byte=0;
            j=7;
        }
        i++;
    }
    if(j!=7){
        fwrite(&byte, sizeof(unsigned char), 1, arquivo);
    }
    fclose(arquivo);
}

unsigned int testa_bit(unsigned char byte, int i){
    unsigned char mascara = (1 << i);
    return byte & mascara;
}

void descompactar(No *raiz){
    FILE *arquivo = fopen("compactado.dc", "rb");
    unsigned char byte;
    No *aux = raiz;

    if(arquivo == NULL){
        fclose(arquivo);
        printf("\nErro ao abrir arquivo em 'descompactar'.");
        return;
    }

    while(fread(&byte, sizeof(unsigned char), 1, arquivo)){
        for(int i=7; i>=0; i--){
            if(testa_bit(byte, i))
                aux = aux->dir;
            else
                aux = aux->esq;

            if(aux->dir == NULL && aux->esq == NULL){
                printf("%c", aux->caracter);
                aux = raiz;
            }
        }
    }
    printf("\n");
    fclose(arquivo);
}

int descobrir_tamanho(){
    FILE *arquivo = fopen("log.txt", "r");
    int tam=0;

    if(arquivo == NULL){
        fclose(arquivo);
        printf("\nErro ao abrir arquivo! (descobrir_tamanho)\n");
        return 0;
    }

    while(fgetc(arquivo) != -1){
        tam++;
    }
    return tam;
}

void ler_texto(unsigned char *frase){

    FILE *arquivo = fopen("log.txt", "r");
    int i=0;
    char letra;

    if(arquivo == NULL){
        fclose(arquivo);
        printf("\nErro ao abrir arquivo! (ler_texto)\n");
        return;
    }

    while(!feof(arquivo)){
        letra = fgetc(arquivo);
        if(letra != -1){
            frase[i] = letra;
            i++;
        }
    }
    fclose(arquivo);
}

