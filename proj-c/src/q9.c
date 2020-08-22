#include <stdio.h>
#include <stdlib.h>
#include <date.h>
#include <pair.h>
#include <string.h>
#include <htable.h>
#include <user.h>
#include <arrayList.h>
#include <stdfunctions.h>
#include <list.h>
#include <globalstruct.h>
#include <real_user.h>
#include <quickSortDates.h>

static void filterMatch(TAD_ARRAY_LIST posts_user1, TAD_ARRAY_LIST posts_user2, TAD_HTABLE users, TAD_HTABLE posts, long *perguntas, long *soma_datas, int N, int *cnt);

/**
@file q9.c
Módulo que contém a funçõe LONG_list both_participated(TAD_community com, long id1, long id2, int N).
*/

/**\brief Devolve a lista com os IDS das N perguntas onde dois utilizadores participaram, via pergunta ou resposta.
@param com - estrutura de dados que guarda toda a informação
@param id1 - ID do utilizador 1
@param id2 - ID do utilizador 2
@param N - número de perguntas onde participaram os utilizadores
@return retorna a lista com os IDS das N perguntas onde dois utilizadores participaram
*/

LONG_list both_participated(TAD_community com, long id1, long id2, int N){ 
    if(N <= 0) return NULL;
    TAD_HTABLE users = getUsers(com);TAD_HTABLE posts = getPosts(com);
    TAD_REAL_USER user1 = getDados(users, id1);TAD_REAL_USER user2 = getDados(users, id2);
    LONG_list res;
    int i, size1, size2, cnt = 0;
    long *perguntas, *soma_datas;

    perguntas = malloc(N*sizeof(long));soma_datas = malloc(N*sizeof(long));

    if (user1 == NULL || user2 == NULL)return NULL;

    TAD_ARRAY_LIST posts_user1 = getArrayList(user1); TAD_ARRAY_LIST posts_user2 = getArrayList(user2);

    if(posts_user1 == NULL || posts_user2 == NULL)return NULL;

    for(i = 0; i < N; i++){
      soma_datas[i] = -3;
      perguntas[i] = -3;
    }
  
    size1 = getArraySize(posts_user1); size2 = getArraySize(posts_user2);

    /*
    **IMPORTANTE** 
    a função filterMatch é aplicada primeiramente aos posts_user1 fazendo match aos posts_user2,
    e depois faz-se o contrário, ou seja, ou seja, match dos posts_user2 aos posts_user1
    */ 
    filterMatch(posts_user1, posts_user2, users, posts, perguntas, soma_datas, N, &cnt);
    filterMatch(posts_user2, posts_user1, users, posts, perguntas, soma_datas, N, &cnt);
    
    res = create_list(cnt);
    
    for(i = 0; i < cnt; i++)
        set_list(res, i, perguntas[i]);

    free(soma_datas);
    free(perguntas);
    return res;
}

/*
    Nesta função percorre-se os posts do utilizador 1, caso estes sejam perguntas, 
percorre-se as respostas do utlizador 2, comparando-se o id da pergunta - parent_id - 
associada a cada respota, com o id da pergunta do utlizador 1. Caso o post do utlizador 1 seja 
uma resposta, compara-se o id da pergunta - parent_id - associada com o id de todas as 
respostas do utlizador 2. 
    Realiza-se este procedimento para o utlizador 2. Quando existe uma 
situação de compartilha de posts entre ambos os utilizadores, ou seja, uma pergunta onde os mesmos
interagem através de respostas, ou respostas feitas por um dos utilizadores face à pergunta do outro,
o id dessa pergunta adicionada de forma ordenada por cronologia inversa.
*/

static void filterMatch(TAD_ARRAY_LIST posts_user1, TAD_ARRAY_LIST posts_user2, TAD_HTABLE users, TAD_HTABLE posts, long *perguntas, long *soma_datas, int N, int *cnt){
    long i, j, post_id1, post_id2, parent_id1, parent_id2, soma;
    TAD_POST post1, post2, post_aux;
    int tipo1, tipo2;

    Date data;

    for(i = 0; i < getArraySize(posts_user1); i++){
        post_id1 = * (long*) getElem(posts_user1, i);
        post1 = (TAD_POST) getDados(posts, post_id1);
        if(post1 != NULL){  // verifica-se se existe post
            tipo1 = getTipo(post1);
            
            for(j = 0; j < getArraySize(posts_user2); j++){
            
                post_id2 = * (long*) getElem(posts_user2, j);
                post2 = (TAD_POST) getDados(posts, post_id2);
                if(post2 != NULL){  // verifica-se se existe post
                    tipo2 = getTipo(post2);
                    if(tipo1 == 1 && tipo2 == 2){   // caso de questão do user 1 e resposta do user 2
                        parent_id2 = getParentId(post2);
                        if(post_id1 == parent_id2){ // se o parent id da resposta do user 2 for igual ao id da questão do user 1 adiciona-se
                            data = getPostData(post1);  // data do post
                            soma = getDateSum(data);    // a soma da data é utilizada para ordenar por cronologia inversa
                            if(insert(soma_datas,perguntas, soma, post_id1, N, 0))(*cnt)++; // insere ordenadamente por cronologia inversa, usando o parâmetro soma
                            break;
                        }
                    }else{
                        if(tipo1 == 2 && tipo2 == 2){   // caso de resposta do user 1 e resposta do user 2
                            parent_id1 = getParentId(post1);
                            parent_id2 = getParentId(post2);
                            if(parent_id1 == parent_id2){   // verifica-se se os parent_ids são os mesmos, ou seja, se respondem à mesma pergunta, em caso afirmativo, adiciona-se
                                post_aux = (TAD_POST) getDados(posts, parent_id1);
                                data = getPostData(post_aux);   // data do post
                                soma = getDateSum(data);    // a soma da data é utilizada para ordenar por cronologia inversa
                                if(insert(soma_datas,perguntas, soma, parent_id1, N, 0))(*cnt)++; // insere ordenadamente por cronologia inversa, usando o parâmetro soma
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}