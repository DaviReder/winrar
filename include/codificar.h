#ifndef CODIFICAR_H_INCLUDED
#define CODIFICAR_H_INCLUDED
#define TAM 256

// =========== STRUCTS GERAIS ===========

typedef struct no{
    unsigned char caracter;
    unsigned int frequencia;
    struct no *prox, *dir, *esq;
}No;

typedef struct lista{
    No *inicio;
    int tam;
}Lista;

// =========== FUNCOES TABELA DE FREQUENCIA ===========

void inicializa_com_zero(unsigned int vet[]);
void preenche_tabela(unsigned char texto[], unsigned int tabela[]);
void imprime_tabela(unsigned int tabela[]);

// =========== FUNCOES PARA LISTA 'ENCADEADA' ===========

void criar_lista(Lista *lista);
void inserir_ordenado(Lista *lista, No *no);
void preencher_lista(unsigned int tab[], Lista *lista);
void imprimir_lista(Lista *lista);

// =========== FUNCOES PARA ARVORE DE HUFFMAN ===========

No* remover_inicio(Lista *lista);
No* montar_arvore(Lista *lista);
void imprimir_arvore(No *raiz, int tam);

// =========== MONTAGEM DO DICIONARIO ===========

int altura_arvore(No *raiz);
char** aloca_dicionario(int colunas);
void gerar_dicionario(char **dicionario, No *raiz, char *caminho, int colunas);
void imprimir_dicionario(char **dicionario);

// =========== CODIFICAR ===========

int calc_tamanho_string(char **dicionario, unsigned char *texto);
char* codificar(char **dicionario, unsigned char *texto);

// =========== DECODIFICAR ===========

char* decodificar(unsigned char texto[], No *raiz);

// =========== ESCREVER ARQUIVO ===========

void compactar(unsigned char codificado[]);
unsigned int testa_bit(unsigned char byte, int i);
void descompactar(No *raiz);

int descobrir_tamanho();
void ler_texto(unsigned char *frase);


#endif // CODIFICAR_H_INCLUDED
