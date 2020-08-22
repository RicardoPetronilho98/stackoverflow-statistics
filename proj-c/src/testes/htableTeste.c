#include <stdio.h>
#include <stdlib.h>

#include "../../include/htable.h"
#include "../../include/post.h"
#include "../../include/real_user.h"


int main(){

	TAD_HTABLE htable = Htable(2);

	TAD_REAL_USER user1 = Real_User();
	setUser(user1, 11, "Jesus Cristo", "I love Satan!", 20, 3);

	TAD_REAL_USER user2 = Real_User();
	setUser(user2, 21, "Lucifer", "I love God", 3, 20);

	add((void*) user1, 1, htable);

	//getchar();

	add((void*) user2, 2, htable);

	//getchar();

	char *str = htable2string(htable, 'u');
	printf("%s" , str );
	free(str);
	printf("\ntaxa de ocupacao = %0.2f\n\n", usedPercentage(htable));
	
	getchar();

	free_htable(htable);
}
