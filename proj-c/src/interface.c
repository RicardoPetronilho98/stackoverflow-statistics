#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <assert.h>

#include <arrayList.h>
#include <common.h>
#include <datas.h>
#include <date.h>
#include <globalstruct.h>
#include <htable.h>
#include <interface.h>
#include <list.h>
#include <pair.h>
#include <post.h>
#include <postsParser.h>
#include <quickSortDates.h>
#include <real_user.h>
#include <stdfunctions.h>
#include <tags.h>
#include <tagsParser.h>
#include <user.h>
#include <usersParser.h>

/**
@file interface.c
Módulo que contém as funções de criação, carregamento e destruição da TAD_community.
*/

/**
\brief Cria a estrutura global.
@return retorna a nova estrutura global
*/
TAD_community init(){ 
	return GlobalStruct();
}


/**
\brief Liberta a memória alocada para a estrutura global.
@return retorna a estrutura global libertada
*/
TAD_community clean(TAD_community com){
  free_globalStruct(com);
	return com;
}



/**
\brief Carrega a informação contida nos diferentes ficheiros .xml, localizados no dump_path, para a estrututa global.
@param com - estrutura global
@param dump_path - diretoria onde se encontram os ficheiros .xml
@return retorna a estrutura global atualizada com a informação
*/
TAD_community load(TAD_community com, char* dump_path){

	int dim = strlen(dump_path);
    
  char *customPath= malloc(dim + 10);
  
  char *parserPath = malloc(dim + 9);
  
  sprintf(customPath, "%s/Tags.xml", dump_path);
  tagsParser(customPath, com);
  free(parserPath);
  
  sprintf(customPath, "%s/Users.xml", dump_path);
  usersParser(customPath, com);
    
  sprintf(customPath, "%s/Posts.xml", dump_path);
  postsParser(customPath, com);
  
  free(customPath);

  return com;
}