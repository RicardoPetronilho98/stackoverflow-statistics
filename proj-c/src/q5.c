#include <string.h>

#include <arrayList.h>
#include <globalstruct.h>
#include <htable.h>
#include <quickSortDates.h>
#include <real_user.h>
#include <user.h>
#include <interface.h>
#include <assert.h>

/**
@file q5.c
Módulo que contém a funçõe USER get_user_info(TAD_community com, long id).
*/

/**
\brief Dado um id de um utilizador e a estrutura global, retorna a sua biografia e os ultimos 10 posts ordenados por cronologia inversa.
@param com - estrutura global
@param id - id do utilizador
@return Retorna a informação através da estrutura USER
*/
USER get_user_info(TAD_community com, long id){	

	TAD_HTABLE users = getUsers(com);
	TAD_HTABLE posts = getPosts(com);
	TAD_ARRAY_LIST list;
	TAD_REAL_USER user;

	assert(users && posts); // esta condição tem de ser válida
	if ( (user = (TAD_REAL_USER) getDados(users, id)) == NULL || (list = getArrayList(user)) == NULL ) return NULL; // não existe o user || user não tem posts
	
	int size = getArraySize(list), i;
    long postsId[size], post_history[10];
    for(i = 0; i < size; i++) postsId[i] = * (long*) getElem(list, i);
	
	sort_posts_by_inverted_cronology(postsId, size, posts);
	memcpy(post_history, postsId, sizeof(post_history));

	return create_user(getBio(user), post_history);
}