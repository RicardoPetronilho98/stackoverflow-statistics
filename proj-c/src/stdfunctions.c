#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdfunctions.h>

/**
@file stdfunctions.c
Módulo que contém funções úteis sem relação contextual com qualquer módulo.
*/


/**
\brief Retorna uma representação de um array de longs em formato String.
@param arr - array de longs
@param N - tamanho do array
@return Retorna a String
*/
char* arrayLong2string(long* arr, int N){

    if (arr == NULL || N <= 0) return "NULL";   //  array vazio;
    
    char* fstBuf = malloc(MB);
    char num[128];

    int i, k;

    for(k = 0, i = 0; i < N; i++){
        sprintf(num, "%ld", arr[i]);
        sprintf(fstBuf + k, "%s - ", num);
        k += strlen(fstBuf + k); 
        if ( k > MB ){
            perror("buffer insuficiente para conter a string: arrayLong2string() on module STDFUNCTIONS");
            exit(EXIT_FAILURE);
        }
    }
    
    k -= 3;

    int length = strlen(fstBuf) + 1;
    char* r = malloc(length);
    memcpy(r, fstBuf, length);

    free(fstBuf);

    return r;
}


/**
\brief Ordena o arr2 de forma decrescente, através do arr1 (controla a ordenação). Contém opções de controlo - flag.\n
flag = 1 - caso a ordenação tenha em conta elementos repetidos.\n
flag = 0 - caso a ordenação não tenha em conta elementos repetidos. 
@param arr1 - array1 de longs
@param arr2 - array2 de longs
@param elem1 - elemento 1
@param elem2 - elemento 2
@param N - tamanho do array
@param flag - flag de controlo
@return Retorna 1 caso tenha inserido, ou 0 caso não tenha.
*/
int insert(long arr1[], long arr2[], long elem1, long elem2, int N, int flag) {

    if (arr1[N-1] > elem1) return 0;
    if (flag == 0 && elem(arr2, N, elem2) == 1 ) return 0;

    int i;
    
    for(i = N-1; i > 0 && arr1[i-1] <= elem1; i--){
        arr1[i] = arr1[i-1]; 
        arr2[i] = arr2[i-1];
    }

    arr1[i] = elem1;
    arr2[i] = elem2;
    
    return 1;
}

/**
\brief Verifica se elem existe em arr.
@param arr - array de longs
@param N - tamanho do array
@param elem - elemento
@return Retorna 1 caso exista, ou 0 caso não exista.
*/
int elem(long arr[], int N, long elem){

    int i;

    for(i = 0; i < N; i++)
        if (arr[i] == elem)
            return 1;

    return 0;
}

/**
\brief Converte um array que contem várias tags em vários arrays com uma tag cada.
@param tags - array com várias tags
@return vários arrays com uma tag cada
*/
char** strToTags(char *tags){ // separa a string com todas as tags 

    int i, count = 1, v = 0;

    for(i = 0; tags[i]; i++) if (tags[i] == '>') count++; // contador do número de tags
  
    char **res = malloc(sizeof(char*) * count);
    res[v++] = tags + 1;
    res[count - 1] = (char*) NULL;
 
    for (i = 0; tags[i]; i++){
      if (tags[i] == '>'){
        tags[i] = '\0'; // sem esta linha cada apontador mostrava a string toda desde o inicio
        if (tags[i + 1] == '\0') break;
        res[v++] = tags + i + 2; 
      }
    }

    return res;
}