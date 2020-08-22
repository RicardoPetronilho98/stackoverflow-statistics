#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>
#include <string.h>

#include <usersParser.h>
#include <globalstruct.h>
#include <real_user.h>

/**
@file usersParser.c
Módulo que contém as funções de parser para a estrutura de dados dos users.
*/

/**\brief Percorre os atributos de cada nodo, obtendo os valores pretendidos e carrega-os para a estrutura global.
@param node - nodo atual no ficheiro .xml
@param com - estrutura global
*/
static void search_elements(xmlTextReaderPtr node, TAD_community com){
    
    long id, reputacao, upvotes, downvotes;
    xmlChar *attribVal = NULL, *nameVal = NULL, *bioVal = NULL;
    TAD_REAL_USER user;
    char *nome, *bio;

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
            id = atoi((const char*) attribVal);
            xmlFree(attribVal);
        } 

        attribVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "Reputation");  
        if (attribVal){
            reputacao = atoi((const char*) attribVal);
            xmlFree(attribVal);
        } 

        nameVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "DisplayName");  
        nome = (char*) nameVal;

        bioVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "AboutMe");  
        bio = (char*) bioVal;


        attribVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "UpVotes");  
        if (attribVal){
            upvotes = atoi((const char*) attribVal);
            xmlFree(attribVal);
        }  

        attribVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "DownVotes");  
        if (attribVal){
            downvotes = atoi((const char*) attribVal);
            xmlFree(attribVal);
        } 
        
        user = Real_User();
        setUser(user, reputacao, nome, bio, upvotes, downvotes);
        addUser(id, user, com);

        if (nameVal){
            xmlFree(nameVal);
            nameVal = NULL;
        }

        if (bioVal){
            xmlFree(bioVal);
            bioVal = NULL;
        }
    }
}


/**\brief Percorre todo o fichiero .xml carregando os valores pretendidos para a estrutura global.
@param path - caminho para o respetivo ficheiro .xml
@param com - estrutura global
*/
void usersParser(char* path, TAD_community com){

    LIBXML_TEST_VERSION

    xmlTextReaderPtr tree = NULL;

    if ((tree = xmlReaderForFile(path, NULL, 0)) == NULL ) {
        perror("error: could not parse file");
        exit(1);
    }

    search_elements(tree, com);

    if (tree) xmlFreeTextReader(tree);

    printf("Users parser done!\n");
}
