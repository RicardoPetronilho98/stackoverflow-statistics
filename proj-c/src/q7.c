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
@file q7.c
Módulo que contém a funçõe LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end).
*/

/**\ Devolve uma LONG_list com os IDs dos N posts com mais respostas
@param com - estrutura com todos os dados
@param N - nº de id's maximo pretendido
@param begin - data de inicio da procura
@param end - data de fim da procura
@return LONG_list com as id's dos posts com mais respostas 
*/

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){

  TAD_DATAS datas = getDatas(com);
  TAD_HTABLE posts = getPosts(com);
  TAD_ARRAY_LIST postsArray;
  TAD_POST post;
  TAD_ITERATOR it = datasIterator(datas, begin, end);
  int i,indice,indiceMax;
  int answerCount;
  long postId;
  long userId;
  long lista[N+1];
  long lista3[N+1];
  int lista2[N+1];
  i = 0;
  while(itHasNext(it)){
    // array de posts do dia em questão
    postsArray = itNext(datas, it);
    indiceMax = getArraySize(postsArray);
    indice = 0;
    // a percorrer todos os posts de um dia individualmente
    for(;indice<indiceMax;indice++){
      postId = getPostIdFromPost(getElem(postsArray, indice));
      post = getDados(posts,postId);
      // só as perguntas têm resposta
      if(getTipo(post) == 1){
        answerCount = getAnswerCount(post);
        userId = getUserId(post);
        // se a lista não estiver cheia
        if(i<N+1){
          // lista de IDs de posts
          lista[i] = postId;
          // lista de respostas
          lista2[i] = answerCount;
          // lista de Ids de users
          lista3[i] = userId;
          i++; // alterar nº de posições ocupadas
        } // se a lista estiver ocupada
        else{
          if(answerCount >= lista2[N]){
            lista[N] = postId;
            lista2[N] = answerCount;
            lista3[N] = userId;
          }
        }
        sortArrays_byUsersId(lista,lista2,lista3,i-1);
      }
    }
  }
  LONG_list l = create_list(i);
  while(i>0){
    i--;
    set_list(l,i,lista[i]);
  }
  free_Iterator(it);

  return l;
}
