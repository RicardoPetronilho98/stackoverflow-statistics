#include <stdio.h>
#include <stdlib.h>

#include <datas.h>
#include <date.h>
#include <globalstruct.h>
#include <interface.h>

int main(void){

	TAD_community com = init();

  	//com = load(com, "../../../android/");
  	com = load(com, "../../../ubuntu/");

  	TAD_DATAS datas = getDatas(com);

  	printf("%s\n", datas2string(datas));

	return 0;
}

