fullmake: clean mysh

mysh:  myshell.o myString.o command.o myMem.o pipeline.o job.o cmdPath.o pgidTracker.o
	gcc -g myshell.o command.o myString.o myMem.o pipeline.o job.o cmdPath.o pgidTracker.o -o mysh

myshell.o: myshell.c types.h
	gcc -g -c myshell.c -o myshell.o

command.o: command.c command.h
	gcc -g -c command.c -o command.o

myString.o: myString.c myString.h
	gcc -g -c myString.c -o myString.o

myMem.o: myMem.c myMem.h
	gcc -g -c myMem.c -o myMem.o

pipeline.o: pipeline.c pipeline.h types.h
	gcc -g -c pipeline.c -o pipeline.o

job.o: job.c job.h
	gcc -g -c job.c -o job.o

cmdPath.o: cmdPath.c cmdPath.h
	gcc -g -c cmdPath.c -o cmdPath.o

pgidTracker.o: pgidTracker.c pgidTracker.h
	gcc -g -c pgidTracker.c -o pgidTracker.o

mySignal.o: mySignal.c mySignal.h
	gcc -g -c mySignal.c -o mySignal.o


clean:
	rm *.o
