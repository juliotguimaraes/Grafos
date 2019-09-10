#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"


int main(int argc, char *argv[]){
    int instancias, nQ, nR, nD, K,i,j;

    //L� o arquivo de entrada
    FILE *entrada;
    entrada=fopen ("input.txt", "r");

    //Define o total de instancias (K)
    fscanf(entrada, "%i", &instancias);
    for(j = 0; j < instancias; j++){
    	fscanf(entrada, "%i %i %i %i", &nQ, &nR, &nD, &K);

    	TipoValorVertice V1;
    	TipoValorVertice V2;
    	TipoPeso Peso;
    	TipoGrafo grafo;
    	grafo.NumArestas = nR;
    	grafo.NumVertices = nQ;
    	FGVazio(&grafo);
    	for(i = 0; i < nR; i++){
    		fscanf(entrada, "%i %i %f", &V1, &V2, &Peso);
    		InsereAresta(&V1,&V2,&Peso,&grafo);
    		InsereAresta(&V2,&V1,&Peso,&grafo);
    	}

    	int delegacias[nD];
    	for(i = 0; i < nD; i++){
    		fscanf(entrada, "%i",&delegacias[i]);
    	}
    	int consultas;
    	fscanf(entrada, "%i", &consultas);
    	TipoValorVertice saida, chegada;
    	for(i = 0; i < consultas; i++){
    		fscanf(entrada, "%i %i", &saida, &chegada);
    	}
        Dijkstra(&grafo, &saida, &chegada);

    }
 return 0;
}
