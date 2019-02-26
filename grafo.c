#include <stdio.h>
#include <stdlib.h>

typedef struct GRAFO Grafo;

struct GRAFO{
	char* nome;
	int flag;
	int nroarestas;
	int* arestaflag;
	Grafo** arestas;
};

void ContaVertice(Grafo* first, int* count){
	for (int i = 0; i < first->nroarestas; ++i){
		if(first->flag == 0){
			*count++;
			first->flag = 1;
			ContaVertice(first->arestas[i],count);
		}
	}
}

int ContaVerticeAux(Grafo* first){
	int* conta= malloc(sizeof(int));
	int aux;
	*conta = 0;
	ContaVertice(first, conta);
	aux = *conta;
	free(conta);
	return aux;	 
}


Grafo* criavertice(){
	Grafo* abc =  malloc(sizeof(Grafo));
	printf("digite o nome do vertice sem espaco\n");
	char* nome = malloc(sizeof(char)*40);
	scanf("%s", nome);
	abc->nome = nome;
	abc->flag = 0;
	abc->nroarestas = 0;
	abc->arestas = malloc(sizeof(Grafo*) * 10);
	abc->arestaflag = malloc(sizeof(int) * 10);
	for (int i = 0; i < 10; ++i){
		abc->arestaflag[i] = 0;
	}	
}

void ShowAllVertices(Grafo** raiz, int nrovert){
	for (int i = 0; i < nrovert; ++i){
		printf("%d %s\n",i , raiz[i]->nome);
	}
}

void ConnectVertices(Grafo* a, Grafo* b){
	a->arestas[a->nroarestas] = b;
	a->arestaflag[a->nroarestas] = 1;
	a->nroarestas++;

	b->arestas[b->nroarestas] = a;
	b->arestaflag[b->nroarestas] = 1;
	b->nroarestas++;	
}

void DisconnectVertices(Grafo* a, Grafo* b){
	
}

void Caminha(Grafo* a){
	int nro;
	printf("\n");
	printf("voce esta no %s\n", a->nome);
	printf("Para onde vc quer ir?\n");
	ShowAllVertices(a->arestas, a->nroarestas);
	scanf("%d", &nro);
	if(nro > a->nroarestas - 1){
		return;
	}
	else{
		Caminha(a->arestas[nro]);
	}
}

void ImprimeCaminhoEuleriano(Grafo** raiz, int nrovert,int totalarestas, int start){
	int aux, aux2;
	for (int i = 0; i < totalarestas; ++i){
		aux = rand()%(raiz[start]->nroarestas);
	
	}
}

int ExisteCaminhoEuleriano(Grafo** raiz, int nrovert){
	int nroimpares = 0;
	int totalarestas = 0;
	int impar = 0;
	for (int i = 0; i < nrovert; ++i){
		totalarestas += raiz[i]->nroarestas;
		if( raiz[i]->nroarestas % 2 == 1){
			nroimpares++;
			impar = i; 
		}
	}

	if(nroimpares != 2 && nroimpares != 0)
		ImprimeCaminhoEuleriano(raiz, nrovert, totalarestas/2, impar);
	else{
		return 0;
	}

}



int main(){
	Grafo** raiz;
	int nrovert = 0, controle, a, b;

	raiz = malloc(sizeof(Grafo*) * 50);
	printf("digite um numero, 0 sai, 1 cria, 2 junta, 3 mostra, 4 caminha\n");
	scanf("%d", &controle);
	while(controle != 0){
		if(controle == 1){
			raiz[nrovert] = criavertice(); 
			nrovert++;
		}
		else if(controle == 2){
			ShowAllVertices(raiz, nrovert);
			printf("Digite dois vertices para criar uma conexao entre eles\n");
			scanf("%d %d", &a, &b);
			ConnectVertices(raiz[a],raiz[b]);			
		}
		else if(controle == 3){
			ShowAllVertices(raiz, nrovert);
		}
		else if(controle == 4){
			ShowAllVertices(raiz, nrovert);
			printf("selecione um lugar para comecar\n");
			scanf("%d", &a);
			Caminha(raiz[a]);	
		}
		
		printf("digite um numero, 0 sai, 1 cria, 2 junta, 3 mostra, 4 caminha\n");
		scanf("%d", &controle);
	}

	for (int i = 0; i < 50; ++i){
		if(raiz[i] != NULL){
			free(raiz[i]);
		}
	}
	free(raiz);
}






