/*
Dado um intervalo de tempo arbitrário, retornar todas as perguntas contendo uma 
determinada tag. O retorno da função deverá ser uma lista com os IDs das 
perguntas ordenadas em cronologia inversa;
*/

#include <stdio.h>
#include <stdlib.h>
#include <date.h>
#include <interface.h>
#include <pair.h>
#include <string.h>

int main(void){ 

    /*
    char **buf, *buf1 = "<google-play-store><paid-apps>";

    buf = strToTags(buf1);

    for(int i = 0; i < 2; i++){
        printf("%s\n", buf[i]);
    }*/

    TAD_community com = init();

  	com = load(com, "../../../ubuntu/");

  	Date begin = createDate(1,3,2013);   //  deu erro na begin= 1 1 2014     //  funciona bem para 1 1 2010

  	Date end = createDate(31,3,2013);     // deu erro na end= 3 1 2015        //  funciona bem para 3 1 2015

  	LONG_list list;

  	list = questions_with_tag(com, "package-management",begin, end);

    printf("DEPOIS DA QUERRY!\n");getchar();

    //free(begin);

    //free(end);

    //free_globalStruct(com);

    //getchar();

	
	return 0;

}