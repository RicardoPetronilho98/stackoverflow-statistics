#ifndef REAL_USER_H
#define REAL_USER_H


/**
@file real_user.h
Módulo que contém as funções de criação, manipulação e destruição da estrutura que armazena informações de cada utilizador.
*/

/**\brief Cria a modularidade para a estrutura TCD_REAL_USER*/
typedef struct TCD_REAL_USER* TAD_REAL_USER;

#include <arrayList.h>

/* Construtor */
TAD_REAL_USER Real_User(void);

/* Setters */
void addPost2User(TAD_REAL_USER user, long id);
void setUser(TAD_REAL_USER user, int reputacao, char* nome, char* bio, int upvotes, int downvotes);

/* Getters */
char* user2string(TAD_REAL_USER user);
char* getName(TAD_REAL_USER user);
char* getBio(TAD_REAL_USER user);
int getReputacao(TAD_REAL_USER user);
TAD_ARRAY_LIST getArrayList(TAD_REAL_USER user);
int getUpvotes(TAD_REAL_USER user);
int getDownvotes(TAD_REAL_USER user);
int contavotos(TAD_REAL_USER user);

/* free */
void free_Real_User(TAD_REAL_USER user);

#endif