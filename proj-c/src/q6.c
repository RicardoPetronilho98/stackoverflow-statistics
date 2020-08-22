#include <string.h>
#include <stdio.h>

#include <arrayList.h>
#include <globalstruct.h>
#include <htable.h>
#include <quickSortDates.h>
#include <real_user.h>
#include <user.h>
#include <interface.h>

/**
@file q6.c
Módulo que contém a funçõe LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end).
*/

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){

  TAD_DATAS datas = getDatas(com);
  TAD_HTABLE posts = getPosts(com);
  TAD_ARRAY_LIST postsArray;
  TAD_ITERATOR it = datasIterator(datas, begin, end);
  long lista[N];
  int lista2[N];
  long postId;
  int i,quantidade,indice,indiceMax;
  i = 0;
  while( itHasNext(it)){ 
   postsArray = itNext(datas, it);
   indiceMax = getArraySize( postsArray);
   indice = 0;
   // percorre todos os posts de 1 dia
   for(;indice < indiceMax;indice++){
     postId = getPostIdFromPost((TAD_POST_DATAS) getElem(postsArray,indice));
     // só passam respostas (tipo 2)
     if(getTipo(getDados(posts,postId)) == 2){
      quantidade = getScore(getDados(posts,postId));
      // se a lista não estiver cheia preenche
      if(i<N){
       lista[i] = postId;
       lista2[i] = quantidade;
       i++;
      }// se a lista estiver cheia ve se deve adicionar ou não
      else{
       if(quantidade > lista2[i-1]){
         lista[i-1] = postId;
         lista2[i-1] = quantidade;
       }
      }
      sortEnd_lists(lista,lista2,quantidade,postId,i-1);
     }
   }
  }
  free_Iterator(it);
  LONG_list l = create_list(i);
  while(i>0){
    i--;
    set_list(l,i,lista[i]);
  }
  
   return l;
}
