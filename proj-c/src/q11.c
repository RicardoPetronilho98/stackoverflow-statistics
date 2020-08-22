#include <string.h>
#include <stdio.h>

#include <arrayList.h>
#include <globalstruct.h>
#include <htable.h>
#include <quickSortDates.h>
#include <real_user.h>
#include <user.h>
#include <interface.h>
#include <stdfunctions.h>

/**
@file q11.c
Módulo que contém a funçõe LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end).
*/

/**\verifica se se trata da mesma tag
@param tag1 - tag a comparar
@param tag2 - tag a comparar
*/
int mystrcmp(char* tag1, char* tag2){
  int i,x;
  if(tag1 == NULL || tag2 == NULL) return 0;
  x = strlen(tag1);
  // não consegue contar o length
  if(x != strlen(tag2)) return 0;
  else{
    for(i=0;i<x && *(tag1+i) == *(tag2+i);i++);
    if(i == x){
      return 1;
    }
  }
  return 0;
}


/**\procura na estrutura de dados das tags a tag pretendida pelo nome
@param tags - estrutura de dados sequêncial que guarda o nome das tags
@ e a correspondente identificação
@param nome - nome da tag a procurar na estrutura de dados
*/
int searchTagId(TAD_ARRAY_LIST list, char* nome){
  int i,max = getArraySize(list);
  char* tagName;
  TAD_TAG tag;
  for(i=0;i<max;i++){
     tag = (TAD_TAG) getElem(list,i);
     tagName = getTagName(tag);
     if(mystrcmp(tagName,nome)){
      return (long)getTagId(tag);
     }
  }
  return -1;
}

/**\ coleta os ids correspondentes as tags
@param list - lista onde serão guardadas as IDs correspondentes as tags
@ mais usadas
@param lista_tags - lista a preencher com os nomes das tags mais usadas
@param tag_original - estrutura de dados sequêncial que guarda o nome das tags
@ e a correspondente identificação
@param lista_ids - lista para armazanar ids das tags
@param tagsStruct - estrutura das tags
*/

void insereTag(TAD_ARRAY_LIST lista_tags, TAD_ARRAY_LIST lista_NTags,char* tag_original, TAD_ARRAY_LIST lista_ids, TAD_ARRAY_LIST tagsStruct){

  int pos,max;
  int* aux;
  long* id;
  char* tag;
  max = getArraySize(lista_tags);
  // percorre o arrayList das tags já registadas
  for(pos = 0;pos < max;pos++){
      // se encontrar uma tag igual incremento o contador
      if(mystrcmp(tag_original,(char*)getElem(lista_tags,pos))){
        aux = (int*) getElem(lista_NTags,pos);
        *aux = *aux + 1;
        break;
      }
    }
  // a tag nova é incrementada e o contador inicializado
  if(pos == max){
    tag = malloc(sizeof(char) * (strlen(tag_original)+1));
    memcpy(tag,tag_original,strlen(tag_original)+1);
    aux = malloc(sizeof(int));
    *(aux) = 1;
    id = malloc(sizeof(long));
    *id = searchTagId(tagsStruct,tag);
    addElem(lista_tags,tag);
    addElem(lista_NTags,aux);
    addElem(lista_ids,id);
  }
  sortEnd_lists_byId(lista_tags,lista_NTags,lista_ids,pos);
}



