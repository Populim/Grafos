#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//A struct palavra armazena uma palavra lida e sua classe gramatical;
typedef struct PALAVRA Palavra;
struct PALAVRA{
	char palavra[30];
	char tipo[5];
};

typedef struct GRAFO Grafo;
struct GRAFO{
	int** mat; //matriz de adjacência
	int tam; //tamanho
};


Palavra* Parser3(char* word);
Palavra* Parser2(char* word);
Palavra** Parser(FILE* fp, int* contador);
int getWordPosition(Palavra** lista, char* word,int count);
void printWords(Palavra** lista, int count, int nro);
void juntaPalavras(Palavra** lista1, Palavra** lista2,Palavra** lista3,int cont1,int cont2,int* cont3);
Grafo* alocaGrafo(int size);
void printMatrix(Grafo* g);
void liberaGrafo(Grafo* g);
void liberaPalavra(Palavra** p, int size);