#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <htable.h>
#include <post.h>
#include <real_user.h>
#include <tags.h>
#include <stdfunctions.h>

/**
@file htable.c
Módulo que contém as funções de criação, manipulação e destruição de uma Tabela de Hash.
*/

/**\brief indica que a célula está livre*/
#define FREE                      0
/**\brief indica que a célula está ocupada*/
#define USED                      1

/**\brief célula que armazena informação na Tabela de Hash*/
typedef struct cell{

	/**\brief id da célula*/
	long id;
	/**\brief indica se a célula está a ser usada*/
	long status;
	/**\brief contador de colisões obtidas quando foi armazenada informação na célula*/
	long colisoes;
	/**\brief informação que a célula contém*/
	void *dados;

} HTABLE_CELL;

/**\brief Estrutura que armazena e gere os elementos da Tabela de Hash*/
typedef struct TCD_HTABLE{

	/**\brief array de células que contêm a informação*/
	HTABLE_CELL* celulas;
	/**\brief número de elementos contidos na Tabela de Hash*/
	long ocupados;
	/**\brief capacidade da Tabela de Hash*/
	long dim;

} TCD_HTABLE;
	

static void resize(TAD_HTABLE htable);
static long hash(long id, long dim);


/**
\brief Retorna o ID da célula na posição especificada.
@param htable - Tabela de Hash
@param index - índice
@return retorna o ID
*/
long getIdAtIndex(TAD_HTABLE htable, long index){

	#ifdef TESTA_ERRO_HTABLE
	if (htable == NULL || htable->celulas == NULL){
		perror("htable == NULL || htable->celulas == NULL: getIdAtIndex() on module HTABLE"); 
		exit(EXIT_FAILURE);
	}	
	#endif

	return htable->celulas[index].id;
}

/**
\brief Retorna a informação contida na célula com o ID especificado.
@param htable - Tabela de Hash
@param id - ID da célula
@return retorna a informação
*/
void* getDados(TAD_HTABLE htable, long id){

	#ifdef TESTA_ERRO_HTABLE
	if (htable == NULL || htable->celulas == NULL){
		perror("htable == NULL || htable->celulas == NULL: getDados() on module HTABLE"); 
		exit(EXIT_FAILURE);
	}	
	#endif

	long index = indexOf(id, htable);
	return htable->celulas[index].dados;
}

/**
\brief Retorna a informação contida na posição especificada.
@param htable - Tabela de Hash
@param index - índice
@return retorna a informação
*/
void* getDadosAtIndex(TAD_HTABLE htable, long index){

	#ifdef TESTA_ERRO_HTABLE
	if (htable == NULL || htable->celulas == NULL){
		perror("htable == NULL || htable->celulas == NULL: getDadosAtIndex() on module HTABLE"); 
		exit(EXIT_FAILURE);
	}	
	#endif

	return htable->celulas[index].dados;
}

/**
\brief Retorna o número de elementos numa Tabela de Hash.
@param htable - Tabela de Hash
@return número de elementos
*/
long getHtableSize(TAD_HTABLE htable){

	#ifdef TESTA_ERRO_HTABLE
	if (htable == NULL || htable->celulas == NULL){
		perror("htable == NULL || htable->celulas == NULL: getHtableSize() on module HTABLE"); 
		exit(EXIT_FAILURE);
	}	
	#endif

	return htable->dim;
}


/**
\brief Cria uma Tabela de Hash com capacidade inicial dim.
@param dim - capacidade inicial
@return retorna a nova Tabela de Hash
*/
TAD_HTABLE Htable(long dim){

	#ifdef TESTA_ERRO_HTABLE
	if (dim == 0){
		perror("dim == 0: Htable() on module HTABLE"); 
		exit(EXIT_FAILURE);
	}	
	#endif

	long i;

	TAD_HTABLE h = malloc(sizeof(TCD_HTABLE));
	h->celulas = malloc(sizeof(HTABLE_CELL) * dim);
	h->ocupados = 0;
	h->dim = dim;

	for (i = 0; i < dim; i++){
		h->celulas[i].status = FREE;
		h->celulas[i].colisoes = 0;
		h->celulas[i].dados = NULL;
	}

	return h;
}

