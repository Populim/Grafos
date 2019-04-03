#include "grafo.h"

int main(){
	int cont1 = 0;
	int cont2 = 0;
	int cont3 = 0;

	//Lê os arquivos input1 e input2, e guarda as palavras lidas nos vetores lista1 e lista2, respectivamente;
	FILE* fp = fopen("input1", "r");
	Palavra** lista1 = Parser(fp, &cont1);
	fclose(fp);
	fp = fopen("input2", "r");
	Palavra** lista2 = Parser(fp, &cont2);
	fclose(fp);
	
	//Imprime o que foi lido;
	printWords(lista1, cont1, 1);
	printWords(lista2, cont2, 2);

	//Cria um terceiro vetor que contém todas as palavras dos dois outros vetores, só que sem repetições;
	Palavra** lista3 = malloc((cont1+cont2) * sizeof(Palavra*));
	juntaPalavras(lista1, lista2, lista3, cont1, cont2, &cont3);
	printWords(lista3, cont3, 3);
	
	
	//Aloca as matrizes de adjacência para que seja feita a comparação dos grafos;
	Grafo* g1 = alocaGrafo(cont3);
	Grafo* g2 = alocaGrafo(cont3);
	
	//Zera as matrizes
	for (int i = 0; i < cont3; ++i){
		for (int j = 0; j < cont3; ++j){
			g1->mat[i][j] = 0;
			g2->mat[i][j] = 0;
		}
	}

	//Armazenam as conexões entre palavras nas matrizes de adjacência
	//A matriz 1 representa as arestas do grafo formado pelo texto contido no vetor lista 1
	//A matriz 2 representa as arestas do grafo formado pelo texto contido no vetor lista 2
	for (int i = 0; i < cont1 - 1; ++i){
		g1->mat[getWordPosition(lista3,lista1[i]->palavra,cont3)][getWordPosition(lista3,lista1[i+1]->palavra,cont3)] = 1;
	}
	for (int i = 0; i < cont2 - 1; ++i){
		g2->mat[getWordPosition(lista3,lista2[i]->palavra,cont3)][getWordPosition(lista3,lista2[i+1]->palavra,cont3)] = 1;
	}

	//Imprime as matrizes
	printf("Matriz1: \n");
	printMatrix(g1);

	printf("Matriz2: \n");
	printMatrix(g2);


	//Algoritmo do coeficiente de similaridade de Jaccard
	int andSum = 0;
	int orSum = 0;
	for (int i = 0; i < cont3; ++i){
		for (int j = 0; j < cont3; ++j){
			if(g1->mat[i][j] < g2->mat[i][j]){
				andSum += g1->mat[i][j];
				orSum += g2->mat[i][j];
			}
			else{
				andSum += g2->mat[i][j];
				orSum += g1->mat[i][j];
			}
		}
	}


	printf("\nsimilaridade: %f \n",(float)andSum/(float)orSum);

	liberaPalavra(lista1, cont1);
	liberaPalavra(lista2, cont2);
	liberaPalavra(lista3, cont3);
	liberaGrafo(g1);
	liberaGrafo(g2);


}