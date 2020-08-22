#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <tags.h>
#include <stdfunctions.h>

/**
@file tags.c
Módulo que contém as funções de criação, manipulação e destruição de uma tag.
*/



/**\brief Estrutura que armazena e gere os elementos do tags
*/

typedef struct TCD_TAG{
    /**\brief tagId - id da tag*/
    int tagId;
    /**\brief nome - nome da tag*/
    char* nome;
} TCD_TAG;

/**\brief Construtor da tag
@param id - id da tag 
@param tagName - nome da tag
*/

TAD_TAG createTag(int id, char* tagName){

  int length = strlen(tagName);
  TAD_TAG tag = malloc(sizeof(TCD_TAG));
  tag->tagId = id;
  tag->nome = NULL;
  
  if(tagName){
    tag->nome = malloc(sizeof(char) * length+1);
    memcpy(tag->nome,tagName,length+1);
  }

	return tag;
}

/**\brief Setter do nome da tag
@param tag - tag a preencher
@param nome - nome a ser guardado na tag
*/
void setTagName(TAD_TAG tag, char* nome){

  int i = strlen(nome);

  tag->nome = malloc(i * sizeof(char));
  memcpy(tag->nome,nome,i+1);
}

/**\brief Getter do nome da tag
@param tag - tag com o nome a retirar
@return NULL caso a tag não esja inicializada ou o nome
*/
char* getTagName(TAD_TAG tag){
  
  #ifdef TESTA_ERRO_TAGS
  if(tag == NULL || tag->nome == NULL){
        perror("tag == NULL || tag->nome == NULL: getTagName() on module TAG_H");
        exit(1);
  }
  #endif

  return tag->nome;
}

/**\brief Getter do id da tag
@param tag - tag com o id a retirar
@return NULL caso a tag não esja inicializada ou o id da tag
*/

int getTagId(TAD_TAG tag){

  #ifdef TESTA_ERRO_TAGS
  if(tag == NULL || tag->nome == NULL){
        perror("tag == NULL || tag->nome == NULL: getTagId() on module TAG_H");
        exit(1);
  }
  #endif

	return tag->tagId;
}

/**\brief Conversor do tag para uma string com a mesma informação
@param tag - tag com parametros a converter para texto
@return NULL caso a tag não esteja inicializada ou a info da tag
*/
char* tag2string(TAD_TAG tag){
  
  if (tag == NULL) return "NULL";
   
  char* fstBuf = malloc(MB);

  #ifdef TESTA_ERRO_TAGS
  if(tag == NULL || tag->nome == NULL){
      perror("tag == NULL || tag->nome == NULL: tag2string() on module TAG_H");
      exit(1);
  }
  #endif
    
  sprintf(fstBuf, "TAG_H{ tagId: %d | nome: %s }", tag->tagId, tag->nome);
  int length = strlen(fstBuf) + 1;
  char* r = malloc(length);
  memcpy(r,fstBuf,length);

  free(fstBuf);

  return r;
}

/**\brief Free da tag*/
void freeTag(TAD_TAG tag){
   
  if (tag){
    
    if (tag->nome){
      free(tag->nome);
      tag->nome = NULL;
    }
    
    free(tag);
    tag = NULL;
  }
}