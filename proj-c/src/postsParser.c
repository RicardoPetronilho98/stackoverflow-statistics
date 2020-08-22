#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>
#include <string.h>

#include <postsParser.h>
#include <globalstruct.h>
#include <post.h>
#include <datas.h>

/**
@file postsParser.c
Módulo que contém as funções de parser para a estrutura de dados dos posts e datas.
*/

/**\brief Percorre os atributos de cada nodo, obtendo os valores pretendidos e carrega-os para a estrutura global.
@param node - nodo atual no ficheiro .xml
@param com - estrutura global
*/
static void search_elements(xmlTextReaderPtr node, TAD_community com){
    
    long postId, userId, type = -1, parentId = -1, answers = 0, score = -1, commentCount = 0;
    xmlChar* attribVal = NULL, *dataStrVal = NULL, *titleVal = NULL, *tagsVal = NULL;
    char* dataStr = NULL;
    char* title = NULL;
    char* tags = NULL;
    Date data = NULL;
    TAD_POST post;

    while(xmlTextReaderRead(node) == 1){    //  enquanto não dá erro ou existe algo para ler
        
        attribVal = xmlTextReaderLocalName(node);
        if (attribVal){
            if (strcmp((char*) attribVal, "row") != 0){
                xmlFree(attribVal);
                continue;
            }
            xmlFree(attribVal);     
        }

        attribVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "Id");  
        if (attribVal){
            postId = atoi((const char*) attribVal);
            xmlFree(attribVal);
        }

        attribVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "PostTypeId");  
        if (attribVal){
            type = atoi((const char*) attribVal);
            xmlFree(attribVal);
        }

        dataStrVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "CreationDate");  
        dataStr = (char*) dataStrVal;

        attribVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "OwnerUserId");  
        if (attribVal){
            userId = atoi((const char*) attribVal);
            xmlFree(attribVal);
        }

        attribVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "Score");  
        if (attribVal){
            score = atoi((const char*) attribVal);
            xmlFree(attribVal);
        }

        attribVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "CommentCount");  
        if (attribVal){
            commentCount = atoi((const char*) attribVal);
            xmlFree(attribVal);
        }

        if(type == 1){
            
            titleVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "Title");  
            title = (char*) titleVal;
            
            tagsVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "Tags");  
            tags = (char*) tagsVal;

            attribVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "AnswerCount");  
            if (attribVal){
                answers = atoi((const char*) attribVal);
                xmlFree(attribVal);
            }
        }

        if (type == 2){ 
            
            attribVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "ParentId");  
            if (attribVal){
                parentId = atoi((const char*) attribVal);
                xmlFree(attribVal);
            }
        }

        atualiza_User_Posts(userId, postId, com);   
        post = Post(type, userId, parentId, title, tags, dataStr, answers, score, commentCount); 
        addPost(postId, post, com);


        char ano[12], mes[12], dia[12];
        int i, k;

        for (i = 0; dataStr[i] != '-'; i++)
            ano[i] = dataStr[i];
        ano[i] = '\0';

        i++;
        for (k = 0; dataStr[i] != '-'; i++, k++)
            mes[k] = dataStr[i];
        mes[k] = '\0';


        i++;
        for (k = 0; dataStr[i] != 'T'; i++, k++)
            dia[k] = dataStr[i];
        dia[k] = '\0';

        data = createDate(atoi(dia), atoi(mes), atoi(ano));
        addDatas(data, userId, postId, com);

        if (data) free_date(data);
        
        if (dataStrVal){
            xmlFree(dataStrVal);
            dataStrVal = NULL;
        }
        
        if (titleVal){
            xmlFree(titleVal);
            titleVal = NULL;
        }
        
        if (tagsVal){
            xmlFree(tagsVal);
            tagsVal = NULL;
        }
    }
}


/**\brief Percorre todo o fichiero .xml carregando os valores pretendidos para a estrutura global.
@param path - caminho para o respetivo ficheiro .xml
@param com - estrutura global
*/
void postsParser(char* path, TAD_community com){

    LIBXML_TEST_VERSION

    xmlTextReaderPtr tree = NULL;

    if ((tree = xmlReaderForFile(path, NULL, 0)) == NULL ) {
        perror("error: could not parse file");
        exit(1);
    }

    search_elements(tree, com);

    if (tree) xmlFreeTextReader(tree);

    printf("Posts parser done!\n");
    printf("Datas parser done!\n");
}

