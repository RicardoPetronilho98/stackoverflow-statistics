#ifndef TAG_H
#define TAG_H

/**
@file tags.h
Módulo que contém as funções de criação, manipulação e destruição de uma tag.
*/

/**\brief Cria a modularidade para a estrutura TCD_TAG*/
typedef struct TCD_TAG* TAD_TAG;


/* Construtor */
TAD_TAG createTag(int id,char* tagName); // cria uma tag

/* Setters */
void setTagName(TAD_TAG tag, char* nome);

/* Getters */
char* getTagName(TAD_TAG tag);  // devolve o nome da tag
int getTagId(TAD_TAG tag);      // devolve o id da tag
char* tag2string(TAD_TAG tag);  // devolve as informações da tag como uma string

/* free */
void freeTag(TAD_TAG tag); // liberta o espaço de memória ocupado pela tag



#endif