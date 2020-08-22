/* Dado o ID de uma pergunta, obter a melhor resposta. Para isso, deverá usar a função 
de média ponderada abaixo:
(Scr × 0.45) + (Rep × 0.25) + (Vot × 0.2) + (Comt × 0.1)
*/

#include <stdio.h>
#include <interface.h>

int main(){

	TAD_community com = init();

	com = load(com, "../../../ubuntu/");
	
	long id = better_answer(com, 5942);

	com = clean(com);
	
	printf("id = %ld\n", id);
	
	printf("depois do free()\n"); getchar();

	return 0;
}