/**
\brief Adiciona a informação com um ID especificado à Tabela de Hash.  
@param dados - informação
@param id - ID da célula
@param htable - Tabela de Hash
*/
void add(void* dados, long id, TAD_HTABLE htable){


	#ifdef TESTA_ERRO_HTABLE
	if (htable == NULL || htable->celulas == NULL || dados == NULL){
		perror("htable == NULL || htable->celulas == NULL || dados == NULL: add() on module HTABLE"); 
		exit(EXIT_FAILURE);
	}	
	#endif
    
	long i = 1; // variável que vai realizar o quadratic probing
	long dim = htable->dim;
	long p = hash(labs(id), dim); // posicao do user na tabela de hash
	long p_inicial = p;
	htable->ocupados++;
	HTABLE_CELL* h = htable->celulas;

	while(h[p].status == USED){		//	vai percorrer até encontrar um posição FREE;

		p = hash(labs(id) + i * i, dim);
		i++;
	}
    
	h[p].id = id;
	h[p].status = USED;
	h[p_inicial].colisoes = i - 1;
	h[p].dados = dados;

    if (usedPercentage(htable) > 0.7) {

    	resize(htable);
    }
}

/**
\brief Liberta a zona de memória alocada para a Tabela de Hash.
@param htable - Tabela de Hash
*/
void free_htable(TAD_HTABLE htable){

	if (htable){
	   	
	   	if (htable->celulas){
	   		free(htable->celulas);
	   		htable->celulas = NULL;
	   	}

		free(htable);
		htable = NULL;
	}
}

/**
\brief Indica a posição onde vai ser armazenada a informação com um ID específico.
@param id - ID da célula
@param dim - Dimensão da Tabela de Hash
@return retorna a posição
*/
static long hash(long id, long dim){

	#ifdef TESTA_ERRO_HTABLE
	if (dim == 0){
		perror("dim == 0: hash() on module HTABLE"); 
		exit(EXIT_FAILURE);
	}	
	#endif
    
	return id % dim;
}

/**
\brief Indica a posição da célula com um ID especificado.
@param id - ID da célula
@param htable - Tabela de Hash
@return retorna a posição
*/
long indexOf(long id, TAD_HTABLE htable){

	#ifdef TESTA_ERRO_HTABLE
	if (htable == NULL || htable->celulas == NULL){
		perror("htable == NULL || htable->celulas == NULL: indexOf() on module HTABLE"); 
		exit(EXIT_FAILURE);
	}	
	#endif

 	long i = 1; // variável que vai realizar o quadratic probing
 	long dim = htable->dim;
	long p = hash( labs(id), dim); // posicao do elemento na tabela de hash
    HTABLE_CELL* h = htable->celulas;
    long colisoes = h[p].colisoes;

	while(h[p].id != id && h[p].status != FREE && colisoes > 0){

		p = hash(labs(id) + i * i, dim);
		colisoes--;
		i++;
	}

	if (h[p].id == id && h[p].status == USED) return p;
	else return -1;
}


/**
\brief Re-dimensiona o array de células da Tabela de Hash, triplicando o seu tamanho.
@param htable - Tabela de Hash
@return retorna a posição
*/
static void resize(TAD_HTABLE htable){

	#ifdef TESTA_ERRO_HTABLE
	if (htable == NULL || htable->celulas == NULL){
		perror("htable == NULL || htable->celulas == NULL: resize() on module HTABLE"); 
		exit(EXIT_FAILURE);
	}	
	#endif

	long i, newDim = htable->dim * 3; 
    
    HTABLE_CELL* newCells = malloc(sizeof(HTABLE_CELL) * newDim); // nova array de células
    for (i = 0; i < newDim; i++){
		newCells[i].status = FREE;
		newCells[i].colisoes = 0;
		newCells[i].dados = NULL;
	}

    for(i = 0; i < htable->dim; i++)
    	if(htable->celulas[i].status == USED){
    		void* dados = htable->celulas[i].dados;
    		long id = htable->celulas[i].id;
    		long v = 1; // variável que vai realizar o quadratic probing
			long p = hash(labs(id), newDim); // posicao do user na tabela de hash
			long p_inicial = p;

			while(newCells[p].status == USED){		//	vai percorrer até encontrar um posição FREE;

				p = hash(labs(id) + v * v, newDim);
				i++;
			}
		    
			newCells[p].id = id;
			newCells[p].status = USED;
			newCells[p_inicial].colisoes = v - 1;
			newCells[p].dados = dados;
    	}
    	 
   	HTABLE_CELL* oldCells = htable->celulas;
    htable->dim = newDim;
    htable->celulas = newCells;
  	free(oldCells);
}

