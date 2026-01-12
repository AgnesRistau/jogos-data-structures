# jogos-data-structures

Este repositório contém dois jogos feitos utilizando a estrutura de dados *pilha*, *fila* e *árvore*

## Pilha - Agnes Ristau

O jogo construído em c, que utiliza a estrutura de dados Pilha, foi uma implementação da Torre de Hanói, que é um quebra-cabeça matemático com três hastes e discos de tamanhos diferentes, onde o objetivo é transferir todos os discos de uma haste para terceira seguindo duas regras: mover um disco por vez e nunca colocar um disco maior sobre um menor, utilizando uma haste auxiliar.

## Fila - Leonardo Dias

O jogo é uma implementação do "jogo da cobrinha" ou "snake", utilizando a estrutura de dados Fila. O objetivo é pegar o máximo de frutas(@), sem colidir com as paredes ou o próprio corpo, enquanto a cobra aumenta de tamanho. Por questões de simplicidade, o programa só funciona no windows.

No jogo:

-Cada elemento da fila representa uma parte do corpo da cobra

-A cauda corresponde ao primeiro elemento da fila

-A cabeça corresponde ao último elemento inserido

### Requisitos

-Windows

-Compilador C++ (MinGW, g++, ou equivalente)

### Compilação

No terminal (cmd ou PowerShell), navegue até a pasta do projeto e execute:
```bash
g++ snake.cpp -o snake
```
### Execução
```bash
.\snake
```

## Arvore - Lucas De Lima

O jogo é uma implementação de um sistema de adivinhação estilo "Akinator", utilizando a estrutura de dados Árvore Binária de Decisão. O objetivo é que a Inteligência Artificial adivinhe o animal pensado pelo jogador fazendo perguntas de Sim/Não. O sistema possui capacidade de aprendizado dinâmico: se o computador errar, ele expande a árvore inserindo o novo animal e uma nova pergunta de diferenciação no banco de dados (.txt). Por utilizar comandos de sistema para limpeza de tela e acentuação (system), o programa é otimizado para Windows.

No jogo:

Cada nó da árvore representa uma Pergunta ou uma Resposta Final (Animal).

A raiz corresponde à pergunta inicial (ex: "Tem ossos?").

O filho da direita corresponde ao caminho do "Sim".

O filho da esquerda corresponde ao caminho do "Não".

O banco de dados é carregado e salvo em pré-ordem (Pre-order Traversal) num arquivo de texto.

Requisitos

Windows

Compilador C (GCC, MinGW ou o embutido no Dev-C++)

Compilação No terminal (cmd ou PowerShell), navegue até a pasta do projeto e execute:

```bash

gcc advinhe.c -o advinhe.exe
```
Execução

```bash

.\advinhe.exe
```
