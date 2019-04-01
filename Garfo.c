#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct PALAVRA Palavra;

struct PALAVRA{
	char palavra[20];
	char tipo[5];
};


Palavra* Parser3(char* word){
	Palavra* p = malloc(sizeof(Palavra));
	int i = 0;
	for(i; word[i] != '/';i++){
		p->palavra[i] = word[i];
	}
	p->palavra[i] = '\0';
	return p;
}

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
			//printf("%s\n",aux);
		}
		fscanf(fp,"%s", &aux);
	}
	*contador = count;
	return vetor;
}

int getWordPosition(Palavra** lista, char* word,int count){
	for (int i = 0; i < count; ++i){
		if(strcmp(lista[i]->palavra, word) == 0){
			return i;
		}
	}
	printf("erro erro deu erro socorro\n");
}


int main(){
	FILE* fp = fopen("input1", "r");
	int cont1 = 0;
	int cont2 = 0;
	int cont3 = 0;

	Palavra** lista1 = Parser(fp, &cont1);
	fclose(fp);
	fp = fopen("input2", "r");
	Palavra** lista2 = Parser(fp, &cont2);
	
	printf("Palavras lidas do primeiro arquivo: %d palavras\n", cont1);
	for(int i = 0; i < cont1; i++){
		printf("%s %s\n", lista1[i]->palavra,lista1[i]->tipo);
	}
	printf("Palavras lidas do segundo arquivo: %d palavras\n", cont2);
	for(int i = 0; i < cont2; i++){
		printf("%s %s\n", lista2[i]->palavra,lista2[i]->tipo);
	}

	Palavra** lista3 = malloc((cont1+cont2) * sizeof(Palavra*));

	int flag = 0;
	for (int i = 0; i < cont1; ++i){
		for (int j = 0; j < cont2; ++j){
			if(strcmp(lista1[i]->palavra,lista2[j]->palavra) == 0){
				flag = 1;
			}
		}
		if(!flag){
			lista3[cont3] = lista1[i];
			cont3++;
		}
		flag = 0;
	}


	for (int j = 0; j < cont2; ++j){
		lista3[cont3] = lista2[j];
		cont3++;
	}
	printf("Todas as palavras lidas, sem repeticoes: %d palavras\n", cont3);
	for(int i = 0; i < cont3; i++){
		printf("%s %s\n", lista3[i]->palavra,lista3[i]->tipo);
	}

	int** matriz1 = malloc(sizeof(int*) * cont3);
	for (int i = 0; i < cont3; ++i){ matriz1[i] = malloc(sizeof(int) * cont3);}

	int** matriz2 = malloc(sizeof(int*) * cont3);
	for (int i = 0; i < cont3; ++i){ matriz2[i] = malloc(sizeof(int) * cont3);}
	
	for (int i = 0; i < cont3; ++i){
		for (int j = 0; j < cont3; ++j){
			matriz1[i][j] = 0;
			matriz2[i][j] = 0;
		}
	}

	for (int i = 0; i < cont1 - 1; ++i){
		matriz1[getWordPosition(lista3,lista1[i]->palavra,cont3)][getWordPosition(lista3,lista1[i+1]->palavra,cont3)] = 1;
	}
	for (int i = 0; i < cont2 - 1; ++i){
		matriz2[getWordPosition(lista3,lista2[i]->palavra,cont3)][getWordPosition(lista3,lista2[i+1]->palavra,cont3)] = 1;
	}
	printf("\nmatriz1: \n");
	for (int i = 0; i < cont3; ++i){
		for (int j = 0; j < cont3; ++j){
			printf("%d ",matriz1[i][j]);
		}
		printf("\n");
	}
	printf("matriz2: \n");
	for (int i = 0; i < cont3; ++i){
		for (int j = 0; j < cont3; ++j){
			printf("%d ",matriz2[i][j]);
		}
		printf("\n");
	}


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


	fclose(fp);
}