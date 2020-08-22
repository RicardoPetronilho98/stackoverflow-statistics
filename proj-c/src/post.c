#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <post.h>
#include <date.h>
#include <stdfunctions.h>
#include <arrayList.h>

#define ANSWERS_ARRAY_LIST_INIT_DIM     16

/**
@file post.c
Módulo que contém as funções de criação, manipulação e destruição da estrutura dos posts.
*/

typedef struct TCD_POST{
    /**\brief número de comentários*/
    int commentCount;
    /**\brief */
    int score; 
    /**\brief Número de respostas ao Post*/
	int answerCount; 
    /**\brief tipo de Post, se tipo for 1 é uma questão, se for 2 é uma resposta, se for 0 nem é pergunta nem resposta*/
    int tipo;
    /**\brief ID do utilizador que fez o Post*/
    long user_id;
    /**\brief ID da pergunta, caso o Post seja uma resposta*/
    long parent_id; 
    /**\brief tags para este Post*/
    char* tags; 
    /**\brief titulo do Post*/
    char* titulo; 
    /**\brief Número de upvotes dos Posts do utilizador*/
    int upvotes;
    /**\brief Número de downvote dos Posts do utilizador*/
    int downvotes;
    /**\brief Data do Post*/
    Date data;

} TCD_POST;

/**\brief Construtor de um Post
@param tipo - tipo do Post
@param user_id - ID do utilizador que fez o Post
@param titulo - título do Post
@param tags - lista de tags do Post
@param data - Data do Post
@param answers - número de respostas ao Post
@param score - 
@param commentCount - Número de comentários
@return retorna um Post*/
TAD_POST Post(int tipo, long user_id, long parent_id, char* titulo, char* tags, char* data, int answers, int score, int commentCount){
    
    TAD_POST post = malloc(sizeof(TCD_POST));
    post->titulo = NULL;
    post->tags = NULL;
    
    if(titulo){
        int tituloLen = strlen(titulo) + 1;
        post->titulo = malloc(tituloLen);
        memcpy(post->titulo, titulo, tituloLen);
    }

    if(tags){
        int tagslen = strlen(tags) + 1;
        post->tags = malloc(tagslen);
        memcpy(post->tags, tags, tagslen);
    }

    post->tipo = tipo;
    post->user_id = user_id;
    post->parent_id = parent_id;
    post->answerCount = answers;
    post->score = score;
    post->commentCount = commentCount;
    post->upvotes = 0;
    post->downvotes = 0;

    char ano[12], mes[12], dia[12];
    int i, k;
    
    for (i = 0; data[i] != '-'; i++)
        ano[i] = data[i];
    ano[i] = '\0';

    i++;
    for (k = 0; data[i] != '-'; i++, k++)
        mes[k] = data[i];
    mes[k] = '\0';
    

    i++;
    for (k = 0; data[i] != 'T'; i++, k++)
        dia[k] = data[i];
    dia[k] = '\0';

    post->data = createDate(atoi(dia), atoi(mes), atoi(ano));
    
    return post;
}

/**\brief Adiciona um vote ao Post
@param vote - número de votos
@param post - Post
*/
void addVoteToPost(int vote, TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: addVoteToPost() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    if(vote == 2) post->upvotes++;
    else post->downvotes++;
}

/**\brief Função que liberta um Post
@param post - Post
*/
void free_Post(TAD_POST post){  //  faz um free à estrutura do post;

    if (post){
    
        if (post->titulo){
            free(post->titulo);
            post->titulo = NULL;
        }

        if (post->tags){
            free(post->tags);
            post->tags = NULL;
        }

        if (post->data){
            free_date(post->data);
            post->data = NULL;
        }

        free(post);
        post = NULL;
    }
}

/**\brief Devolve o número de Comentários de um Post.
@param post - Post
@return número de comentários
*/
int getCommentCount(TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: getCommentCount() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    return post->commentCount;
}

/**\brief Devolve o score de um Post.
@param post - Post
@return score
*/
int getScore(TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: getScore() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    return post->score;
}

/**\brief Devolve o tipo de um Post.
@param post - Post
@return tipo
*/
int getTipo(TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: getTipo() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    return post->tipo;
}

/**\brief Devolve a data de um Post.
@param post - Post
@return data
*/
Date getPostData(TAD_POST post){ 

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: getPostData() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif
    
    return post->data;
}

/**\brief Devolve o id do utilizador que criou o Post.
@param post - Post
@return id do utilizador
*/
long getUserId(TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: getUserId() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    return post->user_id;
}

/**\brief Devolve o id da pergunta á que o respetivo post é uma resposta.
@param post - Post
@return id da pergunta
*/
long getParentId(TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: getParentId() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    return post->parent_id;
}

/**\brief Devolve o titulo de um Post.
@param post - Post
@return titulo
*/
char* getTitulo(TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: getTitulo() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    return post->titulo;
}

/**\brief Devolve as tags de um Post.
@param post - Post
@return tags
*/
char* getTagsFromPost(TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: getTagsFromPost() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    return post->tags;
}

/**\brief Devolve ó numero de respostas de um Post.
@param post - Post
@return número de respostas
*/
int getAnswerCount(TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: getAnswerCount() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    return post->answerCount;
}

/**
\brief Retorna o número de upvotes de um Post.
@param post - Post
@return retorna o número de upvotes
*/
int getUpvotesPost(TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: getUpvotes() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    return post->upvotes;
}


/**
\brief Retorna o número de downvotes de um Post.
@param post - Post
@return retorna o número de downvotes
*/
int getDownvotesPost(TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: getDownvotes() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    return post->downvotes;
}



/**
\brief Retorna a diferença entre o número de upvotes e downvotes.
@param post - Post
@return retorna a diferença de votos
*/
int contavotosPost(TAD_POST post){

    #ifdef TESTA_ERRO_POST
    if (user == NULL){
        perror("user == NULL: contavotos() on module POST");
        exit(EXIT_FAILURE);
    }
    #endif

    return post->upvotes - post->downvotes;
}


/**
\brief Retorna o informação do Post em formato String.
@param post - Post
@return string
*/
char* post2string(TAD_POST post){

    char *r;
    
    if (post == NULL){
        r = malloc(5);
        memcpy(r, "NULL", 5);
        return r;
    }

    char* fstBuf = malloc(MB);
    
    if (post->data == NULL || post->titulo == NULL || post->tags == NULL){
        perror("post->data == NULL || post->titulo == NULL || post->tags == NULL: post2string() on module POST_H");
        exit(EXIT_FAILURE);
    }

    sprintf(fstBuf, "TAD_POST{ user_id: %ld | tipo: %d | data: %d-%d-%d | tags: %s | commentCount = %d | score = %d | answerCount = %d | parent_id = %ld | titulo = %s }", post->user_id, post->tipo, get_day(post->data), get_month(post->data), get_year(post->data), post->tags, post->commentCount, post->score, post->answerCount, post->parent_id, post->titulo);
    
    int length = strlen(fstBuf) + 1;
    r = malloc(length);
    memcpy(r, fstBuf, length);
    
    free(fstBuf);
    
    return r;
}
