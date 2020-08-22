#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>	/*	chamadas ao sistema: defs e decls essenciais*/
#include <fcntl.h>	/*	O_RDONLY, O_WRONLY, O_CREAT, O_* (Chamadas ao sistema) */

#include <datas.h>
#include <date.h>
#include <arrayList.h>
#include <quickSortDates.h>

/**
@file datas.c
Módulo que contém as funções de criação, manipulação e destruição da estrutura que organiza os posts pela data.
*/


#define MESES 					12
#define K 					  1024
#define MB 				 1024*1024
#define CAPACIDADE_MIN 			45
#define BUF2PRINT 			  1500	//	isto é para o buffer que é usado para fazer o datas2string();

/**\brief Estrutura que armazena um Post*/
typedef struct TCD_PPOST{
	/**\brief id do post*/
	long post_id;
	/**\brief id do utilizador que criou o post*/
	long user_id;
}*TCD_PPOST;

/**\brief Estrutura que armazena lista de posts consoante a sua data.*/
typedef struct TCD_DATAS{
	/**\brief primeiro ano de informação*/
	int primeiro_ano;
	/**\brief número de anos de informação*/
	int n_anos;
	/**\brief array tri-dimensional que contém os posts, alocados por ano, mês e dia*/
	TAD_ARRAY_LIST*** array_info;
}TCD_DATAS;

/**\brief Estrutura que itera/percorre a Estrutura das Datas.*/
typedef struct TCD_ITERATOR{
	/**\brief arrayList que contém os posts da data cur */
	TAD_ARRAY_LIST arr; // array_info que o iterador aponta neste momento
	/**\brief data atual que o iterator está a apontar*/
	Date cur;
	/**\brief data final do iterador*/
	Date end;

} TCD_ITERATOR;

/**
\brief Faz um free à estrutura TAD_ITERATOR.
@param it - iterador
*/
void free_Iterator(TAD_ITERATOR it){

	if (it){

		// nao faz o free do arrayList pq o freeDatas ja o faz
		if (it->cur){
			free_date(it->cur);
			it->cur = NULL;
		}
		
		if (it->end){
			free_date(it->end);
			it->end = NULL;
		}

		free(it);
		it = NULL;
	}

}

static int bissexto(int ano);
static TAD_ARRAY_LIST getPosts(TAD_DATAS datas,Date data);
static int isDateEqual(Date date1, Date date2);
static Date getNextDate(Date data);
static char* getMes2String(int mes);

/**
\brief Função que calcula o número de dias de um determinado mês.
@param data - data desse mês
@return retorna o número de dias de um mês
*/
int calc_dias(Date data){	
	int ano = get_year(data);
	int mes = get_month(data);

	if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)return 31;
	else if(mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30;		
	else{
		if(bissexto(ano))return 29;
		else return 28;
	}
}

static int bissexto(int ano){
	if(( ano % 4 == 0 && ano % 100 != 0 ) || ano % 400 == 0 )
		return 1;
	return 0;
}

static int isDateEqual(Date date1, Date date2){

	int ano1 = get_year(date1);
	int mes1 = get_month(date1);
	int dia1 = get_day(date1);

	int ano2 = get_year(date2);
	int mes2 = get_month(date2);
	int dia2 = get_day(date2);	

	return ano1 == ano2 && mes1 == mes2 && dia1 == dia2;
} 

/**
\brief Verifica se o Iterador tem um próximo elemento.
@param it - it
@return retorna 1 se existe próximo e 0 caso contrário
*/
int itHasNext(TAD_ITERATOR it){	//	retorn 1 se tem próximo e 0 se não tem;

	return ! isDateEqual(it->cur, it->end);
}


static Date getNextDate(Date data){

	int ano = get_year(data);
	int mes = get_month(data);
	int dia = get_day(data);
	
	int novo_dia, novo_mes, novo_ano, n_dias;

    n_dias = calc_dias(data);
	
	novo_dia = dia + 1;
	novo_mes = mes;
	novo_ano = ano;
	
	if(novo_dia > n_dias){
		novo_dia = 1;
		novo_mes++;
	}
	
	if(novo_mes > 12){
		novo_mes = 1;
		novo_ano++;
	}

    return createDate(novo_dia, novo_mes, novo_ano);
}

