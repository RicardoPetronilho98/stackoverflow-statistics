#include <stdio.h>
#include <stdlib.h>

#include <htable.h>
#include <datas.h>
#include <globalstruct.h>
#include <post.h>
#include <real_user.h>
#include <tags.h>
#include <date.h>


/**
@file globalstruct.c
Módulo que contém as funções de criação, manipulação e destruição da estrutura global.
*/

/**\brief capacidade inicial da Tabela de Hash que contem os posts*/
#define POSTS_DIM_INICIAL       25000 // 25 mil

/**\brief capacidade inicial da Tabela de Hash que contem os utilizadores*/
#define USERS_DIM_INICIAL      100000 // 100 mil

/**\brief capacidade inicial do ArrayList que contem as tags*/
#define TAGS_DIM_INICIAL          600

/**\brief primeiro ano da base de dados*/
#define PRIMEIRO_ANO             2008

/**\brief primeiro ano da base de dados*/
#define ULTIMO_ANO               2018


/**\brief Estrutura global que contem as sub-estruturas com informação de posts, utilizadores, tags e datas*/
typedef struct TCD_community{

  /**\brief Tabela de Hash que contem os posts*/
  TAD_HTABLE posts;  
  /**\brief Tabela de Hash que contem os utilizadores*/
  TAD_HTABLE users;  
  /**\brief ArrayList que contem as tags*/
  TAD_ARRAY_LIST tags;  
  /**\brief Estrutura que contem as datas*/
  TAD_DATAS datas;

} TCD_community;


/**
\brief Cria a estrutura global.
@return retorna a estrutura
*/
TAD_community GlobalStruct(){ // cria estrutura global que contem as hash tables de users e posts

    TAD_community gs = malloc(sizeof(TCD_community));

    int n_anos =  ULTIMO_ANO - PRIMEIRO_ANO;
    
    gs->users = Htable(USERS_DIM_INICIAL);
    gs->posts = Htable(POSTS_DIM_INICIAL);
    gs->tags = ARRAY_LIST(TAGS_DIM_INICIAL);
    gs->datas = Datas(PRIMEIRO_ANO, n_anos);  //  estes defines são temporários para testes;

    return gs;
}

/**
\brief Retorna a Tabela de Hash que contem a informação dos utilizadores.
@param gs - estrutura global
@return retorna a Tabela de Hash
*/
TAD_HTABLE getUsers (TAD_community gs){

  return gs->users;
}

/**
\brief Retorna a Tabela de Hash que contem a informação dos posts.
@param gs - estrutura global
@return retorna a Tabela de Hash
*/
TAD_HTABLE getPosts (TAD_community gs){

  return gs->posts;
}

/**
\brief Retorna o ArrayList que contem a informação das Tags.
@param gs - estrutura global
@return retorna o ArrayList
*/
TAD_ARRAY_LIST getTags (TAD_community gs){

  return gs->tags;
}

/**
\brief Retorna a estutura que contem a informação das Datas.
@param gs - estrutura global
@return retorna a estrutura
*/
TAD_DATAS getDatas (TAD_community gs){

  return gs->datas;
}

/**
\brief Adiciona um post á Tabela de Hash que contem os posts.
@param id - ID do post
@param post - post
@param gs - estrutura global
*/
void addPost(int id, TAD_POST post, TAD_community gs){

  add( (void*) post, id, gs->posts);
}

/**
\brief Adiciona um utilizador á Tabela de Hash que contem os utilizadores.
@param id - ID do utilizador
@param user - utilizador
@param gs - estrutura global
*/
void addUser(int id, TAD_REAL_USER user, TAD_community gs){

  add( (void*) user, id, gs->users);
}

/**
\brief Adiciona uma tag ao ArrayList que contem as tags.
@param tag - tag
@param gs - estrutura global
*/
void addTag(TAD_TAG tag, TAD_community gs){
  // vou adicionar tag gs
  addElem(gs->tags, (void*) tag);
}

