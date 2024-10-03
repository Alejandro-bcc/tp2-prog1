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

/* coloque aqui as funções auxiliares que precisar neste arquivo */

/* programa principal */
int main (){

	struct racional vetor[100];
	struct racional *ptr = vetor;
	int n, i;

	scanf("%d",&n);
	
	for (i=0; i<n; i++){
		scanf("%ld", &vetor[i].num);
		scanf("%ld", &vetor[i].den);
	}
	
	printf("VETOR = ");
	imprime_vetor(ptr, n);

	/*elimina_invalidos(ptr, n);*/

	return (0) ;
}
