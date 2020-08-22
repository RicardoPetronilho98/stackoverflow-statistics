#ifndef STDFUNCTIONS_H
#define STDFUNCTIONS_H

/**
@file stdfunctions.h
Módulo que contém funções úteis sem relação contextual com qualquer módulo.
*/

/**\brief tamanho de um KB em Bytes*/
#define KB                     1024
/**\brief tamanho de um MB em Bytes*/
#define MB                1024 * KB

char* arrayLong2string(long* arr, int N);
int insert(long reps[], long user_ids[], long rep, long user_id, int N, int flag);
void printArrayLong(long arr[], int N);
void printArrayInt(int arr[], int N);
char** strToTags(char *tags);
int elem(long arr[], int N, long elem);


#endif