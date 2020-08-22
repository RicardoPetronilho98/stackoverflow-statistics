#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>
#include <string.h>

#include <tagsParser.h>
#include <globalstruct.h>
#include <tags.h>

/**
@file tagsParser.c
Módulo que contém as funções de parser para a estrutura de dados das tags.
*/


/**\brief Percorre os atributos de cada nodo, obtendo os valores pretendidos e carrega-os para a estrutura global.
@param node - nodo atual no ficheiro .xml
@param com - estrutura global
*/
static void search_elements(xmlTextReaderPtr node, TAD_community com){
    
    xmlChar *attribVal = NULL, *tagVal = NULL;
    TAD_TAG tag;
    char *tags;
    long id;

    while(xmlTextReaderRead(node)){    //  enquanto não dá erro ou existe algo para ler

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

        tagVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "TagName");
        tags = (char*) tagVal;
        
        tag = createTag(id, tags);
        addTag(tag,com);

        if (tagVal){
            xmlFree(tagVal);
            tagVal = NULL;
        }
    }
}


/**\brief Percorre todo o fichiero .xml carregando os valores pretendidos para a estrutura global.
@param path - caminho para o respetivo ficheiro .xml
@param com - estrutura global
*/
void tagsParser(char* path, TAD_community com){

    LIBXML_TEST_VERSION

    xmlTextReaderPtr tree = NULL;

    if ((tree = xmlReaderForFile(path, NULL, 0)) == NULL ) {
        perror("error: could not parse file");
        exit(1);
    }

    search_elements(tree, com);

    if (tree) xmlFreeTextReader(tree);

    printf("Tags parser done!\n");
}