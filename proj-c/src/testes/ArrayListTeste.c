#include <stdio.h>
#include <arrayList.h>

int main(){

	TAD_ARRAY_LIST list = ARRAY_LIST(1);

	long a = 1;
	long b = 2;
	long c = 3;
	long d = 4;

	addElem(list, &a);
	addElem(list, &b);
	addElem(list, &c);
	addElem(list, &d);

	int size = getArraySize(list);
	for (int i = 0; i < size; i++)
		printf("%ld\n", * (long*) getElem(list, i) );

	printf("after malloc()\n"); getchar();

	free_ARRAY_LIST(list);

	printf("after free()\n"); getchar();

	return 0;

}