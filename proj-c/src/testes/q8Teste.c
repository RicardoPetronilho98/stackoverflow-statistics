/* Dado uma palavra, devolver uma lista com os IDs de N perguntas 
cujos tútulos a contenham, ordenados por cronologia inversa */

#include <interface.h>
#include <list.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

	TAD_community com = init();

	com = load(com, "../../../ubuntu/");

	LONG_list list = contains_word(com, "glib", 10);

	com = clean(com);

	for(int i = 0; i < 10; i++)
		if (list != NULL) printf("%ld - ", get_list(list, i));
	putchar('\n');

	free_list(list);

	printf("depois do free()\n"); getchar();

	return 0;
}