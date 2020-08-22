#ifndef GLOBALSTRUCT_H
#define GLOBALSTRUCT_H

/**
@file globalstruct.h
Módulo que contém as funções de criação, manipulação e destruição da estrutura global.
*/

/**\brief Cria a modularidade para a estrutura TCD_community*/
typedef struct TCD_community* TAD_community;

#include "post.h"
#include "real_user.h"
#include "tags.h"
#include "datas.h"
#include "htable.h"

/* Construtor */
TAD_community GlobalStruct(void); // controi a estrutura global



/* Getters */
TAD_HTABLE getUsers (TAD_community gs);
TAD_HTABLE getPosts (TAD_community gs);
TAD_ARRAY_LIST getTags (TAD_community gs);
TAD_DATAS getDatas (TAD_community gs);



/* Setters */
void addPost(int id, TAD_POST post, TAD_community gs);
void addUser(int id, TAD_REAL_USER user, TAD_community gs);
void addTag(TAD_TAG tag, TAD_community gs);
void addVote(int vote,int postId, TAD_community gs);
void atualiza_User_Posts(int user_id, int post_id, TAD_community gs);
void addDatas(Date data, int user_id, int post_id, TAD_community gs);


/* free */
void free_globalStruct(TAD_community gs);




//  ----- PARA DEBUGGING -------------------------------------------------------

void printGlobalStruct(TAD_community gs); // imprime a Globalstruct
float usedPercentagePosts(TAD_community gs); 
float usedPercentageUsers(TAD_community gs);
//float usedPercentageTags(TAD_community gs); --> falta implementar


#endif