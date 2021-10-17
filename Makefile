build:
	gcc list.c list.h file.c file.h main.c -o fsminishell -std=gnu99

clean: fsminishell
	rm fsminishell

run: fsminishell
	./fsminishell