/**\verifica se uma tag ja se encontra listada incrementando o seu contador
@ ou lista-a no fim da lista e coloca o seu contador a 1
@param tags_original - string contendo todas as tags de uma questão ou resposta
@param lista_tags - lista a preencher com os nomes das tags mais usadas
@param lista_NTags - lista com os contadores das tags presentes na lista_tags
@param lista_ids - lista para armazanar ids das tags
@param tagsStruct - estrutura das tags
*/
void most_used_Tags(char* tags, TAD_ARRAY_LIST lista_tags, TAD_ARRAY_LIST lista_NTags, TAD_ARRAY_LIST lista_ids, TAD_ARRAY_LIST tagsStruct){
  
  //se chamar mais vezes a q11 garanto que as tags permanecem numa string unica
  char* tag;
  int indice,indice2;
  indice = indice2 = 0;
  // criação de apontadores, individualização das tags com \0 e inserção no contador
  for(;*(tags+indice) != '\0';indice2 = 0,indice++){
    if(*(tags+indice) == '<'){
      while(*(tags+indice+indice2) != '>') indice2++;
      tag = malloc(sizeof(char) * indice2);
      memcpy(tag,tags+indice+1,indice2);
      *(tag+indice2-1) = '\0';
      insereTag(lista_tags,lista_NTags,tag,lista_ids,tagsStruct);
      free(tag);
    }
  }
}

/**\verifica se o post foi realizado entre as datas dadas
@param post_date - data de criação do post em questão
@param begin - data do inicio da procura
@param end - data do fim da procura
@return true (1) ou false(0)
*/
int onTime(Date post_date, Date begin, Date end){
  if(getDateSum(begin) > getDateSum(post_date) || getDateSum(post_date) > getDateSum(end)) return 0;
  return 1;
}

/**\coleta as N tags mais usadas pelos utilizadores previamente recolhidos
@param user - estrutura que guarda a informação de um utilizador específico
@param posts - estrutura de dados de procura por ids de posts
@param lista_tags - lista a preencher com os nomes das tags mais usadas
@param lista_NTags - lista com os contadores das tags presentes na lista_tags
@param lista_ids - lista para armazanar ids das tags
@param tagsStruct - estrutura das tags
@param begin - data de inicio da procura
@param end - data de fim da procura
*/
void coleta_tag(TAD_REAL_USER user, TAD_HTABLE posts, TAD_ARRAY_LIST lista_tags, TAD_ARRAY_LIST lista_NTags, TAD_ARRAY_LIST lista_ids, TAD_ARRAY_LIST tagsStruct, Date begin, Date end){

  TAD_ARRAY_LIST list = getArrayList(user);
  int tamanho = getArraySize(list);
  int i;
  TAD_POST post;
  char* tags;
  // cada iteração representa o tratamento de um post feito pelo user
  for(i=0;i<tamanho;i++){
    long *elem = (long*) getElem(list,i);
    post = getDados(posts,*elem);
    // apenas passam posts feitos dentro do intervalo de tempo,têm de ser perguntas !!!
    if(!onTime(getPostData(post),begin,end) || getTipo(post) != 1) continue;
    tags = getTagsFromPost(post);
    most_used_Tags(tags,lista_tags,lista_NTags,lista_ids,tagsStruct);
  }
}

/**\ verifica se um utilizador ja foi contabilizado no array
@param lista_users - lista com os ids dos users colectados até á data 
@param userId - novo userId a ser adicionado á coleção caso 
@ não se encontre já nesta
@return true(1) ou false(0)
*/

int pertence(long* lista_users,long userId, int indice){
  for(;indice>=0;indice--){
    if(lista_users[indice] == userId) return 1;
  }
  return 0;
}

/**\coleciona os N utilizadores com melhor reputação que fizeram posts entre
@ as datas pretendidas
@param lista_users - lista de utilizadores a preencher
@param datas - estrutura de dados de procura por datas
@param users - estrutura de dados de procura por ids de utiizadores
@param begin - data de inicio da procura
@param end - data de fim da procura
@param N - nº de IDs das tags pretendidos
@return o número de utilizadores diferentes que fizeram posts nessa data,
@ que tenham melhor reputação
*/

