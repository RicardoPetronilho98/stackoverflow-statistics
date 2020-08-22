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
@file q10.c
Módulo que contém a funçõe long better_answer(TAD_community com, long id).
*/

/**
\brief Dado um id de uma pergunta retorna o id da melhor resposta.
@param com - estrutura global
@param id - id da pergunta
@return Retorna o id da melhor resposta
*/
long better_answer(TAD_community com, long id){

	TAD_HTABLE posts = getPosts(com);
	TAD_HTABLE users = getUsers(com);
	TAD_POST post = (TAD_POST) getDados(posts, id);
	long max = -1, media = -1, resId = -1, i;
	int Scr, Rep, Vot, Comt;
	TAD_REAL_USER user;

	assert(posts && users); // esta condição tem de ser válida

	if ( post == NULL || getTipo(post) != 1) return -1; // não existe pergunta com esse ID ou não é uma pergunta 

	for(i = 0; i < getHtableSize(posts); i++){

		if ( (post = getDadosAtIndex (posts, i)) == NULL || getTipo(post) != 2 || getParentId(post) != id) continue; // não é uma resposta á pergunta

		user = (TAD_REAL_USER) getDados ( users, getUserId(post) );

		Scr = getScore(post);
		Rep = getReputacao(user);
		Vot = contavotos(user);
		Comt = getCommentCount(post);
		
		media = Scr * 0.45 + Rep * 0.25 + Vot * 0.2 + Comt * 0.1;
		
		if (media > max){
			resId = getIdAtIndex(posts, i);
			max = media;
		}
	}
	
	return resId;
}