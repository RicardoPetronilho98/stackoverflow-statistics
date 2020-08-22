/*
Pretende obter o top N utilizadores com maior número de posts de sempre. 
Para isto, devem ser considerados tanto perguntas quanto respostas dadas 
pelo respectivo utilizador;
*/

#include <stdio.h>
#include <stdlib.h>
#include <date.h>
#include <interface.h>
#include <pair.h>
#include <string.h>

/*
void teste(long cnt, long top_value, long id, int N, TAD_ARRAY_LIST ids_users, TAD_ARRAY_LIST tops, int flag){
  if(flag){
    printf("ANTES:");
  }else{ 
    printf("DEPOIS:");
  }
  printf(" cnt=%ld || top_value=%ld || id=%ld\n", cnt, top_value, id);
  printf("tops\n");
  for(int h = 0; h < N; h++){
    printf("%ld ", *(long*) getElem(tops, h));
  }
  printf("\n");
  printf("ids_users\n");
  
  for(int h = 0; h < N; h++){
    printf("%ld ", *(long*) getElem(ids_users, h));
  }
  printf("\n");
}*/

int main(void){
	
	TAD_community com = init();

  	com = load(com, "../../../ubuntu/");

    printf("load() feito\n"); getchar();

	int N = 100, i;

	LONG_list list = top_most_active(com, N);

	for(i = 0; i < N; i++){
		printf("%ld\n", get_list(list,i));
	}
	//printGlobalStruct(com);

  printf("querry feita\n"); getchar();

	com = clean(com);
	
	return 0;
}