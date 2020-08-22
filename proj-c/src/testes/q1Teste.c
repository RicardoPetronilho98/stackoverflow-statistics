#include <stdio.h>

#include <pair.h>
#include <interface.h>

int main(){

	TAD_community com = init();

	com = load(com, "../../../ubuntu/");

	STR_pair pair = info_from_post(com, 796430);
    
	com = clean(com);
	return 0;
}