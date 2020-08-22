#include <stdio.h>

#include <postsArray.h>
#include <post.h>
#include <globalstruct.h>
#include <load.h>

int main(){

	TAD_POSTS_ARRAY pa = PostsArray();

	TAD_community com = GlobalStruct();
	load(com, "../../../android/");

	TAD_POST p1 = Post(0, 0, 0, "", "2010-03-01");
	TAD_POST p2 = Post(0, 0, 0, "", "2010-02-28");
	// TAD_POST p3 = Post(0, 0, 0, "", "9-5-2018");
	// TAD_POST p4 = Post(0, 0, 0, "", "5-1-2013");
	// TAD_POST p5 = Post(0, 0, 0, "", "23-10-2010");

	addElem(pa, com, p1);
	addElem(pa, com, p2);
	//addElem(pa, p3);
	//addElem(pa, p4);
	//addElem(pa, p5);

	//printf("array ocupados = %d\n", getArraySize(pa));

	//printf( "%s\n", pa2string(pa) );

	/*for(int i = 0; i < getArraySize(pa); i++)
		printf("%d -> ", getElem(i, pa));
	putchar('\n');*/

	//free_Posts_Array(pa);

	return 0;
}