/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1,
 * pelo aluno Alejandro David Nava Nava.
 * GRR 20242778.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
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
    printf("\n");

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

/* intercala dois subvetores ordenados  */
/* auxilia na execucao do algoritmo de ordenacao que utiliza o Merge Sort  */
void intercala(struct racional v[], struct racional v_aux[], int a, int m, int n){

	int i, j, k;
	i = a;
	j = m + 1;
	printf("i: %d\nj: %d\n", i, j);

	for(k=0; k<=n; k++){
		if (j > n || (i <= m && compara_r(v[i], v[j]))){
			v_aux[k] = v[i];
			i++;
		} else {
			v_aux[k] = v[j];
			j++;
		}
	}
	
}

/* sobrescreve o conteudo de v2 em v1  */
void sobrescreve_vetor(struct racional v1[], struct racional v2[], int n){

	int i;
	for(i=0; i<n; i++){
		v1[i] = v2[i];
	}
}
/* ordena um vetor de racionais de maneira crescente  */
/* utiliza o algoritmo de ordenacao Merge Sort  */
void ordena_vetor(struct racional v[], struct racional v_aux[], int a, int n){

	int m;

	if(a < n){
		m = (a + n)/2;
		ordena_vetor(v, v_aux, a, m);
		ordena_vetor(v, v_aux, m+1, n);
		intercala(v, v_aux, a, m, n);
	}
}

/* programa principal */
int main (){

	struct racional vetor[100];
	struct racional v_aux[100];

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

	ordena_vetor(vetor, v_aux, 0, n-1);
	printf("VETOR = ");
	imprime_vetor_r(v_aux, n);

	return (0) ;
}
