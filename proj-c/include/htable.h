#ifndef HTABLE_H
#define HTABLE_H

/**
@file htable.h
Módulo que contém as funções de criação, manipulação e destruição de uma Tabela de Hash.
*/

/**\brief Cria a modularidade para a estrutura TCD_HTABLE*/
typedef struct TCD_HTABLE* TAD_HTABLE;

/* Construtor */
TAD_HTABLE Htable(long dim); 


/* Getters */
long indexOf(long id, TAD_HTABLE htable);  
float usedPercentage(TAD_HTABLE htable); 
void* getDados(TAD_HTABLE htable, long id); 
void* getDadosAtIndex(TAD_HTABLE htable, long index);
long getHtableSize(TAD_HTABLE htable);
long getIdAtIndex(TAD_HTABLE htable, long index);

/* Setters */
void add(void* dados, long id, TAD_HTABLE htable); 
void set(void* dados, long index, TAD_HTABLE htable); 

/* free */
void free_htable(TAD_HTABLE htable);


//  ----- PARA DEBUGGING -------------------------------------------------------

char* htable2string(TAD_HTABLE htable, char type); 

#endif