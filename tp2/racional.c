/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo contem as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também foram definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

struct racional cria_r (long numerador, long denominador){

    struct racional r;
	r.num = numerador;
	r.den = denominador;
    return r;
}

int valido_r (struct racional r){

	if (r.den == 0)
        return 0;
    else
        return 1;
}

/* Retorna um numero aleatorio gerado entre min e max, inclusive  */
long aleat (long min, long max){

    return rand() % (max - min + 1) + min;
}

/* Calcula Máximo Divisor Comum entre a e b */
/* Utiliza o metodo de Euclides */
long mdc (long a, long b){

	long resto;

    while (b != 0){
    	resto = a % b;
		a = b;
        b = resto;
       }
    return labs(a); /* retorna o valor absoluto de a */
}                   /* para evitar modificar o sinal dos racionais  */

/* Calcula o Mínimo Múltiplo Comum entre a e b */
long mmc (long a, long b){
	
	return (a * b) / mdc(a, b);
}

/* Recebe um racional e o retorna na forma simplificada */
struct racional simplifica_r (struct racional r){

	long MDC;

	if (valido_r(r)){

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

struct racional sorteia_r (long min, long max){

    long numerador, denominador;
    struct racional sorteado;

    numerador = aleat(min, max);
	denominador = aleat(min, max);

    sorteado = cria_r(numerador, denominador);
    return simplifica_r(sorteado);
}

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

int multiplica_r (struct racional r1, struct racional r2, struct racional *r3){

	if(!valido_r(r1) || !valido_r(r2) || r3 == NULL){
		return 0;

	} else {

		(*r3).num = r1.num * r2.num;
		(*r3).den = r1.den * r2.den;
		return 1;
	}

}

int divide_r (struct racional r1, struct racional r2, struct racional *r3){

	/* o ultimo teste evita divisoes por zero */
	if(!valido_r(r1) || !valido_r(r2) || r3 == NULL || r2.num == 0){
		return 0;

	} else {

		(*r3).num = r1.num * r2.den;
		(*r3).den = r1.den * r2.num;
		return 1;
	}
}

