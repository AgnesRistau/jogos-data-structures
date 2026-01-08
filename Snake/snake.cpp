#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define ALT 15
#define LARG 30

typedef struct No {
    int x, y;
    struct No* prox;
} No;

typedef struct {
    No* inicio; // cauda
    No* fim;    // cabeca
} Fila;

Fila cobra;
int comidaX, comidaY;
char direcao = 'd';
int gameOver = 0;
int frutasComidas = 0;

void initFila(Fila* f) {
    f->inicio = f->fim = NULL;
}

void enqueue(Fila* f, int x, int y) {
    No* novo = (No*)malloc(sizeof(No));
    novo->x = x;
    novo->y = y;
    novo->prox = NULL;

    if (f->fim == NULL) {
        f->inicio = f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

void dequeue(Fila* f) {
    if (f->inicio == NULL) return;

    No* temp = f->inicio;
    f->inicio = f->inicio->prox;

    if (f->inicio == NULL)
        f->fim = NULL;

    free(temp);
}

int posicaoOcupada(int x, int y) {
    No* atual = cobra.inicio;
    while (atual != NULL) {
        if (atual->x == x && atual->y == y)
            return 1;
        atual = atual->prox;
    }
    return 0;
}


void gerarComida() {
    do {
        comidaX = rand() % (ALT - 2) + 1;
        comidaY = rand() % (LARG - 2) + 1;
    } while (posicaoOcupada(comidaX, comidaY));
}

int colisaoComCorpo(int x, int y) {
    No* atual = cobra.inicio;
    while (atual != NULL) {
        if (atual->x == x && atual->y == y)
            return 1;
        atual = atual->prox;
    }
    return 0;
}

void desenhar() {
    system("cls");

    for (int i = 0; i < LARG + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < ALT; i++) {
        for (int j = 0; j < LARG; j++) {
            if (j == 0) printf("#");

            int impresso = 0;

            if (i == comidaX && j == comidaY) {
                printf("@");
                impresso = 1;
            }

            No* atual = cobra.inicio;
            while (atual != NULL) {
                if (atual->x == i && atual->y == j) {
                    printf("O");
                    impresso = 1;
                    break;
                }
                atual = atual->prox;
            }

            if (!impresso)
                printf(" ");

            if (j == LARG - 1) printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < LARG + 2; i++) printf("#");
    printf("\n");
    printf("Use W A S D | ESC para sair\n");
    printf("Frutas comidas: %d\n", frutasComidas);
}

void atualizar() {
    int novoX = cobra.fim->x;
    int novoY = cobra.fim->y;

    switch (direcao) {
        case 'w': novoX--; break;
        case 's': novoX++; break;
        case 'a': novoY--; break;
        case 'd': novoY++; break;
    }

    // colisao com parede
    if (novoX < 0 || novoX >= ALT || novoY < 0 || novoY >= LARG) {
        gameOver = 1;
        return;
    }

    if (colisaoComCorpo(novoX, novoY)) {
        gameOver = 1;
        return;
    }

    enqueue(&cobra, novoX, novoY);

    if (novoX == comidaX && novoY == comidaY) {
        frutasComidas++;
        gerarComida(); // cresce
    } else {
        dequeue(&cobra); // anda
    }
}

int main() {
    srand(time(NULL));
    initFila(&cobra);

    enqueue(&cobra, ALT / 2, LARG / 2);
    gerarComida();

    while (!gameOver) {
        if (_kbhit()) {
            char tecla = _getch();
            if (tecla == 27) break; // ESC
            if (
                (tecla == 'w' && direcao != 's') || 
                (tecla == 'a' && direcao != 'd') || 
                (tecla == 's' && direcao != 'w') || 
                (tecla == 'd' && direcao != 'a')
            ) {
                direcao = tecla;
            }
        }

        atualizar();
        desenhar();
        Sleep(200);
    }

    system("cls");
    printf("===== GAME OVER =====\n");
    printf("Frutas comidas: %d\n", frutasComidas);

    while(cobra.inicio != NULL){
        dequeue(&cobra);
    }

    return 0;
}

