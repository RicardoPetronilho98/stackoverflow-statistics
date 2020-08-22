#include <stdio.h>
#include <stdlib.h>

#include <post.h>

int main(void){
	
	TAD_POST post = Post(1, 2, 3, "titulo", "mamas", "2010-09-13T19:16:26.763", 4, 5, 6);

	char* str = post2string(post);
	printf("%s\n", str);
	free(str);

	free_Post(post);

	printf("1\n"); getchar();

	return 0;
}