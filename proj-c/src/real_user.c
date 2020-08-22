#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <real_user.h>
#include <arrayList.h>
#include <stdfunctions.h>

/**\brief Dimensão inicial do ArrayList que contém os ID's dos posts do utilizador*/
#define ARRAY_POSTS_DIM_INICIAL                  16

/**
@file real_user.c
Módulo que contém as funções de criação, manipulação e destruição da estrutura que armazena informações de cada utilizador.
*/

/**\brief Estrutura que armazena as informações de cada utilizador*/
typedef struct TCD_REAL_USER{

    /**\brief Reputação do utilizador*/
    int reputacao;
    /**\brief Nome do utilizador*/
    char* nome;
    /**\brief Biografia do utilizador*/
    char* bio;
    /**\brief ArrayList que contém os ID's dos posts do utilizador*/
    TAD_ARRAY_LIST posts;
    /**\brief Número de upvotes dos posts do utilizador*/
    int upvotes;
    /**\brief Número de downvote dos posts do utilizador*/
    int downvotes;

} TCD_REAL_USER;



/**
\brief Cria um utilizador.
@return retorna o novo utilizador
*/
TAD_REAL_USER Real_User(){

	TAD_REAL_USER user = malloc(sizeof(TCD_REAL_USER));
    user->reputacao = 0;
    user->nome = NULL;
    user->bio = NULL;
	user->posts = NULL;
    user->upvotes = 0;
    user->downvotes = 0;

	return user;
}


/**
\brief Preenche os campos do utilizador.
@param user - utilizador
@param reputacao - reputação do utilizador
@param nome - nome do utilizador
@param bio - biografia do utilizador
@param upvotes - número de upvotes dos posts do utilizador
@param downvotes - número de downvotes dos posts do utilizador
*/
void setUser(TAD_REAL_USER user, int reputacao, char* nome, char* bio, int upvotes, int downvotes){

    #ifdef TESTA_ERRO_REAL_USER
    if(user == NULL || nome == NULL || bio == NULL){
        perror("user == NULL || nome == NULL || bio == NULL: setUser() on module REAL_USER");
        exit(EXIT_FAILURE);
    }
    #endif

    user->reputacao = reputacao;

    if (nome){
        int nomeLen = strlen(nome) + 1;
        user->nome = malloc(nomeLen);
        memcpy(user->nome, nome, nomeLen);
    }

    if (bio){
        int bioLen = strlen(bio) + 1;
        user->bio = malloc(bioLen);
        memcpy(user->bio, bio, bioLen);
    }

    user->upvotes = upvotes;
    user->downvotes = downvotes;
}

/**
\brief Retorna o nome de um utilizador.
@param user - utilizador
@return retorna o nome
*/
char* getName(TAD_REAL_USER user){
    
    #ifdef TESTA_ERRO_REAL_USER
    if (user == NULL || user->nome == NULL){
        perror("user == NULL || user->nome == NULL: getName() on module REAL_USER");
        exit(EXIT_FAILURE);
    }
    #endif

    return user->nome;
}


/**
\brief Retorna a biografia de um utilizador.
@param user - utilizador
@return retorna a biografia
*/
char* getBio(TAD_REAL_USER user){

    #ifdef TESTA_ERRO_REAL_USER
    if (user == NULL || user->bio == NULL){
        perror("user == NULL || user->bio == NULL: getBio() on module REAL_USER");
        exit(EXIT_FAILURE);
    }
    #endif

    return user->bio;
}


/**
\brief Retorna reputação de um utilizador.
@param user - utilizador
@return retorna a reputação
*/
int getReputacao(TAD_REAL_USER user){

    #ifdef TESTA_ERRO_REAL_USER
    if (user == NULL){
        perror("user == NULL: getReputacao() on module REAL_USER");
        exit(EXIT_FAILURE);
    }
    #endif
    
    return user->reputacao;
}

/**
\brief Retorna o número de upvotes de um utilizador.
@param user - utilizador
@return retorna o número de upvotes
*/
int getUpvotes(TAD_REAL_USER user){

    #ifdef TESTA_ERRO_REAL_USER
    if (user == NULL){
        perror("user == NULL: getUpvotes() on module REAL_USER");
        exit(EXIT_FAILURE);
    }
    #endif

    return user->upvotes;
}