//	esta função simplesmente serve para uma melhor leitura do debug;
static char* getMes2String(int mes){

	switch(mes){
		case 1: 
			return "JANEIRO";
			break;
		case 2: 
			return "FEVEREIRO";
			break;
		case 3: 
			return "MARÇO";
			break;
		case 4: 
			return "ABRIL";
			break;
		case 5: 
			return "MAIO";
			break;
		case 6: 
			return "JUNHO";
			break;
		case 7: 
			return "JULHO";
			break;
		case 8: 
			return "AGOSTO";
			break;
		case 9: 
			return "SETEMBRO";
			break;
		case 10: 
			return "OUTUBRO";
			break;
		case 11: 
			return "NOVEMBRO";
			break;
		case 12: 
			return "DEZEMBRO";
			break;
		default:
			perror("DATAS_H:ERRO na função getMes2String(), o mês inserido é inválido, insira um mês entre 0 e 11!");
			exit(1);
			break;
	}
}

static TAD_ARRAY_LIST getPosts(TAD_DATAS datas, Date data){
	
	int ano, mes, dia;

	ano = get_year(data);
	mes = get_month(data);
	dia = get_day(data);

	return datas->array_info[ano-datas->primeiro_ano][mes-1][dia-1];
}

/**
\brief Devolve o ArrayList referente ao iterador.
@param it - iterador
@return retorna o ArrayList referente ao Iterador
*/
TAD_ARRAY_LIST itNext(TAD_DATAS datas, TAD_ITERATOR it){

	Date nextDate = getNextDate(it->cur);
	//printf("ano: %d mes: %d dia: %d\n",get_year(nextDate),get_month(nextDate),get_day(nextDate));
	if (it->cur){
		free_date(it->cur);
		it->cur = NULL;
	}
	
	it->arr = getPosts(datas, nextDate);
	it->cur = nextDate;

	return it->arr;
}


/**
\brief Cria o iterador.
@param datas - posts e respectivas datas
@param begin - data inicial do iterador
@param end - data final do iterador
@return retorna o Iterador
*/
TAD_ITERATOR datasIterator(TAD_DATAS datas, Date begin, Date end){

	int ano = get_year(begin);
	int mes = get_month(begin);
	int dia = get_day(begin);
	Date data = createDate(dia-1, mes, ano);
	Date endClone = createDate(get_day(end), get_month(end), get_year(end));

	if(ano >= datas->primeiro_ano && (ano <= datas->primeiro_ano + datas->n_anos) && mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31){

		TAD_ITERATOR it = malloc(sizeof(TCD_ITERATOR));
		it->arr = NULL;
		it->cur = data;	// isto é para evitar que comece na posição a seguir à que recebemos;
		it->end = endClone;

		return it;
	}

	else{
		perror("data inválida: Iterator() no módulo DATAS_H");
		exit(1);
	}
}

/**
\brief Controi a estrutura que organiza os posts pela data dos mesmos.
@param primeiro_ano - primeiro ano de informação
@param anos - quantos anos de informação 
@return retorna a estrutura dos Posts e as respectivas Datas
*/
TAD_DATAS Datas(int primeiro_ano, int anos){
	
	int ano, mes, dias, dia;

	TAD_DATAS datas = malloc(sizeof(struct TCD_DATAS));
	Date data;
	
	datas->primeiro_ano = primeiro_ano;datas->n_anos = anos;
	
	datas->array_info = malloc(datas->n_anos * sizeof(TAD_ARRAY_LIST**));	//	aloca a memória referente aos anos;
		
	for(ano = 0; ano < (datas->n_anos); ano++){
		
		datas->array_info[ano] = malloc(12 * sizeof(TAD_ARRAY_LIST*));
		
		for(mes = 0; mes < MESES; mes++){
			data = createDate(dia+1,mes+1,ano+datas->primeiro_ano);
			dias = calc_dias(data);
			if (data) free_date(data);
			datas->array_info[ano][mes] = malloc(dias * sizeof(TAD_ARRAY_LIST));
			
			for(dia = 0; dia < dias; dia++){
				datas->array_info[ano][mes][dia] = ARRAY_LIST(CAPACIDADE_MIN);
			}
		}
	}

	return datas;
}

/**
\brief Adiciona um Post consoante a sua Data.
@param datas - posts e respectivas datas
@param data - data em que o Post foi criado
@param user_id - ID do utilizador que fez o Post
*/
void setPostDatas(TAD_DATAS datas, Date data, long user_id, long post_id){
	
	TCD_PPOST post = malloc(sizeof (struct TCD_PPOST));
	post->user_id = user_id;
	post->post_id = post_id;

	addElem(getPosts(datas,data), (void*) post);
}