int coleta_users(long* lista_users, TAD_DATAS datas, TAD_HTABLE users, Date begin, Date end, int N){

  TAD_ITERATOR it = datasIterator(datas,begin,end);
  if(it == NULL) return 0;
  TAD_ARRAY_LIST usersArray;
  int lista2[N];
  int indice,indiceMax, indice_usersArray;
  long userId;
  int reputacao;
  indice = 0;
  int contador = 0;
  // percorre todos os users entre as datas dadas
  while(itHasNext(it)){
    contador++;
    // array com todos os users que publicaram num dia
    usersArray = itNext(datas,it);
    indiceMax = getArraySize(usersArray);
    indice_usersArray = 0;
    // percorre usersArray
    while(indice_usersArray < indiceMax){
      userId = getUserIdFromPost( (TAD_POST_DATAS) getElem(usersArray,indice_usersArray));
      // se o user não tiver sido registado ainda será registado
      if(!pertence(lista_users,userId,indice)){
        reputacao = getReputacao((TAD_REAL_USER) getDados(users,userId));
        // se a lista não esta cheia
        if(indice < N){
          lista_users[indice] = userId;
          lista2[indice] = reputacao;
          sortEnd_lists(lista_users,lista2,reputacao,userId,indice);
          indice++;
        }// se a lista esta cheia
        else{
          if(lista2[indice-1] < reputacao){
            lista_users[indice-1] = userId;
            lista2[indice-1] = reputacao;
            sortEnd_lists(lista_users,lista2,reputacao,userId,indice-1);
          }
        }
      }
      indice_usersArray++;
    }
  }
  free_Iterator(it);
  return indice;
}

/**\faz o free das posições apontadas pelos apontadores do array lista
@param
@param
@param
*/

void freeListas(TAD_ARRAY_LIST lista_tags, TAD_ARRAY_LIST lista_NTags, TAD_ARRAY_LIST lista_ids){
   char* tag;
   int* quantidade;
   long* id;
   int indice = getArraySize(lista_tags)-1;
   for(;indice>=0;indice--){
    tag = getElem(lista_tags,indice);
    quantidade = getElem(lista_NTags,indice);
    id = getElem(lista_ids,indice);
    free(tag);
    free(quantidade);
    free(id);
   }
}


/**\devolver os ids das N tags mais usadas pelos N utilizadores com melhor
@ reputação. Em ordem decrescente do número de vezes em que a tag foi usada.
@param com - estrutura de dados que guarda toda a informação 
@param N - nº de IDs das tags pretendidos
@param begin - data de inicio da procura
@param end - data de fim da procura
@return LONG_list de IDs das tags mais usadas pelos N utilizadores
@ com melhor reputação, numa data específica, por ordem decrescente
@ de referências a tag
*/

LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
  
  long inicio = getDateSum(begin);
  long fim = getDateSum(end);
  TAD_DATAS datas = getDatas(com);
  TAD_HTABLE users = getUsers(com);
  TAD_HTABLE posts = getPosts(com);
  TAD_ARRAY_LIST tags = getTags(com);
  LONG_list list;
  if( inicio > fim ){
    list = create_list(0);
    return list;
  }
  long lista[N];
  // garante que a lista enche
  int i,j;
  // array de user mais famosos ( por reputação) a postar no intervalo
  int newTam = coleta_users(lista,datas,users,begin,end,N);
  TAD_ARRAY_LIST lista_tags = ARRAY_LIST(newTam);
  TAD_ARRAY_LIST lista_NTags = ARRAY_LIST(newTam);
  TAD_ARRAY_LIST lista_ids = ARRAY_LIST(newTam);
  // a cada ciclo aplica a coleta das tags de todos os posts de um user
  for(i=0;i < newTam;i++){ 
    if(getArrayList(getDados(users,lista[i])) == NULL) continue;
    coleta_tag(getDados(users,lista[i]),posts,lista_tags,lista_NTags,lista_ids,tags,begin,end);
  }
  i = getArraySize(lista_tags);
  if(N > i) list = create_list(i);
  else{
    list = create_list(N);
    i = N;
  } // preenche a lista de resposta com os ids
  for(j=0;j<i;j++){
    set_list(list,j,*(long*)getElem(lista_ids,j));
  }
  freeListas(lista_tags,lista_NTags,lista_ids);
  free_ARRAY_LIST(lista_NTags);
  free_ARRAY_LIST(lista_tags);
  free_ARRAY_LIST(lista_ids);
  return list;
}