/**
\brief Retorna o número de downvotes de um utilizador.
@param user - utilizador
@return retorna o número de downvotes
*/
int getDownvotes(TAD_REAL_USER user){

    #ifdef TESTA_ERRO_REAL_USER
    if (user == NULL){
        perror("user == NULL: getDownvotes() on module REAL_USER");
        exit(EXIT_FAILURE);
    }
    #endif

    return user->downvotes;
}



/**
\brief Retorna a diferença entre o número de upvotes e downvotes.
@param user - utilizador
@return retorna a diferença de votos
*/
int contavotos(TAD_REAL_USER user){

    #ifdef TESTA_ERRO_REAL_USER
    if (user == NULL){
        perror("user == NULL: contavotos() on module REAL_USER");
        exit(EXIT_FAILURE);
    }
    #endif

    return user->upvotes - user->downvotes;
}


/**
\brief Retorna o ArrayList que contém os ID's dos posts de um utilizador.
@param user - utilizador
@return retorna o ArrayList
*/
TAD_ARRAY_LIST getArrayList(TAD_REAL_USER user){

    #ifdef TESTA_ERRO_REAL_USER
    if (user == NULL || user->posts == NULL){
        perror("user == NULL || user->posts == NULL: getArrayList() on module REAL_USER");
        exit(EXIT_FAILURE);
    }
    #endif

    return user->posts;
}


/**
\brief Retorna uma representação do utilizador em formato String.
@param user - utilizador
@return Retorna a String
*/
char* user2string(TAD_REAL_USER user){

    char *r;
    
    if (user == NULL){
        r = malloc(5);
        memcpy(r, "NULL", 5);
        return r;
    }
   
    char* fstBuf = malloc(MB);

    #ifdef TESTA_ERRO_REAL_USER
    if(user->nome == NULL || user->bio == NULL || user->posts == NULL){
        perror("user->nome == NULL || user->bio == NULL || user->posts == NULL: user2string() on module REAL_USER");
        exit(EXIT_FAILURE);
    }
    #endif

    char* posts2string = NULL;
    int size = 0;

    if (user->posts){

        size = getArraySize(user->posts);

        long posts[size];
        int i;
        for(i = 0; i < size; i++)
            posts[i] = * (long*) getElem(user->posts, i);
        
        posts2string = arrayLong2string(posts, size);
    } else{

        posts2string = malloc(5);
        memcpy(posts2string, "NULL", 5);
    }
    
    sprintf(fstBuf, "REAL_USER{ reputação: %d | nome: %s | bio: %s | posts: %s | ocupados = %d | upvotes = %d | downvotes = %d }", user->reputacao, user->nome, user->bio, posts2string, size, user->upvotes, user->downvotes);
    int length = strlen(fstBuf) + 1;
    r = malloc(length);
    memcpy(r,fstBuf,length);

    if (posts2string) free(posts2string);
    free(fstBuf);

    return r;
}



/**
\brief Adiciona um ID de um post a um utilizador.
@param user - utilizador
@param id - ID do post
*/
void addPost2User(TAD_REAL_USER user, long id){

    #ifdef TESTA_ERRO_REAL_USER
    if (user == NULL){
        perror("user == NULL: addPost2User() on module REAL_USER error");
        exit(EXIT_FAILURE);
    }
    #endif 

    if (user->posts == NULL) user->posts = ARRAY_LIST(ARRAY_POSTS_DIM_INICIAL);

    long* postId = malloc(sizeof(long));
    memcpy(postId, &id, sizeof(long));

	addElem(user->posts, postId);
}


/**
\brief Liberta a zona de memória alocada para o utilizador
@param user - utilizador
*/
void free_Real_User(TAD_REAL_USER user){

    int i;
    long *elem;

    if (user){

        if (user->nome){
            free(user->nome);
            user->nome = NULL;
        }
        
        if (user->bio){
            free(user->bio);
            user->bio = NULL;
        }
        
        if (user->posts){
            
            for (i = 0; i < getArraySize(user->posts); i++){
                elem = (long*) getElem (user->posts, i);
                if (elem){
                    free(elem);
                    elem = NULL;
                }
            }
            
            free_ARRAY_LIST(user->posts);
        }

        free(user);
        user = NULL;
    }   
}
