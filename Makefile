all: main.c helper.o
	gcc -std=c99 $^ -o main

helper.o : helper.c helper.h
    gcc -std=c99 -c $< -o $@

.PHONY : clean
clean:
	rm main helper.o
