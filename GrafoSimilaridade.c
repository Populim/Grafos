#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//A struct palavra armazena uma palavra lida e sua classe gramatical;
typedef struct PALAVRA Palavra;
struct PALAVRA{
	char palavra[30];
	char tipo[5];
};

//A função Parser3 lê apenas a palavra, cria uma struct palavra, guardando a palavra lida.
//O tipo da palavra(classe gramatical) será armazenada nessa struct pela função Parser2,
//após o retorno da função Parser3;
Palavra* Parser3(char* word){
	Palavra* p = malloc(sizeof(Palavra));
	int i = 0;
	for(i; word[i] != '/';i++){
		p->palavra[i] = word[i];
	}
	p->palavra[i] = '\0';
	return p;
}

//A função Parser2 classifica o tipo de palavra lida, e chama a função Parser3 para armazenar apenas as palavras dos tipos:
//ADJ = adjetivo
//PNM = nome/parte do nome
//V = verbo
//CN = substantivo comum;
Palavra* Parser2(char* word){
	char* aux;
	aux = strrchr(word,'/');
	aux++;
	Palavra* p;
	if(strlen(aux) == 0)
		return NULL;

	if(strcmp(aux,"ADJ") == 0){
		p = Parser3(word);
		strcpy(p->tipo,"ADJ");
		return p;
	}
	else if(strcmp(aux,"PNM") == 0){
		p = Parser3(word);
		strcpy(p->tipo,"PNM");
		return p;
	}
	else if(strcmp(aux,"V") == 0){
		p = Parser3(word);
		strcpy(p->tipo,"V");
		return p;
	}
	else if(strcmp(aux,"CN") == 0){
		p = Parser3(word);
		strcpy(p->tipo,"CN");
		return p;
	}
	return NULL;
}

//A função Parser percorre o arquivo e armazena o que foi lido eliminando sinais de pontuação e variações da palavra, como gênero e número.
//Ela também chama a função Parser2 para fazer um parsing mais profundo, e para retornar as palavras de classes desejadas. As palavras
//retornadas são armazenadas em um vetor do tipo palavra; 
Palavra** Parser(FILE* fp, int* contador){
	Palavra** vetor = malloc(sizeof(Palavra*) * 100);
	Palavra* checknull;
	int count = 0;
	char aux[50];
	char* aux2;
	fscanf(fp,"%s", &aux);
	while(!feof(fp)){
		if(strchr(aux,'<') == NULL){
			if(strchr(aux,'#') != NULL){
				aux2 = strchr(aux,'#');
				(*aux2) = '\0';
			}
			checknull = Parser2(aux);
			if(checknull != NULL){
				vetor[count] = checknull;
				count++;
			}
		}
		fscanf(fp,"%s", &aux);
	}
	*contador = count;
	return vetor;
}

//Retorna a posição de uma string no vetor de palavras;
int getWordPosition(Palavra** lista, char* word,int count){
	for (int i = 0; i < count; ++i){
		if(strcmp(lista[i]->palavra, word) == 0){
			return i;
		}
	}
	printf("erro erro deu erro socorro\n");
}

//Printa o vetor de structs "Palavra";
void printWords(Palavra** lista, int count, int nro){
	printf("Palavras no vetor %d: %d palavras\n", nro, count);
	for(int i = 0; i < count; i++){
		printf("%s %s\n", lista[i]->palavra,lista[i]->tipo);
	}
	printf("\n");
}

//Junta dois vetores de palavras, porém, caso os dois vetores juntados tenham palavras iguais, o vetor resultante não receberá
//a palavra repetida.
//Vetor origem 1 = lista 1, número de palavras no vetor origem = cont1
//Vetor origem 2 = lista 2, número de palavras no vetor origem = cont2
//Vetor resultante = lista 3, número de palavras no vetor resultante = cont3;
void juntaPalavras(Palavra** lista1, Palavra** lista2,Palavra** lista3,int cont1,int cont2,int* cont3){
	int flag = 0;
	for (int i = 0; i < cont1; ++i){
		for (int j = 0; j < cont2; ++j){
			if(strcmp(lista1[i]->palavra,lista2[j]->palavra) == 0){
				flag = 1;
			}
		}
		if(!flag){
			lista3[(*cont3)] = lista1[i];
			(*cont3)++;
		}
		flag = 0;
	}

	for (int j = 0; j < cont2; ++j){
		lista3[(*cont3)] = lista2[j];
		(*cont3)++;
	}
}

//Aloca uma matriz quadrada de inteiros de tamanho 'size';
int** alocaMatrix(int size){
	int** matriz = malloc(sizeof(int*) * size);
	for (int i = 0; i < size; ++i){
		matriz[i] = malloc(sizeof(int) * size);
	}
	return matriz;	
}

//Imprime uma matriz quadrada de inteiros de tamanho 'size';
void printMatrix(int** m, int size){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//Libera uma matriz quadrada de inteiros de tamanho 'size';
void liberaMatrix(int** m, int size){
	for (int i = 0; i < size; ++i){
		free(m[i]);
	}
	free(m);
}

//Libera um vetor de palavras de tamanho 'size';
void liberaPalavra(Palavra** p, int size){
	for (int i = 0; i < size; ++i){
		free(p[i]);
	}
	free(p);
}


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
	int** matriz1 = alocaMatrix(cont3);
	int** matriz2 = alocaMatrix(cont3);
	
	//Zera as matrizes
	for (int i = 0; i < cont3; ++i){
		for (int j = 0; j < cont3; ++j){
			matriz1[i][j] = 0;
			matriz2[i][j] = 0;
		}
	}

	//Armazenam as conexões entre palavras nas matrizes de adjacência
	//A matriz 1 representa as arestas do grafo formado pelo texto contido no vetor lista 1
	//A matriz 2 representa as arestas do grafo formado pelo texto contido no vetor lista 2
	for (int i = 0; i < cont1 - 1; ++i){
		matriz1[getWordPosition(lista3,lista1[i]->palavra,cont3)][getWordPosition(lista3,lista1[i+1]->palavra,cont3)] = 1;
	}
	for (int i = 0; i < cont2 - 1; ++i){
		matriz2[getWordPosition(lista3,lista2[i]->palavra,cont3)][getWordPosition(lista3,lista2[i+1]->palavra,cont3)] = 1;
	}

	//Imprime as matrizes
	printf("Matriz1: \n");
	printMatrix(matriz1, cont3);

	printf("Matriz2: \n");
	printMatrix(matriz2, cont3);


	//Algoritmo do coeficiente de similaridade de Jaccard
	int andSum = 0;
	int orSum = 0;
	for (int i = 0; i < cont3; ++i){
		for (int j = 0; j < cont3; ++j){
			if(matriz1[i][j] < matriz2[i][j]){
				andSum += matriz1[i][j];
				orSum += matriz2[i][j];
			}
			else{
				andSum += matriz2[i][j];
				orSum += matriz1[i][j];
			}
		}
	}


	printf("\nsimilaridade: %f \n",(float)andSum/(float)orSum);
}