#ifndef DATAS_H
#define DATAS_H

/**
@file datas.h
Módulo que contém as funções de criação, manipulação e destruição da estrutura DATAS.
*/

/**\brief Cria a modularidade para a estrutura TCD_DATAS*/
typedef struct TCD_DATAS* TAD_DATAS;
/**\brief Cria a modularidade para a estrutura TCD_ITERATOR*/
typedef struct TCD_ITERATOR* TAD_ITERATOR;
/**\brief Cria a modularidade para a estrutura TCD_PPOST*/
typedef struct TCD_PPOST *TAD_POST_DATAS;

#include <date.h>
#include <arrayList.h>

//	construtores e destrutores:
TAD_DATAS Datas(int primeiro_ano, int anos); // Cria a tabela de datas

//	gets e sets:
void setPostDatas(TAD_DATAS datas, Date data, long user_id, long post_id);
int getOcupados(TAD_DATAS datas, Date data);
int getPrimeiroAno(TAD_DATAS datas);
int getNAnos(TAD_DATAS datas);
int getOurYear(void);
long getUserIdFromPost(TAD_POST_DATAS post);
long getPostIdFromPost(TAD_POST_DATAS post);

//	toString() para debug:
char* datas2string(TAD_DATAS datas);

//	free:
void freeDatas(TAD_DATAS datas);

//	iterator:
int itHasNext(TAD_ITERATOR it);
TAD_ARRAY_LIST itNext(TAD_DATAS datas, TAD_ITERATOR it);
TAD_ITERATOR datasIterator(TAD_DATAS datas, Date begin, Date end);
void free_Iterator(TAD_ITERATOR it);


#endif