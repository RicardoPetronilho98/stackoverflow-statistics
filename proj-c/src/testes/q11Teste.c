#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arrayList.h>
#include <datas.h>
#include <globalstruct.h>
#include <quickSortDates.h>
#include <interface.h>
#include <testa_erro_defines.h>
#include <list.h>
#include <date.h>

int main(){

  TAD_community com = GlobalStruct();

  //load(com, "../../../android/");
  load(com, "../../../ubuntu/");

  Date begin = createDate(1,11,2013);
  Date end = createDate(30,11,2013);

  //printGlobalStruct(com);


  LONG_list l;
  l = most_used_best_rep(com, 5, begin, end);

  if(l == NULL){
    printf("NÃO EXISTEM users\n");
  }
  free_globalStruct(com);
  return 0;
}


