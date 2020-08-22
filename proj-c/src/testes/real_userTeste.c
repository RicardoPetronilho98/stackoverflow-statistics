#include <stdio.h>
#include <stdlib.h>

#include <real_user.h>

int main(void){

	
	TAD_REAL_USER user = Real_User();

	setUser(user, 11, "Jesus Cristo", "I love Satan!", 20, 3);

	addPost2User(user, 1);
	addPost2User(user, 2);
	addPost2User(user, 3);
	
	char *str= user2string(user);
	printf("%s\n", str);
	free(str);
	
	free_Real_User(user);
	
	printf("getchar() on main() - 1\n"); getchar();
	
	return 0;
}