/* Dado um intervalo arbitrário de tempo, devolver as N tags mais usadas 
pelos N utilizadores com melhor reputação. 
Em ordem decrescente do número de vezes em que a tag foi usada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <arrayList.h>
#include <datas.h>
#include <globalstruct.h>
#include <quickSortDates.h>
#include <interface.h>
#include <testa_erro_defines.h>
#include <list.h>
#include <date.h>
#include <stdfunctions.h>


int getTagIdStr(char* str, TAD_ARRAY_LIST tags);
int isInsideTime(Date begin, Date end, Date data);
int postouNoItervalo(TAD_REAL_USER user, TAD_HTABLE posts, Date begin, Date end);

LONG_list most_used_best_rep_v2(TAD_community com, int N, Date begin, Date end){

	TAD_DATAS datas = getDatas(com);
	TAD_ITERATOR it = datasIterator(datas, begin, end);
	TAD_HTABLE users = getUsers(com), posts = getPosts(com);
	TAD_ARRAY_LIST postsList, tags = getTags(com); // array list de (TAD_POST_DATAS) 
	TAD_POST_DATAS postDatas;
	TAD_REAL_USER user;
	TAD_POST post;
	int i, k, tagId, max = 0, tagsSize = getArraySize(tags);
	long user_id, rep, user_ids[N], reps[N];
	for(i = 0; i < N; i++) reps[i] = 0;

	for(i = 0; i < getHtableSize(users); i++){ // percorre a hash table dos users
		if ( ( user = (TAD_REAL_USER) getDadosAtIndex (users, i) ) == NULL || postouNoItervalo(user, posts, begin, end) == 0)  continue;
		user_id = getIdAtIndex(users, i);		
		rep = (long) getReputacao(user);
		insert(reps, user_ids, rep, user_id, N, 1); // quer repetidos
	}

	for(i = 0; i < tagsSize; i++){
		tagId = getTagId(  (TAD_TAG) getElem( tags, i ) );
		if (tagId > max) max = tagId;
	}

	int tagsCount[max];
	for(i = 0; i < max; i++) tagsCount[i] = 0; 

	while( itHasNext(it) ){	
		postsList = itNext(datas, it);	
		for(i = 0; i < getArraySize(postsList); i++){ // para todos os posts	
			postDatas = (TAD_POST_DATAS) getElem(postsList, i);
			if ( elem(user_ids, N, getUserIdFromPost(postDatas)) == 0 || (post = (TAD_POST) getDados( posts, getPostIdFromPost(postDatas))) == NULL || getTipo(post) != 1) continue;
			char** tagsStr = strToTags( getTagsFromPost(post) ); // coleta as tags de cada post
			for(k = 0; tagsStr[k] != (char*) NULL; k++){  // percorre todas as tags de cada post
				tagId = getTagIdStr(tagsStr[k], tags);
				tagsCount[tagId]++;
			}
			// copiar as tags !!! NAO ESQUECER
		}
	}

	long res[N], res2[N];
	for(i = 0; i < N; i++) res[i] = 0;
	for(i = 0; i < max; i++) insert(res, res2, tagsCount[i], i, N, 1); // quer repetidos
	for(i = 0; i < N; i++) printf("tagId = %ld | tagCount = %ld\n", res2[i], res[i]);
	
	return NULL;
}



int getTagIdStr(char* str, TAD_ARRAY_LIST tags){

	int i;
	TAD_TAG tag;

	for(i = 0; i < getArraySize(tags); i++){

		tag = (TAD_TAG) getElem(tags, i);
		if  ( strcmp(getTagName(tag), str) == 0) 
			return getTagId(tag);
	}	
	return -1;
}



int postouNoItervalo(TAD_REAL_USER user, TAD_HTABLE posts, Date begin, Date end){

	long beginSum = getDateSum(begin), endSum = getDateSum(end), dataSum, id;
	TAD_ARRAY_LIST postsList;
	TAD_POST post;
	int i;

	if ( user == NULL || (postsList = getArrayList(user)) == NULL) return 0; // nao tem posts

	for(i = 0; i < getArraySize(postsList); i++){
		id = * (long*) getElem(postsList, i); // postId
		if ( (post = (TAD_POST) getDados(posts, id)) == NULL || getTipo(post) != 1) continue;
		dataSum = getDateSum(getPostData(post));
		if (dataSum >= beginSum && dataSum <= endSum) return 1;
	}

	return 0;
}




int main(){

	
	TAD_community com = GlobalStruct();
	
	//load(com, "../../../android/");
	load(com, "../../../ubuntu/");

	Date begin = createDate(1,11,2013);
	Date end = createDate(30,11,2013);
	most_used_best_rep_v2(com, 5, begin, end);

	com = clean(com);

	return 0;
}



