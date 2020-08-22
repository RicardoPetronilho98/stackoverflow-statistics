#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arrayList.h>
#include <globalstruct.h>
#include <htable.h>
#include <quickSortDates.h>
#include <real_user.h>
#include <user.h>
#include <interface.h>
#include <list.h>
#include <stdfunctions.h>

/**
@file q2.c
Módulo que contém a funçõe LONG_list top_most_active(TAD_community com, int N).
*/

/**\brief Função que obtém o top N utilizadores com maior número de posts(perguntas e respostas)
de sempre.
@param com - estrutura de dados que guarda toda a informação
@param N - Número de utilizadores para o top
@return Lista com os top N utilizadores com maior número de posts*/

LONG_list top_most_active(TAD_community com, int N){
    if(N <= 0) return NULL; // em caso de N <= 0, evita-se correr a função desnecessáriamente
    TAD_HTABLE users = getUsers(com), posts = getPosts(com);
    TAD_ARRAY_LIST posts_user;
    TAD_REAL_USER user;
    TAD_POST post;
    LONG_list list = create_list(N);
    int tipo;
    long i, j,post_id, user_id, cnt = 0, numb_users, *ids_users, *tops, size = 0;
    numb_users = getHtableSize(users);
    ids_users = malloc(N*sizeof(long));tops = malloc(N*sizeof(long));

    for(i = 0;i < N;i++)tops[i] = 0;  // incializa-se o tops com valor -3, para não influenciar as comparações feitas pela função insert()

    for(i = 0;i < numb_users;i++){
        user = getDadosAtIndex(users, i);   //  vai buscar os dados do user no indice i
        user_id = getIdAtIndex(users, i);   //  vai buscar o user_id  
        cnt = 0;    
        if(user != NULL){
            posts_user = getArrayList(user);
            if(posts_user != NULL){
                for(j = 0;j < getArraySize(posts_user); j++){
                    post_id = * (long*) getElem(posts_user, j); // obtém-se o post_id
                    post = (TAD_POST) getDados(posts, post_id); // obtém-se a informação do post para saber o seu tipo
                    tipo = getTipo(post);
                    if(tipo == 1 || tipo == 2)cnt++;    //  contador de posts (perguntas e respostas)
                }
                if(insert(tops, ids_users, cnt, user_id, N, 0))size++;    //  faz inserção ordenada pelo contador (cnt)
            }  
        }
    }


    if(size > N) size = N;  //  em caso de o número de elementos ser menor que N, vamos inserir no list apenas o número de elementos

    for(i = 0; i < size; i++)set_list(list, i, ids_users[i]);

    free(ids_users);free(tops);
    return list;
}
