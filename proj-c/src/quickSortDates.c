#include <quickSortDates.h>
#include <stdio.h>

/**
@file quickSortDates.c
Módulo que contém as funções de ordenação de dados diversos.
*/

static void swap(long* a, long* b);
long getDateSum(Date d);

/**\brief devolve a soma de uma data num int
@param
*/
long getDateSum(Date d){

    int dia = get_day(d);
    int mes = get_month(d);
    int ano = get_year(d);

    return (ano * 365) + (mes * 31) + dia;
}


/**\brief swap de 1 Long_list e 1 array
@param quantidade
@param id 
@param lista
@param lista_quantidade
@param indice
*/
void swapInList(int quantidade, long id, LONG_list lista, int* lista_quantidade, int indice){

    int quantidade_aux;
    long id_aux;
    quantidade_aux = *(lista_quantidade + indice);
    id_aux = get_list(lista, indice);
    *(lista_quantidade + indice) = quantidade;
    set_list(lista, indice, id);
    indice++;
    *(lista_quantidade + indice) = quantidade_aux;
    set_list(lista, indice, id_aux);
}

/**\brief sort de 1 Long_list e 1 array
@param lista
@param lista_quantidade
@param quantidade
@param id
@param max
*/
 // com as quantidade e ids inseridos ordena o array a cada inserção nova
void sortEnd(LONG_list lista, int* lista_quantidade, int quantidade, long id, int max){

    // enquanto o post tiver mais quantidade e poder andar no array é feito swap á esquerda
    // swap é aplicado na lista de quantidade e ids
    int aux;
    for(aux = max; quantidade > *(lista_quantidade + aux) && aux >= 0 ;aux--){
      swapInList(quantidade,id,lista,lista_quantidade,aux);
    }
}

/**\brief swap de 2 arrays
@param quantidade - quantidade especifica
@param id - id especifico
@param lista - lista de info
@param lista_quantidade - lista de quantidades
@param indice - indice para começar
*/
void swap_longs(int quantidade, long id, long* lista, int* lista_quantidade, int indice){
    int q = lista_quantidade[indice]; 
    long id_aux = lista[indice];
    lista_quantidade[indice] = quantidade;
    lista[indice] = id;
    indice++;
    lista_quantidade[indice] = q;
    lista[indice] = id_aux;
}

/**\brief sort de 3 arrays
@param lista - lista de info
@param lista_quantidade - lista de quantidades
@param quantidade - quantidade especifica
@param id - id especifico
@param indice - indice para começar
*/
void sortEnd_lists(long* lista, int* lista_quantidade, int quantidade, long id, int indice){

    // enquanto o post tiver mais quantidade e poder andar no array é feito swap á esquerda
    // swap é aplicado na lista de quantidade e ids
    for(; quantidade >= lista_quantidade[indice-1] && indice > 0 ;indice--){
      swap_longs(quantidade,id,lista,lista_quantidade,indice-1);
    }
}

/**\brief swap de 3 arrays
@param lista - lista 
@param lista_quantidade - lista de quantidades
@param lista_users_ids - lista de user ids
@param indice - indice especifico
*/
void swapInArray(long* lista,int* lista_quantidade, long* lista_users_ids, int indice){

    int q = lista_quantidade[indice];
    long info = lista[indice];
    long id = lista_users_ids[indice];
    lista[indice] = lista[indice+1];
    lista_quantidade[indice] = lista_quantidade[indice+1];
    lista_users_ids[indice] = lista_users_ids[indice+1];
    indice++;
    lista[indice] = info;
    lista_quantidade[indice] = q;
    lista_users_ids[indice] = id;
}

/**\brief sort de arrays
@param lista - lista 
@param lista_quantidade - lista de quantidades
@param lista_users_ids - lista de user ids
@param indice - indice especifico
*/
void sortArrays_byUsersId(long* lista, int* lista_quantidade, long* lista_users_ids,int indice){

    if(indice < 1) return;
    int quantidade = lista_quantidade[indice];
    // enquanto o post tiver mais quantidade e poder andar no array é feito swap á esquerda
    // swap é aplicado na lista de quantidade e ids
    for(; indice > 0 && quantidade >= lista_quantidade[indice-1];indice--){
        if(quantidade == lista_quantidade[indice-1] && lista_users_ids[indice] > lista_users_ids[indice-1]){
            break;
        }
        swapInArray(lista,lista_quantidade,lista_users_ids,indice-1);
    }
}


/**\brief swap de 3 TAD_ARRAY_LIST
@param lista - lista
@param lista_quantidade - lista contadores
@param lista_ids - lista de ids
@param indice - indice específico
*/
void swapArrayList(TAD_ARRAY_LIST lista,TAD_ARRAY_LIST lista_quantidade, TAD_ARRAY_LIST lista_ids, int indice){

    int* q = getElem(lista_quantidade,indice);
    void* info = getElem(lista,indice);
    long* id = getElem(lista_ids,indice);
    addElemAtIndex(lista,getElem(lista,indice+1),indice);
    addElemAtIndex(lista_quantidade,getElem(lista_quantidade,indice+1),indice);
    addElemAtIndex(lista_ids,getElem(lista_ids,indice+1),indice);
    indice++;
    addElemAtIndex(lista,info,indice);
    addElemAtIndex(lista_quantidade,q,indice);
    addElemAtIndex(lista_ids,id,indice);
}


