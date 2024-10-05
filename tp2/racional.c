/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/
/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador){

    struct racional r;
	r.num = numerador;
	r.den = denominador;
    return r;
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r (struct racional r){

	if (r.den == 0)
        return 0;
    else
        return 1;
}

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max){

    return rand() % (max - min + 1) + min;
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b){

	long resto;

    while (b != 0){
    	resto = a % b;
		a = b;
        b = resto;
       }
    return labs(a); /* retorna o valor absoluto de a */
}                 

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b){
	
	return (a * b) / mdc(a, b);
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r){

	if (valido_r(r)){
	    long MDC;

        MDC = mdc(r.num, r.den);

		if (MDC != 1){			/* se MDC = 1, ja esta simplficado! */
			r.num = r.num / MDC;
            r.den = r.den / MDC;
		}

        if (r.den < 0){			/* arruma o sinal, se necesario */
            r.num = r.num * -1;             
			r.den = r.den * -1;
        }
    }
    return r;
}

/* Retorna um número racional aleatório na forma simplificada.
 * Deve ser sorteado o numerador e depois o denominador.
 * o racional gerado pode ser válido ou inválido.
 * O numerador e o denominador devem ser inteiros entre min e max. */
struct racional sorteia_r (long min, long max){

    long numerador, denominador;
    struct racional sorteado;

    numerador = aleat(min, max);
	denominador = aleat(min, max);

    sorteado = cria_r(numerador, denominador);
    sorteado = simplifica_r(sorteado);

    return sorteado;
}

/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, imprime a mensagem "NaN" (Not a Number);
     - se o numerador for 0, imprime somente "0";
     - se o denominador for 1, imprime somente o numerador;
     - se o numerador e denominador forem iguais, imprime somente "1";
     - se o racional for negativo, o sinal "-" vem antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r (struct racional r){

    if (valido_r(r)){

		r = simplifica_r(r);

		if (r.num == 0){
			printf("0");
		} else if (r.den == 1){
			printf("%ld", r.num);
		} else if (r.num == r.den){
			printf("1");
		} else {
			printf("%ld/%ld", r.num, r.den);
		}
    } else {
        printf("NaN");
    }
}

/* Compara dois racionais r1 e r2. Retorno: -2 se r1 ou r2 for inválido,
 * -1 se r1 < r2, 0 se r1 = r2 ou 1 se r1 > r2 */
int compara_r (struct racional r1, struct racional r2){

	if (valido_r(r1) && valido_r(r2)){

		r1 = simplifica_r(r1); /* os racionais sao simplicados para */
		r2 = simplifica_r(r2); /* evitar erros na comparacao */

		if (r1.num * r2.den < r2.num * r1.den)
			return 1;
		else 
			return 0;

	} else {
		return -2;
	}
}

/* Retorna a soma dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int soma_r (struct racional r1, struct racional r2, struct racional *r3){

		if (!valido_r(r1) || !valido_r(r2) || r3 == NULL){
		return 0;

	} else {
		long MMC;
	
		MMC = mmc(r1.den, r2.den);
		(*r3).den = MMC;
		(*r3).num = (MMC / r1.den) * r1.num + (MMC / r2.den) * r2.num;

		return 1;
	}

}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int subtrai_r (struct racional r1, struct racional r2, struct racional *r3){

	if (!valido_r(r1) || !valido_r(r2) || r3 == NULL){
		return 0;

	} else {
		long MMC;
	
		MMC = mmc(r1.den, r2.den);
		(*r3).den = MMC;
		(*r3).num = (MMC / r1.den) * r1.num - (MMC / r2.den) * r2.num;

		return 1;
	}
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int multiplica_r (struct racional r1, struct racional r2, struct racional *r3){

	if(!valido_r(r1) || !valido_r(r2) || r3 == NULL){
		return 0;

	} else {

		(*r3).num = r1.num * r2.num;
		(*r3).den = r1.den * r2.den;
		return 1;
	}

}

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int divide_r (struct racional r1, struct racional r2, struct racional *r3){

	if(!valido_r(r1) || !valido_r(r2) || r3 == NULL || r2.num == 0){
		return 0;

	} else {

		(*r3).num = r1.num * r2.den;
		(*r3).den = r1.den * r2.num;
		return 1;
	}
}

