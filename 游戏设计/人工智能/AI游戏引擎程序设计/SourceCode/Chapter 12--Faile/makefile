CC = cl
LD = link
OPT = /O2 /Oy- /G5 /Gr
FLAGS = -DWIN32

# Release Build:

objects = faile.obj utils.obj moves.obj search.obj eval.obj hash.obj rand.obj \
	book.obj
headers = extvars.h faile.h protos.h

faile:  $(objects)
        $(LD) /out:faile.exe $(objects)

eval.obj:	eval.c $(headers)
        $(CC) $(OPT) $(FLAGS) /c /out:eval.obj eval.c

faile.obj:        faile.c $(headers)
        $(CC) $(OPT) $(FLAGS) /c /out:faile.obj faile.c

utils.obj:        utils.c $(headers)
        $(CC) $(OPT) $(FLAGS) /c /out:utils.obj utils.c

moves.obj:        moves.c $(headers)
        $(CC) $(OPT) $(FLAGS) /c /out:moves.obj moves.c

search.obj:       search.c $(headers)
        $(CC) $(OPT) $(FLAGS) /c /out:search.obj search.c

hash.obj:	hash.c $(headers) rand.h
	$(CC) $(OPT) $(FLAGS) /c /out:hash.obj hash.c

rand.obj:	rand.c rand.h
	$(CC) $(OPT) $(FLAGS) /c /out:rand.obj rand.c

book.obj:	book.c $(headers)
	$(CC) $(OPT) $(FLAGS) /c /out:book.obj book.c


all:	faile

clean:
        del *.obj
        del *~

#EOF
