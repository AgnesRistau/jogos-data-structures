#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h> 

#define TAM_BUFFER 200
#define ARQUIVO_DB "animais_db.txt"

//estrutura do nó da arvore
typedef struct No {
    char dado[TAM_BUFFER];
    struct No *sim;
    struct No *nao;
} No;

//Funções Auxiliares

void lerTexto(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

void esperarEnter() {
    printf("\n[Pressione ENTER para continuar...]");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

No* criarNo(char *texto) {
    No *novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro critico: Memoria insuficiente.\n");
        exit(1);
    }
    strcpy(novo->dado, texto);
    novo->sim = NULL;
    novo->nao = NULL;
    return novo;
}

int ehFolha(No *n) {
    return (n->sim == NULL && n->nao == NULL);
}

void liberarArvore(No *n) {
    if (n == NULL) return;
    liberarArvore(n->sim);
    liberarArvore(n->nao);
    free(n);
}

//funções de banco de dados

//salva a arvore no arquivo de forma recursiva
void salvarRecursivo(No *n, FILE *f) {
    if (n == NULL) return;

    if (ehFolha(n)) {
        //[A] indica Animal
        fprintf(f, "[A]%s\n", n->dado);
    } else {
        //[P] indica Pergunta
        fprintf(f, "[P]%s\n", n->dado);
        salvarRecursivo(n->sim, f); // Salva o lado do SIM
        salvarRecursivo(n->nao, f); // Salva o lado do NAO
    }
}

void salvarBancoDeDados(No *raiz) {
    FILE *f = fopen(ARQUIVO_DB, "w");
    if (f == NULL) {
        printf("Erro ao salvar o banco de dados!\n");
        return;
    }
    salvarRecursivo(raiz, f);
    fclose(f);
    printf(">> Banco de dados atualizado com sucesso! <<\n");
}

//carrega a arvore do arquivo recursivamente
No* carregarRecursivo(FILE *f) {
    char linha[TAM_BUFFER];
    
    //tenta ler uma linha do arquivo
    if (fgets(linha, TAM_BUFFER, f) == NULL) {
        return NULL;
    }

    //remove o \n do final da linha lida
    linha[strcspn(linha, "\n")] = 0;

    //cria o nó com o texto (pula os 3 primeiros caracteres "[X]")
    No *novo = criarNo(linha + 3);

    //se a linha começar com [P], é uma pergunta, então tem filhos
    if (linha[1] == 'P') {
        novo->sim = carregarRecursivo(f);
        novo->nao = carregarRecursivo(f);
    }
    //se for [A], é animal, não faz nada (filhos continuam NULL)

    return novo;
}

No* carregarBancoDeDados() {
    FILE *f = fopen(ARQUIVO_DB, "r");
    No *raiz = NULL;

    if (f != NULL) {
        printf("Carregando inteligencia do arquivo...\n");
        raiz = carregarRecursivo(f);
        fclose(f);
    }

    //se o arquivo não existir (primeira vez), cria o padrão
    if (raiz == NULL) {
        printf("Nenhum banco de dados encontrado. Criando novo...\n");
        raiz = criarNo("Cachorro");
    }

    return raiz;
}

//lógica do Jogo (Igual a anterior)

int confirmar(char *pergunta) {
    char resp[10];
    printf("%s (s/n): ", pergunta);
    lerTexto(resp, 10);
    return (toupper(resp[0]) == 'S');
}

void jogar(No *atual) {
    printf("\n----------------------------------------\n");
    
    while (!ehFolha(atual)) {
        if (confirmar(atual->dado)) {
            atual = atual->sim;
        } else {
            atual = atual->nao;
        }
    }

    printf("--> O animal que voce pensou e: %s?\n", atual->dado);
    
    if (confirmar("Acertei?")) {
        printf("\n>>> Haha! Eu sabia! <<<\n");
    } else {
        printf("\nAh nao! Eu perdi.\n");
        
        printf("Que animal era? ");
        char novoAnimal[TAM_BUFFER];
        lerTexto(novoAnimal, TAM_BUFFER);

        printf("Que pergunta diferencia um(a) %s de um(a) %s?\n> ", novoAnimal, atual->dado);
        char novaPergunta[TAM_BUFFER];
        lerTexto(novaPergunta, TAM_BUFFER);

        printf("Para um(a) %s, a resposta para essa pergunta e Sim ou Nao?\n", novoAnimal);
        int respostaParaNovo = confirmar("Resposta");

        char animalAntigo[TAM_BUFFER];
        strcpy(animalAntigo, atual->dado);
        strcpy(atual->dado, novaPergunta);

        if (respostaParaNovo) {
            atual->sim = criarNo(novoAnimal);
            atual->nao = criarNo(animalAntigo);
        } else {
            atual->nao = criarNo(novoAnimal);
            atual->sim = criarNo(animalAntigo);
        }
        
        printf("\n[Aprendido!]\n");
    }
}

int main() {
    //serve para corrigir erros graficos do texto
    system("chcp 1252");
    system("cls");
    setlocale(LC_ALL, "Portuguese");

    No *raiz = carregarBancoDeDados();

    printf("\n==================================\n");
    printf("    AKINATOR COM MEMORIA (TXT)    \n");
    printf("==================================\n");

    int jogando = 1;
    while (jogando) {
        printf("\nPense em um animal...\n");
        esperarEnter();

        jogar(raiz);

        printf("\n----------------------------------------\n");
        jogando = confirmar("Quer jogar novamente?");
    }

    salvarBancoDeDados(raiz);
    
    liberarArvore(raiz);
    printf("\nAte a proxima!\n");
    return 0;
}
