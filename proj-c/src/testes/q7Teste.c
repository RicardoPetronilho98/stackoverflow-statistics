#include <stdio.h>
#include <stdlib.h>

#include <interface.h>
#include <globalstruct.h>

int main(){

	TAD_community com = init();


  com = load(com, "../../../ubuntu/");
        //load(com, "../../../ubuntu/");
	//printGlobalStruct(com);
	Date begin = createDate(1,8,2014);
	Date end = createDate(11,8,2014);

	LONG_list list = most_answered_questions(com, 10, begin, end);
    
  	for(int i = 0; i < 10; i++)
   		printf("%ld - ", get_list(list, i));
	
	com = clean(com);
    getchar();
	return 0;
}