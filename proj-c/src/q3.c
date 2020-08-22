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

/**
@file q3.c
Módulo que contém a funçõe LONG_pair total_posts(TAD_community com, Date begin, Date end).
*/

/**\brief Dado um intervalo de tempo arbitrário, a função retorna um par com o número total de 
posts (identificando perguntas e respostas separadamente) neste período;
@param com - estrutura de dados que guarda toda a informação
@param begin - data inicial
@param end - data final
@return retorna um par, onde o primeiro elemento é o número de perguntas e o segundo o número de respostas
*/

LONG_pair total_posts(TAD_community com, Date begin, Date end){
    int tipo, n;
    long post_id, num_perguntas = 0, num_respostas = 0;

    TAD_DATAS datas = getDatas(com);TAD_HTABLE posts = getPosts(com);
    TAD_POST post;
    TAD_POST_DATAS post_datas;
    LONG_pair par = create_long_pair(0,0);  // fst = número de perguntas e snd = número de respostas;
    TAD_ARRAY_LIST lista_posts;
    TAD_ITERATOR it = datasIterator(datas,begin,end);

    while(itHasNext(it)){
        lista_posts = itNext(datas,it);
        
        for(n = 0; n < getArraySize(lista_posts); n++){ // percorre-se os posts de cada dia, no intervalo dado
            post_datas = getElem(lista_posts, n);
            if(post_datas != NULL){
                post_id = getPostIdFromPost(post_datas);   // obtém-se o post_id
                post = getDados(posts, post_id);    // a informação do post para saber o tipo deste
                tipo = getTipo(post);
                
                if(tipo == 1){  // caso seja pergunta
                    num_perguntas++;    // contador de perguntas
                }else{
                    if(tipo == 2){  // caso seja resposta
                        num_respostas++;    // contador de respostas
                    }
                }
            }
        }
    }

    set_fst_long(par, num_perguntas);set_snd_long(par, num_respostas);
    free_Iterator(it);

    return par;
}