#include <string.h>
#include <stdio.h>

#include <arrayList.h>
#include <globalstruct.h>
#include <htable.h>
#include <quickSortDates.h>
#include <real_user.h>
#include <user.h>
#include <interface.h>
#include <assert.h>

/** capacidade inicial do ArrayList que contém os id's dos posts*/
#define ARRAY_LIST_DIM_INICIAL				256


/**
@file q8.c
Módulo que contém a funçõe LONG_list contains_word(TAD_community com, char* word, int N).
*/

/**
\brief Dado uma palavra e N numero de posts, retorna N id's de posts que contenham a palvra, ordenados por cronologia inversa.
@param com - estrutura global
@param word - palavra a procurar
@param N - número de posts
@return Retorna a informação através da estrutura LONG_list
*/
LONG_list contains_word(TAD_community com, char* word, int N){

	TAD_ARRAY_LIST list = ARRAY_LIST(ARRAY_LIST_DIM_INICIAL);
	TAD_HTABLE posts = getPosts(com);
	int count = 0, listSize;
	long i, *postId, tmp, *elem;
    TAD_POST post;
	char* titulo;

	assert(list && posts); // esta condição tem de ser válida

	for(i = 0; i < getHtableSize(posts); i++){

		if ( (post = (TAD_POST) getDadosAtIndex(posts, i)) == NULL || getTipo(post) != 1 || (titulo = getTitulo(post)) == NULL || strstr(titulo, word) == NULL) continue;

		tmp = getIdAtIndex(posts, i); // id do post
		postId = malloc(sizeof(long));
		memcpy(postId, &tmp, sizeof(long));
		addElem(list, postId); // adicionar o postId ao array
		count++;
	}

	int size = getArraySize(list);	
	long postsId[size];
    for(i = 0; i < size; i++) postsId[i] = * (long*) getElem(list, i);
	
	for (int i = 0; i < getArraySize(list); i++){
        elem = (long*) getElem (list, i);
        if (elem){
        	free(elem);
        	elem = NULL;
        }
    }
	free_ARRAY_LIST(list);
	
	sort_posts_by_inverted_cronology(postsId, size, posts);

	if (count < N) listSize = count;
	else listSize = N;

	LONG_list res = create_list(listSize);
	for(i = 0; i < listSize; i++) set_list(res, i, postsId[i]);
	
	return res;
}