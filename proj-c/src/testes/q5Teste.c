/*
Dado um ID de utilizador, devolver a informação do seu perfil (short bio) 
e os IDs dos seus 10 últimos posts (perguntas ou res- postas), 
ordenados por cronologia inversa;
*/

#include <stdio.h>

#include <interface.h>
#include <user.h>
#include <stdfunctions.h>


void testa_q5(){

	TAD_community com = init();

	com = load(com, "../../../ubuntu/");

	USER u = get_user_info(com, 449);

	com = clean(com);

	// DEBUGGING:
	
	printf("\nbio = %s\n", get_bio(u) );
	
	long* posts = get_10_latest_posts(u);
	printf("post_history =");
	for (int i = 0; i < 10; i++)
		printf(" %ld", posts[i] );
	putchar('\n');
	
	free_user(u);

	printf("depois do free()\n"); getchar();

}

int main(){

	testa_q5();

	return 0;
}