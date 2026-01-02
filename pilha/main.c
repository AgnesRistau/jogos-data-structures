#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// Tamanho máximo da pilha
#define MAX_SIZE 6


// Definição da pilha
typedef struct {
    int items[MAX_SIZE];
    int top;
    int qtd;
} Stack;

void createStack(Stack *s) {
    s->top = -1;
    s->qtd = 0;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

bool isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

int stackSize(Stack *s) {
    return s->qtd;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Erro: Pilha cheia. Não é possível empilhar %d\n", value);
    } else {
        s->items[++(s->top)] = value;
        s->qtd++;
    }
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Erro: Pilha vazia.\n");
    }

    s->qtd--;
    return s->items[(s->top)--];
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Erro: Pilha vazia!\n");
    }
    return s->items[s->top];
}

void centralizar_texto(char *texto, int largura) {
    int tamanho = strlen(texto);
    
    int espacamento = (largura - tamanho) / 2;
    for (int i = 0; i < espacamento; i++) {
        printf(" ");
    }
    printf("%s", texto);
    for (int i = 0; i < espacamento; i++) {
        printf(" ");
    }
}


char* construir_camada_torre (int size) {
    switch (size) {
        case 1:
            return "O";
        case 2:
            return "oOo";
        case 3:
            return "OOO";
        case 4:
            return "oOOOo";
        case 5:
            return "OOOOO";
        case 6:
            return "oOOOOOo";
    }
}


void exibir_pilhas(Stack *s1, Stack *s2, Stack *s3) {
    printf("- Pilha 1- Pilha 2- Pilha 3 -\n");
    int i_s1 = 0;
    int i_s2 = 0;
    int i_s3 = 0;

    
    for (int i = 0; i <= MAX_SIZE; i++) {
        int s1_qtd = stackSize(s1);
        int s2_qtd = stackSize(s2);
        int s3_qtd = stackSize(s3);

        if (MAX_SIZE - s1_qtd + 1 > i) {
            centralizar_texto("|", 10);
        } else {
            centralizar_texto(render_block(s1->items[s1_qtd-1-i_s1]), 10);
            i_s1++;
        }

        if (MAX_SIZE - s2_qtd + 1 > i) {
            centralizar_texto("|", 10);
        } else {
            centralizar_texto(render_block(s2->items[s2_qtd-1-i_s2]), 10);
            i_s2++;
        }

        if (MAX_SIZE - s3_qtd + 1 > i) {
            print_centered("|", 10);
        } else {
            print_centered(render_block(s3->items[s3_qtd-1-i_s3]), 10);
            i_s3++;
        }   

        printf("\n");
    }
}

Stack s1, s2, s3;

Stack *pilhas[] = {&s1, &s2, &s3};

void setup() {
    
    createStack(&s1);
    createStack(&s2);
    createStack(&s3);

    push(&s1, 6);
    push(&s1, 5);
    push(&s1, 4);
    push(&s1, 3);
    push(&s1, 2);
    push(&s1, 1);
    
    exibir_pilhas(&s1, &s2, &s3);

}

void swap_stacks(Stack *source, Stack *destination) {
    if (isEmpty(source)) {
        printf("Erro: Pilha de origem vazia!\n");
        return;
    }

    int item = peek(source);

    if (!isEmpty(destination) && item > peek(destination)) {
        printf("Erro: Movimento inválido! Não é possível colocar um bloco maior sobre um menor.\n");
        Sleep(2500);
        return;
    }

    if (source == destination) {
        printf("Erro: Pilha de origem e destino são iguais!\n");
        Sleep(2500);
        return;
    }

    pop(source);
    push(destination, item);
}

void pedir_para_trocar_peca() {
    int source, destination;
    // Implementation for user interaction to swap stacks
    printf("------------------------------\n");
    print_centered("Escolha as pilhas para mover os blocos.\n", 30);
    printf("Digite o número da pilha de origem (1, 2 ou 3): ");
    scanf("%d", &source);
    printf("Digite o número da pilha de destino (1, 2 ou 3): ");
    scanf("%d", &destination);

    swap_stacks(pilhas[source - 1], pilhas[destination - 1]);
}


void verificar_vitoria() {
    if (stackSize(&s3) == 4) {
        system("cls");
        printf("Parabéns! Você venceu o jogo!\n");
        exibir_pilhas(&s1, &s2, &s3);
        exit(0);
    }
}

int main() {
    // Isso faz o console reconhecer acentos da lingua portuguesa
    system("chcp 65001 > nul"); 
    system("cls");

    printf("Bem-vindo ao jogo Torres de Hanoi!\n");
    printf("O seu objetivo é o mover todos os blocos da Pilha 1 para a Pilha 3.\n");

    printf("Regras:\n");
    printf("1. Você só pode mover um bloco por vez.\n");
    printf("2. Você não pode colocar um bloco maior sobre um menor.\n\n");
    printf("Pressione qualquer tecla para começar...");

    getchar();

    system("cls");


    setup();
    pedir_para_trocar_peca();
    while (true) {
        system("cls");
        exibir_pilhas(&s1, &s2, &s3);
        verificar_vitoria();
        pedir_para_trocar_peca();
    }
    return 0;
}
