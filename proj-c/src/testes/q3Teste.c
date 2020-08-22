/*
Dado um intervalo de tempo arbitrário, obter o número total de 
posts (identificando perguntas e respostas separadamente) neste período;
*/
#include <stdio.h>
#include <stdlib.h>
#include <date.h>
#include <interface.h>
#include <pair.h>

int main(void){

	TAD_community com = init();

  	com = load(com, "../../../ubuntu/");

  	Date begin = createDate(1,1,2014);

  	Date end = createDate(31,12,2014);

  	LONG_pair par = total_posts(com, begin, end);

  	printf("perguntas = %ld || respostas = %ld\n", get_fst_long(par), get_snd_long(par));

  	getchar();

	return 0;
}