/**
\brief Adiciona a informação numa determinada posição da Tabela de Hash.
@param dados - informação
@param index - índice
@param htable - Tabela de Hash
*/
void set(void* dados, long index, TAD_HTABLE htable){

	#ifdef TESTA_ERRO_HTABLE
	if (htable == NULL || htable->celulas == NULL){
		perror("htable == NULL || htable->celulas == NULL: set() on module HTABLE"); 
		exit(EXIT_FAILURE);
	}	
	#endif

	HTABLE_CELL* h = htable->celulas;
	h[index].dados = dados;
}

/**
\brief Retorna o fator de ocupação da Tabela de Hash.
@param htable - Tabela de Hash
@return Retorna o fator
*/
float usedPercentage(TAD_HTABLE htable){

	#ifdef TESTA_ERRO_HTABLE
	if (htable == NULL){
		perror("htable == NULL: usedPercentage() on module HTABLE"); 
		exit(EXIT_FAILURE);
	}	
	#endif
    
    return (float) htable->ocupados / (float) htable->dim;
}



//  ----- PARA DEBUGGING -------------------------------------------------------

/**
\brief Retorna uma representação da informação contida em cada célula em formato String.
@param dados - informação
@param type - Tipo de Tabela de Hash
@return Retorna a String
*/
static char* dados2string(void* dados, char type){
    
    if ( type == 'p'){
 		return post2string( (TAD_POST) dados);
    }
    
    else if (type == 'u'){ 
		return user2string( (TAD_REAL_USER) dados ); 
	}

	else return NULL;
}

/**
\brief Retorna uma representação da Tabela de Hash em formato String.
@param htable - Tabela de Hash
@param type - Tipo de Tabela de Hash
@return Retorna a String
*/
char* htable2string(TAD_HTABLE htable, char type){ 
    
	#ifdef TESTA_ERRO_HTABLE
	if ( htable == NULL || htable->celulas == NULL || (type != 'p' && type != 'u' && type != 't') ){
		perror("htable == NULL || (type != 'p' && type != 'u'): htable2string on module HTABLE");
		exit(EXIT_FAILURE);
	}
	#endif

	
	long i, k;
	long dim = htable->dim;
	HTABLE_CELL* h = htable->celulas;
	
    char* fstBuf = malloc(512 * MB);

    sprintf(fstBuf, "TAD_HTABLE{\n");
    k = 12;

   	char num_1[12];
   	char num_2[12];
   	char num_3[12];
    char *dados = NULL;
   
    for (i = 0; i < dim; i++){
    	sprintf(num_1, "%ld", h[i].id);
	 	sprintf(num_2, "%ld", h[i].status);
	 	sprintf(num_3, "%ld", h[i].colisoes);
        dados = dados2string(h[i].dados, type);
		sprintf( fstBuf + k, "\n\npos = %ld | id = %s | status = %s | colisoes = %s | dados = %s\n", i, num_1, num_2, num_3, dados );
		k += strlen(fstBuf + k);
		if (dados) free(dados);
	    if (k > 512 * MB){
	    	perror("buffer insuficiente para conter a string: htable2string() on module HTABLE");
	    	exit(EXIT_FAILURE);
	    }
	}

    sprintf(fstBuf + k, "}");
    
    long length = strlen(fstBuf) + 1;
    char* r = malloc(length);
    memcpy(r, fstBuf, length);

    free(fstBuf);

    return r;

}
