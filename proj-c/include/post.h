#ifndef POST_H
#define POST_H

typedef struct TCD_POST *TAD_POST;

#include <date.h>

//construtores e destrutores:
TAD_POST Post(int tipo, long user_id, long parent_id, char* titulo, char* tags, char* data, int answers, int score, int commentCount);
void free_Post(TAD_POST post);			//	faz clean á estrutura TAD_POST;

//geters
int getTipo(TAD_POST post);
long getUserId(TAD_POST post);		//	devolve o user id de um post;
long getParentId(TAD_POST post);     //	devolve o parent_id do post;
char* getTitulo(TAD_POST post);
char* getTagsFromPost(TAD_POST post); // nota: mudei o nome pq existia uma função com este nome
int getAnswerCount(TAD_POST post);
int getCommentCount(TAD_POST post);
int getScore(TAD_POST post);
Date getPostData(TAD_POST post);
int getUpvotesPost(TAD_POST post);
int getDownvotesPost(TAD_POST post);
int contavotosPost(TAD_POST post);

//setters
void addVoteToPost(int vote,TAD_POST post);


//toString
char* post2string(TAD_POST post);	//	retorna uma string com a informção de um post;

#endif