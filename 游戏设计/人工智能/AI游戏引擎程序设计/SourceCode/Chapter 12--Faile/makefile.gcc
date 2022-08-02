CC = gcc
OPT = -O2
FLAGS = -Wall
PROF = -pg

# Release Build:

objects = faile.o utils.o moves.o search.o eval.o hash.o rand.o book.o
headers = extvars.h faile.h protos.h

faile:	$(objects)
	$(CC) -o faile $(objects) -lm

eval.o:	eval.c $(headers)
	$(CC) $(OPT) $(FLAGS) -c -o eval.o eval.c

faile.o:	faile.c $(headers)
	$(CC) $(OPT) $(FLAGS) -c -o faile.o faile.c

utils.o:	utils.c $(headers)
	$(CC) $(OPT) $(FLAGS) -c -o utils.o utils.c

moves.o:	moves.c $(headers)
	$(CC) $(OPT) $(FLAGS) -c -o moves.o moves.c

search.o:	search.c $(headers)
	$(CC) $(OPT) $(FLAGS) -c -o search.o search.c

hash.o:	hash.c $(headers) rand.h
	$(CC) $(OPT) $(FLAGS) -c -o hash.o hash.c

rand.o:	rand.c rand.h
	$(CC) $(OPT) $(FLAGS) -c -o rand.o rand.c

book.o:	book.c $(headers)
	$(CC) $(OPT) $(FLAGS) -c -o book.o book.c

# Profiling Build:

pr_objects = faile_pr.o utils_pr.o moves_pr.o search_pr.o eval_pr.o hash_pr.o \
	rand_pr.o book_pr.o

faile_pr:	$(pr_objects)
	$(CC) $(PROF) -o $(pr_objects)

eval_pr.o:	eval.c $(headers)
	$(CC) $(OPT) $(FLAGS) $(PROF) -c -o eval_pr.o eval.c

faile_pr.o:	faile.c $(headers)
	$(CC) $(OPT) $(FLAGS) $(PROF) -c -o faile_pr.o faile.c

utils_pr.o:	utils.c $(headers)
	$(CC) $(OPT) $(FLAGS) $(PROF) -c -o utils_pr.o utils.c

moves_pr.o:	moves.c $(headers)
	$(CC) $(OPT) $(FLAGS) $(PROF) -c -o moves_pr.o moves.c

search_pr.o:	search.c $(headers)
	$(CC) $(OPT) $(FLAGS) $(PROF) -c -o search_pr.o search.c

hash_pr.o:	hash.c $(headers) rand.h
	$(CC) $(OPT) $(FLAGS) $(PROF) -c -o hash_pr.o hash.c

rand_pr.o:	rand.c rand.h
	$(CC) $(OPT) $(FLAGS) $(PROF) -c -o rand_pr.o rand.c

book_pr.o:	book.c $(headers)
	$(CC) $(OPT) $(FLAGS) $(PROF) -c -o book_pr.o book.c


all:	faile

clean:
	rm -f *.o
	rm -f *.out
	rm -f *~

clean_win:
	del *.o
	del *~

touch:
	touch *.c
	touch *.h
new:
	rm -f *.o
	rm -f *.out
	touch *.c
	touch *.h

profile:	faile_pr

emacs:
	rm -f *~

#EOF
