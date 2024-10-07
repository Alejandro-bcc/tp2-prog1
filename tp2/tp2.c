/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1,
 * pelo aluno Alejandro David Nava Nava.
 * GRR 20242778.
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* Imprime um vetor de racionais  */
void imprime_vetor_r(struct racional vetor[], int n){

    int i;

    for (i=0; i<n; i++){
        imprime_r(vetor[i]);
        printf(" ");
    }
    printf("\b\n");

}

/* Elimina todos os elementos invalidos de um vetor de racionais  */
/* Ou seja, aqueles cujo denominador eh zero  */
void elimina_invalidos(struct racional vetor[], int *n){

    int i;

    i = 0;
    while (i < *n){
        if (!valido_r(vetor[i])){
			vetor[i] = vetor[*n-1];
            *n-=1;

        } else {
            i++;
        }
    }
}

/* Ordena todos os elementos de um vetor de racionais de maneira crescente */
/* Utiliza o algoritmo de bubble sort  */
void ordena_vetor(struct racional v[], int n){

	struct racional aux;
	int i, j;

	for(i = n-1; i > 0; i--){
		for(j = 0; j < i; j++){
			if(compara_r(v[j+1], v[j])){
				aux = v[j+1];
				v[j+1] = v[j];
				v[j] = aux;
			}
		}
	}
}

/* Soma os elementos de um vetor de racionais */
void soma_vetor(struct racional vetor[], int n, struct racional *soma){

	int i;
	(*soma).num = 0;
	(*soma).den = 1;
	for(i = 0; i < n; i++){
		soma_r(*soma, vetor[i], soma);
	}

}

/* programa principal */
int main (){

	struct racional vetor[100];
	struct racional soma;
	int n, i;

	scanf("%d",&n);
	
	for (i=0; i<n; i++){
		scanf("%ld", &vetor[i].num);
		scanf("%ld", &vetor[i].den);
	}
	
	printf("VETOR = ");
	imprime_vetor_r(vetor, n);

	elimina_invalidos(vetor, &n);
	printf("VETOR = ");
	imprime_vetor_r(vetor, n);
								
	ordena_vetor(vetor, n);
	printf("VETOR = ");
	imprime_vetor_r(vetor, n);

	soma_vetor(vetor, n, &soma);
	printf("SOMA = ");
	imprime_r(soma);
	printf("\n");

	return (0) ;
}
