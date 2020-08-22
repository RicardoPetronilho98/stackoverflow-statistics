#include <stdio.h>

#include <interface.h>
#include <testa_erro_defines.h>
#include <globalstruct.h>

//#define TESTA_ERRO_LOAD

int main(){
	
	TAD_community com;

	com = init();

	com = load(com, "../../../ubuntu/");
	//com = load(com, "../../../android/");
	
	#ifdef TESTA_ERRO_LOAD
	printGlobalStruct(com);
	printf( "\n\nposts = %0.2f", usedPercentagePosts(com) );
	printf( "\nusers = %0.2f", usedPercentageUsers(com) );
	#endif

	printf("antes do free()\n"); getchar();

	com = clean(com);

	printf("depois do free()\n"); getchar();

	return 0;
}