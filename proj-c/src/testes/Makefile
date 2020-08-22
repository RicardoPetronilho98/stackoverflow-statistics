IDIR=../../include

CC=gcc
CFLAGS = -Wall -std=c11 -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0` -I$(IDIR)
CFILES = $(filter-out ../main.c, $(wildcard ../*.c))
PROFCFILES = $(wildcard ../lib/*.c)
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`

echo_teste:
	echo $(wildcard ../*.c)

compile_load: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) loadTeste.c -o exec $(LIBS)

compile_arrayList: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) ArrayListTeste.c -o exec $(LIBS)

compile_htable: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) htableTeste.c -o exec $(LIBS) 

compile_post: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) postTeste.c -o exec $(LIBS)

compile_user: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) real_userTeste.c -o exec $(LIBS)

compile_pa: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) postsArrayTeste.c -o exec $(LIBS) 

compile_datas: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) datasTeste.c -o exec $(LIBS)   

compile_tags: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) tagsTeste.c -o exec $(LIBS)

compile_q1: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q1Teste.c -o exec $(LIBS)

compile_q2: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q2Teste.c -o exec $(LIBS)

compile_q3: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q3Teste.c -o exec $(LIBS)

compile_q4: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q4Teste.c -o exec $(LIBS)

compile_q5: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q5Teste.c -o exec $(LIBS)

compile_q6: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q6Teste.c -o exec $(LIBS)

compile_q7: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q7Teste.c -o exec $(LIBS)

compile_q8: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q8Teste.c -o exec $(LIBS)

compile_q9: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q9Teste.c -o exec $(LIBS)

compile_q10: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q10Teste.c -o exec $(LIBS)

compile_q11: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q11Teste.c -o exec $(LIBS)

compile_q11_v2: clear
	$(CC) $(CFLAGS) $(CFILES) $(PROFCFILES) q11_v2.c -o exec $(LIBS)

clean:
	rm -r ../../latex ../../html exec

clear:
	clear