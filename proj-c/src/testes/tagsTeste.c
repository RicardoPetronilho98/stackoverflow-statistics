#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <interface.h>
#include <tagsParser.h>

#include "../../include/tags.h"

int main(){
	/*
	TAD_TAG tag = createTag(0,"seis",6);
	printf("%s\n",getTagName(tag));
	printf("%d\n",getTagId(tag));
	printf("%d\n",getTagCount(tag));
	printf("%s\n",tag2string(tag));
	freeTag(tag);
	printf("%s\n",tag2string(tag));
	*/


	TAD_community com = init();

	tagsParser("../../../ubuntu/Posts.xml", com);


}

