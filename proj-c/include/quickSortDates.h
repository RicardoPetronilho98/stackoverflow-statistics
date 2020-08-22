#ifndef QUICKSORTDATES_H
#define QUICKSORTDATES_H

#include <stdlib.h>
#include <htable.h>
#include <arrayList.h>
#include <tags.h>
#include <date.h>
#include <post.h>
#include <list.h>

/**
@file quickSortDates.h
Módulo que contém as funções de ordenação de dados diversos.
*/


// Ordena um array - que contém os ids dos posts - por cronologia inversa (RECENTE -> ANTIGO)
void sort_posts_by_inverted_cronology(long ids[], int size, TAD_HTABLE h);
void swapInList(int quantidade, long postId, LONG_list lista, int* lista_quantidade, int indice);
void sortEnd(LONG_list lista, int* lista_quantidade, int quantidade, long postId, int indice);
void swap_longs(int quantidade, long id, long* lista, int* lista_quantidade, int indice);
void sortEnd_lists(long* lista, int* lista_quantidade, int quantidade, long id, int max);
void swapInArray(long* lista,int* lista_quantidade, long* lista_users_ids, int indice);
void sortArrays_byUsersId(long* lista, int* lista_quantidade, long* lista_users_ids,int indice);
void swapArrayList(TAD_ARRAY_LIST lista,TAD_ARRAY_LIST lista_quantidade, TAD_ARRAY_LIST lista_ids, int indice);
void sortEnd_lists_byId(TAD_ARRAY_LIST lista, TAD_ARRAY_LIST lista_quantidade,TAD_ARRAY_LIST lista_ids,int pos);
void sortByPos(TAD_ARRAY_LIST lista_tags,TAD_ARRAY_LIST lista_NTags,int ocupados);
void swapInList(int quantidade, long postId, LONG_list lista, int* lista_quantidade, int indice);
long getDateSum(Date d);

#endif