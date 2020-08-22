/* 
Dados os IDs de dois utilizadores, devolver as últimas N perguntas (cronologia inversa) 
em que participaram dois utilizadores específicos. Note que os utilizadores podem ter 
participado via pergunta ou respostas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <date.h>
#include <interface.h>
#include <pair.h>
#include <string.h>

#define CAP_MIN 15

int main(){

	TAD_community com = init();

  	com = load(com, "../../../ubuntu/");

	LONG_list list;

	int N = 5;

	list = both_participated(com, 87, 5691, N);

	getchar();

	return 0;
}
