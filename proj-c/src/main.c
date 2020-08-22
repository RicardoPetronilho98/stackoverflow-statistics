#include <interface.h>
#include <stdio.h>

// para correr -----> make clean -i && make && time ./program

/**
@file main.c
Módulo que contém a função main usada para testar todas as interrogações.
*/

/**
\brief Função que executa todo o programa
*/
int main(){

	Date data1 = createDate(1, 7, 2016);
	Date data2 = createDate(31, 7, 2016);
	Date data3 = createDate(1, 3, 2013);
	Date data4 = createDate(31, 3, 2013);
	Date data5 = createDate(1, 11, 2015);
	Date data6 = createDate(30, 11, 2015);
	Date data7 =  createDate(1, 8, 2014);
	Date data8 = createDate(11, 8, 2014);

	TAD_community com;

	com = init();

	//com = load(com, "../../android/");
	com = load(com, "../../ubuntu/"); // 0 leaks testada

	printf("getchar() para testar os leaks da load()"); getchar();

	// query 1
	info_from_post(com, 801049);   // 0 leaks testada
	printf("q1() feita\n"); getchar();

	// query 2
	top_most_active(com, 10);
	printf("q2() feita\n"); getchar();

	// query 3
	total_posts(com, data1, data2); // 0 leaks testada
	printf("q3() feita\n"); getchar();

	// query 4
	questions_with_tag(com, "nautilus", data3, data4); // 0 leaks testada
	printf("q4() feita\n"); getchar();

	// query 5
	get_user_info(com, 15811); // 0 leaks testada
	printf("q5() feita\n"); getchar();

	// query 6
	most_voted_answers(com, 5, data5, data6); // 0 leaks testada
	printf("q6() feita\n"); getchar();

	// query 7
	most_answered_questions(com, 10, data7, data8); // 0 leaks testada
	printf("q7() feita\n"); getchar();

	// query 8
	contains_word(com, "kde", 10); // 0 leaks testada
	printf("q8() feita\n"); getchar();

	// query 9
	both_participated(com, 87, 5691, 10); // 0 leaks testada
	printf("q9() feita\n"); getchar();

	// query 10
	better_answer(com, 30334); // 0 leaks testada
	printf("q10() feita\n"); getchar();

	// query 11
	most_used_best_rep(com, 5, createDate(1, 11, 2013), createDate(30, 11, 2013));
	printf("q11() feita\n"); getchar();

	com = clean(com); // 0 leaks testada

	free_date(data1);
	free_date(data2);
	free_date(data3);
	free_date(data4);
	free_date(data5);
	free_date(data6);
	free_date(data7);
	free_date(data8);

	printf("getchar() para testar os leaks após a clean()"); getchar();

	return 0;
} 