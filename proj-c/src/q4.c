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
@file q4.c
Módulo que contém a funçõe LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end).
*/

/**\brief Dado um intervalo de tempo arbitrário, a função retorna uma lista com os posts identificados com a respectiva tag, esta lista está ordenada por cronologia inversa.
@param com - estrutura de dados que guarda toda a informação
@param tag - tag que vai ser procurada nos posts
@param begin - data inicial
@param end - data final
@return retorna uma lista, com todos os posts onde a tag dada como argumento está presente 
*/

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    int tipo, i;
    long post_id, n, size = 0, *elem;
    char *tmp_tag, **tagsStr, *aux = NULL;
    
    TAD_DATAS datas = getDatas(com);
    TAD_HTABLE posts = getPosts(com);
    TAD_POST post;
    TAD_POST_DATAS post_datas;
    LONG_list lista_perguntas;
    TAD_ARRAY_LIST lista_posts, perguntas = ARRAY_LIST(15);

    TAD_ITERATOR it = datasIterator(datas,begin,end);

    while(itHasNext(it)){
        lista_posts = itNext(datas, it);

        if(lista_posts != NULL){

            for(n = 0; n < getArraySize(lista_posts) ; n++){
                
                post_datas = getElem(lista_posts, n);
                
                if(post_datas != NULL){
                
                    post_id = getPostIdFromPost(post_datas);
                    post = getDados(posts, post_id);
                    
                    if(post != NULL){    // verifica-se a existência de post
                        tipo = getTipo(post);
                        
                        if(tipo == 1){  //  se for pergunta, assumindo que só existem tags em perguntas
                            tmp_tag = getTagsFromPost(post);
                            aux = malloc( (strlen(tmp_tag) + 1 ) * sizeof(char));   // faz-se uma cópia da tmp_tag, para não se perder informação, visto que depois é feito um free
                            memcpy(aux, tmp_tag, strlen(tmp_tag)+1);
                            tagsStr = strToTags(aux);   // separa as tags numa lista de strings
                            
                            for(i = 0; tagsStr[i]; i++){
                                
                                if(strcmp(tagsStr[i], tag) == 0){   // verifica-se se a tag é igual à recebida como argumento
                                    elem = malloc(sizeof(long));    // em caso afirmativo adiciona-se ao arraylist, mas por cronologia não inversa
                                    memcpy(elem, &post_id, sizeof(long));
                                    addElem(perguntas, elem);
                                }
                            }
                            free(tagsStr);  // liberta-se ponteiros, para que não sejam perdidos (leaks)
                            free(aux);
                        }
                    }
                }
            }
        }
    }

    if(perguntas == NULL)return NULL; // verifica-se se foram adicionadas perguntas com tags igual à dada como argumento

    size = getArraySize(perguntas);

    lista_perguntas = create_list(size);
  
    for(n = 0; n < size; n++)  // colocar por cronologia inversa, basta reverter o array, logo aproveitou-se para fazer isso quando estamos a copiar para o LONG_list
        set_list(lista_perguntas, size -1 - n, * (long*) getElem(perguntas, n));

    for (int i = 0; i < getArraySize(perguntas); i++){  // liberta-se a memória utilizada anteriormente para adicionar elementos ao arraylist
        elem = (long*) getElem (perguntas, i);
        if (elem) free(elem);
    }

    free_ARRAY_LIST(perguntas); // liberta-se memória utilizada apenas nesta questão

    free_Iterator(it);  // liberta-se a memória utilizada pelo iterator

    return lista_perguntas;
}

