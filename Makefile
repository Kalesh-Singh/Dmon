all: rules.o main.c
	gcc -std=c99 $^ -o main
rules.o: rules.c rules.h
	gcc -std=c99 -c $< -o $@
.PHONY : clean
clean:
	rm main