/**
\brief Devolve o número de Posts numa Data.
@param datas - posts e respectivas datas
@param data - data dos Posts
@return retorna o número de Posts num Data
*/
int getOcupados(TAD_DATAS datas, Date data){
    return getArraySize(getPosts(datas,data));
}

/**
\brief Devolve o ID de Utilizador através do Post do mesmo.
@param post - post
@return retorna o ID do Utilizador deste Post
*/
long getUserIdFromPost(TAD_POST_DATAS post){
   return post->user_id;
}

/**
\brief Devolve o primeiro ano de informação da Estrutura.
@param datas - posts e respectivas datas
@return retorna o primeiro ano de informação
*/
int getPrimeiroAno(TAD_DATAS datas){
	return datas->primeiro_ano;
}

/**
\brief Devolve o número de anos de informação da Estrutura.
@param datas - posts e respectivas datas
@param data - data em que o Post foi criado
@param user_id - ID do utilizador que fez o Post
*/
int getNAnos(TAD_DATAS datas){
	return datas->n_anos;
}


/**
\brief Devolve o ID de um Post através do Post.
@param post - post
@return retorna o ID de um Post através do Post
*/
long getPostIdFromPost(TAD_POST_DATAS post){
	return post->post_id;
}

/**
\brief Faz um free a toda a Estrutura.
@param datas - posts e respectivas datas

*/
void freeDatas(TAD_DATAS datas){

	if (datas){

		int ano, mes, dias, dia, i;
		Date data;

		if (datas->array_info){

			for(ano = 0; ano < (datas->n_anos); ano++){
			
				if (datas->array_info[ano]){
				
					for(mes = 0; mes < MESES; mes++){
						data = createDate(dia+1,mes+1,ano+datas->primeiro_ano);
						dias = calc_dias(data);
						if (data){
							free_date(data);
							data = NULL;
						}
						
						if (datas->array_info[ano][mes]){
							
							for(dia = 0; dia < dias; dia++){

								TAD_ARRAY_LIST list = datas->array_info[ano][mes][dia];
								
								if (list){

									for (i = 0; i < getArraySize(list); i++){
									    TAD_POST_DATAS elem = (TAD_POST_DATAS) getElem (list, i);
									    if (elem){
									    	free(elem);
									    	elem = NULL;
									    }
								  	}

								  	free_ARRAY_LIST(list);
								}
							}

							free(datas->array_info[ano][mes]);
							datas->array_info[ano][mes] = NULL;
						}	
					}

					free(datas->array_info[ano]);
					datas->array_info[ano] = NULL;
				}
			}
		}

		free(datas->array_info);
		datas->array_info = NULL;
	
		free(datas);
		datas = NULL;
	}
}

/**
\brief Devolve uma String com toda a informação da Estrutura.
@param datas - posts e respectivas datas
@return retorna uma String com toda a informação da Estrutura
*/
char* datas2string(TAD_DATAS datas){
	char *fstBuf, *sndBuf;
	int n, size, k=0;
	fstBuf = malloc(BUF2PRINT*MB*sizeof(char));
	TCD_PPOST post;
	TAD_ARRAY_LIST posts;

	Date begin = createDate(1, 1, datas->primeiro_ano); 
	Date end = createDate(31, 12, datas->primeiro_ano + datas->n_anos-1);
	TAD_ITERATOR it = datasIterator(datas, begin, end);
    
	while( itHasNext(it) ){
		posts = itNext(datas, it);
	    for(n = 0; n < getArraySize(posts); n++){
			if(k > BUF2PRINT*MB){
				perror("ULTRAPASSOU O BUFFER: datas2string() on module DATAS_H");
				exit(1);
			}		
			post = (TCD_PPOST) getElem(posts, n);
			sprintf(fstBuf + k,"ano: %d | mes: %s | dia: %d = user_id: %ld | post_id: %ld\n", get_year(it->cur), getMes2String(get_month(it->cur)), get_day(it->cur), post->user_id, post->post_id);	
	    	k = k + strlen(fstBuf + k);
	    } 
	}

	free_Iterator(it);
	
    size = strlen(fstBuf)+1;
	sndBuf = malloc(size*sizeof(char));
	memcpy(sndBuf, fstBuf, size);
	free(fstBuf);
	return sndBuf;
}
