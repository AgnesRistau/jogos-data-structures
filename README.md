# jogos-data-structures

Este repositório contém dois jogos feitos utilizando a estrutura de dados *pilha* e *fila*.

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
g++ main.cpp -o snake
```
### Execução
```bash
.\snake
```

## Arvore - Lucas De Lima

O jogo é uma inspiração direta do famoso jogo "Akinator", só que advinhando animais, o qual utiliza a estrutura de dados Arvore. A ideia é bem simples, pense em um animal e responda as perguntas que ele irá fazer para tentar advinhar o animal. Se ele não advinhar o animal, ele irá perguntar qual é o animal e qual pergunta diferencia esse animal do que ele tentou advinhar, salvando em seu banco de dados. 