void addVote(int vote,int postId, TAD_community gs){
    TAD_POST post = getDados(gs->posts,postId);
    if(post != NULL){
      addVoteToPost(vote,post);
    }
}

/**
\brief Adiciona um ID de um post e o ID do utlizador que criou o respetivo post á estrutura que contem a informação das Datas.
@param data - uma data especificada
@param user_id - ID do utilizador que criou o post
@param post_id - ID do post
@param gs - estrutura global
*/
void addDatas(Date data, int user_id, int post_id, TAD_community gs){

  int dia = get_day(data);
  int mes = get_month(data);
  int ano = get_year(data);
  
  if(ano >= getPrimeiroAno(gs->datas) && (ano <= getPrimeiroAno(gs->datas) + getNAnos(gs->datas)) && mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31){
    
    setPostDatas(gs->datas, data, user_id, post_id);
  }

  else{
    perror("data inválida: addDatas() no módulo GLOBALSTRUCT");
    exit(1);
  }
}

/**
\brief Adiciona um post ao respetivo utilizador que o criou.
@param data - uma data especificada
@param user_id - ID do utilizador que criou o post
@param post_id - ID do post
@param gs - estrutura global
*/
void atualiza_User_Posts(int user_id, int post_id, TAD_community gs){

  TAD_REAL_USER user = (TAD_REAL_USER) getDados(gs->users, user_id);
  addPost2User(user, post_id);
}




static void free_htable_posts(TAD_HTABLE posts){

    if (posts){

        long i;
        TAD_POST post;

        for (i = 0; i < getHtableSize(posts); i++){
            post = (TAD_POST) getDadosAtIndex(posts, i);
            free_Post(post);
        }

        free_htable(posts);
    }
}




static void free_htable_users(TAD_HTABLE users){

    if (users){

        long i;
        TAD_REAL_USER user;

        for (i = 0; i < getHtableSize(users); i++){
            user = (TAD_REAL_USER) getDadosAtIndex(users, i);
            free_Real_User(user);
        }

        free_htable(users);
    }
}




static void free_ARRAY_LIST_tags(TAD_ARRAY_LIST tags){

    if (tags){

        for (int i = 0; i < getArraySize(tags); i++){
            TAD_TAG elem = (TAD_TAG) getElem (tags, i);
            if (elem) freeTag(elem);
        }

        free_ARRAY_LIST(tags);
    }
}




/**
\brief Liberta a zona de memória alocada para a estrutura global.
@param gs - estrutura global
*/
void free_globalStruct(TAD_community gs){

  if (gs){

    free_htable_posts(gs->posts);
    free_htable_users(gs->users);
    free_ARRAY_LIST_tags(gs->tags);
    freeDatas(gs->datas);

    free(gs);
    gs = NULL;
  }
}


/**
\brief Retorna o fator de ocupação da Tabela de Hash que contem os posts.
@param gs - estrutura global
@return Retorna o fator
*/
float usedPercentagePosts(TAD_community gs){

  return usedPercentage(gs->posts);
}

/**
\brief Retorna o fator de ocupação da Tabela de Hash que contem os utilizadores.
@param gs - estrutura global
@return Retorna o fator
*/
float usedPercentageUsers(TAD_community gs){

  return usedPercentage(gs->users);
}


//  ----- PARA DEBUGGING -------------------------------------------------------

/**
\brief Imprime no STD_OUT uma representação da Tabela de Hash.
@param gs - estrutura global
*/
void printGlobalStruct(TAD_community gs){

  int i;

  char* users = htable2string(gs->users, 'u');
  printf("\n%s", users );
  free(users);

  char* posts = htable2string(gs->posts, 'p');
  printf("\n%s", posts );
  free(posts);

  char* datas = datas2string(gs->datas);
  printf("\n\n%s", datas);
  free(datas);

  printf("\n\n");
  for(i = 0; i < getArraySize(gs->tags); i++){
     printf("%s\n", tag2string ((TAD_TAG) getElem (gs->tags, i)));
  }

}