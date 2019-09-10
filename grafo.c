#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#define INFINITO 999999

void FGVazio(TipoGrafo *Grafo){
    short i, j;
    for(i = 0; i <= Grafo->NumVertices; i++){
        for(j = 0; j <= Grafo->NumVertices; j++)
            Grafo->Mat[i][j] = 0;
    }
}

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, TipoPeso *Peso, TipoGrafo *Grafo){
	Grafo->Mat[*V1][*V2] = *Peso;
}

bool ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo){
	TipoApontador Aux = 0;
	bool ListaVazia = true;
	while(Aux < Grafo->NumVertices && ListaVazia){
		if(Grafo->Mat[*Vertice][Aux] > 0)
			ListaVazia = false;
		else
			Aux++;
	}
	return (ListaVazia == true);

}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo){
	TipoValorVertice Result;
	TipoApontador Aux = 0;
	bool ListaVazia = true;
	while(Aux < Grafo->NumVertices && ListaVazia){
		if(Grafo->Mat[*Vertice][Aux] > 0){
			Result = Aux;
			ListaVazia = false;
		}else{
			Aux++;
		}
	}if(Aux == Grafo->NumVertices)
		printf("Erro: Lista adjacencia vazia");
	return Result;
}

void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo, TipoValorVertice *Adj, TipoPeso *Peso, TipoApontador *Prox, bool *FimListaAdj){
	*Adj = *Prox;
	*Peso = Grafo->Mat[*Vertice][*Prox];
	(*Prox)++;
	while(*Prox < Grafo->NumVertices && Grafo->Mat[*Vertice][*Prox] == 0)
		(*Prox)++;
	if(*Prox == Grafo->NumVertices)
		*FimListaAdj = true;
}

void ImprimeGrafo(TipoGrafo *Grafo){
	short i, j;
	printf("%s","    ");
	for(i = 1; i <= Grafo->NumVertices; i++){
		printf("%4d", i);
	}
	printf("\n");
	for(i = 1; i <= Grafo->NumVertices; i++){
		printf("%4d", i);
		for(j = 1; j <= Grafo->NumVertices; j++){
			printf("%4g", Grafo->Mat[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void RefazInd(TipoIndice Esq, TipoIndice Dir, TipoItem *A, TipoPeso *P, TipoValorVertice *Pos){
    TipoIndice i = Esq;
    int j = i * 2;
    TipoItem x = A[i];
    while(j <= Dir){
        if(j < Dir){
            if(P[A[j].Chave] > P[A[j+1].Chave]);
                j++;
        }
        if(P[x.Chave] <= P[A[j].Chave])
            break;
        A[i] = A[j];
        Pos[A[j].Chave] = i;
        i = j;
        j = i * 2;
    }
    A[i] = x;
    Pos[x.Chave] = i;
}
void Constroi(TipoItem *A, TipoPeso *P, TipoValorVertice *Pos, int n){
    TipoIndice Esq;
    Esq = n/2 + 1;
    while(Esq > 1){
        Esq--;
        RefazInd(Esq, n, A, P, Pos);
    }
}

TipoItem RetiraMinInd(TipoItem *A, TipoPeso *P, TipoValorVertice *Pos, int n){
    TipoItem Result;
    if(n < 1){
        printf("Erro: Heap Vázio");
        return Result;
    }
    Result = A[1];
    A[1] = A[n];
    Pos[A[n].Chave] = 1;
    n--;
    RefazInd(1, n, A, P, Pos);
    return Result;
}

void DiminuiChaveInd(TipoIndice i, TipoPeso ChaveNova, TipoItem *A, TipoPeso *P, TipoValorVertice *Pos){
    TipoItem x;
    if(ChaveNova > P[A[i].Chave]){
        //printf("Erro: Chave nova maior que Chave atual");
        return;
    }
    P[A[i].Chave] = ChaveNova;
    while(i > 1 && P[A[i/2].Chave] > P[A[i].Chave]){
        x = A[i/2];
        A[i/2] = A[i];
        Pos[A[i].Chave] = i/2;
        A[i] = x;
        Pos[x.Chave] = i;
        i /= 2;
    }
}

void Dijkstra(TipoGrafo *Grafo, TipoValorVertice *Raiz, TipoValorVertice *Destino){
    FILE *saida;
    saida=fopen ("output.txt", "w+");
    TipoPeso P[MAXNUMVERTICES + 1];
    TipoValorVertice Pos[MAXNUMVERTICES + 1];
    long Antecessor[MAXNUMVERTICES + 1];
    bool Itensheap[MAXNUMVERTICES + 1];
    TipoVetor A;
    TipoValorVertice u, v;
    TipoItem temp;
    for(u = 0; u <= Grafo->NumVertices; u++){
        Antecessor[u] = -1;
        P[u] = INFINITO;
        A[u+1].Chave = u;
        Itensheap[u] = true;
        Pos[u] = u+1;
    }
    int n;
    n = Grafo->NumVertices;
    P[*(Raiz)] = 0;
    Constroi(A, P, Pos, n);
    while(n >= 1){
        temp = RetiraMinInd(A,P,Pos, n);
        u = temp.Chave;
        Itensheap[u] = false;
        if(!ListaAdjVazia(&u, Grafo)){
            TipoApontador Aux;
            Aux = PrimeiroListaAdj(&u, Grafo);
            bool FimListaAdj = false;
            n--;
            TipoPeso Peso = Grafo->Mat[u][v];
            while(!FimListaAdj){
                ProxAdj(&u, Grafo, &v, &Peso, &Aux, &FimListaAdj);
                if(P[v] > (P[u] + Peso)){
                    P[v] = P[u] + Peso;
                    Antecessor[v] = u;
                    DiminuiChaveInd(Pos[v], P[v], A, P, Pos);
                    fprintf(saida, "%.2lf %d %d\n", P[v], Antecessor[v], v);
                }
            }
        }
    }
    fprintf(saida, "\n\n");
}