/**\brief sort de 3 TAD_ARRAY_LIST
@param lista - lista
@param lista_quantidade - lista de contadores
@param lista_ids - lista de ids
@param indice - indice específico
*/

void sortEnd_lists_byId(TAD_ARRAY_LIST lista, TAD_ARRAY_LIST lista_quantidade,TAD_ARRAY_LIST lista_ids,int indice){

    if(indice < 1) return;
    int quantidade = *(int*) getElem(lista_quantidade,indice);
    // enquanto o post tiver mais quantidade e poder andar no array é feito swap á esquerda
    // swap é aplicado na lista de quantidade e ids
    for(; indice > 0 && quantidade >= *(int*)getElem(lista_quantidade,indice-1);indice--){
        if(quantidade == *(int*)getElem(lista_quantidade,indice-1) && *(long*) getElem(lista_ids,indice) >= *(long*) getElem(lista_ids,indice-1)){
            break;
        }
        swapArrayList(lista,lista_quantidade,lista_ids,indice-1);
    }
}
/**\brief sorte de 2 TAD_ARRAY_LIST
@param lista_tags - lista de tags
@param lista_NTags - lista de contadores de tags
@param ocupados - posição do elemento inserido/alterado na lista 
*/
void sortByPos(TAD_ARRAY_LIST lista_tags,TAD_ARRAY_LIST lista_NTags, int ocupados){
    char* aux1;
    // mudar ha chanses de o valor ser alterado
    int* aux2;
    while(ocupados > 0 && * (int *) getElem(lista_NTags,ocupados) > * (int*) getElem(lista_NTags,ocupados-1)){
        aux1 = (char*) getElem(lista_tags,ocupados-1);
        aux2 = (int*) getElem(lista_NTags,ocupados-1);
        addElemAtIndex(lista_tags,getElem(lista_tags,ocupados),ocupados-1);
        addElemAtIndex(lista_NTags,getElem(lista_NTags,ocupados),ocupados-1);
        addElemAtIndex(lista_tags,aux1,ocupados);
        addElemAtIndex(lista_NTags,aux2,ocupados);
        ocupados--;
    }
}

// --------------------------------------------------------------------------------------------

/**\brief Troca os elementos a e b de posição na memória.
@param a - elemento a
@param b - elemento b
*/
static void swap(long* a, long* b){
    int t = *a;
    *a = *b;
    *b = t;
}

/**\brief Aplica o algoritmo partition ao array dateSum[] ordenando simultaneamente o array ids[].
@param dateSum - array com conversoes de datas em longs
@param ids - array com ids 
@param low - indice minimo 
@param high - indice maximo
*/
static int partition_v2Array(long dateSum[], long ids[], int low, int high){
    int pivot = dateSum[high];    
    int i = (low - 1);  
 
    for (int j = low; j <= high- 1; j++)
    {

        if (dateSum[j] <= pivot)
        {
            i++;    
            swap(&dateSum[i], &dateSum[j]);
            swap(&ids[i], &ids[j]);
        }
    }
    swap(&dateSum[i + 1], &dateSum[high]);
    swap(&ids[i + 1], &ids[high]);
    return (i + 1);
}

/**\brief Aplica o algoritmo quickSort ao array dateSum[] ordenando simultaneamente o array ids[].
@param dateSum - array com conversoes de datas em longs
@param ids - array com ids 
@param low - indice minimo 
@param high - indice maximo
*/
static void quickSort_v2Array(long dateSum[], long ids[], int low, int high){
    if (low < high)
    {
        int pi = partition_v2Array(dateSum, ids, low, high); 
        quickSort_v2Array(dateSum, ids, low, pi - 1);
        quickSort_v2Array(dateSum, ids, pi + 1, high);
    }
}

// --------------------------------------------------------------------------------------------

/**\brief Dado um array com id's de posts e a tabela de hash de posts, ordena os posts por cronologia inversa.
@param ids - array com id's dos posts
@param size - tamanho do arry
@param h - tabela de hash dos posts
*/
void sort_posts_by_inverted_cronology(long ids[], int size, TAD_HTABLE h){

    long arrSUM[size]; // array que contem os SUM de cada data
    int i;
    Date d;
    TAD_POST p;

    for (i = 0; i < size; i++){
        p = (TAD_POST) getDados(h, ids[i]);
        d = getPostData(p);
        arrSUM[i] = getDateSum(d);
    }
    
    // ordena o ids[] com base na ordenação do arrSUM[] 
    quickSort_v2Array(arrSUM, ids, 0, size-1);

    for(int i = 0; i < size / 2; i++)
        swap(ids + i, ids + (size - i -1));
}