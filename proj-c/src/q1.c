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
@file q1.c
Módulo que contém a funçõe STR_pair info_from_post(TAD_community com, long id).
*/

/**\Função que procura o id de uma pergunta
@param com - estrutura de dados que guarda toda a informação 
@param id - id da pergunta sobre a qual queremos saber o id do user ou
@ resposta da qual queremos saber o id do user que fez a pergunta a qual
@ a resposta corresponde 
@return titulo e id de um user especifico 
*/

STR_pair info_from_post(TAD_community com, long id){ 
	
	STR_pair resposta;
	TAD_POST post = (TAD_POST) getDados(getPosts(com), id);
	if (post == NULL){
	 resposta = create_str_pair(NULL,NULL);
	 return resposta;
	}
	TAD_REAL_USER user = (TAD_REAL_USER) getDados(getUsers(com), getUserId(post));

	//Depois de ter os dados verificamos se se trata de uma pergunta ou uma resposta:
	//Tratando-se de uma pergunta basta-nos obter o nome do utilizador que a fez. 
   	if(getTipo(post) == 1){
		resposta = create_str_pair(getTitulo(post),getName(user)); // post.c-> getpergunta
	}
	
	// Tratando-se de uma resposta identificamos a pergunta correspondente 
	//e de seguida procuramos o nome de utilizador dessa mesma pergunta.
	else{
		int parent = getParentId(post);
		post = getDados(getPosts(com),parent);
		user = getDados(getUsers(com),getUserId(post));
		resposta = create_str_pair(getTitulo(post),getName(user));
	}
    
	return resposta;
}