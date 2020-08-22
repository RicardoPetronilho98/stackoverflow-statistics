#include <list.h>
#include <interface.h>
#include <stdio.h>
/*
Dado um intervalo de tempo arbitrário, devolver os
IDs das N respostas com mais quantidade, em ordem decrescente do número de
quantidade; O número de quantidade deverá ser obtido pela diferença entre Up Votes
(UpMod) e Down Votes (DownMod).
*/

int main(){

	TAD_community com = init();

  //com = load(com, "../../../android/");
  com = load(com, "../../../ubuntu/");
  //printGlobalStruct(com);
  
  Date begin = createDate(1,11,2015);
  Date end = createDate(30,11,2015);

  LONG_list list = most_voted_answers(com, 5, begin, end);
  for(int i = 0; i < 5; i++)
    printf("%ld - ", get_list(list, i));
  getchar();
  com = clean(com);
	getchar();
	return 0;
}